#ifndef _ANALYZE_CMD_H_
#define _ANALYZE_CMD_H_

#include <map>
#include <vector>
#include <string>
#include "publicFun.h"



enum EM_Protocol_Tag
{
	EM_SHAKE_HANDS			= 0x01,		// ����
	EM_QUERY_VERSION		= 0x02,		// ��ѯ�汾
	EM_QUERY_INPUT			= 0x03,		// ��ѯIO����״̬
	EM_QUERY_OUTPUT			= 0x05,		// ��ѯIO���״̬
	EM_QUERY_IO_STATUS		= 0x06,		// ��ѯ�ŷ�IO״̬
	EM_QUERY_WORK_STATUS	= 0x07,		// ��ѯ����״̬
	EM_WRITE_ROLL_SPEED		= 0x91,		// д����/�������ٶ�
	EM_QUERY_ROLL_SPEED		= 0x92,		// ��ȡ��/�������ٶ�
	EM_WRITE_FLIP_SPEED		= 0x93,		// д�뷭ת�ٶ�
	EM_QUERY_FLIP_SPEED		= 0x94,		// ��ȡ��ת�ٶ�
	EM_WRITE_PULSES_COUNT			= 0x95,		// д��ذ�������
	EM_QUERY_PULSES_COUNT			= 0x96,		// ��ȡ�ذ�������
	EM_WRITE_ACTION_TIME			= 0x97,		// д�������ʱ��
	EM_QUERY_ACTION_TIME			= 0x98,		// ��ȡ������ʱ��
	EM_WRITE_COMPLETE_SIGNAL_DELAY	= 0x99,		// д����忪ʼ/��������ź���ʱ
	EM_QUERY_COMPLETE_SIGNAL_DELAY	= 0x9A,		// ��ȡ��忪ʼ/��������ź���ʱ

	EM_QUERY_LAST_TIME_CONSUMING    = 0x21,		// ��ȡ�ϴη����ʱ
	EM_QUERY_ALARM_NUM				= 0x22,		// ��ȡ��������
	EM_QUERY_ALARM_LOG				= 0x23,		// ��ȡ������¼
	EM_WRITE_FANBAN_TYPE			= 0x31,		// ��ȡ���������
	EM_QUERY_FANBAN_TYPE			= 0x32,		// ��ȡ���������
	EM_WRITE_INDUCTOR_POSITION		= 0x33,		// д�����������Ӧ��λ��
	EM_QUERY_INDUCTOR_POSITION		= 0x34,		// ��ȡ���������Ӧ��λ��
	EM_WRITE_CYLINDER_SENSOR		= 0x35,		// д�����׸�Ӧ������
	EM_QUERY_CYLINDER_SENSOR		= 0x36,		// ��ȡ���׸�Ӧ������
	EM_WRITE_360MACHINE_DIRETION	= 0X37,		// д��360����ת���͵���ת����		
	EM_QUERY_360MACHINE_DIRETION    = 0x38,		// ��ȡ360����ת���͵���ת����		
	EM_WRITE_SIGNAL_DELAY			= 0x51,		// д���������ź�ʧЧ�ӳ�
	EM_QUERY_SIGNAL_DELAY			= 0x52,		// ��ȡ�������ź�ʧЧ�ӳ�
	EM_WRITE_PRESS_TIME				= 0x53,		// д��ذ���ɵ����׿�ʼ��ѹʱ��
	EM_QUERY_PRESS_TIME				= 0x54,		// ��ȡ�ذ���ɵ����׿�ʼ��ѹʱ��
	EM_WRITE_SLOW_FLIP_ANGLE		= 0x55,		// д�����ٷ�ת�ĽǶ�
	EM_QUERY_SLOW_FLIP_ANGLE		= 0x56,		// ��ȡ���ٷ�ת�ĽǶ�
	EM_WRITE_TOUCH_SENSOR_ANGLE		= 0x57,		// д�봥����ת��λ��Ӧ���ĽǶ�
	EM_QUERY_TOUCH_SENSOR_ANGLE		= 0x58,		// ��ȡ�������浽λ��Ӧ���ĽǶ�
	EM_WRITE_FAILED_JUDGMENT_ANGLE  = 0x59,		// д�뷭ת��λʧ�ܵ��ж��Ƕ�
	EM_QUERY_FAILED_JUDGMENT_ANGLE  = 0x5A,		// ��ȡ��ת��λʧ�ܵ��ж��Ƕ�
	EM_WRITE_PULSE_DISTANCE			= 0x5B,		// д�����ִ�������ת�������
	EM_QUERY_PULSE_DISTANCE			= 0x5C,		// ��ȡ���ִ�������ת�������
	EM_WRITE_ROLLER_MAX_SPEED		= 0x61,		// д����ִ���ĳ�ʼ������ٶ�
	EM_QUERY_ROLLER_MAX_SPEED		= 0x62,		// ��ȡ���ִ���ĳ�ʼ������ٶ�
	EM_WRITE_PLATFORM_MAX_SPEED     = 0x63,		// д��ƽ̨��ת�ĳ�ʼ������ٶ�
	EM_QUERY_PLATFORM_MAX_SPEED     = 0x64,		// ��ȡƽ̨��ת�ĳ�ʼ������ٶ�
	EM_WRITE_ACCELERATION_DISTANCE   = 0x65,		// д�봫�䡢��ת�ļ��ٲ���
	EM_QUERY_ACCELERATION_DISTANCE   = 0x66,		// ��ȡ���䡢��ת�ļ��ٲ���
//

};

class CAnalyzeProtocol
{
public:
	CAnalyzeProtocol();
	~CAnalyzeProtocol();

	bool PackStrBuffer(const char*pParam, int nParamLen, char* pRetBuffer);							// ʮ�������ַ���ʹ��
	int  PackHexBuffer(char chTag, const u8*pParam, int nParamLen, u8* pRetBuffer);					// ʮ����������ʹ�ú���
	bool CheckRevCmd(const STComData& stComData);

	bool CheckParmaRange(char chTag, int nParam1);

	void InitProtocolVec();
	void GetProtocolVec(std::vector<STComData> &vecProtocol);
	int GetProtocolLen(unsigned char chTag, bool bIsSend = true);
	CString GetWorkStatus(int nIndex, bool bIsError = false);		// ��ȡ����״̬��bIsErrorΪ�Ƿ�Ϊ����״̬
	CString GetError(unsigned char chErrorValue);						// ���Ĵ��󷵻�
private:
	void InitProLen();
	void InitParamRange();
	// ��������chCrc8����
	void CalcProtocolCrc(STProtocol& stProtocol);
	void PackData(STProtocol &stProtocol, unsigned char* pOutBuf);
	bool ExamineCRC(u8* pParam, unsigned int nProDataLen);
private:
	std::vector<STComData>					m_vecProtocol;					// �ɶ�ȡ����Ҫ���ⲿ�޸�
	std::map<char, STProDataLen>	m_mapSendRevLen;				// �ذ�����
	std::map<char, STParamRange>	m_mapParamRange;				// ������Χ
	
};

#endif
