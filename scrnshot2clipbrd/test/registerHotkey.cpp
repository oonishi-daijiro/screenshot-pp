#include <iostream>
#include <Windows.h>

int main()
{
  HANDLE mutex = CreateMutexA(NULL, TRUE, "registerKey");
  if (GetLastError() == ERROR_ALREADY_EXISTS)
  {
    std::cout << "" << std::endl;
    ReleaseMutex(mutex);
    CloseHandle(mutex);
    return 0;
  }
  RegisterHotKey(NULL, 810, MOD_SHIFT, VK_SNAPSHOT);
  RegisterHotKey(NULL, 1919, MOD_SHIFT | MOD_ALT, VK_SNAPSHOT);
  tagMSG message;
  while (true)
  {
    BOOL quit = GetMessage(&message, NULL, 0, 0);
    if (quit == WM_QUIT)
    {
      break;
    }
    if (message.wParam == 810)
    {
      std::cout << "printScreen and shift detected" << std::endl;
    }
    else if (message.wParam == 1919)
    {
      UnregisterHotKey(NULL, 810);
      UnregisterHotKey(NULL, 1919);
      return 0;
    }
    DispatchMessage(&message);
  }
  UnregisterHotKey(NULL, 810);
  ReleaseMutex(mutex);
  CloseHandle(mutex);
  return 0;
}
