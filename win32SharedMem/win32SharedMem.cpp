#pragma once
#include <Windows.h>
#include <iostream>

template <typename T>

class Win32SharedMem
{
public:
    Win32SharedMem(const char *name, size_t length);
    T &operator[](size_t index);
    ~Win32SharedMem();
    size_t GetUsers();

private:
    LPVOID buffer;
    HANDLE hMapFile;
    size_t users;
};

template <typename T>
Win32SharedMem<T>::Win32SharedMem(const char *name, size_t length)
{
    DWORD size = (sizeof(T) * length) + sizeof(size_t);
    HANDLE f = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0, size,
        name);
    LPVOID buf = MapViewOfFile(
        f,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        size);
    size_t user = (size_t)buf;
    LPVOID fmap = user++;
    this->hMapFile = f;
    this->buffer = fmap;
};

template <typename T>
T &Win32SharedMem<T>::operator[](size_t index)
{
    T *p = (T *)buffer;

    for (size_t i = 0; i < index; ++i)
    {
        p++;
    }
    return *p;
};

template <typename T>
Win32SharedMem<T>::~Win32SharedMem()
{
    UnmapViewOfFile(buffer);
    CloseHandle(hMapFile);
}
