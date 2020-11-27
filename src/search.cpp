#include <QtWidgets>

#include <string>

#include "app.hpp"
#include "search.hpp"

void searchBarInput(EmojiPicker *widget, const char *msg)
{
    // /@@@ fix empty keys
    QLineEdit *search_bar = widget->search_bar;

    if (strcmp(msg, "Backspace") == 0)
    {
        if (!search_bar->text().isEmpty())
        {
            if (search_bar->text().length() == 1)
            {
                search_bar->hide();
                widget->label->show();
            }
            QString search_bar_text = search_bar->text();
            search_bar_text.chop(1);
            search_bar->setText(search_bar_text);
        }
    }
    else
    {
        if (search_bar->text().isEmpty())
        {
            widget->label->hide();
            search_bar->show();
        }
        search_bar->setText(search_bar->text() + msg);
    }

    QString emoji_style = "QPushButton{background-color: #333333;}";
    QString found_emoji_style = "QPushButton{background-color: #2976b2;}";
    std::string search_query = search_bar->text().toStdString();
    printf("Search query: %s\n", search_query.c_str());

    for (const Tab* tab : widget->tabs)
    {
        FlowLayout *flowLayout =  tab->flowLayout;
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
                emoji_button->setStyleSheet(found_emoji_style);
            else
                emoji_button->setStyleSheet(emoji_style);
        }
    }
}
