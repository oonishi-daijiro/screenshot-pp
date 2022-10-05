#include <Windows.h>
#include <iostream>
#include "clipboard/clipboard.hpp"
#include "screenshot/screenshot.hpp"
#include "win32SharedMem/win32SharedMem.cpp"

#define CAPTURE 810
#define QUIT 26

void registarHotkey()
{
	RegisterHotKey(NULL, 810, MOD_SHIFT, VK_SNAPSHOT);
}

void setupWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND own = CreateWindow(
			TEXT("STATIC"), TEXT("scrnshot2clipbrd"),
			SW_HIDE,
			0, 0, 0, 0, NULL, NULL,
			hInstance, NULL);
	return;
}

int WINAPI WinMain(
		HINSTANCE hInstanc,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow)
{
	setupWindow();
	registarHotkey();
	tagMSG message;
	while (true)
	{
		BOOL quit = GetMessage(&message, NULL, 0, 0);
		if (quit == WM_QUIT)
		{
			break;
		}
		else if (quit == -1)
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
	return 0;
}
