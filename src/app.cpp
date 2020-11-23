#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "input.hpp"

EmojiPicker::EmojiPicker(QWidget *parent, int w, int h)
    : QWidget(parent), window_width(w), window_height(h)
{
    setWindowFlags(Qt::Window
    | Qt::WindowStaysOnTopHint
    | Qt::FramelessWindowHint);
    setFixedSize(QSize(window_width, window_height));
    setWindowTitle("Rushia");
}

bool EmojiPicker::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    MSG* msg = reinterpret_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY)
    {
        if (msg->wParam == 100)
        {
            if (isVisible())
            {
                hide();
            }
            else
            {
                QPoint point = QCursor::pos();
                point.setY(point.y() - window_height);
                move(point);
                show();
            }
        }
        return true;
    }
    return false;
}