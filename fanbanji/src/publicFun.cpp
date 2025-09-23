
#include "publicFun.h"
#include <stdio.h>
#include <io.h>
//#include <windows.h>

#define MaxMallocMem 128

bool g_bIsWriteLog = true;

CPutSerialData::CPutSerialData()
{
}

CPutSerialData::~CPutSerialData()
{
}

STComData CPutSerialData::PopSerialData()
{	
	CAutoCriticalSection AutoLock(&s_CriticalSection);
	STComData strSerialData = m_queueRevData.front();  
	m_queueRevData.pop();
	return strSerialData;
}

void CPutSerialData::PushSerialData(STComData strSerialData)
{
	CAutoCriticalSection AutoLock(&s_CriticalSection);
	m_queueRevData.push(strSerialData);

}


// 构造时自动加锁
CAutoCriticalSection::CAutoCriticalSection(CCriticalSection *p_pCS)
{
	m_pCS = p_pCS;
	if (m_pCS != NULL)
		m_pCS->Lock();
}

// 析构时自动解锁
CAutoCriticalSection::~CAutoCriticalSection()
{
	if (m_pCS != NULL)
		m_pCS->Unlock();
}





// 专用函数 *****************************************************************************
unsigned char ascii_table[16] =
{
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

int asc2hex(unsigned char bKey, unsigned char *bNew)
{
	if ((bKey >= '0') && (bKey <= '9'))
		*bNew = bKey - '0';
	else if ((bKey >= 'A') && (bKey <= 'F'))
		*bNew = bKey - 'A' + 10;
	else if ((bKey >= 'a') && (bKey <= 'f'))
		*bNew = bKey - 'a' + 10;
	else
	{
		return -1;
	}
	return 0;
}

void hex2asc(unsigned char dat, unsigned char **out)
{
	**out = ascii_table[dat >> 4];
	*out += 1;
	**out = ascii_table[dat & 0x0f];
	*out += 1;
}

int Str2Hex(unsigned char *pRead, unsigned char *pWrite, int nCount)
{
	unsigned char bNew = '\0';

	while (nCount--)
	{
		if (asc2hex(*pRead++, &bNew) == -1)
			return -1;

		*pWrite = *pWrite << 4 | bNew;

		if (!(nCount & 0x01))
			++pWrite;
	}
	return 0;
}

u8 CalcCrc8(u8* pAddr, int nDataLen)
{
	return crc8(pAddr, nDataLen, crc_8);
}

void Hex2Str(unsigned char *pRead, unsigned char **pWrite, int nLen)
{
	while (nLen--)
		hex2asc(*pRead++, pWrite);
}


void DEBUG_LOG(EM_LogLevel emLv, const char* pFormat, ...)
{
	if (EM_LOG_ERROR != emLv &&  !g_bIsWriteLog)
	{
		return;
	}

	char zMemory[MaxMallocMem];
	va_list VaList;
	memset(zMemory, 0, MaxMallocMem);
	va_start(VaList, pFormat);
	vsnprintf_s(zMemory, MaxMallocMem - 1, MaxMallocMem -1, pFormat, VaList); 

	CUtil::WriteLog(emLv, zMemory);
	va_end(VaList);
}

void DEBUG_HEX(EM_LogLevel emLv, char *pVarName,char *pBuffer,int Len)
{
	if (EM_LOG_ERROR != emLv &&  !g_bIsWriteLog)
	{
		return;
	}

	if(g_bIsWriteLog)//目录存在
	{
		CUtil::WriteHexLog(emLv, pVarName,pBuffer,Len);
	}
}

void SetLogFlag(bool bIsWrite)
{
	g_bIsWriteLog = bIsWrite;
}


