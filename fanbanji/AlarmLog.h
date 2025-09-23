#pragma once

#include "analyzeCmd.h"
#include <vector>
// CAlarmLog �Ի���

class CAlarmLog : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmLog)

public:
	CAlarmLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlarmLog();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM };
public:
	void SetAlarmLog(std::vector<int> & vAlarmLog);
	void SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol);

private:
	std::vector<int> m_vAlarmLog;
	CAnalyzeProtocol*	m_pAnalyzeProtocol;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
