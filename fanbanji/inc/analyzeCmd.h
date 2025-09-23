#ifndef _ANALYZE_CMD_H_
#define _ANALYZE_CMD_H_

#include <map>
#include <vector>
#include <string>
#include "publicFun.h"



enum EM_Protocol_Tag
{
	EM_SHAKE_HANDS			= 0x01,		// 握手
	EM_QUERY_VERSION		= 0x02,		// 查询版本
	EM_QUERY_INPUT			= 0x03,		// 查询IO输入状态
	EM_QUERY_OUTPUT			= 0x05,		// 查询IO输出状态
	EM_QUERY_IO_STATUS		= 0x06,		// 查询伺服IO状态
	EM_QUERY_WORK_STATUS	= 0x07,		// 查询工作状态
	EM_WRITE_ROLL_SPEED		= 0x91,		// 写入入/出滚轮速度
	EM_QUERY_ROLL_SPEED		= 0x92,		// 读取入/出滚轮速度
	EM_WRITE_FLIP_SPEED		= 0x93,		// 写入翻转速度
	EM_QUERY_FLIP_SPEED		= 0x94,		// 读取翻转速度
	EM_WRITE_PULSES_COUNT			= 0x95,		// 写入回板脉冲数
	EM_QUERY_PULSES_COUNT			= 0x96,		// 读取回板脉冲数
	EM_WRITE_ACTION_TIME			= 0x97,		// 写入各动作时间
	EM_QUERY_ACTION_TIME			= 0x98,		// 读取各动作时间
	EM_WRITE_COMPLETE_SIGNAL_DELAY	= 0x99,		// 写入入板开始/出板完成信号延时
	EM_QUERY_COMPLETE_SIGNAL_DELAY	= 0x9A,		// 读取入板开始/出板完成信号延时

	EM_QUERY_LAST_TIME_CONSUMING    = 0x21,		// 读取上次翻板耗时
	EM_QUERY_ALARM_NUM				= 0x22,		// 读取报警次数
	EM_QUERY_ALARM_LOG				= 0x23,		// 读取报警记录
	EM_WRITE_FANBAN_TYPE			= 0x31,		// 读取翻板机类型
	EM_QUERY_FANBAN_TYPE			= 0x32,		// 读取翻板机类型
	EM_WRITE_INDUCTOR_POSITION		= 0x33,		// 写入输入输出感应器位置
	EM_QUERY_INDUCTOR_POSITION		= 0x34,		// 读取输入输出感应器位置
	EM_WRITE_CYLINDER_SENSOR		= 0x35,		// 写入气缸感应器有无
	EM_QUERY_CYLINDER_SENSOR		= 0x36,		// 读取气缸感应器有无
	EM_WRITE_360MACHINE_DIRETION	= 0X37,		// 写入360度旋转机型的旋转方向		
	EM_QUERY_360MACHINE_DIRETION    = 0x38,		// 读取360度旋转机型的旋转方向		
	EM_WRITE_SIGNAL_DELAY			= 0x51,		// 写入入板出板信号失效延迟
	EM_QUERY_SIGNAL_DELAY			= 0x52,		// 读取入板出板信号失效延迟
	EM_WRITE_PRESS_TIME				= 0x53,		// 写入回板完成到气缸开始下压时间
	EM_QUERY_PRESS_TIME				= 0x54,		// 读取回板完成到气缸开始下压时间
	EM_WRITE_SLOW_FLIP_ANGLE		= 0x55,		// 写入慢速翻转的角度
	EM_QUERY_SLOW_FLIP_ANGLE		= 0x56,		// 读取慢速翻转的角度
	EM_WRITE_TOUCH_SENSOR_ANGLE		= 0x57,		// 写入触碰翻转到位感应器的角度
	EM_QUERY_TOUCH_SENSOR_ANGLE		= 0x58,		// 读取触碰翻版到位感应器的角度
	EM_WRITE_FAILED_JUDGMENT_ANGLE  = 0x59,		// 写入翻转到位失败的判定角度
	EM_QUERY_FAILED_JUDGMENT_ANGLE  = 0x5A,		// 读取翻转到位失败的判定角度
	EM_WRITE_PULSE_DISTANCE			= 0x5B,		// 写传滚轮传输进板回转脉冲距离
	EM_QUERY_PULSE_DISTANCE			= 0x5C,		// 读取滚轮传输进板回转脉冲距离
	EM_WRITE_ROLLER_MAX_SPEED		= 0x61,		// 写入滚轮传输的初始、最大速度
	EM_QUERY_ROLLER_MAX_SPEED		= 0x62,		// 读取滚轮传输的初始、最大速度
	EM_WRITE_PLATFORM_MAX_SPEED     = 0x63,		// 写入平台翻转的初始，最大速度
	EM_QUERY_PLATFORM_MAX_SPEED     = 0x64,		// 读取平台翻转的初始，最大速度
	EM_WRITE_ACCELERATION_DISTANCE   = 0x65,		// 写入传输、翻转的加速步距
	EM_QUERY_ACCELERATION_DISTANCE   = 0x66,		// 读取传输、翻转的加速步距
//

};

class CAnalyzeProtocol
{
public:
	CAnalyzeProtocol();
	~CAnalyzeProtocol();

	bool PackStrBuffer(const char*pParam, int nParamLen, char* pRetBuffer);							// 十六进制字符串使用
	int  PackHexBuffer(char chTag, const u8*pParam, int nParamLen, u8* pRetBuffer);					// 十六进制数组使用函数
	bool CheckRevCmd(const STComData& stComData);

	bool CheckParmaRange(char chTag, int nParam1);

	void InitProtocolVec();
	void GetProtocolVec(std::vector<STComData> &vecProtocol);
	int GetProtocolLen(unsigned char chTag, bool bIsSend = true);
	CString GetWorkStatus(int nIndex, bool bIsError = false);		// 获取工作状态，bIsError为是否为错误状态
	CString GetError(unsigned char chErrorValue);						// 报文错误返回
private:
	void InitProLen();
	void InitParamRange();
	// 结算结果从chCrc8导出
	void CalcProtocolCrc(STProtocol& stProtocol);
	void PackData(STProtocol &stProtocol, unsigned char* pOutBuf);
	bool ExamineCRC(u8* pParam, unsigned int nProDataLen);
private:
	std::vector<STComData>					m_vecProtocol;					// 可读取，不要在外部修改
	std::map<char, STProDataLen>	m_mapSendRevLen;				// 回包长度
	std::map<char, STParamRange>	m_mapParamRange;				// 参数范围
	
};

#endif
