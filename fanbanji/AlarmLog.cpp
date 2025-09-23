// AlarmLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "AlarmLog.h"
#include "afxdialogex.h"


// CAlarmLog �Ի���

IMPLEMENT_DYNAMIC(CAlarmLog, CDialogEx)

CAlarmLog::CAlarmLog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlarmLog::IDD, pParent)
{
	m_vAlarmLog.clear();
	m_pAnalyzeProtocol = NULL;
}

CAlarmLog::~CAlarmLog()
{
}

void CAlarmLog::SetAlarmLog(std::vector<int> & vAlarmLog)
{
	m_vAlarmLog = vAlarmLog;
}

void CAlarmLog::SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol)
{
	if (pAnalyzeProtocol)
	{
		m_pAnalyzeProtocol = pAnalyzeProtocol;
	}
}

void CAlarmLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlarmLog, CDialogEx)
END_MESSAGE_MAP()


// CAlarmLog ��Ϣ�������


BOOL CAlarmLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit* pEditAlarm =((CEdit*)GetDlgItem(IDC_EDIT_ALARM));
	pEditAlarm->EnableWindow(FALSE);
	if (pEditAlarm && m_pAnalyzeProtocol)
	{
		CString strRev = L"";
		int nIndex = 1;
		for (auto iter = m_vAlarmLog.begin(); iter != m_vAlarmLog.end(); ++iter)
		{
			CString strTemp;
			strTemp.Format(L"%d.    %s  \r\n" , nIndex++, m_pAnalyzeProtocol->GetWorkStatus(*iter, true));
			strRev += strTemp;
		}
		pEditAlarm->SetWindowTextW(strRev);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
