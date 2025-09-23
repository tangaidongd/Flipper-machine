
// fanbanji.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "fanbanji.h"
#include "fanbanjiDlg.h"
#include "CDialogNetworkMain.h"
#include "dataByCmdDlg.h"
#include "CDialogVersionChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfanbanjiApp

BEGIN_MESSAGE_MAP(CfanbanjiApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CfanbanjiApp ����

CfanbanjiApp::CfanbanjiApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CfanbanjiApp ����

CfanbanjiApp theApp;


// CfanbanjiApp ��ʼ��

BOOL CfanbanjiApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	HANDLE hMutex = ::CreateMutex(NULL, FALSE, L"fanbanji_cus");
	if (NULL == hMutex)
		return false;
	if (ERROR_SUCCESS != GetLastError())
		return false;
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return false;


	// �汾�л�
	CVersionChoice VersionChoice;
	int nVersionType = VersionChoice.GetCfgType();

	CfanbanjiDlg* pDlgSerial = NULL;
	CDialogNetworkMain* pDlgNetwork = NULL;
	INT_PTR nResponse = 0;
	if (nVersionType == 1)
	{
		pDlgNetwork = new CDialogNetworkMain();
		m_pMainWnd = pDlgNetwork;
		nResponse = pDlgNetwork->DoModal();
	}
	else
	{
		pDlgSerial = new CfanbanjiDlg();
		m_pMainWnd = pDlgSerial;
		nResponse = pDlgSerial->DoModal();
	}

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	if (pDlgNetwork)
	{
		delete pDlgNetwork;
		pDlgNetwork = NULL;
	}
	if (pDlgSerial)
	{
		delete pDlgSerial;
		pDlgSerial = NULL;
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

