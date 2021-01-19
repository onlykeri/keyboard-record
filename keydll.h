#include <Windows.h>

HHOOK g_hHook = NULL;

//安装钩子
extern "C" __declspec(dllexport) BOOL InstallHook();

// 卸载钩子
extern "C" __declspec(dllexport) BOOL UninstallHook();

// 钩子处理函数
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);