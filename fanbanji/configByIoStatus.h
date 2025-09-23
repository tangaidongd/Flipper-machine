#pragma once

#include "afxwin.h"
#include "cusCheckBox.h"
#include "serialport.h"
// configByIoStatus 对话框

class CConfigByIoStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigByIoStatus)

public:
	CConfigByIoStatus(CWnd* pParent = nullptr);   // 标准构造函数
	CConfigByIoStatus(unsigned int nIoStatus, CSerialPort* pSerialPort, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CConfigByIoStatus();

	enum { IDD = IDD_DIALOG_IO_STATUS };

private:
	unsigned int  m_nIoStatus;
	CSerialPort*  m_pSerialPort;
	CCusCheckBox m_zCusCheckBox[16];

private:
	bool SendIoStatus(unsigned int nIoStatus);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
