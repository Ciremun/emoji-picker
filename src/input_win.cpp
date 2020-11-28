#include <QtWidgets>
#include <qt_windows.h>

#include <iostream>
#include <atomic>

#include "app.hpp"
#include "input_win.hpp"
#include "search.hpp"

HHOOK hHook;
EmojiPicker *instance;
std::atomic<int> block_keystrokes{0};

void updateKeyState(BYTE *keystate, int keycode)
{
    keystate[keycode] = GetKeyState(keycode);
}

LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYUP || !instance->isVisible())
    {
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }

    if (block_keystrokes.load() > 0)
    {
        block_keystrokes -= 1;
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT *)lParam);
    wchar_t buffer[5];
    BYTE keyboard_state[256];

    GetKeyboardState(keyboard_state);
    updateKeyState(keyboard_state, VK_SHIFT);
    updateKeyState(keyboard_state, VK_CAPITAL);
    updateKeyState(keyboard_state, VK_CONTROL);
    updateKeyState(keyboard_state, VK_MENU);

    HKL keyboard_layout = GetKeyboardLayout(0);

    char lpszName[0x100] = {0};

    DWORD dwMsg = 1;
    dwMsg += cKey.scanCode << 16;
    dwMsg += cKey.flags << 24;

    int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);
    int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer, 4, 0, keyboard_layout);

    buffer[4] = L'\0';

    std::wcout << "Key: " << cKey.vkCode << " " << buffer << " " << lpszName << std::endl;

    // enter : cKey.vkCode == 13
    if (cKey.vkCode == 8)
    {
        searchBarInput(instance, lpszName);
    }
    else if (isLetter(cKey.vkCode) || cKey.vkCode == 32 || isNumber(cKey.vkCode))
    {
        char msg[256];
        wcstombs(msg, buffer, 256);
        searchBarInput(instance, msg);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void setKeyboardHook(EmojiPicker *widget)
{
    instance = widget;
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, windowsHookCallback, NULL, 0);
}

void sendInput(const wchar_t *msg, int size)
{
    INPUT inputs[size * 2];
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.dwFlags = KEYEVENTF_UNICODE;

    for (int i = 0; i < size; i++)
    {
        input.ki.wScan = msg[i];
        inputs[i] = input;
    }
    for (int i = 0; i < size; i++)
    {
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        input.ki.wScan = msg[i];
        inputs[i + size] = input;
    }

    block_keystrokes += size;
    SendInput(size * 2, inputs, sizeof(INPUT));
}

void registerHotKey(WId wid)
{
    HWND hwnd = (HWND)wid;
    RegisterHotKey(hwnd, 100, MOD_ALT | MOD_NOREPEAT, 0xBF);
}

void setSpecialWindowState(WId wid)
{
    HWND hwnd = (HWND)wid;
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_NOACTIVATE | WS_EX_APPWINDOW);
}

bool isNumber(int keycode)
{
    return (48 <= keycode && keycode <= 57);
}

bool isLetter(int keycode)
{
    return (65 <= keycode && keycode <= 90);
}
