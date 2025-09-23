#ifndef _LOG_H_
#define _LOG_H_
#include <Windows.h>


enum EM_LogLevel
{
	EM_LOG_NORMAL,
	EM_LOG_INFO,
	EM_LOG_WARM,
	EM_LOG_ERROR,
};

const static char* g_pLogLevel[] = {
	"normal",
	"info",
	"warm",
	"error"
};


class CUtil
{
public:
public:
	static int  AscToHex(char *pDst,unsigned char *pSrc,int SrcLen);
	static int  HexToAsc(unsigned char *pDst, char *pSrc, int nSrcLen);
	static bool ReverseBytesString(unsigned char *pBytes, int stringLen);
	static void WriteLog(EM_LogLevel emLogLv, char * pMsg);
	static bool WriteFormatLog(EM_LogLevel emLogLv, const char* pFormat, ...);
	static bool WriteHexLog(EM_LogLevel emLogLv, char *pVarName,char *pBuffer,unsigned int Len);
};
#endif
