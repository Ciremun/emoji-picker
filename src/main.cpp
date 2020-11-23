#include <QApplication>
#include <QtWidgets>

#include "app.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("conout$","w",stdout);
    QApplication Application(argc, argv);

    QMainWindow window;
    EmojiPicker widget(&window, 340, 310);

    RegisterHotKey((HWND)widget.winId(), 100, MOD_CONTROL | MOD_NOREPEAT, 'E');
    setWindowsKeyboardHook();

    return Application.exec();
}