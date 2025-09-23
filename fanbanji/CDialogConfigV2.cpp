// DialogConfigV2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogConfigV2.h"
#include "afxdialogex.h"
#include "CDialogConfigV2.h"


#define ONTIME_ID  7000
// CDialogConfigV2 �Ի���

#define  DEL_PTR(_ptr)  \
		if(_ptr)\
		{ \
			delete _ptr; \
			_ptr = NULL; \
		}



CDialogConfigV2::CDialogConfigV2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogConfigV2::IDD, pParent)
{
	m_pAnalyzeNetwork = NULL;
	m_pDialogForceIo = NULL;
	m_pDialogIoReplace = NULL;
	m_pDialogFunCfg = NULL;
	m_pDialogSetIP = NULL;
}

CDialogConfigV2::~CDialogConfigV2()
{
	DEL_PTR(m_pDialogForceIo);
	DEL_PTR(m_pDialogIoReplace);
	DEL_PTR(m_pDialogFunCfg);
	DEL_PTR(m_pDialogSetIP);
}

void CDialogConfigV2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogConfigV2, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_START, &CDialogConfigV2::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDialogConfigV2::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CDialogConfigV2::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_START_SECOND, &CDialogConfigV2::OnBnClickedBtnStartSecond)
	ON_BN_CLICKED(IDC_BTN_START_HALF, &CDialogConfigV2::OnBnClickedBtnStartHalf)
	ON_BN_CLICKED(IDC_BTN_AGE_ROTATE, &CDialogConfigV2::OnBnClickedBtnAgeRotate)
	ON_BN_CLICKED(IDC_BTN_AGE_ACTION, &CDialogConfigV2::OnBnClickedBtnAgeAction)
	ON_BN_CLICKED(IDC_BTN_AGE_STOP, &CDialogConfigV2::OnBnClickedBtnAgeStop)
	ON_BN_CLICKED(IDC_BTN_AGE_CLEAN, &CDialogConfigV2::OnBnClickedBtnAgeClean)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_FORCE_IO, &CDialogConfigV2::OnBnClickedBtnForceIo)
	ON_BN_CLICKED(IDC_BTN_OUT_REPLACE, &CDialogConfigV2::OnBnClickedBtnOutReplace)
	ON_BN_CLICKED(IDC_BTN_CFG_105_106, &CDialogConfigV2::OnBnClickedBtnCfg105106)
	ON_BN_CLICKED(IDC_BTN_SET_IP, &CDialogConfigV2::OnBnClickedBtnSetIp)
	ON_BN_CLICKED(IDC_BTN_2_Time, &CDialogConfigV2::OnBnClickedBtn2Time)
	ON_BN_CLICKED(IDC_BTN_LEFT_BACK, &CDialogConfigV2::OnBnClickedBtnLeftBack)
	ON_BN_CLICKED(IDC_BTN_LEFT_OUT, &CDialogConfigV2::OnBnClickedBtnLeftOut)
	ON_BN_CLICKED(IDC_BTN_RIGHT_BACK, &CDialogConfigV2::OnBnClickedBtnRightBack)
	ON_BN_CLICKED(IDC_BTN_RIGHT_OUT, &CDialogConfigV2::OnBnClickedBtnRightOut)
END_MESSAGE_MAP()


void CDialogConfigV2::SetStartStart(CString strStartValue)
{
	if (!m_pAnalyzeNetwork)
		return;

	unsigned int nRunStatus = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_060, nRunStatus);
	if(nRunStatus != 0)
	{
		MessageBox(L"��ǰ����״̬��Ϊ�ֶ�ѡ��");
		return;
	}

	//	��ת�ᾲֹ�ж�ʱ��1
	CString strValue;

	// ��תֹͣ�Ƕ�
	GetDlgItem(IDC_EDIT_TAG_241)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_241, strValue);

	// ��ת���ڽǶ�
	//GetDlgItem(IDC_EDIT_TAG_243)->GetWindowText(strValue);
	//m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_243, strValue);

	// 0 ֹͣ    1:�������λ���    2:������ת  3:��ת����
	// 0 ֹͣ    1:�������λ���    2:������ת
	if (strStartValue == L"0")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_240, strStartValue);
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_245, strStartValue);
	}
	if (strStartValue == L"1")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_245, L"1");
	}
	if (strStartValue == L"2")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_240, L"1");
	}
	if (strStartValue == L"3")
	{
		GetDlgItem(IDC_EDIT_TAG_243)->GetWindowText(strValue);
		int nTagValue = _ttoi(strValue);
		unsigned int nValue = 0;
		m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_204, nValue);
		nTagValue = nTagValue/2 + nValue;

		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_241, nTagValue);
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_240, L"1");
	}

	// ��ʶtag��λ ʵ��Ϊ240-245
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_245, EM_PRO_TAG_242, 1);
	
	//MessageBox(L"���óɹ�");
}

void CDialogConfigV2::SetAgeActionTest(CString strStartValue)
{
	if (!m_pAnalyzeNetwork)
		return;

	unsigned int nRunStatus = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_060, nRunStatus);
	if (nRunStatus != 0)
	{
		MessageBox(L"��ǰ����״̬��Ϊ�ֶ�ѡ��");
		return;
	}

	CString strValue;
	// �趨�ϻ�����
	GetDlgItem(IDC_EDIT_AGE_NUM)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_232, strValue);

	
	// �ϻ����� 0:ֹͣ 1:��ת���ϻ� 2:ȫ�����ϻ� 3:�ϻ�������0
	if (strStartValue == L"0")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_230, L"0");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_231, L"0");
	}
	else if (strStartValue == L"1")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_230, L"1");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_231, L"0");
	}
	else if (strStartValue == L"2")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_230, L"0");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_231, L"1");
	}
	else if (strStartValue == L"3")
	{
		int nValue = 0x80;
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_230, nValue);
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_231, L"0");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_232, L"0");
	}
	else
	{
		//MessageBox(L"����ʧ��");
		return;
	}

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_230, EM_PRO_TAG_235, 1);
	//MessageBox(L"���óɹ�");
}

void CDialogConfigV2::SetSylinderOutBackStatus(CString strStatus)
{
	if (!m_pAnalyzeNetwork)
	{
		return;
	}
	
	// limitn  ��λ��ӦΪ0ʱ�����Բ������ײ��ԣ����ҽ�230-235��0
	// 1 ����������   2 ���������  3 ���������� 4 ���������
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_230, L"0");
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_231, L"0");
	//m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_232, L"0");
	//m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_233, L"0");
	//m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_234, L"0");
	//m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_235, L"0");

	if (strStatus == L"1")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_236, L"1");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_237, L"0");
	}
	if (strStatus == L"2")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_236, L"2");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_237, L"0");
	}
	if (strStatus == L"3")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_236, L"0");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_237, L"1");
	}
	if (strStatus == L"4")
	{
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_236, L"0");
		m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_237, L"2");
	}

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_230, EM_PRO_TAG_237, 1);
}

void CDialogConfigV2::InitSomeParam()
{
	m_pDialogForceIo = new CDialogForceIo();
	m_pDialogForceIo->Create(IDD_DIALOG_IO_FORCE);
	m_pDialogForceIo->ShowWindow(SW_HIDE);

	m_pDialogIoReplace = new CDialogIoReplace();
	m_pDialogIoReplace->Create(IDD_DIALOG_IO_REPLACE);
	m_pDialogIoReplace->ShowWindow(SW_HIDE);

	m_pDialogFunCfg = new CDialogFunCfg();
	m_pDialogFunCfg->Create(IDD_DIALOG_CFG_106_107);
	m_pDialogFunCfg->ShowWindow(SW_HIDE);

	m_pDialogSetIP = new CCDialogSetIP();
	m_pDialogSetIP->Create(IDD_DIALOG_SET_IP);
	m_pDialogSetIP->ShowWindow(SW_HIDE);

}


void CDialogConfigV2::SetAnalyzeNetwork(CAnalyzeNetwork* pAnalyzeNetwork)
{
	m_pAnalyzeNetwork = pAnalyzeNetwork;
	if(m_pDialogForceIo && m_pDialogIoReplace)
	{
		m_pDialogForceIo->SetAnalyzeNetwork(pAnalyzeNetwork);
		m_pDialogIoReplace->SetAnalyzeNetwork(pAnalyzeNetwork);
		m_pDialogFunCfg->SetAnalyzeNetwork(pAnalyzeNetwork);
		m_pDialogSetIP->SetAnalyzeNetwork(pAnalyzeNetwork);
	}
}

void CDialogConfigV2::UpdateCtrlValue()
{
	if (!m_pAnalyzeNetwork)
		return;

	CString strValue;
	// ��ת״̬
	unsigned int nValue = 0;
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_240, nValue))
	{
		strValue = (nValue==0)?L"ֹͣ":L"����";
		((CButton*)GetDlgItem(IDC_STATIC_TAG_240))->SetWindowText(strValue);
	}
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_245, nValue))
	{
		strValue = (nValue == 0) ? L"ֹͣ" : L"����";
		((CButton*)GetDlgItem(IDC_STATIC_TAG_245))->SetWindowText(strValue);
	}

	// ������ת���ڽǶ����ڱ༭�������и���
	HWND Hwnd = ::GetFocus();
	if(IDC_EDIT_TAG_241 != ::GetDlgCtrlID(Hwnd))
	{
		//	��תֹͣ�Ƕ�
		if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_241, strValue))
			GetDlgItem(IDC_EDIT_TAG_241)->SetWindowText(strValue);
	}

	//	��ת���ڽǶ�
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_243, strValue))
		GetDlgItem(IDC_EDIT_TAG_243)->SetWindowText(strValue);


	// �ϻ����
	// ��ת���ϻ�
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_230, nValue))
	{
		strValue = (nValue == 0) ? L"ֹͣ" : L"����";
		((CButton*)GetDlgItem(IDC_STATIC_ROTATE_STA))->SetWindowText(strValue);
	}

	// ȫ�����ϻ�
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_231, nValue))
	{
		strValue = (nValue == 0) ? L"ֹͣ" : L"����";
		((CButton*)GetDlgItem(IDC_STATIC_ACTION_STA))->SetWindowText(strValue);
	}

	// ��ǰ�ϻ�����
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_234, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_AGE_CUR))->SetWindowText(strValue);


	if(IDC_EDIT_AGE_NUM != ::GetDlgCtrlID(Hwnd))
	{
		// �趨�ϻ�����
		if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_232, strValue))
			GetDlgItem(IDC_EDIT_AGE_NUM)->SetWindowText(strValue);
	}
}


void CDialogConfigV2::UpdateCtrlValueByForceIo()
{
	if(m_pDialogForceIo)
		m_pDialogForceIo->UpdateCtrlValue();
}

void CDialogConfigV2::UpdateCtrlValueByReplace()
{
	if(m_pDialogIoReplace)
		m_pDialogIoReplace->UpdateCtrlValue();
}

void CDialogConfigV2::UpdateCtrlValueByFunCfg()
{
	if(m_pDialogFunCfg)
		m_pDialogFunCfg->UpdateCtrlValue();
}

void CDialogConfigV2::SignleAutoRunDisplayIo(bool bIsAuto)
{
	if(m_pDialogForceIo)
		m_pDialogForceIo->SignleAutoRunDisplayIo(bIsAuto);

	if(m_pDialogIoReplace)
		m_pDialogIoReplace->SignleAutoRunDisplayIo(bIsAuto);
}


// CDialogConfigV2 ��Ϣ�������


BOOL CDialogConfigV2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitSomeParam();

	UpdateCtrlValue();

	KillTimer(ONTIME_ID);
	SetTimer(ONTIME_ID, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogConfigV2::OnBnClickedBtnStart()
{
	SetStartStart(L"2");
}


void CDialogConfigV2::OnBnClickedBtnStop()
{
	SetStartStart(L"0");
}


void CDialogConfigV2::OnBnClickedBtnRefresh()
{
	if(!m_pAnalyzeNetwork)
		return;

	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_230, EM_PRO_TAG_244, 0);
}


void CDialogConfigV2::OnBnClickedBtnStartSecond()
{
	SetStartStart(L"1");
}


void CDialogConfigV2::OnBnClickedBtnStartHalf()
{
	SetStartStart(L"3");
}


void CDialogConfigV2::OnBnClickedBtnAgeRotate()
{
	// �ϻ����� 0:ֹͣ 1:��ת���ϻ� 2:ȫ�����ϻ� 3:�趨�ϻ�������0
	SetAgeActionTest(L"1");
}


void CDialogConfigV2::OnBnClickedBtnAgeAction()
{
	// �ϻ����� 0:ֹͣ 1:��ת���ϻ� 2:ȫ�����ϻ� 3:�趨�ϻ�������0
	SetAgeActionTest(L"2");
}


void CDialogConfigV2::OnBnClickedBtnAgeStop()
{
	// �ϻ����� 0:ֹͣ 1:��ת���ϻ� 2:ȫ�����ϻ� 3:�趨�ϻ�������0
	SetAgeActionTest(L"0");
}


void CDialogConfigV2::OnBnClickedBtnAgeClean()
{
	// �ϻ����� 0:ֹͣ 1:��ת���ϻ� 2:ȫ�����ϻ� 3:�趨�ϻ�������0
	SetAgeActionTest(L"3");
}


void CDialogConfigV2::OnTimer(UINT_PTR nIDEvent)
{
	if(ONTIME_ID == nIDEvent)
	{
		if(!m_pAnalyzeNetwork)
		return;

		m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_230, EM_PRO_TAG_244, 0);

		if(!IsWindowVisible())
			KillTimer(ONTIME_ID);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDialogConfigV2::OnShowWindow(BOOL bShow, UINT nStatus)
{
	
	GetDlgItem(IDC_BTN_REFRESH)->SetFocus();
	KillTimer(ONTIME_ID);
	SetTimer(ONTIME_ID, 1000, NULL);
	CDialogEx::OnShowWindow(bShow, nStatus);

}


void CDialogConfigV2::OnClose()
{
	KillTimer(ONTIME_ID);
	CDialogEx::OnClose();
}


void CDialogConfigV2::OnBnClickedBtnForceIo()
{
	if(m_pDialogForceIo)
	{
		m_pDialogForceIo->CenterWindow();
		m_pDialogForceIo->ShowWindow(SW_NORMAL);
		ShowWindow(SW_HIDE);
	}
}


void CDialogConfigV2::OnBnClickedBtnOutReplace()
{
	if(m_pDialogIoReplace)
	{
		m_pDialogIoReplace->CenterWindow();
		m_pDialogIoReplace->ShowWindow(SW_NORMAL);
		ShowWindow(SW_HIDE);
	}
}


void CDialogConfigV2::OnBnClickedBtnCfg105106()
{
	if(m_pDialogFunCfg)
	{
		m_pDialogFunCfg->CenterWindow();
		m_pDialogFunCfg->ShowWindow(SW_NORMAL);
		ShowWindow(SW_HIDE);
	}
}


void CDialogConfigV2::OnBnClickedBtnSetIp()
{

	if (m_pDialogSetIP)
	{
		m_pDialogSetIP->CenterWindow();
		m_pDialogSetIP->ShowWindow(SW_NORMAL);
		ShowWindow(SW_HIDE);
	}
}


void CDialogConfigV2::OnBnClickedBtn2Time()
{
	
	CString strValue;
	GetDlgItem(IDC_EDIT_TAG_241)->GetWindowText(strValue);
	if (strValue.IsEmpty())
	{
		MessageBox(L"��ת�ǶȲ���Ϊ��");
		return;
	}

	double dAngle = _ttof(strValue);
	dAngle = dAngle * 2;

	if (dAngle - 360 > 1e-4)
	{
		MessageBox(L"��ת�Ƕȳ���360��");
		return;
	}
	strValue.Format(L"%.2f", dAngle);
	GetDlgItem(IDC_EDIT_TAG_241)->SetWindowText(strValue);
	((CEdit*)GetDlgItem(IDC_EDIT_TAG_241))->SetSel(strValue.GetLength(), strValue.GetLength());
	GetDlgItem(IDC_EDIT_TAG_241)->SetFocus();
}


void CDialogConfigV2::OnBnClickedBtnLeftBack()
{
	// 1 ����������   2 ���������  3 ���������� 4 ���������
	SetSylinderOutBackStatus(L"1");
}


void CDialogConfigV2::OnBnClickedBtnLeftOut()
{
	// 1 ����������   2 ���������  3 ���������� 4 ���������
	SetSylinderOutBackStatus(L"2");
}


void CDialogConfigV2::OnBnClickedBtnRightBack()
{
	// 1 ����������   2 ���������  3 ���������� 4 ���������
	SetSylinderOutBackStatus(L"3");
}


void CDialogConfigV2::OnBnClickedBtnRightOut()
{
	// 1 ����������   2 ���������  3 ���������� 4 ���������
	SetSylinderOutBackStatus(L"4");
}
