#include <iostream>
#include <windows.h>

BOOL CALLBACK EnumWindowCallback(HWND hwnd, LPARAM Iparm)
{
  TCHAR buf[1000];
  GetWindowText(hwnd, buf, 1000);
  std::cout << buf << std::endl;

  return true;
}

int main()
{
  EnumWindows(EnumWindowCallback, (LPARAM)NULL);
}
