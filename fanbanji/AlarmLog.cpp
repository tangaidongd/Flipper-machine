// AlarmLog.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "AlarmLog.h"
#include "afxdialogex.h"


// CAlarmLog 对话框

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


// CAlarmLog 消息处理程序


BOOL CAlarmLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}
