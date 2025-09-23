#pragma once

#include "inc/analyzeByNetwork.h"
#include "cusCheckBox.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "CDialogLogManage.h"
// CDialogReadOnly 对话框
#define  CHECKBOX_NUM_COUNT	82

class CDialogReadOnly : public CDialogEx
{

public:
	CDialogReadOnly(CAnalyzeNetwork* pAnalyzeNetwork, CWnd* pParent = nullptr);   // 标准构造函数
	CDialogReadOnly(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogReadOnly();


	enum { IDD = IDD_DIALOG_READ };

public:
	void UpdateCtrlValue();
	void UpdateAlarmCtrlValue();

	void SignleAutoRunDisplayIo(bool bIsAuto);

private:
	void UpdateIoStatus();
	void InitDisplayStr();
	void InitAlarmCtrl();
	void InitEmptyListCtrl();
	void InitSomeCtrl();
	void WriteAlarmInfo2Csv(std::vector<ST_AlarmItemData>& vecAlarmItemData);
	void WriteCsv(std::vector<ST_AlarmItemData>& vecAlarmItemData, std::string strCsvPath);
	void QueryAlarmInfo();
	void DisplayMotorCtrl(bool bDisplay);
	

private:
	CAnalyzeNetwork*	m_pAnalyzeNetwork;
	CDialogLogManage*	m_pDialogLogManage;
	CCusCheckBox	 m_zCusCheckBox[CHECKBOX_NUM_COUNT];
	CCusCheckBox     m_zCusIOStatus[13];
	CListCtrl		 m_listAlarmDetailMsg;

	int	m_nAlarmNum;				// 记录当前报警数
	int	m_nCurProduceAlarmNum;		// 记录当前更新的报警数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnAlarmClean();
	afx_msg void OnEnChangeEditAlarmNum();
	afx_msg void OnBnClickedBtnLog();
};
