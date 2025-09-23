#include "analyzeByNetwork.h"
#include "..\inc\publicFun.h"
#include <iostream>
#include <fstream>
#include <ctime>


#define  PRO_DATA_LEN	50



Alarm_Detail g_AlarmDetail[] = {
	{0x1, "急停", "急停按钮按下"},
	{0x2, "传输驱动器告警", "传输驱动器报警IO指示异常，电源按钮重启恢复"},
	{0x3, "旋转驱动器告警", "旋转驱动器报警IO指示异常，电源按钮重启恢复"},
	{0x4, "传输轴反馈异常", "未检测到有效传输轴反馈，检查驱动器参数，传输轴DB插头，控制板硬件"},
	{0x5, "旋转轴反馈异常", "未检测到有效旋转轴反馈，检查驱动器参数，旋转轴DB插头，控制板硬件"},
	{0x6, "急停按钮下压时按复位", "先把急停按钮松开，再按复位按钮"},
	{0x7, "电源开关按钮松开", "电源开关按钮松开后，驱动器掉电"},
	{0x11, "气缸1缩回不到位", "没到磁性开关缩回位置（平台零位下的左侧气缸）"},
	{0x12, "气缸1伸出不到位", "没到磁性开关到位位置（平台零位下的左侧气缸）"},
	{0x13, "气缸2缩回不到位", "没到磁性开关缩回位置（平台零位下的右侧气缸）"},
	{0x14, "气缸2伸出不到位", "没到磁性开关到位位置（平台零位下的右侧气缸）"},
	{0x15, "底部挡板脱离位置", "旋转中检测到，底部挡板的到位磁性开关没有保持有效"},
	{0x16, "到位挡板未及关闭", "进板到开始减速时，挡板气缸依然没有下压到位，需调大气压"},
	{0x23, "到位检测有板异常1", "在到位挡板有效关闭时刻，平台零位下的到位处感应器就已经有效，需避免该到位感应器误感应"},
	{0x24, "到位检测有板异常2", "在到位挡板有效关闭时刻，平台非零位下的到位处感应器就已经有效，需避免该到位感应器误感应"},
	{0x25, "入口有板传输超时", "因入口感应器一直感应有板，导致进板传输超时"},
	{0x26, "到位无效传输超时", "因到位感应器不能保持有效，导致进板传输超时"},
	{0x27, "入板传输超距离", "当调试参数中配置两项：不到位判定：1使能，不到位判定动作：0 时，产生该报警，改设任意项即屏蔽"},
	{0x28, "入板信号未消失", "在配置不到位判定使能，要求进板信号消失后，传输超距离后检测到入板信号未消失，产生该报警"},
	{0x29, "加速进板后入口仍有板", "加速进板下超时，检测到入口处仍有板"},
	{0x2A, "加速进板后板仍未到位", "加速进板下超时，检测到板仍没有到位"},
	{0x31, "旋转超范围（220°）", "旋转中因未触碰感应器，导致超范围，（可能感应器问题）"},
	{0x32, "旋转动作超时", "旋转动作超过指定运行时间（可能驱动器参数，或控制板硬件问题）"},
	{0x33, "旋转超时未启动", "开始旋转一段时间后，未离开两感应区域（可能反馈，控制板硬件问题，或感应器问题）"},
	{0x34, "旋转超出感应位", "旋转因过冲，脱离了两感应器区域"},
	{0x35, "平台脱离感应位", "旋转水平后，因抖动或结构原因，脱离了两感应器区域"},
	{0x36, "旋转两次未经零点", "零点判定感应器异常导致"},
	{0x37, "旋转时进口处有板", "翻板机在旋转时，检测到移栽机出板感应器有效，产生该报警"},
	{0x38, "平台调平超时", "因抖动或结构原因，平台脱离两感应器水平位置，自动调平时发生超时（加大调平时间，或者设0屏蔽）"},
	{0x40, "进板超时0", "在加速入板传输时，入板总时间超时"},
	{0x41, "进板超时1", "在快速入板传输时，入板总时间超时"},
	{0x42, "进板超时2", "在慢速入板传输时，入板总时间超时"},
	{0x43, "出板超时1", "因出板感应器不消失，导致出板超时"},
	{0x44, "出板超时2", "因下流请板信号一直有效，导致出板超时"},
	{0x45, "出板超时3", "因出板时传输距离，未达到入板距离的倍数，导致超时"},
	{0x51, "回零检测板边到位错误1", "回零阶段1，板传输撞到挡板后弹回，导致检测失败。需将传输初始速度降低"},
	{0x52, "回零检测板边到位错误2", "回零阶段2，板传输撞到挡板后弹回，导致检测失败。需将传输初始速度降低"},
	{0x53, "回零检测板边到位错误3", "回零阶段3，板传输撞到挡板后弹回，导致检测失败。需将传输初始速度降低"},
	{0x54, "回零前检测到两边有板", "两边感应器都检测到有板，这时回零会直接报错"},
	{0x55, "回零传输检测板边超距离1", "回零时，将板往出板侧传输时，超过距离未到板边"},
	{0x56, "回零传输检测板边超距离2", "回零时，将板往出板侧传输时，超过时间未到板边"},
	{0x57, "回零传输检测板边超时1", "回零时，将板往入板侧传输时，超过距离未到板边"},
	{0x58, "回零传输检测板边超时2", "回零时，将板往入板侧传输时，超过时间未到板边"},
	{0x59, "回零入板纠正失败1", "回零时平台倾斜，导致传输带不动板子，板边感应器1始终感应到板，纠正失败"},
	{0x5A, "回零入板纠正失败2", "回零时平台倾斜，导致传输带不动板子，板边感应器2始终感应到板，纠正失败"},
	{0x5B, "上电时回零检测到有板", "上电初始状态下，无法判断平台里面板的AB面，这时回零会报错"},

	{0x61, "加载保存数据失败", "上电读取外部FLASH数据失败，恢复为默认配置，需排查硬件故障。"},
	{0x62, "IO扩展芯片检测失败", "上电未检测到IO扩展芯片，需确认板硬件和相关配置，是否用到扩展IO口"},
	{0x63, "扩展IO读取失败", "未有效轮询到IO扩展输入口，检查板硬件和配置"},
	{0x64, "扩展IO写入失败", "IO扩展输出未有效执行，检查板硬件和配置"},
	{0x71, "两方向信号有效", "在向移栽机请板时，移栽机同时给出了从左到右，从右到左两信号。（单机自动化）"},
	{0x72, "方向无效时进板", "移栽机未给出从左到右，从右到左信号，但进板感应器检测到有板（单机自动化）"},
};




CAnalyzeNetwork::CAnalyzeNetwork()
{
	m_nRefreshTime = 100;
	m_bOnTimeExitFlag = false;
	m_hHandleParent = NULL;
	m_hThreadOnTimeUpdate = NULL;
	memset(m_zTagValueBuf, 0, MAX_TAG_LEN);
	memset(m_zAlarmValueBuf, 0, MAX_ALARM_LEN);
	
	m_mapUintTrans.clear();
	m_mapWorkStatusStr.clear();
	m_mapAlarmDetail.clear();
	m_mapTagValueLen.clear();
	InitValueUint();
	InitTagIndexValueMap();
	InitAlarmDetailMap();
	InitWorkStatusStr();

}


CAnalyzeNetwork::~CAnalyzeNetwork()
{
	m_bOnTimeExitFlag = true;
	Sleep(50);
	m_hThreadOnTimeUpdate = NULL;
}

void CAnalyzeNetwork::StopUpdateThread()
{
	if (NULL == m_hThreadOnTimeUpdate)
		return;

	m_bOnTimeExitFlag = true;

	int nCycleTime = 3000;
	DWORD timeSt = 0;
	timeSt = GetTickCount();
	while (NULL != m_hThreadOnTimeUpdate)
	{
		if (GetTickCount() - timeSt < nCycleTime)
		{
			Sleep(20);
			continue;
		}
		else
		{
			DWORD dwCode = 0;
			GetExitCodeThread(m_hThreadOnTimeUpdate, &dwCode);
			if (STILL_ACTIVE == dwCode)
			{
				TerminateThread(m_hThreadOnTimeUpdate, 0);
			}
			m_hThreadOnTimeUpdate = NULL;
		}
	}
}


bool CAnalyzeNetwork::InitConect(char* pAddress, char* pPort, int nRefresh)
{
	m_nRefreshTime = nRefresh;
	if(m_nRefreshTime < 100 || m_nRefreshTime > 5000)
		m_nRefreshTime = 100;

	// 暂停刷新定时器
	StopUpdateThread();

	m_clientSocket.RegisterNotify(this);
	if(m_clientSocket.InitSocket(pAddress, pPort))
	{
		// 第一次连接成功，获取全部数据
		STSendDataItem stNormalItem;
		GetRequstOntimePack(stNormalItem, EM_ONTIME_NORMAL);
		m_clientSocket.SendRequestData(stNormalItem);

		// 设置时间
		GetRequstOntimePack(stNormalItem, EM_GET_TIME_PACK);
		m_clientSocket.SendRequestData(stNormalItem);

		// 定时获取数据。
		m_bOnTimeExitFlag = false;
		m_hThreadOnTimeUpdate = (void*)_beginthread(OnTimeUpdateValue, 0, this);
		SetThreadPriority(m_hThreadOnTimeUpdate, THREAD_PRIORITY_BELOW_NORMAL);

		return true;
	}
	return false;
}


bool CAnalyzeNetwork::GetConnectStatus()
{
	return  m_clientSocket.GetConnectStatus();
}

void CAnalyzeNetwork::RequestRetMsg()
{

	STRevDataItem stDataItem;
	if(!m_clientSocket.PopRevData(stDataItem))
		return;
	
	if(stDataItem.bRcvSuccessFlag && stDataItem.nTagReadOrWrite == 0x01)
	{
		int nCpyCount = stDataItem.nTagEnd - stDataItem.nTagStart + 1;
		// 查看是否为告警的报文
		if(stDataItem.nTagStart >= EM_PRO_ALARM_START)
		{
			int nStartIndex = stDataItem.nTagStart - EM_PRO_ALARM_START;
			memcpy(m_zAlarmValueBuf + nStartIndex, stDataItem.zRevBuf, nCpyCount);
		}

		if(stDataItem.nTagEnd < EM_PRO_TAG_DATA_END)
		{
			int nStartIndex = stDataItem.nTagStart - EM_PRO_TAG_000;
			memcpy(m_zTagValueBuf + nStartIndex, stDataItem.zRevBuf, nCpyCount);
		}
	}

	// 通知父窗口提取数据
	if(m_hHandleParent)
	{
		STRevDataItem* pstDataItem = new STRevDataItem;
		*pstDataItem = stDataItem;
		PostMessage(m_hHandleParent, WM_REV_UPDATE, (WPARAM)pstDataItem, 0);
	}
	
}

int CAnalyzeNetwork::GetSingleTagNeedLength(int nTagValue)
{
	int nRet = -1;
	switch (nTagValue)
	{
	case	EM_PRO_TAG_000:
	case	EM_PRO_TAG_001:
	case	EM_PRO_TAG_002:
	case	EM_PRO_TAG_003:
	case	EM_PRO_TAG_004:
	case	EM_PRO_TAG_007:
	case	EM_PRO_TAG_008:
	case	EM_PRO_TAG_009:
	case	EM_PRO_TAG_010:
	case	EM_PRO_TAG_011:
	case	EM_PRO_TAG_012:
	case	EM_PRO_TAG_013:
	case	EM_PRO_TAG_014:
	case	EM_PRO_TAG_015:
	case	EM_PRO_TAG_016:
	case	EM_PRO_TAG_017:
	case	EM_PRO_TAG_018:
	case	EM_PRO_TAG_019:
	case	EM_PRO_TAG_060:
	case	EM_PRO_TAG_061:
	case	EM_PRO_TAG_062:
	case	EM_PRO_TAG_063:
	case	EM_PRO_TAG_064:
	case	EM_PRO_TAG_100:
	case	EM_PRO_TAG_101:
	case	EM_PRO_TAG_102:
	case	EM_PRO_TAG_103:
	case	EM_PRO_TAG_104:
	case	EM_PRO_TAG_105:
	case	EM_PRO_TAG_106:
	case	EM_PRO_TAG_107:
	case	EM_PRO_TAG_108:
	case	EM_PRO_TAG_185:
	case	EM_PRO_TAG_186:
	case	EM_PRO_TAG_189:
	case	EM_PRO_TAG_190:
	case	EM_PRO_TAG_191:
	case	EM_PRO_TAG_192:
	case	EM_PRO_TAG_193:
	case	EM_PRO_TAG_194:
	case	EM_PRO_TAG_195:
	case	EM_PRO_TAG_196:
	case	EM_PRO_TAG_197:
	case	EM_PRO_TAG_198:
	case	EM_PRO_TAG_199:
	case	EM_PRO_TAG_200:
	case	EM_PRO_TAG_201:
	case	EM_PRO_TAG_202:
	case    EM_PRO_TAG_203:
	case	EM_PRO_TAG_230:
	case	EM_PRO_TAG_231:
	case	EM_PRO_TAG_240:
	case	EM_PRO_TAG_245:
	case	EM_PRO_TAG_236:
	case	EM_PRO_TAG_237:
		nRet = 1;
		break;
	case	EM_PRO_TAG_020:
	//case	EM_PRO_TAG_021:
	case	EM_PRO_TAG_022:
	//case	EM_PRO_TAG_023:
	case	EM_PRO_TAG_024:
	//case	EM_PRO_TAG_025:
	case	EM_PRO_TAG_026:
	//case	EM_PRO_TAG_027:
	case	EM_PRO_TAG_028:
	//case	EM_PRO_TAG_029:
	case	EM_PRO_TAG_030:
	//case	EM_PRO_TAG_031:
	case	EM_PRO_TAG_032:
	//case	EM_PRO_TAG_033:
	case	EM_PRO_TAG_038:
	//case	EM_PRO_TAG_039:
	case	EM_PRO_TAG_040:
	//case	EM_PRO_TAG_041:
	case	EM_PRO_TAG_042:
	//case	EM_PRO_TAG_043:
	case	EM_PRO_TAG_044:
	//case	EM_PRO_TAG_045:
	case	EM_PRO_TAG_046:
	//case	EM_PRO_TAG_047:
	case	EM_PRO_TAG_048:
	//case	EM_PRO_TAG_049:
	case	EM_PRO_TAG_050:
	//case	EM_PRO_TAG_051:
	case	EM_PRO_TAG_052:
	//case	EM_PRO_TAG_053:
	case	EM_PRO_TAG_054:
	//case	EM_PRO_TAG_055:
	case	EM_PRO_TAG_056:
	//case	EM_PRO_TAG_057:
	case	EM_PRO_TAG_058:
	//case	EM_PRO_TAG_059:
	//case	EM_PRO_TAG_107:
	//case	EM_PRO_TAG_108:
	case	EM_PRO_TAG_109:
	//case	EM_PRO_TAG_110:
	case	EM_PRO_TAG_111:
	//case	EM_PRO_TAG_112:
	case	EM_PRO_TAG_113:
	//case	EM_PRO_TAG_114:
	case	EM_PRO_TAG_115:
	//case	EM_PRO_TAG_116:
	case	EM_PRO_TAG_117:
	//case	EM_PRO_TAG_118:
	case	EM_PRO_TAG_119:
	//case	EM_PRO_TAG_120:
	case	EM_PRO_TAG_121:
	//case	EM_PRO_TAG_122:
	case	EM_PRO_TAG_123:
	//case	EM_PRO_TAG_124:
	case	EM_PRO_TAG_125:
	//case	EM_PRO_TAG_126:
	case	EM_PRO_TAG_127:
	//case	EM_PRO_TAG_128:
	case	EM_PRO_TAG_129:
	//case	EM_PRO_TAG_130:
	case	EM_PRO_TAG_131:
	//case	EM_PRO_TAG_132:
	case	EM_PRO_TAG_133:
	//case	EM_PRO_TAG_134:
	case	EM_PRO_TAG_135:
	//case	EM_PRO_TAG_136:
	case	EM_PRO_TAG_137:
	//case	EM_PRO_TAG_138:
	case	EM_PRO_TAG_139:
	//case	EM_PRO_TAG_140:
	case	EM_PRO_TAG_141:
	//case	EM_PRO_TAG_142:
	case	EM_PRO_TAG_143:
	//case	EM_PRO_TAG_144:
	case	EM_PRO_TAG_145:
	//case	EM_PRO_TAG_146:
	case	EM_PRO_TAG_147:
	//case	EM_PRO_TAG_148:
	case	EM_PRO_TAG_149:
	//case	EM_PRO_TAG_150:
	case	EM_PRO_TAG_151:
	//case	EM_PRO_TAG_152:
	case	EM_PRO_TAG_153:
	//case	EM_PRO_TAG_154:
	case	EM_PRO_TAG_155:
	//case	EM_PRO_TAG_156:
	case	EM_PRO_TAG_157:
	//case	EM_PRO_TAG_158:
	case	EM_PRO_TAG_159:
	//case	EM_PRO_TAG_160:
	case	EM_PRO_TAG_161:
	//case	EM_PRO_TAG_162:
	case	EM_PRO_TAG_163:
	//case	EM_PRO_TAG_164:
	case	EM_PRO_TAG_165:
	//case	EM_PRO_TAG_166:
	case	EM_PRO_TAG_167:
	//case	EM_PRO_TAG_168:
	case	EM_PRO_TAG_169:
	//case	EM_PRO_TAG_170:
	case	EM_PRO_TAG_171:
	//case	EM_PRO_TAG_172:
	case	EM_PRO_TAG_173:
	//case	EM_PRO_TAG_174:
	case	EM_PRO_TAG_175:
	//case	EM_PRO_TAG_176:
	case	EM_PRO_TAG_177:
	//case	EM_PRO_TAG_178:
	case	EM_PRO_TAG_179:
	//case	EM_PRO_TAG_180:
	case	EM_PRO_TAG_181:
	//case	EM_PRO_TAG_182:
	case	EM_PRO_TAG_183:
	//case	EM_PRO_TAG_184:
	case	EM_PRO_TAG_187:
	//case	EM_PRO_TAG_188:
	case	EM_PRO_TAG_204:
	//case	EM_PRO_TAG_204:
	case	EM_PRO_TAG_206:
	//case	EM_PRO_TAG_206:
	case	EM_PRO_TAG_208:
	//case	EM_PRO_TAG_208:
	case	EM_PRO_TAG_210:
	//case	EM_PRO_TAG_211:
	case	EM_PRO_TAG_212:
	//case	EM_PRO_TAG_212:
	case	EM_PRO_TAG_214:
	//case	EM_PRO_TAG_214:
	case	EM_PRO_TAG_216:
	//case	EM_PRO_TAG_216:
	case	EM_PRO_TAG_218:
	//case	EM_PRO_TAG_218:
	case	EM_PRO_TAG_232:
	//case	EM_PRO_TAG_233:
	case	EM_PRO_TAG_234:
	//case	EM_PRO_TAG_235:
	case	EM_PRO_TAG_241:
	//case	EM_PRO_TAG_242:
	case	EM_PRO_TAG_243:
	//case	EM_PRO_TAG_244:
		nRet = 2;
		break;
	default:
		nRet = -1;
		break;
	}

	return nRet;
}


double CAnalyzeNetwork::GetTagUint(int nTagValue)
{
	double nRet = 1.0;
	switch (nTagValue)
	{
		//case	EM_PRO_TAG_022:
		//case	EM_PRO_TAG_024:
		//case	EM_PRO_TAG_026:
		case	EM_PRO_TAG_030:
		case	EM_PRO_TAG_032:
		case	EM_PRO_TAG_111:
		case	EM_PRO_TAG_115:
		case	EM_PRO_TAG_119:
		case	EM_PRO_TAG_123:
		case	EM_PRO_TAG_127:
		case	EM_PRO_TAG_131:
		case	EM_PRO_TAG_149:
		case	EM_PRO_TAG_151:
		case	EM_PRO_TAG_161:
		case	EM_PRO_TAG_163:
		case	EM_PRO_TAG_165:
		case	EM_PRO_TAG_167:
		case	EM_PRO_TAG_169:
		case	EM_PRO_TAG_171:
		case    EM_PRO_TAG_191:
		case	EM_PRO_TAG_216:
			nRet = 10.0;
			break;
		case	EM_PRO_TAG_020:
		case	EM_PRO_TAG_028:
		case	EM_PRO_TAG_153:
		case	EM_PRO_TAG_155:
		case	EM_PRO_TAG_157:
		case	EM_PRO_TAG_204:
		case	EM_PRO_TAG_206:
		case	EM_PRO_TAG_208:
		case	EM_PRO_TAG_210:
		case	EM_PRO_TAG_212:
		case	EM_PRO_TAG_159:
		case	EM_PRO_TAG_173:
		case	EM_PRO_TAG_175:
		case	EM_PRO_TAG_177:
		case	EM_PRO_TAG_179:
		case	EM_PRO_TAG_181:
		case	EM_PRO_TAG_183:
			nRet = 100.0;
			break;
		case	EM_PRO_TAG_038:
		case	EM_PRO_TAG_040:
		case	EM_PRO_TAG_042:
		case	EM_PRO_TAG_044:
		case	EM_PRO_TAG_046:
		case	EM_PRO_TAG_048:
		case	EM_PRO_TAG_050:
		case	EM_PRO_TAG_052:
		case	EM_PRO_TAG_054:
		case	EM_PRO_TAG_056:
		case	EM_PRO_TAG_109:
		case	EM_PRO_TAG_113:
		case	EM_PRO_TAG_117:
		case	EM_PRO_TAG_121:
		case	EM_PRO_TAG_125:
		case	EM_PRO_TAG_129:
		case	EM_PRO_TAG_133:
		case	EM_PRO_TAG_135:
		case	EM_PRO_TAG_137:
		case	EM_PRO_TAG_139:
		case	EM_PRO_TAG_141:
		case	EM_PRO_TAG_143:
		case	EM_PRO_TAG_145:
		case	EM_PRO_TAG_147:
		case	EM_PRO_TAG_214:
			nRet = 1000.0;
			break;	
	}

	return nRet;
}

void CAnalyzeNetwork::OnTimeUpdateValue(LPVOID lpParam)
{
	CAnalyzeNetwork* pThis = (CAnalyzeNetwork*)lpParam;
	ASSERT(NULL != pThis);
	if (NULL == pThis)
	{
		return;
	}
	pThis->OnTimeUpdateValue();

	pThis->m_hThreadOnTimeUpdate = NULL;
}

void CAnalyzeNetwork::OnTimeUpdateValue()
{
	// 读取数据
	int nFixLen = 5;
	int nIndex = 0;
	int nTagStart = EM_PRO_TAG_007;
	int nTagEnd = EM_PRO_TAG_062;
	STSendDataItem stRequestReadData;
	stRequestReadData.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;	//
	stRequestReadData.SendBuf[nIndex++] = 0x01;
	stRequestReadData.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
	stRequestReadData.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
	stRequestReadData.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
	stRequestReadData.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
	stRequestReadData.nSendLen = nIndex;

	int nCycleTime = m_nRefreshTime;
	// 定时读取所有数据
	DWORD timeSt = 0;
	timeSt = GetTickCount();
	while(!m_bOnTimeExitFlag)
	{
		if(GetTickCount()-timeSt < nCycleTime)
		{
			Sleep(20);
			continue;
		}
		timeSt = GetTickCount();

		// 检测连接状态
		if (!m_clientSocket.GetConnectStatus())
		{
			PostMessage(m_hHandleParent, WM_CONNECT_STATUS, 0, 0);
			DEBUG_LOG(EM_LOG_ERROR, "检测到连接中断");
			return;
		}

		m_clientSocket.SendRequestData(stRequestReadData);
	}
}

void CAnalyzeNetwork::GetRequstOntimePack(STSendDataItem& stSendDataItem, EM_ONTIME_TYPE emRequestType)
{
	if(EM_ONTIME_ALARM == emRequestType)
	{
		unsigned int nAlarmNum = 0;
		GetIndexValueByTag(EM_PRO_TAG_010, nAlarmNum);

		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_ALARM_START;
		int nTagEnd = EM_PRO_ALARM_START + nAlarmNum*5;			// 一条报警有5个字节数据
		stSendDataItem.nResposeLen = nTagEnd -  nTagStart + nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
	else if(EM_GET_TIME_PACK == emRequestType)
	{
		CTime CurrTime = CTime::GetCurrentTime();
		int nMonth = CurrTime.GetMonth();
		int nDay = CurrTime.GetDay();
		int nHour = CurrTime.GetHour();
		int nMinu = CurrTime.GetMinute();
		int nSec = CurrTime.GetSecond();

		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_TAG_199;
		int nTagEnd = EM_PRO_TAG_203;
		stSendDataItem.nResposeLen = nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0xAA;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nMonth&0xff;
		stSendDataItem.SendBuf[nIndex++] = nDay&0xff;
		stSendDataItem.SendBuf[nIndex++] = nHour&0xff;
		stSendDataItem.SendBuf[nIndex++] = nMinu&0xff;
		stSendDataItem.SendBuf[nIndex++] = nSec&0xff;
		stSendDataItem.nSendLen = nIndex;
	}
	else
	{
		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_TAG_000;
		int nTagEnd = EM_PRO_TAG_DATA_END - 1;
		stSendDataItem.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
}



bool CAnalyzeNetwork::SetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf)
{
	return true;
}

bool CAnalyzeNetwork::SetIndexValueByTag(int nTag, int& nValue)
{
	char chTagValue;
	int nValueLen = GetSingleTagNeedLength(nTag);
	if (nValueLen < 1 || nValueLen > 2)
		return false;
	
	memcpy(&m_zTagValueBuf[nTag], &nValue, nValueLen);
	return true;
}

bool CAnalyzeNetwork::GetIndexValueByTag(int nTag, unsigned int& nValue)
{
	if (m_mapTagValueLen.count(nTag) < 1)
	{
		return false; 
	}

	int nValueCount = m_mapTagValueLen[nTag];
	if (nValueCount < 0 || nValueCount > 4)	// nValueCount不会超过2，这里用一个整型的大小
		return false;

	// 不会越界
	unsigned int nRetTagValue = 0;
	memcpy(&nRetTagValue, &m_zTagValueBuf[nTag], nValueCount);

	nValue = nRetTagValue;
	return true;
}

bool CAnalyzeNetwork::GetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf)
{
	if (nTagStart + nDataLen > MAX_TAG_LEN)
		return false;

	memcpy(zDataBuf, m_zTagValueBuf+nTagStart, nDataLen);
	return true;
}

bool CAnalyzeNetwork::GetStrValueValueByTag(int nTag, CString& strValue)
{
	unsigned int nRetTagValue = 0;
	if (!GetIndexValueByTag(nTag, nRetTagValue))
		return false;

	double dDisValue = 1.0;
	if (m_mapUintTrans.count(nTag) > 0)
		dDisValue = m_mapUintTrans[nTag];

	CString strFormat = L"%.0f";
	if(abs(dDisValue - 10) < 1e-5)
		strFormat = L"%.1f";
	if(abs(dDisValue - 100) < 1e-5)
		strFormat = L"%.2f";
	if(abs(dDisValue - 1000) < 1e-5)
		strFormat = L"%.3f";

	dDisValue = nRetTagValue / dDisValue;
	strValue.Format(strFormat, dDisValue);
	return true;
}

bool CAnalyzeNetwork::SetStrValueValueByTag(int nTag, CString strValue)
{
	unsigned int nRetTagValue = 0;
	double nTagValue = _ttof(strValue);

	int nSetValue = 1;
	if (m_mapUintTrans.count(nTag) > 0)
		nSetValue = m_mapUintTrans[nTag];

	nSetValue = nSetValue * nTagValue;
	if (!SetIndexValueByTag(nTag, nSetValue))
		return false;
	return true;
}

void CAnalyzeNetwork::SynchronizeAlarm2Local(int nQueryNum)
{
	//unsigned int nAlarmNum = 0;
	//GetIndexValueByTag(EM_PRO_TAG_194, nAlarmNum);
	//int nTagStart = EM_PRO_ALARM_START;
	//int nTagEnd = EM_PRO_ALARM_START + nAlarmNum*5;			// 一条报警有5个字节数据

	if(nQueryNum > 100)
		nQueryNum = 100;
	int nTagStart = EM_PRO_ALARM_START;
	int nTagEnd = EM_PRO_ALARM_START + nQueryNum*5;			// 一条报警有5个字节数据
	SynchronizeNetworkData(nTagStart, nTagEnd - 1, 0);
}

bool CAnalyzeNetwork::GetAlarmInfo(int nGetAlarmNum, std::vector<ST_AlarmItemData>& vecAlarmItem)
{
	if(nGetAlarmNum > 100)
		nGetAlarmNum = 100;

	vecAlarmItem.clear();
	for (int i = 0; i < nGetAlarmNum; ++i)
	{
		ST_AlarmItemData stAlarmItemData;
		m_zAlarmValueBuf[i * 5];
		int  nAlarmID = m_zAlarmValueBuf[i * 5 + 4];
		if (nAlarmID ==0)
			continue;
		stAlarmItemData.nAlarmID = nAlarmID;
		stAlarmItemData.strTime.Format(L"%02d-%02d %02d:%02d", m_zAlarmValueBuf[i * 5],
			m_zAlarmValueBuf[i * 5 + 1], m_zAlarmValueBuf[i * 5 + 2], m_zAlarmValueBuf[i * 5 + 3]);

		if (m_mapAlarmDetail.count(nAlarmID) > 0)
		{
			stAlarmItemData.strAlarmMsg = m_mapAlarmDetail[nAlarmID].zStrAlarmMsg;
			stAlarmItemData.strAlarmDetail = m_mapAlarmDetail[nAlarmID].zStrAlarmDetail;
		}

		vecAlarmItem.push_back(stAlarmItemData);
	}
	return true;
}


bool CAnalyzeNetwork::ImportParam(CString strPath)
{
	// 读取文件
	// 写入文件
	std::ifstream fin(strPath, std::ios_base::in | std::ios_base::binary);
	if(!fin.is_open())
		return false;

	char zTagValueBuf[MAX_TAG_LEN] = {0}; 
	char zReadBuf[50] = {0};

	// 文件大小 有一位是校验位
	int nExpectLen = EM_PRO_TAG_193 - EM_PRO_TAG_100 + 1 + 1;
	fin.seekg(0, fin.end);
	int nBufLen = fin.tellg();
	fin.seekg(0);

	if(nBufLen != nExpectLen || nBufLen >= MAX_TAG_LEN)
	{
		DEBUG_LOG(EM_LOG_ERROR,"配置文件长度不符合 预期=%d, 实际为=%d   ", nExpectLen, nBufLen);
		return false;
	}
	fin.read(zTagValueBuf, nBufLen);
	fin.close();
	
	// 校验校验码
	u8 calcCRC[MAX_TAG_LEN] = {0};
	memcpy(calcCRC, zTagValueBuf, nBufLen);
	u8 crcValue = CalcCrc8(calcCRC, nBufLen);
	if(crcValue != (unsigned char)zTagValueBuf[nBufLen])
	{
		DEBUG_LOG(EM_LOG_ERROR,"参数文件校验码校验失败");
		return false;
	}

	// 复制数据 慎重
	// 不复制校验位
	memcpy(m_zTagValueBuf + EM_PRO_TAG_100, zTagValueBuf, nBufLen - 1);

	// 同步数据到翻板机
	if (!GetConnectStatus())
		return false;

	SynchronizeNetworkData(EM_PRO_TAG_100, EM_PRO_TAG_193);
	return true;
}

bool CAnalyzeNetwork::ExportParam(CString strFilePath)
{
	// 写入写出区间为EM_PRO_TAG_100 - EM_PRO_TAG_DATA_END
	
	char zTagValueBuf[MAX_TAG_LEN] = {0};
	int nDataLen = EM_PRO_TAG_193 - EM_PRO_TAG_100 + 1;
	memcpy(zTagValueBuf, m_zTagValueBuf + EM_PRO_TAG_100, nDataLen);

	// 计算校验码
	u8 calcCRC[MAX_TAG_LEN] = {0};
	memcpy(calcCRC, zTagValueBuf, nDataLen);
	u8 crcValue = CalcCrc8(calcCRC, nDataLen);

	// 
	zTagValueBuf[nDataLen] = crcValue;

	// 写入文件
	std::ofstream fout(strFilePath, std::ios_base::out | std::ios_base::binary);
	if(!fout.is_open())
		return false;

	fout.write(zTagValueBuf, nDataLen + 1);
	fout.close();
	return true;
}

CString CAnalyzeNetwork::GetWorkStatusStr(int nWorkStatus)
{
	if(m_mapWorkStatusStr.count(nWorkStatus) < 1)
		return L"";

	return m_mapWorkStatusStr[nWorkStatus];
}

void CAnalyzeNetwork::SynchronnizationTime()
{
	STSendDataItem stNormalItem;
	GetRequstOntimePack(stNormalItem, EM_GET_TIME_PACK);
	m_clientSocket.SendRequestData(stNormalItem);
}



void CAnalyzeNetwork::SynchronizeNetworkData(int nTagStart, int nTagEnd, int nReadOrWrite)
{
	if (nTagStart > nTagEnd)
		return;

	int nIndex = 0;
	int nFixLen = 5;
	STSendDataItem stSendDataItem;
	if (nReadOrWrite)
	{
		// 写入数据
		stSendDataItem.nResposeLen = nFixLen;	//
		stSendDataItem.SendBuf[nIndex++] = 0xAA;
		stSendDataItem.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
		memcpy(stSendDataItem.SendBuf + nIndex, m_zTagValueBuf + nTagStart, nTagEnd - nTagStart + 1);
		stSendDataItem.nSendLen = nTagEnd - nTagStart + 1 + nIndex;
	}
	else
	{
		// 读取数据
		stSendDataItem.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;	//
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
	
	// 请求
	m_clientSocket.SendRequestData(stSendDataItem);
}

void CAnalyzeNetwork::InitTagIndexValueMap()
{
	m_mapTagValueLen.clear();

	for (int i = EM_PRO_TAG_000; i < EM_PRO_TAG_MAX; i++)
	{
		int nValue = GetSingleTagNeedLength(i);

		m_mapTagValueLen[i] = nValue;
	}
}

void CAnalyzeNetwork::InitAlarmDetailMap()
{
	m_mapAlarmDetail.clear();
	int nDetailNum = sizeof(g_AlarmDetail)/sizeof(Alarm_Detail);
	for (int i = 0; i < nDetailNum; ++i)
	{
		m_mapAlarmDetail[g_AlarmDetail[i].nAlarmID] = g_AlarmDetail[i];
	}
}

void CAnalyzeNetwork::InitWorkStatusStr()
{
	m_mapWorkStatusStr.clear();
	int nIndex  = 0;
	m_mapWorkStatusStr[nIndex++] = L"手动选择";
	m_mapWorkStatusStr[nIndex++] = L"手动传输";
	m_mapWorkStatusStr[nIndex++] = L"手动旋转";
	m_mapWorkStatusStr[nIndex++] = L"上电初始";
	m_mapWorkStatusStr[nIndex++] = L"复位状态";
	m_mapWorkStatusStr[nIndex++] = L"异常状态";
	m_mapWorkStatusStr[nIndex++] = L"停止状态";
	m_mapWorkStatusStr[nIndex++] = L"门开暂停";
	m_mapWorkStatusStr[nIndex++] = L"归零状态";
	m_mapWorkStatusStr[nIndex++] = L"请板状态";
	m_mapWorkStatusStr[nIndex++] = L"入板状态";
	m_mapWorkStatusStr[nIndex++] = L"到位状态";
	m_mapWorkStatusStr[nIndex++] = L"准备出板";
	m_mapWorkStatusStr[nIndex++] = L"出板状态";
	m_mapWorkStatusStr[nIndex++] = L"快速旋转";
	m_mapWorkStatusStr[nIndex++] = L"慢速旋转";
}



void CAnalyzeNetwork::InitValueUint()
{
	m_mapUintTrans.clear();
	for (int i = 0; i < EM_PRO_TAG_DATA_END; ++i)
	{
		int nUint = GetTagUint(i);
		m_mapUintTrans[i] = nUint;
	}
}

void TransBuf2SendFormat(int nSendOrRev, int nTagStart, int nTagEnd, unsigned char* pSendBuf, unsigned char* pOutSendBuf)
{
	int nSendIndex = 0;
	pOutSendBuf[nSendIndex] = 0x01;
	if(nSendOrRev == 0xAA)
		pOutSendBuf[nSendIndex] = 0xAA;
	nSendIndex++;
	pOutSendBuf[nSendIndex++] = nTagStart&0x000000aa;
	pOutSendBuf[nSendIndex++] = (nTagStart>>8)&0x000000aa;
	pOutSendBuf[nSendIndex++] = nTagEnd&0x000000aa;
	pOutSendBuf[nSendIndex++] = (nTagEnd>>8)&0x000000aa;
	memcpy(pOutSendBuf+nSendIndex, pSendBuf, nTagEnd - nTagStart);
}
