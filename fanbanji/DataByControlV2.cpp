// DataByControlV2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fanbanji.h"
#include "DataByControlV2.h"
#include "afxdialogex.h"


// CDataByControlV2 �Ի���
#define  MS_UINT   0.65					// ms��һ�㵥λ
#define  MS_UINT_SPECIAL 0.69			// ms��һ�㵥λ
#define  DEF_PRECISION   0.5			// ��ȷ�ȵ���

IMPLEMENT_DYNAMIC(CDataByControlV2, CDialogEx)

CDataByControlV2::CDataByControlV2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataByControlV2::IDD, pParent)
{
	m_pAnalyzeProtocol = NULL;			
	m_pSerialThread = NULL;			
	m_pSerialPort = NULL;				
}

CDataByControlV2::~CDataByControlV2()
{
}

void CDataByControlV2::SetSerialPort(CSerialPort* pSerialPort)
{
	if (pSerialPort)
	{
		m_pSerialPort = pSerialPort;
	}
}

void CDataByControlV2::SetSerialThread(CSerialThread* pSerialThread)
{
	if (pSerialThread)
	{
		m_pSerialThread  = pSerialThread;
	}
}

void CDataByControlV2::SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol)
{
	if (pAnalyzeProtocol)
	{
		m_pAnalyzeProtocol = pAnalyzeProtocol;
	}
}

void CDataByControlV2::OnRevCmdMsg(STComData& stComData)
{
	// У�������
	if (!m_pAnalyzeProtocol->CheckRevCmd(stComData))
	{
		return;
	}

	switch(stComData.chTag)
	{
	case EM_QUERY_FANBAN_TYPE:
		QueryType(stComData);
		break;
	case EM_QUERY_INDUCTOR_POSITION:
		QueryInductor(stComData);
		break;
	case EM_QUERY_CYLINDER_SENSOR:
		QuerySensor(stComData);
		break;
	case EM_QUERY_360MACHINE_DIRETION:
		Query360Machine(stComData);
		break;
	case EM_QUERY_SIGNAL_DELAY:
		QuerySignal(stComData);
		break;
	case EM_QUERY_PRESS_TIME:
		QueryPress(stComData);
		break;
	case EM_QUERY_SLOW_FLIP_ANGLE:
		QuerySlow(stComData);
		break;
	case EM_QUERY_TOUCH_SENSOR_ANGLE:
		QueryTouch(stComData);
		break;
	case EM_QUERY_FAILED_JUDGMENT_ANGLE:
		QueryFailed(stComData);
		break;
	case EM_QUERY_PULSE_DISTANCE:
		QueryPulse(stComData);
		break;
	case EM_QUERY_ROLLER_MAX_SPEED:
		QueryRollerSpeed(stComData);
		break;
	case EM_QUERY_PLATFORM_MAX_SPEED:
		QueryPlatformSpeed(stComData);
		break;
	case EM_QUERY_ACCELERATION_DISTANCE:
		QueryAccelerationDis(stComData);
		break;
	default:
		break;
	}
}


void CDataByControlV2::GetControlValue(std::map<int, STCFData>& mapConfigData)
{
	// ��ȡ�ؼ�ֵ
	CString strValue1, strValue2, strValue3;
	STCFData stCFData;
	int nIndex = -1;
	((CStatic*)GetDlgItem(IDC_STATIC_TYPE))->GetWindowTextW(strValue1);
	nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->FindString(0, strValue1);
	stCFData.chCmdID = EM_WRITE_FANBAN_TYPE;
	stCFData.strCFName = "���������";
	stCFData.vCmdValue.push_back(nIndex);
	mapConfigData[EM_WRITE_FANBAN_TYPE] = stCFData;

	((CStatic*)GetDlgItem(IDC_STATIC_INDUCTOR))->GetWindowTextW(strValue1);
	nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->FindString(0, strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_INDUCTOR_POSITION;
	stCFData.strCFName = "������Ӧ����װλ��";
	stCFData.vCmdValue.push_back(nIndex);
	mapConfigData[EM_WRITE_INDUCTOR_POSITION] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_SENSOR))->GetWindowTextW(strValue1);
	nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->FindString(0, strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_CYLINDER_SENSOR;
	stCFData.strCFName = "���׸�Ӧ������";
	stCFData.vCmdValue.push_back(nIndex);
	mapConfigData[EM_WRITE_CYLINDER_SENSOR] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_360MACHINE))->GetWindowTextW(strValue1);
	nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->FindString(0, strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_360MACHINE_DIRETION;
	stCFData.strCFName = "360����ת���͵���ת����";
	stCFData.vCmdValue.push_back(nIndex);
	mapConfigData[EM_WRITE_360MACHINE_DIRETION] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_ROLLER_INIT))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ROLLER_MAX))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ROLLER_MAX_SPEED;
	stCFData.strCFName = "���ִ���ĳ�ʼ������ٶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_ROLLER_MAX_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_PLATFORM_INIT))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_PLATFORM_MAX))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_PLATFORM_MAX_SPEED;
	stCFData.strCFName = "ƽ̨��ת�ĳ�ʼ������ٶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_PLATFORM_MAX_SPEED] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_SIGNAL_IN))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_SIGNAL_OUT))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_SIGNAL_DELAY;
	stCFData.strCFName = "�������ź�ʧЧ�ӳ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_SIGNAL_DELAY] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_ACCELERATION_TRANS))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACCELERATION_FLIP))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_ACCELERATION_DISTANCE;
	stCFData.strCFName = "���䡢��ת�ļ��ٲ���";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_ACCELERATION_DISTANCE] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_PULSE_FORWARD))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_PULSE_REVERSE))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_PULSE_DISTANCE;
	stCFData.strCFName = "�����ִ�������ת�������";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_PULSE_DISTANCE] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_KEEP))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_DISAPPEAR))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_FAILED_JUDGMENT_ANGLE;
	stCFData.strCFName = "��ת��λʧ�ܵ��ж��Ƕ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_FAILED_JUDGMENT_ANGLE] = stCFData;

	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_KEEP))->GetWindowTextW(strValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_DISAPPEAR))->GetWindowTextW(strValue2);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_FAILED_JUDGMENT_ANGLE;
	stCFData.strCFName = "��ת��λʧ�ܵ��ж��Ƕ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	stCFData.vCmdValue.push_back(_ttoi(strValue2));
	mapConfigData[EM_WRITE_FAILED_JUDGMENT_ANGLE] = stCFData;

	((CStatic*)GetDlgItem(IDC_STATIC_PRESS))->GetWindowTextW(strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_PRESS_TIME;
	stCFData.strCFName = "�ذ��굽�а���ѹ�ӳ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	mapConfigData[EM_WRITE_PRESS_TIME] = stCFData;


	((CStatic*)GetDlgItem(IDC_STATIC_SLOW))->GetWindowTextW(strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_SLOW_FLIP_ANGLE;
	stCFData.strCFName = "�������ٷ�ת�ĽǶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	mapConfigData[EM_WRITE_SLOW_FLIP_ANGLE] = stCFData;

	((CStatic*)GetDlgItem(IDC_STATIC_TOUCH))->GetWindowTextW(strValue1);
	stCFData.Init();
	stCFData.chCmdID = EM_WRITE_TOUCH_SENSOR_ANGLE;
	stCFData.strCFName = "�ж����嵽λ��λ�ýǶ�";
	stCFData.vCmdValue.push_back(_ttoi(strValue1));
	mapConfigData[EM_WRITE_TOUCH_SENSOR_ANGLE] = stCFData;
}

void CDataByControlV2::SetControlValue(std::map<int, STCFData>& mapConfigData)
{
	for (auto iter = mapConfigData.begin(); iter != mapConfigData.end(); ++iter)
	{
		switch(iter->first)
		{
		case EM_WRITE_FANBAN_TYPE:
			if (iter->second.vCmdValue.size() > 0)
			{
				SendType(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_INDUCTOR_POSITION:
			if (iter->second.vCmdValue.size() > 0)
			{
				SendInductor(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_CYLINDER_SENSOR:
			if (iter->second.vCmdValue.size() > 0)
			{
				SendSensor(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_360MACHINE_DIRETION:
			if (iter->second.vCmdValue.size() > 0)
			{
				Send360machine(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_SIGNAL_DELAY:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendSignal(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_PRESS_TIME:
			if (iter->second.vCmdValue.size() > 0)
			{
				SendPress(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_SLOW_FLIP_ANGLE:
			if (iter->second.vCmdValue.size() > 0)
			{
				SendSlow(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_TOUCH_SENSOR_ANGLE:
			if (iter->second.vCmdValue.size() > 0)
			{
				//SendSensor(iter->second.vCmdValue.at(0), false);
				SendTouch(iter->second.vCmdValue.at(0), false);
			}
			break;
		case EM_WRITE_FAILED_JUDGMENT_ANGLE:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendFail(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_PULSE_DISTANCE:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendPulse(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;;
		case EM_WRITE_ROLLER_MAX_SPEED:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendRollerSpeed(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_PLATFORM_MAX_SPEED:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendPlatFormSpeed(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		case EM_WRITE_ACCELERATION_DISTANCE:
			if (iter->second.vCmdValue.size() > 1)
			{
				SendAccelerationDis(iter->second.vCmdValue.at(0), iter->second.vCmdValue.at(1), false);
			}
			break;
		default:
			break;
		}
	}
}

void CDataByControlV2::RefreshControlValue()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_FANBAN_TYPE);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_INDUCTOR_POSITION);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_CYLINDER_SENSOR);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_360MACHINE_DIRETION);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_SIGNAL_DELAY);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_PRESS_TIME);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_SLOW_FLIP_ANGLE);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_TOUCH_SENSOR_ANGLE);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_FAILED_JUDGMENT_ANGLE);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSE_DISTANCE);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLLER_MAX_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_PLATFORM_MAX_SPEED);
		Sleep(20);
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACCELERATION_DISTANCE);
		Sleep(20);
	}
}

void CDataByControlV2::QueryType(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	int nIndex = int(chInput1);
	CString strType = L"";
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetLBText(nIndex, strType);
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(nIndex);
	((CStatic*)GetDlgItem(IDC_STATIC_TYPE))->SetWindowText(strType);
}

void CDataByControlV2::QuerySensor(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	int nIndex = int(chInput1);
	CString strType = L"";
	((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->GetLBText( nIndex, strType);
	((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->SetCurSel(nIndex);
	((CStatic*)GetDlgItem(IDC_STATIC_SENSOR))->SetWindowText(strType);
}

void CDataByControlV2::QueryInductor(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	int nIndex = int(chInput1);
	CString strType = L"";
	((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->GetLBText( nIndex, strType);
	((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->SetCurSel(nIndex);
	((CStatic*)GetDlgItem(IDC_STATIC_INDUCTOR))->SetWindowText(strType);
}

void CDataByControlV2::Query360Machine(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	int nIndex = int(chInput1);
	CString strType = L"";
	((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->GetLBText( nIndex, strType);
	((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->SetCurSel(nIndex);
	((CStatic*)GetDlgItem(IDC_STATIC_360MACHINE))->SetWindowText(strType);
}

void CDataByControlV2::QueryRollerSpeed(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	/*u32 nSpeed1 = (u32)pRealData[0];
	u32 nSpeed2 = (u32)pRealData[1];*/
	u32 nSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nSpeed2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	// �ٶȼ��㹫ʽ��3150/V ��VΪ�����ٶȵ�λ1m/s��Ĭ�����9m/s������16m/s���ٶ�ȡֵ��Χ3m/s-35m/s��
	// ��Ӧд��ֵ1050-90��ֵС��90��90д�롣�����ֽڲ�ȡ��˸�ʽ��
	if (nSpeed1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 3150/nSpeed1);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLLER_INIT))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLLER_INIT))->SetWindowText(strValue1);
	}
	if (nSpeed2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 3150/nSpeed2);
		((CStatic*)GetDlgItem(IDC_STATIC_ROLLER_MAX))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_ROLLER_MAX))->SetWindowText(strValue2);
	}
}

void CDataByControlV2::QueryPlatformSpeed(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nSpeed1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nSpeed2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	// �ٶȼ���ʽ��33720/V����/s)��Ĭ�Ϸ�ת����123��/s����ת����25��/s   �������÷�Χ��1-180�㣩
	if (nSpeed1 != 0)
	{
		CString strValue1;
		strValue1.Format(_T("%d"), 33720/nSpeed1);
		((CStatic*)GetDlgItem(IDC_STATIC_PLATFORM_INIT))->SetWindowText(strValue1);
		((CStatic*)GetDlgItem(IDC_EDIT_PLATFORM_INIT))->SetWindowText(strValue1);
	}
	if (nSpeed2 != 0)
	{
		CString strValue2;
		strValue2.Format(_T("%d"), 33720/nSpeed2);
		((CStatic*)GetDlgItem(IDC_STATIC_PLATFORM_MAX))->SetWindowText(strValue2);
		((CStatic*)GetDlgItem(IDC_EDIT_PLATFORM_MAX))->SetWindowText(strValue2);
	}
}

void CDataByControlV2::QuerySignal(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nTime1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nTime2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	CString strValue1;
	strValue1.Format(_T("%d"), nTime1);
	((CStatic*)GetDlgItem(IDC_STATIC_SIGNAL_IN))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_SIGNAL_IN))->SetWindowText(strValue1);

	CString strValue2;
	strValue2.Format(_T("%d"), nTime2);
	((CStatic*)GetDlgItem(IDC_STATIC_SIGNAL_OUT))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_SIGNAL_OUT))->SetWindowText(strValue2);
}

void CDataByControlV2::QueryPress(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nTime1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);

	CString strValue1;
	strValue1.Format(_T("%d"), nTime1);
	((CStatic*)GetDlgItem(IDC_STATIC_PRESS))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_PRESS))->SetWindowText(strValue1);
}

void CDataByControlV2::QuerySlow(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nRollSpeed1 = (int)pRealData[0];

	// �ذ�0.65Ϊ��λ������0.69Ϊ��λ
	nRollSpeed1 = nRollSpeed1*MS_UINT_SPECIAL + DEF_PRECISION;
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nRollSpeed1);
	((CStatic*)GetDlgItem(IDC_STATIC_SLOW))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_SLOW))->SetWindowText(strValue1);

}

void CDataByControlV2::QueryPulse(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nPulse = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);

	u32 nValue1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nValue2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	// Ĭ�ϵ�λΪ0.1��
	//int nPulseDis = nPulse/0.2;
	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_PULSE_FORWARD))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_PULSE_FORWARD))->SetWindowText(strValue1);
	strValue2.Format(_T("%d"), nValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_PULSE_REVERSE))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_PULSE_REVERSE))->SetWindowText(strValue2);
}

void CDataByControlV2::QueryTouch(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nTouch = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);


	//int nPulseDis = nPulse/;

	CString strValue1;
	strValue1.Format(_T("%d"), nTouch);
	((CStatic*)GetDlgItem(IDC_STATIC_TOUCH))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_TOUCH))->SetWindowText(strValue1);
}

void CDataByControlV2::QueryAccelerationDis(STComData &stComData)
{
	u8* pRealData = stComData.zData + 2;
	u8 chInput1 = pRealData[0];
	u8 chInput2 = pRealData[1];
	int nValue1 = int(chInput1);
	int nValue2 = int(chInput2);

	CString strValue1, strValue2;
	strValue1.Format(_T("%d"), nValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_ACCELERATION_TRANS))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_ACCELERATION_TRANS))->SetWindowText(strValue1);
	strValue2.Format(_T("%d"), nValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_ACCELERATION_FLIP))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_ACCELERATION_FLIP))->SetWindowText(strValue2);
}

void CDataByControlV2::QueryFailed(STComData &stComData)
{
	// ��ȡ������������С�˸�ʽ
	u8* pRealData = stComData.zData + 2;
	u32 nValue1 = (pRealData[0]<<8 & 0xffff) | (pRealData[1]&0xffff);
	u32 nValue2 = (pRealData[2]<<8 & 0xffff) | (pRealData[3]&0xffff);

	CString strValue1;
	strValue1.Format(_T("%d"), nValue1);
	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_KEEP))->SetWindowText(strValue1);
	((CStatic*)GetDlgItem(IDC_EDIT_FAILED_KEEP))->SetWindowText(strValue1);

	CString strValue2;
	strValue2.Format(_T("%d"), nValue2);
	((CStatic*)GetDlgItem(IDC_STATIC_FAILED_DISAPPEAR))->SetWindowText(strValue2);
	((CStatic*)GetDlgItem(IDC_EDIT_FAILED_DISAPPEAR))->SetWindowText(strValue2);
}

//void CDataByControlV2::QueryAcelerationTnt(STComData &stComData)
//{
//	u8* pRealData = stComData.zData + 2;
//	u8 chInput1 = pRealData[0];
//	int nValue1 = int(chInput1);
//
//	CString strValue1, strValue2;
//	strValue1.Format(_T("%d"), nValue1);
//	((CStatic*)GetDlgItem(IDC_STATIC_ACCELERATION_TNT))->SetWindowText(strValue1);
//	((CStatic*)GetDlgItem(IDC_EDIT_ACCELERATION_TNT))->SetWindowText(strValue1);
//}



void CDataByControlV2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataByControlV2, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_TYPE1, &CDataByControlV2::OnBnClickedBtnType1)
	ON_BN_CLICKED(IDC_BTN_TYPE2, &CDataByControlV2::OnBnClickedBtnType2)
	ON_BN_CLICKED(IDC_BTN_SENSOR1, &CDataByControlV2::OnBnClickedBtnSensor1)
	ON_BN_CLICKED(IDC_BTN_SENSOR2, &CDataByControlV2::OnBnClickedBtnSensor2)
	ON_BN_CLICKED(IDC_BTN_INDUCTOR1, &CDataByControlV2::OnBnClickedBtnInductor1)
	ON_BN_CLICKED(IDC_BTN_INDUCTOR2, &CDataByControlV2::OnBnClickedBtnInductor2)
	ON_BN_CLICKED(IDC_BTN_360MACHINE1, &CDataByControlV2::OnBnClickedBtn360machine1)
	ON_BN_CLICKED(IDC_BTN_360MACHINE2, &CDataByControlV2::OnBnClickedBtn360machine2)
	ON_BN_CLICKED(IDC_BTN_SIGNAL1, &CDataByControlV2::OnBnClickedBtnSignal1)
	ON_BN_CLICKED(IDC_BTN_SIGNAL2, &CDataByControlV2::OnBnClickedBtnSignal2)
	ON_BN_CLICKED(IDC_BTN_PRESS1, &CDataByControlV2::OnBnClickedBtnPress1)
	ON_BN_CLICKED(IDC_BTN_PRESS2, &CDataByControlV2::OnBnClickedBtnPress2)
	ON_BN_CLICKED(IDC_BTN_SLOW1, &CDataByControlV2::OnBnClickedBtnSlow1)
	ON_BN_CLICKED(IDC_BTN_SLOW2, &CDataByControlV2::OnBnClickedBtnSlow2)
	ON_BN_CLICKED(IDC_BTN_PULSE1, &CDataByControlV2::OnBnClickedBtnPulse1)
	ON_BN_CLICKED(IDC_BTN_PULSE2, &CDataByControlV2::OnBnClickedBtnPulse2)
	ON_BN_CLICKED(IDC_BTN_TOUCH1, &CDataByControlV2::OnBnClickedBtnTouch1)
	ON_BN_CLICKED(IDC_BTN_TOUCH2, &CDataByControlV2::OnBnClickedBtnTouch2)
	ON_BN_CLICKED(IDC_BTN_ACCELERATION_DIS1, &CDataByControlV2::OnBnClickedBtnAccelerationDis1)
	ON_BN_CLICKED(IDC_BTN_ACCELERATION_DIS2, &CDataByControlV2::OnBnClickedBtnAccelerationDis2)
	ON_BN_CLICKED(IDC_BTN_FAILED1, &CDataByControlV2::OnBnClickedBtnFailed1)
	ON_BN_CLICKED(IDC_BTN_FAILED2, &CDataByControlV2::OnBnClickedBtnFailed2)
	//ON_BN_CLICKED(IDC_BTN_EDITACCELERATION_TNT1, &CDataByControlV2::OnBnClickedBtnEditaccelerationTnt1)
	//ON_BN_CLICKED(IDC_BTN_EDITACCELERATION_TNT2, &CDataByControlV2::OnBnClickedBtnEditaccelerationTnt2)
	ON_BN_CLICKED(IDC_BTN_ROLLER_SPEED1, &CDataByControlV2::OnBnClickedBtnRollerSpeed1)
	ON_BN_CLICKED(IDC_BTN_ROLLER_SPEED2, &CDataByControlV2::OnBnClickedBtnRollerSpeed2)
	ON_BN_CLICKED(IDC_BTN_PLATFORM_SPEED1, &CDataByControlV2::OnBnClickedBtnPlatformSpeed1)
	ON_BN_CLICKED(IDC_BTN_PLATFORM_SPEED2, &CDataByControlV2::OnBnClickedBtnPlatformSpeed2)
END_MESSAGE_MAP()


// CDataByControlV2 ��Ϣ�������



void CDataByControlV2::OnBnClickedBtnType1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_FANBAN_TYPE);
	}
}

void CDataByControlV2::SendType(int nParma, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FANBAN_TYPE, nParma))
	{
		BoxCustom(L"EM_WRITE_FANBAN_TYPE ��������Χ", bDisBox);
		return;
	}
	
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nParma&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_FANBAN_TYPE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_FANBAN_TYPE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);
			CString strCur;
			CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE));
			pCombox->GetLBText(nParma, strCur);
			((CButton*)GetDlgItem(IDC_STATIC_TYPE))->SetWindowText(strCur);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}

void CDataByControlV2::OnBnClickedBtnType2()
{
	CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_TYPE));
	int nValueIndex = pCombox->GetCurSel();
	if (nValueIndex != -1)
	{
		SendType(nValueIndex);
	}
}


void CDataByControlV2::OnBnClickedBtnSensor1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_CYLINDER_SENSOR);
	}
}

void CDataByControlV2::SendSensor(int nParam, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_CYLINDER_SENSOR, nParam))
	{
		BoxCustom(L"EM_WRITE_FANBAN_TYPE ��������Χ", bDisBox);
		return;
	}
	
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nParam&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_CYLINDER_SENSOR, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_CYLINDER_SENSOR, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);
			CString strCur;
			CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR));
			pCombox->GetLBText(nParam, strCur);
			((CButton*)GetDlgItem(IDC_STATIC_SENSOR))->SetWindowText(strCur);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}
void CDataByControlV2::OnBnClickedBtnSensor2()
{
	CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR));
	int nValueIndex = pCombox->GetCurSel();
	if (nValueIndex != -1)
	{
		SendSensor(nValueIndex);
	}
}


void CDataByControlV2::OnBnClickedBtnInductor1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_INDUCTOR_POSITION);
	}
}

void CDataByControlV2::SendInductor(int nParam, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_INDUCTOR_POSITION, nParam))
	{
		BoxCustom(L"EM_WRITE_INDUCTOR_POSITION ��������Χ", bDisBox);
		return;
	}

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nParam&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_INDUCTOR_POSITION, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_INDUCTOR_POSITION, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);
			CString strCur;
			CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR));
			pCombox->GetLBText(nParam, strCur);
			((CButton*)GetDlgItem(IDC_STATIC_INDUCTOR))->SetWindowText(strCur);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}

}

void CDataByControlV2::OnBnClickedBtnInductor2()
{
	CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR));
	int nValueIndex = pCombox->GetCurSel();
	if (nValueIndex != -1)
	{
		SendInductor(nValueIndex);
	}
}


void CDataByControlV2::OnBnClickedBtn360machine1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_360MACHINE_DIRETION);
	}
}


void CDataByControlV2::Send360machine(int nParam, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_360MACHINE_DIRETION, nParam))
	{
		BoxCustom(L"EM_WRITE_FANBAN_TYPE ��������Χ", bDisBox);
		return;
	}

	
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nParam&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_360MACHINE_DIRETION, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_360MACHINE_DIRETION, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);
			CString strCur;
			CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE));
			pCombox->GetLBText(nParam, strCur);
			((CButton*)GetDlgItem(IDC_STATIC_360MACHINE))->SetWindowText(strCur);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}

void CDataByControlV2::OnBnClickedBtn360machine2()
{
	CComboBox* pCombox = ((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE));
	int nValueIndex = pCombox->GetCurSel();
	if (nValueIndex != -1)
	{
		Send360machine(nValueIndex);
	}
}


void CDataByControlV2::OnBnClickedBtnSignal1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_SIGNAL_DELAY);
	}
}


void CDataByControlV2::OnBnClickedBtnSignal2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_SIGNAL_IN, strValue1);
	GetEditValue(IDC_EDIT_SIGNAL_OUT, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SendSignal(nEdit1, nEdit2);
}


void CDataByControlV2::SendSignal(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_SIGNAL_DELAY, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_SIGNAL_DELAY, nParam2))
	{
		BoxCustom(L"EM_WRITE_SIGNAL_DELAY ��������Χ", bDisBox);
		return;
	}

	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2>>8&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_SIGNAL_DELAY, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_SIGNAL_DELAY, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_SIGNAL_IN, nParam1);
			SetStaticValue(IDC_STATIC_SIGNAL_OUT, nParam2);
		}
		else
		{
			MessageBox(L"��������ʧ��");
		}
	}
}


void CDataByControlV2::OnBnClickedBtnPress1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_PRESS_TIME);
	}
}


void CDataByControlV2::OnBnClickedBtnPress2()
{
	CString strValue1;
	GetEditValue(IDC_EDIT_PRESS, strValue1);
	int nEdit1 = _ttoi(strValue1);

	SendPress(nEdit1);
}


void CDataByControlV2::SendPress(int nParam1, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PRESS_TIME, nParam1))
	{
		BoxCustom(L"EM_WRITE_PRESS_TIME ��������Χ", bDisBox);
		return;
	}

	u32 nRoll1 = nParam1;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_PRESS_TIME, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_PRESS_TIME, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_PRESS, nParam1);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}


void CDataByControlV2::OnBnClickedBtnSlow1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_SLOW_FLIP_ANGLE);
	}
}


void CDataByControlV2::OnBnClickedBtnSlow2()
{
	CString strValue1;
	GetEditValue(IDC_EDIT_SLOW, strValue1);
	int nEdit1 = _ttoi(strValue1);

	SendSlow(nEdit1);
}


void CDataByControlV2::SendSlow(int nParam1, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_SLOW_FLIP_ANGLE, nParam1))
	{
		BoxCustom(L"EM_WRITE_SLOW_FLIP_ANGLE ��������Χ", bDisBox);
		return;
	}

	int nRoll1 = nParam1/MS_UINT_SPECIAL + DEF_PRECISION;
	// int nRoll1 = 33720/nParam1;
	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_SLOW_FLIP_ANGLE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_SLOW_FLIP_ANGLE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_SLOW, nParam1);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}



void CDataByControlV2::OnBnClickedBtnPulse1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_PULSE_DISTANCE);
	}
}


void CDataByControlV2::OnBnClickedBtnPulse2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_PULSE_FORWARD, strValue1);
	GetEditValue(IDC_EDIT_PULSE_REVERSE, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SendPulse(nEdit1, nEdit2);
}



void CDataByControlV2::SendPulse(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PULSE_DISTANCE, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PULSE_DISTANCE, nParam2))
	{
		BoxCustom(L"EM_WRITE_PULSE_DISTANCE ��������Χ", bDisBox);
		return;
	}


	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2>>8&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_PULSE_DISTANCE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_PULSE_DISTANCE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_PULSE_FORWARD, nParam1);
			SetStaticValue(IDC_STATIC_PULSE_REVERSE, nParam2);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}


void CDataByControlV2::OnBnClickedBtnTouch1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_TOUCH_SENSOR_ANGLE);
	}
}


void CDataByControlV2::OnBnClickedBtnTouch2()
{
	CString strValue1;
	GetEditValue(IDC_EDIT_TOUCH, strValue1);
	int nEdit1 = _ttoi(strValue1);

	SendTouch(nEdit1);
}


void CDataByControlV2::SendTouch(int nParam1, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_TOUCH_SENSOR_ANGLE, nParam1))
	{
		BoxCustom(L"EM_WRITE_TOUCH_SENSOR_ANGLE ��������Χ", bDisBox);
		return;
	}

	u32 nRoll1 = nParam1;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_TOUCH_SENSOR_ANGLE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_TOUCH_SENSOR_ANGLE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_TOUCH, nParam1);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}


void CDataByControlV2::OnBnClickedBtnAccelerationDis1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ACCELERATION_DISTANCE);
	}
}


void CDataByControlV2::OnBnClickedBtnAccelerationDis2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_ACCELERATION_TRANS, strValue1);
	GetEditValue(IDC_EDIT_ACCELERATION_FLIP, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	
	SendAccelerationDis(nEdit1, nEdit2);
}


void CDataByControlV2::SendAccelerationDis(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACCELERATION_DISTANCE, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ACCELERATION_DISTANCE, nParam2))
	{
		BoxCustom(L"EM_WRITE_ACCELERATION_DISTANCE ��������Χ", bDisBox);
		return;
	}

	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ACCELERATION_DISTANCE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ACCELERATION_DISTANCE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_ACCELERATION_TRANS, nParam1);
			SetStaticValue(IDC_STATIC_ACCELERATION_FLIP, nParam2);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
	else
	{
		BoxCustom(L"��������ʧ��", bDisBox);
	}
}


void CDataByControlV2::OnBnClickedBtnFailed1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_FAILED_JUDGMENT_ANGLE);
	}
}


void CDataByControlV2::OnBnClickedBtnFailed2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_FAILED_KEEP, strValue1);
	GetEditValue(IDC_EDIT_FAILED_DISAPPEAR, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);

	SendFail(nEdit1, nEdit2);
}


void CDataByControlV2::SendFail(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FAILED_JUDGMENT_ANGLE, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_FAILED_JUDGMENT_ANGLE, nParam2))
	{
		BoxCustom(L"EM_WRITE_FAILED_JUDGMENT_ANGLE ��������Χ", bDisBox);
		return;
	}

	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	zData[nIndex++] = nRoll1>>8&0x00ff;
	zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2>>8&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;

	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_FAILED_JUDGMENT_ANGLE, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_FAILED_JUDGMENT_ANGLE, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", bDisBox);

			SetStaticValue(IDC_STATIC_FAILED_KEEP, nParam1);
			SetStaticValue(IDC_STATIC_FAILED_DISAPPEAR, nParam2);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}


//void CDataByControlV2::OnBnClickedBtnEditaccelerationTnt1()
//{
//	if (m_pSerialThread)
//	{
//		m_pSerialThread->SendSpecialPro(EM_QUERY_ACCELERATION_INTERVAL);
//	}
//}


//void CDataByControlV2::OnBnClickedBtnEditaccelerationTnt2()
//{
//	CString strValue1;
//	GetEditValue(IDC_EDIT_ACCELERATION_TNT, strValue1);
//	int nEdit1 = _ttoi(strValue1);
//
//	SendAccelerationTnt(nEdit1);
//}


BOOL CDataByControlV2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString(L"��׼����");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString(L"�躸����");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString(L"360���׼����");
	//((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->AddString(L"360���躸����");
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->AddString(L"��תƽ̨��");
	((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->AddString(L"��תƽ̨��");
	((CComboBox*)GetDlgItem(IDC_COMBO_INDUCTOR))->SetCurSel(0);


	((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->AddString(L"�����׸�Ӧ��");
	((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->AddString(L"�����׸�Ӧ��");
	((CComboBox*)GetDlgItem(IDC_COMBO_SENSOR))->SetCurSel(0);


	((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->AddString(L"˳ʱ����ת");
	((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->AddString(L"��ʱ����ת");
	((CComboBox*)GetDlgItem(IDC_COMBO_360MACHINE))->SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDataByControlV2::OnBnClickedBtnRollerSpeed1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_ROLLER_MAX_SPEED);
	}
}


void CDataByControlV2::OnBnClickedBtnRollerSpeed2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_ROLLER_INIT, strValue1);
	GetEditValue(IDC_EDIT_ROLLER_MAX, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	
	SendRollerSpeed(nEdit1, nEdit2);
}


void CDataByControlV2::SendRollerSpeed(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLLER_MAX_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_ROLLER_MAX_SPEED, nParam2))
	{
		BoxCustom(L"EM_WRITE_ROLLER_MAX_SPEED ��������Χ", bDisBox);
		return;
	}

	//	�ٶȼ���ʽ��3150/V(m/s����Ĭ��������30m/s���������10m/s����������18m/s �������÷�Χ��1-50m/s ��
	u32 nRoll1 = nParam1;
	u32 nRoll2 = nParam2;

	// �ٶȼ��㹫ʽ��3150/V ��VΪ�����ٶȵ�λ1m/s��Ĭ�����9m/s������16m/s���ٶ�ȡֵ��Χ3m/s-35m/s����Ӧд��ֵ1050-90��ֵС��90��90д�롣�����ֽڲ�ȡ��˸�ʽ��
	if (nRoll1 == 0 || nRoll2 == 0)
	{
		BoxCustom(L"������ֵ����Ϊ0", bDisBox);
		return;
	}

	nRoll1 = 3150/nRoll1;
	nRoll2 = 3150/nRoll2;

	u32 nIndex = 0;
	u8 zData[MAX_DATA_LEN] = {0};
	/*zData[nIndex++] = nRoll1&0x00ff;
	zData[nIndex++] = nRoll2&0x00ff;*/
	zData[nIndex++] = nRoll1>>8&0xff;
	zData[nIndex++] = nRoll1&0xff;
	zData[nIndex++] = nRoll2>>8&0xff;
	zData[nIndex++] = nRoll2&0xff;


	u8 zDataRet[MAX_DATA_LEN] = {0};
	int nPackLen =  m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_ROLLER_MAX_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{	
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_ROLLER_MAX_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�",bDisBox);

			SetStaticValue(IDC_STATIC_ROLLER_INIT, nParam1);
			SetStaticValue(IDC_STATIC_ROLLER_MAX, nParam2);
		}
		else
		{
			BoxCustom(L"��������ʧ��", bDisBox);
		}
	}
}



void CDataByControlV2::OnBnClickedBtnPlatformSpeed1()
{
	if (m_pSerialThread)
	{
		m_pSerialThread->SendSpecialPro(EM_QUERY_PLATFORM_MAX_SPEED);
	}
}


void CDataByControlV2::OnBnClickedBtnPlatformSpeed2()
{
	CString strValue1, strValue2;
	GetEditValue(IDC_EDIT_PLATFORM_INIT, strValue1);
	GetEditValue(IDC_EDIT_PLATFORM_MAX, strValue2);
	int nEdit1 = _ttoi(strValue1);
	int nEdit2 = _ttoi(strValue2);
	
	SendPlatFormSpeed(nEdit1, nEdit2);
}


void CDataByControlV2::SendPlatFormSpeed(int nParam1, int nParam2, bool bDisBox)
{
	if (!m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PLATFORM_MAX_SPEED, nParam1) 
		|| !m_pAnalyzeProtocol->CheckParmaRange(EM_WRITE_PLATFORM_MAX_SPEED, nParam2))
	{
		BoxCustom(L"EM_WRITE_PLATFORM_MAX_SPEED ��������Χ", bDisBox);
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
	int nPackLen =   m_pAnalyzeProtocol->PackHexBuffer(EM_WRITE_PLATFORM_MAX_SPEED, zData, nIndex, zDataRet);
	if (nPackLen > 0 && m_pSerialPort->IsOpen())
	{
		char zRevData[MAX_DATA_LEN] = {0};
		int nMaxRev =  m_pAnalyzeProtocol->GetProtocolLen(EM_WRITE_PLATFORM_MAX_SPEED, false);
		int nRev = m_pSerialPort->SendAndRev(zDataRet, nPackLen, zRevData, nMaxRev);
		if(nRev == nMaxRev)
		{
			BoxCustom(L"�������óɹ�", false);

			SetStaticValue(IDC_STATIC_PLATFORM_INIT, nParam1);
			SetStaticValue(IDC_STATIC_PLATFORM_MAX, nParam2);
		}
		else
		{
			MessageBox(L"��������ʧ��");
		}
	}
}


void CDataByControlV2::BoxCustom(CString strMsg, bool disBox /*= true*/)
{
	if (disBox)
	{
		MessageBox(strMsg, L"", MB_OK);
	}
}

void CDataByControlV2::SetStaticValue(unsigned int nControlID, unsigned int nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	((CButton*)GetDlgItem(nControlID))->SetWindowText(strValue);
}


void CDataByControlV2::GetEditValue(unsigned int nControlID, CString& strValue)
{
	((CEdit*)GetDlgItem(nControlID))->GetWindowText(strValue);
}
