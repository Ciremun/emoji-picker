#include <QtWidgets>

#include "app.hpp"

#ifdef _WIN32
#include "input_win.hpp"
#else
#include "input_X11.hpp"
#endif

SearchTab::SearchTab(QLabel *sq)
    : search_query(sq)
{
    flowLayout = new FlowLayout(0, 0, 0);
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    flowLayout->setContentsMargins(8, 0, 0, 0);

    scrollWidget = new QWidget();
    scrollWidget->setLayout(flowLayout);
    scrollWidget->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->verticalScrollBar()->setStyleSheet(" "
                                                   "QScrollBar:vertical {"
                                                   "   border: 1px solid #999999;"
                                                   "   background-color: #ffffff;"
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

    centralLayout = new QHBoxLayout();
    centralLayout->addWidget(scrollArea);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    scrollWidget->setVisible(0);
    scrollArea->setVisible(0);
}

void SearchTab::hide()
{
    scrollWidget->setVisible(0);
    scrollArea->setVisible(0);
}
void SearchTab::show()
{
    scrollWidget->setVisible(1);
    scrollArea->setVisible(1);
}

void SearchTab::update(std::vector<std::wstring> &emojis)
{
    for (const std::wstring &emoji : emojis)
    {
        QPushButton *button = new QPushButton(QString::fromStdWString(emoji));
        if (button->text().length() > 2)
        {
            button->setFixedSize(100, 40);
            button->setFont(QFont("Arial", 11));
        }
        else
        {
            button->setFixedSize(38, 38);
            button->setFont(QFont("Arial", 14));
        }
        button->setStyleSheet("QPushButton{color: #ffffff;}");
        connect(button, &QPushButton::pressed, this, [this, button] {
            QString button_text = button->text();
            int button_text_length = button_text.length();
            wchar_t buffer[button_text_length];
            button_text.toWCharArray(buffer);
            int search_query_length = search_query->text().length();
            printf("query len: %u\n", search_query_length);
            for (int i = 0; i < search_query_length; i++)
                sendInput(L"Backspace", 10);
            sendInput(buffer, button_text_length);
        });
        flowLayout->addWidget(button);
    }
}

void SearchTab::clear()
{
    QList<QPushButton *> emoji_buttons = flowLayout->parentWidget()->findChildren<QPushButton *>();
    for (auto it = emoji_buttons.begin(); it != emoji_buttons.end(); ++it)
    {
        QPushButton *emoji_button = (*it);
        delete emoji_button;
    }
}
