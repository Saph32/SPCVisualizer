#pragma once

#include <windows.h>

#include <memory>

// Source : http://stackoverflow.com/questions/14841396/stdunique-ptr-deleters-and-the-win32-api
struct WndHandleDeleter
{
    typedef HANDLE pointer;

    void operator()(HANDLE h) { ::CloseHandle(h); }
};

typedef std::unique_ptr<HANDLE, WndHandleDeleter> unique_handle;