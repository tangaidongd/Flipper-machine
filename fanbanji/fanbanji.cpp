
// fanbanji.cpp : 定义应用程序的类行为。
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


// CfanbanjiApp 构造

CfanbanjiApp::CfanbanjiApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CfanbanjiApp 对象

CfanbanjiApp theApp;


// CfanbanjiApp 初始化

BOOL CfanbanjiApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	HANDLE hMutex = ::CreateMutex(NULL, FALSE, L"fanbanji_cus");
	if (NULL == hMutex)
		return false;
	if (ERROR_SUCCESS != GetLastError())
		return false;
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return false;


	// 版本切换
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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
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

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

