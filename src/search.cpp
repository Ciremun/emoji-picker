#include <QtWidgets>

#include "app.hpp"
#include "search.hpp"

void searchBarInput(EmojiPicker *widget, const char *msg)
{
    // /@@@ fix empty keys
    QLineEdit *search_bar = widget->search_bar;
    QString search_bar_text = search_bar->text();

    if (strcmp(msg, "Backspace") == 0)
    {
        if (!search_bar_text.isEmpty())
        {
            if (search_bar_text.length() == 1)
            {
                search_bar->hide();
                widget->label->show();
            }
            search_bar_text.chop(1);
            search_bar->setText(search_bar_text);
        }
        return;
    }
    search_bar->setText(search_bar_text + msg);
    if (search_bar_text.isEmpty())
    {
        widget->label->hide();
        search_bar->show();
    }
}