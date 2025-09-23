#pragma once
#include "inc/analyzeByNetwork.h"
#include "CDialogForceIo.h"
#include "CDialogIoReplace.h"
#include "CDialogFunCfg.h"
#include "CCDialogSetIP.h"

// CDialogConfigV2 对话框

class CDialogConfigV2 : public CDialogEx
{

public:
	CDialogConfigV2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogConfigV2();
	 
// 对话框数据
	enum { IDD = IDD_DIALOG_CFG_2 };

public:
	void SetAnalyzeNetwork(CAnalyzeNetwork* pAnalyzeNetwork) ;

	void UpdateCtrlValue();
	void UpdateCtrlValueByForceIo();
	void UpdateCtrlValueByReplace();
	void UpdateCtrlValueByFunCfg();

	// 单机自动化文字
	void SignleAutoRunDisplayIo(bool bIsAuto);

private:
	// 0 停止    1:启动二次回零    2:启动旋转  3:旋转半周
	void SetStartStart(CString strStartValue);

	// 老化测试 0:停止 1:旋转轴老化 2:全动作老化 3:设定老化次数清0
	void SetAgeActionTest(CString strStartValue);

	void SetSylinderOutBackStatus(CString strStatus);
	void InitSomeParam();

private:
	CAnalyzeNetwork* m_pAnalyzeNetwork;

	CDialogForceIo*		m_pDialogForceIo;
	CDialogIoReplace*	m_pDialogIoReplace;
	CDialogFunCfg*		m_pDialogFunCfg;
	CCDialogSetIP*		m_pDialogSetIP;
	// cylinder out back

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnStartSecond();
	afx_msg void OnBnClickedBtnStartHalf();
	afx_msg void OnBnClickedBtnAgeRotate();
	afx_msg void OnBnClickedBtnAgeAction();
	afx_msg void OnBnClickedBtnAgeStop();
	afx_msg void OnBnClickedBtnAgeClean();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnForceIo();
	afx_msg void OnBnClickedBtnOutReplace();
	afx_msg void OnBnClickedBtnCfg105106();
	afx_msg void OnBnClickedBtnSetIp();
	afx_msg void OnBnClickedBtn2Time();
	afx_msg void OnBnClickedBtnLeftBack();
	afx_msg void OnBnClickedBtnLeftOut();
	afx_msg void OnBnClickedBtnRightBack();
	afx_msg void OnBnClickedBtnRightOut();
};
