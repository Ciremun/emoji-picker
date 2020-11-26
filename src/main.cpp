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
    #ifdef _WIN32
    AllocConsole();
    freopen("conout$","w",stdout);
    #endif
    QApplication Application(argc, argv);
    QFrame window;
    EmojiPicker widget(&window, 330, 360);

    WId wid = widget.winId();

    setKeyboardHook();
    registerHotKey(wid);
    setSpecialWindowState(wid);
    widget.show();
    return Application.exec();
}