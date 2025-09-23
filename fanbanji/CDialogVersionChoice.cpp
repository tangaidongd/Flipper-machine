// CCVersonChoice.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogVersionChoice.h"
#include "afxdialogex.h"


// CCVersonChoice 对话框

CVersionChoice::CVersionChoice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETING, pParent)
	, m_nChoiceType(0)
	, m_strIP(_T(""))
	, m_strPort(_T(""))
	, m_strRefresh(_T(""))
	, m_bReConncet(FALSE)
{
	ReadParamInit();
}

CVersionChoice::~CVersionChoice()
{
}

void CVersionChoice::ReadParamInit()
{
	WCHAR zReadStr[MAX_PATH] = { 0 };
	CString  strIP;
	CString  strPort;
	CString  strType;
	GetPrivateProfileString(L"CONFIG", L"IP", L"192.168.0.100", zReadStr, MAX_PATH, FILE_PATH_PARAM);
	m_strIP = zReadStr;

	memset(zReadStr, 0, MAX_PATH);
	GetPrivateProfileString(L"CONFIG", L"Port", L"8000", zReadStr, MAX_PATH, FILE_PATH_PARAM);
	m_strPort = zReadStr;

	memset(zReadStr, 0, MAX_PATH);
	GetPrivateProfileString(L"CONFIG", L"Refresh", L"200", zReadStr, MAX_PATH, FILE_PATH_PARAM);
	m_strRefresh = zReadStr;
	int nRefresh = _ttoi(m_strRefresh);
	if(nRefresh > 5000)
		m_strRefresh = L"5000";

	memset(zReadStr, 0, MAX_PATH);
	GetPrivateProfileString(L"CONFIG", L"Type", L"1", zReadStr, MAX_PATH, FILE_PATH_PARAM);
	strType = zReadStr;
	m_nChoiceType = _ttoi(strType);

	memset(zReadStr, 0, MAX_PATH);
	GetPrivateProfileString(L"CONFIG", L"ReConnect", L"1", zReadStr, MAX_PATH, FILE_PATH_PARAM);
	strType = zReadStr;
	m_bReConncet = (strType == L"0") ? false : true;
}



void CVersionChoice::EnalbeSomeCtrl()
{
	UpdateData(true);

	bool bEnable = m_nChoiceType == 1 ? true : false;
	GetDlgItem(IDC_EDIT_ip)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_RE_CONNECT)->EnableWindow(bEnable);
}

void CVersionChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nChoiceType);
	DDX_Text(pDX, IDC_EDIT_ip, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_REFRESH, m_strRefresh);
	DDX_Check(pDX, IDC_CHECK_RE_CONNECT, m_bReConncet);
}


BEGIN_MESSAGE_MAP(CVersionChoice, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CVersionChoice::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CVersionChoice::OnBnClickedRadio2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CVersionChoice::OnBnClickedOk)
END_MESSAGE_MAP()


// CCVersonChoice 消息处理程序


void CVersionChoice::OnBnClickedRadio1()
{
	EnalbeSomeCtrl();
}


void CVersionChoice::OnBnClickedRadio2()
{
	EnalbeSomeCtrl();
}


void CVersionChoice::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	ReadParamInit();
	UpdateData(FALSE);

	EnalbeSomeCtrl();
}


void CVersionChoice::OnBnClickedOk()
{
	UpdateData(true);

	if (m_nChoiceType == 1)
	{
		if (m_strIP.IsEmpty() || m_strPort.IsEmpty())
		{
			MessageBox(L"IP与端口不能为空");
			return;
		}

		int nRefresh = _ttoi(m_strRefresh);
		if(nRefresh < 100 || nRefresh > 5000)
		{
			MessageBox(L"周期范围100-5000ms");
			return;
		}
	}

	// 检查目录
	CString strFilePath = FILE_PATH_PARAM;
	int nIndex = strFilePath.ReverseFind('\\');
	strFilePath = strFilePath.Left(nIndex);
	DWORD dwAttrib = GetFileAttributes(strFilePath);
	if(!(INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
		bool flag = CreateDirectory(strFilePath, NULL);


	if (m_strIP.IsEmpty())
		WritePrivateProfileString(L"CONFIG", L"IP", NULL, FILE_PATH_PARAM);
	else
		WritePrivateProfileString(L"CONFIG", L"IP", m_strIP, FILE_PATH_PARAM);

	if (m_strPort.IsEmpty())
		WritePrivateProfileString(L"CONFIG", L"Port", NULL, FILE_PATH_PARAM);
	else
		WritePrivateProfileString(L"CONFIG", L"Port", m_strPort, FILE_PATH_PARAM);

	if (m_strRefresh.IsEmpty())
		WritePrivateProfileString(L"CONFIG", L"Refresh", NULL, FILE_PATH_PARAM);
	else
		WritePrivateProfileString(L"CONFIG", L"Refresh", m_strRefresh, FILE_PATH_PARAM);

	CString strType;
	strType.Format(L"%d", m_nChoiceType);
	WritePrivateProfileString(L"CONFIG", L"Type", strType, FILE_PATH_PARAM);

	strType.Format(L"%d", m_bReConncet);
	WritePrivateProfileString(L"CONFIG", L"ReConnect", strType, FILE_PATH_PARAM);

	CDialogEx::OnOK();
}
