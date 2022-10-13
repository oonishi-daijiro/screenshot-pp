#include <windows.h>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
class SharedMemory
{
public:
    SharedMemory(const char *name) : name(name), bufSize(sizeof(T))
    {
        static_assert(std::is_pod<T>::value, "Cannot share non POD data and pointer");
        if (isAlreadyExist())
        {
            openSharedMemory();
        }
        else
        {
            createSharedMemory();
            this->isCreatedFirst = true;
        }
    }
    SharedMemory<T> &operator=(const T &value)
    {
        CopyMemory(this->buffer, (void *)(&value), this->bufSize);
        return *this;
    }
    explicit virtual operator T()
    {
        return *(this->buffer);
    }
    bool isOwnner()
    {
        return this->isCreatedFirst;
    }
    template <typename S>
    friend std::ostream &operator<<(std::ostream &stream, const SharedMemory<S> &value);
    ~SharedMemory()
    {
        CloseHandle(this->sharedMemFileMapping);
        UnmapViewOfFile((void *)this->buffer);
        ReleaseMutex(this->mutex);
    }

protected:
    bool isCreatedFirst = false;
    HANDLE mutex;
    T *buffer;
    HANDLE sharedMemFileMapping;
    const size_t bufSize;
    const char *name;

    SharedMemory(const char *name, size_t length) : name(name), bufSize(sizeof(T) * length)
    {
        if (isAlreadyExist())
        {
            openSharedMemory();
        }
        else
        {
            createSharedMemory();
        }
    }

    void createSharedMemory()
    {
        HANDLE hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            this->bufSize,
            this->name);

        this->sharedMemFileMapping = hMapFile;
        LPVOID mappingFile = MapViewOfFile(
            hMapFile,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            this->bufSize);
        this->buffer = (T *)mappingFile;
        return;
    }

    void openSharedMemory()
    {
        HANDLE hMapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            FALSE,
            this->name);

        LPVOID mappingFile = MapViewOfFile(
            hMapFile,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            this->bufSize);

        this->sharedMemFileMapping = hMapFile;
        this->buffer = (T *)mappingFile;

        return;
    }

    bool isAlreadyExist()
    {
        std::string mutexName = std::string("EXISTENCE_IDENTIFIER_") + std::string(this->name);
        HANDLE mutex = CreateMutex(NULL, TRUE, mutexName.c_str());
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return true;
        }
        this->mutex = mutex;
        return false;
    }
};
template <typename T>
class SharedMemoryArray : public SharedMemory<T>
{
public:
    SharedMemoryArray(const char *name, size_t length) : SharedMemory<T>(name, length){};
    T &operator[](const size_t index)
    {
        return this->buffer[index];
    }
    explicit operator T *() override
    {
        return this->buffer;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, const SharedMemory<T> &value)
{
    stream << *value.buffer;
    return stream;
}
