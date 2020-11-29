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
#ifdef _WIN32
    AllocConsole();
    freopen("conout$", "w", stdout);
#endif
    setOSHooks(widget);
    widget->show();
    return Application.exec();
}