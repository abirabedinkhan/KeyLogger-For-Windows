cmake_minimum_required(VERSION 3.2)
project(keylogger VERSION 1.3.0 LANGUAGES C)
add_executable(keylogger
    keylogger/util/clipboard.c		keylogger/util/clipboard.h
    keylogger/util/file.c			keylogger/util/file.h
    keylogger/util/keyboard.c		keylogger/util/keyboard.h
    keylogger/util/registry.c		keylogger/util/registry.c
    keylogger/config.h
    keylogger/constants.h
    keylogger/keylogger.c			keylogger/keylogger.h
    keylogger/library.h
    keylogger/main.c
    keylogger/win32.c				keylogger/win32.h
)

target_include_directories(keylogger
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/keylogger
)

target_compile_features(keylogger PRIVATE c_std_11)

target_compile_definitions(keylogger
    PRIVATE
        -_WIN32_WINNT=0x501
        -WINVER=_WIN32_WINNT
        -WIN32_LEAN_AND_MEAN
        -WIN32
        -_WINDOWS
        -_USING_V110_SDK71_
        -_UNICODE
        -UNICODE
)

if(MSVC)
	target_compile_options(keylogger PRIVATE /W4)
else()
	target_compile_options(keylogger PRIVATE -Wall -Wextra -Wpedantic)
endif()
