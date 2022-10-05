#include <iostream>
#include <windows.h>

BOOL CALLBACK EnumWindowCallback(HWND hwnd, LPARAM Iparm)
{
  TCHAR buf[1000];
  GetWindowText(hwnd, buf, 1000);
  MessageBox(NULL, buf, "hoge", MB_OK);
  return true;
}
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine,
    int nCmdShow)
{
  RegisterClass("topsOwnTest");
  
  EnumWindows(EnumWindowCallback, 0);
  return 0;
}
