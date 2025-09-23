#pragma once


// CCDialogSetIP 对话框
#include "analyzeByNetwork.h"

class CCDialogSetIP : public CDialogEx
{

public:
	CCDialogSetIP(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCDialogSetIP();

	enum {IDD = IDD_DIALOG_SET_IP};

public:
	void SetAnalyzeNetwork(CAnalyzeNetwork* pAnalyzeNetwork);

private:
	CAnalyzeNetwork* m_pAnalyzeNetwork;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CString m_strPort;
	CIPAddressCtrl m_ipAddressCtrl;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	virtual BOOL OnInitDialog();
};
