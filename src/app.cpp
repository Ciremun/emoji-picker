#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "emojis.hpp"
#include "tab.hpp"

EmojiPicker::EmojiPicker(QFrame *parent, int w, int h)
    : QFrame(parent), window_width(w), window_height(h)
{
    setObjectName("MainFrame");
    setStyleSheet(" "
                  "#MainFrame {"
                  "   border-color: #323338;"
                  "   border-width: 1.2px;"
                  "   border-style: inset;"
                  "   background-color: #111111;"
                  "}"
                  "QPushButton {border: none;}"
                  "QPushButton:hover {background-color: #474747;}"
                  "* {background: #333333; border:none;}");

    QIcon closeIcon = style()->standardIcon(QStyle::SP_TitleBarCloseButton);
    QPushButton *close_button = new QPushButton();
    close_button->setFixedSize(32, 32);
    close_button->setStyleSheet(" "
                                "QPushButton {background-color: #111111;}"
                                "QPushButton:hover {background-color: #cc0c1c;}");
    close_button->setIcon(closeIcon);
    connect(close_button, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addWidget(close_button, 0, Qt::AlignRight);

    QLabel *label = new QLabel();
    label->setFont(QFont("Arial", 11));
    label->setText("Emoji - Keep typing to find an emoji");
    label->setContentsMargins(15, 0, 0, 10);
    label->setStyleSheet("QLabel{color: #969696; background-color: #111111;}");
    main_layout->addWidget(label);

    QHBoxLayout *tabs = new QHBoxLayout();
    tabs->setSpacing(0);
    tabs->setContentsMargins(8, 0, 0, 0);

    QString tab_button_style = " "
                               "QPushButton {color: #ffffff; background-color: #111111;}"
                               "QPushButton:hover {color: #026fc5; background-color: #282828;}";

    QPushButton *tab_button_1 = new QPushButton(":)");
    tab_button_1->setFixedSize(40, 40);
    tab_button_1->setFont(QFont("Arial", 13));
    tab_button_1->setStyleSheet(tab_button_style);
    Tab *tab_1 = new Tab(tab_button_1, label, "Emoji - Keep typing to find an emoji", emojis, 38, 38, 14);
    tabs->addWidget(tab_button_1);

    QPushButton *tab_button_2 = new QPushButton(";-)");
    tab_button_2->setFixedSize(40, 40);
    tab_button_2->setFont(QFont("Arial", 13));
    tab_button_2->setStyleSheet(tab_button_style);
    Tab *tab_2 = new Tab(tab_button_2, label, "Kaomoji", kaomoji, 100, 40, 11, false);
    tabs->addWidget(tab_button_2);

    tabs->addStretch();
    main_layout->addLayout(tabs);

    main_layout->addLayout(tab_1->centralLayout);
    main_layout->addLayout(tab_2->centralLayout);
    connect(tab_1->tab_button, &QPushButton::pressed, this, [tab_1, tab_2] { tab_2->hide(); tab_1->show(); });
    connect(tab_2->tab_button, &QPushButton::pressed, this, [tab_1, tab_2] { tab_1->hide(); tab_2->show(); });

    setLayout(main_layout);

    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setFixedSize(QSize(window_width, window_height));
    setAttribute(Qt::WA_ShowWithoutActivating);
}

bool EmojiPicker::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

#ifdef _WIN32
    MSG *msg = reinterpret_cast<MSG *>(message);

    if (msg->message == WM_HOTKEY)
    {
        if (msg->wParam == 100)
            toggleOnHotKey();
        return true;
    }
#endif
    return false;
}

void EmojiPicker::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void EmojiPicker::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX() - m_nMouseClick_X_Coordinate, event->globalY() - m_nMouseClick_Y_Coordinate);
}

void EmojiPicker::toggleOnHotKey()
{
    if (isVisible())
    {
        hide();
    }
    else
    {
        QPoint mouse = QCursor::pos();
        QSize screen_size = QGuiApplication::screenAt(mouse)->size();
        QPoint window_corner(mouse.x() + window_width, mouse.y() - window_height);
        if (window_corner.x() > screen_size.width())
            mouse.setX(mouse.x() - window_width);
        if (window_corner.y() > 0)
            mouse.setY(mouse.y() - window_height);
        move(mouse);
        show();
    }
}