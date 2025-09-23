// CDialogReadOnly.cpp: 实现文件
//

#include <iostream>
#include <stdlib.h>
#include <io.h>
#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogReadOnly.h"
#include "afxdialogex.h"


#define  SAVE_LOG_DIR "D:\\Log\\fanbanji\\"

// CDialogReadOnly 对话框


CDialogReadOnly::CDialogReadOnly(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_READ, pParent)
{
	m_pAnalyzeNetwork = NULL;
	m_pDialogLogManage = NULL;
	m_nAlarmNum = 0;
	m_nCurProduceAlarmNum = 0;
}

CDialogReadOnly::CDialogReadOnly(CAnalyzeNetwork* pAnalyzeNetwork, CWnd* pParent /*= nullptr*/)
{
	m_pAnalyzeNetwork = pAnalyzeNetwork;
	m_nAlarmNum = 0;
}

CDialogReadOnly::~CDialogReadOnly()
{
	if (m_pDialogLogManage)
	{
		delete m_pDialogLogManage;
		m_pDialogLogManage = NULL;
	}
}

void CDialogReadOnly::DoDataExchange(CDataExchange* pDX)
{
	int nCheckIndex = 0;
	for (int i = 0; i < 48 && nCheckIndex < CHECKBOX_NUM_COUNT; ++i)
	{
		DDX_Control(pDX, IDC_CHECK2 + i, m_zCusCheckBox[nCheckIndex++]);
		m_zCusCheckBox[nCheckIndex - 1].EnableWindow(false);
	}

	// 伺服传输旋转状态10个checkbox
	for(int i = 0; i < 10 && nCheckIndex < CHECKBOX_NUM_COUNT; ++i)
	{
		DDX_Control(pDX, IDC_CHECK52 + i, m_zCusCheckBox[nCheckIndex++]);
		m_zCusCheckBox[nCheckIndex - 1].EnableWindow(false);
	}

	// 新增的16个checkbox
	for (int i = 0; i < 16 && nCheckIndex < CHECKBOX_NUM_COUNT; ++i)
	{
		DDX_Control(pDX, IDC_CHECK62 + i, m_zCusCheckBox[nCheckIndex++]);
		m_zCusCheckBox[nCheckIndex - 1].EnableWindow(false);
	}

	DDX_Control(pDX, IDC_CHECK80, m_zCusCheckBox[nCheckIndex++]);
	m_zCusCheckBox[nCheckIndex - 1].EnableWindow(false);
	DDX_Control(pDX, IDC_CHECK81, m_zCusCheckBox[nCheckIndex++]);
	m_zCusCheckBox[nCheckIndex - 1].EnableWindow(false);


	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listAlarmDetailMsg);
}


BEGIN_MESSAGE_MAP(CDialogReadOnly, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ALARM_CLEAN, &CDialogReadOnly::OnBnClickedBtnAlarmClean)
	ON_EN_CHANGE(IDC_EDIT_ALARM_NUM, &CDialogReadOnly::OnEnChangeEditAlarmNum)
	ON_BN_CLICKED(IDC_BTN_LOG, &CDialogReadOnly::OnBnClickedBtnLog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



void CDialogReadOnly::InitDisplayStr()
{

}


BOOL IsDirExist(std::string csDir)
{
	DWORD dwAttrib = GetFileAttributesA(csDir.c_str());
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

//创建多级目录
bool CheckDirectory(std::string& directoryPath)
{
	if (directoryPath.length() > MAX_PATH || directoryPath.empty())
	{
		return false;
	}

	char tmpDirPath[MAX_PATH + 1] = { 0 };
	for (int i = 0; i < directoryPath.length(); ++i)
	{
		tmpDirPath[i] = directoryPath[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (!IsDirExist(tmpDirPath))
			{
				bool flag = CreateDirectoryA(tmpDirPath, NULL);
				if (!flag)
				{
					return false;
				}
			}
		}
	}
	return TRUE;
}


void CDialogReadOnly::WriteCsv(std::vector<ST_AlarmItemData>& vecAlarmItemData, std::string strCsvPath)
{	
	bool bFileExsit = true;
	if (_access(strCsvPath.c_str(), 0) == -1)
		bFileExsit = false;

	std::ofstream dataFile;
	dataFile.open(strCsvPath.c_str(), std::ios::app);
	if (!dataFile.is_open())
		return;

	if (!bFileExsit)
	{
		dataFile << "报警项" << ','
			<< "报警时间" << ','
			<< "报警定义" << ','
			<< "报警说明";
		dataFile << std::endl;
	}

	CString strFormat;
	for (auto iter = vecAlarmItemData.rbegin(); iter != vecAlarmItemData.rend(); ++iter)
	{
		strFormat.Format(L"%d", iter->nAlarmID);
		dataFile << CStringA(strFormat) << ',' << CStringA(iter->strTime) << ','
			<< CStringA(iter->strAlarmMsg) << ',' << CStringA(iter->strAlarmDetail) << std::endl;
	}
	dataFile.close();
	m_nCurProduceAlarmNum = 0;
}


void CDialogReadOnly::QueryAlarmInfo()
{
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_009, (unsigned int&)m_nCurProduceAlarmNum);
	CString strSetValue;
	GetDlgItem(IDC_EDIT_ALARM_NUM)->GetWindowText(strSetValue);
	int nSetQueryNum = _ttoi(strSetValue);
	if (nSetQueryNum > m_nAlarmNum)
		nSetQueryNum = m_nAlarmNum;

	if (0 == nSetQueryNum)
	{
		UpdateAlarmCtrlValue();
	}
	else
	{
		// 最小为当前产生的报警数目，从而写日志
		if (m_nCurProduceAlarmNum > nSetQueryNum)
			nSetQueryNum = m_nCurProduceAlarmNum;
		m_pAnalyzeNetwork->SynchronizeAlarm2Local(nSetQueryNum);
	}
}

void CDialogReadOnly::DisplayMotorCtrl(bool bDisplay)
{
	bool bGetVisble = (GetDlgItem(IDC_STATIC_MOTOR)->GetStyle()& WS_VISIBLE) > 0;
	if (bDisplay != bGetVisble)
	{
		GetDlgItem(IDC_STATIC_MOTOR)->ShowWindow(bDisplay);
		GetDlgItem(IDC_CHECK80)->ShowWindow(bDisplay);
		GetDlgItem(IDC_CHECK81)->ShowWindow(bDisplay);
		GetDlgItem(IDC_STATIC_020_TEXT)->ShowWindow(bDisplay);
		GetDlgItem(IDC_STATIC_TAG_020)->ShowWindow(bDisplay);
		GetDlgItem(IDC_STATIC_020_UINT)->ShowWindow(bDisplay);
		GetDlgItem(IDC_STATIC_020_NUM_TEXT)->ShowWindow(bDisplay);
		GetDlgItem(IDC_STATIC_TAG_20_NUM)->ShowWindow(bDisplay);
	}
}

void CDialogReadOnly::SignleAutoRunDisplayIo(bool bIsAuto)
{
	CString strValue;
	// jin2_4
	strValue = bIsAuto ? L"收放机请板" : L"下流机请板";
	GetDlgItem(IDC_CHECK9)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK9)->Invalidate();

	// jin6_1
	strValue = bIsAuto ? L"从左到右传输" : L"预留";
	GetDlgItem(IDC_CHECK22)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK22)->Invalidate();

	// jin6_2
	strValue = bIsAuto ? L"从右到左传输" : L"预留";
	GetDlgItem(IDC_CHECK23)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK23)->Invalidate();

	// jin6_3
	strValue = bIsAuto ? L"最后一块板" : L"预留";
	GetDlgItem(IDC_CHECK24)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK24)->Invalidate();

	// jin6_4
	strValue = bIsAuto ? L"移栽机请板" : L"预留";
	GetDlgItem(IDC_CHECK25)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK25)->Invalidate();

	// jin7_1
	strValue = bIsAuto ? L"收放机出板感应" : L"预留";
	GetDlgItem(IDC_CHECK62)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK62)->Invalidate();

	// jin7_2
	strValue = bIsAuto ? L"收放机出板滚动" : L"预留";
	GetDlgItem(IDC_CHECK63)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK63)->Invalidate();

	// jin7_3
	strValue = bIsAuto ? L"收放机报警" : L"预留";
	GetDlgItem(IDC_CHECK64)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK64)->Invalidate();

	// jin7_4
	strValue = bIsAuto ? L"收放机完板" : L"预留";
	GetDlgItem(IDC_CHECK65)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK65)->Invalidate();

	// jin8_3
	strValue = bIsAuto ? L"接收板OK" : L"预留";
	GetDlgItem(IDC_CHECK68)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK68)->Invalidate();

	// jin8_4
	strValue = bIsAuto ? L"接收板NG" : L"预留";
	GetDlgItem(IDC_CHECK69)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK69)->Invalidate();


	// jout2_1
	strValue = bIsAuto ? L"向移栽机要板" : L"向上流发送请板";
	GetDlgItem(IDC_CHECK38)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK38)->Invalidate();

	// jout2_3
	strValue = bIsAuto ? L"向收放机要板" : L"预留";
	GetDlgItem(IDC_CHECK40)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK40)->Invalidate();

	// jout5_1
	strValue = bIsAuto ? L"上报完板" : L"预留";
	GetDlgItem(IDC_CHECK70)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK70)->Invalidate();

	// jout5_2
	strValue = bIsAuto ? L"收放机切换" : L"预留";
	GetDlgItem(IDC_CHECK71)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK71)->Invalidate();

	// jout5_3
	strValue = bIsAuto ? L"上报板OK" : L"预留";
	GetDlgItem(IDC_CHECK72)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK72)->Invalidate();

	// jout5_4
	strValue = bIsAuto ? L"上报板NG" : L"预留";
	GetDlgItem(IDC_CHECK73)->SetWindowText(strValue);
	GetDlgItem(IDC_CHECK73)->Invalidate();
}

void CDialogReadOnly::WriteAlarmInfo2Csv(std::vector<ST_AlarmItemData>& vecAlarmItemData)
{
	if (m_nCurProduceAlarmNum != 0 && vecAlarmItemData.size() >= m_nCurProduceAlarmNum)
	{
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		CString strCsvPath;
		strCsvPath.Format(L"%dYEAR\\%dM\\%04d%02d%02d.csv", systime.wYear,
			systime.wMonth, systime.wYear, systime.wMonth, systime.wDay);

		// 检查目录
		std::string strCsvFullPath;
		strCsvFullPath.append(SAVE_LOG_DIR);
		strCsvFullPath.append(CStringA(strCsvPath));
		CheckDirectory(strCsvFullPath);

		std::vector<ST_AlarmItemData> vecAlarmItemDataLog(vecAlarmItemData.begin(), 
			vecAlarmItemData.begin() + m_nCurProduceAlarmNum);
		WriteCsv(vecAlarmItemDataLog, strCsvFullPath);
		m_nCurProduceAlarmNum = 0;
	}
}


void CDialogReadOnly::UpdateAlarmCtrlValue()
{
	if(!m_pAnalyzeNetwork)
		return;

	CString strSetValue;
	GetDlgItem(IDC_EDIT_ALARM_NUM)->GetWindowText(strSetValue);

	// nDisplayQueryNum 为当前界面显示的报警，当前报警数与设置的显示数目取最小
	int nDisplayQueryNum = _ttoi(strSetValue);
	if(nDisplayQueryNum > m_nAlarmNum)
		nDisplayQueryNum = m_nAlarmNum;

	// m_nCurProduceAlarmNum当前新产生报警数，无论显示多少，都要写入足够数
	int nGetAlarmNum = m_nCurProduceAlarmNum > nDisplayQueryNum ? m_nCurProduceAlarmNum : nDisplayQueryNum;
	std::vector<ST_AlarmItemData> vecAlarmItem;
	vecAlarmItem.clear();
	m_pAnalyzeNetwork->GetAlarmInfo(nGetAlarmNum, vecAlarmItem);
	
	// 写日志
	WriteAlarmInfo2Csv(vecAlarmItem);

	m_listAlarmDetailMsg.SetRedraw(false);
	CRect rcList;
	m_listAlarmDetailMsg.GetClientRect(&rcList);
	int nListWidth = rcList.Width();
	m_listAlarmDetailMsg.DeleteAllItems();

	if (nDisplayQueryNum == 0)
	{
		m_listAlarmDetailMsg.SetRedraw(true);
		return;
	}
		
	CString strAlarmTemp;
	for (int i = 0; i < vecAlarmItem.size() && i < nDisplayQueryNum; ++i)
	{
		ST_AlarmItemData& stAlarmItem = vecAlarmItem[i];
		int nRow = m_listAlarmDetailMsg.InsertItem(i, L"1212");

		int nIndex = 0;
		strAlarmTemp.Format(L"%d", i+1);
		m_listAlarmDetailMsg.SetItemText(nRow, nIndex++, strAlarmTemp);
		strAlarmTemp.Format(L"0x%02x", stAlarmItem.nAlarmID);
		m_listAlarmDetailMsg.SetItemText(nRow, nIndex++, strAlarmTemp);
		m_listAlarmDetailMsg.SetItemText(nRow, nIndex++, stAlarmItem.strTime);
		m_listAlarmDetailMsg.SetItemText(nRow, nIndex++, stAlarmItem.strAlarmMsg);
		m_listAlarmDetailMsg.SetItemText(nRow, nIndex++, stAlarmItem.strAlarmDetail);
	}

	m_listAlarmDetailMsg.SetRedraw(true);
}


void CDialogReadOnly::UpdateIoStatus()
{
	// io状态相关
	unsigned int nValue = 0;
	unsigned char zIoStatus[10] = { 0 };
	if (!m_pAnalyzeNetwork->GetMultiTagValue(EM_PRO_TAG_011, 6, zIoStatus))
		return;
	for (int i = 0; i < 32; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK2 + i);
		unsigned char chValue = zIoStatus[i / 8];
		u32 nValue = chValue >> (i % 8) & 0x01;
		pIoStatus->SetChecked(!nValue);
	}
	for (int i = 32; i < 48; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK2 + i);
		unsigned char chValue = zIoStatus[i / 8];
		u32 nValue = chValue >> (i % 8) & 0x01;
		pIoStatus->SetChecked(nValue);
	}

	// jout5  sw1-4
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_007, nValue);
	unsigned char chValue = nValue & 0xff;
	int nBitIndex = 0;
	for (int i = 0; i < 4; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK74 + i);
		u32 nValue = chValue >> nBitIndex++ & 0x01;
		pIoStatus->SetChecked(!nValue);
	}
	for (int i = 0; i < 4; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK70 + i);
		u32 nValue = chValue >> nBitIndex++ & 0x01;
		pIoStatus->SetChecked(nValue);
	}
	

	// jin7-8
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_008, nValue);
	chValue = nValue & 0xff;
	for (int i = 0; i < 8; ++i)
	{
		CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK62 + i);
		u32 nValue = chValue >> i & 0x01;
		pIoStatus->SetChecked(!nValue);
	}

	//	传输伺服IO状态
	//	传输伺服脉冲频率1
	CString strTrans = L"";
	m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_022, strTrans);
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_017, nValue))
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 3)
			{
				CCusCheckBox* pIoStatusLeft = (CCusCheckBox*)GetDlgItem(IDC_CHECK52 + i);
				CCusCheckBox* pIoStatusRight = (CCusCheckBox*)GetDlgItem(IDC_CHECK52 + i + 1);
				if (_ttoi(strTrans) == 0)
				{
					pIoStatusLeft->SetChecked(0);
					pIoStatusRight->SetChecked(0);
					break;
				}
				u32 unCheckValue = nValue >> (i) & 0x01;
				pIoStatusLeft->SetChecked(!unCheckValue);
				pIoStatusRight->SetChecked(unCheckValue);
				break;
			}
			CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK52 + i);
			u32 unCheckValue = nValue >> (i) & 0x01;
			if (i == 0)
				unCheckValue = !unCheckValue;
			pIoStatus->SetChecked(unCheckValue);
		}
	}

	//	旋转伺服脉冲频率1
	CString strRotate = L"";
	m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_024, strRotate);
	//	旋转伺服IO状态
	if (m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_018, nValue))
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 3)
			{
				CCusCheckBox* pIoStatusLeft = (CCusCheckBox*)GetDlgItem(IDC_CHECK57 + i);
				CCusCheckBox* pIoStatusRight = (CCusCheckBox*)GetDlgItem(IDC_CHECK57 + i + 1);
				if (_ttoi(strRotate) == 0)
				{
					pIoStatusLeft->SetChecked(0);
					pIoStatusRight->SetChecked(0);
					break;
				}
				u32 unCheckValue = nValue >> (i) & 0x01;
				pIoStatusLeft->SetChecked(!unCheckValue);
				pIoStatusRight->SetChecked(unCheckValue);
				break;
				break;
			}
			CCusCheckBox* pIoStatus = (CCusCheckBox*)GetDlgItem(IDC_CHECK57 + i);
			u32 unCheckValue = nValue >> (i) & 0x01;
			if (i == 0)
				unCheckValue = !unCheckValue;
			pIoStatus->SetChecked(unCheckValue);
		}
	}

	static int nTemp = 10;
	nTemp = nTemp + 1;
	unsigned int nTransferType = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_105, nTransferType);
	bool bDisble = nTransferType == 1 ? true : false;
	DisplayMotorCtrl(bDisble);
	if (bDisble)
	{
		// 马达IO
		unsigned int nMotorStatus = 0;
		CString strVolValue;
		m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_019, nMotorStatus);
		m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_020, strVolValue);
		// 方向
		CCusCheckBox* pIoMotorRight = (CCusCheckBox*)GetDlgItem(IDC_CHECK80);
		CCusCheckBox* pIoMotorLeft = (CCusCheckBox*)GetDlgItem(IDC_CHECK81);
		u32 unCheckValue = nMotorStatus & 0x01;
		pIoMotorRight->SetChecked(unCheckValue);
		unCheckValue = nMotorStatus & 0x02;
		pIoMotorLeft->SetChecked(unCheckValue);
		// 电压
		((CButton*)GetDlgItem(IDC_STATIC_TAG_020))->SetWindowText(strVolValue);
		CString strTransNum;
		double dTransNum = _ttof(strVolValue) * 140;
		strTransNum.Format(L"%.0f", dTransNum);
		((CButton*)GetDlgItem(IDC_STATIC_TAG_20_NUM))->SetWindowText(strTransNum);
	}
}


void CDialogReadOnly::UpdateCtrlValue()
{
	if (!m_pAnalyzeNetwork)
		return;

	UpdateIoStatus();

	//	传输伺服脉冲频率1
	CString strTrans = L"";
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_022, strTrans))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_022))->SetWindowText(strTrans);

	//	旋转伺服脉冲频率1
	CString strRotate = L"";
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_024, strRotate))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_024))->SetWindowText(strRotate);

	// 部分只读的数据显示
	unsigned int nValue = 0;
	CString strValue = L"";

	//	当前传输实际速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_026, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_026))->SetWindowText(strValue);
	// 当前传输速度转换为米/分钟
	double dTransValue = _ttof(strValue);
	strValue.Format(L"%.1f m/min", dTransValue*60/1000);
	((CButton*)GetDlgItem(IDC_STATIC_TAG_026_TRANS))->SetWindowText(strValue);

	//	当前旋转实际速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_028, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_028))->SetWindowText(strValue);

	//	进板信号持续距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_030, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_030))->SetWindowText(strValue);

	//	出板信号持续距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_032, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_032))->SetWindowText(strValue);

	////	上次旋转整体角度1
	//if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_034, strValue))
	//	((CButton*)GetDlgItem(IDC_STATIC_TAG_034))->SetWindowText(strValue);

	////	当前水平停留角度1
	//if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_036, strValue))
	//	((CButton*)GetDlgItem(IDC_STATIC_TAG_036))->SetWindowText(strValue);

	//	请板时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_038, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_038))->SetWindowText(strValue);

	//	入板时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_040, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_040))->SetWindowText(strValue);

	//	到位时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_042, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_042))->SetWindowText(strValue);

	//	快速翻板时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_044, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_044))->SetWindowText(strValue);

	//	慢速翻板时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_046, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_046))->SetWindowText(strValue);


	//	水平不当时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_048, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_048))->SetWindowText(strValue);

	//	等待出板状态运行时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_050, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_050))->SetWindowText(strValue);

	//	出板状态运行时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_052, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_052))->SetWindowText(strValue);
	
	//	上次翻板总耗时1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_054, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_054))->SetWindowText(strValue);

	//	上次翻板动作耗时1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_056, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_056))->SetWindowText(strValue);

	//	无故障翻板次数1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_058, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_058))->SetWindowText(strValue);

	//	当前工作状态
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_060, strValue))
	{
		CString strTemp = m_pAnalyzeNetwork->GetWorkStatusStr(_ttoi(strValue));
		((CButton*)GetDlgItem(IDC_STATIC_TAG_060))->SetWindowText(strTemp);
	}
		
	//	上次工作状态
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_061, strValue))
	{
		CString strTemp = m_pAnalyzeNetwork->GetWorkStatusStr(_ttoi(strValue));
		((CButton*)GetDlgItem(IDC_STATIC_TAG_061))->SetWindowText(strTemp);
	}

	//	细分状态
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_062, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_062))->SetWindowText(strValue);

	//	当前旋转角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_204, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_204))->SetWindowText(strValue);

	//	零位同时感应角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_206, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_206))->SetWindowText(strValue);

	//	非零同时感应角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_208, strValue))
		((CButton*)GetDlgItem(IDC_STATIC_TAG_208))->SetWindowText(strValue);

	// 当前报警数
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_010, strValue))
	{
		((CButton*)GetDlgItem(IDC_STATIC_CUR_ALARM_NUM))->SetWindowText(strValue);
		int nAlarmNum = _ttoi(strValue);
		if(m_nAlarmNum != nAlarmNum)
		{
			m_nAlarmNum = nAlarmNum;
			QueryAlarmInfo();	
		}
	}	
}

void CDialogReadOnly::InitEmptyListCtrl()
{
	CRect rcList;
	m_listAlarmDetailMsg.GetClientRect(&rcList);
	int nListWidth = rcList.Width() - 40;
	m_listAlarmDetailMsg.DeleteAllItems();
	m_listAlarmDetailMsg.InsertColumn(0, L"索引", LVCFMT_LEFT, 80);//插入列
	m_listAlarmDetailMsg.InsertColumn(1, L"报警项", LVCFMT_LEFT, 80);
	m_listAlarmDetailMsg.InsertColumn(2, L"报警时间", LVCFMT_LEFT, 140);
	m_listAlarmDetailMsg.InsertColumn(3, L"报警定义", LVCFMT_LEFT, 220);
	m_listAlarmDetailMsg.InsertColumn(4, L"报警说明", LVCFMT_LEFT, nListWidth- 520);
}



void CDialogReadOnly::InitSomeCtrl()
{
	InitAlarmCtrl();

	// 创建日志管理
	m_pDialogLogManage = new CDialogLogManage();
	m_pDialogLogManage->Create(IDD_DIALOG_LOG_MANAGE);
	m_pDialogLogManage->ShowWindow(SW_HIDE);

	DisplayMotorCtrl(false);
}



void CDialogReadOnly::InitAlarmCtrl()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listAlarmDetailMsg.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listAlarmDetailMsg.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listAlarmDetailMsg.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listAlarmDetailMsg.SetExtendedStyle(dwStyle); //设置扩展风格

	//InitEmptyListCtrl();
	CRect rcList;
	m_listAlarmDetailMsg.GetClientRect(&rcList);
	int nListWidth = rcList.Width() - 40;
	m_listAlarmDetailMsg.DeleteAllItems();
	m_listAlarmDetailMsg.InsertColumn(0, L"索引", LVCFMT_LEFT, 40);//插入列
	m_listAlarmDetailMsg.InsertColumn(1, L"报警项", LVCFMT_LEFT, 60);
	m_listAlarmDetailMsg.InsertColumn(2, L"报警时间", LVCFMT_LEFT, 100);
	m_listAlarmDetailMsg.InsertColumn(3, L"报警定义", LVCFMT_LEFT, 180);
	m_listAlarmDetailMsg.InsertColumn(4, L"报警说明", LVCFMT_LEFT, nListWidth- 380);

}


BOOL CDialogReadOnly::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_ALARM_NUM)->SetWindowText(L"20");

	InitSomeCtrl();

	UpdateCtrlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogReadOnly::OnBnClickedBtnAlarmClean()
{
	int nResult = MessageBox(L"报警是否清零", L"提示", MB_YESNO);
	if(IDNO == nResult)
		return;

	int nAlarm = 0xab;
	m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_194, nAlarm);
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_194, EM_PRO_TAG_194);
}

void CDialogReadOnly::OnEnChangeEditAlarmNum()
{
	QueryAlarmInfo();
}


void CDialogReadOnly::OnBnClickedBtnLog()
{
	


	// 测试代码 start
	/*std::vector<ST_AlarmItemData> vecAlarmData;
	for (int i = 0; i < 40; ++i)
	{
		CString strTime;
		strTime.Format(L"202606%d", 40-i);
		ST_AlarmItemData stAlarmItemData;
		stAlarmItemData.nAlarmID = 10 + i;
		stAlarmItemData.strTime = strTime;
		stAlarmItemData.strAlarmMsg = L"fsafasf";
		stAlarmItemData.strAlarmDetail = L"dfasfsdaf";
		vecAlarmData.push_back(stAlarmItemData);
	}
	m_nCurProduceAlarmNum = 20;
	WriteAlarmInfo2Csv(vecAlarmData);*/
	// end
	
	if (m_pDialogLogManage)
	{
		m_pDialogLogManage->CenterWindow();
		m_pDialogLogManage->ShowWindow(SW_NORMAL);
	}
}
