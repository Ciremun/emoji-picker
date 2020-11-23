#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "hotkeys.hpp"

EmojiPicker::EmojiPicker(QWidget *parent, int w, int h)
    : QWidget(parent), window_width(w), window_height(h)
{
    setWindowFlags(Qt::Window
    | Qt::WindowStaysOnTopHint
    | Qt::FramelessWindowHint);
    setFixedSize(QSize(window_width, window_height));
    setWindowTitle("Rushia");
    move(mapFromGlobal(QCursor::pos()));
}

bool EmojiPicker::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    MSG* msg = reinterpret_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY)
    {
        if (0 <= msg->wParam && msg->wParam <= 61)
        {
            std::cout << "Message: " << keys[msg->wParam] << std::endl;
        }
        else if (msg->wParam == 100)
        {
            setPalette(QPalette(QColor("#111111")));
        }
        return true;
    }
    return false;
}