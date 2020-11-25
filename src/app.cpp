#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "input.hpp"
#include "FlowLayout.hpp"

EmojiPicker::EmojiPicker(QFrame *parent, int w, int h)
    : QFrame(parent), window_width(w), window_height(h)
{
    setObjectName("MainFrame");
    setFrameShape(QFrame::Box);
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

    FlowLayout *flowLayout = new FlowLayout(0, 0, 0);
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    flowLayout->setContentsMargins(8, 0, 0, 0);

    QLabel *label = new QLabel();
    label->setFont(QFont("Arial", 11));
    label->setText("Emoji - Keep typing to find an emoji");
    label->setContentsMargins(15, 0, 0, 10);
    label->setStyleSheet("QLabel{color: #969696; background-color: #111111;}");
    main_layout->addWidget(label);

    QHBoxLayout* tabs = new QHBoxLayout();
    tabs->setSpacing(0);
    tabs->setContentsMargins(8, 0, 0, 0);

    const wchar_t* tab_labels[] = {L":)", L";-)"};
    for (const wchar_t* l: tab_labels)
    {
        QPushButton* tab_button = new QPushButton(QString::fromWCharArray(l));
        tab_button->setContentsMargins(0, 0, 0, 0);
        tab_button->setFixedSize(40, 40);
        tab_button->setFont(QFont("Arial", 13));
        tab_button->setStyleSheet(" "
        "QPushButton {color: #ffffff; background-color: #111111;}"
        "QPushButton:hover {color: #026fc5; background-color: #282828;}");
        tabs->addWidget(tab_button);
    }

    tabs->addStretch();
    main_layout->addLayout(tabs);

    const wchar_t* emojis[] = {
        L"😀", L"😁", L"😂", L"🤣", L"😃", L"😄", L"😅", L"😆",
        L"😉", L"😊", L"😋", L"😎", L"😍", L"😘", L"🥰", L"😗",
        L"😙 ", L"😚", L"☺", L"🙂", L"🤗", L"🤩", L"🤔", L"🤨",
        L"😐", L"😑", L"😶", L"🙄", L"😏", L"😣", L"😥", L"😮",
        L"🤐", L"😯", L"😪", L"😫", L"🥱", L"😴", L"😌", L"😛",
        L"😜", L"😝", L"🤤", L"😒", L"😓", L"😔", L"😕", L"🙃",
        L"🤑", L"😲", L"☹", L"🙁", L"😖", L"😞", L"😟", L"😤",
        L"😢", L"😭", L"😦", L"😧", L"😨", L"😩", L"🤯", L"😬",
        L"😰", L"😱", L"🥵", L"🥶", L"😳", L"🤪", L"😵", L"🥴",
        L"😠", L"😡", L"🤬", L"😷", L"🤒", L"🤕", L"🤢", L"🤮",
        L"🤧", L"😇", L"🥳", L"🥺", L"🤠", L"🤡", L"🤥", L"🤫",
        L"🤭", L"🧐", L"🤓", L"😈", L"👿", L"👹", L"👺", L"💀",
        L"☠", L"👻", L"👽", L"👾", L"🤖", L"💩", L"😺", L"😸",
        L"😹", L"😻", L"😼", L"😽", L"🙀", L"😿", L"🐱", L"👤",
        L"🐱", L"🏍", L"🐱", L"💻", L"🐱", L"🐉", L"🐱", L"🐱",
        L"🚀", L"🙈", L"🙉", L"🙊", L"🐵", L"🐶", L"🐺", L"🐱",
        L"🦁", L"🐯", L"🦒", L"🦊", L"🦝", L"🐷", L"🐗", L"🐭",
        L"🐹", L"🐰", L"🐻", L"🐨", L"🐼", L"🐸", L"🦓", L"🐴",
        L"🦄", L"🐔", L"🐲", L"🐽", L"🐾", L"🐒", L"🦍", L"🦧",
        L"🐕", L"🦺", L"🐩", L"🐕", L"🐈", L"🐅", L"🐆", L"🐎",
        L"🦌", L"🦏", L"🦛", L"🐂", L"🐃", L"🐄", L"🐏", L"🐑",
        L"🐐", L"🐪", L"🐫", L"🦙", L"🦘", L"🦥", L"🦨", L"🦡",
        L"🐘", L"🐁", L"🐀", L"🦔", L"🐇", L"🐿", L"🦎", L"🐊"
        "🐢", L"🐉", L"🦕", L"🦖", L"🦦", L"🦈", L"🐬", L"🐳",
        L"🐋", L"🐟", L"🐠", L"🐡", L"🦐", L"🦑", L"🐙", L"🦞",
        L"🦀", L"🐚", L"🦆", L"🐓", L"🦃", L"🦅", L"🕊",L"🦢",
        L"🦜", L"🦩", L"🦚", L"🦉", L"🐦", L"🐧", L"🐥",L"🐤",
        L"🐣", L"🦇", L"🦋", L"🐛", L"🦟", L"🦗", L"🐜",L"🐝",
        L"🐞", L"🦂", L"🕷", L"🕸", L"🦠", L"🧞", L"♀",L"♂",
        L"🗣", L"👤", L"👥", L"👁", L"👀", L"🦴", L"🦷",L"👅",
        L"👄", L"🧠", L"🦾", L"🦿", L"👣", L"🤺", L"⛷",L"🤼",
        L"♂", L"🤼", L"♀", L"️", L"👯", L"♂", L"👯", L"♀",L"💑",
        L"👩" L"❤" L"👩", L"👨", L"❤", L"👨", L"💏",L"👩",
        L"❤" L"💋", L"👩", L"👨", L"❤",L"💋", L"👨", L"👪",
        L"👨", L"👩", L"👦"
    };
    for(const wchar_t* l : emojis)
    {
        QPushButton *button = new QPushButton(QString::fromWCharArray(l));
        button->setFixedSize(38, 38);
        button->setFont(QFont("Arial", 14));
        connect(button, &QPushButton::released, this, [this, button]
        {
            QString button_text = button->text();
            int button_text_length = button_text.length();
            wchar_t buffer[button_text_length];
            button_text.toWCharArray(buffer);
            this->handleButton(buffer, button_text_length);
        });
        flowLayout->addWidget(button);
    }

	QWidget *scrollWidget = new QWidget();
	scrollWidget->setLayout(flowLayout);
    scrollWidget->setContentsMargins(0, 0, 0, 0);
	QScrollArea *scrollArea = new QScrollArea();
	scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->verticalScrollBar()->setStyleSheet(" "
    "QScrollBar:vertical {"
    "   border: 1px solid #999999;"
    "   background-color: none;"
    "   width: 4px;"
    "   margin: 0px 0px 0px 0px;"
    "}"
    "QScrollBar::handle:vertical {"
    "    background: #858585;"
    "    min-height: 0px;"
    "}"
    "QScrollBar::add-line:vertical {"
    "    height: 0px;"
    "    subcontrol-position: bottom;"
    "    subcontrol-origin: margin;"
    "}"
    "QScrollBar::sub-line:vertical {"
    "    height: 0 px;"
    "    subcontrol-position: top;"
    "    subcontrol-origin: margin;"
    "}");

	QHBoxLayout *centralLayout = new QHBoxLayout();
	centralLayout->addWidget(scrollArea);
    centralLayout->setContentsMargins(0, 0, 0, 0);

    main_layout->addLayout(centralLayout);
	setLayout(main_layout);

    setWindowFlags(Qt::Window
    | Qt::X11BypassWindowManagerHint
    | Qt::WindowStaysOnTopHint
    | Qt::FramelessWindowHint
    | Qt::WindowDoesNotAcceptFocus);
    setFixedSize(QSize(window_width, window_height));
    setWindowTitle("Rushia");
    setAttribute(Qt::WA_ShowWithoutActivating);
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

void EmojiPicker::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void EmojiPicker::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX() - m_nMouseClick_X_Coordinate, event->globalY() - m_nMouseClick_Y_Coordinate);
}

void EmojiPicker::handleButton(const wchar_t* msg, int size)
{
    windowsSendInput(msg, size);
}
