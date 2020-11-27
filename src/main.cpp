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
    EmojiPicker widget(&window, 330, 360);

    WId wid = widget.winId();

    setKeyboardHook();
    #ifdef _WIN32
    AllocConsole();
    freopen("conout$","w",stdout);
    registerHotKey(wid);
    setSpecialWindowState(wid);
    #endif
    widget.show();
    return Application.exec();
}