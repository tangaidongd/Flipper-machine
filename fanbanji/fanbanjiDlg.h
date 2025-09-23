
// fanbanjiDlg.h : 头文件
//
#pragma once

#include "dataByCmdDlg.h"
#include "dataByPollingDlg.h"
#include "DataByControlV2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <map>


// CfanbanjiDlg 对话框
class CfanbanjiDlg : public CDialogEx
{
// 构造
public:
	CfanbanjiDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CfanbanjiDlg();

// 对话框数据
	//enum { IDD = IDD_FANBANJI_DIALOG };
	enum { IDD = IDD_FANBANJI_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	void InitControl();
	void SerialStatusChange(bool bIsOpen);
	void SetTcpEvent(bool bIsSignal);		// 暂停线程
	bool AnalyConfig(CString strConfigPath);
	bool WriteConfig(std::string strConfigPath);
	

private:
	CAnalyzeProtocol	m_AnalyzeProtocol;			// 数据转换与协议
	CPutSerialData		m_PutSerialData;			// 数据队列
	CSerialThread*		m_pSerialThread;			// 设备工作线程


	bool			m_bSerialOpenStatus;	
	int				m_nOnTimeLog;
	CButton			m_btnCmd;
	CButton			m_checkboxLog;
	CComboBox		m_comboxCom;
	CComboBox		m_comboxBaudrate;
	
	CDataByCmdDlg* 		m_pDataByCmdDlg;
	CDataByControlV2*	m_pDataByControlV2;
	CSerialPort			m_SerialPort;				//	Com设备通讯
	CDataByPollingDlg	m_DataByPollingDlg;

	std::map<int, STCFData> m_mapConfigData;		// 配置文件值


		
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedBtnCmd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckLog();
	
	
	afx_msg void OnBnClickedBtnCmd2();
	LRESULT OnRevCmdMsg(WPARAM wParam, LPARAM lParam);
	LRESULT OnSaveConfig(WPARAM wParam, LPARAM lParam);
	LRESULT OnLoadConfig(WPARAM wParam, LPARAM lParam);
	LRESULT OnRefreshControl(WPARAM wParam, LPARAM lParam);
	CButton m_btnCmd2;
	afx_msg void OnBnClickedBtnVersion();
};
