#include <QtWidgets>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <iostream>
#include <thread>
#include <sstream>
#include <cstring>
#include <atomic>

#include "input_X11.hpp"

std::atomic<int> block_keystrokes{0};

void InputThread::setKeyboardHook()
{
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    Window current_focus_window;
    int revert;

    XGetInputFocus(display, &current_focus_window, &revert);
    XSelectInput(display, current_focus_window, KeyPressMask | KeyReleaseMask | FocusChangeMask);
    XIM xim = XOpenIM(display, 0, 0, 0);
    XIC xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);
    XEvent event;
    while (true)
    {
        XNextEvent(display, &event);
        switch (event.type)
        {
        case FocusOut:
            if (current_focus_window != root)
                XSelectInput(display, current_focus_window, 0);
            XGetInputFocus(display, &current_focus_window, &revert);
            if (current_focus_window == PointerRoot)
                current_focus_window = root;
            XSelectInput(display, current_focus_window, KeyPressMask | KeyReleaseMask | FocusChangeMask);
            break;
        case KeyPress:
            if (!widget->isVisible())
                break;
            if (block_keystrokes.load() > 0)
            {
                block_keystrokes -= 1;
                break;
            }
            char buffer[32];
            unsigned int &keycode = event.xkey.keycode;
            if (keycode == 22)
            {
                strcpy(buffer, "Backspace");
            }
            else if (isLetter(keycode) || keycode == 65 || isNumber(keycode))
            {
                KeySym ignore;
                Status return_status;
                Xutf8LookupString(xic, &event.xkey, buffer, 32, &ignore, &return_status);
            }
            else
            {
                break;
            }
            printf("KeyPress: %s -> %u\n", buffer, keycode);
            std::string msgs(buffer);
            emit startSearch(msgs);
            memset(buffer, 0, 32);
            break;
        }
    }
}

void InputThread::registerHotKey()
{
    Display *dpy = XOpenDisplay(0);
    Window root = DefaultRootWindow(dpy);
    XEvent ev;
    XGrabKey(dpy, 61, Mod1Mask, root, 0, GrabModeAsync, GrabModeAsync);
    XSelectInput(dpy, root, KeyPressMask);
    while (true)
    {
        XNextEvent(dpy, &ev);
        if (ev.type == KeyPress)
        {
            emit toggleOnHotKey();
        }
    }
}

void InputThread::setOSHooks(EmojiPicker *widget)
{
    this->widget = widget;
    std::thread *registerHotKey_t = new std::thread(&InputThread::registerHotKey, this);
}

void sendInput(const wchar_t *msg, int size)
{
    Display *display = XOpenDisplay(0);

    std::wcout << L"msg: " << msg << std::endl;

    if (wcscmp(msg, L"Backspace") == 0)
    {
        XTestFakeKeyEvent(display, 22, true, 0);
        XTestFakeKeyEvent(display, 22, false, 0);
        XFlush(display);
        return;
    }

    int total_chars = 0;
    KeyCode u = XKeysymToKeycode(display, XStringToKeysym("u"));

    if (size == 2)
        size -= 1;

    for (int i = 0; i < size; i++)
    {
        unsigned int code = msg[i];

        std::stringstream stream;
        stream << std::hex << code;

        const char *emoji_code = stream.str().c_str();
        size_t emoji_code_len = strlen(emoji_code);

        int ctrl_key = 37;
        int shift_key = 50;
        int return_key = 36;

        XTestFakeKeyEvent(display, ctrl_key, true, 0);
        XTestFakeKeyEvent(display, shift_key, true, 0);
        XTestFakeKeyEvent(display, u, true, 0);

        XTestFakeKeyEvent(display, u, false, 0);
        XTestFakeKeyEvent(display, shift_key, false, 0);
        XTestFakeKeyEvent(display, ctrl_key, false, 0);

        for (int j = 0; j < emoji_code_len; j++)
        {
            char emoji_code_char[2] = {emoji_code[j], '\0'};
            KeyCode emoji_code = XKeysymToKeycode(display, XStringToKeysym(emoji_code_char));
            XTestFakeKeyEvent(display, emoji_code, true, 0);
            XTestFakeKeyEvent(display, emoji_code, false, 0);
            total_chars++;
        }

        XTestFakeKeyEvent(display, return_key, true, 0);
        XTestFakeKeyEvent(display, return_key, false, 0);

        total_chars += 4;

        XFlush(display);
    }
    block_keystrokes += total_chars;
}

bool isLetter(unsigned int keycode)
{
    return (24 <= keycode && keycode <= 33) || (38 <= keycode && keycode <= 46) || (52 <= keycode && keycode <= 58);
}

bool isNumber(unsigned int keycode)
{
    return 10 <= keycode && keycode <= 19;
}
