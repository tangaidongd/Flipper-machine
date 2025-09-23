#ifndef _PUB_STRUCT_H_
#define _PUB_STRUCT_H_

/////////////////////// 协议结构
typedef struct STProtocol
{
	char				chHead;			// 帧头
	char				chTag;			// 类型
	int					nSendLen;		// 协议发包长度
	int					nRevLen;		// 协议收包长度
	unsigned int		nProType;		// 协议类型
	char				zData[50+1];	// 数据
	char				chCrc8;			// 效验
	char				chEnd;			// 帧尾
} STProtocol;



/////////////////////// 协议长度
typedef struct STProDataLen
{
	//char				chTag;			// 类型
	int					nSendLen;		// 协议发包长度
	int					nRevLen;		// 协议收包长度
	STProDataLen()
	{
		nSendLen = 0;
		nRevLen  = 0;
	}
} STProDataLen;


enum EM_Protocol_Type
{
	EM_TYPE_STATUS	= 0x00000008,
	EM_TYPE_CONTROL	= 0x00000004,
	EM_TYPE_READ	= 0x00000002,
	EM_TYPE_WRITE	= 0x00000001,
};

/////////////////////// 通讯报文
typedef struct STComData
{	
	unsigned char		chTag;			// 协议标识
	unsigned char		zData[50+1];	// 数据
	int					nDataLen;		// 数据长度
	int					nProtocolType;	// 协议类型，是否为控制
	STComData()
	{
		memset(zData, 0, sizeof(zData));
		nDataLen = 0;
		nProtocolType = 0;
	}
} STComData;



/////////////////////// 参数范围
typedef struct STParamRange
{
	char  chHead;			
	int   nMarxRange;
	int   nMinRange;
} STParamRange;




/////////////////////// 通讯报文
typedef struct STConfigData
{	
	unsigned char	 chCmdID;			// 配置ID
	std::string strCFName;		// 配置名
	std::vector<int> vCmdValue;
	void Init()
	{
		strCFName = "";
		vCmdValue.clear();
		chCmdID = 0;
	}
	STConfigData()
	{
		Init();
	}
} STCFData;



#endif
