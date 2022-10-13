#include <iostream>
#include <Windows.h>

bool captureDesktop()
{
  HWND desktop = GetDesktopWindow();
  HDC dc = GetDC(desktop);
  RECT rect;
  GetWindowRect(desktop, &rect);
  int desktopWidth = rect.right;
  int desktopHeight = rect.bottom;
  HBITMAP hoge = CreateCompatibleBitmap(dc, desktopWidth, desktopHeight);
}

int main()
{
  HWND desktop = GetDesktopWindow();
  HWND clipboard;
  bool result = OpenClipboard(clipboard);
  if (!result)
  {
    std::cout << "Cannot open clipboard." << std::endl;
    std::cout
        << "ERRORINFO:\n"
        << GetLastError()
        << std::endl;
    return;
  }
  GlobalLock(clipboard);
}
