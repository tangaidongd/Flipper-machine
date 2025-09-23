// CDialogNetAlarm.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogNetAlarm.h"
#include "afxdialogex.h"


// CDialogNetAlarm 对话框

CDialogNetAlarm::CDialogNetAlarm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NET_ALARM, pParent)
{
	m_vecAlarmItemMsg.clear();
}

CDialogNetAlarm::~CDialogNetAlarm()
{
}

void CDialogNetAlarm::InitCtrl()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listAlarmDetail.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listAlarmDetail.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listAlarmDetail.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listAlarmDetail.SetExtendedStyle(dwStyle); //设置扩展风格

	CRect rcList;
	m_listAlarmDetail.GetClientRect(&rcList);
	int nListWidth = rcList.Width();
	m_listAlarmDetail.DeleteAllItems();
	m_listAlarmDetail.InsertColumn(0, L"索引", LVCFMT_LEFT, 80);//插入列
	m_listAlarmDetail.InsertColumn(1, L"报警项", LVCFMT_LEFT, 80);
	m_listAlarmDetail.InsertColumn(2, L"报警时间", LVCFMT_LEFT, 140);
	m_listAlarmDetail.InsertColumn(3, L"报警定义", LVCFMT_LEFT, 220);
	m_listAlarmDetail.InsertColumn(4, L"报警说明", LVCFMT_LEFT, nListWidth- 520);

	CString strAlarmTemp;
	for (int i = 0; i < m_vecAlarmItemMsg.size(); ++i)
	{
		ST_AlarmItemData& stAlarmItem = m_vecAlarmItemMsg[i];
		int nRow = m_listAlarmDetail.InsertItem(i, L"1212");

		int nIndex = 0;
		strAlarmTemp.Format(L"%d", i+1);
		m_listAlarmDetail.SetItemText(nRow, nIndex++, strAlarmTemp);
		strAlarmTemp.Format(L"%d", stAlarmItem.nAlarmID);
		m_listAlarmDetail.SetItemText(nRow, nIndex++, strAlarmTemp);
		m_listAlarmDetail.SetItemText(nRow, nIndex++, stAlarmItem.strTime);
		m_listAlarmDetail.SetItemText(nRow, nIndex++, stAlarmItem.strAlarmMsg);
		m_listAlarmDetail.SetItemText(nRow, nIndex++, stAlarmItem.strAlarmDetail);
	}
}

void CDialogNetAlarm::SetAlarmMsg(std::vector<ST_AlarmItemData>& vecAlarmItemMsg)
{
	m_vecAlarmItemMsg = vecAlarmItemMsg;
}

void CDialogNetAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listAlarmDetail);
}


BEGIN_MESSAGE_MAP(CDialogNetAlarm, CDialogEx)
END_MESSAGE_MAP()


// CDialogNetAlarm 消息处理程序


BOOL CDialogNetAlarm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE; 
}
