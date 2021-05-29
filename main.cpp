#include <Windows.h>
#include <wchar.h>
#include <stdio.h>

wchar_t path_mark[] = L"8A46PXtSYbAbRYUHqV7SKCvwzFBaAkSbfhhgtuzNDeXusfQE6zZGLJmmJun3zrj3";

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

bool GetModuleFolder(wchar_t* buffer, size_t length)
{
    if (GetModuleFileName(NULL, buffer, length) == 0)
        return false;

    wchar_t* delimeter = wcsrchr(buffer, L'\\');
    if (delimeter == NULL)
        return false;

    *delimeter = L'\0';
    return true;
}

wchar_t* GetCommandLineArgs()
{
    wchar_t* wcs = GetCommandLine();

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

size_t AppendData(wchar_t* dest, const wchar_t* source, size_t pos)
{
    size_t len = wcslen(source);
    wcsncpy(dest + pos, source, len);
    return len;
}

size_t ReadFile(const wchar_t* path, void** buffer)
{
    FILE* f = _wfopen(path, L"rb");
    if (f == NULL)
        return -1;
    
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    *buffer = new unsigned char[fsize];

    fseek(f, 0, SEEK_SET);
    fread(*buffer, 1, fsize, f);
    fclose(f);

    return fsize;
}

size_t WriteFile(const wchar_t* path, void* buffer, size_t buffer_length)
{
    FILE* f = _wfopen(path, L"wb");
    if (f == NULL)
        return -1;

    size_t fsize = fwrite(buffer, 1, buffer_length, f);
    fclose(f);

    return fsize;
}

bool WrapExecutable(const wchar_t* self_folder, const wchar_t* exe_path)
{
    wchar_t self_exe[MAX_PATH];
    if (!GetModuleFileName(NULL, self_exe, MAX_PATH))
        return false;

    void* data = NULL;
    size_t data_length = ReadFile(self_exe, &data);
    if (data_length < 0)
        return false;

    size_t path_mark_len = wcslen(path_mark) * sizeof(wchar_t);
    wchar_t* mark = (wchar_t*)memmem(data, data_length, path_mark, path_mark_len);
    if (mark == NULL)
        return false;

    memset(mark, 0, path_mark_len);
    wcscpy(mark, exe_path);

    wchar_t* exe_name = wcsrchr((wchar_t*)exe_path, L'\\');
    if (exe_name == NULL)
        return false;

    wchar_t other_exe[MAX_PATH] = { 0 };
    size_t pos = 0;

    pos += AppendData(other_exe, self_folder, pos);
    pos += AppendData(other_exe, exe_name, pos);

    if (WriteFile(other_exe, data, data_length) < 0)
        return false;

    return true;
}

int wmain(int argc, wchar_t* argv[])
{
    wchar_t self_folder[MAX_PATH];
    if (!GetModuleFolder(self_folder, MAX_PATH))
        return 1;   

    if (argc == 3 && wcscmp(argv[1], L"--d7k9FxrRM8-wrap") == 0)
        return WrapExecutable(self_folder, argv[2]) ? 0 : 1;        

    wchar_t* args = GetCommandLineArgs();
    wchar_t command[1024] = { 0 };
    size_t pos = 0;

    pos += AppendData(command, self_folder, pos);
    pos += AppendData(command, path_mark, pos);
    pos += AppendData(command, L" ", pos);
    pos += AppendData(command, args, pos);

    return _wsystem(command);
}
