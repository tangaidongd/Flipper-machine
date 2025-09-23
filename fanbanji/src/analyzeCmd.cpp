#include "analyzeCmd.h"


#define  PRO_DATA_LEN	50


// 接口定义	效验位初始化时会自动计算，效验值先填充一个默认值
STProtocol g_Protocol[] = {
	{0xAA, EM_SHAKE_HANDS, 4, 4, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_VERSION, 4, 6, EM_TYPE_STATUS, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_INPUT, 4, 6, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_OUTPUT, 4, 6, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_IO_STATUS, 4, 6, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_WORK_STATUS, 4, 7, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_ROLL_SPEED, 10, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ROLL_SPEED, 4, 10, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_FLIP_SPEED, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_FLIP_SPEED, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_PULSES_COUNT, 6, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_PULSES_COUNT, 4, 6, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_ACTION_TIME, 10, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ACTION_TIME, 4, 10, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_COMPLETE_SIGNAL_DELAY, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_COMPLETE_SIGNAL_DELAY, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},


	{0xAA, EM_QUERY_LAST_TIME_CONSUMING, 4, 10, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ALARM_NUM, 4, 5, EM_TYPE_STATUS|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ALARM_LOG,5, 14, EM_TYPE_STATUS, "", 0x01, 0xEE},		// 告警的请求带了参数，回包不能固定长度不做验证
	{0xAA, EM_WRITE_FANBAN_TYPE, 5, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_FANBAN_TYPE, 4, 5, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_INDUCTOR_POSITION, 5, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_INDUCTOR_POSITION, 4, 5, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_CYLINDER_SENSOR, 5, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_CYLINDER_SENSOR, 4, 5, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_360MACHINE_DIRETION, 5, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_360MACHINE_DIRETION, 4, 5, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_SIGNAL_DELAY, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_SIGNAL_DELAY, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_PRESS_TIME, 6, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_PRESS_TIME, 4, 6, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_SLOW_FLIP_ANGLE, 5, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_SLOW_FLIP_ANGLE, 4, 5, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_TOUCH_SENSOR_ANGLE, 6, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_TOUCH_SENSOR_ANGLE, 4, 6, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_FAILED_JUDGMENT_ANGLE, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_FAILED_JUDGMENT_ANGLE, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_PULSE_DISTANCE, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_PULSE_DISTANCE, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_ROLLER_MAX_SPEED, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ROLLER_MAX_SPEED, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_PLATFORM_MAX_SPEED, 8, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_PLATFORM_MAX_SPEED, 4, 8, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},
	{0xAA, EM_WRITE_ACCELERATION_DISTANCE, 6, 4, EM_TYPE_CONTROL|EM_TYPE_WRITE, "", 0x01, 0xEE},
	{0xAA, EM_QUERY_ACCELERATION_DISTANCE, 4, 6, EM_TYPE_CONTROL|EM_TYPE_READ, "", 0x01, 0xEE},

};


STParamRange g_ParamRange[] = {
	{EM_WRITE_ROLL_SPEED,  50, 1},
	{EM_WRITE_FLIP_SPEED,  200, 1},
	{EM_WRITE_PULSES_COUNT,  180, 120},
	{EM_WRITE_ACTION_TIME,  2000, 1},
	{EM_WRITE_COMPLETE_SIGNAL_DELAY,  2000, 1},

	{EM_WRITE_FANBAN_TYPE,  2, 0},
	{EM_WRITE_INDUCTOR_POSITION,  1, 0},
	{EM_WRITE_CYLINDER_SENSOR,  1, 0},
	{EM_WRITE_360MACHINE_DIRETION,  1, 0},
	{EM_WRITE_SIGNAL_DELAY,  2000, 1},
	{EM_WRITE_PRESS_TIME,  2000, 1},
	{EM_WRITE_SLOW_FLIP_ANGLE,  80, 1},
	{EM_WRITE_TOUCH_SENSOR_ANGLE,  20, 0},
	{EM_WRITE_FAILED_JUDGMENT_ANGLE,  100, 0},
	{EM_WRITE_PULSE_DISTANCE,  500, 0},
	{EM_WRITE_ROLLER_MAX_SPEED,  50, 1},
	{EM_WRITE_PLATFORM_MAX_SPEED,  200, 1},
	{EM_WRITE_ACCELERATION_DISTANCE,  10, 0},
};






CAnalyzeProtocol::CAnalyzeProtocol()
{
	// 初始化完整轮询数据，轮询的地方可直接调用
	//InitProtocol();
	m_mapSendRevLen.clear();
	m_mapParamRange.clear();
	InitParamRange();
	InitProLen();
}

CAnalyzeProtocol::~CAnalyzeProtocol()
{

}

bool CAnalyzeProtocol::PackStrBuffer(const char*pParam, int nParamLen, char* pRetBuffer)
{
	u8* pTransStr = (u8*)pParam;
	u8  zCalcRetBuff[PRO_DATA_LEN] = {0};
	Str2Hex(pTransStr, zCalcRetBuff, nParamLen);

	// 校验Crc-8
	if(ExamineCRC(zCalcRetBuff, nParamLen/2 - 3))
	{
		memcpy(pRetBuffer, zCalcRetBuff, nParamLen/2);
		return true;
	}
	return false;
}


int CAnalyzeProtocol::PackHexBuffer(char chTag, const u8*pParam, int nParamLen, u8* pRetBuffer)
{
	int nRetLen = 0;
	if (m_mapSendRevLen.count(chTag) < 1)
	{
		// 没有找到对应的协议
		return nRetLen;
	}

	// 检查数据长度
	if (m_mapSendRevLen[chTag].nSendLen - 4 != nParamLen) 
	{
		return nRetLen;
	}

	int nIndex = 0;
	u8 zSendBuf[PRO_DATA_LEN] = {0};
	zSendBuf[nIndex++] = 0xAA;
	zSendBuf[nIndex++] = chTag;
	memcpy(zSendBuf + nIndex, pParam, nParamLen);
	nIndex += nParamLen;
	if(!ExamineCRC((u8*)zSendBuf, (nIndex++) - 1))		// 数据域去掉一个aa
	{
		MessageBox(NULL, _T("数据长度计算异常"), NULL, MB_OK);
		return nRetLen;
	}
	//zSendBuf[nIndex++] = 0x11;			// CRC效验先随便填，后面替换
	zSendBuf[nIndex++] = 0xEE;

	memcpy(pRetBuffer, zSendBuf, nIndex);
	nRetLen = nIndex;
	return nRetLen;
}

bool CAnalyzeProtocol::CheckRevCmd(const STComData& stComData)
{
	CStringA strOut;

	// 检查数据长度
	if (stComData.nDataLen < 2)
	{
		return false;
	}

	// 是否为异常包
	if(stComData.zData[0] == 0xdd)
	{
		strOut.Format("\r\n%02x  %s \r\n", stComData.chTag, GetError(stComData.zData[1]));
		DEBUG_LOG(EM_LOG_ERROR, strOut);
		return false;
	}

	if (m_mapSendRevLen.count(stComData.chTag) == 0)
	{
		DEBUG_HEX(EM_LOG_ERROR, "没此协议：", (char*)stComData.zData, stComData.nDataLen);
		return false;
	}

	// 检查数据长度,检查长度顺便检查了是否存在协议
	if (stComData.nDataLen < 4 || GetProtocolLen(stComData.chTag, false) != stComData.nDataLen)
	{
		char zTemp[50] = {0};
		sprintf_s(zTemp, "回包长度异常：包长为%d", stComData.nDataLen);
		DEBUG_HEX(EM_LOG_ERROR, zTemp, (char*)stComData.zData, stComData.nDataLen);
		return false;
	}

	if (stComData.zData[0] != 0xaa || stComData.zData[stComData.nDataLen - 1] != 0xee)
	{
		DEBUG_HEX(EM_LOG_ERROR, "异常包：", (char*)stComData.zData, stComData.nDataLen);
		return false;
	}

	// 检查crc校验
	u8 chCrc = CalcCrc8((u8*)stComData.zData + 1, stComData.nDataLen - 3);
	if (chCrc != stComData.zData[stComData.nDataLen - 2])
	{
		DEBUG_HEX(EM_LOG_ERROR, "crc校验失败：", (char*)stComData.zData, stComData.nDataLen);
		return false;
	}

	return true;
}

bool CAnalyzeProtocol::CheckParmaRange(char chTag, int nParam1)
{
	if (m_mapParamRange.count(chTag) > 0)
	{
		if (nParam1 > m_mapParamRange[chTag].nMarxRange || nParam1 < m_mapParamRange[chTag].nMinRange)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool CAnalyzeProtocol::ExamineCRC(u8* pParam, unsigned int nProDataLen)
{
	// 小于4个字符的的可以直接丢弃
	// 协议先固定长度，后期优化从代码获取
	unsigned char chTag = pParam[1];
	if (m_mapSendRevLen.count(chTag) < 1 || (nProDataLen + 3) != m_mapSendRevLen[chTag].nSendLen)
	{
		//MessageBox(NULL, _T("数据长度异常"), NULL, MB_OK);
		return false;
	}

	u8* pAnalyData = pParam;
	int nProSendLen = m_mapSendRevLen[chTag].nSendLen;
	int nCalcLen = nProSendLen - 3;
	
	u8 calcCRC[PRO_DATA_LEN] = {0};
	memcpy(calcCRC, pAnalyData+1, nCalcLen);
	u8 crcValue = CalcCrc8(calcCRC, nCalcLen);
	pAnalyData[nCalcLen + 1] = crcValue;
	return true;
}



void CAnalyzeProtocol::InitProLen()
{
	// 计算效验值，填充命令数据
	m_mapSendRevLen.clear();
	int nCommandNum =  sizeof(g_Protocol)/sizeof(STProtocol);
	for (int i = 0; i < nCommandNum; i++)
	{
		STProtocol protocol =  g_Protocol[i];
		// 拼接数据
		STProDataLen stProLen;
		stProLen.nRevLen = protocol.nRevLen;
		stProLen.nSendLen = protocol.nSendLen;
		m_mapSendRevLen[protocol.chTag] = stProLen;
	}
}

void CAnalyzeProtocol::InitParamRange()
{
	// 计算效验值，填充命令数据
	m_mapParamRange.clear();
	int nParamNum =  sizeof(g_ParamRange)/sizeof(STParamRange);
	for (int i = 0; i < nParamNum; i++)
	{
		m_mapParamRange[g_ParamRange[i].chHead] =  g_ParamRange[i];
	}
}

void CAnalyzeProtocol::CalcProtocolCrc(STProtocol& stProtocol)
{
	u8 szProData[PRO_DATA_LEN];
	memset(szProData, 0, PRO_DATA_LEN);

	int nDataLen = stProtocol.nSendLen - 3;
	szProData[0] = stProtocol.chTag;
	memcpy(szProData+1, stProtocol.zData, nDataLen);

	// 增加一位tag
	u8 crc = CalcCrc8(szProData, nDataLen);

	stProtocol.chCrc8 = crc;
}

void CAnalyzeProtocol::PackData(STProtocol &stProtocol, unsigned char* pOutBuf)
{
	char packBuf[50] = {0};
	int nIndex = 0;
	packBuf[nIndex++] = stProtocol.chHead;
	packBuf[nIndex++] = stProtocol.chTag;
	
	// 数据域
	int nDataLen = strlen(stProtocol.zData);
	memcpy(packBuf + 2, stProtocol.zData, nDataLen);

	nIndex += nDataLen;
	packBuf[nIndex++] = stProtocol.chCrc8;
	packBuf[nIndex++] = stProtocol.chEnd;

	memcpy(pOutBuf, packBuf, nIndex);
}
void CAnalyzeProtocol::InitProtocolVec()
{
	// 计算效验值，填充命令数据
	m_vecProtocol.clear();
	int nCommandNum =  sizeof(g_Protocol)/sizeof(STProtocol);
	for (int i = 0; i < nCommandNum; i++)
	{
		STProtocol protocol =  g_Protocol[i];
		// 写属性的不加入轮询
		if (protocol.nProType & EM_TYPE_WRITE)
		{
			continue;
		}

		CalcProtocolCrc(protocol);
		// 拼接数据
		STComData stComData;
		memset(stComData.zData, 0, sizeof(stComData.zData));
		stComData.chTag = protocol.chTag;
		stComData.nDataLen = protocol.nSendLen;
		stComData.nProtocolType = protocol.nProType;
		PackData(protocol, stComData.zData);
		m_vecProtocol.push_back(stComData);
	}
}

void CAnalyzeProtocol::GetProtocolVec(std::vector<STComData> &vecProtocol)
{
	vecProtocol = m_vecProtocol;
}


int CAnalyzeProtocol::GetProtocolLen(unsigned char chTag, bool bIsSend)
{
	int nRetLen = 0;
	if (m_mapSendRevLen.count(chTag) > 0)
	{
		if (bIsSend)
		{
			nRetLen = m_mapSendRevLen[chTag].nSendLen;
		}
		else
		{
			nRetLen =  m_mapSendRevLen[chTag].nRevLen;
		}
	}

	return nRetLen;
}

CString CAnalyzeProtocol::GetWorkStatus(int nIndex, bool bIsError)
{
	CString strRet;
	if (!bIsError)
	{
		switch(nIndex)
		{
		case 1:
			strRet = _T("初始");
			break;
		case 2:
			strRet = _T("异常状态");
			break;
		case 3:
			strRet = _T("停止状态");
			break;
		case 4:
			strRet = _T("门开暂停状态");
			break;
		case 5:
			strRet = _T("寻位状态");
			break;
		case 6:
			strRet = _T("请板状态");
			break;
		case 7:
			strRet = _T("入板状态");
			break;
		case 8:
			strRet = _T("回板状态");
			break;
		case 9:
			strRet = _T("夹板状态");
			break;
		case 10:
			strRet = _T("逆时旋转状态");
			break;
		case 11:
			strRet = _T("逆时到位状态");
			break;
		case 12:
			strRet = _T("顺时旋转状态");
			break;
		case 13:
			strRet = _T("顺时到位状态");
			break;
		case 14:
			strRet = _T("准备出板状态");
			break;
		case 15:
			strRet = _T("出板状态");
			break;
		case 16:
			strRet = _T("手动选择状态");
			break;
		case 17:
			strRet = _T("手动传输状态");
			break;
		case 18:
			strRet = _T("手动顺时针旋转");
			break;
		case 19:
			strRet = _T("手动逆时针旋转");
			break;
		case 0:
			strRet = _T("无效状态");
			break;
		default:
			break;
		}
	}
	else
	{

		switch(nIndex)
		{
		case 1:
			strRet = _T("急停按下");
			break;
		case 2:
			strRet = _T("板超出居中位置");
			break;
		case 3:
			strRet = _T("旋转触防撞限位");
			break;
		case 4:
			strRet = _T("旋转超软件量程");
			break;
		case 5:
			strRet = _T("入板检测误感应");
			break;
		case 6:
			strRet = _T("出板检测误感应");
			break;
		case 7:
			strRet = _T("有板检测误感应");
			break;
		case 8:
			strRet = _T("夹板气缸未到位");
			break;
		case 9:
			strRet = _T("有板状态下启动");
			break;
		case 10:
			strRet = _T("出板超时");
			break;
		case 11:
			strRet = _T("到位感应器异常");
			break;
		case 12:
			strRet = _T("状态机工作异常");
			break;
		default:
			break;
		}
	}

	return strRet;
}

CString CAnalyzeProtocol::GetError(unsigned char chErrorValue)
{
	CString strRet;
	switch(chErrorValue)
	{
	case 0x11:
		strRet = _T("超时");
		break;
	case 0x12:
		strRet = _T("类型字节有误");
		break;
	case 0x13:
		strRet = _T("结束字节有误");
		break;
	case 0x14:
		strRet = _T("校验0失败");
		break;
	case 0x22:
		strRet = _T("参数写入失败（超量程）");
		break;
	default:
		break;
	}

	return strRet;
}
