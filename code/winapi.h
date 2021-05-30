#pragma once

#define _In_
#define _In_opt_
#define _Inout_
#define _Inout_opt_
#define _Out_
#define _Out_opt_

#define WINAPI
#define WINBASEAPI extern "C" 
#define NULL nullptr
#define VOID void
#define CONST const
#define INFINITE 0xFFFFFFFF
#define MAX_PATH 260
#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define GENERIC_EXECUTE 0x20000000L
#define GENERIC_ALL 0x10000000L
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define FILE_SHARE_READ 0x00000001  
#define FILE_SHARE_WRITE 0x00000002  
#define FILE_SHARE_DELETE 0x00000004
#define FILE_ATTRIBUTE_READONLY 0x00000001  
#define FILE_ATTRIBUTE_HIDDEN 0x00000002  
#define FILE_ATTRIBUTE_SYSTEM 0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020  
#define FILE_ATTRIBUTE_DEVICE 0x00000040  
#define FILE_ATTRIBUTE_NORMAL 0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800  
#define FILE_ATTRIBUTE_OFFLINE 0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM 0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL 0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA 0x00020000  
#define FILE_ATTRIBUTE_EA 0x00040000  
#define FILE_ATTRIBUTE_PINNED 0x00080000  
#define FILE_ATTRIBUTE_UNPINNED 0x00100000  
#define FILE_ATTRIBUTE_RECALL_ON_OPEN 0x00040000  
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000
#define CREATE_NEW 1
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_SESSION_AWARE         0x00800000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

typedef void* HANDLE;
typedef void* PVOID;
typedef void* PVOID;
typedef void* HGLOBAL;
typedef void* HMODULE;
typedef char CHAR;
typedef wchar_t WCHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;
typedef SHORT* PSHORT;
typedef LONG* PLONG;
typedef FLOAT *PFLOAT;
typedef BOOL *PBOOL;
typedef BOOL *LPBOOL;
typedef BYTE *PBYTE;
typedef BYTE *LPBYTE;
typedef int *PINT;
typedef int *LPINT;
typedef WORD *PWORD;
typedef WORD *LPWORD;
typedef long *LPLONG;
typedef DWORD *PDWORD;
typedef DWORD *LPDWORD;
typedef void *LPVOID;
typedef CONST void *LPCVOID;
typedef int INT;
typedef unsigned int UINT;
typedef __int64 INT_PTR, * PINT_PTR;
typedef unsigned __int64 UINT_PTR, * PUINT_PTR;
typedef __int64 LONG_PTR, * PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, * PULONG_PTR;
typedef ULONG_PTR SIZE_T, * PSIZE_T;
typedef LONG_PTR SSIZE_T, * PSSIZE_T;
typedef WCHAR* NWPSTR, * LPWSTR, * PWSTR;
typedef CONST WCHAR* LPCWSTR, * PCWSTR;

typedef struct _STARTUPINFOW {
    DWORD   cb;
    LPWSTR  lpReserved;
    LPWSTR  lpDesktop;
    LPWSTR  lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOW, * LPSTARTUPINFOW;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, * PSECURITY_ATTRIBUTES, * LPSECURITY_ATTRIBUTES;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, * PPROCESS_INFORMATION, * LPPROCESS_INFORMATION;

typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        } DUMMYSTRUCTNAME;
        PVOID Pointer;
    } DUMMYUNIONNAME;

    HANDLE  hEvent;
} OVERLAPPED, * LPOVERLAPPED;

typedef STARTUPINFOW STARTUPINFO;
typedef LPSTARTUPINFOW LPSTARTUPINFO;

WINBASEAPI
BOOL
WINAPI
CreateProcessW(
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation
);

WINBASEAPI
DWORD
WINAPI
WaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds
);

WINBASEAPI
BOOL
WINAPI
GetExitCodeProcess(
    _In_ HANDLE hProcess,
    _Out_ LPDWORD lpExitCode
);

WINBASEAPI
BOOL
WINAPI
CloseHandle(
    _In_ HANDLE hObject
);

WINBASEAPI
HGLOBAL
WINAPI
GlobalAlloc(
    _In_ UINT uFlags,
    _In_ SIZE_T dwBytes
);

WINBASEAPI
HGLOBAL
WINAPI
GlobalFree(
    HGLOBAL hMem
);

WINBASEAPI
HANDLE
WINAPI
GetProcessHeap(
    VOID
);

WINBASEAPI
LPVOID
WINAPI
HeapAlloc(
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes
);

WINBASEAPI
BOOL
WINAPI
HeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    LPVOID lpMem
);

WINBASEAPI
VOID
WINAPI
ExitProcess(
    _In_ UINT uExitCode
);

WINBASEAPI
DWORD
WINAPI
GetModuleFileNameW(
    _In_opt_ HMODULE hModule,
    LPWSTR lpFilename,
    _In_ DWORD nSize
);

WINBASEAPI
LPWSTR
WINAPI
GetCommandLineW(
    VOID
);

WINBASEAPI
DWORD
WINAPI
GetLastError(
    VOID
);

WINBASEAPI
HANDLE
WINAPI
CreateFileW(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile
);

WINBASEAPI
DWORD
WINAPI
GetFileSize(
    _In_ HANDLE hFile,
    _Out_opt_ LPDWORD lpFileSizeHigh
);

WINBASEAPI
BOOL
WINAPI
ReadFile(
    _In_ HANDLE hFile,
    _Out_ LPVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToRead,
    _Out_opt_ LPDWORD lpNumberOfBytesRead,
    _Inout_opt_ LPOVERLAPPED lpOverlapped
);

WINBASEAPI
DWORD
WINAPI
SetFilePointer(
    _In_ HANDLE hFile,
    _In_ LONG lDistanceToMove,
    _Inout_opt_ PLONG lpDistanceToMoveHigh,
    _In_ DWORD dwMoveMethod
);

WINBASEAPI
BOOL
WINAPI
WriteFile(
    _In_ HANDLE hFile,
    _In_ LPCVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToWrite,
    _Out_opt_ LPDWORD lpNumberOfBytesWritten,
    _Inout_opt_ LPOVERLAPPED lpOverlapped
);