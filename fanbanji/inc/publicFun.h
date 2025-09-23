#ifndef _PUBLIC_FUN_H_
#define _PUBLIC_FUN_H_
#include <afxmt.h>
#include <queue>
#include <string>
#include "crc.h"
#include "log.h"
#include "pubStruct.h"
#include "analyzeCmd.h"
#include "serialport.h"



// 公用函数
void Hex2Str(unsigned char *pRead, unsigned char **pWrite, int nLen);
int  Str2Hex(unsigned char *pRead, unsigned char *pWrite, int nCount);
u8   CalcCrc8(u8* pAddr, int nDataLen);

void DEBUG_LOG(EM_LogLevel emLv, const char* pFormat, ...);
void DEBUG_HEX(EM_LogLevel emLv, char *pVarName,char *pBuffer,int Len);
void SetLogFlag(bool bIsWrite);



// 公用类
// 数据队列
class CPutSerialData
{
public:
	CPutSerialData();
	~CPutSerialData();

	STComData PopSerialData();
	void PushSerialData(STComData stComData);

private:
	std::queue<STComData>	m_queueRevData;

};

static CCriticalSection     s_CriticalSectionByNetWork;   // 临界区
static CCriticalSection     s_CriticalSection;          // 临界区
class CAutoCriticalSection
{
public:
	CAutoCriticalSection(CCriticalSection *p_pCS);
	~CAutoCriticalSection();

private:
	CCriticalSection *m_pCS;
};



#endif
