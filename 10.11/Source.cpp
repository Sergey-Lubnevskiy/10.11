#include <windows.h>
#include "resource.h"
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Êàðêàñíîå ïðèëîæåíèå");
HICON hIcon;
HCURSOR hCursor1, hCursor2;
WNDCLASSEX wcl;
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;

	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // èêîíêà çàãðóæàåòñÿ èç ðåñóðñîâ ïðèëîæåíèÿ	
	wcl.hCursor = NULL;// LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));	// êóðñîð çàãðóæàåòñÿ èç ðåñóðñîâ ïðèëîæåíèÿ	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Ðåñóðñû"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		// ïîëó÷àåì äåñêðèïòîð ïðèëîæåíèÿ
		HINSTANCE hInstance = GetModuleHandle(0);
		// çàãðóæàåì èêîíêó èç ðåñóðñîâ ïðèëîæåíèÿ
	   // çàãðóæàåì êóðñîðû èç ðåñóðñîâ ïðèëîæåíèÿ
		hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
	}
	break;

	case WM_MOUSEMOVE:
	{
		// óñòàíàâëèâàåì òîò èëè èíîé êóðñîð â çàâèñèìîñòè îò ìåñòîíàõîæäåíèÿ óêàçàòåëÿ ìûøè
		RECT rect;

		GetClientRect(hWnd, &rect);

		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (x >= rect.right / 2)
			SetCursor(hCursor1);
		else
			SetCursor(hCursor2);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}