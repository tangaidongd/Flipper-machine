#ifndef _ANALYZE_NET_WORK_H_
#define _ANALYZE_NET_WORK_H_

#include <map>
#include <vector>
#include <string>
#include "publicFun.h"
#include "CClientSocket.h"


#define  WM_REV_UPDATE  WM_USER + 1096			//	命令
#define  WM_CONNECT_STATUS  WM_USER + 1097		//	命令

#define  MAX_TAG_LEN	250			// tag指定为202，扩大部分缓存
#define  MAX_ALARM_LEN	130*5		// 保存条数最大为100条，扩大30条缓存


struct  STRequestRet
{
	int nStartTag;
	int nEndTag;
	int nReadOrWrite;
	bool bSuccess;
	STRequestRet()
	{
		nStartTag = 0;
		nEndTag = 0;
		nReadOrWrite = 0;
		bSuccess = 0;
	}
};


typedef struct AlarmItemData
{
	int nAlarmID;
	CString strTime;
	CString strAlarmMsg;
	CString strAlarmDetail;
	AlarmItemData()
	{
		nAlarmID		= 0;
		strTime			= L"";
		strAlarmMsg		= L"";
		strAlarmDetail	= L"";
	}
}ST_AlarmItemData;

enum EM_Pro_Network_Tag
{
	EM_PRO_TAG_000	=	0	,	//	版本1
	EM_PRO_TAG_001	=	1	,	//	版本2
	EM_PRO_TAG_002	=	2	,	//	版本3
	EM_PRO_TAG_003	=	3	,	//	版本4
	EM_PRO_TAG_004	=	4	,	//	版本5
	EM_PRO_TAG_005	=	5	,	//	
	EM_PRO_TAG_006	=	6	,	//	
	EM_PRO_TAG_007	=	7	,	//	IO输出和开关 jout5  sw1-4
	EM_PRO_TAG_008	=	8	,	//	IO输入 jin7-8
	EM_PRO_TAG_009	=	9	,	//	出错更新次数
	EM_PRO_TAG_010	=	10	,	//	出错次数
	EM_PRO_TAG_011	=	11	,	//	IO输入状态1
	EM_PRO_TAG_012	=	12	,	//	IO输入状态2
	EM_PRO_TAG_013	=	13	,	//	IO输入状态3
	EM_PRO_TAG_014	=	14	,	//	IO输入状态4
	EM_PRO_TAG_015	=	15	,	//	IO输出状态1
	EM_PRO_TAG_016	=	16	,	//	IO输出状态2
	EM_PRO_TAG_017	=	17	,	//	传输伺服IO状态
	EM_PRO_TAG_018	=	18	,	//	旋转伺服IO状态
	EM_PRO_TAG_019	=	19	,	//	马达端子IO状态
	EM_PRO_TAG_020	=	20	,	//	马达端子调速电压1
	EM_PRO_TAG_021	=	21	,	//	马达端子调速电压2
	EM_PRO_TAG_022	=	22	,	//	传输伺服脉冲频率1
	EM_PRO_TAG_023	=	23	,	//	传输伺服脉冲频率2
	EM_PRO_TAG_024	=	24	,	//	旋转伺服脉冲频率1
	EM_PRO_TAG_025	=	25	,	//	旋转伺服脉冲频率2
	EM_PRO_TAG_026	=	26	,	//	当前传输实际速度1
	EM_PRO_TAG_027	=	27	,	//	当前传输实际速度2
	EM_PRO_TAG_028	=	28	,	//	当前旋转实际速度1
	EM_PRO_TAG_029	=	29	,	//	当前旋转实际速度2
	EM_PRO_TAG_030	=	30	,	//	进板信号持续距离1
	EM_PRO_TAG_031	=	31	,	//	进板信号持续距离2
	EM_PRO_TAG_032	=	32	,	//	出板信号持续距离1
	EM_PRO_TAG_033	=	33	,	//	出板信号持续距离2
	EM_PRO_TAG_204	=	34	,	//	当前旋转角度1
	EM_PRO_TAG_205	=	35	,	//	当前旋转角度2
	EM_PRO_TAG_206	=	36	,	//	零位同时感应角度1
	EM_PRO_TAG_207	=	37	,	//	零位同时感应角度2
	EM_PRO_TAG_208	=	38	,	//	非零同时感应角度1
	EM_PRO_TAG_209	=	39	,	//	非零同时感应角度2				
	EM_PRO_TAG_038	=	40	,	//	请板时间1
	EM_PRO_TAG_039	=	41	,	//	请板时间2
	EM_PRO_TAG_040	=	42	,	//	入板时间1
	EM_PRO_TAG_041	=	43	,	//	入板时间2
	EM_PRO_TAG_042	=	44	,	//	到位时间1
	EM_PRO_TAG_043	=	45	,	//	到位时间2
	EM_PRO_TAG_044	=	46	,	//	快速翻板时间1
	EM_PRO_TAG_045	=	47	,	//	快速翻板时间2
	EM_PRO_TAG_046	=	48	,	//	慢速翻板时间1
	EM_PRO_TAG_047	=	49	,	//	慢速翻板时间2
	EM_PRO_TAG_048	=	50	,	//	水平不当时间1
	EM_PRO_TAG_049	=	51	,	//	水平不当时间2
	EM_PRO_TAG_050	=	52	,	//	等待出板状态运行时间1
	EM_PRO_TAG_051	=	53	,	//	等待出板状态运行时间2
	EM_PRO_TAG_052	=	54	,	//	出板状态运行时间1
	EM_PRO_TAG_053	=	55	,	//	出板状态运行时间2
	EM_PRO_TAG_054	=	56	,	//	上次翻板总耗时1
	EM_PRO_TAG_055	=	57	,	//	上次翻板总耗时2
	EM_PRO_TAG_056	=	58	,	//	上次翻板动作耗时1
	EM_PRO_TAG_057	=	59	,	//	上次翻板动作耗时2
	EM_PRO_TAG_058	=	60	,	//	无故障翻板次数1
	EM_PRO_TAG_059	=	61	,	//	无故障翻板次数2
	EM_PRO_TAG_060	=	62	,	//	当前工作状态
	EM_PRO_TAG_061	=	63	,	//	上次工作状态
	EM_PRO_TAG_062	=	64	,	//	细分状态
	EM_PRO_TAG_063	=	65	,	//		
	EM_PRO_TAG_064	=	66	,	//	
	EM_PRO_TAG_065	=	67	,	//	
	EM_PRO_TAG_066	=	68	,	//	
	EM_PRO_TAG_067	=	69	,	//	
	EM_PRO_TAG_068	=	70	,	//	
	EM_PRO_TAG_069	=	71	,	//	
	EM_PRO_TAG_070	=	72	,	//	
	EM_PRO_TAG_071	=	73	,	//	
	EM_PRO_TAG_072	=	74	,	//	
	EM_PRO_TAG_073	=	75	,	//	
	EM_PRO_TAG_074	=	76	,	//	
	EM_PRO_TAG_075	=	77	,	//	
	EM_PRO_TAG_076	=	78	,	//	
	EM_PRO_TAG_077	=	79	,	//	
	EM_PRO_TAG_078	=	80	,	//	
	EM_PRO_TAG_079	=	81	,	//	
	EM_PRO_TAG_080	=	82	,	//	
	EM_PRO_TAG_081	=	83	,	//	
	EM_PRO_TAG_082	=	84	,	//	
	EM_PRO_TAG_083	=	85	,	//	
	EM_PRO_TAG_084	=	86	,	//	
	EM_PRO_TAG_085	=	87	,	//	
	EM_PRO_TAG_086	=	88	,	//	
	EM_PRO_TAG_087	=	89	,	//	
	EM_PRO_TAG_088	=	90	,	//	
	EM_PRO_TAG_089	=	91	,	//	
	EM_PRO_TAG_090	=	92	,	//	
	EM_PRO_TAG_091	=	93	,	//	
	EM_PRO_TAG_092	=	94	,	//	
	EM_PRO_TAG_093	=	95	,	//	
	EM_PRO_TAG_100	=	100	,	//	机型方向
	EM_PRO_TAG_101	=	101	,	//	翻版选择
	EM_PRO_TAG_102	=	102	,	//	有无有板感应器
	EM_PRO_TAG_103	=	103	,	//	有无气缸磁性开关
	EM_PRO_TAG_104	=	104	,	//	平台边沿附加检测
	EM_PRO_TAG_105	=	105	,	//	平台传输电机类型
	EM_PRO_TAG_106	=	106	,	//	功能配置项1------------
	EM_PRO_TAG_107	=	107	,	//	功能配置项2------------
	EM_PRO_TAG_108	=	108	,	//	出板完成判定附加选项2-----
	EM_PRO_TAG_109	=	109	,	//	进板外沿信号有效延迟1
	EM_PRO_TAG_110	=	110	,	//	进板外沿信号有效延迟2
	EM_PRO_TAG_111	=	111	,	//	进板外沿信号有效距离1
	EM_PRO_TAG_112	=	112	,	//	进板外沿信号有效距离2
	EM_PRO_TAG_113	=	113	,	//	进板外沿信号失效延迟1
	EM_PRO_TAG_114	=	114	,	//	进板外沿信号失效延迟2
	EM_PRO_TAG_115	=	115	,	//	进板外沿信号失效距离1
	EM_PRO_TAG_116	=	116	,	//	进板外沿信号失效距离2
	EM_PRO_TAG_117	=	117	,	//	进板内沿信号有效延迟1
	EM_PRO_TAG_118	=	118	,	//	进板内沿信号有效延迟2
	EM_PRO_TAG_119	=	119	,	//	进板内沿信号有效距离1
	EM_PRO_TAG_120	=	120	,	//	进板内沿信号有效距离2
	EM_PRO_TAG_121	=	121	,	//	进板内沿信号失效延迟1
	EM_PRO_TAG_122	=	122	,	//	进板内沿信号失效延迟2
	EM_PRO_TAG_123	=	123	,	//	进板内沿信号失效距离1
	EM_PRO_TAG_124	=	124	,	//	进板内沿信号失效距离2
	EM_PRO_TAG_125	=	125	,	//	出板外沿信号有效延迟1
	EM_PRO_TAG_126	=	126	,	//	出板外沿信号有效延迟2
	EM_PRO_TAG_127	=	127	,	//	出板外沿信号有效距离1
	EM_PRO_TAG_128	=	128	,	//	出板外沿信号有效距离2
	EM_PRO_TAG_129	=	129	,	//	出板外沿信号失效延迟1
	EM_PRO_TAG_130	=	130	,	//	出板外沿信号失效延迟2
	EM_PRO_TAG_131	=	131	,	//	出板外沿信号失效距离1
	EM_PRO_TAG_132	=	132	,	//	出板外沿信号失效距离2
	EM_PRO_TAG_133	=	133	,	//	请板信号有效延迟1
	EM_PRO_TAG_134	=	134	,	//	请板信号有效延迟2
	EM_PRO_TAG_135	=	135	,	//	请板信号失效延迟1
	EM_PRO_TAG_136	=	136	,	//	请板信号失效延迟2
	EM_PRO_TAG_137	=	137	,	//	进板中间信号有效延迟1
	EM_PRO_TAG_138	=	138	,	//	进板中间信号有效延迟2
	EM_PRO_TAG_139	=	139	,	//	出板中间信号有效延迟1
	EM_PRO_TAG_140	=	140	,	//	出板中间信号有效延迟2
	EM_PRO_TAG_141	=	141	,	//	报警/门禁信号有效延迟
	EM_PRO_TAG_142	=	142	,	//	报警/门禁信号有效延迟
	EM_PRO_TAG_143	=	143	,	//	挡板气缸伸出判定延迟1
	EM_PRO_TAG_144	=	144	,	//	挡板气缸伸出判定延迟2
	EM_PRO_TAG_145	=	145	,	//	挡板气缸收回判定延迟1
	EM_PRO_TAG_146	=	146	,	//	挡板气缸收回判定延迟2
	EM_PRO_TAG_147	=	147	,	//	入板到位后传输延迟1
	EM_PRO_TAG_148	=	148	,	//	入板到位后传输延迟2
	EM_PRO_TAG_149	=	149	,	//	入板到位后传输距离1
	EM_PRO_TAG_150	=	150	,	//	入板到位后传输距离2
	EM_PRO_TAG_151	=	151	,	//	进板快速持续的距离1
	EM_PRO_TAG_152	=	152	,	//	进板快速持续的距离2
	EM_PRO_TAG_153	=	153	,	//	翻转中开始关挡板角度1
	EM_PRO_TAG_154	=	154	,	//	翻转中开始关挡板角度2
	EM_PRO_TAG_155	=	155	,	//	快速翻转角度1
	EM_PRO_TAG_156	=	156	,	//	快速翻转角度2
	EM_PRO_TAG_157	=	157	,	//	零位旋转停止角度1
	EM_PRO_TAG_158	=	158	,	//	零位旋转停止角度2
	EM_PRO_TAG_210	=	159	,	//	非零旋转停止角度1
	EM_PRO_TAG_211	=	160	,	//	非零旋转停止角度2
	EM_PRO_TAG_212	=	161	,	//	旋转轴静止判定角度1
	EM_PRO_TAG_213	=	162	,	//	旋转轴静止判定角度2
	EM_PRO_TAG_214	=	163	,	//	旋转轴静止判定时间1
	EM_PRO_TAG_215	=	164	,	//	旋转轴静止判定时间2
	EM_PRO_TAG_159	=	165	,	//	旋转中挡板检测角度1
	EM_PRO_TAG_160	=	166	,	//	旋转中挡板检测角度2
	EM_PRO_TAG_161	=	167	,	//	传输初始速度1
	EM_PRO_TAG_162	=	168	,	//	传输初始速度2
	EM_PRO_TAG_163	=	169	,	//	传输快速1
	EM_PRO_TAG_164	=	170	,	//	传输快速2
	EM_PRO_TAG_165	=	171	,	//	传输慢速1
	EM_PRO_TAG_166	=	172	,	//	传输慢速2
	EM_PRO_TAG_167	=	173	,	//	准备出板传输速度1
	EM_PRO_TAG_168	=	174	,	//	准备出板传输速度2
	EM_PRO_TAG_169	=	175	,	//	出板/手动传输速度1
	EM_PRO_TAG_170	=	176	,	//	出板/手动传输速度2
	EM_PRO_TAG_171	=	177	,	//	传输加速度1
	EM_PRO_TAG_172	=	178	,	//	传输加速度2
	EM_PRO_TAG_173	=	179	,	//	旋转初始速度1
	EM_PRO_TAG_174	=	180	,	//	旋转初始速度2
	EM_PRO_TAG_175	=	181	,	//	旋转快速1
	EM_PRO_TAG_176	=	182	,	//	旋转快速2
	EM_PRO_TAG_177	=	183	,	//	旋转慢速1
	EM_PRO_TAG_178	=	184	,	//	旋转慢速2
	EM_PRO_TAG_179	=	185	,	//	旋转水平速度1
	EM_PRO_TAG_180	=	186	,	//	旋转水平速度2
	EM_PRO_TAG_181	=	187	,	//	回零/手动旋转速度1
	EM_PRO_TAG_182	=	188	,	//	回零/手动旋转速度2
	EM_PRO_TAG_183	=	189	,	//	旋转加速度1
	EM_PRO_TAG_184	=	190	,	//	旋转加速度2
	EM_PRO_TAG_216	=	191,	// 马达最大传输速度1	新增
	EM_PRO_TAG_217	=	192,	// 马达最大传输速度2
	EM_PRO_TAG_218	=	193,	// 马达快速传输时间1	新增
	EM_PRO_TAG_219	=	194,	// 马达快速传输时间2
	EM_PRO_TAG_185	=	195	,	//	IP地址1
	EM_PRO_TAG_186	=	196	,	//	IP地址2
	EM_PRO_TAG_187	=	197	,	//	端口1
	EM_PRO_TAG_188	=	198	,	//	端口2
	EM_PRO_TAG_189	=	199	,	//	入板超时报警时间
	EM_PRO_TAG_190	=	200	,	//	出板超时报警时间
	EM_PRO_TAG_191	=	201	,	//	水平调整报警时间
	EM_PRO_TAG_192	=	202	,	//	JIN4-4替代输入IO
	EM_PRO_TAG_193	=	203	,	//	JOUT2-2替代输出IO
	EM_PRO_TAG_194	=	204	,	//	报警次数(N)
	EM_PRO_TAG_195	=	205	,	//	IO强制输出使能
	EM_PRO_TAG_196	=	206	,	//	IO强制输出1
	EM_PRO_TAG_197	=	207	,	//	IO强制输出2
	EM_PRO_TAG_198	=	208	,	//	IO强制输出3
	EM_PRO_TAG_199	=	209	,	//	当前时间-月份
	EM_PRO_TAG_200	=	210	,	//	当前时间-日期
	EM_PRO_TAG_201	=	211	,	//	当前时间-小时
	EM_PRO_TAG_202	=	212	,	//	当前时间-分钟
	EM_PRO_TAG_203	=	213	,	//	当前时间-秒

	EM_PRO_TAG_230  =   230,	//  旋转轴老化
	EM_PRO_TAG_231	=	231,	//  全动作老化
	EM_PRO_TAG_232	=	232,	//  设定老化次数1
	EM_PRO_TAG_233	=	233,	//  设定老化次数2
	EM_PRO_TAG_234	=	234,	//  当前老化次数1
	EM_PRO_TAG_235	=	235,	//  当前老化次数2
	EM_PRO_TAG_236	=	236,	//  气缸测试1
	EM_PRO_TAG_237	=	237,	//  气缸测试2

	EM_PRO_TAG_240	=	241	,	//	启动旋转指令
	EM_PRO_TAG_241	=	242	,	//	旋转停止角度1
	EM_PRO_TAG_242	=	243	,	//	旋转停止角度2
	EM_PRO_TAG_243  =	244,	//	旋转周期角度1
	EM_PRO_TAG_244  =   245,	//	旋转周期角度2
	EM_PRO_TAG_245  =   240,	//	启动二次回零

	EM_PRO_TAG_DATA_END = 246,	// 排除告警后的数据长度
	EM_PRO_ALARM_START = 250,	//	报警起始
	EM_PRO_TAG_MAX
};


struct Alarm_Detail
{
	int nAlarmID;
	char zStrAlarmMsg[256];
	char zStrAlarmDetail[256];
};

struct ST_VALUE_UINT
{
	unsigned int nTag;
	unsigned int nUintValue;   
};


enum EM_ONTIME_TYPE	
{
	EM_ONTIME_NORMAL,
	EM_ONTIME_ALARM,
	EM_GET_TIME_PACK,
};


class CAnalyzeNetwork: public CNotifyRequestRet
{
public:
	CAnalyzeNetwork();
	~CAnalyzeNetwork();

	
	// 消息回调位置
	void SetParentHand(HWND hHand) { m_hHandleParent = hHand;}	// 设置收消息窗口
	bool InitConect(char* pAddress, char* pPort, int nRefresh = 100);

	bool GetConnectStatus();

	virtual void RequestRetMsg();			

	//void PackRequestByRead(int nRequestTagIndex, int nRequestDataLen);
	//void PackRequestByWrite(int nRequestTagIndex, int nRequestDataLen, unsigned char* pPostData);
	//void AnalysisResposeDataBuff(unsigned char* pResposeBuf, int nStartTag, int nDataLen);
	
	// 设置和读取数据，
	// 设置的是缓冲区没有真实发送到翻版机，发送数据流程为先设置数据，再使用同步函数
	bool SetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf);	// 通过tag设置多个值
	bool SetIndexValueByTag(int nTag, int& nValue);		// 通过tag设置键值，异常键值返回false
	bool GetIndexValueByTag(int nTag, unsigned int& nValue);	// 通过tag获取键值，异常键值返回false
	bool GetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf);	
	
	// 获取字符串和设置字符串这种，都需要单位转换
	bool GetStrValueValueByTag(int nTag, CString& strValue);		
	bool SetStrValueValueByTag(int nTag, CString strValue);

	// 获取
	void SynchronizeAlarm2Local(int nQueryNum);
	bool GetAlarmInfo(int nGetAlarmNum, std::vector<ST_AlarmItemData>& vecAlarmItem);

	// 参数导入导出
	bool ImportParam(CString strPath);
	bool ExportParam(CString strFilePath);

	// 工作状态
	CString GetWorkStatusStr(int nWorkStatus);

	void SynchronnizationTime();

	// 同步函数，同步本地数据与翻版机数据, nReadOrWrite: 0 读取，1写入
	void SynchronizeNetworkData(int nTagStart, int nTagEnd, int nReadOrWrite = 1);


private:
	int GetSingleTagNeedLength(int nTagValue);		// 单独设置一个属性时，有多少个字节,一般是1个或者2个。
	double GetTagUint(int nTagValue);					// 获取协议的单位；
	void GetRequstOntimePack(STSendDataItem& stSendDataItem, EM_ONTIME_TYPE emRequestType);

	static void	OnTimeUpdateValue(LPVOID lpParam);
	void OnTimeUpdateValue();
	void StopUpdateThread();
	

private:
	void InitTagIndexValueMap();
	void InitAlarmDetailMap();
	void InitWorkStatusStr();
	void InitValueUint();
	

private:
	int		m_nRefreshTime;		// 定时刷新时间
	unsigned char		m_zTagValueBuf[MAX_TAG_LEN];
	unsigned char		m_zAlarmValueBuf[MAX_ALARM_LEN];
	std::map<int, int>   m_mapTagValueLen;			//  协议每条指令的数据长度
	std::map<int, Alarm_Detail>  m_mapAlarmDetail;
	std::map<int, CString>   m_mapWorkStatusStr;
	std::map<int ,double>   m_mapUintTrans;
	HWND m_hHandleParent;					// 父窗口
	bool m_bOnTimeExitFlag;
	HANDLE	m_hThreadOnTimeUpdate;

	CClientSocket	m_clientSocket;
};

#endif
