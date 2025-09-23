#pragma once


// CDialogIoReplace �Ի���
#include "analyzeByNetwork.h"

class CDialogIoReplace : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogIoReplace)

public:
	CDialogIoReplace(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogIoReplace();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnIoReplace();
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
