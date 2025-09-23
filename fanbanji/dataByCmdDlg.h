#pragma once
#include "afxwin.h"
//#include "publicFun.h"
#include "serialport.h"
#include "serialThread.h"
#include "analyzeCmd.h"

// CDataByCmdDlg 对话框

class CDataByCmdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataByCmdDlg)

public:
	CDataByCmdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataByCmdDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CMD };

	virtual BOOL OnInitDialog();

	void SetSerialPort(CSerialPort* pSerialPort);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	void InitControlValue();

private:
	
	CEdit			m_editRev;
	CEdit			m_editSend;
	CEdit			m_editTag;
	CSerialPort*	m_pSerialPort;	
	CAnalyzeProtocol	m_AnalyzeProtocol;

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnCleanSend();
	afx_msg void OnBnClickedBtnCleanRev();
	afx_msg void OnBnClickedBtnSend();


	
};
