#include "screenshot.hpp"


HBITMAP Screenshot::Capture() {
	HWND desktop = GetDesktopWindow();
	HDC hdc = GetDC(desktop);
	RECT windowRect;
	GetWindowRect(desktop, &windowRect);
	int width = windowRect.right;
	int height = windowRect.bottom;
	HDC srcDC = GetDC(desktop);
	HBITMAP bmp = CreateCompatibleBitmap(srcDC, width, height);
	HDC destDC = CreateCompatibleDC(srcDC);
	SelectObject(destDC, bmp);
	BitBlt(destDC, 0, 0, width, height, srcDC, 0, 0, SRCCOPY);
	DeleteDC(destDC);
	DeleteDC(hdc);
	return bmp;
}

void Screenshot::Save(std::string filePath,HBITMAP &data) {
	CImage img;
	img.Attach(data);
	img.Save(filePath.c_str());
	img.Detach();
	return;
}
