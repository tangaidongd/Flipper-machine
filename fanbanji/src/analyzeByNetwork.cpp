#include "analyzeByNetwork.h"
#include "..\inc\publicFun.h"
#include <iostream>
#include <fstream>
#include <ctime>


#define  PRO_DATA_LEN	50



Alarm_Detail g_AlarmDetail[] = {
	{0x1, "��ͣ", "��ͣ��ť����"},
	{0x2, "�����������澯", "��������������IOָʾ�쳣����Դ��ť�����ָ�"},
	{0x3, "��ת�������澯", "��ת����������IOָʾ�쳣����Դ��ť�����ָ�"},
	{0x4, "�����ᷴ���쳣", "δ��⵽��Ч�����ᷴ�������������������������DB��ͷ�����ư�Ӳ��"},
	{0x5, "��ת�ᷴ���쳣", "δ��⵽��Ч��ת�ᷴ���������������������ת��DB��ͷ�����ư�Ӳ��"},
	{0x6, "��ͣ��ť��ѹʱ����λ", "�ȰѼ�ͣ��ť�ɿ����ٰ���λ��ť"},
	{0x7, "��Դ���ذ�ť�ɿ�", "��Դ���ذ�ť�ɿ�������������"},
	{0x11, "����1���ز���λ", "û�����Կ�������λ�ã�ƽ̨��λ�µ�������ף�"},
	{0x12, "����1�������λ", "û�����Կ��ص�λλ�ã�ƽ̨��λ�µ�������ף�"},
	{0x13, "����2���ز���λ", "û�����Կ�������λ�ã�ƽ̨��λ�µ��Ҳ����ף�"},
	{0x14, "����2�������λ", "û�����Կ��ص�λλ�ã�ƽ̨��λ�µ��Ҳ����ף�"},
	{0x15, "�ײ���������λ��", "��ת�м�⵽���ײ�����ĵ�λ���Կ���û�б�����Ч"},
	{0x16, "��λ����δ���ر�", "���嵽��ʼ����ʱ������������Ȼû����ѹ��λ���������ѹ"},
	{0x23, "��λ����а��쳣1", "�ڵ�λ������Ч�ر�ʱ�̣�ƽ̨��λ�µĵ�λ����Ӧ�����Ѿ���Ч�������õ�λ��Ӧ�����Ӧ"},
	{0x24, "��λ����а��쳣2", "�ڵ�λ������Ч�ر�ʱ�̣�ƽ̨����λ�µĵ�λ����Ӧ�����Ѿ���Ч�������õ�λ��Ӧ�����Ӧ"},
	{0x25, "����а崫�䳬ʱ", "����ڸ�Ӧ��һֱ��Ӧ�а壬���½��崫�䳬ʱ"},
	{0x26, "��λ��Ч���䳬ʱ", "��λ��Ӧ�����ܱ�����Ч�����½��崫�䳬ʱ"},
	{0x27, "��崫�䳬����", "�����Բ����������������λ�ж���1ʹ�ܣ�����λ�ж�������0 ʱ�������ñ������������������"},
	{0x28, "����ź�δ��ʧ", "�����ò���λ�ж�ʹ�ܣ�Ҫ������ź���ʧ�󣬴��䳬������⵽����ź�δ��ʧ�������ñ���"},
	{0x29, "���ٽ����������а�", "���ٽ����³�ʱ����⵽��ڴ����а�"},
	{0x2A, "���ٽ�������δ��λ", "���ٽ����³�ʱ����⵽����û�е�λ"},
	{0x31, "��ת����Χ��220�㣩", "��ת����δ������Ӧ�������³���Χ�������ܸ�Ӧ�����⣩"},
	{0x32, "��ת������ʱ", "��ת��������ָ������ʱ�䣨��������������������ư�Ӳ�����⣩"},
	{0x33, "��ת��ʱδ����", "��ʼ��תһ��ʱ���δ�뿪����Ӧ���򣨿��ܷ��������ư�Ӳ�����⣬���Ӧ�����⣩"},
	{0x34, "��ת������Ӧλ", "��ת����壬����������Ӧ������"},
	{0x35, "ƽ̨�����Ӧλ", "��תˮƽ���򶶶���ṹԭ������������Ӧ������"},
	{0x36, "��ת����δ�����", "����ж���Ӧ���쳣����"},
	{0x37, "��תʱ���ڴ��а�", "���������תʱ����⵽���Ի������Ӧ����Ч�������ñ���"},
	{0x38, "ƽ̨��ƽ��ʱ", "�򶶶���ṹԭ��ƽ̨��������Ӧ��ˮƽλ�ã��Զ���ƽʱ������ʱ���Ӵ��ƽʱ�䣬������0���Σ�"},
	{0x40, "���峬ʱ0", "�ڼ�����崫��ʱ�������ʱ�䳬ʱ"},
	{0x41, "���峬ʱ1", "�ڿ�����崫��ʱ�������ʱ�䳬ʱ"},
	{0x42, "���峬ʱ2", "��������崫��ʱ�������ʱ�䳬ʱ"},
	{0x43, "���峬ʱ1", "������Ӧ������ʧ�����³��峬ʱ"},
	{0x44, "���峬ʱ2", "����������ź�һֱ��Ч�����³��峬ʱ"},
	{0x45, "���峬ʱ3", "�����ʱ������룬δ�ﵽ������ı��������³�ʱ"},
	{0x51, "�������ߵ�λ����1", "����׶�1���崫��ײ������󵯻أ����¼��ʧ�ܡ��轫�����ʼ�ٶȽ���"},
	{0x52, "�������ߵ�λ����2", "����׶�2���崫��ײ������󵯻أ����¼��ʧ�ܡ��轫�����ʼ�ٶȽ���"},
	{0x53, "�������ߵ�λ����3", "����׶�3���崫��ײ������󵯻أ����¼��ʧ�ܡ��轫�����ʼ�ٶȽ���"},
	{0x54, "����ǰ��⵽�����а�", "���߸�Ӧ������⵽�а壬��ʱ�����ֱ�ӱ���"},
	{0x55, "���㴫�����߳�����1", "����ʱ������������ഫ��ʱ����������δ�����"},
	{0x56, "���㴫�����߳�����2", "����ʱ������������ഫ��ʱ������ʱ��δ�����"},
	{0x57, "���㴫�����߳�ʱ1", "����ʱ�����������ഫ��ʱ����������δ�����"},
	{0x58, "���㴫�����߳�ʱ2", "����ʱ�����������ഫ��ʱ������ʱ��δ�����"},
	{0x59, "����������ʧ��1", "����ʱƽ̨��б�����´�����������ӣ���߸�Ӧ��1ʼ�ո�Ӧ���壬����ʧ��"},
	{0x5A, "����������ʧ��2", "����ʱƽ̨��б�����´�����������ӣ���߸�Ӧ��2ʼ�ո�Ӧ���壬����ʧ��"},
	{0x5B, "�ϵ�ʱ�����⵽�а�", "�ϵ��ʼ״̬�£��޷��ж�ƽ̨������AB�棬��ʱ����ᱨ��"},

	{0x61, "���ر�������ʧ��", "�ϵ��ȡ�ⲿFLASH����ʧ�ܣ��ָ�ΪĬ�����ã����Ų�Ӳ�����ϡ�"},
	{0x62, "IO��չоƬ���ʧ��", "�ϵ�δ��⵽IO��չоƬ����ȷ�ϰ�Ӳ����������ã��Ƿ��õ���չIO��"},
	{0x63, "��չIO��ȡʧ��", "δ��Ч��ѯ��IO��չ����ڣ�����Ӳ��������"},
	{0x64, "��չIOд��ʧ��", "IO��չ���δ��Чִ�У�����Ӳ��������"},
	{0x71, "�������ź���Ч", "�������Ի����ʱ�����Ի�ͬʱ�����˴����ң����ҵ������źš��������Զ�����"},
	{0x72, "������Чʱ����", "���Ի�δ���������ң����ҵ����źţ��������Ӧ����⵽�а壨�����Զ�����"},
};




CAnalyzeNetwork::CAnalyzeNetwork()
{
	m_nRefreshTime = 100;
	m_bOnTimeExitFlag = false;
	m_hHandleParent = NULL;
	m_hThreadOnTimeUpdate = NULL;
	memset(m_zTagValueBuf, 0, MAX_TAG_LEN);
	memset(m_zAlarmValueBuf, 0, MAX_ALARM_LEN);
	
	m_mapUintTrans.clear();
	m_mapWorkStatusStr.clear();
	m_mapAlarmDetail.clear();
	m_mapTagValueLen.clear();
	InitValueUint();
	InitTagIndexValueMap();
	InitAlarmDetailMap();
	InitWorkStatusStr();

}


CAnalyzeNetwork::~CAnalyzeNetwork()
{
	m_bOnTimeExitFlag = true;
	Sleep(50);
	m_hThreadOnTimeUpdate = NULL;
}

void CAnalyzeNetwork::StopUpdateThread()
{
	if (NULL == m_hThreadOnTimeUpdate)
		return;

	m_bOnTimeExitFlag = true;

	int nCycleTime = 3000;
	DWORD timeSt = 0;
	timeSt = GetTickCount();
	while (NULL != m_hThreadOnTimeUpdate)
	{
		if (GetTickCount() - timeSt < nCycleTime)
		{
			Sleep(20);
			continue;
		}
		else
		{
			DWORD dwCode = 0;
			GetExitCodeThread(m_hThreadOnTimeUpdate, &dwCode);
			if (STILL_ACTIVE == dwCode)
			{
				TerminateThread(m_hThreadOnTimeUpdate, 0);
			}
			m_hThreadOnTimeUpdate = NULL;
		}
	}
}


bool CAnalyzeNetwork::InitConect(char* pAddress, char* pPort, int nRefresh)
{
	m_nRefreshTime = nRefresh;
	if(m_nRefreshTime < 100 || m_nRefreshTime > 5000)
		m_nRefreshTime = 100;

	// ��ͣˢ�¶�ʱ��
	StopUpdateThread();

	m_clientSocket.RegisterNotify(this);
	if(m_clientSocket.InitSocket(pAddress, pPort))
	{
		// ��һ�����ӳɹ�����ȡȫ������
		STSendDataItem stNormalItem;
		GetRequstOntimePack(stNormalItem, EM_ONTIME_NORMAL);
		m_clientSocket.SendRequestData(stNormalItem);

		// ����ʱ��
		GetRequstOntimePack(stNormalItem, EM_GET_TIME_PACK);
		m_clientSocket.SendRequestData(stNormalItem);

		// ��ʱ��ȡ���ݡ�
		m_bOnTimeExitFlag = false;
		m_hThreadOnTimeUpdate = (void*)_beginthread(OnTimeUpdateValue, 0, this);
		SetThreadPriority(m_hThreadOnTimeUpdate, THREAD_PRIORITY_BELOW_NORMAL);

		return true;
	}
	return false;
}


bool CAnalyzeNetwork::GetConnectStatus()
{
	return  m_clientSocket.GetConnectStatus();
}

void CAnalyzeNetwork::RequestRetMsg()
{

	STRevDataItem stDataItem;
	if(!m_clientSocket.PopRevData(stDataItem))
		return;
	
	if(stDataItem.bRcvSuccessFlag && stDataItem.nTagReadOrWrite == 0x01)
	{
		int nCpyCount = stDataItem.nTagEnd - stDataItem.nTagStart + 1;
		// �鿴�Ƿ�Ϊ�澯�ı���
		if(stDataItem.nTagStart >= EM_PRO_ALARM_START)
		{
			int nStartIndex = stDataItem.nTagStart - EM_PRO_ALARM_START;
			memcpy(m_zAlarmValueBuf + nStartIndex, stDataItem.zRevBuf, nCpyCount);
		}

		if(stDataItem.nTagEnd < EM_PRO_TAG_DATA_END)
		{
			int nStartIndex = stDataItem.nTagStart - EM_PRO_TAG_000;
			memcpy(m_zTagValueBuf + nStartIndex, stDataItem.zRevBuf, nCpyCount);
		}
	}

	// ֪ͨ��������ȡ����
	if(m_hHandleParent)
	{
		STRevDataItem* pstDataItem = new STRevDataItem;
		*pstDataItem = stDataItem;
		PostMessage(m_hHandleParent, WM_REV_UPDATE, (WPARAM)pstDataItem, 0);
	}
	
}

int CAnalyzeNetwork::GetSingleTagNeedLength(int nTagValue)
{
	int nRet = -1;
	switch (nTagValue)
	{
	case	EM_PRO_TAG_000:
	case	EM_PRO_TAG_001:
	case	EM_PRO_TAG_002:
	case	EM_PRO_TAG_003:
	case	EM_PRO_TAG_004:
	case	EM_PRO_TAG_007:
	case	EM_PRO_TAG_008:
	case	EM_PRO_TAG_009:
	case	EM_PRO_TAG_010:
	case	EM_PRO_TAG_011:
	case	EM_PRO_TAG_012:
	case	EM_PRO_TAG_013:
	case	EM_PRO_TAG_014:
	case	EM_PRO_TAG_015:
	case	EM_PRO_TAG_016:
	case	EM_PRO_TAG_017:
	case	EM_PRO_TAG_018:
	case	EM_PRO_TAG_019:
	case	EM_PRO_TAG_060:
	case	EM_PRO_TAG_061:
	case	EM_PRO_TAG_062:
	case	EM_PRO_TAG_063:
	case	EM_PRO_TAG_064:
	case	EM_PRO_TAG_100:
	case	EM_PRO_TAG_101:
	case	EM_PRO_TAG_102:
	case	EM_PRO_TAG_103:
	case	EM_PRO_TAG_104:
	case	EM_PRO_TAG_105:
	case	EM_PRO_TAG_106:
	case	EM_PRO_TAG_107:
	case	EM_PRO_TAG_108:
	case	EM_PRO_TAG_185:
	case	EM_PRO_TAG_186:
	case	EM_PRO_TAG_189:
	case	EM_PRO_TAG_190:
	case	EM_PRO_TAG_191:
	case	EM_PRO_TAG_192:
	case	EM_PRO_TAG_193:
	case	EM_PRO_TAG_194:
	case	EM_PRO_TAG_195:
	case	EM_PRO_TAG_196:
	case	EM_PRO_TAG_197:
	case	EM_PRO_TAG_198:
	case	EM_PRO_TAG_199:
	case	EM_PRO_TAG_200:
	case	EM_PRO_TAG_201:
	case	EM_PRO_TAG_202:
	case    EM_PRO_TAG_203:
	case	EM_PRO_TAG_230:
	case	EM_PRO_TAG_231:
	case	EM_PRO_TAG_240:
	case	EM_PRO_TAG_245:
	case	EM_PRO_TAG_236:
	case	EM_PRO_TAG_237:
		nRet = 1;
		break;
	case	EM_PRO_TAG_020:
	//case	EM_PRO_TAG_021:
	case	EM_PRO_TAG_022:
	//case	EM_PRO_TAG_023:
	case	EM_PRO_TAG_024:
	//case	EM_PRO_TAG_025:
	case	EM_PRO_TAG_026:
	//case	EM_PRO_TAG_027:
	case	EM_PRO_TAG_028:
	//case	EM_PRO_TAG_029:
	case	EM_PRO_TAG_030:
	//case	EM_PRO_TAG_031:
	case	EM_PRO_TAG_032:
	//case	EM_PRO_TAG_033:
	case	EM_PRO_TAG_038:
	//case	EM_PRO_TAG_039:
	case	EM_PRO_TAG_040:
	//case	EM_PRO_TAG_041:
	case	EM_PRO_TAG_042:
	//case	EM_PRO_TAG_043:
	case	EM_PRO_TAG_044:
	//case	EM_PRO_TAG_045:
	case	EM_PRO_TAG_046:
	//case	EM_PRO_TAG_047:
	case	EM_PRO_TAG_048:
	//case	EM_PRO_TAG_049:
	case	EM_PRO_TAG_050:
	//case	EM_PRO_TAG_051:
	case	EM_PRO_TAG_052:
	//case	EM_PRO_TAG_053:
	case	EM_PRO_TAG_054:
	//case	EM_PRO_TAG_055:
	case	EM_PRO_TAG_056:
	//case	EM_PRO_TAG_057:
	case	EM_PRO_TAG_058:
	//case	EM_PRO_TAG_059:
	//case	EM_PRO_TAG_107:
	//case	EM_PRO_TAG_108:
	case	EM_PRO_TAG_109:
	//case	EM_PRO_TAG_110:
	case	EM_PRO_TAG_111:
	//case	EM_PRO_TAG_112:
	case	EM_PRO_TAG_113:
	//case	EM_PRO_TAG_114:
	case	EM_PRO_TAG_115:
	//case	EM_PRO_TAG_116:
	case	EM_PRO_TAG_117:
	//case	EM_PRO_TAG_118:
	case	EM_PRO_TAG_119:
	//case	EM_PRO_TAG_120:
	case	EM_PRO_TAG_121:
	//case	EM_PRO_TAG_122:
	case	EM_PRO_TAG_123:
	//case	EM_PRO_TAG_124:
	case	EM_PRO_TAG_125:
	//case	EM_PRO_TAG_126:
	case	EM_PRO_TAG_127:
	//case	EM_PRO_TAG_128:
	case	EM_PRO_TAG_129:
	//case	EM_PRO_TAG_130:
	case	EM_PRO_TAG_131:
	//case	EM_PRO_TAG_132:
	case	EM_PRO_TAG_133:
	//case	EM_PRO_TAG_134:
	case	EM_PRO_TAG_135:
	//case	EM_PRO_TAG_136:
	case	EM_PRO_TAG_137:
	//case	EM_PRO_TAG_138:
	case	EM_PRO_TAG_139:
	//case	EM_PRO_TAG_140:
	case	EM_PRO_TAG_141:
	//case	EM_PRO_TAG_142:
	case	EM_PRO_TAG_143:
	//case	EM_PRO_TAG_144:
	case	EM_PRO_TAG_145:
	//case	EM_PRO_TAG_146:
	case	EM_PRO_TAG_147:
	//case	EM_PRO_TAG_148:
	case	EM_PRO_TAG_149:
	//case	EM_PRO_TAG_150:
	case	EM_PRO_TAG_151:
	//case	EM_PRO_TAG_152:
	case	EM_PRO_TAG_153:
	//case	EM_PRO_TAG_154:
	case	EM_PRO_TAG_155:
	//case	EM_PRO_TAG_156:
	case	EM_PRO_TAG_157:
	//case	EM_PRO_TAG_158:
	case	EM_PRO_TAG_159:
	//case	EM_PRO_TAG_160:
	case	EM_PRO_TAG_161:
	//case	EM_PRO_TAG_162:
	case	EM_PRO_TAG_163:
	//case	EM_PRO_TAG_164:
	case	EM_PRO_TAG_165:
	//case	EM_PRO_TAG_166:
	case	EM_PRO_TAG_167:
	//case	EM_PRO_TAG_168:
	case	EM_PRO_TAG_169:
	//case	EM_PRO_TAG_170:
	case	EM_PRO_TAG_171:
	//case	EM_PRO_TAG_172:
	case	EM_PRO_TAG_173:
	//case	EM_PRO_TAG_174:
	case	EM_PRO_TAG_175:
	//case	EM_PRO_TAG_176:
	case	EM_PRO_TAG_177:
	//case	EM_PRO_TAG_178:
	case	EM_PRO_TAG_179:
	//case	EM_PRO_TAG_180:
	case	EM_PRO_TAG_181:
	//case	EM_PRO_TAG_182:
	case	EM_PRO_TAG_183:
	//case	EM_PRO_TAG_184:
	case	EM_PRO_TAG_187:
	//case	EM_PRO_TAG_188:
	case	EM_PRO_TAG_204:
	//case	EM_PRO_TAG_204:
	case	EM_PRO_TAG_206:
	//case	EM_PRO_TAG_206:
	case	EM_PRO_TAG_208:
	//case	EM_PRO_TAG_208:
	case	EM_PRO_TAG_210:
	//case	EM_PRO_TAG_211:
	case	EM_PRO_TAG_212:
	//case	EM_PRO_TAG_212:
	case	EM_PRO_TAG_214:
	//case	EM_PRO_TAG_214:
	case	EM_PRO_TAG_216:
	//case	EM_PRO_TAG_216:
	case	EM_PRO_TAG_218:
	//case	EM_PRO_TAG_218:
	case	EM_PRO_TAG_232:
	//case	EM_PRO_TAG_233:
	case	EM_PRO_TAG_234:
	//case	EM_PRO_TAG_235:
	case	EM_PRO_TAG_241:
	//case	EM_PRO_TAG_242:
	case	EM_PRO_TAG_243:
	//case	EM_PRO_TAG_244:
		nRet = 2;
		break;
	default:
		nRet = -1;
		break;
	}

	return nRet;
}


double CAnalyzeNetwork::GetTagUint(int nTagValue)
{
	double nRet = 1.0;
	switch (nTagValue)
	{
		//case	EM_PRO_TAG_022:
		//case	EM_PRO_TAG_024:
		//case	EM_PRO_TAG_026:
		case	EM_PRO_TAG_030:
		case	EM_PRO_TAG_032:
		case	EM_PRO_TAG_111:
		case	EM_PRO_TAG_115:
		case	EM_PRO_TAG_119:
		case	EM_PRO_TAG_123:
		case	EM_PRO_TAG_127:
		case	EM_PRO_TAG_131:
		case	EM_PRO_TAG_149:
		case	EM_PRO_TAG_151:
		case	EM_PRO_TAG_161:
		case	EM_PRO_TAG_163:
		case	EM_PRO_TAG_165:
		case	EM_PRO_TAG_167:
		case	EM_PRO_TAG_169:
		case	EM_PRO_TAG_171:
		case    EM_PRO_TAG_191:
		case	EM_PRO_TAG_216:
			nRet = 10.0;
			break;
		case	EM_PRO_TAG_020:
		case	EM_PRO_TAG_028:
		case	EM_PRO_TAG_153:
		case	EM_PRO_TAG_155:
		case	EM_PRO_TAG_157:
		case	EM_PRO_TAG_204:
		case	EM_PRO_TAG_206:
		case	EM_PRO_TAG_208:
		case	EM_PRO_TAG_210:
		case	EM_PRO_TAG_212:
		case	EM_PRO_TAG_159:
		case	EM_PRO_TAG_173:
		case	EM_PRO_TAG_175:
		case	EM_PRO_TAG_177:
		case	EM_PRO_TAG_179:
		case	EM_PRO_TAG_181:
		case	EM_PRO_TAG_183:
			nRet = 100.0;
			break;
		case	EM_PRO_TAG_038:
		case	EM_PRO_TAG_040:
		case	EM_PRO_TAG_042:
		case	EM_PRO_TAG_044:
		case	EM_PRO_TAG_046:
		case	EM_PRO_TAG_048:
		case	EM_PRO_TAG_050:
		case	EM_PRO_TAG_052:
		case	EM_PRO_TAG_054:
		case	EM_PRO_TAG_056:
		case	EM_PRO_TAG_109:
		case	EM_PRO_TAG_113:
		case	EM_PRO_TAG_117:
		case	EM_PRO_TAG_121:
		case	EM_PRO_TAG_125:
		case	EM_PRO_TAG_129:
		case	EM_PRO_TAG_133:
		case	EM_PRO_TAG_135:
		case	EM_PRO_TAG_137:
		case	EM_PRO_TAG_139:
		case	EM_PRO_TAG_141:
		case	EM_PRO_TAG_143:
		case	EM_PRO_TAG_145:
		case	EM_PRO_TAG_147:
		case	EM_PRO_TAG_214:
			nRet = 1000.0;
			break;	
	}

	return nRet;
}

void CAnalyzeNetwork::OnTimeUpdateValue(LPVOID lpParam)
{
	CAnalyzeNetwork* pThis = (CAnalyzeNetwork*)lpParam;
	ASSERT(NULL != pThis);
	if (NULL == pThis)
	{
		return;
	}
	pThis->OnTimeUpdateValue();

	pThis->m_hThreadOnTimeUpdate = NULL;
}

void CAnalyzeNetwork::OnTimeUpdateValue()
{
	// ��ȡ����
	int nFixLen = 5;
	int nIndex = 0;
	int nTagStart = EM_PRO_TAG_007;
	int nTagEnd = EM_PRO_TAG_062;
	STSendDataItem stRequestReadData;
	stRequestReadData.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;	//
	stRequestReadData.SendBuf[nIndex++] = 0x01;
	stRequestReadData.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
	stRequestReadData.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
	stRequestReadData.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
	stRequestReadData.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
	stRequestReadData.nSendLen = nIndex;

	int nCycleTime = m_nRefreshTime;
	// ��ʱ��ȡ��������
	DWORD timeSt = 0;
	timeSt = GetTickCount();
	while(!m_bOnTimeExitFlag)
	{
		if(GetTickCount()-timeSt < nCycleTime)
		{
			Sleep(20);
			continue;
		}
		timeSt = GetTickCount();

		// �������״̬
		if (!m_clientSocket.GetConnectStatus())
		{
			PostMessage(m_hHandleParent, WM_CONNECT_STATUS, 0, 0);
			DEBUG_LOG(EM_LOG_ERROR, "��⵽�����ж�");
			return;
		}

		m_clientSocket.SendRequestData(stRequestReadData);
	}
}

void CAnalyzeNetwork::GetRequstOntimePack(STSendDataItem& stSendDataItem, EM_ONTIME_TYPE emRequestType)
{
	if(EM_ONTIME_ALARM == emRequestType)
	{
		unsigned int nAlarmNum = 0;
		GetIndexValueByTag(EM_PRO_TAG_010, nAlarmNum);

		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_ALARM_START;
		int nTagEnd = EM_PRO_ALARM_START + nAlarmNum*5;			// һ��������5���ֽ�����
		stSendDataItem.nResposeLen = nTagEnd -  nTagStart + nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
	else if(EM_GET_TIME_PACK == emRequestType)
	{
		CTime CurrTime = CTime::GetCurrentTime();
		int nMonth = CurrTime.GetMonth();
		int nDay = CurrTime.GetDay();
		int nHour = CurrTime.GetHour();
		int nMinu = CurrTime.GetMinute();
		int nSec = CurrTime.GetSecond();

		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_TAG_199;
		int nTagEnd = EM_PRO_TAG_203;
		stSendDataItem.nResposeLen = nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0xAA;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nMonth&0xff;
		stSendDataItem.SendBuf[nIndex++] = nDay&0xff;
		stSendDataItem.SendBuf[nIndex++] = nHour&0xff;
		stSendDataItem.SendBuf[nIndex++] = nMinu&0xff;
		stSendDataItem.SendBuf[nIndex++] = nSec&0xff;
		stSendDataItem.nSendLen = nIndex;
	}
	else
	{
		int nIndex = 0;
		int nFixLen = 5;
		int nTagStart = EM_PRO_TAG_000;
		int nTagEnd = EM_PRO_TAG_DATA_END - 1;
		stSendDataItem.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart&0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart>>8&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd&0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd>>8&0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
}



bool CAnalyzeNetwork::SetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf)
{
	return true;
}

bool CAnalyzeNetwork::SetIndexValueByTag(int nTag, int& nValue)
{
	char chTagValue;
	int nValueLen = GetSingleTagNeedLength(nTag);
	if (nValueLen < 1 || nValueLen > 2)
		return false;
	
	memcpy(&m_zTagValueBuf[nTag], &nValue, nValueLen);
	return true;
}

bool CAnalyzeNetwork::GetIndexValueByTag(int nTag, unsigned int& nValue)
{
	if (m_mapTagValueLen.count(nTag) < 1)
	{
		return false; 
	}

	int nValueCount = m_mapTagValueLen[nTag];
	if (nValueCount < 0 || nValueCount > 4)	// nValueCount���ᳬ��2��������һ�����͵Ĵ�С
		return false;

	// ����Խ��
	unsigned int nRetTagValue = 0;
	memcpy(&nRetTagValue, &m_zTagValueBuf[nTag], nValueCount);

	nValue = nRetTagValue;
	return true;
}

bool CAnalyzeNetwork::GetMultiTagValue(int nTagStart, int nDataLen, unsigned char* zDataBuf)
{
	if (nTagStart + nDataLen > MAX_TAG_LEN)
		return false;

	memcpy(zDataBuf, m_zTagValueBuf+nTagStart, nDataLen);
	return true;
}

bool CAnalyzeNetwork::GetStrValueValueByTag(int nTag, CString& strValue)
{
	unsigned int nRetTagValue = 0;
	if (!GetIndexValueByTag(nTag, nRetTagValue))
		return false;

	double dDisValue = 1.0;
	if (m_mapUintTrans.count(nTag) > 0)
		dDisValue = m_mapUintTrans[nTag];

	CString strFormat = L"%.0f";
	if(abs(dDisValue - 10) < 1e-5)
		strFormat = L"%.1f";
	if(abs(dDisValue - 100) < 1e-5)
		strFormat = L"%.2f";
	if(abs(dDisValue - 1000) < 1e-5)
		strFormat = L"%.3f";

	dDisValue = nRetTagValue / dDisValue;
	strValue.Format(strFormat, dDisValue);
	return true;
}

bool CAnalyzeNetwork::SetStrValueValueByTag(int nTag, CString strValue)
{
	unsigned int nRetTagValue = 0;
	double nTagValue = _ttof(strValue);

	int nSetValue = 1;
	if (m_mapUintTrans.count(nTag) > 0)
		nSetValue = m_mapUintTrans[nTag];

	nSetValue = nSetValue * nTagValue;
	if (!SetIndexValueByTag(nTag, nSetValue))
		return false;
	return true;
}

void CAnalyzeNetwork::SynchronizeAlarm2Local(int nQueryNum)
{
	//unsigned int nAlarmNum = 0;
	//GetIndexValueByTag(EM_PRO_TAG_194, nAlarmNum);
	//int nTagStart = EM_PRO_ALARM_START;
	//int nTagEnd = EM_PRO_ALARM_START + nAlarmNum*5;			// һ��������5���ֽ�����

	if(nQueryNum > 100)
		nQueryNum = 100;
	int nTagStart = EM_PRO_ALARM_START;
	int nTagEnd = EM_PRO_ALARM_START + nQueryNum*5;			// һ��������5���ֽ�����
	SynchronizeNetworkData(nTagStart, nTagEnd - 1, 0);
}

bool CAnalyzeNetwork::GetAlarmInfo(int nGetAlarmNum, std::vector<ST_AlarmItemData>& vecAlarmItem)
{
	if(nGetAlarmNum > 100)
		nGetAlarmNum = 100;

	vecAlarmItem.clear();
	for (int i = 0; i < nGetAlarmNum; ++i)
	{
		ST_AlarmItemData stAlarmItemData;
		m_zAlarmValueBuf[i * 5];
		int  nAlarmID = m_zAlarmValueBuf[i * 5 + 4];
		if (nAlarmID ==0)
			continue;
		stAlarmItemData.nAlarmID = nAlarmID;
		stAlarmItemData.strTime.Format(L"%02d-%02d %02d:%02d", m_zAlarmValueBuf[i * 5],
			m_zAlarmValueBuf[i * 5 + 1], m_zAlarmValueBuf[i * 5 + 2], m_zAlarmValueBuf[i * 5 + 3]);

		if (m_mapAlarmDetail.count(nAlarmID) > 0)
		{
			stAlarmItemData.strAlarmMsg = m_mapAlarmDetail[nAlarmID].zStrAlarmMsg;
			stAlarmItemData.strAlarmDetail = m_mapAlarmDetail[nAlarmID].zStrAlarmDetail;
		}

		vecAlarmItem.push_back(stAlarmItemData);
	}
	return true;
}


bool CAnalyzeNetwork::ImportParam(CString strPath)
{
	// ��ȡ�ļ�
	// д���ļ�
	std::ifstream fin(strPath, std::ios_base::in | std::ios_base::binary);
	if(!fin.is_open())
		return false;

	char zTagValueBuf[MAX_TAG_LEN] = {0}; 
	char zReadBuf[50] = {0};

	// �ļ���С ��һλ��У��λ
	int nExpectLen = EM_PRO_TAG_193 - EM_PRO_TAG_100 + 1 + 1;
	fin.seekg(0, fin.end);
	int nBufLen = fin.tellg();
	fin.seekg(0);

	if(nBufLen != nExpectLen || nBufLen >= MAX_TAG_LEN)
	{
		DEBUG_LOG(EM_LOG_ERROR,"�����ļ����Ȳ����� Ԥ��=%d, ʵ��Ϊ=%d   ", nExpectLen, nBufLen);
		return false;
	}
	fin.read(zTagValueBuf, nBufLen);
	fin.close();
	
	// У��У����
	u8 calcCRC[MAX_TAG_LEN] = {0};
	memcpy(calcCRC, zTagValueBuf, nBufLen);
	u8 crcValue = CalcCrc8(calcCRC, nBufLen);
	if(crcValue != (unsigned char)zTagValueBuf[nBufLen])
	{
		DEBUG_LOG(EM_LOG_ERROR,"�����ļ�У����У��ʧ��");
		return false;
	}

	// �������� ����
	// ������У��λ
	memcpy(m_zTagValueBuf + EM_PRO_TAG_100, zTagValueBuf, nBufLen - 1);

	// ͬ�����ݵ������
	if (!GetConnectStatus())
		return false;

	SynchronizeNetworkData(EM_PRO_TAG_100, EM_PRO_TAG_193);
	return true;
}

bool CAnalyzeNetwork::ExportParam(CString strFilePath)
{
	// д��д������ΪEM_PRO_TAG_100 - EM_PRO_TAG_DATA_END
	
	char zTagValueBuf[MAX_TAG_LEN] = {0};
	int nDataLen = EM_PRO_TAG_193 - EM_PRO_TAG_100 + 1;
	memcpy(zTagValueBuf, m_zTagValueBuf + EM_PRO_TAG_100, nDataLen);

	// ����У����
	u8 calcCRC[MAX_TAG_LEN] = {0};
	memcpy(calcCRC, zTagValueBuf, nDataLen);
	u8 crcValue = CalcCrc8(calcCRC, nDataLen);

	// 
	zTagValueBuf[nDataLen] = crcValue;

	// д���ļ�
	std::ofstream fout(strFilePath, std::ios_base::out | std::ios_base::binary);
	if(!fout.is_open())
		return false;

	fout.write(zTagValueBuf, nDataLen + 1);
	fout.close();
	return true;
}

CString CAnalyzeNetwork::GetWorkStatusStr(int nWorkStatus)
{
	if(m_mapWorkStatusStr.count(nWorkStatus) < 1)
		return L"";

	return m_mapWorkStatusStr[nWorkStatus];
}

void CAnalyzeNetwork::SynchronnizationTime()
{
	STSendDataItem stNormalItem;
	GetRequstOntimePack(stNormalItem, EM_GET_TIME_PACK);
	m_clientSocket.SendRequestData(stNormalItem);
}



void CAnalyzeNetwork::SynchronizeNetworkData(int nTagStart, int nTagEnd, int nReadOrWrite)
{
	if (nTagStart > nTagEnd)
		return;

	int nIndex = 0;
	int nFixLen = 5;
	STSendDataItem stSendDataItem;
	if (nReadOrWrite)
	{
		// д������
		stSendDataItem.nResposeLen = nFixLen;	//
		stSendDataItem.SendBuf[nIndex++] = 0xAA;
		stSendDataItem.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
		memcpy(stSendDataItem.SendBuf + nIndex, m_zTagValueBuf + nTagStart, nTagEnd - nTagStart + 1);
		stSendDataItem.nSendLen = nTagEnd - nTagStart + 1 + nIndex;
	}
	else
	{
		// ��ȡ����
		stSendDataItem.nResposeLen = nTagEnd - nTagStart + 1 + nFixLen;	//
		stSendDataItem.SendBuf[nIndex++] = 0x01;
		stSendDataItem.SendBuf[nIndex++] = nTagStart & 0x000000FF;;
		stSendDataItem.SendBuf[nIndex++] = nTagStart >> 8 & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd & 0x000000FF;
		stSendDataItem.SendBuf[nIndex++] = nTagEnd >> 8 & 0x000000FF;
		stSendDataItem.nSendLen = nIndex;
	}
	
	// ����
	m_clientSocket.SendRequestData(stSendDataItem);
}

void CAnalyzeNetwork::InitTagIndexValueMap()
{
	m_mapTagValueLen.clear();

	for (int i = EM_PRO_TAG_000; i < EM_PRO_TAG_MAX; i++)
	{
		int nValue = GetSingleTagNeedLength(i);

		m_mapTagValueLen[i] = nValue;
	}
}

void CAnalyzeNetwork::InitAlarmDetailMap()
{
	m_mapAlarmDetail.clear();
	int nDetailNum = sizeof(g_AlarmDetail)/sizeof(Alarm_Detail);
	for (int i = 0; i < nDetailNum; ++i)
	{
		m_mapAlarmDetail[g_AlarmDetail[i].nAlarmID] = g_AlarmDetail[i];
	}
}

void CAnalyzeNetwork::InitWorkStatusStr()
{
	m_mapWorkStatusStr.clear();
	int nIndex  = 0;
	m_mapWorkStatusStr[nIndex++] = L"�ֶ�ѡ��";
	m_mapWorkStatusStr[nIndex++] = L"�ֶ�����";
	m_mapWorkStatusStr[nIndex++] = L"�ֶ���ת";
	m_mapWorkStatusStr[nIndex++] = L"�ϵ��ʼ";
	m_mapWorkStatusStr[nIndex++] = L"��λ״̬";
	m_mapWorkStatusStr[nIndex++] = L"�쳣״̬";
	m_mapWorkStatusStr[nIndex++] = L"ֹͣ״̬";
	m_mapWorkStatusStr[nIndex++] = L"�ſ���ͣ";
	m_mapWorkStatusStr[nIndex++] = L"����״̬";
	m_mapWorkStatusStr[nIndex++] = L"���״̬";
	m_mapWorkStatusStr[nIndex++] = L"���״̬";
	m_mapWorkStatusStr[nIndex++] = L"��λ״̬";
	m_mapWorkStatusStr[nIndex++] = L"׼������";
	m_mapWorkStatusStr[nIndex++] = L"����״̬";
	m_mapWorkStatusStr[nIndex++] = L"������ת";
	m_mapWorkStatusStr[nIndex++] = L"������ת";
}



void CAnalyzeNetwork::InitValueUint()
{
	m_mapUintTrans.clear();
	for (int i = 0; i < EM_PRO_TAG_DATA_END; ++i)
	{
		int nUint = GetTagUint(i);
		m_mapUintTrans[i] = nUint;
	}
}

void TransBuf2SendFormat(int nSendOrRev, int nTagStart, int nTagEnd, unsigned char* pSendBuf, unsigned char* pOutSendBuf)
{
	int nSendIndex = 0;
	pOutSendBuf[nSendIndex] = 0x01;
	if(nSendOrRev == 0xAA)
		pOutSendBuf[nSendIndex] = 0xAA;
	nSendIndex++;
	pOutSendBuf[nSendIndex++] = nTagStart&0x000000aa;
	pOutSendBuf[nSendIndex++] = (nTagStart>>8)&0x000000aa;
	pOutSendBuf[nSendIndex++] = nTagEnd&0x000000aa;
	pOutSendBuf[nSendIndex++] = (nTagEnd>>8)&0x000000aa;
	memcpy(pOutSendBuf+nSendIndex, pSendBuf, nTagEnd - nTagStart);
}
