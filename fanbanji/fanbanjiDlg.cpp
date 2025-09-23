
// fanbanjiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "fanbanjiDlg.h"
#include "afxdialogex.h"
#include "DataByControlV2.h"
#include "log.h"
#include "tinyxml/tinyxml.h"
#include "CDialogVersionChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  ON_TIME_DELLOG	 10010


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfanbanjiDlg �Ի���




CfanbanjiDlg::CfanbanjiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfanbanjiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_mapConfigData.clear();
	m_bSerialOpenStatus = false;	
	m_pDataByCmdDlg = NULL;
	m_pDataByControlV2 = NULL;
	m_pSerialThread = NULL;
}

CfanbanjiDlg::~CfanbanjiDlg()
{
	if (m_pDataByCmdDlg)
	{
		delete m_pDataByCmdDlg;
		m_pDataByCmdDlg = NULL;
	}

	if (m_pDataByControlV2)
	{
		delete m_pDataByControlV2;
		m_pDataByControlV2 = NULL;
	}

	if(m_pSerialThread)
	{
		m_pSerialThread->SetRunStatus(FALSE);
		m_pSerialThread = NULL;
	}
}

void CfanbanjiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboxCom);
	DDX_Control(pDX, IDC_COMBO2, m_comboxBaudrate);
	DDX_Control(pDX, IDC_CHECK_LOG, m_checkboxLog);
	DDX_Control(pDX, IDC_BTN_CMD, m_btnCmd);
	DDX_Control(pDX, IDC_BTN_CMD2, m_btnCmd2);
}


BEGIN_MESSAGE_MAP(CfanbanjiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_REV_CMD, OnRevCmdMsg)
	ON_MESSAGE(WM_SAVE_CONFIG, OnSaveConfig)
	ON_MESSAGE(WM_LOAD_CONFIG, OnLoadConfig)
	ON_MESSAGE(WM_REFRESH_CONTROL, OnRefreshControl)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CfanbanjiDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BTN_CMD, &CfanbanjiDlg::OnBnClickedBtnCmd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_LOG, &CfanbanjiDlg::OnBnClickedCheckLog)
	ON_BN_CLICKED(IDC_BTN_CMD2, &CfanbanjiDlg::OnBnClickedBtnCmd2)
	ON_BN_CLICKED(IDC_BTN_VERSION, &CfanbanjiDlg::OnBnClickedBtnVersion)
END_MESSAGE_MAP()



// CfanbanjiDlg ��Ϣ�������

BOOL CfanbanjiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T("�����"));
	InitControl();
	//m_dataByPollingDlg.EnableWindow(false);
	//m_dataByCmdDlg.EnableWindow(false);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CfanbanjiDlg::InitControl()
{
	// �����Ӵ���
	m_DataByPollingDlg.Create(IDD_DIALOG_POLLING, this);
	CRect rcTab;
	GetClientRect(&rcTab);

	rcTab.top += 65;
	m_DataByPollingDlg.MoveWindow(rcTab);
	m_DataByPollingDlg.ShowWindow(true);
	m_DataByPollingDlg.EnableWindow(false);

	// ����
	m_comboxCom.ResetContent();
	m_comboxCom.AddString(_T("COM5"));
	m_comboxCom.SetCurSel(0);

	m_comboxBaudrate.ResetContent();
	m_comboxBaudrate.AddString(_T("9600"));
	m_comboxBaudrate.SetCurSel(0);

	m_btnCmd.EnableWindow(false);
	m_btnCmd2.EnableWindow(false);
	m_checkboxLog.SetCheck(false);

	m_pDataByCmdDlg = new CDataByCmdDlg();
	m_pDataByCmdDlg->Create(IDD_DIALOG_CMD);
	m_pDataByCmdDlg->SetSerialPort(&m_SerialPort);
	m_pDataByCmdDlg->ShowWindow(SW_HIDE);

	// ��ѯ����
	m_AnalyzeProtocol.InitProtocolVec();

	m_DataByPollingDlg.SetSerialPort(&m_SerialPort);
	m_DataByPollingDlg.SetAnalyzeProtocol(&m_AnalyzeProtocol);

	m_pDataByControlV2 = new CDataByControlV2();
	m_pDataByControlV2->Create(IDD_DIALOG_CTL_V2);
	m_pDataByControlV2->ShowWindow(SW_HIDE);
	m_pDataByControlV2->SetSerialPort(&m_SerialPort);
	m_pDataByControlV2->SetAnalyzeProtocol(&m_AnalyzeProtocol);

	GetDlgItem(IDC_BTN_VERSION)->EnableWindow(true);
}



void CfanbanjiDlg::SerialStatusChange(bool bIsOpen)
{
	m_DataByPollingDlg.EnableWindow(bIsOpen);
	m_btnCmd.EnableWindow(bIsOpen);
	m_btnCmd2.EnableWindow(bIsOpen);

	CString strDis = bIsOpen ?_T("�رմ���"):_T("�򿪴���");
	((CButton*)GetDlgItem(IDC_BUTTON_OPEN))->SetWindowText(strDis);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->EnableWindow(!bIsOpen);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->EnableWindow(!bIsOpen);

	GetDlgItem(IDC_BTN_VERSION)->EnableWindow(!bIsOpen);
}


void CfanbanjiDlg::SetTcpEvent(bool bIsSignal)
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SetTcpEvent(bIsSignal);
	}
}

void CfanbanjiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CfanbanjiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CfanbanjiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CfanbanjiDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);

	CString strCom;
	CString strBaudrate;
	m_comboxCom.GetWindowText(strCom);
	m_comboxBaudrate.GetWindowText(strBaudrate);

	if (!m_bSerialOpenStatus)
	{
		m_bSerialOpenStatus = true;
		m_bSerialOpenStatus = m_SerialPort.Open(CStringA(strCom), _ttoi(strBaudrate), 0, 8, 1, 1);
		if (m_bSerialOpenStatus)
		{
			if(m_SerialPort.IsOpen())
			{
				m_pSerialThread = new CSerialThread();
				//m_pSerialThread = (CSerialThread*)AfxBeginThread(RUNTIME_CLASS(CSerialThread), THREAD_PRIORITY_NORMAL, NULL, CREATE_SUSPENDED);
				m_pSerialThread->CreateThread(CREATE_SUSPENDED);
				m_pSerialThread->SetRunStatus(TRUE);
				m_pSerialThread->SetSerialDev(&m_SerialPort);
				m_pSerialThread->SetParentHand(GetSafeHwnd());
				m_pSerialThread->SetPutSerialDataPoint(&m_PutSerialData);

				m_DataByPollingDlg.SetSerialThread(m_pSerialThread);
				if (m_pDataByControlV2)
				{
					m_pDataByControlV2->SetSerialThread(m_pSerialThread);
				}
				
				// ����Ϊ0���Զ��ͷ�
				//m_pSerialThread->m_bAutoDelete;
				m_pSerialThread->ResumeThread();
			}
		}
		else
		{
			MessageBox(_T("�򿪶˿�ʧ�ܣ�"), _T("�����"), MB_OK);
		}		
	}
	else
	{
		m_bSerialOpenStatus	= false;
		m_SerialPort.Close();

		if(m_pSerialThread)
		{
			m_pSerialThread->SetRunStatus(FALSE);
			m_pSerialThread = NULL;
		}
	}
	SerialStatusChange(m_bSerialOpenStatus);

	// һЩ��ʼ�����ֻ����һ��
	if (m_bSerialOpenStatus)
	{
		SetTcpEvent(false);
		m_DataByPollingDlg.GetVersion();
		m_DataByPollingDlg.RefreshControlValue();
		if (m_pDataByControlV2)
		{
			m_pDataByControlV2->RefreshControlValue();
		}
		SetTcpEvent(true);
	}
	// ���¿������
	
}



void CfanbanjiDlg::OnBnClickedBtnCmd()
{
	// �����ڵ���ѯ������ſ�
	//m_dataByPollingDlg.SetTcpEvent(false);
	if (m_pDataByCmdDlg->IsWindowVisible())
	{
		return;
	}

	m_pDataByCmdDlg->CenterWindow();
	m_pDataByCmdDlg->ShowWindow(SW_NORMAL);
	//m_dataByPollingDlg.SetTcpEvent(true);
}


void CfanbanjiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case ON_TIME_DELLOG:
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CfanbanjiDlg::OnBnClickedCheckLog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nStatus = 0;
	nStatus = m_checkboxLog.GetCheck();
	SetLogFlag(nStatus);
}


void CfanbanjiDlg::OnBnClickedBtnCmd2()
{

	if (m_pDataByControlV2->IsWindowVisible())
	{
		return;
	}

	m_pDataByControlV2->CenterWindow();
	m_pDataByControlV2->ShowWindow(SW_NORMAL);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


LRESULT CfanbanjiDlg::OnRefreshControl(WPARAM wParam, LPARAM lParam)
{
	SetTcpEvent(false);
	// ����ͣ�߳�
	if (m_pDataByControlV2)
	{
		m_pDataByControlV2->RefreshControlValue();
	}

	m_DataByPollingDlg.RefreshControlValue();

	SetTcpEvent(true);

	return 0;
}




LRESULT CfanbanjiDlg::OnRevCmdMsg(WPARAM wParam, LPARAM lParam)
{
	int nRevLen = (int)lParam;
	STComData stComData = m_PutSerialData.PopSerialData();
	STProDataLen stProDataLen;

	// У�������
	if (!m_AnalyzeProtocol.CheckRevCmd(stComData))
	{
		return 0;
	}

	switch(stComData.chTag)
	{
	case EM_SHAKE_HANDS:
	case EM_QUERY_VERSION:
	case EM_QUERY_INPUT:
	case EM_QUERY_OUTPUT:
	case EM_QUERY_IO_STATUS:
	case EM_QUERY_WORK_STATUS:
	case EM_WRITE_ROLL_SPEED:
	case EM_QUERY_ROLL_SPEED:
	case EM_WRITE_FLIP_SPEED:
	case EM_QUERY_FLIP_SPEED:
	case EM_WRITE_PULSES_COUNT:
	case EM_QUERY_PULSES_COUNT:
	case EM_WRITE_ACTION_TIME:
	case EM_QUERY_ACTION_TIME:
	case EM_WRITE_COMPLETE_SIGNAL_DELAY:
	case EM_QUERY_COMPLETE_SIGNAL_DELAY:
	case EM_QUERY_LAST_TIME_CONSUMING:
	case EM_QUERY_ALARM_NUM:
	case EM_QUERY_ALARM_LOG:
		m_DataByPollingDlg.OnRevCmdMsg(stComData);
		break;
	default:
		if (m_pDataByControlV2)
		{
			m_pDataByControlV2->OnRevCmdMsg(stComData);
		}
		break;
	}
				

	return 0;
}


bool CfanbanjiDlg::WriteConfig(std::string strConfigPath)
{
	TiXmlDocument *doc = new TiXmlDocument();				//����xml�ĵ�����
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0","gb2312","");
	doc->LinkEndChild(pDeclaration);

	TiXmlElement *RootLv1 = new TiXmlElement("CONFIG");  	
	doc->LinkEndChild(RootLv1);			

	char zCmdTemp[20] = {0}; 
	char zValue[20] = {0}; 
	for (auto iter = m_mapConfigData.begin(); iter != m_mapConfigData.end(); ++iter)
	{
		TiXmlElement *RootLv2 = new TiXmlElement("CF");		
		RootLv1->LinkEndChild(RootLv2);		
		sprintf_s(zCmdTemp, "%02x", iter->first);


		RootLv2->SetAttribute("type", zCmdTemp);	
		RootLv2->SetAttribute("name", iter->second.strCFName.c_str());	
		int iIndex = 0;
		for (auto iter2 = iter->second.vCmdValue.begin(); iter2 != iter->second.vCmdValue.end(); ++iter2)
		{
			sprintf_s(zValue, "value%d", ++iIndex);
			RootLv2->SetAttribute(zValue, *iter2);	
		}	
	}
	/*TiXmlElement *Name = new TiXmlElement("name");			
	RootLv2->LinkEndChild(Name);	*/						

	doc->SaveFile(strConfigPath.c_str());				   //���浽�ļ�
	return 0;
}

LRESULT CfanbanjiDlg::OnSaveConfig(WPARAM wParam, LPARAM lParam)
{
	// ��ȡÿ���ؼ�����ʷֵ
	std::string strSaveFilePath;
	CFolderPickerDialog fd(NULL, 0, this, 0);
	if (fd.DoModal() == IDOK)
	{
		CString des = fd.GetPathName();
		strSaveFilePath = CStringA(des);
	}

	if (!strSaveFilePath.empty())
	{
		m_mapConfigData.clear();
		if (m_pDataByControlV2)
		{
			m_pDataByControlV2->GetControlValue(m_mapConfigData);
		}
		m_DataByPollingDlg.GetControlValue(m_mapConfigData);

		strSaveFilePath += "\\ConfigXML.xml";
		WriteConfig(strSaveFilePath.c_str());

		MessageBox(L"���ñ���ɹ�", NULL, MB_OK);
	}
	return 0;
}


bool CfanbanjiDlg::AnalyConfig(CString strConfigPath)
{

	std::string strPath = CStringA(strConfigPath);
	TiXmlDocument Doc;
	if ( !Doc.LoadFile(strPath.c_str()))
	{
		DWORD dw = GetLastError();
		return false;
	}

	TiXmlElement* pRootElement = Doc.RootElement();
	if ( NULL == pRootElement )
	{
		return false;
	}
	
	if (0 == strcmp(pRootElement->Value(), "CONFIG") )
	{
		unsigned char zHexTemp[20] = {0};
		for (TiXmlElement* pElement = pRootElement->FirstChildElement(); NULL != pElement; pElement = pElement->NextSiblingElement())
		{
			//
			const char* pElementValue = pElement->Value();
			if (NULL == pElementValue)
			{
				continue;
			}

			if (0 == strcmp(pElementValue, "CF"))
			{
				STCFData stConfig;
				const char* pszAttr = pElement->Attribute("type");
				if ( NULL != pszAttr)
				{
					//MultiChar2Unicode(CP_UTF8, pszAttr, str);
					memset(zHexTemp, 0, 20);
					CUtil::HexToAsc(zHexTemp, (char*)pszAttr, strlen(pszAttr));

					stConfig.chCmdID = zHexTemp[0];
				}

				pszAttr = pElement->Attribute("name");
				if ( NULL != pszAttr)
				{
					stConfig.strCFName = pszAttr;
				}

				pszAttr = pElement->Attribute("value1");
				if ( NULL != pszAttr)
				{
					stConfig.vCmdValue.push_back(atoi(pszAttr));
				}

				pszAttr = pElement->Attribute("value2");
				if ( NULL != pszAttr)
				{
					stConfig.vCmdValue.push_back(atoi(pszAttr));
				}


				pszAttr = pElement->Attribute("value3");
				if ( NULL != pszAttr)
				{
					stConfig.vCmdValue.push_back(atoi(pszAttr));
				}

				pszAttr = pElement->Attribute("value4");
				if ( NULL != pszAttr)
				{
					stConfig.vCmdValue.push_back(atoi(pszAttr));
				}

				m_mapConfigData[stConfig.chCmdID] = stConfig;
			}
		}
	}

	return true;
}
LRESULT CfanbanjiDlg::OnLoadConfig(WPARAM wParam, LPARAM lParam)
{
	CFileDialog dlg(TRUE);
	// �ɻ�ȡ����ļ���ȡһ��
	OPENFILENAME& ofn = dlg.GetOFN();
	ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	//ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	CString strFilename;
	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		CString strPath = dlg.GetFolderPath();
		while (fileNamesPosition != NULL)
		{
			// filename �ǻ�ȡ���ļ���
			strFilename = dlg.GetNextPathName(fileNamesPosition);
			break;
			// CString strFileName = filename.Right(filename.GetLength() - strPath.GetLength()) + L";";
			// strDisplay += strFileName;
			// vSendFiles.push_back(filename);
		}
	}

	if (strFilename.IsEmpty())
	{
		return 0;
	}

	m_mapConfigData.clear();
	AnalyConfig(strFilename);
	if (m_mapConfigData.size() < 1)
	{
		MessageBox(L"��ȡ�����ļ�ʧ��");
		return 0;
	}

	// �������� ����ͣ��ѯ
	SetTcpEvent(false);
	if (m_pDataByControlV2)
	{
		m_pDataByControlV2->SetControlValue(m_mapConfigData);
		m_pDataByControlV2->RefreshControlValue();
	}
	m_DataByPollingDlg.SetControlValue(m_mapConfigData);
	m_DataByPollingDlg.RefreshControlValue();
	SetTcpEvent(true);

	MessageBox(L"�������óɹ�");

	return 0;
}



void CfanbanjiDlg::OnBnClickedBtnVersion()
{
	CVersionChoice VersionChoice;
	VersionChoice.DoModal();
}
