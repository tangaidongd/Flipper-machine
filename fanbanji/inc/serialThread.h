#pragma once
#include <afxwin.h>
#include <queue>
#include <vector>
#include <string>
#include "serialport.h"
#include "publicFun.h"



#define  WM_REV_CMD  WM_USER + 1008			//	����
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

	void SendSpecialPro(u8 chTag);		// ��������Э�飬����					
	//bool SendRevPro(const STComData &stComData, u8* pRevBuf, u32& nRevLen);		// �շ�ָ��

	void SetTcpEvent(bool bIsSignal);
	void SetRunStatus(bool bIsRun){ m_bRuning = bIsRun;}		// ֹͣ�߳�
	void SetRunControlStatus(bool bIsRunControl);				// �Ƿ���ѯ��д��Э�����ʾ״̬
	void SetRunReadStatus(bool bIsRunRead);						// �Ƿ���ѯ��ͨ�������״̬
	void SetParentHand(HWND hHand) { m_hHandleParent = hHand;}	// ��������Ϣ����
	void SetSerialDev(CSerialPort *pSerialPort);				// �����豸
	void SetPutSerialDataPoint(CPutSerialData* pPutSerialData);	// ��Ϣ����

private:
	void SendRevPro(const STComData &stComData);
	//bool SendAndRev(u8* pSenBuf, u32 nSendLen, u8*pRevBuf, u32& nRevLen);


private:
	
	HANDLE			m_hWait;
	bool			m_bRuning;	
	u32				m_nPollControl;						// ��ѯ����
	HWND			m_hHandleParent;					// ������
	char			m_zComDataBuf[MAX_DATA_LEN+1];
	u8				m_zRevDataFinal[50];
	
	CSerialPort*			m_pSerialPort;
	std::vector<STComData>	m_vecAnalyzeProtocol;
	CAnalyzeProtocol		m_AnalyzeProtocol;
	CPutSerialData*			m_pPutSerialData;			// ��ת���ݽṹ
	
	
};
