#include <Windows.h>

HHOOK g_hHook = NULL;

//��װ����
extern "C" __declspec(dllexport) BOOL InstallHook();

// ж�ع���
extern "C" __declspec(dllexport) BOOL UninstallHook();

// ���Ӵ�����
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);