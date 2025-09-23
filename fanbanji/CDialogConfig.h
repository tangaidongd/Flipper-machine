#pragma once


// CDialogConfig 对话框
#include "inc/analyzeByNetwork.h"
#include "afxwin.h"

#define  WM_UPDATE_ROLL_BOARD WM_USER + 1087

class CDialogConfig : public CDialogEx
{

public:
	CDialogConfig(CAnalyzeNetwork* pAnalyzeNetwork, CWnd* pParent = nullptr);   // 标准构造函数
	CDialogConfig(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogConfig();


	enum { IDD = IDD_DIALOG_CONFIG };


public:
	void UpdateCtrlValue();

	// 单机自动化文字
	void SignleAutoRunDisplayIo(bool bIsAuto);

private:
	void InitCtrlValue();
	void LinkTransValueFunc(int nCtrlId, int nToCtrlID);
	void LinkValueDisplay(int nCtrlID, int nDisplayID);
	void LinkRotateSpeedUpTime(int nCtrlQuick, int nCtrlInit, int nCtrlSpeedUp);
	void LinkRotateSlowDownTime(int nCtrlQuick, int nCtrlSlow, int nCtrlSpeedUp);
	void LinkZeroAndNoZeroTime(int nCtrlID, int nDisCtrlID);

	void LinkRotateSpeedupAngle(int nRotateBegin, int nRotateQuick, int nRotateSpeedupTime);
	void LinkRotateSlowDownAngle(int nQuickAngle, int nRotateQuick, int nRotateSlow, int nRotateSpeedupTime);


private:
	CAnalyzeNetwork* m_pAnalyzeNetwork;
	int m_nRollBoardType;				// 翻版选择，是单机自动化还是普通类型
	
	CComboBox m_combTag100;
	CComboBox m_combTag101;
	CComboBox m_combTag102;
	CComboBox m_combTag103;
	CComboBox m_combTag104;
	CComboBox m_combTag105;
	CComboBox m_combTag105_1;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();

	afx_msg void OnEnChangeEditTag161();
	afx_msg void OnEnChangeEditTag163();
	afx_msg void OnEnChangeEditTag165();
	afx_msg void OnEnChangeEditTag167();
	afx_msg void OnEnChangeEditTag169();


	afx_msg void OnEnChangeEditTag175();
	afx_msg void OnEnChangeEditTag177();
	afx_msg void OnEnChangeEditTag181();
	afx_msg void OnEnChangeEditTag159();
	afx_msg void OnEnChangeEditTag173();
	afx_msg void OnEnChangeEditTag157();
	afx_msg void OnEnChangeEditTag210();
	afx_msg void OnEnChangeEditTag183();
	
	afx_msg void OnEnChangeEditTag155();
	afx_msg void OnEnChangeEditTag216();
};
