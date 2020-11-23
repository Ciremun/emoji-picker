#include <iostream>

#include <QtWidgets>

#include "hotkeys.hpp"

HHOOK hHook;

void updateKeyState(BYTE *keystate, int keycode)
{
    keystate[keycode] = GetKeyState(keycode);
}

LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYUP)
    {
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
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

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void setWindowsKeyboardHook()
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, windowsHookCallback, NULL, 0);
}
