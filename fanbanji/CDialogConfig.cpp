// CDialogConfig.cpp: 实现文件
//

#include "stdafx.h"
#include "fanbanji.h"
#include "CDialogConfig.h"
#include "afxdialogex.h"


// CDialogConfig 对话框


CDialogConfig::CDialogConfig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG, pParent)
{
	m_pAnalyzeNetwork = NULL;
	m_nRollBoardType = -1;
}

CDialogConfig::CDialogConfig(CAnalyzeNetwork* pAnalyzeNetwork, CWnd* pParent /*= nullptr*/)
{
	m_pAnalyzeNetwork = pAnalyzeNetwork;
	m_nRollBoardType = -1;
}

CDialogConfig::~CDialogConfig()
{
}


void CDialogConfig::UpdateCtrlValue()
{
	if (!m_pAnalyzeNetwork)
		return;

	// 部分只读的数据显示
	unsigned int nTagValue = 0;
	CString strValue = L"";
	//	机型方向
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_100, nTagValue);
	m_combTag100.SetCurSel(nTagValue);
	if (m_nRollBoardType != nTagValue)
	{
		m_nRollBoardType = nTagValue;
		bool bIsAutoRoll = m_nRollBoardType > 1 ? true : false;
		PostMessageA(GetParent()->GetSafeHwnd(), WM_UPDATE_ROLL_BOARD, bIsAutoRoll, 0);
		/*PostMessage()*/
	}

	//	翻版选择
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_101, nTagValue);
	m_combTag101.SetCurSel(nTagValue);
	
	//	有无有板感应器
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_102, nTagValue);
	m_combTag102.SetCurSel(nTagValue);

	//	有无气缸磁性开关
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_103, nTagValue);
	m_combTag103.SetCurSel(nTagValue);

	//	平台边沿附加检测
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_104, nTagValue);
	m_combTag104.SetCurSel(nTagValue);


	//	平台传输电机类型
	int nValue105 = 0;
	m_pAnalyzeNetwork->GetIndexValueByTag(EM_PRO_TAG_105, nTagValue);
	nValue105 = nTagValue & 0x00000001;
	m_combTag105.SetCurSel(nValue105);

	//	AB相关系
	nValue105 = nTagValue>>1 & 0x00000001;
	m_combTag105_1.SetCurSel(nValue105);

	////	上流出板感应检测
	//if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_106, strValue))
	//	GetDlgItem(IDC_EDIT_TAG_106)->SetWindowText(strValue);

	////	出板完成判定附加选项1
	//if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_107, strValue))
	//	GetDlgItem(IDC_EDIT_TAG_107)->SetWindowText(strValue);

	//	出板完成判定附加选项2
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_108, strValue))
		GetDlgItem(IDC_EDIT_TAG_108)->SetWindowText(strValue);

	//	进板外沿信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_109, strValue))
		GetDlgItem(IDC_EDIT_TAG_109)->SetWindowText(strValue);

	//	进板外沿信号有效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_111, strValue))
		GetDlgItem(IDC_EDIT_TAG_111)->SetWindowText(strValue);

	//	进板外沿信号失效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_113, strValue))
		GetDlgItem(IDC_EDIT_TAG_113)->SetWindowText(strValue);

	//	进板外沿信号失效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_115, strValue))
		GetDlgItem(IDC_EDIT_TAG_115)->SetWindowText(strValue);

	//	进板内沿信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_117, strValue))
		GetDlgItem(IDC_EDIT_TAG_117)->SetWindowText(strValue);

	//	进板内沿信号有效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_119, strValue))
		GetDlgItem(IDC_EDIT_TAG_119)->SetWindowText(strValue);

	//	进板内沿信号失效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_121, strValue))
		GetDlgItem(IDC_EDIT_TAG_121)->SetWindowText(strValue);

	//	进板内沿信号失效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_123, strValue))
		GetDlgItem(IDC_EDIT_TAG_123)->SetWindowText(strValue);

	//	出板外沿信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_125, strValue))
		GetDlgItem(IDC_EDIT_TAG_125)->SetWindowText(strValue);

	//	出板外沿信号有效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_127, strValue))
		GetDlgItem(IDC_EDIT_TAG_127)->SetWindowText(strValue);

	//	出板外沿信号失效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_129, strValue))
		GetDlgItem(IDC_EDIT_TAG_129)->SetWindowText(strValue);

	//	出板外沿信号失效距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_131, strValue))
		GetDlgItem(IDC_EDIT_TAG_131)->SetWindowText(strValue);

	//	请板信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_133, strValue))
		GetDlgItem(IDC_EDIT_TAG_133)->SetWindowText(strValue);

	//	请板信号失效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_135, strValue))
		GetDlgItem(IDC_EDIT_TAG_135)->SetWindowText(strValue);

	//	进板中间信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_137, strValue))
		GetDlgItem(IDC_EDIT_TAG_137)->SetWindowText(strValue);

	//	出板中间信号有效延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_139, strValue))
		GetDlgItem(IDC_EDIT_TAG_139)->SetWindowText(strValue);

	//	报警/门禁信号有效延迟
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_141, strValue))
		GetDlgItem(IDC_EDIT_TAG_141_1)->SetWindowText(strValue);

	//	挡板气缸伸出判定延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_143, strValue))
		GetDlgItem(IDC_EDIT_TAG_143)->SetWindowText(strValue);

	//	挡板气缸收回判定延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_145, strValue))
		GetDlgItem(IDC_EDIT_TAG_145)->SetWindowText(strValue);

	//	入板到位后传输延迟1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_147, strValue))
		GetDlgItem(IDC_EDIT_TAG_147)->SetWindowText(strValue);

	//	入板到位后传输距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_149, strValue))
		GetDlgItem(IDC_EDIT_TAG_149)->SetWindowText(strValue);

	//	进板快速持续的距离1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_151, strValue))
		GetDlgItem(IDC_EDIT_TAG_151)->SetWindowText(strValue);

	//	翻转中开始关挡板角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_153, strValue))
		GetDlgItem(IDC_EDIT_TAG_153)->SetWindowText(strValue);

	//	快速翻转角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_155, strValue))
		GetDlgItem(IDC_EDIT_TAG_155)->SetWindowText(strValue);

	//	旋转中挡板检测角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_159, strValue))
		GetDlgItem(IDC_EDIT_TAG_159)->SetWindowText(strValue);

	//	传输初始速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_161, strValue))
		GetDlgItem(IDC_EDIT_TAG_161)->SetWindowText(strValue);

	//	传输快速1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_163, strValue))
		GetDlgItem(IDC_EDIT_TAG_163)->SetWindowText(strValue);

	//	传输慢速1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_165, strValue))
		GetDlgItem(IDC_EDIT_TAG_165)->SetWindowText(strValue);

	//	准备出板传输速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_167, strValue))
		GetDlgItem(IDC_EDIT_TAG_167)->SetWindowText(strValue);

	//	出板/手动传输速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_169, strValue))
		GetDlgItem(IDC_EDIT_TAG_169)->SetWindowText(strValue);

	//	传输加速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_171, strValue))
		GetDlgItem(IDC_EDIT_TAG_171)->SetWindowText(strValue);

	//	旋转初始速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_173, strValue))
		GetDlgItem(IDC_EDIT_TAG_173)->SetWindowText(strValue);

	//	旋转快速1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_175, strValue))
		GetDlgItem(IDC_EDIT_TAG_175)->SetWindowText(strValue);

	//	旋转慢速1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_177, strValue))
		GetDlgItem(IDC_EDIT_TAG_177)->SetWindowText(strValue);

	//	旋转水平速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_179, strValue))
		GetDlgItem(IDC_EDIT_TAG_179)->SetWindowText(strValue);

	//	回零/手动旋转速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_181, strValue))
		GetDlgItem(IDC_EDIT_TAG_181)->SetWindowText(strValue);

	//	旋转加速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_183, strValue))
		GetDlgItem(IDC_EDIT_TAG_183)->SetWindowText(strValue);

	// 马达最大传输速度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_216, strValue))
		GetDlgItem(IDC_EDIT_TAG_216)->SetWindowText(strValue);

	// 马达快速传输时间1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_218, strValue))
		GetDlgItem(IDC_EDIT_TAG_218)->SetWindowText(strValue);

	//	入板超时报警时间
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_189, strValue))
		GetDlgItem(IDC_EDIT_TAG_189)->SetWindowText(strValue);

	//	出板超时报警时间
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_190, strValue))
		GetDlgItem(IDC_EDIT_TAG_190)->SetWindowText(strValue);

	//	水平调整报警时间
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_191, strValue))
		GetDlgItem(IDC_EDIT_TAG_191)->SetWindowText(strValue);

	//	零位旋转停止角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_157, strValue))
		GetDlgItem(IDC_EDIT_TAG_157)->SetWindowText(strValue);

	//	非零旋转停止角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_210, strValue))
		GetDlgItem(IDC_EDIT_TAG_210)->SetWindowText(strValue);

	//	旋转轴静止判定角度1
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_212, strValue))
		GetDlgItem(IDC_EDIT_TAG_212)->SetWindowText(strValue);

	//	旋转轴静止判定时间11
	if (m_pAnalyzeNetwork->GetStrValueValueByTag(EM_PRO_TAG_214, strValue))
		GetDlgItem(IDC_EDIT_TAG_214)->SetWindowText(strValue);

}


void CDialogConfig::SignleAutoRunDisplayIo(bool bIsAuto)
{
	CString strValue;
	// jout5_1
	strValue = bIsAuto ? L"粘尘机速度" : L"出板/手动速度";
	GetDlgItem(IDC_STATIC_169)->SetWindowText(strValue);
}

void CDialogConfig::InitCtrlValue()
{
	// 机型选择
	m_combTag100.ResetContent();
	m_combTag100.AddString(L"从右到左");
	m_combTag100.AddString(L"从左到右");
	m_combTag100.AddString(L"单机;移载机在右");
	m_combTag100.AddString(L"单机:移载机在左");
	m_combTag100.SetCurSel(0);

	// 翻版选择
	m_combTag101.ResetContent();
	m_combTag101.AddString(L"不翻板");
	m_combTag101.AddString(L"正常翻板");
	m_combTag101.AddString(L"单机;右到左翻");
	m_combTag101.AddString(L"单机:左到右翻");
	m_combTag101.SetCurSel(0);

	// 有板感应
	m_combTag102.ResetContent();
	m_combTag102.AddString(L"无");
	m_combTag102.AddString(L"有");
	m_combTag102.SetCurSel(0);
	
	// 气缸磁性开关
	m_combTag103.ResetContent();
	m_combTag103.AddString(L"无");
	m_combTag103.AddString(L"检测伸出缩回");
	m_combTag103.AddString(L"捕捉气缸伸出");
	m_combTag103.SetCurSel(0);

	// 进出附加感应
	m_combTag104.ResetContent();
	m_combTag104.AddString(L"无");
	m_combTag104.AddString(L"有");
	m_combTag104.SetCurSel(0);

	// 传输电机类型
	m_combTag105.ResetContent();
	m_combTag105.AddString(L"伺服电机");
	m_combTag105.AddString(L"调速电机");
	m_combTag105.SetCurSel(0);

	// AB相关系
	m_combTag105_1.ResetContent();
	m_combTag105_1.AddString(L"A超前B");
	m_combTag105_1.AddString(L"B超前A");
	m_combTag105_1.SetCurSel(0);
	
}


void CDialogConfig::LinkTransValueFunc(int nCtrlId, int nToCtrlID)
{
	if(!m_pAnalyzeNetwork)
		return;

	unsigned int nValue = 0;
	CString strValue = L"";
	GetDlgItem(nCtrlId)->GetWindowText(strValue);
	double dEditValue = _ttof(strValue);

	strValue.Format(L"%.1f", dEditValue*60/1000.0);
	((CButton*)GetDlgItem(nToCtrlID))->SetWindowText(strValue);
}

void CDialogConfig::LinkValueDisplay(int nCtrlID, int nDisplayID)
{
	if(!m_pAnalyzeNetwork)
		return;

	unsigned int nValue = 0;
	CString strValue = L"";
	GetDlgItem(nCtrlID)->GetWindowText(strValue);
	double dTagValue = _ttof(strValue);

	double dMin = 90 - dTagValue;
	double dMax = 90 + dTagValue;

	strValue.Format(L"(%.0f, %.0f)", dMin, dMax);
	((CButton*)GetDlgItem(nDisplayID))->SetWindowText(strValue);
}

void CDialogConfig::LinkRotateSpeedUpTime(int nCtrlQuick, int nCtrlInit, int nCtrlSpeedUp)
{
	if(!m_pAnalyzeNetwork)
		return;

	// (旋转快速 - 旋转初始速度)/旋转加速度
	CString strTrans1 = L"";
	CString strTrans2 = L"";
	CString strTrans3 = L"";

	GetDlgItem(nCtrlQuick)->GetWindowText(strTrans1);
	GetDlgItem(nCtrlInit)->GetWindowText(strTrans2);
	GetDlgItem(nCtrlSpeedUp)->GetWindowText(strTrans3);

	double dTagValue1 = _ttof(strTrans1);
	double dTagValue2 = _ttof(strTrans2);
	double dTagValue3 = _ttof(strTrans3);

	if(abs(dTagValue3 - 0) < 1e-5)
	{
		((CButton*)GetDlgItem(IDC_STATIC_TAG_175))->SetWindowText(L"0.00s");
		LinkRotateSpeedupAngle(IDC_EDIT_TAG_173, IDC_EDIT_TAG_175, IDC_STATIC_TAG_175);
		return;
	}
		
	CString strValue;
	double dDisValue = (dTagValue1-dTagValue2)/dTagValue3/1000;
	strValue.Format(L"%.2fs", dDisValue);
	((CButton*)GetDlgItem(IDC_STATIC_TAG_175))->SetWindowText(strValue);


	LinkRotateSpeedupAngle(IDC_EDIT_TAG_173, IDC_EDIT_TAG_175, IDC_STATIC_TAG_175);
}

void CDialogConfig::LinkRotateSlowDownTime(int nCtrlQuick, int nCtrlSlow, int nCtrlSpeedUp)
{
	if(!m_pAnalyzeNetwork)
		return;

	// (旋转快速 - 旋转慢速)/旋转加速度/1000
	CString strTrans1 = L"";
	CString strTrans2 = L"";
	CString strTrans3 = L"";
	GetDlgItem(nCtrlQuick)->GetWindowText(strTrans1);
	GetDlgItem(nCtrlSlow)->GetWindowText(strTrans2);
	GetDlgItem(nCtrlSpeedUp)->GetWindowText(strTrans3);

	double dTagValue1 = _ttof(strTrans1);
	double dTagValue2 = _ttof(strTrans2);
	double dTagValue3 = _ttof(strTrans3);

	if(abs(dTagValue3 - 0) < 1e-5)
	{
		((CButton*)GetDlgItem(IDC_STATIC_TAG_177))->SetWindowText(L"0.00s");
		LinkRotateSlowDownAngle(IDC_EDIT_TAG_155, IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_STATIC_TAG_177);
		return;
	}
		
	CString strValue;
	double dDisValue = (dTagValue1-dTagValue2)/dTagValue3/1000;
	strValue.Format(L"%.2fs", dDisValue);
	((CButton*)GetDlgItem(IDC_STATIC_TAG_177))->SetWindowText(strValue);

	LinkRotateSlowDownAngle(IDC_EDIT_TAG_155, IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_STATIC_TAG_177);
}

void CDialogConfig::LinkZeroAndNoZeroTime(int nCtrlID, int nDisCtrlID)
{
	if(!m_pAnalyzeNetwork)
		return;

	CString strValue;
	GetDlgItem(nCtrlID)->GetWindowText(strValue);
	double dCtrlValue = _ttof(strValue);

	strValue.Format(L"%.2fs", dCtrlValue/200.00);
	((CButton*)GetDlgItem(nDisCtrlID))->SetWindowText(strValue);
}

void CDialogConfig::LinkRotateSpeedupAngle(int nRotateBegin, int nRotateQuick, int nRotateSpeedupTime)
{
	if (!m_pAnalyzeNetwork)
		return;

	// （旋转初始速度+旋转快速）/2 *旋转加速耗时
	CString strTrans1 = L"";
	CString strTrans2 = L"";
	CString strTrans3 = L"";
	GetDlgItem(nRotateBegin)->GetWindowText(strTrans1);
	GetDlgItem(nRotateQuick)->GetWindowText(strTrans2);
	GetDlgItem(nRotateSpeedupTime)->GetWindowText(strTrans3);
	strTrans3.MakeLower();
	strTrans3.Replace(L"s", L"");

	double dTagValue1 = _ttof(strTrans1);
	double dTagValue2 = _ttof(strTrans2);
	double dTagValue3 = _ttof(strTrans3);


	CString strValue;
	double dDisValue = (dTagValue1 + dTagValue2) / 2 * dTagValue3;
	strValue.Format(L"%.2f°", dDisValue);
	((CButton*)GetDlgItem(IDC_STATIC_QUICK_ANGLE))->SetWindowText(strValue);
}

void CDialogConfig::LinkRotateSlowDownAngle(int nQuickAngle, int nRotateQuick, int nRotateSlow, int nRotateSpeedupTime)
{
	if (!m_pAnalyzeNetwork)
		return;

	// 快速翻转角度+（旋转快速+旋转慢速）/2 *旋转减速耗时）
	CString strTrans1 = L"";
	CString strTrans2 = L"";
	CString strTrans3 = L"";
	CString strTrans4 = L"";
	GetDlgItem(nQuickAngle)->GetWindowText(strTrans1);
	GetDlgItem(nRotateQuick)->GetWindowText(strTrans2);
	GetDlgItem(nRotateSlow)->GetWindowText(strTrans3);
	GetDlgItem(nRotateSpeedupTime)->GetWindowText(strTrans4);
	strTrans4.MakeLower();
	strTrans4.Replace(L"s", L"");

	double dTagValue1 = _ttof(strTrans1);
	double dTagValue2 = _ttof(strTrans2);
	double dTagValue3 = _ttof(strTrans3);
	double dTagValue4 = _ttof(strTrans4);

	CString strValue;
	double dDisValue = dTagValue1 + (dTagValue2 + dTagValue3) / 2 * dTagValue4;
	strValue.Format(L"%.2f°", dDisValue);
	((CButton*)GetDlgItem(IDC_STATIC_SLOW_ANGLE))->SetWindowText(strValue);
}

void CDialogConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_TAG_102, m_combTag102);
	DDX_Control(pDX, IDC_COMB_TAG_103, m_combTag103);
	DDX_Control(pDX, IDC_COMB_TAG_104, m_combTag104);
	DDX_Control(pDX, IDC_COMB_105, m_combTag105);
	DDX_Control(pDX, IDC_COMB_TAG_100, m_combTag100);
	DDX_Control(pDX, IDC_COMB_TAG_101, m_combTag101);
	DDX_Control(pDX, IDC_COMB_105_1, m_combTag105_1);
}


BEGIN_MESSAGE_MAP(CDialogConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogConfig::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogConfig::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CDialogConfig::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CDialogConfig::OnBnClickedBtnExport)
	ON_EN_CHANGE(IDC_EDIT_TAG_161, &CDialogConfig::OnEnChangeEditTag161)
	ON_EN_CHANGE(IDC_EDIT_TAG_163, &CDialogConfig::OnEnChangeEditTag163)
	ON_EN_CHANGE(IDC_EDIT_TAG_165, &CDialogConfig::OnEnChangeEditTag165)
	ON_EN_CHANGE(IDC_EDIT_TAG_167, &CDialogConfig::OnEnChangeEditTag167)
	ON_EN_CHANGE(IDC_EDIT_TAG_169, &CDialogConfig::OnEnChangeEditTag169)

	ON_EN_CHANGE(IDC_EDIT_TAG_175, &CDialogConfig::OnEnChangeEditTag175)
	ON_EN_CHANGE(IDC_EDIT_TAG_177, &CDialogConfig::OnEnChangeEditTag177)
	ON_EN_CHANGE(IDC_EDIT_TAG_181, &CDialogConfig::OnEnChangeEditTag181)
	ON_EN_CHANGE(IDC_EDIT_TAG_159, &CDialogConfig::OnEnChangeEditTag159)
	ON_EN_CHANGE(IDC_EDIT_TAG_173, &CDialogConfig::OnEnChangeEditTag173)
	ON_EN_CHANGE(IDC_EDIT_TAG_157, &CDialogConfig::OnEnChangeEditTag157)
	ON_EN_CHANGE(IDC_EDIT_TAG_210, &CDialogConfig::OnEnChangeEditTag210)
	ON_EN_CHANGE(IDC_EDIT_TAG_183, &CDialogConfig::OnEnChangeEditTag183)
	ON_EN_CHANGE(IDC_EDIT_TAG_155, &CDialogConfig::OnEnChangeEditTag155)
	ON_EN_CHANGE(IDC_EDIT_TAG_216, &CDialogConfig::OnEnChangeEditTag216)
END_MESSAGE_MAP()


// CDialogConfig 消息处理程序


void CDialogConfig::OnBnClickedButton1()
{
	//UpdateCtrlValue();

	// 顺序最后一个同步100，主界面判断为100时候，会刷新一次配置界面
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_100, EM_PRO_TAG_191, 0);
}


void CDialogConfig::OnBnClickedButton2()
{
	CString strValue = L"";
	int nValueIndex = 0;

	//	机型方向
	nValueIndex = m_combTag100.GetCurSel();
	if (nValueIndex != -1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_100, nValueIndex);
	}

	//	翻版选择
	m_pAnalyzeNetwork->SetStrValueValueByTag(IDC_EDIT_TAG_101, strValue);
	nValueIndex = m_combTag101.GetCurSel();
	if (nValueIndex != -1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_101, nValueIndex);
	}

	//	有无有板感应器
	nValueIndex = m_combTag102.GetCurSel();
	if (nValueIndex != -1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_102, nValueIndex);
	}

	//	有无气缸磁性开关
	nValueIndex = m_combTag103.GetCurSel();
	if (nValueIndex != -1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_103, nValueIndex);
	}

	//	平台边沿附加检测
	nValueIndex = m_combTag104.GetCurSel();
	if (nValueIndex != -1)
	{
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_104, nValueIndex);
	}

	//	平台传输电机类型  AB相关系
	int nValue105 = m_combTag105.GetCurSel();
	int nValue105_1 = m_combTag105_1.GetCurSel();
	if (nValue105 != -1 && nValue105_1 != -1)
	{
		nValueIndex = 0;
		if (nValue105 == 1)
			nValueIndex = 1;
		if (nValue105_1 == 1)
			nValueIndex = nValueIndex | 0x02;
		m_pAnalyzeNetwork->SetIndexValueByTag(EM_PRO_TAG_105, nValueIndex);
	}


	//	出板完成判定附加选项2-----
	GetDlgItem(IDC_EDIT_TAG_108)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_108, strValue);

	//	进板外沿信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_109)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_109, strValue);

	//	进板外沿信号有效距离1
	GetDlgItem(IDC_EDIT_TAG_111)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_111, strValue);

	//	进板外沿信号失效延迟1
	GetDlgItem(IDC_EDIT_TAG_113)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_113, strValue);

	//	进板外沿信号失效距离1
	GetDlgItem(IDC_EDIT_TAG_115)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_115, strValue);

	//	进板内沿信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_117)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_117, strValue);

	//	进板内沿信号有效距离1
	GetDlgItem(IDC_EDIT_TAG_119)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_119, strValue);

	//	进板内沿信号失效延迟1
	GetDlgItem(IDC_EDIT_TAG_121)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_121, strValue);

	//	进板内沿信号失效距离1
	GetDlgItem(IDC_EDIT_TAG_123)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_123, strValue);

	//	出板外沿信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_125)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_125, strValue);

	//	出板外沿信号有效距离1
	GetDlgItem(IDC_EDIT_TAG_127)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_127, strValue);

	//	出板外沿信号失效延迟1
	GetDlgItem(IDC_EDIT_TAG_129)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_129, strValue);

	//	出板外沿信号失效距离1
	GetDlgItem(IDC_EDIT_TAG_131)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_131, strValue);

	//	请板信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_133)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_133, strValue);

	//	请板信号失效延迟1
	GetDlgItem(IDC_EDIT_TAG_135)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_135, strValue);

	//	进板中间信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_137)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_137, strValue);

	//	出板中间信号有效延迟1
	GetDlgItem(IDC_EDIT_TAG_139)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_139, strValue);

	//	报警/门禁信号有效延迟
	GetDlgItem(IDC_EDIT_TAG_141_1)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_141, strValue);

	//	挡板气缸伸出判定延迟1
	GetDlgItem(IDC_EDIT_TAG_143)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_143, strValue);

	//	挡板气缸收回判定延迟1
	GetDlgItem(IDC_EDIT_TAG_145)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_145, strValue);

	//	入板到位后传输延迟1
	GetDlgItem(IDC_EDIT_TAG_147)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_147, strValue);

	//	入板到位后传输距离1
	GetDlgItem(IDC_EDIT_TAG_149)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_149, strValue);

	//	进板快速持续的距离1
	GetDlgItem(IDC_EDIT_TAG_151)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_151, strValue);

	//	翻转中开始关挡板角度1
	GetDlgItem(IDC_EDIT_TAG_153)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_153, strValue);

	//	快速翻转角度1
	GetDlgItem(IDC_EDIT_TAG_155)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_155, strValue);

	//	旋转中挡板检测角度1
	GetDlgItem(IDC_EDIT_TAG_159)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_159, strValue);

	//	传输初始速度1
	GetDlgItem(IDC_EDIT_TAG_161)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_161, strValue);

	//	传输快速1
	GetDlgItem(IDC_EDIT_TAG_163)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_163, strValue);

	//	传输慢速1
	GetDlgItem(IDC_EDIT_TAG_165)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_165, strValue);

	//	准备出板传输速度1
	GetDlgItem(IDC_EDIT_TAG_167)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_167, strValue);

	//	出板/手动传输速度1
	GetDlgItem(IDC_EDIT_TAG_169)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_169, strValue);

	//	传输加速度1
	GetDlgItem(IDC_EDIT_TAG_171)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_171, strValue);

	//	旋转初始速度1
	GetDlgItem(IDC_EDIT_TAG_173)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_173, strValue);

	//	旋转快速1
	GetDlgItem(IDC_EDIT_TAG_175)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_175, strValue);

	//	旋转慢速1
	GetDlgItem(IDC_EDIT_TAG_177)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_177, strValue);

	//	旋转水平速度1
	GetDlgItem(IDC_EDIT_TAG_179)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_179, strValue);

	//	回零/手动旋转速度1
	GetDlgItem(IDC_EDIT_TAG_181)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_181, strValue);

	//	旋转加速度1
	GetDlgItem(IDC_EDIT_TAG_183)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_183, strValue);

	// 马达最大传输速度1
	GetDlgItem(IDC_EDIT_TAG_216)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_216, strValue);

	// 马达快速传输时间1
	GetDlgItem(IDC_EDIT_TAG_218)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_218, strValue);

	//	入板超时报警时间
	GetDlgItem(IDC_EDIT_TAG_189)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_189, strValue);

	//	出板超时报警时间
	GetDlgItem(IDC_EDIT_TAG_190)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_190, strValue);

	//	水平调整报警时间
	GetDlgItem(IDC_EDIT_TAG_191)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_191, strValue);

	//	零位旋转停止角度1
	GetDlgItem(IDC_EDIT_TAG_157)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_157, strValue);

	//	非零旋转停止角度1
	GetDlgItem(IDC_EDIT_TAG_210)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_210, strValue);

	//	旋转轴静止判定角度1
	GetDlgItem(IDC_EDIT_TAG_212)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_212, strValue);

	//	旋转轴静止判定时间1
	GetDlgItem(IDC_EDIT_TAG_214)->GetWindowText(strValue);
	m_pAnalyzeNetwork->SetStrValueValueByTag(EM_PRO_TAG_214, strValue);

	// 同步数据到翻版机主板  
	m_pAnalyzeNetwork->SynchronizeNetworkData(EM_PRO_TAG_100, EM_PRO_TAG_191);
	
}


BOOL CDialogConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrlValue();

	UpdateCtrlValue();

	return TRUE;  	
}



void CDialogConfig::OnBnClickedBtnImport()
{
	CFileDialog dlg(TRUE);
	// 可获取多个文件，取一个
	OPENFILENAME& ofn = dlg.GetOFN();
	ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	//ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	CString strFilename;
	if (dlg.DoModal() == IDOK)
	{

		POSITION fileNamesPosition = dlg.GetStartPosition();
		CString strPath = dlg.GetFolderPath();
		while (fileNamesPosition != NULL)
		{
			// filename 是获取得文件名
			strFilename = dlg.GetNextPathName(fileNamesPosition);
			break;
		}
	}

	if (strFilename.IsEmpty())
	{
		return ;
	}

	bool bRet = m_pAnalyzeNetwork->ImportParam(strFilename);
	if(!bRet)
		MessageBox(L"加载配置失败");  
}


void CDialogConfig::OnBnClickedBtnExport()
{
	// 获取每个控件的历史值
	CString strSaveFileTemp;
	CFolderPickerDialog fd(NULL, 0, this, 0);
	if (fd.DoModal() == IDOK)
	{
		strSaveFileTemp = fd.GetPathName();
	}

	if(strSaveFileTemp.IsEmpty())
		return;
	
	strSaveFileTemp += L"\\ParamConfig";

	// 增加时间戳
	CTime CurrTime = CTime::GetCurrentTime();
	CString strSavePath;
	strSavePath.Format(L"%s_%02d%02d%02d%02d", strSaveFileTemp, CurrTime.GetMonth(), 
			CurrTime.GetDay(), CurrTime.GetHour(), CurrTime.GetMinute());


	CString strMsg = L"导出配置失败";
	bool bRet = m_pAnalyzeNetwork->ExportParam(strSavePath);
	if(bRet)
		strMsg = L"导出配置成功";

	MessageBox(strMsg);

	//WriteConfig(strSaveFilePath.c_str());
	//MessageBox(L"配置保存成功", NULL, MB_OK);

	return ;
}


void CDialogConfig::OnEnChangeEditTag161()
{
	LinkTransValueFunc(IDC_EDIT_TAG_161, IDC_STATIC_TAG_161);
}


void CDialogConfig::OnEnChangeEditTag163()
{
	LinkTransValueFunc(IDC_EDIT_TAG_163, IDC_STATIC_TAG_163);
}


void CDialogConfig::OnEnChangeEditTag165()
{
	LinkTransValueFunc(IDC_EDIT_TAG_165, IDC_STATIC_TAG_165);
}


void CDialogConfig::OnEnChangeEditTag167()
{
	LinkTransValueFunc(IDC_EDIT_TAG_167, IDC_STATIC_TAG_167);
}


void CDialogConfig::OnEnChangeEditTag169()
{
	LinkTransValueFunc(IDC_EDIT_TAG_169, IDC_STATIC_TAG_169);
}


void CDialogConfig::OnEnChangeEditTag175()
{
	LinkRotateSpeedUpTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_173, IDC_EDIT_TAG_183);
	LinkRotateSlowDownTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_EDIT_TAG_183);
}


void CDialogConfig::OnEnChangeEditTag177()
{
	// (旋转快速 - 旋转慢速)/旋转加速度/1000
	LinkRotateSlowDownTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_EDIT_TAG_183);

	LinkRotateSpeedUpTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_173, IDC_EDIT_TAG_183);
}


void CDialogConfig::OnEnChangeEditTag181()
{

}


void CDialogConfig::OnEnChangeEditTag159()
{
	LinkValueDisplay(IDC_EDIT_TAG_159, IDC_STATIC_TAG_159);
}


void CDialogConfig::OnEnChangeEditTag173()
{
	LinkRotateSpeedUpTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_173, IDC_EDIT_TAG_183);
}


void CDialogConfig::OnEnChangeEditTag157()
{

}


void CDialogConfig::OnEnChangeEditTag210()
{

}


void CDialogConfig::OnEnChangeEditTag183()
{
	LinkRotateSpeedUpTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_173, IDC_EDIT_TAG_183);
	LinkRotateSlowDownTime(IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_EDIT_TAG_183);
}


void CDialogConfig::OnEnChangeEditTag155()
{
	LinkRotateSlowDownAngle(IDC_EDIT_TAG_155, IDC_EDIT_TAG_175, IDC_EDIT_TAG_177, IDC_STATIC_TAG_175);
}


void CDialogConfig::OnEnChangeEditTag216()
{
	LinkTransValueFunc(IDC_EDIT_TAG_216, IDC_STATIC_TAG_216);
}
