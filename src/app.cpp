#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "emojis.hpp"
#include "search.hpp"

EmojiPicker::EmojiPicker(QFrame *parent, int w, int h)
    : QFrame(parent), window_width(w), window_height(h), current_tab(nullptr)
{
    setWindowTitle("Rushia - emoji picker");
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

    QFont label_font = QFont("Arial");
    label_font.setPixelSize(15);

    label = new QLabel();
    label->setFont(label_font);
    label->setText("Emoji - Keep typing to find an emoji");
    label->setContentsMargins(15, 0, 0, 10);
    label->setStyleSheet("QLabel{color: #969696; background-color: #111111;}");
    main_layout->addWidget(label);

    search_query = new QLabel();
    search_query->hide();

    emojis_found = new QLabel();
    emojis_found->setFont(label_font);
    emojis_found->setContentsMargins(15, 0, 0, 10);
    emojis_found->setStyleSheet("QLabel{background-color: #111111; color: #ffffff;}");
    emojis_found->hide();
    main_layout->addWidget(emojis_found);

    QHBoxLayout *tabs_layout = new QHBoxLayout();
    tabs_layout->setSpacing(0);
    tabs_layout->setContentsMargins(8, 0, 0, 0);

    QString tab_button_style = " "
                               "QPushButton {color: #ffffff; background-color: #111111;}"
                               "QPushButton:hover {color: #026fc5; background-color: #282828;}";

    QPushButton *tab_button_1 = new QPushButton(":)");
    tab_button_1->setFixedSize(40, 40);
    tab_button_1->setFont(QFont("Arial", 13));
    tab_button_1->setStyleSheet(tab_button_style);
    Tab *tab_1 = new Tab(tab_button_1, label, "Emoji - Keep typing to find an emoji", emojis, true);
    tabs_layout->addWidget(tab_button_1);

    QPushButton *tab_button_2 = new QPushButton(";-)");
    tab_button_2->setFixedSize(40, 40);
    tab_button_2->setFont(QFont("Arial", 13));
    tab_button_2->setStyleSheet(tab_button_style);
    Tab *tab_2 = new Tab(tab_button_2, label, "Kaomoji", kaomoji);
    tabs_layout->addWidget(tab_button_2);

    search_tab = new SearchTab(search_query);

    tabs = {tab_1, tab_2};
    tab_buttons = {tab_button_1, tab_button_2};
    current_tab = tab_1;

    tabs_layout->addStretch();
    main_layout->addLayout(tabs_layout);

    main_layout->addLayout(tab_1->centralLayout);
    main_layout->addLayout(tab_2->centralLayout);
    main_layout->addLayout(search_tab->centralLayout);

    connect(tab_1->tab_button, &QPushButton::pressed, this, [this, tab_1, tab_2] {
        tab_2->hide();
        tab_1->show();
        current_tab = tab_1;
    });
    connect(tab_2->tab_button, &QPushButton::pressed, this, [this, tab_1, tab_2] {
        tab_1->hide();
        tab_2->show();
        current_tab = tab_2;
    });

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

void EmojiPicker::startSearch(std::string msg)
{
    searchBarInput(this, msg.c_str());
}
