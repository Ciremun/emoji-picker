#include <QtWidgets>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <iostream>
#include <thread>
#include <sstream>
#include <cstring>

#include "app.hpp"
#include "input_X11.hpp"
#include "search.hpp"

void loopInput(EmojiPicker *widget)
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
            char buffer[32];
            if (event.xkey.keycode == 22)
            {
                strcpy(buffer, "Backspace");
            }
            else
            {
                KeySym ignore;
                Status return_status;
                Xutf8LookupString(xic, &event.xkey, buffer, 32, &ignore, &return_status);
            }
            printf("KeyPress: %s -> %u\n", buffer, event.xkey.keycode);
            searchBarInput(widget, buffer);
            memset(buffer, 0, 32);
            break;
        }
    }
}

void setKeyboardHook(EmojiPicker *widget)
{
    // std::thread *loopInput_t = new std::thread(loopInput, widget);
}

void sendInput(const wchar_t *msg, int size)
{
    Display *display = XOpenDisplay(0);
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
        }

        XTestFakeKeyEvent(display, return_key, true, 0);
        XTestFakeKeyEvent(display, return_key, false, 0);

        XFlush(display);
    }
}

void loopInputHotKey(EmojiPicker *widget)
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
            widget->toggleOnHotKey();
        }
    }
}

void registerHotKey(EmojiPicker *widget)
{
    std::thread *loopInputHotKey_t = new std::thread(loopInputHotKey, widget);
}
