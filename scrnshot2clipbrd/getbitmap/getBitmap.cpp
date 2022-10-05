#include <windows.h>
#include <wingdi.h>
#include <iostream>
#include <winuser.h>
void setBitmapToCpB(const HANDLE &bmp)
{
  BOOL res = OpenClipboard(NULL);
  std::cout << "res:" << res << std::endl;
  EmptyClipboard();
  SetClipboardData(CF_BITMAP, bmp);
  CloseClipboard();
}

int main()
{
	HWND desktop = GetDesktopWindow();
	RECT windowRect;
	GetWindowRect(desktop, &windowRect);
	int width = windowRect.right;
	int height = windowRect.bottom;

	HDC srcDC = GetDC(desktop);
	HBITMAP bmp = CreateCompatibleBitmap(srcDC, width, height);
	HDC destDC = CreateCompatibleDC(srcDC);
	SelectObject(destDC, bmp);
	BitBlt(destDC, 0, 0, width, height, srcDC, 0, 0, SRCCOPY);
  setBitmapToCpB(bmp);
  std::cout << GetLastError() << std::endl;
  DeleteObject(bmp);
  DeleteObject(destDC);
}
