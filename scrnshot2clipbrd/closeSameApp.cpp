#include <iostream>
#include <windows.h>

template <typename T>
class Win32SharedMem
{
public:
  Win32SharedMem(const char *name, size_t length)
  {
    HANDLE f = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0, sizeof(T) * length,
        name);
    if (f == NULL)
    {
      std::cout << "error: cannot make filemapping" << std::endl;
      return;
    }

    LPVOID map = MapViewOfFile(
        f,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        sizeof(T) * length);
    std::cout << "size" << sizeof(T) * length << std::endl;
    if (map == NULL)
    {
      std::cout << "cannot make mapview of file" << std::endl;
      return;
    }
    this->hMapFile = f;
    this->buffer = map;
    std::cout << "buf" << sizeof(buffer) << std::endl;
  }
  ~Win32SharedMem()
  {
    std::cout << "destruction" << std::endl;
    UnmapViewOfFile(buffer);
    CloseHandle(hMapFile);
  };
  void ShowAll()
  {
    T *p = (T *)this->buffer;
    size_t count = sizeof(this->buffer) / sizeof(T);
    std::cout << count << std::endl;
    for (size_t i = 0; i < count; i++)
    {
      std::cout << i << std::endl;
      std::cout << *p << std::endl;
      p++;
    }
    return;
  };
  T &operator[](size_t index)
  {
    T *p = (T *)buffer;
    for (int i; i < index; i++)
    {
      p++;
    }
    return *p;
  };

private:
  LPVOID buffer;
  HANDLE hMapFile;
};

int main()
{
  Win32SharedMem<int> p("test", 10);
  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  for (size_t i = 0; i < 10; i++)
  {
    std::cout << i;
    std::cout << p[i] << std::endl;
  }

  p.ShowAll();
  tagMSG message;
  while (true)
  {
    std::cout << "in the loop" << std::endl;
    BOOL quite = GetMessage(&message, NULL, 0, 0);
    if (quite)
    {
      break;
    }
    if (message.wParam == 810)
    {
      std::cout << "close pls!!!" << std::endl;
    }
  };
}
