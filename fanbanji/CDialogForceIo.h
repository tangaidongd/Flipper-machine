#pragma once
#include "analyzeByNetwork.h"
#include "cusCheckBox.h"

// CDialogForceIo 对话框
#define CHECKBOX_FORCE_NUM 34

class CDialogForceIo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogForceIo)

public:
	CDialogForceIo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogForceIo();

// 对话框数据
	enum { IDD = IDD_DIALOG_IO_FORCE };

public:
	void SetAnalyzeNetwork(CAnalyzeNetwork *pAnalyzeNetwork);
	void UpdateCtrlValue();

	// 单机自动化文字
	void SignleAutoRunDisplayIo(bool bIsAuto);

private:
	void SetCtrlValue2Buf();

	void EnableCtrlStatus(int nChoiceType);


private:
	CAnalyzeNetwork*	m_pAnalyzeNetwork;
	CCusCheckBox		m_zForceIOStatus[CHECKBOX_FORCE_NUM];
	int m_checkIoForceType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnSetIo();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedBtnNetworkStart();
	afx_msg void OnBnClickedBtnNetworkStop();
};
