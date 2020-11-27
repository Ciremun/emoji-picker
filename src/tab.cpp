#include <QtWidgets>
#include <iostream>

#include "app.hpp"
#ifdef _WIN32
#include "input_win.hpp"
#else
#include "input_X11.hpp"
#endif

Tab::Tab(QPushButton *tab_button, QLabel *label, QString label_text,
         std::vector<std::pair<const char*, const wchar_t *>> &emojis, int button_width,
         int button_height, int font_size, bool visible)
    : tab_button(tab_button), label(label), label_text(label_text), emojis(emojis)
{
    connect(tab_button, &QPushButton::pressed, this, [this] {
        this->setLabelText(this->label_text);
    });

    flowLayout = new FlowLayout(0, 0, 0);
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    flowLayout->setContentsMargins(8, 0, 0, 0);

    for (const auto &pair : emojis)
    {
        const char* emoji_name = pair.first;
        const wchar_t * emoji = pair.second;
        QPushButton *button = new QPushButton(QString::fromWCharArray(emoji));
        button->setFixedSize(button_width, button_height);
        button->setFont(QFont("Arial", font_size));
        button->setStyleSheet("QPushButton{color: #ffffff;}");
        button->setObjectName(emoji_name);
        connect(button, &QPushButton::pressed, this, [button] {
            QString button_text = button->text();
            int button_text_length = button_text.length();
            wchar_t buffer[button_text_length];
            button_text.toWCharArray(buffer);
            sendInput(buffer, button_text_length);
        });
        flowLayout->addWidget(button);
    }

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
    if (!visible)
    {
        scrollWidget->setVisible(0);
        scrollArea->setVisible(0);
    }
}

void Tab::setLabelText(QString text)
{
    label->setText(text);
}

void Tab::show()
{
    scrollWidget->setVisible(1);
    scrollArea->setVisible(1);
}

void Tab::hide()
{
    scrollWidget->setVisible(0);
    scrollArea->setVisible(0);
}
