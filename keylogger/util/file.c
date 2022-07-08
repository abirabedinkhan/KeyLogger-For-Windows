#include "file.h"

DWORD open_utf16_file(HANDLE *const file, const LPCWSTR name)
{
	DWORD rc;
	HANDLE handle = CreateFile(
		name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		rc = GetLastError();
		goto out;
	}

	rc = ensure_utf16(handle);
out:
	*file = rc ? NULL : handle;
	return rc;
}

DWORD ensure_utf16(const HANDLE file)
{
	static const BYTE UTF16_MAGIC[] = { 0xFF, 0xFE };

	UCHAR buff[2];
	DWORD read;
	BOOL success = LpReadFile(file, buff, 2, &read, NULL);

	if (!success)
		return GetLastError();

	if (!memcmp(buff, UTF16_MAGIC, 2)) {
		LARGE_INTEGER dist = { 0 };
		DWORD res = SetFilePointerEx(file, dist, NULL, FILE_END);

		return res != INVALID_SET_FILE_POINTER ? 0 : GetLastError();
	}

	DWORD count;
	success = WriteFile(file, UTF16_MAGIC, 2, &count, NULL);

	if (!success)
		return GetLastError();
	else if (count != 2)
		return 1;

	return 0;
}

DWORD write_wstr(const HANDLE file, const LPCWSTR content)
{
	DWORD buff_size = wcslen(content) * sizeof(content[0]);
	DWORD count;
	BOOL success = WriteFile(file, content, buff_size, &count, NULL);

	if (count != buff_size)
		return 1;

	return success ? 0 : GetLastError();
}
