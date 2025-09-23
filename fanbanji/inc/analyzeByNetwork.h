#ifndef _ANALYZE_NET_WORK_H_
#define _ANALYZE_NET_WORK_H_

#include <map>
#include <vector>
#include <string>
#include "publicFun.h"
#include "CClientSocket.h"


#define  WM_REV_UPDATE  WM_USER + 1096			//	����
#define  WM_CONNECT_STATUS  WM_USER + 1097		//	����

#define  MAX_TAG_LEN	250			// tagָ��Ϊ202�����󲿷ֻ���
#define  MAX_ALARM_LEN	130*5		// �����������Ϊ100��������30������


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
	EM_PRO_TAG_000	=	0	,	//	�汾1
	EM_PRO_TAG_001	=	1	,	//	�汾2
	EM_PRO_TAG_002	=	2	,	//	�汾3
	EM_PRO_TAG_003	=	3	,	//	�汾4
	EM_PRO_TAG_004	=	4	,	//	�汾5
	EM_PRO_TAG_005	=	5	,	//	
	EM_PRO_TAG_006	=	6	,	//	
	EM_PRO_TAG_007	=	7	,	//	IO����Ϳ��� jout5  sw1-4
	EM_PRO_TAG_008	=	8	,	//	IO���� jin7-8
	EM_PRO_TAG_009	=	9	,	//	������´���
	EM_PRO_TAG_010	=	10	,	//	�������
	EM_PRO_TAG_011	=	11	,	//	IO����״̬1
	EM_PRO_TAG_012	=	12	,	//	IO����״̬2
	EM_PRO_TAG_013	=	13	,	//	IO����״̬3
	EM_PRO_TAG_014	=	14	,	//	IO����״̬4
	EM_PRO_TAG_015	=	15	,	//	IO���״̬1
	EM_PRO_TAG_016	=	16	,	//	IO���״̬2
	EM_PRO_TAG_017	=	17	,	//	�����ŷ�IO״̬
	EM_PRO_TAG_018	=	18	,	//	��ת�ŷ�IO״̬
	EM_PRO_TAG_019	=	19	,	//	������IO״̬
	EM_PRO_TAG_020	=	20	,	//	�����ӵ��ٵ�ѹ1
	EM_PRO_TAG_021	=	21	,	//	�����ӵ��ٵ�ѹ2
	EM_PRO_TAG_022	=	22	,	//	�����ŷ�����Ƶ��1
	EM_PRO_TAG_023	=	23	,	//	�����ŷ�����Ƶ��2
	EM_PRO_TAG_024	=	24	,	//	��ת�ŷ�����Ƶ��1
	EM_PRO_TAG_025	=	25	,	//	��ת�ŷ�����Ƶ��2
	EM_PRO_TAG_026	=	26	,	//	��ǰ����ʵ���ٶ�1
	EM_PRO_TAG_027	=	27	,	//	��ǰ����ʵ���ٶ�2
	EM_PRO_TAG_028	=	28	,	//	��ǰ��תʵ���ٶ�1
	EM_PRO_TAG_029	=	29	,	//	��ǰ��תʵ���ٶ�2
	EM_PRO_TAG_030	=	30	,	//	�����źų�������1
	EM_PRO_TAG_031	=	31	,	//	�����źų�������2
	EM_PRO_TAG_032	=	32	,	//	�����źų�������1
	EM_PRO_TAG_033	=	33	,	//	�����źų�������2
	EM_PRO_TAG_204	=	34	,	//	��ǰ��ת�Ƕ�1
	EM_PRO_TAG_205	=	35	,	//	��ǰ��ת�Ƕ�2
	EM_PRO_TAG_206	=	36	,	//	��λͬʱ��Ӧ�Ƕ�1
	EM_PRO_TAG_207	=	37	,	//	��λͬʱ��Ӧ�Ƕ�2
	EM_PRO_TAG_208	=	38	,	//	����ͬʱ��Ӧ�Ƕ�1
	EM_PRO_TAG_209	=	39	,	//	����ͬʱ��Ӧ�Ƕ�2				
	EM_PRO_TAG_038	=	40	,	//	���ʱ��1
	EM_PRO_TAG_039	=	41	,	//	���ʱ��2
	EM_PRO_TAG_040	=	42	,	//	���ʱ��1
	EM_PRO_TAG_041	=	43	,	//	���ʱ��2
	EM_PRO_TAG_042	=	44	,	//	��λʱ��1
	EM_PRO_TAG_043	=	45	,	//	��λʱ��2
	EM_PRO_TAG_044	=	46	,	//	���ٷ���ʱ��1
	EM_PRO_TAG_045	=	47	,	//	���ٷ���ʱ��2
	EM_PRO_TAG_046	=	48	,	//	���ٷ���ʱ��1
	EM_PRO_TAG_047	=	49	,	//	���ٷ���ʱ��2
	EM_PRO_TAG_048	=	50	,	//	ˮƽ����ʱ��1
	EM_PRO_TAG_049	=	51	,	//	ˮƽ����ʱ��2
	EM_PRO_TAG_050	=	52	,	//	�ȴ�����״̬����ʱ��1
	EM_PRO_TAG_051	=	53	,	//	�ȴ�����״̬����ʱ��2
	EM_PRO_TAG_052	=	54	,	//	����״̬����ʱ��1
	EM_PRO_TAG_053	=	55	,	//	����״̬����ʱ��2
	EM_PRO_TAG_054	=	56	,	//	�ϴη����ܺ�ʱ1
	EM_PRO_TAG_055	=	57	,	//	�ϴη����ܺ�ʱ2
	EM_PRO_TAG_056	=	58	,	//	�ϴη��嶯����ʱ1
	EM_PRO_TAG_057	=	59	,	//	�ϴη��嶯����ʱ2
	EM_PRO_TAG_058	=	60	,	//	�޹��Ϸ������1
	EM_PRO_TAG_059	=	61	,	//	�޹��Ϸ������2
	EM_PRO_TAG_060	=	62	,	//	��ǰ����״̬
	EM_PRO_TAG_061	=	63	,	//	�ϴι���״̬
	EM_PRO_TAG_062	=	64	,	//	ϸ��״̬
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
	EM_PRO_TAG_100	=	100	,	//	���ͷ���
	EM_PRO_TAG_101	=	101	,	//	����ѡ��
	EM_PRO_TAG_102	=	102	,	//	�����а��Ӧ��
	EM_PRO_TAG_103	=	103	,	//	�������״��Կ���
	EM_PRO_TAG_104	=	104	,	//	ƽ̨���ظ��Ӽ��
	EM_PRO_TAG_105	=	105	,	//	ƽ̨����������
	EM_PRO_TAG_106	=	106	,	//	����������1------------
	EM_PRO_TAG_107	=	107	,	//	����������2------------
	EM_PRO_TAG_108	=	108	,	//	��������ж�����ѡ��2-----
	EM_PRO_TAG_109	=	109	,	//	���������ź���Ч�ӳ�1
	EM_PRO_TAG_110	=	110	,	//	���������ź���Ч�ӳ�2
	EM_PRO_TAG_111	=	111	,	//	���������ź���Ч����1
	EM_PRO_TAG_112	=	112	,	//	���������ź���Ч����2
	EM_PRO_TAG_113	=	113	,	//	���������ź�ʧЧ�ӳ�1
	EM_PRO_TAG_114	=	114	,	//	���������ź�ʧЧ�ӳ�2
	EM_PRO_TAG_115	=	115	,	//	���������ź�ʧЧ����1
	EM_PRO_TAG_116	=	116	,	//	���������ź�ʧЧ����2
	EM_PRO_TAG_117	=	117	,	//	���������ź���Ч�ӳ�1
	EM_PRO_TAG_118	=	118	,	//	���������ź���Ч�ӳ�2
	EM_PRO_TAG_119	=	119	,	//	���������ź���Ч����1
	EM_PRO_TAG_120	=	120	,	//	���������ź���Ч����2
	EM_PRO_TAG_121	=	121	,	//	���������ź�ʧЧ�ӳ�1
	EM_PRO_TAG_122	=	122	,	//	���������ź�ʧЧ�ӳ�2
	EM_PRO_TAG_123	=	123	,	//	���������ź�ʧЧ����1
	EM_PRO_TAG_124	=	124	,	//	���������ź�ʧЧ����2
	EM_PRO_TAG_125	=	125	,	//	���������ź���Ч�ӳ�1
	EM_PRO_TAG_126	=	126	,	//	���������ź���Ч�ӳ�2
	EM_PRO_TAG_127	=	127	,	//	���������ź���Ч����1
	EM_PRO_TAG_128	=	128	,	//	���������ź���Ч����2
	EM_PRO_TAG_129	=	129	,	//	���������ź�ʧЧ�ӳ�1
	EM_PRO_TAG_130	=	130	,	//	���������ź�ʧЧ�ӳ�2
	EM_PRO_TAG_131	=	131	,	//	���������ź�ʧЧ����1
	EM_PRO_TAG_132	=	132	,	//	���������ź�ʧЧ����2
	EM_PRO_TAG_133	=	133	,	//	����ź���Ч�ӳ�1
	EM_PRO_TAG_134	=	134	,	//	����ź���Ч�ӳ�2
	EM_PRO_TAG_135	=	135	,	//	����ź�ʧЧ�ӳ�1
	EM_PRO_TAG_136	=	136	,	//	����ź�ʧЧ�ӳ�2
	EM_PRO_TAG_137	=	137	,	//	�����м��ź���Ч�ӳ�1
	EM_PRO_TAG_138	=	138	,	//	�����м��ź���Ч�ӳ�2
	EM_PRO_TAG_139	=	139	,	//	�����м��ź���Ч�ӳ�1
	EM_PRO_TAG_140	=	140	,	//	�����м��ź���Ч�ӳ�2
	EM_PRO_TAG_141	=	141	,	//	����/�Ž��ź���Ч�ӳ�
	EM_PRO_TAG_142	=	142	,	//	����/�Ž��ź���Ч�ӳ�
	EM_PRO_TAG_143	=	143	,	//	������������ж��ӳ�1
	EM_PRO_TAG_144	=	144	,	//	������������ж��ӳ�2
	EM_PRO_TAG_145	=	145	,	//	���������ջ��ж��ӳ�1
	EM_PRO_TAG_146	=	146	,	//	���������ջ��ж��ӳ�2
	EM_PRO_TAG_147	=	147	,	//	��嵽λ�����ӳ�1
	EM_PRO_TAG_148	=	148	,	//	��嵽λ�����ӳ�2
	EM_PRO_TAG_149	=	149	,	//	��嵽λ�������1
	EM_PRO_TAG_150	=	150	,	//	��嵽λ�������2
	EM_PRO_TAG_151	=	151	,	//	������ٳ����ľ���1
	EM_PRO_TAG_152	=	152	,	//	������ٳ����ľ���2
	EM_PRO_TAG_153	=	153	,	//	��ת�п�ʼ�ص���Ƕ�1
	EM_PRO_TAG_154	=	154	,	//	��ת�п�ʼ�ص���Ƕ�2
	EM_PRO_TAG_155	=	155	,	//	���ٷ�ת�Ƕ�1
	EM_PRO_TAG_156	=	156	,	//	���ٷ�ת�Ƕ�2
	EM_PRO_TAG_157	=	157	,	//	��λ��תֹͣ�Ƕ�1
	EM_PRO_TAG_158	=	158	,	//	��λ��תֹͣ�Ƕ�2
	EM_PRO_TAG_210	=	159	,	//	������תֹͣ�Ƕ�1
	EM_PRO_TAG_211	=	160	,	//	������תֹͣ�Ƕ�2
	EM_PRO_TAG_212	=	161	,	//	��ת�ᾲֹ�ж��Ƕ�1
	EM_PRO_TAG_213	=	162	,	//	��ת�ᾲֹ�ж��Ƕ�2
	EM_PRO_TAG_214	=	163	,	//	��ת�ᾲֹ�ж�ʱ��1
	EM_PRO_TAG_215	=	164	,	//	��ת�ᾲֹ�ж�ʱ��2
	EM_PRO_TAG_159	=	165	,	//	��ת�е�����Ƕ�1
	EM_PRO_TAG_160	=	166	,	//	��ת�е�����Ƕ�2
	EM_PRO_TAG_161	=	167	,	//	�����ʼ�ٶ�1
	EM_PRO_TAG_162	=	168	,	//	�����ʼ�ٶ�2
	EM_PRO_TAG_163	=	169	,	//	�������1
	EM_PRO_TAG_164	=	170	,	//	�������2
	EM_PRO_TAG_165	=	171	,	//	��������1
	EM_PRO_TAG_166	=	172	,	//	��������2
	EM_PRO_TAG_167	=	173	,	//	׼�����崫���ٶ�1
	EM_PRO_TAG_168	=	174	,	//	׼�����崫���ٶ�2
	EM_PRO_TAG_169	=	175	,	//	����/�ֶ������ٶ�1
	EM_PRO_TAG_170	=	176	,	//	����/�ֶ������ٶ�2
	EM_PRO_TAG_171	=	177	,	//	������ٶ�1
	EM_PRO_TAG_172	=	178	,	//	������ٶ�2
	EM_PRO_TAG_173	=	179	,	//	��ת��ʼ�ٶ�1
	EM_PRO_TAG_174	=	180	,	//	��ת��ʼ�ٶ�2
	EM_PRO_TAG_175	=	181	,	//	��ת����1
	EM_PRO_TAG_176	=	182	,	//	��ת����2
	EM_PRO_TAG_177	=	183	,	//	��ת����1
	EM_PRO_TAG_178	=	184	,	//	��ת����2
	EM_PRO_TAG_179	=	185	,	//	��תˮƽ�ٶ�1
	EM_PRO_TAG_180	=	186	,	//	��תˮƽ�ٶ�2
	EM_PRO_TAG_181	=	187	,	//	����/�ֶ���ת�ٶ�1
	EM_PRO_TAG_182	=	188	,	//	����/�ֶ���ת�ٶ�2
	EM_PRO_TAG_183	=	189	,	//	��ת���ٶ�1
	EM_PRO_TAG_184	=	190	,	//	��ת���ٶ�2
	EM_PRO_TAG_216	=	191,	// ���������ٶ�1	����
	EM_PRO_TAG_217	=	192,	// ���������ٶ�2
	EM_PRO_TAG_218	=	193,	// �����ٴ���ʱ��1	����
	EM_PRO_TAG_219	=	194,	// �����ٴ���ʱ��2
	EM_PRO_TAG_185	=	195	,	//	IP��ַ1
	EM_PRO_TAG_186	=	196	,	//	IP��ַ2
	EM_PRO_TAG_187	=	197	,	//	�˿�1
	EM_PRO_TAG_188	=	198	,	//	�˿�2
	EM_PRO_TAG_189	=	199	,	//	��峬ʱ����ʱ��
	EM_PRO_TAG_190	=	200	,	//	���峬ʱ����ʱ��
	EM_PRO_TAG_191	=	201	,	//	ˮƽ��������ʱ��
	EM_PRO_TAG_192	=	202	,	//	JIN4-4�������IO
	EM_PRO_TAG_193	=	203	,	//	JOUT2-2������IO
	EM_PRO_TAG_194	=	204	,	//	��������(N)
	EM_PRO_TAG_195	=	205	,	//	IOǿ�����ʹ��
	EM_PRO_TAG_196	=	206	,	//	IOǿ�����1
	EM_PRO_TAG_197	=	207	,	//	IOǿ�����2
	EM_PRO_TAG_198	=	208	,	//	IOǿ�����3
	EM_PRO_TAG_199	=	209	,	//	��ǰʱ��-�·�
	EM_PRO_TAG_200	=	210	,	//	��ǰʱ��-����
	EM_PRO_TAG_201	=	211	,	//	��ǰʱ��-Сʱ
	EM_PRO_TAG_202	=	212	,	//	��ǰʱ��-����
	EM_PRO_TAG_203	=	213	,	//	��ǰʱ��-��

	EM_PRO_TAG_230  =   230,	//  ��ת���ϻ�
	EM_PRO_TAG_231	=	231,	//  ȫ�����ϻ�
	EM_PRO_TAG_232	=	232,	//  �趨�ϻ�����1
	EM_PRO_TAG_233	=	233,	//  �趨�ϻ�����2
	EM_PRO_TAG_234	=	234,	//  ��ǰ�ϻ�����1
	EM_PRO_TAG_235	=	235,	//  ��ǰ�ϻ�����2
	EM_PRO_TAG_236	=	236,	//  ���ײ���1
	EM_PRO_TAG_237	=	237,	//  ���ײ���2

	EM_PRO_TAG_240	=	241	,	//	������תָ��
	EM_PRO_TAG_241	=	242	,	//	��תֹͣ�Ƕ�1
	EM_PRO_TAG_242	=	243	,	//	��תֹͣ�Ƕ�2
	EM_PRO_TAG_243  =	244,	//	��ת���ڽǶ�1
	EM_PRO_TAG_244  =   245,	//	��ת���ڽǶ�2
	EM_PRO_TAG_245  =   240,	//	�������λ���

	EM_PRO_TAG_DATA_END = 246,	// �ų��澯������ݳ���
	EM_PRO_ALARM_START = 250,	//	������ʼ
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

	
	// ��Ϣ�ص�λ��
	void SetParentHand(HWND hHand) { m_hHandleParent = hHand;}	// ��������Ϣ����
	bool InitConect(char* pAddress, char* pPort, int nRefresh = 100);

	bool GetConnectStatus();

	virtual void RequestRetMsg();			

	//void PackRequestByRead(int nRequestTagIndex, int nRequestDataLen);
	//void PackRequestByWrite(int nRequestTagIndex, int nRequestDataLen, unsigned char* pPostData);
	//void AnalysisResposeDataBuff(unsigned char* pResposeBuf, int nStartTag, int nDataLen);
	
	// ���úͶ�ȡ���ݣ�
	// ���õ��ǻ�����û����ʵ���͵��������������������Ϊ���������ݣ���ʹ��ͬ������
	bool SetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf);	// ͨ��tag���ö��ֵ
	bool SetIndexValueByTag(int nTag, int& nValue);		// ͨ��tag���ü�ֵ���쳣��ֵ����false
	bool GetIndexValueByTag(int nTag, unsigned int& nValue);	// ͨ��tag��ȡ��ֵ���쳣��ֵ����false
	bool GetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf);	
	
	// ��ȡ�ַ����������ַ������֣�����Ҫ��λת��
	bool GetStrValueValueByTag(int nTag, CString& strValue);		
	bool SetStrValueValueByTag(int nTag, CString strValue);

	// ��ȡ
	void SynchronizeAlarm2Local(int nQueryNum);
	bool GetAlarmInfo(int nGetAlarmNum, std::vector<ST_AlarmItemData>& vecAlarmItem);

	// �������뵼��
	bool ImportParam(CString strPath);
	bool ExportParam(CString strFilePath);

	// ����״̬
	CString GetWorkStatusStr(int nWorkStatus);

	void SynchronnizationTime();

	// ͬ��������ͬ�����������뷭�������, nReadOrWrite: 0 ��ȡ��1д��
	void SynchronizeNetworkData(int nTagStart, int nTagEnd, int nReadOrWrite = 1);


private:
	int GetSingleTagNeedLength(int nTagValue);		// ��������һ������ʱ���ж��ٸ��ֽ�,һ����1������2����
	double GetTagUint(int nTagValue);					// ��ȡЭ��ĵ�λ��
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
	int		m_nRefreshTime;		// ��ʱˢ��ʱ��
	unsigned char		m_zTagValueBuf[MAX_TAG_LEN];
	unsigned char		m_zAlarmValueBuf[MAX_ALARM_LEN];
	std::map<int, int>   m_mapTagValueLen;			//  Э��ÿ��ָ������ݳ���
	std::map<int, Alarm_Detail>  m_mapAlarmDetail;
	std::map<int, CString>   m_mapWorkStatusStr;
	std::map<int ,double>   m_mapUintTrans;
	HWND m_hHandleParent;					// ������
	bool m_bOnTimeExitFlag;
	HANDLE	m_hThreadOnTimeUpdate;

	CClientSocket	m_clientSocket;
};

#endif
