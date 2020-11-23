#include <QApplication>
#include <QtWidgets>

#include "app.hpp"
#include "hotkeys.hpp"

int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);

    QMainWindow window;
    EmojiPicker widget(&window, 340, 310);

    RegisterHotKeys(&widget);

    widget.show();
    return Application.exec();
}