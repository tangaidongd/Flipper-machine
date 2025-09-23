#include "CClientSocket.h"
#include <time.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


void RevAndSendThread(LPVOID lpParam)
{

}

CClientSocket::CClientSocket()
{
    m_hThreadRevAndSend = NULL;
	m_pNotifyRequestRet = NULL;
	m_hSocket = INVALID_SOCKET;

	CleanQueueSend(m_queueSendRequestWriteData);
	CleanQueueRev(m_queueRevData);
}

CClientSocket::~CClientSocket()
{
}



bool CClientSocket::InitSocket(char* pAddress, char* pPort)
{
	DisConnect();

	 // 初始化Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
		DEBUG_LOG(EM_LOG_ERROR,"WSAStartup failed::  %d", iResult);
        return false;
    }
 
    // 创建socket
    m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_hSocket == INVALID_SOCKET) {
		DEBUG_LOG(EM_LOG_ERROR,"socket failed with error:  %d", WSAGetLastError());
        WSACleanup();
        return false;
    }
 
    // 指定服务器地址和端口
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(pPort));
    inet_pton(AF_INET, pAddress, &serverAddress.sin_addr);
 
	// 设置连接超时
	timeval tm;
	fd_set set;
	int nError = -1;
	int nLen = sizeof(nError);
	unsigned long ul = 1;
	ioctlsocket(m_hSocket, FIONBIO, &ul);

    // 连接到服务器
	bool bConnectRet = false;
    if (connect(m_hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) 
	{
		// 设置超时
		tm.tv_sec = 4;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_hSocket, &set);
		if (select(0, NULL, &set, NULL, &tm) > 0)
		{
			getsockopt(m_hSocket, SOL_SOCKET, SO_ERROR, (char*)&nError, &nLen);
			if (nError == 0)
			{
				bConnectRet = true;
			}
		}
    }

	if (!bConnectRet)
	{
		DEBUG_LOG(EM_LOG_ERROR, "connect failed with error:  %d", WSAGetLastError());
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		WSACleanup();
		return false;
	}

	// 设置回阻塞模式
	ul = 0;
	ioctlsocket(m_hSocket, FIONBIO, &ul);

	// 收发超时时间
	int NetTimeout = 2000;
	setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&NetTimeout, sizeof(int));
	setsockopt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&NetTimeout, sizeof(int));

	// 超时检测
	//DWORD dwError = 0;
	//TCP_KEEPALIVE sKA_Setting = { 0 };

	// 清空收发队列
	CleanQueueSend(m_queueSendRequestWriteData);
	CleanQueueRev(m_queueRevData);

	// 创建收发线程
	CreatThreadRevAndSend();

	return true;
}


void CClientSocket::CloseSocket()
{
    if (INVALID_SOCKET != m_hSocket)
    {
		//shutdown(m_hSocket, SHUT_RD);
        closesocket(m_hSocket);
		WSACleanup();
        m_hSocket = INVALID_SOCKET;
    }
}


bool CClientSocket::GetConnectStatus()
{
	if(m_hSocket == INVALID_SOCKET)
		return false;

	return true;
}

void CClientSocket::DisConnect()
{
	StopThread();
    CloseSocket();
}

void CClientSocket::StopThread()
{
	if (NULL == m_hThreadRevAndSend)
		return;

    m_bExitRevAndSendThread = true;

	int nCycleTime = 5000;
	DWORD timeSt = 0;
	timeSt = GetTickCount();
	while (NULL != m_hThreadRevAndSend)
	{
		if(GetTickCount()-timeSt < nCycleTime)
		{
			Sleep(20);
			continue;
		}
		else
		{
			DWORD dwCode = 0;
			GetExitCodeThread(m_hThreadRevAndSend, &dwCode);
			if(STILL_ACTIVE == dwCode)
			{
				TerminateThread(m_hThreadRevAndSend, 0);
			}
			m_hThreadRevAndSend = NULL;
		}
	}
}

bool CClientSocket::CreatThreadRevAndSend()
{
    StopThread();

    CAutoCriticalSection AutoLock(&s_CriticalSectionByNetWork);

	// 创建线程
	m_bExitRevAndSendThread = false;
    m_hThreadRevAndSend = (void*)_beginthread(RevAndSendThread, 0, this);
	SetThreadPriority(m_hThreadRevAndSend, THREAD_PRIORITY_BELOW_NORMAL);

	return true;
}

bool CClientSocket::PopSendRequestData(STSendDataItem& stDataItem)
{
	CAutoCriticalSection AutoLock(&s_CriticalSectionByNetWork);
	if(m_queueSendRequestWriteData.size() == 0)
		return false;

	stDataItem = m_queueSendRequestWriteData.front();
	m_queueSendRequestWriteData.pop();
	return true;
}

bool CClientSocket::PushBackRevItem(STRevDataItem& stDataItem)
{
	CAutoCriticalSection AutoLock(&s_CriticalSectionByNetWork);

	if(m_queueRevData.size() > 200)
		CleanQueueRev(m_queueRevData);
	
	m_queueRevData.push(stDataItem);
	return true;
}


bool CClientSocket::RevData2SaveItem(unsigned char* pRev, int nRevLen, bool bRevSuccess)
{
	if(nRevLen < 5)
	{
		DEBUG_HEX(EM_LOG_ERROR, "接收数据异常，数据   ", (char*)pRev, nRevLen);
		return false;
	}

	int nTag = pRev[0];
	int nTagStart = pRev[1]|pRev[2]<<8;
	int nTagEnd = pRev[3]|pRev[4]<<8;
	STRevDataItem stDataItem;
	stDataItem.nTagReadOrWrite = nTag;
	stDataItem.nTagStart = nTagStart;
	stDataItem.nTagEnd = nTagEnd;
	stDataItem.bRcvSuccessFlag = bRevSuccess;

	// 借用接收结构体，发送错误信息
	if(bRevSuccess)
		memcpy(stDataItem.zRevBuf, pRev+5, nRevLen - 5);
	PushBackRevItem(stDataItem);

	// 通知上层更新数据
	NotifyRequestResult();
	return true;
}

void CClientSocket::NotifyRequestResult()
{
	if(m_pNotifyRequestRet)
	{
		m_pNotifyRequestRet->RequestRetMsg();
	}
}

void CClientSocket::CleanQueueSend(std::queue<STSendDataItem>& stQueueData)
{
	std::queue<STSendDataItem> empty;
	swap(empty, stQueueData);
}

void CClientSocket::CleanQueueRev(std::queue<STRevDataItem>& stQueueData)
{
	std::queue<STRevDataItem> empty;
	swap(empty, stQueueData);
}

//void CClientSocket::ReConnectThread()
//{
//
//}


void CClientSocket::RevAndSendThread()
{
	char szRevBuf[MAX_BUF_LEN] = {0};
	struct timeval timeout;
	int nFailLimit = 2;
	int nTimeOutCount = 0;		// 超时计数
	while (!m_bExitRevAndSendThread)
	{
		// 看有没有超出总超时时长
		
		if (m_hSocket == INVALID_SOCKET)
			return;

		STSendDataItem stDataItem;
		if (!PopSendRequestData(stDataItem))
		{
			Sleep(50);
			continue;
		}

		// ETIMEDOUT
		// 发送
		int nSendedLen = send(m_hSocket, (const char*)stDataItem.SendBuf, stDataItem.nSendLen, 0);
		if(nSendedLen == -1 || nSendedLen == 0)
		{
			nTimeOutCount++;
			if (nTimeOutCount > nFailLimit)
			{
				m_bExitRevAndSendThread = true; 
			}
				
			DEBUG_HEX(EM_LOG_ERROR, "发送数据失败 ", stDataItem.SendBuf, stDataItem.nSendLen);
			RevData2SaveItem((unsigned char*) stDataItem.SendBuf, stDataItem.nSendLen, false);
			Sleep(50);
			continue;
		}
		nTimeOutCount = 0;

		// 读取
		memset(szRevBuf, 0, MAX_BUF_LEN);
		int nRevCount = 0;
		while(nRevCount < stDataItem.nResposeLen)
		{
			int nRecv = recv(m_hSocket, szRevBuf+nRevCount, MAX_BUF_LEN-nRevCount, 0);
			if(SOCKET_ERROR == nRecv)
			{
				nTimeOutCount++;
				if (nTimeOutCount > nFailLimit)
				{
					m_bExitRevAndSendThread = true; 
				}
				DEBUG_HEX(EM_LOG_ERROR, "接收数据失败 发送数据为 ", stDataItem.SendBuf, stDataItem.nSendLen);
				break;
			}

			if(nRecv == 0)
				break;
			nRevCount += nRecv;
		}

		if (nRevCount != 0)
			nTimeOutCount = 0;

		if ((unsigned char)stDataItem.SendBuf[0] == 0xaa || nRevCount != stDataItem.nResposeLen)
		{
			DEBUG_HEX(EM_LOG_ERROR, "收发异常发送数据  ", stDataItem.SendBuf, stDataItem.nSendLen);
			DEBUG_HEX(EM_LOG_ERROR, "收发异常接收数据  ", szRevBuf, nRevCount);
		}

		if(nRevCount == stDataItem.nResposeLen)
		{
			nTimeOutCount = 0;
			RevData2SaveItem((unsigned char*) szRevBuf, nRevCount, true);
		}
		else
		{
			RevData2SaveItem((unsigned char*) stDataItem.SendBuf, stDataItem.nSendLen, false);
		}
	}
		
	return ;
}


void CClientSocket::RevAndSendThread(LPVOID lpParam)
{
	CClientSocket* pThis = (CClientSocket*)lpParam;
	ASSERT(NULL != pThis);
	if (NULL == pThis)
	{
		return;
	}

	pThis->RevAndSendThread();
	
	pThis->m_hThreadRevAndSend = NULL;

	pThis->DisConnect();
}

void CClientSocket::SendRequestData(STSendDataItem stDataItem)
{
	CAutoCriticalSection AutoLock(&s_CriticalSectionByNetWork);

	if (m_hThreadRevAndSend == NULL)
		return;

	// 200以上数据未处理，就清空
	if(m_queueSendRequestWriteData.size() > 200)
		CleanQueueSend(m_queueSendRequestWriteData);

	m_queueSendRequestWriteData.push(stDataItem);
}

bool CClientSocket::PopRevData(STRevDataItem& stDataItem)
{
	CAutoCriticalSection AutoLock(&s_CriticalSectionByNetWork);
	if(m_queueRevData.size() ==0)
		return false;

	stDataItem = m_queueRevData.front();
	m_queueRevData.pop();
	return true;
}

void CClientSocket::RegisterNotify(CNotifyRequestRet* pNotifyRequestRet)
{
	m_pNotifyRequestRet = pNotifyRequestRet;
	//m_pNotifyRequestRet = pNotifyRequestRet;
}

