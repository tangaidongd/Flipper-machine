#pragma once

#include "analyzeCmd.h"
#include <vector>
// CAlarmLog 对话框

class CAlarmLog : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmLog)

public:
	CAlarmLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlarmLog();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALARM };
public:
	void SetAlarmLog(std::vector<int> & vAlarmLog);
	void SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol);

private:
	std::vector<int> m_vAlarmLog;
	CAnalyzeProtocol*	m_pAnalyzeProtocol;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
