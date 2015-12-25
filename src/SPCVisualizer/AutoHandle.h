#pragma once

#include <windows.h>

class AutoHandle {
  public:
    AutoHandle() {}
    AutoHandle(HANDLE handle) : m_handle(handle) {}
    ~AutoHandle() {
        if (m_handle) {
            ::CloseHandle(m_handle);
        }
    }

    operator HANDLE() const { return m_handle; }

    HANDLE Get() const { return m_handle; }
    void Set(HANDLE handle) { m_handle = handle; }

  private:
    HANDLE m_handle = 0;
};
