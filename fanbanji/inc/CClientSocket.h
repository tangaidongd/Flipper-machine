#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <queue>
#include <sstream>
#include "publicFun.h"

#pragma comment(lib,"Ws2_32.lib")

#define MAX_BUF_LEN 530

struct STSendDataItem
{
	int nSendLen;
	int nResposeLen;
	char SendBuf[MAX_BUF_LEN];		// 数据缓冲区	

	STSendDataItem()
	{
		nSendLen = 0;
		nResposeLen = 0;
		memset(SendBuf, 0, MAX_BUF_LEN);
	};
};

struct STRevDataItem
{
	int nTagReadOrWrite;
	int nTagStart;
	int nTagEnd;
	bool bRcvSuccessFlag;
	char zRevBuf[MAX_BUF_LEN];		// 数据缓冲区

	STRevDataItem()
	{
		nTagReadOrWrite = 01;
		nTagStart = 0;
		nTagEnd = 0;
		bRcvSuccessFlag = true;
		memset(zRevBuf, 0, MAX_BUF_LEN);
	};
};

// 通知更新数据
class CNotifyRequestRet
{
public:
	~CNotifyRequestRet(){}
	virtual void RequestRetMsg() = 0;			
};


class CClientSocket
{
public:
	CClientSocket();
	~CClientSocket();

	bool InitSocket(char* pAddress, char* pPort);
	

	void DisConnect();

	bool GetConnectStatus();
	

	void SendRequestData(STSendDataItem stDataItem);
	bool PopRevData(STRevDataItem& stDataItem);
	void RegisterNotify(CNotifyRequestRet* pNotifyRequestRet);

	
private: 
	void CloseSocket();
	void StopThread();
	bool CreatThreadRevAndSend();

	void RevAndSendThread();
	bool PopSendRequestData(STSendDataItem& stDataItem);
	bool PushBackRevItem(STRevDataItem& stDataItem);

	// 借用接收结构体，发送错误信息, 接收错误时，也发送结构体到上层
	bool RevData2SaveItem(unsigned char* pRev, int nRevLen, bool bRevSuccess = true);

	void NotifyRequestResult();

	void CleanQueueSend(std::queue<STSendDataItem>& stQueueData);
	void CleanQueueRev(std::queue<STRevDataItem>& stQueueData);

	//void ReConnectThread();

	static void	RevAndSendThread(LPVOID lpParam);
private:
	SOCKET	m_hSocket;
	HANDLE	m_hThreadRevAndSend;
	bool	m_bExitRevAndSendThread;
	CNotifyRequestRet*	m_pNotifyRequestRet;

	

	std::queue<STSendDataItem> m_queueSendRequestWriteData;
	std::queue<STRevDataItem> m_queueRevData;
	

private:


};

