
// fanbanjiDlg.h : ͷ�ļ�
//
#pragma once

#include "dataByCmdDlg.h"
#include "dataByPollingDlg.h"
#include "DataByControlV2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <map>


// CfanbanjiDlg �Ի���
class CfanbanjiDlg : public CDialogEx
{
// ����
public:
	CfanbanjiDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CfanbanjiDlg();

// �Ի�������
	//enum { IDD = IDD_FANBANJI_DIALOG };
	enum { IDD = IDD_FANBANJI_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	void InitControl();
	void SerialStatusChange(bool bIsOpen);
	void SetTcpEvent(bool bIsSignal);		// ��ͣ�߳�
	bool AnalyConfig(CString strConfigPath);
	bool WriteConfig(std::string strConfigPath);
	

private:
	CAnalyzeProtocol	m_AnalyzeProtocol;			// ����ת����Э��
	CPutSerialData		m_PutSerialData;			// ���ݶ���
	CSerialThread*		m_pSerialThread;			// �豸�����߳�


	bool			m_bSerialOpenStatus;	
	int				m_nOnTimeLog;
	CButton			m_btnCmd;
	CButton			m_checkboxLog;
	CComboBox		m_comboxCom;
	CComboBox		m_comboxBaudrate;
	
	CDataByCmdDlg* 		m_pDataByCmdDlg;
	CDataByControlV2*	m_pDataByControlV2;
	CSerialPort			m_SerialPort;				//	Com�豸ͨѶ
	CDataByPollingDlg	m_DataByPollingDlg;

	std::map<int, STCFData> m_mapConfigData;		// �����ļ�ֵ


		
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
