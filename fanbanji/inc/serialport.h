#pragma once
#include <afxwin.h>
#include <string>


/////////////////////// 串口连接信息
typedef struct STConInfo
{
	int				nBaudrate;					// 波特率
	char			chParity;					// 效验位
	char			chDatabit;					// 数据位
	char			chStopbit;					// 停止位
	char			chSynchronizeflag;			// 是否同步
	std::string		strPortName;				// 端口名称

} STConInfo;

class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();

	// 打开串口,成功返回true，失败返回false
	// portname(串口名): 在Windows下是"COM1""COM2"等，在Linux下是"/dev/ttyS1"等
	// baudrate(波特率): 9600、19200、38400、43000、56000、57600、115200 
	// parity(校验位): 0为无校验，1为奇校验，2为偶校验，3为标记校验（仅适用于windows)
	// databit(数据位): 4-8(windows),5-8(linux)，通常为8位
	// stopbit(停止位): 1为1位停止位，2为2位停止位,3为1.5位停止位
	// synchronizeflag(同步、异步,仅适用与windows): 0为异步，1为同步
	bool Open(const char* pPortname, int nBaudrate, char chParity, char chDatabit, char chStopbit, char chSynchronizeflag=1);

	//关闭串口，参数待定
	void Close();

	//发送数据或写数据，成功返回发送数据长度，失败返回0
	int Send(const void *pBuf,int nLen);

	//接受数据或读数据，成功返回读取实际数据的长度，失败返回0
	int Receive(void *pBuf,int nMaxlen);

	int SendAndRev(const unsigned char* pSenBuf, int nSendLen, char*pRevBuf, int nMaxRevLen);

	bool IsOpen() { return m_bIsOpen;}

private:
	int m_pHandle[16];
	char m_synchronizeflag;
	bool m_bIsOpen;
};