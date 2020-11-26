#include <iostream>
#include <QtWidgets>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <chrono>
#include <thread>
#include "input_X11.hpp"

void loopInput()
{
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    Window current_focus_window;
    int revert;

    XGetInputFocus(display, &current_focus_window, &revert);
    XSelectInput(display, current_focus_window, KeyPressMask | KeyReleaseMask | FocusChangeMask);
    XIM xim = XOpenIM(display, 0, 0, 0);
    XIC xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);
    while (true)
    {
        XEvent event;
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
            KeySym ignore;
            Status return_status;
            Xutf8LookupString(xic, &event.xkey, buffer, 32, &ignore, &return_status);
            printf("KeyPress: %s\n", buffer);
            break;
        }
    }
}

void setKeyboardHook()
{
    std::thread *t1 = new std::thread(loopInput);
}

void sendInput(const wchar_t *msg, int size)
{
}

void registerHotKey(WId wid)
{
}

void setSpecialWindowState(WId wid)
{
}
