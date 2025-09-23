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
		//ͬ����ʽ
		hCom = CreateFileA(pPortname, //������
			GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
			0, //��ռ��ʽ�����ڲ�֧�ֹ���
			NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
			OPEN_EXISTING, //�����еĴ����ļ�
			0, //0��ͬ����ʽ��FILE_FLAG_OVERLAPPED���첽��ʽ
			NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL
	}
	else
	{
		//�첽��ʽ
		hCom = CreateFileA(pPortname, //������
			GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
			0, //��ռ��ʽ�����ڲ�֧�ֹ���
			NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
			OPEN_EXISTING, //�����еĴ����ļ�
			FILE_FLAG_OVERLAPPED, //0��ͬ����ʽ��FILE_FLAG_OVERLAPPED���첽��ʽ
			NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL
	}

	if(hCom == (HANDLE)-1)
	{		
		DWORD dw = GetLastError();
		return false;
	}

	//���û�������С 
	if(! SetupComm(hCom,1024, 1024))
	{
		return false;
	}

	// ���ò��� 
	DCB p;
	memset(&p, 0, sizeof(p));
	p.DCBlength = sizeof(p);
	p.BaudRate = nBaudrate; // ������
	p.ByteSize = chDatabit; // ����λ

	switch (chParity) //У��λ
	{   
	case 0:   
		p.Parity = NOPARITY; //��У��
		break;  
	case 1:   
		p.Parity = ODDPARITY; //��У��
		break;  
	case 2:
		p.Parity = EVENPARITY; //żУ��
		break;
	case 3:
		p.Parity = MARKPARITY; //���У��
		break;
	}

	switch(chStopbit) //ֹͣλ
	{
	case 1:
		p.StopBits = ONESTOPBIT; //1λֹͣλ
		break;
	case 2:
		p.StopBits = TWOSTOPBITS; //2λֹͣλ
		break;
	case 3:
		p.StopBits = ONE5STOPBITS; //1.5λֹͣλ
		break;
	}

	if(! SetCommState(hCom, &p))
	{
		// ���ò���ʧ��
		return false;
	}

	//��ʱ����,��λ������
	//�ܳ�ʱ��ʱ��ϵ��������д���ַ�����ʱ�䳣��

	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 100; //�������ʱ
	TimeOuts.ReadTotalTimeoutMultiplier = 30; //��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutConstant = 200; //��ʱ�䳣��
	TimeOuts.WriteTotalTimeoutMultiplier = 15; // дʱ��ϵ��
	TimeOuts.WriteTotalTimeoutConstant = 200; //дʱ�䳣��
	SetCommTimeouts(hCom,&TimeOuts);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//��մ��ڻ�����

	memcpy(m_pHandle, &hCom, sizeof(hCom));// ������


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
		// ͬ����ʽ
		DWORD dwBytesWrite = nLen; //�ɹ�д��������ֽ���
		BOOL bWriteStat = WriteFile(hCom, //���ھ��
			pBuf, //�����׵�ַ
			dwBytesWrite, //Ҫ���͵������ֽ���
			&dwBytesWrite, //DWORD*���������շ��سɹ����͵������ֽ���
			NULL); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bWriteStat)
		{
			return 0;
		}
		return dwBytesWrite;
	}
	else
	{
		//�첽��ʽ
		DWORD dwBytesWrite = nLen; //�ɹ�д��������ֽ���
		DWORD dwErrorFlags; //�����־
		COMSTAT comStat; //ͨѶ״̬
		OVERLAPPED m_osWrite; //�첽��������ṹ��

		//����һ������OVERLAPPED���¼��������������õ�����ϵͳҪ����ô��
		memset(&m_osWrite, 0, sizeof(m_osWrite));
		m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, L"WriteEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
		BOOL bWriteStat = WriteFile(hCom, //���ھ��
			pBuf, //�����׵�ַ
			dwBytesWrite, //Ҫ���͵������ֽ���
			&dwBytesWrite, //DWORD*���������շ��سɹ����͵������ֽ���
			&m_osWrite); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bWriteStat)
		{
			DWORD dw  = GetLastError();
			if (GetLastError() == ERROR_IO_PENDING) //�����������д��
			{
				WaitForSingleObject(m_osWrite.hEvent, 1000); //�ȴ�д���¼�1����
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ����
				CloseHandle(m_osWrite.hEvent); //�رղ��ͷ�hEvent�ڴ�
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
		//ͬ����ʽ
		DWORD wCount = nMaxlen; //�ɹ���ȡ�������ֽ���
		BOOL bReadStat = ReadFile(hCom, //���ھ��
			pBuf, //�����׵�ַ
			wCount, //Ҫ��ȡ����������ֽ���
			&wCount, //DWORD*,�������շ��سɹ���ȡ�������ֽ���
			NULL); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
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
		//�첽��ʽ
		DWORD wCount = nMaxlen; //�ɹ���ȡ�������ֽ���
		DWORD dwErrorFlags; //�����־
		COMSTAT comStat; //ͨѶ״̬
		OVERLAPPED m_osRead; //�첽��������ṹ��

		//����һ������OVERLAPPED���¼��������������õ�����ϵͳҪ����ô��
		memset(&m_osRead, 0, sizeof(m_osRead));
		m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
		if (!comStat.cbInQue)return 0; //������뻺�����ֽ���Ϊ0���򷵻�false

		BOOL bReadStat = ReadFile(hCom, //���ھ��
			pBuf, //�����׵�ַ
			wCount, //Ҫ��ȡ����������ֽ���
			&wCount, //DWORD*,�������շ��سɹ���ȡ�������ֽ���
			&m_osRead); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING) //����������ڶ�ȡ��
			{
				//GetOverlappedResult���������һ��������ΪTRUE
				//������һֱ�ȴ���ֱ����������ɻ����ڴ��������
				GetOverlappedResult(hCom, &m_osRead, &wCount, TRUE);
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ����
				CloseHandle(m_osRead.hEvent); //�رղ��ͷ�hEvent���ڴ�
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
		// ���Ӷ�ʱ�չ���
		DWORD timeSt = 0;
		timeSt = GetTickCount();
		memset(zComDataBuf, 0, DATA_LEN);
		while(1)
		{
			if(GetTickCount()-timeSt > RECV_TIMEOUT)
			{
				DEBUG_HEX(EM_LOG_ERROR, "�������ʱ����������Ϊ��", (char*)pSenBuf, nSendLen);
				DEBUG_HEX(EM_LOG_ERROR, "�������ʱ����������Ϊ��", zComDataBuf, nRevDataLen);
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
		DEBUG_HEX(EM_LOG_ERROR, "��������ʧ�ܣ���������Ϊ��", (char*)pSenBuf, nSendLen);
	}

	return nRevDataLen;
}
