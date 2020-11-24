#include <iostream>

#include <QtWidgets>

#include "app.hpp"
#include "input.hpp"
#include "FlowLayout.hpp"

EmojiPicker::EmojiPicker(QFrame *parent, int w, int h)
    : QFrame(parent), window_width(w), window_height(h)
{
    setFrameShape(QFrame::Box);
    setStyleSheet(" "
    "QFrame {"
    "   border-color: #323338;"
    "   border-width: 1.2px;"
    "   border-style: inset;"
    "   background-color: #111111;"
    "}"
    "QPushButton {border: none;}"
    "QPushButton:hover {background-color: #474747;}"
    "* {background-color: #333333;}");

    QIcon closeIcon = style()->standardIcon(QStyle::SP_TitleBarCloseButton);
    QPushButton *close_button = new QPushButton();
    close_button->setFixedSize(32, 32);
    close_button->setStyleSheet(" "
    "QPushButton {background-color: #111111;}"
    "QPushButton:hover {background-color: #cc0c1c;}");
    close_button->setIcon(closeIcon);
    connect(close_button, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *title_bar = new QHBoxLayout();
    title_bar->setObjectName("title_bar");
    title_bar->addWidget(close_button, 0, Qt::AlignRight);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    main_layout->addLayout(title_bar);

    FlowLayout *flowLayout = new FlowLayout(0, 0, 0);
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    flowLayout->setContentsMargins(8, 0, 0, 0);

    QLabel *label = new QLabel();
    label->setText("Search");
    label->setContentsMargins(8, 15, 0, 15);
    label->setStyleSheet("QLabel{color:white;}");
    main_layout->addWidget(label);

    const wchar_t* test[] = {
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620",
        L"\U00002620", L"\U000000D2", L"w", L"\U000000D3", L"\U0001F602", L"\U0001F914", L"\U0001F921", L"\U00002620"
    };

    for(const wchar_t* l : test)
    {
        QPushButton *button = new QPushButton(QString::fromWCharArray(l));
        button->setFixedSize(38, 38);
        button->setFont(QFont("Consolas", 14));
        connect(button, &QPushButton::released, this, &EmojiPicker::handleButton);
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

void EmojiPicker::handleButton()
{
    return;
}
