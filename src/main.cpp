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
    setOSHooks(widget);
#else
    qRegisterMetaType<std::string>("std::string");
    QThread keyboard_hook_thread;
    InputThread input_thread;
    QObject::connect(&input_thread, &InputThread::toggleOnHotKey, widget, &EmojiPicker::toggleOnHotKey);
    QObject::connect(&input_thread, &InputThread::startSearch, widget, &EmojiPicker::startSearch);
    QObject::connect(&keyboard_hook_thread, &QThread::started, &input_thread, &InputThread::setKeyboardHook);
    input_thread.setOSHooks(widget);
    input_thread.moveToThread(&keyboard_hook_thread);
    keyboard_hook_thread.start();
#endif
    widget->show();
    return Application.exec();
}
