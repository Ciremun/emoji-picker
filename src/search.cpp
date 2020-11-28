#include <QtWidgets>

#include <string>

#include "app.hpp"
#include "search.hpp"

#ifdef _WIN32
#include "input_win.hpp"
#else
#include "input_X11.hpp"
#endif

// /@@@ fix empty keys
// @@@ override Enter keypress?
void searchBarInput(EmojiPicker *widget, const char *msg)
{
    if (!widget->isVisible())
        return;

    QLineEdit *search_bar = widget->search_bar;

    if (strcmp(msg, "Backspace") == 0)
    {
        if (!search_bar->text().isEmpty())
        {
            if (search_bar->text().length() == 1)
            {
                search_bar->hide();
                widget->label->show();
                for (QPushButton *tab_button : widget->tab_buttons)
                    tab_button->show();
            }
            QString search_bar_text = search_bar->text();
            search_bar_text.chop(1);
            search_bar->setText(search_bar_text);

            for (const Tab *tab : widget->tabs)
            {
                FlowLayout *flowLayout = tab->flowLayout;
                for (int i = 0; i < flowLayout->count(); i++)
                    flowLayout->itemAt(i)->widget()->show();
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        if (search_bar->text().isEmpty())
        {
            widget->label->hide();
            search_bar->show();
            for (QPushButton *tab_button : widget->tab_buttons)
                tab_button->hide();
        }
        search_bar->setText(search_bar->text() + msg);
    }
    QString emoji_style = "QPushButton {color: #ffffff;} "
                          "QPushButton:hover {background-color: #474747;}";
    QString found_emoji_style = "QPushButton {background-color: #2976b2;}";
    std::string search_query = search_bar->text().toStdString();

    bool first_emoji = false;

    for (const Tab *tab : widget->tabs)
    {
        FlowLayout *flowLayout = tab->flowLayout;
        for (int i = 0; i < flowLayout->count(); i++)
        {
            QWidget *emoji_button = flowLayout->itemAt(i)->widget();
            if (search_query.length() == 0)
            {
                emoji_button->setStyleSheet(emoji_style);
                continue;
            }
            std::string emoji_name = emoji_button->objectName().toStdString();
            bool emoji_found = emoji_name.find(search_query) != std::string::npos;
            if (emoji_found)
            {
                if (!first_emoji)
                {
                    first_emoji = true;
                    emoji_button->setStyleSheet(found_emoji_style);
                }
                else
                {
                    emoji_button->setStyleSheet(emoji_style);
                }
                emoji_button->show();
            }
            else
            {
                emoji_button->setStyleSheet(emoji_style);
                emoji_button->hide();
            }
        }
    }
}
