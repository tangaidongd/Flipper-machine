#pragma once

#include "serialThread.h"
#include "serialport.h"
#include "analyzeCmd.h"
#include "cusCheckBox.h"
#include "..\configByIoStatus.h"
#include "afxwin.h"


#define  WM_SAVE_CONFIG  WM_USER + 10020			//  保存配置
#define  WM_LOAD_CONFIG  WM_USER + 10021			//	加载配置
#define  WM_REFRESH_CONTROL  WM_USER + 10022			//	加载配置

#define  CHECKBOX_NUM	48

// CDataByPollingDlg 对话框

class CDataByPollingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataByPollingDlg)

public:
	CDataByPollingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataByPollingDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_POLLING };

	// void StartPolling();
	// void StopPolling();
	void SetSerialPort(CSerialPort* pSerialPort);
	void SetSerialThread(CSerialThread* pSerialThread);		// 设置工作线程
	void SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol);

	void GetControlValue(std::map<int, STCFData>& mapConfigData);
	void SetControlValue(std::map<int, STCFData>& mapConfigData);
	void RefreshControlValue();

	void  OnRevCmdMsg(STComData& stComData);
	void GetVersion();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

	// 发送
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

	CAnalyzeProtocol*	m_pAnalyzeProtocol;			// 数据转换与协议
	CSerialThread*		m_pSerialThread;			// 设备工作线程
	CSerialPort*		m_pSerialPort;				//	Com设备通讯
	std::vector<CCusCheckBox*> m_vInputStatus;			// IO輸入狀態
	std::vector<CCusCheckBox*> m_vOutPutStatus;			// IO输出状态
	std::vector<CCusCheckBox*> m_vIoStatus;				// 伺服IO状态：	
	std::vector<int>	  m_vAlarmLog;				// 保留所有告警
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
