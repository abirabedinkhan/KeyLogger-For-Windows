#include "constants.h"
#include "registry.h"

/*
* All conversions from LONG to DWORD are safe as all Windows error codes are
* unsigned. You can thank them for the inconsistency.
*/
DWORD add_to_startup(VOID)
{
	HKEY hkey;
	DWORD rc = LpRegCreateKeyEx(HKEY_CURRENT_USER, LP_SUB_KEY, 0, NULL,
				    REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
				    &hkey, NULL);
	if (rc)
		goto out;

	WCHAR exe_path[MAX_PATH];
	const DWORD written = GetModuleFileName(NULL, exe_path, MAX_PATH);

	if (!written) {
		rc = GetLastError();
		goto close;
	}

	rc = LpRegSetValueEx(hkey, NULL, 0, REG_SZ, (BYTE*)exe_path,
			     (written + 1) * sizeof(WCHAR));
close:
	LpRegCloseKey(hkey);
out:
	return rc;
}
