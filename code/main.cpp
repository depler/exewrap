#include "winapi.h"

#pragma region STD
void* heap = NULL;

void* malloc(size_t len)
{
    return HeapAlloc(heap, 0, len);
}

void free(void* ptr)
{
    HeapFree(heap, 0, ptr);
}

void* memset(void* dst, int val, size_t len)
{
    unsigned char* ptr = (unsigned char*)dst;

    while (len-- > 0)
        *ptr++ = val;

    return dst;
}

void memcpy(void* dst, const void* src, size_t len)
{
    unsigned char* s = (unsigned char*)src;
    unsigned char* d = (unsigned char*)dst;

    while (len--)
        *d++ = *s++;
}

int memcmp(const void* ptr1, const void* ptr2, size_t count)
{
    unsigned char* s1 = (unsigned char*)ptr1;
    unsigned char* s2 = (unsigned char*)ptr2;

    while (count-- > 0)
    {
        if (*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }

    return 0;
}

void* memmem(const void* haystack, size_t haystack_len, const void* const needle, const size_t needle_len)
{
    if (haystack == NULL || haystack_len == 0)
        return NULL;

    if (needle == NULL || needle_len == 0)
        return NULL;

    for (char* h = (char*)haystack; haystack_len >= needle_len; h++, haystack_len--)
    {
        if (memcmp(h, needle, needle_len) == 0)
            return h;
    }

    return NULL;
}

size_t wcslen(const wchar_t* s)
{
    const wchar_t* p = s;

    while (*p)
        p++;

    return p - s;
}

wchar_t* wcscreate(const wchar_t* src)
{
    size_t size = (wcslen(src) + 1) * sizeof(wchar_t);
    wchar_t* dst = (wchar_t*)malloc(size);
    memcpy(dst, src, size);
    return dst;
}

wchar_t* wcscpy(wchar_t* dst, const wchar_t* src)
{
    wchar_t* cp = dst;
    while ((*cp++ = *src++) != L'\0') {}
    return (dst);
}

wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, size_t n)
{
    if (n != 0)
    {
        wchar_t* d = dst;
        const wchar_t* s = src;

        do
        {
            if ((*d++ = *s++) == L'\0')
            {
                while (--n != 0)
                    *d++ = L'\0';
                break;
            }
        } while (--n != 0);
    }
    return dst;
}

size_t wcsappend(wchar_t* dest, const wchar_t* source, size_t pos)
{
    size_t len = wcslen(source);
    wcsncpy(dest + pos, source, len);
    return len;
}

wchar_t* wcsrchr(const wchar_t* s, wchar_t c)
{
    const wchar_t* last = NULL;

    for (;;)
    {
        if (*s == c)
            last = s;
        if (*s == L'\0')
            break;
        s++;
    }

    return (wchar_t*)last;
}

int wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
    if (n == 0)
        return 0;

    do
    {
        if (*s1 != *s2++)
            return (*(unsigned short*)s1 - *(unsigned short*)--s2);
        if (*s1++ == 0)
            break;
    } while (--n != 0);

    return 0;
}

wchar_t* wcsqtrim(wchar_t* wcs)
{
    while (*wcs == L'"')
        wcs++;

    wchar_t* tail = wcs + wcslen(wcs);
    while (--tail >= wcs)
    {
        if (*tail == L'"')
            *tail = L'\0';
        else
            break;
    }

    return wcs;
}

int wsystem(const wchar_t* command)
{
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(STARTUPINFO);

    wchar_t* pcmd = wcscreate(command);
    bool result = CreateProcessW(NULL, pcmd, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    free(pcmd);

    if (result)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD code;
        result = GetExitCodeProcess(pi.hProcess, &code);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return result ? code : -1;
    }

    return -1;
}
#pragma endregion

#pragma region CODE
wchar_t path_mark[] = L"8A46PXtSYbAbRYUHqV7SKCvwzFBaAkSbfhhgtuzNDeXusfQE6zZGLJmmJun3zrj3";

bool GetModuleFolder(wchar_t* buffer, size_t length)
{
    if (GetModuleFileNameW(NULL, buffer, length) == 0)
        return false;

    wchar_t* delimeter = wcsrchr(buffer, L'\\');
    if (delimeter == NULL)
        return false;

    *delimeter = L'\0';
    return true;
}

wchar_t* GetCommandLineArgs()
{
    wchar_t* wcs = GetCommandLineW();

    if (*wcs == L'"')
    {
        wcs++;
        while (*wcs)
            if (*wcs++ == L'"')
                break;
    }
    else
    {
        while (*wcs && *wcs != L' ' && *wcs != L'\t')
            wcs++;
    }

    while (*wcs == L' ' || *wcs == L'\t')
        wcs++;

    return wcs;
}

size_t ReadFileData(const wchar_t* path, void** buffer)
{
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == NULL)
        return 0;

    size_t fsize = GetFileSize(file, NULL);
    *buffer = malloc(fsize);

    DWORD bytesRead = 0;
    ReadFile(file, *buffer, fsize, &bytesRead, NULL);

    CloseHandle(file);
    return bytesRead;
}

size_t WriteFileData(const wchar_t* path, void* buffer, size_t buffer_length)
{
    HANDLE file = CreateFileW(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == NULL)
        return 0;

    DWORD bytesWritten = 0;
    WriteFile(file, buffer, buffer_length, &bytesWritten, NULL);

    CloseHandle(file);
    return bytesWritten;
}

bool WrapExecutable(const wchar_t* self_folder, const wchar_t* exe_path)
{
    if (self_folder == NULL || wcslen(self_folder) == 0)
        return false;

    if (exe_path == NULL || wcslen(exe_path) == 0)
        return false;

    wchar_t* exe_name = wcsrchr(exe_path, L'\\');
    if (exe_name == NULL)
        return false;

    wchar_t self_exe[MAX_PATH];
    if (!GetModuleFileNameW(NULL, self_exe, MAX_PATH))
        return false;

    void* data = NULL;
    size_t data_length = ReadFileData(self_exe, &data);
    if (data_length == 0)
        return false;

    size_t path_mark_len = wcslen(path_mark) * sizeof(wchar_t);
    wchar_t* mark = (wchar_t*)memmem(data, data_length, path_mark, path_mark_len);
    if (mark == NULL)
        return false;

    memset(mark, 0, path_mark_len);
    wcscpy(mark, exe_path);

    wchar_t other_exe[MAX_PATH] = { 0 };
    size_t pos = 0;

    pos += wcsappend(other_exe, self_folder, pos);
    pos += wcsappend(other_exe, exe_name, pos);

    if (WriteFileData(other_exe, data, data_length) == 0)
        return false;

    return true;
}
#pragma endregion

int main_impl()
{
    wchar_t self_folder[MAX_PATH];
    if (!GetModuleFolder(self_folder, MAX_PATH))
        return 1;

    wchar_t* args = GetCommandLineArgs();
    if (wcslen(args) > 18 && wcsncmp(args, L"--d7k9FxrRM8-wrap", 17) == 0)
    {
        wchar_t* exe_path = wcsqtrim(args + 18);
        return WrapExecutable(self_folder, exe_path) ? 0 : 1;
    }

    wchar_t command[1024] = { 0 };
    size_t pos = 0;

    pos += wcsappend(command, self_folder, pos);
    pos += wcsappend(command, path_mark, pos);
    pos += wcsappend(command, L" ", pos);
    pos += wcsappend(command, args, pos);

    return wsystem(command);
}

void main()
{
    heap = GetProcessHeap();
    int result = main_impl();
    ExitProcess(result);
}