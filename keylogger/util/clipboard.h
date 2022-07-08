#pragma once

#include "win32.h"

/*
 * write_clipboard_data - Writes the current clipboard data to the provided
 * file.
 * @file: A handle to the file in which the clipboard data will be written.
 *
 * Returns zero if successful. On error, returns a non-zero error code.
 */
DWORD write_clipboard_data(const HANDLE file);
