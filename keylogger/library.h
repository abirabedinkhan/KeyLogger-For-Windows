#pragma once

#include "win32.h"

struct library {
	const HMODULE module;
	FARPROC *const function;
	const LPCSTR name;
};
