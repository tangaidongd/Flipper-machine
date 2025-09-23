#include "serialport.h"
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <windows.h>
#include "publicFun.h"

#define DATA_LEN 110

CSerialPort::CSerialPort()
{
	m_bIsOpen = false;
}

CSerialPort::~CSerialPort()
{

}

bool CSerialPort::Open(const char* pPortname, 
	int nBaudrate, 
	char chParity, 
	char chDatabit, 
	char chStopbit, 
	char chSynchronizeflag)
{
	this->m_synchronizeflag = chSynchronizeflag;
	HANDLE hCom = NULL;
	if (this->m_synchronizeflag)
	{
		//同步方式
		hCom = CreateFileA(pPortname, //串口名
			GENERIC_READ | GENERIC_WRITE, //支持读写
			0, //独占方式，串口不支持共享
			NULL,//安全属性指针，默认值为NULL
			OPEN_EXISTING, //打开现有的串口文件
			0, //0：同步方式，FILE_FLAG_OVERLAPPED：异步方式
			NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL
	}
	else
	{
		//异步方式
		hCom = CreateFileA(pPortname, //串口名
			GENERIC_READ | GENERIC_WRITE, //支持读写
			0, //独占方式，串口不支持共享
			NULL,//安全属性指针，默认值为NULL
			OPEN_EXISTING, //打开现有的串口文件
			FILE_FLAG_OVERLAPPED, //0：同步方式，FILE_FLAG_OVERLAPPED：异步方式
			NULL);//用于复制文件句柄，默认值为NULL，对串口而言该参数必须置为NULL
	}

	if(hCom == (HANDLE)-1)
	{		
		DWORD dw = GetLastError();
		return false;
	}

	//配置缓冲区大小 
	if(! SetupComm(hCom,1024, 1024))
	{
		return false;
	}

	// 配置参数 
	DCB p;
	memset(&p, 0, sizeof(p));
	p.DCBlength = sizeof(p);
	p.BaudRate = nBaudrate; // 波特率
	p.ByteSize = chDatabit; // 数据位

	switch (chParity) //校验位
	{   
	case 0:   
		p.Parity = NOPARITY; //无校验
		break;  
	case 1:   
		p.Parity = ODDPARITY; //奇校验
		break;  
	case 2:
		p.Parity = EVENPARITY; //偶校验
		break;
	case 3:
		p.Parity = MARKPARITY; //标记校验
		break;
	}

	switch(chStopbit) //停止位
	{
	case 1:
		p.StopBits = ONESTOPBIT; //1位停止位
		break;
	case 2:
		p.StopBits = TWOSTOPBITS; //2位停止位
		break;
	case 3:
		p.StopBits = ONE5STOPBITS; //1.5位停止位
		break;
	}

	if(! SetCommState(hCom, &p))
	{
		// 设置参数失败
		return false;
	}

	//超时处理,单位：毫秒
	//总超时＝时间系数×读或写的字符数＋时间常量

	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 100; //读间隔超时
	TimeOuts.ReadTotalTimeoutMultiplier = 30; //读时间系数
	TimeOuts.ReadTotalTimeoutConstant = 200; //读时间常量
	TimeOuts.WriteTotalTimeoutMultiplier = 15; // 写时间系数
	TimeOuts.WriteTotalTimeoutConstant = 200; //写时间常量
	SetCommTimeouts(hCom,&TimeOuts);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//清空串口缓冲区

	memcpy(m_pHandle, &hCom, sizeof(hCom));// 保存句柄


	m_bIsOpen = true;
	return true;
}

void CSerialPort::Close()
{
	m_bIsOpen = false;
	HANDLE hCom = *(HANDLE*)m_pHandle;
	CloseHandle(hCom);
}

int CSerialPort::Send(const void *pBuf,int nLen)
{
	DEBUG_HEX(EM_LOG_INFO, "SendBuf 0x:", (char*)pBuf, nLen);
	HANDLE hCom = *(HANDLE*)m_pHandle;

	if (this->m_synchronizeflag)
	{
		// 同步方式
		DWORD dwBytesWrite = nLen; //成功写入的数据字节数
		BOOL bWriteStat = WriteFile(hCom, //串口句柄
			pBuf, //数据首地址
			dwBytesWrite, //要发送的数据字节数
			&dwBytesWrite, //DWORD*，用来接收返回成功发送的数据字节数
			NULL); //NULL为同步发送，OVERLAPPED*为异步发送
		if (!bWriteStat)
		{
			return 0;
		}
		return dwBytesWrite;
	}
	else
	{
		//异步方式
		DWORD dwBytesWrite = nLen; //成功写入的数据字节数
		DWORD dwErrorFlags; //错误标志
		COMSTAT comStat; //通讯状态
		OVERLAPPED m_osWrite; //异步输入输出结构体

		//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
		memset(&m_osWrite, 0, sizeof(m_osWrite));
		m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, L"WriteEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
		BOOL bWriteStat = WriteFile(hCom, //串口句柄
			pBuf, //数据首地址
			dwBytesWrite, //要发送的数据字节数
			&dwBytesWrite, //DWORD*，用来接收返回成功发送的数据字节数
			&m_osWrite); //NULL为同步发送，OVERLAPPED*为异步发送
		if (!bWriteStat)
		{
			DWORD dw  = GetLastError();
			if (GetLastError() == ERROR_IO_PENDING) //如果串口正在写入
			{
				WaitForSingleObject(m_osWrite.hEvent, 1000); //等待写入事件1秒钟
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误
				CloseHandle(m_osWrite.hEvent); //关闭并释放hEvent内存
				return 0;
			}
		}
		return dwBytesWrite;
	}
}

int CSerialPort::Receive(void *pBuf,int nMaxlen)
{
	HANDLE hCom = *(HANDLE*)m_pHandle;
	if (this->m_synchronizeflag)
	{
		//同步方式
		DWORD wCount = nMaxlen; //成功读取的数据字节数
		BOOL bReadStat = ReadFile(hCom, //串口句柄
			pBuf, //数据首地址
			wCount, //要读取的数据最大字节数
			&wCount, //DWORD*,用来接收返回成功读取的数据字节数
			NULL); //NULL为同步发送，OVERLAPPED*为异步发送
		if (!bReadStat)
		{
			DEBUG_LOG(EM_LOG_ERROR, "receive fail");
			return 0;
		}

		DEBUG_HEX(EM_LOG_INFO, "receive 0x:", (char*)pBuf, wCount);
		return wCount;
	}
	else
	{
		//异步方式
		DWORD wCount = nMaxlen; //成功读取的数据字节数
		DWORD dwErrorFlags; //错误标志
		COMSTAT comStat; //通讯状态
		OVERLAPPED m_osRead; //异步输入输出结构体

		//创建一个用于OVERLAPPED的事件处理，不会真正用到，但系统要求这么做
		memset(&m_osRead, 0, sizeof(m_osRead));
		m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误，获得设备当前状态
		if (!comStat.cbInQue)return 0; //如果输入缓冲区字节数为0，则返回false

		BOOL bReadStat = ReadFile(hCom, //串口句柄
			pBuf, //数据首地址
			wCount, //要读取的数据最大字节数
			&wCount, //DWORD*,用来接收返回成功读取的数据字节数
			&m_osRead); //NULL为同步发送，OVERLAPPED*为异步发送
		if (!bReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING) //如果串口正在读取中
			{
				//GetOverlappedResult函数的最后一个参数设为TRUE
				//函数会一直等待，直到读操作完成或由于错误而返回
				GetOverlappedResult(hCom, &m_osRead, &wCount, TRUE);
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //清除通讯错误
				CloseHandle(m_osRead.hEvent); //关闭并释放hEvent的内存
				DEBUG_LOG(EM_LOG_ERROR, "receive fail");
				return 0;
			}
		}

		//DEBUG_HEX("receive 0x:", (char*)buf, wCount);
		return wCount;
	}
}

int CSerialPort::SendAndRev(const unsigned char* pSenBuf, int nSendLen, char*pRevBuf, int nMaxRevLen)
{
	CAutoCriticalSection AutoLock(&s_CriticalSection);

	if (!IsOpen())
	{
		return 0;
	}

	const int RECV_TIMEOUT = 500;
	char zComDataBuf[DATA_LEN] = {0};
	int nRevDataLen = 0;
	int nRev = Send(pSenBuf, nSendLen);
	if (nRev > 0)
	{
		// 增加定时收功能
		DWORD timeSt = 0;
		timeSt = GetTickCount();
		memset(zComDataBuf, 0, DATA_LEN);
		while(1)
		{
			if(GetTickCount()-timeSt > RECV_TIMEOUT)
			{
				DEBUG_HEX(EM_LOG_ERROR, "发送命令超时，发送命令为：", (char*)pSenBuf, nSendLen);
				DEBUG_HEX(EM_LOG_ERROR, "发送命令超时，接收数据为：", zComDataBuf, nRevDataLen);
				break;
			}

			nRev = Receive(zComDataBuf + nRevDataLen, nMaxRevLen - nRevDataLen);
			if (nRev == 0)
			{
				Sleep(20);
				continue;
			}

			nRevDataLen += nRev;
			if (nRevDataLen == nMaxRevLen)
			{
				break;
			}
		}

		memcpy(pRevBuf, zComDataBuf, nRevDataLen);
	}
	else
	{
		DEBUG_HEX(EM_LOG_ERROR, "发送数据失败，发送命令为：", (char*)pSenBuf, nSendLen);
	}

	return nRevDataLen;
}
