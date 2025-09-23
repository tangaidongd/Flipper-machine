#pragma once

#include "serialThread.h"
#include "serialport.h"
#include "analyzeCmd.h"
#include "cusCheckBox.h"
#include "..\configByIoStatus.h"
#include "afxwin.h"


#define  WM_SAVE_CONFIG  WM_USER + 10020			//  ��������
#define  WM_LOAD_CONFIG  WM_USER + 10021			//	��������
#define  WM_REFRESH_CONTROL  WM_USER + 10022			//	��������

#define  CHECKBOX_NUM	48

// CDataByPollingDlg �Ի���

class CDataByPollingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataByPollingDlg)

public:
	CDataByPollingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataByPollingDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_POLLING };

	// void StartPolling();
	// void StopPolling();
	void SetSerialPort(CSerialPort* pSerialPort);
	void SetSerialThread(CSerialThread* pSerialThread);		// ���ù����߳�
	void SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol);

	void GetControlValue(std::map<int, STCFData>& mapConfigData);
	void SetControlValue(std::map<int, STCFData>& mapConfigData);
	void RefreshControlValue();

	void  OnRevCmdMsg(STComData& stComData);
	void GetVersion();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	void InitControlPoint();

	void ShkeHands(STComData &stComData);
	void QueryVersion(STComData &stComData);
	void QueryInput(STComData &stComData);
	void QueryOutput(STComData &stComData);
	void QueryIoStatus(STComData &stComData);
	void QueryWorkStatus(STComData &stComData);
	void QueryRollSpeed(STComData &stComData);
	void QueryFlipSpeed(STComData &stComData);
	void QueryPulsesCount(STComData &stComData);
	void QueryActionTime(STComData &stComData);
	void QueryCompleteSignalDelay(STComData &stComData);

	void QueryLastTimeConsuming(STComData &stComData);
	void QueryAlarmNum(STComData &stComData);
	void QueryAlarmLog(STComData &stComData);

	// ����
	void RollEvent();
	void SendRoll(int nParam1, int nParam2, int nParam3, bool bDisBox = true);
	
	void FlipEvent();
	void SendFlip(int nParam1, int nParam2, bool bDisBox = true);

	void PulsesEvent();
	void SentPulses(int nParam1, bool bDisBox = true);

	void SentAction(int nParam1, int nParam2, int nParam3, bool bDisBox = true);
	void ActionEvent();

	void SentDelay(int nParam1, int nParam2, bool bDisBox = true);
	void DelayEvent();


	void SetStaticValue(unsigned int nControlID, unsigned int nValue);
	void GetEditValue(unsigned int nControlID, CString& strValue);
	void BoxCustom(CString strMsg, bool disBox = true);

	
private:
	CButton m_checkboxControl1;
	CButton m_checkboxStatus;

	CAnalyzeProtocol*	m_pAnalyzeProtocol;			// ����ת����Э��
	CSerialThread*		m_pSerialThread;			// �豸�����߳�
	CSerialPort*		m_pSerialPort;				//	Com�豸ͨѶ
	std::vector<CCusCheckBox*> m_vInputStatus;			// IOݔ���B
	std::vector<CCusCheckBox*> m_vOutPutStatus;			// IO���״̬
	std::vector<CCusCheckBox*> m_vIoStatus;				// �ŷ�IO״̬��	
	std::vector<int>	  m_vAlarmLog;				// �������и澯
	CCusCheckBox m_zCusCheckBox[CHECKBOX_NUM];
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton13();
	
	afx_msg void OnBnClickedBtnRoll1();
	afx_msg void OnBnClickedBtnFlip1();
	afx_msg void OnBnClickedBtnPulses1();
	afx_msg void OnBnClickedBtnAction1();
	afx_msg void OnBnClickedBtnDelay1();
	
	afx_msg void OnBnClickedCheckControl1();
	afx_msg void OnBnClickedBtnRollRefresh();
	afx_msg void OnBnClickedBtnActionRefresh();
	afx_msg void OnBnClickedBtnFlibRefresh();
	afx_msg void OnBnClickedBtnDelayRefresh();
	afx_msg void OnBnClickedBtnPuleseRefresh();
	afx_msg void OnBnClickedCheckStatus1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedButtonRefresh();
	
	afx_msg void OnBnClickedBtnIoStatus();
	afx_msg void OnBnClickedBtnClean();
};
