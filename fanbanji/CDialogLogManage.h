#pragma once


// CDialogLogManage 对话框
#include <map>
#include <string>
#include <vector>
#include "analyzeByNetwork.h"

struct ST_TIME
{
	int nYear;
	int nMonth;
	int nDay;
	int nTimeValue;
	ST_TIME()
	{
		nYear	= 0;
		nMonth	= 0;
		nDay	= 0;
		nTimeValue = 0;
	}
};


class CDialogLogManage : public CDialogEx
{
public:
	CDialogLogManage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogLogManage();

	enum { IDD = IDD_DIALOG_LOG_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	void InitCtrlList();
	void InitAlarmCtrl();

	void ReadLogRecord();
	void ReadCsvFile();
	void DisplayAlarmLog();
	void DisplayPageTips();

	bool EnumFileList(const char* pFilePath, const ST_TIME* stStartTime, const ST_TIME* stEndTime, bool bIsAllFile = true);
private:
	CListCtrl m_listDisplayAlarmLog;
	CDateTimeCtrl m_timePickStart;
	CDateTimeCtrl m_timePickEnd;

	std::map<int, CString>		 m_mapEnumFile;
	std::vector<AlarmItemData>   m_vecReadCsvAlarmInfo;

	// 翻页相关
	int m_nCurPage;
	int m_nPageCount;
	int m_nPageCapacity;

public:
	
	afx_msg void OnBnClickedBtnQuery();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditCurPage();
	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnNext();
	
};
