#pragma once


#include "serialThread.h"
#include "serialport.h"
#include "analyzeCmd.h"



// CDataByControlV2 对话框

class CDataByControlV2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDataByControlV2)

public:
	CDataByControlV2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataByControlV2();

// 对话框数据
	enum { IDD = IDD_DIALOG_CTL_V2 };


public:
	void SetSerialPort(CSerialPort* pSerialPort);
	void SetSerialThread(CSerialThread* pSerialThread);		// 设置工作线程
	void SetAnalyzeProtocol(CAnalyzeProtocol* pAnalyzeProtocol);
	void OnRevCmdMsg(STComData& stComData);

	void GetControlValue(std::map<int, STCFData>& mapConfigData);
	void SetControlValue(std::map<int, STCFData>& mapConfigData);
	void RefreshControlValue();


private:
	void QueryType(STComData &stComData);
	void QuerySensor(STComData &stComData);
	void QueryInductor(STComData &stComData);
	void Query360Machine(STComData &stComData);
	void QueryRollerSpeed(STComData &stComData);		
	void QueryPlatformSpeed(STComData &stComData);
	void QuerySignal(STComData &stComData);
	void QueryPress(STComData &stComData);
	void QuerySlow(STComData &stComData);
	void QueryPulse(STComData &stComData);
	void QueryTouch(STComData &stComData);
	void QueryAccelerationDis(STComData &stComData);
	void QueryFailed(STComData &stComData);
	//void QueryAcelerationTnt(STComData &stComData);

	void SendType(int nParma, bool bDisBox = true);
	void SendInductor(int nParam, bool bDisBox = true);
	void SendSignal(int nParam1, int nParam2, bool bDisBox = true);
	void SendPress(int nParam1, bool bDisBox = true);
	void SendSlow(int nParam1, bool bDisBox = true);
	void SendPulse(int nParam1, int nParam2, bool bDisBox = true);
	void SendTouch(int nParam1, bool bDisBox = true);
	void SendAccelerationDis(int nParam1, int nParam2, bool bDisBox = true);
	void SendFail(int nParam1, int nParam2, bool bDisBox = true);
	void SendPlatFormSpeed(int nParam1, int nParam2, bool bDisBox = true);
	void SendRollerSpeed(int nParam1, int nParam2, bool bDisBox = true);

	void BoxCustom(CString strMsg, bool disBox = true);


	void GetEditValue(unsigned int nControlID, CString& strValue);
	void SetStaticValue(unsigned int nControlID, unsigned int nValue);
	

	
private:
	CAnalyzeProtocol*	m_pAnalyzeProtocol;			// 数据转换与协议
	CSerialThread*		m_pSerialThread;			// 设备工作线程
	CSerialPort*		m_pSerialPort;				//	Com设备通讯



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnType1();
	afx_msg void OnBnClickedBtnType2();
	afx_msg void OnBnClickedBtnSensor1();
	void SendSensor(int nParam, bool bDisBox = true);
	afx_msg void OnBnClickedBtnSensor2();
	afx_msg void OnBnClickedBtnInductor1();
	afx_msg void OnBnClickedBtnInductor2();
	afx_msg void OnBnClickedBtn360machine1();
	void Send360machine(int nParam, bool bDisBox = true);
	afx_msg void OnBnClickedBtn360machine2();	
	afx_msg void OnBnClickedBtnSignal1();
	afx_msg void OnBnClickedBtnSignal2();
	afx_msg void OnBnClickedBtnPress1();
	afx_msg void OnBnClickedBtnPress2();	
	afx_msg void OnBnClickedBtnSlow1();
	afx_msg void OnBnClickedBtnSlow2();
	afx_msg void OnBnClickedBtnPulse1();
	afx_msg void OnBnClickedBtnPulse2();
	afx_msg void OnBnClickedBtnTouch1();
	afx_msg void OnBnClickedBtnTouch2();
	afx_msg void OnBnClickedBtnAccelerationDis1();
	afx_msg void OnBnClickedBtnAccelerationDis2();
	afx_msg void OnBnClickedBtnFailed1();
	afx_msg void OnBnClickedBtnFailed2();
	//afx_msg void OnBnClickedBtnEditaccelerationTnt1();
	//afx_msg void OnBnClickedBtnEditaccelerationTnt2();
	afx_msg void OnBnClickedBtnRollerSpeed1();
	afx_msg void OnBnClickedBtnRollerSpeed2();
	afx_msg void OnBnClickedBtnPlatformSpeed1();
	afx_msg void OnBnClickedBtnPlatformSpeed2();
	virtual BOOL OnInitDialog();
};
