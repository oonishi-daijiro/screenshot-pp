#include <Windows.h>
#include <iostream>
#include "clipboard/clipboard.hpp"
#include "screenshot/screenshot.hpp"
#include "win32SharedMem/win32SharedMem.cpp"

#define CAPTURE 810
#define QUIT 26

void registarHotkey()
{
	RegisterHotKey(NULL, CAPTURE, MOD_ALT, VK_SNAPSHOT);
}

HWND setupWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND own = CreateWindow(
			TEXT("STATIC"), TEXT("scrnshot2clipbrd"),
			SW_HIDE,
			0, 0, 0, 0, NULL, NULL,
			hInstance, NULL);
	return own;
}

int WINAPI WinMain(
		HINSTANCE hInstanc,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow)
{
	HWND own = setupWindow();
	SharedMemory<HWND> simultaneousWindow = SharedMemory<HWND>("simultaneous_screenshotpp");

	if (!simultaneousWindow.isOwnner())
	{
		int isRequiredClose = MessageBox(NULL, TEXT("This application is already launched. Wanna close?"), TEXT("Notification"), MB_YESNO | MB_ICONQUESTION);
		if (isRequiredClose == IDYES)
		{
			HWND simultaneousWindowHandle = (HWND)simultaneousWindow;
			PostMessage(simultaneousWindowHandle, WM_CLOSE, QUIT, 0);
		}
		return 0;
	}
	simultaneousWindow = own;

	registarHotkey();
	tagMSG message;
	while (true)
	{
		BOOL quit = GetMessage(&message, NULL, 0, 0);
		printf("message:%d", message.wParam);
		if (quit == WM_QUIT || quit == -1)
		{
			break;
		}

		if (message.wParam == CAPTURE)
		{
			HBITMAP screenshot = Screenshot::Capture();
			Clipboard::Write(screenshot);
		}
		if (message.wParam == QUIT)
		{
			break;
		}
		DispatchMessage(&message);
	}
	UnregisterHotKey(NULL, CAPTURE);
	return 0;
}
