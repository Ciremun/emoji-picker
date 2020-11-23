#include <iostream>

#include <QtWidgets>
#include "winuser.h"

#include "hotkeys.hpp"

char keys[] = {
    '1','2','3','4','5','6','7','8','9','0',
    'q','w','e','r','t','y','u','i','o','p',
    'a','s','d','f','g','h','j','k','l',
    'z','x','c','v','b','n','m',
    'Q','W','E','R','T','Y','U','I','O','P',
    'A','S','D','F','G','H','J','K','L',
    'Z','X','C','V','B','N','M'
};

size_t keys_size = sizeof(keys) / sizeof(keys[0]);

void RegisterHotKeys(QWidget *widget)
{
    AllocConsole();
    freopen("conout$","w",stdout);
    HWND hWnd = (HWND)widget->winId();
    RegisterHotKey(hWnd, 100, MOD_CONTROL | MOD_NOREPEAT, 'E');
    UINT fsModifiers = NULL;
    for (int i = 0; i < keys_size; i++)
    {
        char key = keys[i];
        if (10 <= i && i <= 35)
        {
            key = toupper(key);
        }
        else if (36 <= i && i <= 61)
        {
            fsModifiers = MOD_SHIFT;
        }
        RegisterHotKey(hWnd, i, fsModifiers, key);
        std::cout << "Register hotkey " << key << " with id " << i << std::endl;
    }
}