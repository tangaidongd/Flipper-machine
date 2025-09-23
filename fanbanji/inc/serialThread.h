#pragma once
#include <afxwin.h>
#include <queue>
#include <vector>
#include <string>
#include "serialport.h"
#include "publicFun.h"



#define  WM_REV_CMD  WM_USER + 1008			//	命令
#define  MAX_DATA_LEN	110

class CSerialThread : public CWinThread
{
public:
	CSerialThread();
	~CSerialThread(void);

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();

	void SendSpecialPro(u8 chTag);		// 发送特殊协议，慎用					
	//bool SendRevPro(const STComData &stComData, u8* pRevBuf, u32& nRevLen);		// 收发指令

	void SetTcpEvent(bool bIsSignal);
	void SetRunStatus(bool bIsRun){ m_bRuning = bIsRun;}		// 停止线程
	void SetRunControlStatus(bool bIsRunControl);				// 是否轮询可写入协议的显示状态
	void SetRunReadStatus(bool bIsRunRead);						// 是否轮询普通输入输出状态
	void SetParentHand(HWND hHand) { m_hHandleParent = hHand;}	// 设置收消息窗口
	void SetSerialDev(CSerialPort *pSerialPort);				// 窗口设备
	void SetPutSerialDataPoint(CPutSerialData* pPutSerialData);	// 消息队列

private:
	void SendRevPro(const STComData &stComData);
	//bool SendAndRev(u8* pSenBuf, u32 nSendLen, u8*pRevBuf, u32& nRevLen);


private:
	
	HANDLE			m_hWait;
	bool			m_bRuning;	
	u32				m_nPollControl;						// 轮询控制
	HWND			m_hHandleParent;					// 父窗口
	char			m_zComDataBuf[MAX_DATA_LEN+1];
	u8				m_zRevDataFinal[50];
	
	CSerialPort*			m_pSerialPort;
	std::vector<STComData>	m_vecAnalyzeProtocol;
	CAnalyzeProtocol		m_AnalyzeProtocol;
	CPutSerialData*			m_pPutSerialData;			// 中转数据结构
	
	
};
