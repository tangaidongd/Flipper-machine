#pragma once
#include "analyzeByNetwork.h"
#include "afxwin.h"

// CDialogFunCfg 对话框

class CDialogFunCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFunCfg)

public:
	CDialogFunCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogFunCfg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CFG_106_107 };

public:
	void SetAnalyzeNetwork(CAnalyzeNetwork *pAnalyzeNetwork) { m_pAnalyzeNetwork = pAnalyzeNetwork;};
	void UpdateCtrlValue();

private:
	CAnalyzeNetwork*	m_pAnalyzeNetwork;

	int m_nOutAdjust;
	int m_nInAdjust;
	int m_nEnableAdjust;
	int m_nSensorValid;
	int m_nSignSendTime;
	BOOL m_bEnableBit5;
	BOOL m_bEnableBit6;
	BOOL m_bEnableBit7;

	int m_nOutSuccessAdjust;
	int m_nInSuccessAdjust;
	int m_nNoSignEnableAdjust;
	int m_nNoSignAction;
	int m_nNoSignActionAdjust;
	int m_nNoSignAdjustLen;
	int m_nAheadRoll;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	

	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnExit();
	
	
	
	
};
