// dataByPollingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "dataByPollingDlg.h"
#include "afxdialogex.h"
#include "AlarmLog.h"


// CDataByPollingDlg �Ի���

#define  MS_UINT   0.65					// ms��һ�㵥λ
#define  MS_UINT_SPECIAL 0.69			// ms��һ�㵥λ
#define  DEF_PRECISION   0.5			// ��ȷ�ȵ���

IMPLEMENT_DYNAMIC(CDataByPollingDlg, CDialogEx)

CDataByPollingDlg::CDataByPollingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataByPollingDlg::IDD, pParent)
{
	m_pSerialThread = NULL;
	m_pSerialPort = NULL;
	m_pAnalyzeProtocol = NULL;
	m_vIoStatus.clear();
	m_vInputStatus.clear();
	m_vOutPutStatus.clear();
	m_vAlarmLog.clear();
}

CDataByPollingDlg::~CDataByPollingDlg()
{
	
}

//void CDataByPollingDlg::StartPolling()
//{
//	if(m_pSerialPort && m_pSerialPort->IsOpen())
//	{
//		m_pSerialThread = new CSerialThread();
//		//m_pSerialThread = (CSerialThread*)AfxBeginThread(RUNTIME_CLASS(CSerialThread), THREAD_PRIORITY_NORMAL, NULL, CREATE_SUSPENDED);
//		m_pSerialThread->CreateThread(CREATE_SUSPENDED);
//		m_pSerialThread->SetRunStatus(TRUE);
//		m_pSerialThread->SetSerialDev(m_pSerialPort);
//		m_pSerialThread->SetParentHand(GetSafeHwnd());
//		m_pSerialThread->SetPutSerialDataPoint(&m_PutSerialData);
//		// ����Ϊ0���Զ��ͷ�
//		//m_pSerialThread->m_bAutoDelete;
//		m_pSerialThread->ResumeThread();
//	}
//}

//void CDataByPollingDlg::StopPolling()
//{
//	if(m_pSerialThread)
//	{
//		m_pSerialThread->SetRunStatus(FALSE);
//		m_pSerialThread = NULL;
//	}
//	
//}

void CDataByPollingDlg::SetSerialPort(CSerialPort* pSerialPort)
{
	if (pSerialPort)
	{
		m_pSerialPort = pSerialPort;		
	}
	
}

void CDataByPollingDlg::SetSerialThread(CSerialThread* pSerialThread)
{
	if (pSerialThread)
	{
		m_pSerialThread = pSerialThread;
	}
}

void CDataByPollingDlg::SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol)
{
	if (pAnalyzeProtocol)
	{
		m_pAnalyzeProtocol = pAnalyzeProtocol;
	}
}


void CDataByPollingDlg::GetControlValue(std::map<int, STCFData>& mapConfigData)
{
	// ��ȡ�ؼ�ֵ
	CString strValue1, strValue2, strValue3;
	STCFData stCFData;
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL2))->GetWindowTextW(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ROLL3))->GetWindowTextW(strValue3);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ROLL_SPEED;
	stCFData.strCFName = "��/�������ٶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	stCFData.vCmdValue.push_back(_ttoi(strValue3));
	mapConfigData[EM_WRITE_ROLL_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_ACTION1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION2))->GetWindowTextW(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION3))->GetWindowTextW(strValue3);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ACTION_TIME;
	stCFData.strCFName = "������ʱ��";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	stCFData.vCmdValue.push_back(_ttoi(strValue3));
	mapConfigData[EM_WRITE_ACTION_TIME] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_FLIP1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_FLIP2))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_FLIP_SPEED;
	stCFData.strCFName = "��ת�ٶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_FLIP_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_PULSES1))->GetWindowTextW(strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_PULSES_COUNT;
	stCFData.strCFName = "���ٷ�ת�Ƕȣ��ذ����壩";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	mapConfigData[EM_WRITE_PULSES_COUNT] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_DELAY1))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY2))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_COMPLETE_SIGNAL_DELAY;
	stCFData.strCFName = "��忪ʼ/��������ź���ʱ";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_COMPLETE_SIGNAL_DELAY] = stCFData;
}

void CDataByPollingDlg::SetControlValue(std::map<int, STCFData>& mapConfigData)
{
	for (auto iter = mapConfigData.begin(); iter != mapConfigData.end(); ++iter)
	{
		switch(iter->first)
		{
		case EM_WRITE_ROLL_SPEED:
			if (iter->second.vCmdValue.size() > 2)
			{
				SendRoll(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), iter->second.vCmdValue.at(2), false);
			}
			break;
		case EM_WRITE_FLIP_SPEED:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendFlip(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_PULSES_COUNT:
			if (iter->second.vCmdValue.size() > 0)
			{
				SentPulses(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_ACTION_TIME:
			if (iter->second.vCmdValue.size() > 2)
			{
				SentAction(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), iter->second.vCmdValue.at(2), false);
			}
			break;
		case EM_WRITE_COMPLETE_SIGNAL_DELAY:
			if (iter->second.vCmdValue.size() > 1)
			{
				SentDelay(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		default:
			break;
		}
	}
}

void CDataByPollingDlg::RefreshControlValue()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLL_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACTION_TIME);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_FLIP_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_COMPLETE_SIGNAL_DELAY);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSES_COUNT);
	}
}

void CDataByPollingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_CONTROL1, m_checkboxControl1);
	DDX_Control(pDX, IDC_CHECK_STATUS1, m_checkboxStatus);
	//DDX_Control(pDX, IDC_CHECK33, m_cusCheckBox33);
	//DDX_Control(pDX, IDC_CHECK32, m_cusCheckBox32);

	int nCheckIndex = 0;
	for (int i = 0; i < CHECKBOX_NUM; ++i)
	{
		DDX_Control(pDX, IDC_CHECK2 + i, m_zCusCheckBox[nCheckIndex++]);
	}
}

BEGIN_MESSAGE_MAP(CDataByPollingDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON13, &CDataByPollingDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BTN_ROLL1, &CDataByPollingDlg::OnBnClickedBtnRoll1)
	ON_BN_CLICKED(IDC_BTN_FLIP1, &CDataByPollingDlg::OnBnClickedBtnFlip1)
	ON_BN_CLICKED(IDC_BTN_PULSES1, &CDataByPollingDlg::OnBnClickedBtnPulses1)
	ON_BN_CLICKED(IDC_BTN_ACTION1, &CDataByPollingDlg::OnBnClickedBtnAction1)
	ON_BN_CLICKED(IDC_BTN_DELAY1, &CDataByPollingDlg::OnBnClickedBtnDelay1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_CONTROL1, &CDataByPollingDlg::OnBnClickedCheckControl1)
	ON_BN_CLICKED(IDC_BTN_ROLL_REFRESH, &CDataByPollingDlg::OnBnClickedBtnRollRefresh)
	ON_BN_CLICKED(IDC_BTN_ACTION_REFRESH, &CDataByPollingDlg::OnBnClickedBtnActionRefresh)
	ON_BN_CLICKED(IDC_BTN_FLIB_REFRESH, &CDataByPollingDlg::OnBnClickedBtnFlibRefresh)
	ON_BN_CLICKED(IDC_BTN_DELAY_REFRESH, &CDataByPollingDlg::OnBnClickedBtnDelayRefresh)
	ON_BN_CLICKED(IDC_BTN_PULESE_REFRESH, &CDataByPollingDlg::OnBnClickedBtnPuleseRefresh)
	ON_BN_CLICKED(IDC_CHECK_STATUS1, &CDataByPollingDlg::OnBnClickedCheckStatus1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataByPollingDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDataByPollingDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CDataByPollingDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CDataByPollingDlg::OnBnClickedButtonRefresh)
	// ����һ���޸���ɫ
	ON_BN_CLICKED(IDC_BTN_IO_STATUS, &CDataByPollingDlg::OnBnClickedBtnIoStatus)
	ON_BN_CLICKED(IDC_BTN_CLEAN, &CDataByPollingDlg::OnBnClickedBtnClean)
END_MESSAGE_MAP()


// CDataByPollingDlg ��Ϣ�������


void CDataByPollingDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	int a = 10;
	// TODO: �ڴ˴������Ϣ����������
}

void  CDataByPollingDlg::OnRevCmdMsg(STComData& stComData)
{
	// У�������
	if (!m_pAnalyzeProtocol->CheckRevCmd(stComData))
	{
		return;
	}

	switch(stComData.chTag)
	{
	case EM_SHAKE_HANDS:
		ShkeHands(stComData);
		break;
	case EM_QUERY_VERSION:
		QueryVersion(stComData);
		break;
	case EM_QUERY_INPUT:
		QueryInput(stComData);
		break;
	case EM_QUERY_OUTPUT:
		QueryOutput(stComData);
		break;
	case EM_QUERY_IO_STATUS:
		QueryIoStatus(stComData);
		break;
	case EM_QUERY_WORK_STATUS:
		QueryWorkStatus(stComData);
		break;
	case EM_QUERY_ROLL_SPEED:
		QueryRollSpeed(stComData);
		break;
	case EM_QUERY_FLIP_SPEED:
		QueryFlipSpeed(stComData);
		break;
	case EM_QUERY_PULSES_COUNT:
		QueryPulsesCount(stComData);
		break;
	case EM_QUERY_ACTION_TIME:
		QueryActionTime(stComData);
		break;
	case EM_QUERY_COMPLETE_SIGNAL_DELAY:
		QueryCompleteSignalDelay(stComData);
		break;
	case EM_QUERY_LAST_TIME_CONSUMING:
		QueryLastTimeConsuming(stComData);
		break;
	case EM_QUERY_ALARM_NUM:
		QueryAlarmNum(stComData);
		break;
	case EM_QUERY_ALARM_LOG:
		//QueryAlarmLog(stComData);
		break;
	default:
		break;
	}

	// ת���������鿴
	/*u8 zRevDataFinal[MAX_DATA_LEN*2] = {0};
	u8* pRevDataFinal = zRevDataFinal;
	Hex2Str((u8*)stComData.zData, &pRevDataFinal, stComData.nDataLen);
	CStringA strRevA = (char*)zRevDataFinal;
	strRevA = "\r\n" + strRevA;
	OutputDebugStringA(strRevA);*/
}	




void CDataByPollingDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDataByPollingDlg::InitControlPoint()
{
	// io����״̬
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK2 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vInputStatus.push_back(pIoStatus);
	}

	// io���״̬
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK18 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vOutPutStatus.push_back(pIoStatus);
	}

	// �ŷ�IO״̬
	for (int i = 0; i < 16; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK34 + i);
		pIoStatus->EnableWindow(FALSE);
		m_vIoStatus.push_back(pIoStatus);
	}
}

void CDataByPollingDlg::ShkeHands(STComData &stComData)
{
	static int nHanks = 1;
	nHanks = nHanks++%3;

	CString strHand;
	strHand.Format(_T("%d"), nHanks);
	((CStatic*)GetDlgItem(IDC_STATIC_HAND))->SetWindowText(strHand); 
}

void CDataByPollingDlg::QueryVersion(STComData &stComData)
{
	// ��ѯ�汾
	u8* pRealData = stComData.zData + 2;
	CString strVersion;
	int nVersion =  (pRealData[0]& 0x00ff);
	int nFuncVersion = (pRealData[1]&0x00ff);
	strVersion.Format(_T("%02x  %02x"), nVersion, nFuncVersion);

	((CStatic*)GetDlgItem(IDC_STATIC_VERSION))->SetWindowText(strVersion);
}

void CDataByPollingDlg::QueryInput(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vInputStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vInputStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryOutput(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vOutPutStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vOutPutStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryIoStatus(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];

	for (int i = 0; i < 8; ++i)
	{
		u32 nValue = (chInput1>>(7-i)) & 0x01;
		m_vIoStatus.at(i)->SetChecked(nValue);
	}

	for (int i = 8; i < 16; ++i)
	{
		u32 nValue = (chInput2>>(15-i)) & 0x01;
		m_vIoStatus.at(i)->SetChecked(nValue);
	}
}

void CDataByPollingDlg::QueryWorkStatus(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];
	u8 chInput3 = pRealData[2];

	u32 nInput1 = chInput1&0xff;
	u32 nInput2 = chInput2&0xff;
	u32 nInput3 = chInput3&0xff;

	CString strCurStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput1);
	CString strProStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput2);
	CString strErrorStatus = m_pAnalyzeProtocol->GetWorkStatus(nInput3, true);

	((CStatic*)GetDlgItem(IDC_STATIC_WORK1))->SetWindowText(strCurStatus);
	((CStatic*)GetDlgItem(IDC_STATIC_WORK2))->SetWindowText(strProStatus);
	((CStatic*)GetDlgItem(IDC_STATIC_WORK3))->SetWindowText(strErrorStatus);
}

void CDataByPollingDlg::QueryRollSpeed(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nRollSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nRollSpeed2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);
	u32 nRollSpeed3 = (pRealData[4]<<8 & 0xffff) | (pRealData[5]&0xffff);

	// �ٶȼ��㹫ʽ��3150/V ��VΪ�����ٶȵ�λ1m/s��Ĭ�����9m/s������16m/s���ٶ�ȡֵ��Χ3m/s-35m/s��
	// ��Ӧд��ֵ1050-90��ֵС��90��90д�롣�����ֽڲ�ȡ��˸�ʽ��
	if (nRollSpeed1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 3150/nRollSpeed1);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL1))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL1))->SetWindowText(strValue1);
	}
	if (nRollSpeed2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 3150/nRollSpeed2);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL2))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL2))->SetWindowText(strValue2);
	}
	if (nRollSpeed3 != 0)
	{
		CString strValue3;
		strValue3.Format(_T("%d"), 3150/nRollSpeed3);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLL3))->SetWindowText(strValue3);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLL3))->SetWindowText(strValue3);
	}
}

void CDataByPollingDlg::QueryFlipSpeed(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nFlip1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nFlip2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	// �ٶȼ��㹫ʽ��3150/V ��VΪ�����ٶȵ�λ1m/s��Ĭ�����9m/s������16m/s���ٶ�ȡֵ��Χ3m/s-35m/s��
	// ��Ӧд��ֵ1050-90��ֵС��90��90д�롣�����ֽڲ�ȡ��˸�ʽ��
	if (nFlip1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 33720/nFlip1);
		((CStatic*)GetDlgItem(IDC_STATIC_FLIP1))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_FLIP1))->SetWindowText(strValue1);
	}
	if (nFlip2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 33720/nFlip2);
		((CStatic*)GetDlgItem(IDC_STATIC_FLIP2))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_FLIP2))->SetWindowText(strValue2);
	}
}

void CDataByPollingDlg::QueryPulsesCount(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nRollSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);

	// �ذ�0.65Ϊ��λ������0.69Ϊ��λ
	nRollSpeed1 = nRollSpeed1*MS_UINT_SPECIAL + DEF_PRECISION;

	// �ذ��������ڰ����봫�����󣬼����ߵľ��롣Ĭ��100��λ������Ҫ��0-250����������Ŀ�������������1��Ϊ��λ��ȡֵ90-180
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nRollSpeed1);
	((CStatic*)GetDlgItem(IDC_STATIC_PULSES1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_PULSES1))->SetWindowText(strValue1);
}

void CDataByPollingDlg::QueryActionTime(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nAction1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nAction2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);
	u32 nAction3 = (pRealData[4]<<8 & 0xffff) | (pRealData[5]&0xffff);

	// ��λ����
	nAction1 = nAction1*MS_UINT + DEF_PRECISION;
	nAction2 = nAction2*MS_UINT + DEF_PRECISION;
	nAction3 = nAction3*MS_UINT + DEF_PRECISION;

	CString strValue1, strValue2, strValue3;
	strValue1.Format(_T("%d"), nAction1);
	strValue2.Format(_T("%d"), nAction2);
	strValue3.Format(_T("%d"), nAction3);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION2))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ACTION3))->SetWindowText(strValue3);

	((CStatic*)GetDlgItem(IDC_EDIT_ACTION1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_ACTION2))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_ACTION3))->SetWindowText(strValue3);
}

void CDataByPollingDlg::QueryCompleteSignalDelay(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nDelay1 = (pRealData[0]<<8 &0xffff) | (pRealData[1]&0xffff);
	u32 nDelay2 = (pRealData[2]<<8 &0xffff) | (pRealData[3]&0xffff);

	nDelay1 = nDelay1*MS_UINT + DEF_PRECISION;
	nDelay2 = nDelay2*MS_UINT + DEF_PRECISION;
	//������1.31msΪ��λ��ռ���ֽڣ�ȡֵ0-4095��
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nDelay1);
	strValue2.Format(_T("%d"), nDelay2);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_DELAY2))->SetWindowText(strValue2);

	((CStatic*)GetDlgItem(IDC_EDIT_DELAY1))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_DELAY2))->SetWindowText(strValue2);
}


void CDataByPollingDlg::QueryLastTimeConsuming(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nTimeCount = (pRealData[0]<<8 &0xffff) | (pRealData[1]&0xffff);
	u32 nTimeWait = (pRealData[2]<<8 &0xffff) | (pRealData[3]&0xffff);
	u32 nTimeOut = (pRealData[4]<<8 &0xffff) | (pRealData[5]&0xffff);
	u32 nTimeAction = nTimeCount - nTimeWait - nTimeOut;

	CString strValue1, strValue2, strValue3, strValue4;
	strValue1.Format(_T("%d"), nTimeCount);
	strValue2.Format(_T("%d"), nTimeWait);
	strValue3.Format(_T("%d"), nTimeAction);
	strValue4.Format(_T("%d"), nTimeOut);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_COUNT))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_WAIT))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_ACTION))->SetWindowText(strValue3);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME_OUT))->SetWindowText(strValue4);

}

void CDataByPollingDlg::QueryAlarmNum(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u32 nAlarmNum = int(pRealData[0]);

	CString strValue1;
	strValue1.Format(_T("%d"), nAlarmNum);
	((CStatic*)GetDlgItem(IDC_STATIC_ALARM_NUM))->SetWindowText(strValue1);
}

void CDataByPollingDlg::QueryAlarmLog(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;

	m_vAlarmLog.clear();
	// �澯��Ŀд���ǻ�ȡ100��
	for (auto i = 0; i < 100; ++i)
	{
		int nAlarmIndex = int(pRealData[i]);
		m_vAlarmLog.push_back(nAlarmIndex);
	}
}

BOOL CDataByPollingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitControlPoint();

	////QueryPulsesCount(stComData);
	//ShkeHands(stComData);
	m_checkboxStatus.SetCheck(1);
	m_checkboxControl1.SetCheck(0);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDataByPollingDlg::SendRoll(int nParam1, int nParam2, int nParam3, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam2)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLL_SPEED, nParam3))
	{
		BoxCustom(L"EM_WRITE_ROLL_SPEED ��������Χ", bDisBox);
		return;
	}

	// ���ݰ������3���ٶȣ���ռ2�ֽڣ�1.�����٣�����ʼ���嵽������2���а��Ӧ��ʱ���Լ�����ʼ���嵽���������Ӧ��ʱ��
	// 2.������٣���������2����Ӧ��������ȫ����ʱ��3.�������٣����������������ʱ
	//	�ٶȼ���ʽ��3150/V(m/s����Ĭ��������30m/s���������10m/s����������18m/s �������÷�Χ��1-50m/s ��
	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;
	u32 nRoll3 = nParam3;

	// �ٶȼ��㹫ʽ��3150/V ��VΪ�����ٶȵ�λ1m/s��Ĭ�����9m/s������16m/s���ٶ�ȡֵ��Χ3m/s-35m/s����Ӧд��ֵ1050-90��ֵС��90��90д�롣�����ֽڲ�ȡ��˸�ʽ��
	if (nRoll1 == 0 || nRoll2 == 0 || nRoll3 == 0)
	{
		BoxCustom(L"������ֵ����Ϊ0", bDisBox);
		return;
	}

	nRoll1 = 3150/nRoll1;
	nRoll2 = 3150/nRoll2;
	nRoll3 = 3150/nRoll3;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2>>8&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;
	zData[nIndex++] = nRoll3>>8&0x00ff;
	zData[nIndex++] = nRoll3&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ROLL_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ROLL_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_ROLL1, nParam1);
			SetStaticValue(IDC_STATIC_ROLL2, nParam2);
			SetStaticValue(IDC_STATIC_ROLL3, nParam3);
		}
		else
		{
			MessageBox(L"��������ʧ��");
		}
	}


}

void CDataByPollingDlg::RollEvent()
{
	CString strValue1, strValue2, strValue3;
	GetEditValue(IDC_EDIT_ROLL1, strValue1);
	GetEditValue(IDC_EDIT_ROLL2, strValue2);
	GetEditValue(IDC_EDIT_ROLL3, strValue3);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	int nEdit3 = _ttoi(strValue3);

	SendRoll(nEdit1, nEdit2, nEdit3);
}

void CDataByPollingDlg::OnBnClickedBtnRoll1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RollEvent();
}

void CDataByPollingDlg::SendFlip(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FLIP_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FLIP_SPEED, nParam2))
	{
		BoxCustom(L"EM_WRITE_FLIP_SPEED ��������Χ", bDisBox);
		return;
	}

	// �ݰ������2���ٶȣ���ռ2�ֽڣ�1.��ת���٣��ӿ�ʼ��ת�����ٷ�ת��ɣ�2.��ת���٣�
	// �����ٷ�ת����ת��λ�����߷�����ת�쳣�����ٷ�ת����60�������ת��λ��Ӧ����
	// 	�ٶȼ���ʽ��33720/V����/s)��Ĭ�Ϸ�ת����123��/s����ת����25��/s   �������÷�Χ��1-180�㣩
	// �ⲿ�Ѿ��жϷ�Χ���Ͳ��ж�0ֵ
	int nFlip1 = 33720/nParam1;
	int nFlip2 = 33720/nParam2;

	int nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nFlip1>>8&0xff;
	zData[nIndex++] = nFlip1&0xff;
	zData[nIndex++] = nFlip2>>8&0xff;
	zData[nIndex++] = nFlip2&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_FLIP_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_FLIP_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_FLIP1, nParam1);
			SetStaticValue(IDC_STATIC_FLIP2, nParam2);
		}
		else
		{
			MessageBox(L"EM_WRITE_FLIP_SPEED ��������ʧ��");
		}
	}
}

void CDataByPollingDlg::FlipEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_FLIP1, strValue1);
	GetEditValue(IDC_EDIT_FLIP2, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SendFlip(nEdit1, nEdit2);
}


void CDataByPollingDlg::OnBnClickedBtnFlip1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	FlipEvent();
}


void CDataByPollingDlg::SentPulses(int nParam1, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PULSES_COUNT, nParam1))
	{
		BoxCustom(L"EM_WRITE_PULSES_COUNT ��������Χ", bDisBox);
		return;
	}

	// ռ���ֽڣ����ٷ�ת��ɺ�ƽ�����ٳɷ�ת���١�
	// 	��0.69��Ϊ��λ(Ĭ��155��  �������÷�Χ��120-180�㣩
	int nPulses1 = nParam1/MS_UINT_SPECIAL + DEF_PRECISION;

	int nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nPulses1>>8&0xff;
	zData[nIndex++] = nPulses1&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_PULSES_COUNT, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_PULSES_COUNT, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_PULSES1, nParam1);
			//SetStaticValue(IDC_STATIC_PULSES2, nParam2);
		}
		else
		{
			MessageBox(L"EM_WRITE_PULSES_COUNT ��������ʧ��");
		}
	}
}

void CDataByPollingDlg::PulsesEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_PULSES1, strValue1);
	int nEdit1 = _ttoi(strValue1);

	SentPulses(nEdit1);
}


void CDataByPollingDlg::OnBnClickedBtnPulses1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PulsesEvent();
}

void CDataByPollingDlg::SentAction(int nParam1, int nParam2, int nParam3, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam1)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam2)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACTION_TIME, nParam3))
	{
		BoxCustom(L"EM_WRITE_ACTION_TIME ��������Χ", bDisBox);
		return;
	}


	// ���ݰ������3���ٶȣ���ռ2�ֽڣ�1.�ж��ذ����ʱ�䣻2.�ж��ذ�ʧ��ʱ�䣻3.�ж�������ѹ�������ʱ��
	//	��0.65msΪ��λ��Ĭ��1��150ms��2��500ms 3��400ms  �������÷�Χ��1-2000ms )
	// ��λ����
	u32 nAction1 = nParam1/MS_UINT + DEF_PRECISION;
	u32 nAction2 = nParam2/MS_UINT + DEF_PRECISION;
	u32 nAction3 = nParam3/MS_UINT + DEF_PRECISION;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nAction1>>8&0xff;
	zData[nIndex++] = nAction1&0xff;
	zData[nIndex++] = nAction2>>8&0xff;
	zData[nIndex++] = nAction2&0xff;
	zData[nIndex++] = nAction3>>8&0xff;
	zData[nIndex++] = nAction3&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ACTION_TIME, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ACTION_TIME, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_ACTION1, nParam1);
			SetStaticValue(IDC_STATIC_ACTION2, nParam2);
			SetStaticValue(IDC_STATIC_ACTION3, nParam3);
		}
		else
		{
			MessageBox(L"��������ʧ��");
		}
	}
}

void CDataByPollingDlg::ActionEvent()
{
	CString strValue1, strValue2, strValue3;
	GetEditValue(IDC_EDIT_ACTION1, strValue1);
	GetEditValue(IDC_EDIT_ACTION2, strValue2);
	GetEditValue(IDC_EDIT_ACTION3, strValue3);
	if (strValue1.IsEmpty() || strValue2.IsEmpty(), strValue3.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��"));
		return ;
	}

	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	int nEdit3 = _ttoi(strValue3);
	
	SentAction(nEdit1, nEdit2, nEdit3);
}

void CDataByPollingDlg::OnBnClickedBtnAction1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ActionEvent();
}

void CDataByPollingDlg::SentDelay(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_COMPLETE_SIGNAL_DELAY, nParam1)
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_COMPLETE_SIGNAL_DELAY, nParam2))
	{
		BoxCustom(L"EM_WRITE_COMPLETE_SIGNAL_DELAY ��������Χ", bDisBox);
		return;
	}

	// ���ݰ������2���ٶȣ���ռ2�ֽڣ�1.��崫�����ź��ӳٹ��ˣ�2.���������ź��ӳٹ���
	// ��0.65msΪ��λ��Ĭ��1��200ms��2��400ms  �������÷�Χ��1-2000ms)

	// ��λ����
	u32 nDelay1 = nParam1/MS_UINT + DEF_PRECISION;
	u32 nDelay2 = nParam2/MS_UINT + DEF_PRECISION;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nDelay1>>8&0xff;
	zData[nIndex++] = nDelay1&0xff;
	zData[nIndex++] = nDelay2>>8&0xff;
	zData[nIndex++] = nDelay2&0xff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_COMPLETE_SIGNAL_DELAY, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_COMPLETE_SIGNAL_DELAY, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_DELAY1, nParam1);
			SetStaticValue(IDC_STATIC_DELAY2, nParam2);
		}
		else
		{
			MessageBox(L"��������ʧ��");
		}
	}
}

void CDataByPollingDlg::DelayEvent()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_DELAY1, strValue1);
	GetEditValue(IDC_EDIT_DELAY2, strValue2);
	if (strValue1.IsEmpty() || strValue2.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��"));
		return ;
	}
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SentDelay(nEdit1, nEdit2);
}

void CDataByPollingDlg::OnBnClickedBtnDelay1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DelayEvent();
}

void CDataByPollingDlg::SetStaticValue(unsigned int nControlID, unsigned int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	((CButton*)GetDlgItem(nControlID))->SetWindowText(strValue);
}

void CDataByPollingDlg::GetEditValue(unsigned int nControlID, CString& strValue)
{
	((CEdit*)GetDlgItem(nControlID))->GetWindowText(strValue);
}



void CDataByPollingDlg::BoxCustom(CString strMsg, bool disBox /*= true*/)
{
	if (disBox)
	{
		MessageBox(strMsg, L"", MB_OK);
	}
}

HBRUSH CDataByPollingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	//pDC->SetTextColor(RGB(255, 0, 0));
	//pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() >= IDC_CHECK2 && pWnd->GetDlgCtrlID() <= IDC_CHECK49)
		{
			if (((CButton*)pWnd)->GetCheck() == 1)
			{
				hbr = CreateSolidBrush(RGB(20, 150, 150));
			}
			
			return hbr;
		}
	}
	return hbr;
}


void CDataByPollingDlg::OnBnClickedCheckControl1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nStatus = 0;
	nStatus = m_checkboxControl1.GetCheck();

	// ���ÿ�����Э�鿪��
	if (m_pSerialThread)
	{
		m_pSerialThread->SetRunControlStatus(nStatus);
	}
}

void CDataByPollingDlg::OnBnClickedCheckStatus1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nStatus = 0;
	nStatus = m_checkboxStatus.GetCheck();

	// ���ÿ�����Э�鿪��
	if (m_pSerialThread)
	{
		m_pSerialThread->SetRunReadStatus(nStatus);
	}
}



void CDataByPollingDlg::OnBnClickedBtnRollRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLL_SPEED);
	}
}


void CDataByPollingDlg::OnBnClickedBtnActionRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACTION_TIME);
	}
}


void CDataByPollingDlg::OnBnClickedBtnFlibRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_FLIP_SPEED);
	}
}


void CDataByPollingDlg::OnBnClickedBtnDelayRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_COMPLETE_SIGNAL_DELAY);
	}
}


void CDataByPollingDlg::OnBnClickedBtnPuleseRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSES_COUNT);
	}
}


void CDataByPollingDlg::OnBnClickedButton4()
{
	//m_vAlarmLog.clear();
	//// �澯��Ŀд���ǻ�ȡ100��
	//char zTemp[50] = {0};
	//int nIndex1 = 0;
	//zTemp[nIndex1++] = 0xaa;
	//zTemp[nIndex1++] = 0x23;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x01;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x00;
	//zTemp[nIndex1++] = 0x15;
	//zTemp[nIndex1++] = 0xee;

	//char* pTemp = zTemp+2;
	//int iNum1 = 10;
	//for (auto i = 0; i < iNum1; ++i)
	//{
	//	int nAlarmIndex = int(pTemp[i]);
	//	if (!nAlarmIndex)
	//	{
	//		continue;
	//	}
	//	m_vAlarmLog.push_back(nAlarmIndex);
	//}

	//CAlarmLog AlarmLog1;
	//AlarmLog1.SetAnalyzeProtocol(m_pAnalyzeProtocol);
	//AlarmLog1.SetAlarmLog(m_vAlarmLog);
	//AlarmLog1.DoModal();

	//return;


	// ��ȡ��ǰ�澯�������ٻ�ȡ���и澯
	CString strAlarmNum;
	((CButton*)GetDlgItem(IDC_STATIC_ALARM_NUM))->GetWindowTextW(strAlarmNum);
	int iNum = _ttoi(strAlarmNum);

	//iNum = 100;
	if (iNum < 1)
	{
		MessageBox(L"�޸澯");
		return;
	}
	if (iNum > 100)
	{
		MessageBox(L"�쳣,�澯��Ŀ����100");
		return;
	}
	
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = iNum&0xff;


	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_QUERY_ALARM_LOG, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		//int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_QUERY_ALARM_LOG, false);
		int nMaxRev = iNum + 4;
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{

			char* pRealData = zRevData + 2;

			m_vAlarmLog.clear();
			// �澯��Ŀд���ǻ�ȡ100��
			for (auto i = 0; i < iNum; ++i)
			{
				int nAlarmIndex = int(pRealData[i]);
				if (!nAlarmIndex)
				{
					continue;
				}
				m_vAlarmLog.push_back(nAlarmIndex);
			}

			CAlarmLog AlarmLog;
			AlarmLog.SetAnalyzeProtocol(m_pAnalyzeProtocol);
			AlarmLog.SetAlarmLog(m_vAlarmLog);
			AlarmLog.DoModal();

		}
		else
		{
			MessageBox(L"��ȡ�澯ʧ��");
		}
	}
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CAlarmLog AlarmLog;
	//AlarmLog.SetAnalyzeProtocol(m_pAnalyzeProtocol);
	//AlarmLog.SetAlarmLog(m_vAlarmLog);
	//AlarmLog.DoModal();
}


void CDataByPollingDlg::GetVersion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_VERSION);
	}
}




void CDataByPollingDlg::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostMessageA(GetParent()->GetSafeHwnd(), WM_SAVE_CONFIG, 0, 0);
}


void CDataByPollingDlg::OnBnClickedBtnLoad()
{
	PostMessageA(GetParent()->GetSafeHwnd(), WM_LOAD_CONFIG, 0, 0);
}


void CDataByPollingDlg::OnBnClickedButtonRefresh()
{
	PostMessageA(GetParent()->GetSafeHwnd(), WM_REFRESH_CONTROL, 0, 0);
}


void CDataByPollingDlg::OnBnClickedBtnIoStatus()
{
	// ��ȡIO״̬
	CString strCurStatus;
	((CStatic*)GetDlgItem(IDC_STATIC_WORK1))->GetWindowText(strCurStatus);
	if (strCurStatus != "ֹͣ״̬")
	{
		MessageBox(L"��ǰ״̬��ҪΪֹͣ״̬");
		return;
	}

	unsigned int nIoStatus = 0;
	for (int i = 0; i < m_vOutPutStatus.size(); ++i)
	{
		bool bCheck = m_vOutPutStatus.at(i)->GetChecked();
		nIoStatus = nIoStatus | bCheck << i;
	}

	CConfigByIoStatus configByIoStatus(nIoStatus, m_pSerialPort);
	configByIoStatus.DoModal();
}




void CDataByPollingDlg::OnBnClickedBtnClean()
{
	unsigned char zSendBuf[32] = { 0 };
	unsigned char zRevBuf[32] = { 0 };

	zSendBuf[0] = 0xAA;
	zSendBuf[1] = 0x24;
	zSendBuf[2] = CalcCrc8(&zSendBuf[1], 1);
	zSendBuf[3] = 0xEE;
	if (m_pSerialPort && m_pSerialPort->IsOpen())
	{
		char zRevData[32] = { 0 };
		int nMaxRev = 4;
		int nRev = m_pSerialPort->SendAndRev(zSendBuf, 4, zRevData, nMaxRev);
		if (nRev == 4)
		{
			MessageBox(L"��������ɹ�");
			return ;
		}
	}
	MessageBox(L"�������ʧ��");
	return;
}
