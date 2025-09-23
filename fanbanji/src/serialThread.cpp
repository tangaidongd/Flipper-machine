#include "serialThread.h"
#include "publicFun.h"
#include <afxwin.h>


CSerialThread::CSerialThread()
{
	m_bRuning = false;
	//m_nPollControl = EM_TYPE_CONTROL & EM_TYPE_READ;
	m_nPollControl =  EM_TYPE_STATUS;
	m_pPutSerialData = NULL;
	m_hHandleParent	 = NULL;
	
	m_AnalyzeProtocol.InitProtocolVec();
	m_AnalyzeProtocol.GetProtocolVec(m_vecAnalyzeProtocol);

	memset(m_zComDataBuf, 0, sizeof(m_zComDataBuf));
	memset(m_zRevDataFinal, 0, sizeof(m_zRevDataFinal));

	m_hWait = ::CreateEvent(NULL, true, true, NULL);
	
}


CSerialThread::~CSerialThread(void)
{

}

BOOL CSerialThread::InitInstance()
{
	return true;
}

int CSerialThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

void CSerialThread::SendRevPro(const STComData &stComData)
{
	unsigned char	zRevData[50+1] = {0};	// 数据
	int nMustRevLen = m_AnalyzeProtocol.GetProtocolLen(stComData.zData[1], false);
	int nRevDataLen = m_pSerialPort->SendAndRev(stComData.zData, stComData.nDataLen, (char*)zRevData, nMustRevLen);

	// 经过多次接收之后，认为数据已接收完成, 大于1是因为一场代码为0xdd **
	if( nRevDataLen < 2)
	{
		// 只接受到一个一个字节以下，放弃数据
		DEBUG_LOG(EM_LOG_INFO, "接收数据长度异常 长度为：%d", nRevDataLen);
		DEBUG_HEX(EM_LOG_INFO, "接收数据为:", (char*)zRevData, nRevDataLen);
		return ;
	}
	
	STComData stRevComData;
	stRevComData.chTag = zRevData[1];
	stRevComData.nDataLen = nRevDataLen;
	memcpy(stRevComData.zData, zRevData, nRevDataLen);

	m_pPutSerialData->PushSerialData(stRevComData);
	// 通知父窗口提取数据
	if(m_hHandleParent)
	{
		PostMessage(m_hHandleParent, WM_REV_CMD, 0, 0);
	}
}
//
//bool CSerialThread::SendRevPro(const STComData &stComData, u8* pRevBuf, u32& nRevLen)
//{
//	unsigned char	zRevData[50+1] = {0};	// 数据
//	int nMustRevLen = m_AnalyzeProtocol.GetProtocolLen(stComData.zData[1], false);
//	int nRevDataLen = m_pSerialPort->SendAndRev(stComData.zData, stComData.nDataLen, (char*)zRevData, nMustRevLen);
//	if (nRevLen > 0)
//	{
//		nRevLen = nRevDataLen;
//		memcpy(pRevBuf, zRevData, nRevLen);
//		return true;
//	}
//
//	return false;
//}
//
//bool CSerialThread::SendAndRev(u8* pSenBuf, u32 nSendLen, u8*pRevBuf, u32& nRevLen)
//{
//	const int RECV_TIMEOUT = 100;
//	int nRevDataLen = 0;
//	int nMustRevLen = m_AnalyzeProtocol.GetProtocolLen(pSenBuf[1], false);
//	int nRev = m_pSerialPort->Send(pSenBuf, nSendLen);
//	if (nRev > 0)
//	{
//		// 增加定时收功能
//		while(1)
//		{
//			DWORD timeSt = 0;
//			timeSt = GetTickCount();
//			if(GetTickCount()-timeSt > RECV_TIMEOUT)
//			{
//				DEBUG_HEX("发送命令超时，发送命令为：", (char*)pSenBuf, nSendLen);
//				DEBUG_HEX("发送命令超时，接收数据为：", m_zComDataBuf, nRevDataLen);
//				break;
//			}
//
//			memset(m_zComDataBuf, 0, MAX_DATA_LEN);
//			nRev = m_pSerialPort->Receive(m_zComDataBuf + nRevDataLen, nMustRevLen - nRevDataLen);
//			if (nRev == 0)
//			{
//				Sleep(20);
//				continue;
//			}
//
//			nRevDataLen += nRev;
//			if (nRevDataLen == nMustRevLen)
//			{
//				break;
//			}
//		}
//
//		// 经过多次接收之后，认为数据已接收完成, 大于1是因为一场代码为0xdd **
//		if(nRevDataLen > 0 && nRevDataLen >1)
//		{
//			memcpy(pRevBuf, m_zComDataBuf, nRevDataLen);
//			nRevLen = nRevDataLen;
//			return true;
//		}
//		else
//		{
//			// 只接受到一个一个字节以下，放弃数据
//			DEBUG_LOG("接收数据长度异常 长度为：%d", nRevDataLen);
//			DEBUG_HEX("接收数据为:", (char*)pRevBuf, nRevDataLen);
//			return false;
//		}
//	}
//
//	return false;
//}

int CSerialThread::Run()
{
	if(!m_pSerialPort || !m_pPutSerialData || m_vecAnalyzeProtocol.size()< 1)
		return 0;

	int nSendIndex = 0;
	int nProtolNum = m_vecAnalyzeProtocol.size();
	while(m_bRuning)
	{
		try
		{
			// 线程暂停
			if(WaitForSingleObject(m_hWait, -1) == WAIT_TIMEOUT)
			{
				return false;
			}

			// 避免板子压力，查询一轮多休息一段时间
			int nIndex = nSendIndex++ % nProtolNum;

			// 过滤部分协议
			STComData stComData = m_vecAnalyzeProtocol.at(nIndex);
			if((stComData.nProtocolType & EM_TYPE_CONTROL) && !(m_nPollControl & EM_TYPE_CONTROL))
			{
				continue;
			}
			// 非read指令不读
			if((stComData.nProtocolType & EM_TYPE_STATUS))
			{
				if (!(m_nPollControl & EM_TYPE_STATUS))
				{
					continue;
				}

				if (!(stComData.nProtocolType & EM_TYPE_READ))
				{
					continue;
				}
			}

			SendRevPro(stComData);
		}
		catch (std::string err)
		{
			CString strErrMsg;
			strErrMsg.Format(_T("TCP执行流程捕捉到异常信息:%s"), err.c_str());
		}
		catch (...)
		{
			std::string strErrMsg = "线程执行异常!";
		}

		if (nSendIndex%nProtolNum == 0)
		{
			Sleep(1000);
			nSendIndex = 0;
		}
		else
		{
			Sleep(85);
		}
		
	}

	OutputDebugStringA("thread end ===============\r\n");
	
	return 0;
}



void CSerialThread::SendSpecialPro(u8 chTag)
{
	if(!m_pSerialPort || !m_pPutSerialData || m_vecAnalyzeProtocol.size()< 1)
		return ;

	for (int i = 0; i < m_vecAnalyzeProtocol.size(); ++i)
	{
		if (chTag == m_vecAnalyzeProtocol.at(i).chTag)
		{
			STComData stComDate = m_vecAnalyzeProtocol.at(i);
			SendRevPro(stComDate);
			break;
		}
	}
}

void CSerialThread::SetTcpEvent(bool bIsSignal)
{
	if (bIsSignal)
	{
		::SetEvent(m_hWait);
	}
	else
	{
		::ResetEvent(m_hWait);;
	}
}

void CSerialThread::SetRunControlStatus(bool bIsRunControl)
{
	if (bIsRunControl)
	{
		m_nPollControl = m_nPollControl | EM_TYPE_CONTROL;
	}
	else
	{
		m_nPollControl = m_nPollControl & (~EM_TYPE_CONTROL);
	}
}


void CSerialThread::SetRunReadStatus(bool bIsRunRead)
{
	if (bIsRunRead)
	{
		m_nPollControl = m_nPollControl | EM_TYPE_STATUS;
	}
	else
	{
		m_nPollControl = m_nPollControl & (~EM_TYPE_STATUS);
	}
}

void CSerialThread::SetPutSerialDataPoint(CPutSerialData* pPutSerialData)
{
	m_pPutSerialData  = pPutSerialData;
}

void CSerialThread::SetSerialDev(CSerialPort *pSerialPort)
{
	m_pSerialPort = pSerialPort;
}


