
// CVMain.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CVMain.h"
#include "CVMainDlg.h"
#include "mdump.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCVMainApp

BEGIN_MESSAGE_MAP(CCVMainApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCVMainApp 构造

CCVMainApp::CCVMainApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCVMainApp 对象

CCVMainApp theApp;


// CCVMainApp 初始化

BOOL CCVMainApp::InitInstance()
{
	AfxSocketInit();	// 调用 CWinApp::InitInstance 中的重写函数初始化此 Windows 套接字。	#include <afxsock.h>

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	CreateNMLogWriter();

	DWORD id = GetCurrentThreadId();//获取最近线程的ID

	CString strLog;
	strLog.Format(_T("\n-------------------------------------------------CCVMainApp::InitInstance[%d] CV Init v_0.0.0.1 CurrentThread:%d-------------------------------------------------"), __LINE__, id);
	WriteLog(_T("CVMainLog"), logLevelInfo, strLog);

	//自动抓取错误dump
	TCHAR szPath[MAX_PATH];
	//获取应用程序或者DLL的完整路径
	GetModuleFileName(NULL, szPath, MAX_PATH);
	//去掉路径末尾的文件名和反斜杠
	PathRemoveFileSpec(szPath);
	CString strFileName;
	strFileName.Format(_T("%s\\config.ini"), szPath);
	
	DWORD dwDmpKeepDays = GetPrivateProfileInt(_T("DumpInfo"), _T("KeepDays"), 7, strFileName);
	DWORD dwDmpKeepCnt = GetPrivateProfileInt(_T("DumpInfo"), _T("KeepCnt"), 10, strFileName);

	CMiniDumper::SetExceptionFilter(MiniDumpWithFullMemory, dwDmpKeepDays, dwDmpKeepCnt);


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CCVMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
