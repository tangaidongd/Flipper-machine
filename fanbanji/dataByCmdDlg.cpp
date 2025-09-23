// dataByCmdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "dataByCmdDlg.h"
#include "afxdialogex.h"
#include <iostream>


// CDataByCmdDlg 对话框

IMPLEMENT_DYNAMIC(CDataByCmdDlg, CDialogEx)

CDataByCmdDlg::CDataByCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataByCmdDlg::IDD, pParent)
{
	m_pSerialPort = NULL;
}

CDataByCmdDlg::~CDataByCmdDlg()
{
	m_pSerialPort = NULL;
}

void CDataByCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editRev);
	DDX_Control(pDX, IDC_EDIT1, m_editSend);
	DDX_Control(pDX, IDC_EDIT3, m_editTag);
}


BEGIN_MESSAGE_MAP(CDataByCmdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CLEAN_SEND, &CDataByCmdDlg::OnBnClickedBtnCleanSend)
	ON_BN_CLICKED(IDC_BTN_CLEAN_REV, &CDataByCmdDlg::OnBnClickedBtnCleanRev)
	ON_BN_CLICKED(IDC_BTN_SEND, &CDataByCmdDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CDataByCmdDlg 消息处理程序

BOOL CDataByCmdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitControlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDataByCmdDlg::SetSerialPort(CSerialPort* pSerialPort)
{
	m_pSerialPort = pSerialPort;
}

void CDataByCmdDlg::InitControlValue()
{
	m_editRev.Clear();
	m_editSend.Clear();

	UpdateData(FALSE);
}

void CDataByCmdDlg::OnBnClickedBtnCleanSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editSend.SetSel(0, -1);
	m_editSend.Clear();

	m_editTag.SetSel(0, -1);
	m_editTag.Clear();
}


void CDataByCmdDlg::OnBnClickedBtnCleanRev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editRev.SetSel(0, -1);
	//m_editRev.Clear();
	m_editRev.ReplaceSel(_T(""));
	UpdateData(FALSE);
}


void CDataByCmdDlg::OnBnClickedBtnSend()
{
	if (m_pSerialPort && !m_pSerialPort->IsOpen())
	{
		MessageBox(L"检查串口打开情况");
		return;
	}

	UpdateData(TRUE);
	CString strTag		= _T("");
	CString strSend		= _T("");
	m_editSend.GetWindowText(strSend);
	m_editTag.GetWindowText(strTag);
	strSend.Replace(_T(" "), _T(""));
	strTag.Replace(_T(" "), _T(""));
	CString strSendCmd = _T("aa") + strTag + strSend + _T("eeee");

	std::string strTemp = CStringA(strSendCmd).GetBuffer(0);
	char szSendBuff[50] = {0};
	char szRevBuff[50]  = {0};
	bool bAnaly = m_AnalyzeProtocol.PackStrBuffer(strTemp.c_str(), strTemp.length(), szSendBuff);
	if (bAnaly && m_pSerialPort->IsOpen())
	{
		int nMaxRev =  m_AnalyzeProtocol.GetProtocolLen(szSendBuff[1], false);
		int nRev = m_pSerialPort->SendAndRev((u8*)szSendBuff, strTemp.length()/2, szRevBuff, nMaxRev);
		if(nRev > 0)
		{
			// 转换结果方便查看
			u8 zRevDataFinal[MAX_DATA_LEN*2] = {0};
			u8* pRevDataFinal = zRevDataFinal;
			Hex2Str((u8*)szRevBuff, &pRevDataFinal, nRev);

			CStringA strRevA = (char*)zRevDataFinal;
			CString strRev = (CString)strRevA;

			int nLen = m_editRev.GetWindowTextLength();
			m_editRev.SetSel(nLen, nLen);
			if (nLen > 0)
			{
				strRev = L"\r\n" + strRev;
			}
			m_editRev.ReplaceSel(strRev);
		}
	}
	else
	{
		MessageBox(L"发送失败，检查格式");
	}
}