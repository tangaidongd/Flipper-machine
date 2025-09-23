#pragma once


// CDialogIoReplace 对话框
#include "analyzeByNetwork.h"

class CDialogIoReplace : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogIoReplace)

public:
	CDialogIoReplace(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogIoReplace();

// 对话框数据
	enum { IDD = IDD_DIALOG_IO_REPLACE };

public:
	void SetAnalyzeNetwork(CAnalyzeNetwork* pAnalyzeNetwork) { m_pAnalyzeNetwork = pAnalyzeNetwork;} ;
	void UpdateCtrlValue();

	void SignleAutoRunDisplayIo(bool bIsAuto);


private:
	int m_nRadioInput;
	int m_nRadioOutput;

	CAnalyzeNetwork* m_pAnalyzeNetwork;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnIoReplace();
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
