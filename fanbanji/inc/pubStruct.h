#ifndef _PUB_STRUCT_H_
#define _PUB_STRUCT_H_

/////////////////////// Э��ṹ
typedef struct STProtocol
{
	char				chHead;			// ֡ͷ
	char				chTag;			// ����
	int					nSendLen;		// Э�鷢������
	int					nRevLen;		// Э���հ�����
	unsigned int		nProType;		// Э������
	char				zData[50+1];	// ����
	char				chCrc8;			// Ч��
	char				chEnd;			// ֡β
} STProtocol;



/////////////////////// Э�鳤��
typedef struct STProDataLen
{
	//char				chTag;			// ����
	int					nSendLen;		// Э�鷢������
	int					nRevLen;		// Э���հ�����
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

/////////////////////// ͨѶ����
typedef struct STComData
{	
	unsigned char		chTag;			// Э���ʶ
	unsigned char		zData[50+1];	// ����
	int					nDataLen;		// ���ݳ���
	int					nProtocolType;	// Э�����ͣ��Ƿ�Ϊ����
	STComData()
	{
		memset(zData, 0, sizeof(zData));
		nDataLen = 0;
		nProtocolType = 0;
	}
} STComData;



/////////////////////// ������Χ
typedef struct STParamRange
{
	char  chHead;			
	int   nMarxRange;
	int   nMinRange;
} STParamRange;




/////////////////////// ͨѶ����
typedef struct STConfigData
{	
	unsigned char	 chCmdID;			// ����ID
	std::string strCFName;		// ������
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
