#include <QApplication>
#include <QtWidgets>

#include "app.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("conout$","w",stdout);
    QApplication Application(argc, argv);
    QFrame window;
    EmojiPicker widget(&window, 330, 360);

    HWND hwnd = (HWND)widget.winId();
    RegisterHotKey(hwnd, 100, MOD_WIN | MOD_NOREPEAT, 0xBF);
    setWindowsKeyboardHook();
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE)
        | WS_EX_NOACTIVATE | WS_EX_APPWINDOW);

    return Application.exec();
}