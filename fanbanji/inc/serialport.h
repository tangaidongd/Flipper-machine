#pragma once
#include <afxwin.h>
#include <string>


/////////////////////// ����������Ϣ
typedef struct STConInfo
{
	int				nBaudrate;					// ������
	char			chParity;					// Ч��λ
	char			chDatabit;					// ����λ
	char			chStopbit;					// ֹͣλ
	char			chSynchronizeflag;			// �Ƿ�ͬ��
	std::string		strPortName;				// �˿�����

} STConInfo;

class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();

	// �򿪴���,�ɹ�����true��ʧ�ܷ���false
	// portname(������): ��Windows����"COM1""COM2"�ȣ���Linux����"/dev/ttyS1"��
	// baudrate(������): 9600��19200��38400��43000��56000��57600��115200 
	// parity(У��λ): 0Ϊ��У�飬1Ϊ��У�飬2ΪżУ�飬3Ϊ���У�飨��������windows)
	// databit(����λ): 4-8(windows),5-8(linux)��ͨ��Ϊ8λ
	// stopbit(ֹͣλ): 1Ϊ1λֹͣλ��2Ϊ2λֹͣλ,3Ϊ1.5λֹͣλ
	// synchronizeflag(ͬ�����첽,��������windows): 0Ϊ�첽��1Ϊͬ��
	bool Open(const char* pPortname, int nBaudrate, char chParity, char chDatabit, char chStopbit, char chSynchronizeflag=1);

	//�رմ��ڣ���������
	void Close();

	//�������ݻ�д���ݣ��ɹ����ط������ݳ��ȣ�ʧ�ܷ���0
	int Send(const void *pBuf,int nLen);

	//�������ݻ�����ݣ��ɹ����ض�ȡʵ�����ݵĳ��ȣ�ʧ�ܷ���0
	int Receive(void *pBuf,int nMaxlen);

	int SendAndRev(const unsigned char* pSenBuf, int nSendLen, char*pRevBuf, int nMaxRevLen);

	bool IsOpen() { return m_bIsOpen;}

private:
	int m_pHandle[16];
	char m_synchronizeflag;
	bool m_bIsOpen;
};