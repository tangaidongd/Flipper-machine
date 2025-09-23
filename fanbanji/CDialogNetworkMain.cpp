// CDialogNetworkMain.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogNetworkMain.h"
#include "CDialogNetAlarm.h"
#include "afxdialogex.h"


#define WM_USER_SHOW_SOFTWND 0x2015

#define  DEL_PTR(_ptr)  \
		if(_ptr)\
		{ \
			delete _ptr; \
			_ptr = NULL; \
		}


#define  RE_CONNECT_NETWORK    2200
#define  SYNCHRONIZATION_TIME  2300


// CDialogNetworkMain 对话框
CDialogNetworkMain::CDialogNetworkMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NET_MAIN, pParent)
	, m_bReConnect(FALSE)
{
	m_pDialogReadOnly = NULL;
	m_pDialogConfig = NULL;
	m_pDialogConfigV2 = NULL;
	m_pDialogMsgBox = NULL;
	m_pVersionChoice = NULL;
	m_rcCaptionHight.SetRectEmpty();

}

CDialogNetworkMain::~CDialogNetworkMain()
{
	DEL_PTR(m_pDialogReadOnly);
	DEL_PTR(m_pDialogConfig);
	DEL_PTR(m_pDialogConfigV2);
	DEL_PTR(m_pDialogMsgBox);
	DEL_PTR(m_pVersionChoice);
}

void CDialogNetworkMain::InitControl()
{
	m_pDialogConfigV2 = new CDialogConfigV2();
	m_pDialogConfigV2->Create(IDD_DIALOG_CFG_2);
	m_pDialogConfigV2->SetAnalyzeNetwork(&m_AnalyzeNetwork);
	m_pDialogConfigV2->ShowWindow(SW_HIDE);

	m_pDialogReadOnly = new CDialogReadOnly(&m_AnalyzeNetwork);
	m_pDialogReadOnly->Create(IDD_DIALOG_READ);
	m_pDialogReadOnly->ShowWindow(SW_SHOW);

	m_pDialogConfig = new CDialogConfig(&m_AnalyzeNetwork);
	m_pDialogConfig->Create(IDD_DIALOG_CONFIG);
	m_pDialogConfig->ShowWindow(SW_HIDE);

	m_pDialogMsgBox = new CDialogMsgBox();
	m_pDialogMsgBox->Create(IDD_DIALOG_CUS_MSG);
	m_pDialogMsgBox->ShowWindow(SW_HIDE);

	m_pVersionChoice = new CVersionChoice();
	m_pVersionChoice->Create(IDD_DIALOG_SETING);
	m_pVersionChoice->ShowWindow(SW_HIDE);

	// 设置默认IP
	CString strIp = m_pVersionChoice->GetCfgIp();
	CString strPort = m_pVersionChoice->GetCfgPort();
	strIp = strIp + L":" + strPort;
	((CButton*)GetDlgItem(IDC_STATIC_IP))->SetWindowText(strIp);


	CRect rcBtn;
	GetDlgItem(IDC_BTN_NORMAL)->GetClientRect(rcBtn);
	CRect rcTab;
	GetClientRect(&rcTab);
	rcTab.top = rcBtn.bottom + 65;
	
	m_pDialogReadOnly->MoveWindow(rcTab);
	m_pDialogConfig->MoveWindow(rcTab);
}



void CDialogNetworkMain::DoDataExchange(CDataExchange* pDX)
{
	int nIndex = 0;
	DDX_Control(pDX, IDOK, m_CusButton[nIndex++]);
	DDX_Control(pDX, IDC_BTN_MINIMIZE, m_CusButton[nIndex++]);
	DDX_Control(pDX, IDCANCEL, m_CusButton[nIndex++]);
	DDX_Control(pDX, IDC_BTN_HELP, m_CusButton[nIndex++]);
	DDX_Control(pDX, IDC_BTN_SETTING, m_CusButton[nIndex++]);

	CDialogEx::DoDataExchange(pDX);
}


void CDialogNetworkMain::AddTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_USER_SHOW_SOFTWND;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(nid.szTip, L"fanbanji");
	Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标
}

void CDialogNetworkMain::DelTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_USER_SHOW_SOFTWND;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(nid.szTip, L"fanbanji");
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


LRESULT CDialogNetworkMain::OnShowSoftWnd(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK://双击左键的处理
	{
		DelTray();
		ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
	}
	break;
	default:
		break;
	}
	return 0;
}



void CDialogNetworkMain::OnBtnMinimize()
{
	ShowWindow(SW_MINIMIZE);
}

BEGIN_MESSAGE_MAP(CDialogNetworkMain, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NORMAL, &CDialogNetworkMain::OnBnClickedBtnNormal)
	ON_BN_CLICKED(IDC_BTN_CFG, &CDialogNetworkMain::OnBnClickedBtnCfg)
	ON_MESSAGE(WM_REV_UPDATE, OnRevDataUpdate)
	ON_MESSAGE(WM_CONNECT_STATUS, OnRevUpdateConnect)
	ON_MESSAGE(WM_UPDATE_ROLL_BOARD, OnRevUpdateRollBoardType)

	// ON_MESSAGE(WM_REV_UPDATE_ALARM, OnRevAlarmUpdate)
	ON_BN_CLICKED(IDC_BTN_CFG2, &CDialogNetworkMain::OnBnClickedBtnCfg2)
	ON_BN_CLICKED(IDC_BTN_CFG3, &CDialogNetworkMain::OnBnClickedBtnCfg3)
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_MINIMIZE, &CDialogNetworkMain::OnBtnMinimize)
	ON_MESSAGE(WM_USER_SHOW_SOFTWND, OnShowSoftWnd)

	ON_BN_CLICKED(IDC_BTN_SETTING, &CDialogNetworkMain::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_HELP, &CDialogNetworkMain::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDCANCEL, &CDialogNetworkMain::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDialogNetworkMain::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogNetworkMain 消息处理程序


BOOL CDialogNetworkMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_AnalyzeNetwork.SetParentHand(GetSafeHwnd());
	//m_AnalyzeNetwork.InitConect("192.168.0.100", "8000");

	InitControl();
	// 初始化数据模块
	return TRUE;  
}


void CDialogNetworkMain::OnBnClickedBtnNormal()
{
	m_pDialogReadOnly->ShowWindow(true);
	m_pDialogConfig->ShowWindow(false);
}


void CDialogNetworkMain::OnBnClickedBtnCfg()
{
	m_pDialogReadOnly->ShowWindow(false);
	m_pDialogConfig->ShowWindow(true);
}


LRESULT CDialogNetworkMain::OnRevUpdateConnect(WPARAM wParam, LPARAM lParam)
{
	int nConnectStatus = wParam;
	if (nConnectStatus == 0)
	{
		((CButton*)GetDlgItem(IDC_STATIC_CONNECT_STATUS))->SetWindowText(L"连接中断");

		if (m_pVersionChoice && m_pVersionChoice->GetCfgReConnect())
		{
			KillTimer(RE_CONNECT_NETWORK);
			SetTimer(RE_CONNECT_NETWORK, 4000, NULL);
		}
		else
		{
			CusMsgBox(L"网络连接中断,请重新连接");
		}

		KillTimer(SYNCHRONIZATION_TIME);
	}

	return 0;
}

LRESULT CDialogNetworkMain::OnRevUpdateRollBoardType(WPARAM wParam, LPARAM lParam)
{
	bool bAutoType = wParam ;
	if (m_pDialogReadOnly)
		m_pDialogReadOnly->SignleAutoRunDisplayIo(bAutoType);

	if(m_pDialogConfigV2)
		m_pDialogConfigV2->SignleAutoRunDisplayIo(bAutoType);

	if (m_pDialogConfig)
		m_pDialogConfig->SignleAutoRunDisplayIo(bAutoType);

	return 0;
}

LRESULT CDialogNetworkMain::OnRevDataUpdate(WPARAM wParam, LPARAM lParam)
{

	STRevDataItem* pstRequestRet = (STRevDataItem*)wParam;
	STRevDataItem stRequestRet = *pstRequestRet ;
	delete pstRequestRet;
	pstRequestRet = NULL;

	// 设置返回的提示
	ResponseStatusTip(stRequestRet);

	if(!stRequestRet.bRcvSuccessFlag)
		return -1;

	// 加入是设置属性，自动请求一次服务器数据
	if(stRequestRet.nTagReadOrWrite == 0xAA)
	{
		m_AnalyzeNetwork.SynchronizeNetworkData(stRequestRet.nTagStart, stRequestRet.nTagEnd, 0);
		return 0;
	}
		
	RefreshDialogData(stRequestRet);

	// 更新部分显示，如告警条目，ip，和时间
	return 0;
}


void CDialogNetworkMain::UpdateSomeCtrlValue()
{
	CString strValue;

	//m_AnalyzeNetwork.GetStrValueValueByTag(EM_PRO_TAG_010, strValue);
	//((CButton*)GetDlgItem(IDC_STATIC_IP))->SetWindowText(strValue);

	CString strIP  = L"192.168.";
	m_AnalyzeNetwork.GetStrValueValueByTag(EM_PRO_TAG_185, strValue); 
	strIP += strValue;
	m_AnalyzeNetwork.GetStrValueValueByTag(EM_PRO_TAG_186, strValue); 
	strIP += L".";
	strIP += strValue;
	m_AnalyzeNetwork.GetStrValueValueByTag(EM_PRO_TAG_187, strValue); 
	strIP += L":";
	strIP += strValue;
	((CButton*)GetDlgItem(IDC_STATIC_IP))->SetWindowText(strIP);

	CString strTime;
	unsigned int nTagVerValue1 = 0;
	unsigned int nTagVerValue2 = 0;
	unsigned int nTagVerValue3 = 0;
	unsigned int nTagVerValue4 = 0;
	unsigned int nTagVerValue5 = 0;
	m_AnalyzeNetwork.GetIndexValueByTag(EM_PRO_TAG_000, nTagVerValue1);
	m_AnalyzeNetwork.GetIndexValueByTag(EM_PRO_TAG_001, nTagVerValue2);
	m_AnalyzeNetwork.GetIndexValueByTag(EM_PRO_TAG_002, nTagVerValue3);
	m_AnalyzeNetwork.GetIndexValueByTag(EM_PRO_TAG_003, nTagVerValue4);
	m_AnalyzeNetwork.GetIndexValueByTag(EM_PRO_TAG_004, nTagVerValue5);

	strTime.Format(L"%02d%02d%02d", nTagVerValue1, nTagVerValue2, nTagVerValue3);
	
	CString strVerInfo = L"";
	strVerInfo = nTagVerValue4 == 0 ? "Bate" : "Release";
	strValue = nTagVerValue5 == 0 ? "标准" : "非标";
	strValue = strValue  + strVerInfo;
	strValue = strValue + strTime;
	((CButton*)GetDlgItem(IDC_STATIC_VER_INFO))->SetWindowText(strValue);

}

void CDialogNetworkMain::RefreshDialogData(STRevDataItem& stRevDataItem)
{
	// 初次请求数据
	if (stRevDataItem.nTagStart == EM_PRO_TAG_000 && stRevDataItem.nTagEnd == EM_PRO_TAG_DATA_END - 1)
	{
		UpdateSomeCtrlValue();
		m_pDialogReadOnly->UpdateCtrlValue();
		m_pDialogConfig->UpdateCtrlValue();
		m_pDialogConfigV2->UpdateCtrlValue();
		m_pDialogConfigV2->UpdateCtrlValueByForceIo();
		m_pDialogConfigV2->UpdateCtrlValueByFunCfg();
		m_pDialogConfigV2->UpdateCtrlValueByReplace();
		return;
	}

	// 读数据
	if (stRevDataItem.nTagEnd <= EM_PRO_TAG_062
		&& m_pDialogReadOnly)
	{
		UpdateSomeCtrlValue();
		m_pDialogReadOnly->UpdateCtrlValue();
		return;
	}

	// 配置数据
	if ((stRevDataItem.nTagStart > EM_PRO_TAG_062 && stRevDataItem.nTagEnd <= EM_PRO_TAG_191)
		&& m_pDialogConfig && stRevDataItem.nTagStart != EM_PRO_TAG_106)
	{
		m_pDialogConfig->UpdateCtrlValue();
		return;
	}

	if (stRevDataItem.nTagStart >= EM_PRO_TAG_230 && stRevDataItem.nTagEnd <= EM_PRO_TAG_244)
	{
		m_pDialogConfigV2->UpdateCtrlValue();
		return;
	}

	// 报警数据
	if (stRevDataItem.nTagStart >= 250)
	{
		// 更新报警数据
		//PostMessage(WM_REV_UPDATE_ALARM, 0, 0);
		m_pDialogReadOnly->UpdateAlarmCtrlValue();
		return;
	}

	// 增加一种，读取配置文件的
	if(stRevDataItem.nTagStart == EM_PRO_TAG_100 && stRevDataItem.nTagEnd == EM_PRO_TAG_193)
	{
		m_pDialogConfig->UpdateCtrlValue();
		m_pDialogConfigV2->UpdateCtrlValue();
		return;
	}

	// 增加一种，更新106 107属性
	if(stRevDataItem.nTagStart == EM_PRO_TAG_106 && stRevDataItem.nTagEnd == EM_PRO_TAG_107)
	{
		m_pDialogConfigV2->UpdateCtrlValueByFunCfg();
		return;
	}

	// 增加一种, 
	if(stRevDataItem.nTagStart == EM_PRO_TAG_192 && stRevDataItem.nTagEnd == EM_PRO_TAG_193)
	{
		m_pDialogConfigV2->UpdateCtrlValueByReplace();
		return;
	}

	// 增加一种, 
	if(stRevDataItem.nTagStart == EM_PRO_TAG_195 && stRevDataItem.nTagEnd == EM_PRO_TAG_198)
	{
		m_pDialogConfigV2->UpdateCtrlValueByForceIo();
		return;
	}
}

void CDialogNetworkMain::ResponseStatusTip(STRevDataItem& stRevDataItem)
{
	// 可区分具体的命令,后期可扩展
	if (stRevDataItem.nTagReadOrWrite == 0xaa)
	{
		if(EM_PRO_TAG_199 == stRevDataItem.nTagStart)
			return;

		if (EM_PRO_TAG_230 == stRevDataItem.nTagStart && EM_PRO_TAG_235 == stRevDataItem.nTagEnd)
			return;

		if (EM_PRO_TAG_230 == stRevDataItem.nTagStart && EM_PRO_TAG_237 == stRevDataItem.nTagEnd)
			return;

		if (EM_PRO_TAG_245 == stRevDataItem.nTagStart && EM_PRO_TAG_242 == stRevDataItem.nTagEnd)
			return;

		if (EM_PRO_TAG_186 == stRevDataItem.nTagStart && EM_PRO_TAG_187 == stRevDataItem.nTagEnd)
			return;

		CString strMsg = L"设置数据失败";
		if (stRevDataItem.bRcvSuccessFlag)
			strMsg = "设置数据成功";
		CusMsgBox(strMsg);
	}
}

void CDialogNetworkMain::EnableDialog(bool bEnable)
{

}

void CDialogNetworkMain::CusMsgBox(CString strMsg)
{
	if (m_pDialogMsgBox)
	{
		m_pDialogMsgBox->SetDisplayMsg(strMsg);
		m_pDialogMsgBox->CenterWindow();
		m_pDialogMsgBox->ShowWindow(SW_SHOW);
	}
}

void CDialogNetworkMain::OnBnClickedBtnCfg2()
{
	if(m_pDialogConfigV2)
	{
		//m_pDialogConfigV2->UpdateCtrlValue();
		m_AnalyzeNetwork.SynchronizeNetworkData(EM_PRO_TAG_106, EM_PRO_TAG_107, 0);
		m_AnalyzeNetwork.SynchronizeNetworkData(EM_PRO_TAG_245, EM_PRO_TAG_244, 0);
		
		m_pDialogConfigV2->CenterWindow();
		m_pDialogConfigV2->ShowWindow(SW_NORMAL);
	}
}

void CDialogNetworkMain::OnBnClickedBtnCfg3()
{
	KillTimer(RE_CONNECT_NETWORK);		// 网络重连
	KillTimer(SYNCHRONIZATION_TIME);	// 时间同步
	
	if (!m_pVersionChoice)
		return;

	CString strIp = m_pVersionChoice->GetCfgIp();
	CString strPort = m_pVersionChoice->GetCfgPort();
	CString strRefresh = m_pVersionChoice->GetCfgRefresh();
	int nRefresh = _ttoi(strRefresh);

	bool bConnect = false;
	bConnect = m_AnalyzeNetwork.InitConect(CStringA(strIp).GetBuffer(), CStringA(strPort).GetBuffer(), nRefresh);
	CString strMsg = L"连接翻板机成功";
	if(!bConnect)
		strMsg = L"连接翻板机失败";
	CusMsgBox(strMsg);

	strMsg = bConnect == 1 ? L"连接成功" : L"连接失败";
	((CButton*)GetDlgItem(IDC_STATIC_CONNECT_STATUS))->SetWindowText(strMsg);

	if (bConnect)
	{
		strIp = strIp + L":" + strPort;
		((CButton*)GetDlgItem(IDC_STATIC_IP))->SetWindowText(strIp);
		SetTimer(SYNCHRONIZATION_TIME, 3600*1000*12, NULL);
	}
}


void CDialogNetworkMain::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	int nHight = GetSystemMetrics(SM_CYCAPTION);
	GetClientRect(&m_rcCaptionHight);
	m_rcCaptionHight.bottom = nHight + 1;

	CPaintDC dc(this);
	CBrush brush(RGB(255, 255, 255));
	dc.FillRect(m_rcCaptionHight, &brush);
}


LRESULT CDialogNetworkMain::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc = m_rcCaptionHight;
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}


HBRUSH CDialogNetworkMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor = CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)
		{
			pDC->SetTextColor(RGB(75, 75, 75));     //文字颜色
			pDC->SetBkMode(TRANSPARENT);      //不显示文字背景
			hbr = (HBRUSH)::GetStockObject(NULL_BRUSH); //编辑框背景。注意：和文字背景不是一个意思。
		}
	}
	return hbr;
}


void CDialogNetworkMain::OnBnClickedBtnSetting()
{
	if (m_pVersionChoice)
	{
		m_pVersionChoice->CenterWindow();
		m_pVersionChoice->ShowWindow(SW_SHOW);
	}
}

void CDialogNetworkMain::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogNetworkMain::OnBnClickedCancel()
{
	AddTray();
	ShowWindow(SW_HIDE);//隐藏主窗口

	// CDialogEx::OnCancel();
}


void CDialogNetworkMain::OnBnClickedOk()
{
	if (AfxMessageBox(L"是否退出?", MB_YESNO) == IDNO)
		return;

	CDialogEx::OnOK();
}


void CDialogNetworkMain::OnTimer(UINT_PTR nIDEvent)
{
	if (RE_CONNECT_NETWORK == nIDEvent)
	{
		if (!m_pVersionChoice)
		{
			KillTimer(RE_CONNECT_NETWORK);
			return;
		}

		bool bReConnect = m_pVersionChoice->GetCfgReConnect();
		if (!bReConnect || m_AnalyzeNetwork.GetConnectStatus())
		{
			KillTimer(RE_CONNECT_NETWORK);
			return;
		}

		CVersionChoice VersionChoice;
		CString strIp = m_pVersionChoice->GetCfgIp();
		CString strPort = m_pVersionChoice->GetCfgPort();
		CString strRefresh = m_pVersionChoice->GetCfgRefresh();
		int nRefresh = _ttoi(strRefresh);

		bool bConnect = false;
		bConnect = m_AnalyzeNetwork.InitConect(CStringA(strIp).GetBuffer(), CStringA(strPort).GetBuffer(), nRefresh);
		CString strMsg;
		strMsg = bConnect == 1 ? L"连接成功" : L"连接失败";
		((CButton*)GetDlgItem(IDC_STATIC_CONNECT_STATUS))->SetWindowText(strMsg);

		// 连接成功后，也不再重连
		if (bConnect)
		{
			KillTimer(RE_CONNECT_NETWORK);
			SetTimer(SYNCHRONIZATION_TIME, 3600 * 1000 * 12, NULL);
		}
	}
	if (SYNCHRONIZATION_TIME == nIDEvent)
	{
		m_AnalyzeNetwork.SynchronnizationTime();
	}

	CDialogEx::OnTimer(nIDEvent);
}
