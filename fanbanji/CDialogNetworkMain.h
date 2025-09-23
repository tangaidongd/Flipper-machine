#pragma once
#include "CDialogReadOnly.h"
#include "CDialogConfig.h"
#include "inc/analyzeByNetwork.h"
#include "inc/CCusButton.h"
#include "CDialogConfigV2.h"
#include "CDialogMsgBox.h"
#include "CDialogVersionChoice.h"

// CDialogNetworkMain 对话框
#define  WM_REV_UPDATE_ALARM  WM_USER + 1073			//	命令

class CDialogNetworkMain : public CDialogEx
{

public:
	CDialogNetworkMain(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogNetworkMain();


	enum { IDD = IDD_DIALOG_NET_MAIN };


private:
	void InitControl();

	void UpdateSomeCtrlValue();
	void RefreshDialogData(STRevDataItem& stRevDataItem);
	void ResponseStatusTip(STRevDataItem& stRevDataItem);

	void EnableDialog(bool bEnable);


	void CusMsgBox(CString strMsg);

private:
	CDialogReadOnly*	m_pDialogReadOnly;
	CDialogConfig*		m_pDialogConfig;
	CDialogConfigV2*	m_pDialogConfigV2;
	CDialogMsgBox*		m_pDialogMsgBox;
	CVersionChoice*		m_pVersionChoice;
	CAnalyzeNetwork		m_AnalyzeNetwork;
	CRect	m_rcCaptionHight;
	BOOL	m_bReConnect;

	CCusButton		m_CusButton[10];


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void AddTray();
	void DelTray();

	afx_msg void OnBtnMinimize();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnNormal();
	afx_msg void OnBnClickedBtnCfg();
	LRESULT OnRevUpdateConnect(WPARAM wParam, LPARAM lParam);
	LRESULT OnRevUpdateRollBoardType (WPARAM wParam, LPARAM lParam);
	LRESULT OnRevDataUpdate(WPARAM wParam, LPARAM lParam);
	LRESULT OnShowSoftWnd(WPARAM wParam, LPARAM lParam);
	// LRESULT OnRevAlarmUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnCfg2();
	afx_msg void OnBnClickedBtnCfg3();
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
