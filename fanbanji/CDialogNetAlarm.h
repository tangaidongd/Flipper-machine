#pragma once
#include "analyzeByNetwork.h"

// CDialogNetAlarm 对话框

class CDialogNetAlarm : public CDialogEx
{


public:
	CDialogNetAlarm(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogNetAlarm();

	enum { IDD = IDD_DIALOG_NET_ALARM };
public:
	void SetAlarmMsg(std::vector<ST_AlarmItemData>& vecAlarmItemMsg);

private:
	void InitCtrl();
	

private:
	std::vector<ST_AlarmItemData>  m_vecAlarmItemMsg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listAlarmDetail;
};
