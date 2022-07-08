#pragma once

#include "win32.h"

/*
 * open_utf16_file - Opens a file and ensures the encoding is UTF-16.
 * @file: A handle pointer which will be assigned to a file hanlde on success.
 * NULL is written on failure.
 * @name: The name of the file.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
DWORD open_utf16_file(HANDLE *const file, const LPCWSTR name);

/*
 * ensure_utf16 - Ensures the encoding is UTF-16.
 * @file: An open file handle.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
DWORD ensure_utf16(const HANDLE file);

/*
 * write_wstr - Writes a wide string to a UTF-16 encoded file.
 * @file: An open file handle.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
DWORD write_wstr(const HANDLE file, const LPCWSTR content);
