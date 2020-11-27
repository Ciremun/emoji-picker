#include <QApplication>
#include <QtWidgets>

#include "app.hpp"
#ifdef _WIN32
#include "input_win.hpp"
#else
#include "input_X11.hpp"
#endif

int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);
    QFrame window;
    EmojiPicker *widget = new EmojiPicker(&window, 330, 360);

    setKeyboardHook();
#ifdef _WIN32
    AllocConsole();
    freopen("conout$", "w", stdout);
    WId wid = widget.winId();
    registerHotKey(wid);
    setSpecialWindowState(wid);
#else
    registerHotKey(widget);
#endif
    widget->show();
    return Application.exec();
}