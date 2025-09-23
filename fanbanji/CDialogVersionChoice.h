#pragma once


// CCVersonChoice 对话框
#define FILE_PATH_PARAM  L".\\Param\\fanbanjiCfg.ini"

class CVersionChoice : public CDialogEx
{

public:
	CVersionChoice(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CVersionChoice();


	enum { IDD = IDD_DIALOG_SETING };

	CString GetCfgIp() { return m_strIP; }
	CString GetCfgPort() { return m_strPort; }
	CString GetCfgRefresh() { return m_strRefresh; }
	int GetCfgType() { return m_nChoiceType; }
	bool GetCfgReConnect() { return m_bReConncet;}

private:
	void ReadParamInit();
	void EnalbeSomeCtrl();

private:
	int m_nChoiceType;
	CString m_strIP;
	CString m_strPort;
	CString m_strRefresh;
	BOOL	m_bReConncet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
};
