// CDialogLogManage.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogLogManage.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <io.h>


#define  LOG_RECORD_PATH	"d:\\log\\fanbanji"

// CDialogLogManage 对话框

CDialogLogManage::CDialogLogManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOG_MANAGE, pParent)
{
	m_vecReadCsvAlarmInfo.clear();
	m_mapEnumFile.clear();

	m_nCurPage = 1;
	m_nPageCount = 1;
	m_nPageCapacity = 100;
}

CDialogLogManage::~CDialogLogManage()
{
}

void CDialogLogManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listDisplayAlarmLog);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_timePickStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_timePickEnd);
}


void CDialogLogManage::InitCtrlList()
{
	InitAlarmCtrl();
}


void CDialogLogManage::InitAlarmCtrl()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listDisplayAlarmLog.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listDisplayAlarmLog.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listDisplayAlarmLog.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listDisplayAlarmLog.SetExtendedStyle(dwStyle); //设置扩展风格

	//InitEmptyListCtrl();
	CRect rcList;
	m_listDisplayAlarmLog.GetClientRect(&rcList);
	int nListWidth = rcList.Width() - 4;
	m_listDisplayAlarmLog.DeleteAllItems();
	m_listDisplayAlarmLog.InsertColumn(0, L"索引", LVCFMT_LEFT, 40);//插入列
	m_listDisplayAlarmLog.InsertColumn(1, L"报警项", LVCFMT_LEFT, 60);
	m_listDisplayAlarmLog.InsertColumn(2, L"报警时间", LVCFMT_LEFT, 100);
	m_listDisplayAlarmLog.InsertColumn(3, L"报警定义", LVCFMT_LEFT, 180);
	m_listDisplayAlarmLog.InsertColumn(4, L"报警说明", LVCFMT_LEFT, nListWidth - 380);
}



void CDialogLogManage::ReadLogRecord()
{
	CTime  timeStart;
	CTime  timeEnd;
	m_timePickStart.GetTime(timeStart);
	m_timePickEnd.GetTime(timeEnd);

	CString strTimeValue;
	ST_TIME stStartTime, stEndTime;
	stStartTime.nYear = timeStart.GetYear();
	stStartTime.nMonth = timeStart.GetMonth();
	stStartTime.nDay = timeStart.GetDay();
	strTimeValue.Format(L"%04d%02d%02d", stStartTime.nYear, stStartTime.nMonth, stStartTime.nDay);
	stStartTime.nTimeValue = _ttoi(strTimeValue);

	stEndTime.nYear = timeEnd.GetYear();
	stEndTime.nMonth = timeEnd.GetMonth();
	stEndTime.nDay = timeEnd.GetDay();
	strTimeValue.Format(L"%04d%02d%02d", stEndTime.nYear, stEndTime.nMonth, stEndTime.nDay);
	stEndTime.nTimeValue = _ttoi(strTimeValue);

	m_mapEnumFile.clear();
	// 避免枚举所有文件，主动计算枚举的年月日路径
	EnumFileList(LOG_RECORD_PATH, &stStartTime, &stEndTime);

}


void CDialogLogManage::ReadCsvFile()
{
	std::map<int, std::vector<AlarmItemData>>  mapReadCsvAlarmInfo;
	mapReadCsvAlarmInfo.clear();
	char zReadBuf[270] = { 0 };
	for (auto iter = m_mapEnumFile.rbegin(); iter != m_mapEnumFile.rend(); ++iter)
	{
		CString strFilePath = iter->second;

		std::ifstream inFile;
		inFile.open(strFilePath, std::ios::in);
		if (!inFile.is_open())
			continue;

		// 过滤第一行
		memset(zReadBuf, 0, 270);
		inFile.getline(zReadBuf, 270);

		std::vector<AlarmItemData> vecReadStr;
		vecReadStr.clear();
		while (!inFile.eof())
		{
			AlarmItemData stAlarmItemData;
			memset(zReadBuf, 0, 270);
			inFile.getline(zReadBuf, 270);
			CString strReadLine = CString(zReadBuf);
			int index = strReadLine.Find(_T(","));
			if (index != -1)
			{
				stAlarmItemData.nAlarmID = _ttoi(strReadLine.Left(index));
				strReadLine = strReadLine.Right(strReadLine.GetLength() - index - 1);
			}
			else
			{
				if(!strReadLine.IsEmpty())
					stAlarmItemData.nAlarmID = _ttoi(strReadLine.Left(index));
				strReadLine.Empty();
			}

			index = strReadLine.Find(_T(","));
			if (index != -1)
			{
				stAlarmItemData.strTime = strReadLine.Left(index);
				strReadLine = strReadLine.Right(strReadLine.GetLength() - index - 1);
			}
			else
			{
				if (!strReadLine.IsEmpty())
					stAlarmItemData.strTime = strReadLine;
				strReadLine.Empty();
			}

			index = strReadLine.Find(_T(","));
			if (index != -1)
			{
				stAlarmItemData.strAlarmMsg = strReadLine.Left(index);
				strReadLine = strReadLine.Right(strReadLine.GetLength() - index - 1);
				stAlarmItemData.strAlarmDetail = strReadLine;
			}
			else
			{
				if (!strReadLine.IsEmpty())
					stAlarmItemData.strAlarmMsg = strReadLine;
				strReadLine.Empty();
			}

			if (strReadLine != CString(zReadBuf))
			{
				vecReadStr.push_back(stAlarmItemData);
			}
		}

		if (vecReadStr.size() != 0)
			mapReadCsvAlarmInfo[iter->first] = vecReadStr;

		inFile.close();
	}
	
	// 调整顺序
	m_vecReadCsvAlarmInfo.clear();
	for (auto iter = mapReadCsvAlarmInfo.rbegin(); iter != mapReadCsvAlarmInfo.rend(); ++iter)
	{
		for (auto iterVec = iter->second.rbegin(); iterVec != iter->second.rend(); ++iterVec)
		{
			m_vecReadCsvAlarmInfo.push_back(*iterVec);
		}
	}
}

void CDialogLogManage::DisplayAlarmLog()
{
	m_listDisplayAlarmLog.SetRedraw(false);

	CRect rcList;
	m_listDisplayAlarmLog.GetClientRect(&rcList);
	int nListWidth = rcList.Width();
	m_listDisplayAlarmLog.DeleteAllItems();

	if (m_vecReadCsvAlarmInfo.size() == 0 || m_nCurPage < 1)
	{
		m_listDisplayAlarmLog.SetRedraw(true);
		return;
	}
	
	int nStartData = (m_nCurPage - 1) * m_nPageCapacity;
	int nEndData = m_nCurPage * m_nPageCapacity;
	int nDataCount = 1;
	CString strAlarmTemp;
	for (int i = nStartData; i < nEndData && i < m_vecReadCsvAlarmInfo.size(); ++i)
	{
		AlarmItemData& stAlarmItemData = m_vecReadCsvAlarmInfo[i];
		int nRow = m_listDisplayAlarmLog.InsertItem(nDataCount, L"1212");
		int nIndex = 0;
		strAlarmTemp.Format(L"%d", nDataCount++);
		m_listDisplayAlarmLog.SetItemText(nRow, nIndex++, strAlarmTemp);
		strAlarmTemp.Format(L"0x%02x", stAlarmItemData.nAlarmID);
		m_listDisplayAlarmLog.SetItemText(nRow, nIndex++, strAlarmTemp);
		m_listDisplayAlarmLog.SetItemText(nRow, nIndex++, stAlarmItemData.strTime);
		m_listDisplayAlarmLog.SetItemText(nRow, nIndex++, stAlarmItemData.strAlarmMsg);
		m_listDisplayAlarmLog.SetItemText(nRow, nIndex++, stAlarmItemData.strAlarmDetail);

		if (nDataCount > 100)
			break;
	}
	m_listDisplayAlarmLog.SetRedraw(true);
}



BOOL IsDirExist(char* csDir)
{
	DWORD dwAttrib = GetFileAttributesA(csDir);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}


bool CDialogLogManage::EnumFileList(const char* pFilePath, const ST_TIME* stStartTime,
					const ST_TIME* stEndTime, bool bIsAllFile)
{
	WIN32_FIND_DATAA FindData;
	HANDLE handle;

	std::string strCurFold = pFilePath;

	char fullName[MAX_PATH] = { 0 };
	char filePathName[MAX_PATH] = { 0 };
	sprintf_s(filePathName, "%s\\*.*", pFilePath);

	handle = FindFirstFileA(filePathName, &FindData);
	if (handle == INVALID_HANDLE_VALUE)
	{
		//MessageBox(L"搜索失败", L"", MB_OK);
		return false;
	}
	while (FindNextFileA(handle, &FindData))
	{
		//过滤.和..
		if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}

		sprintf_s(fullName, "%s\\%s", pFilePath, FindData.cFileName);

		//判断是否是文件夹
		if (IsDirExist(fullName))
		{
			std::string strDirPath = FindData.cFileName;
			int nLen = strDirPath.length();
			if (nLen == 8 || nLen == 3 || nLen == 2)
			{
				// 判断年份
				if (nLen == 8)
				{
					if (_stricmp(FindData.cFileName + 4, "year") != 0)
						continue;
					strDirPath.erase(4, nLen);
					int nYear = atoi(strDirPath.c_str());
					if (nYear < stStartTime->nYear || nYear > stEndTime->nYear)
						continue;
				}

				// 判断月份
				if (nLen == 3 || nLen == 2)
				{
					if (_stricmp(FindData.cFileName + nLen - 1, "m") != 0)
						continue;
					strDirPath.erase(nLen - 1, nLen);
					int nMonth = atoi(strDirPath.c_str());

					// 判断年份，不做多余月份检查
					std::string strPreDir = strCurFold.substr(strCurFold.find_last_of('\\') + 1);
					if (strPreDir.length() != 8 || _stricmp(strPreDir.c_str()+4, "year") != 0)
					{
						continue;
					}

					bIsAllFile = true;
					strPreDir.erase(4, nLen);
					int nYear = atoi(strPreDir.c_str());
					if ((nYear == stStartTime->nYear && nMonth == stStartTime->nMonth)
						|| (nYear == stEndTime->nYear && nMonth == stEndTime->nMonth))
					{
						bIsAllFile = false;
					}
					if (nYear == stStartTime->nYear && nMonth != stStartTime->nMonth)
					{
						if (nMonth < stStartTime->nMonth)
						{
							continue;
						}
					}
					if (nYear == stEndTime->nYear && nMonth != stEndTime->nMonth)
					{
						if (nMonth > stEndTime->nMonth)
						{
							continue;
						}
					}
				}

				EnumFileList(fullName, stStartTime, stEndTime, bIsAllFile);
			}
			
		}
		else
		{
			/*string str = "  Arbitrary   str ing with lots of spaces to be removed   .";
			str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());*/
			std::string strTemp = FindData.cFileName;
			std::string suffixStr = strTemp.substr(strTemp.find_last_of('.') + 1);//获取文件后缀
			std::string strFileName = strTemp.substr(0, strTemp.find_last_of('.'));
			suffixStr = CStringA(suffixStr.c_str()).MakeLower();
			if (suffixStr ==  "csv")
			{
				// 隐藏属性文件，也不做处理
				if (FILE_ATTRIBUTE_HIDDEN & FindData.dwFileAttributes)
				{
					continue;
				}

				if (!bIsAllFile)
				{
					int nFileTime = atoi(strFileName.c_str());
					if (nFileTime >= stStartTime->nTimeValue && nFileTime <= stEndTime->nTimeValue)
					{
						m_mapEnumFile[atoi(strFileName.c_str())] = fullName;
					}
					continue;
				}
				
				m_mapEnumFile[atoi(strFileName.c_str())] = fullName;
			}
		}
	}
	FindClose(handle);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CDialogLogManage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CDialogLogManage::OnBnClickedBtnQuery)
	ON_EN_CHANGE(IDC_EDIT_CUR_PAGE, &CDialogLogManage::OnEnChangeEditCurPage)
	ON_BN_CLICKED(IDC_BTN_PRE, &CDialogLogManage::OnBnClickedBtnPre)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CDialogLogManage::OnBnClickedBtnNext)
END_MESSAGE_MAP()


// CDialogLogManage 消息处理程序



void CDialogLogManage::OnBnClickedBtnQuery()
{
	ReadLogRecord(); 
	m_mapEnumFile;
	ReadCsvFile();

	//DisplayAlarmLog();

	DisplayPageTips();
}

void CDialogLogManage::DisplayPageTips()
{
	m_nCurPage = 1;
	m_nPageCount = m_vecReadCsvAlarmInfo.size() / m_nPageCapacity;
	int nMod = m_vecReadCsvAlarmInfo.size() % m_nPageCapacity;
	if (nMod > 0)
		m_nPageCount += 1;

	if (m_nPageCount == 0)
		m_nCurPage = 0;

	CString strFormat;
	strFormat.Format(L"/%d", m_nPageCount);
	((CButton*)GetDlgItem(IDC_STATIC_PAGE_COUNT))->SetWindowText(strFormat);
	strFormat.Format(L"%d", m_nCurPage);
	GetDlgItem(IDC_EDIT_CUR_PAGE)->SetWindowText(strFormat);
}


BOOL CDialogLogManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialogLogManage::OnEnChangeEditCurPage()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString strValue;
	GetDlgItem(IDC_EDIT_CUR_PAGE)->GetWindowText(strValue);
	int nPageValue = _ttoi(strValue);
	if (nPageValue > m_nPageCount)
	{
		return;
	}

	m_nCurPage = nPageValue;
	DisplayAlarmLog();
}


void CDialogLogManage::OnBnClickedBtnPre()
{
	if (m_nPageCount == 0)
		return;

	if (m_nCurPage <= 1)
		m_nCurPage = m_nPageCount;
	else
		m_nCurPage = m_nCurPage - 1;

	CString strFormat;
	strFormat.Format(L"%d", m_nCurPage);
	GetDlgItem(IDC_EDIT_CUR_PAGE)->SetWindowText(strFormat);
}


void CDialogLogManage::OnBnClickedBtnNext()
{
	if (m_nPageCount == 0)
		return;

	if (m_nCurPage >= m_nPageCount)
		m_nCurPage = 1;
	else
		m_nCurPage = m_nCurPage + 1;

	CString strFormat;
	strFormat.Format(L"%d", m_nCurPage);
	GetDlgItem(IDC_EDIT_CUR_PAGE)->SetWindowText(strFormat);
}
