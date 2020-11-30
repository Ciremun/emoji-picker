#include <iostream>
#include <QtWidgets>

#include "app.hpp"
#include "search.hpp"

#ifdef _WIN32
#include "input_win.hpp"
#else
#include "input_X11.hpp"
#endif

void searchBarInput(EmojiPicker *widget, const char *msg)
{
    auto &search_query = widget->search_query;
    auto &emojis_found = widget->emojis_found;

    if (strcmp(msg, "Backspace") == 0)
    {
        if (search_query->text().isEmpty())
            return;
        QString search_query_text = search_query->text();
        search_query_text.chop(1);
        search_query->setText(search_query_text);
        if (search_query->text().isEmpty())
        {
            emojis_found->hide();
            widget->label->show();
            for (QPushButton *tab_button : widget->tab_buttons)
                tab_button->show();
            widget->search_tab->hide();
            widget->current_tab->show();
        }
    }
    else
    {
        if (search_query->text().isEmpty())
        {
            widget->label->hide();
            emojis_found->setText("0 emojis are found");
            emojis_found->show();
            for (QPushButton *tab_button : widget->tab_buttons)
                tab_button->hide();
            widget->search_tab->show();
            widget->current_tab->hide();
        }
        search_query->setText(search_query->text() + msg);
    }
    std::string search_query_str = search_query->text().toStdString();
    if (search_query_str.length() == 0)
        return;

    widget->search_tab->clear();
    std::vector<std::wstring> found_emojis;

    for (const Tab *tab : widget->tabs)
    {
        FlowLayout *flowLayout = tab->flowLayout;
        QList<QPushButton *> emoji_buttons = flowLayout->parentWidget()->findChildren<QPushButton *>();
        for (auto it = emoji_buttons.begin(); it != emoji_buttons.end(); ++it)
        {
            QPushButton *emoji_button = (*it);
            std::string emoji_name = emoji_button->objectName().toStdString();
            bool emoji_found = emoji_name.find(search_query_str) != std::string::npos;
            if (emoji_found)
            {
                QString button_text = emoji_button->text();
                int button_text_length = button_text.length();
                wchar_t buffer[button_text_length];
                found_emojis.push_back(button_text.toStdWString());
            }
        }
    }
    widget->search_tab->update(found_emojis);
    int found_emojis_count =  found_emojis.size();
    std::string emojis_found_text_p1 = std::to_string(found_emojis_count);
    std::string emojis_found_text_p2;
    if (found_emojis_count == 1)
        emojis_found_text_p2 = " emoji is found";
    else
        emojis_found_text_p2 = " emojis are found";
    emojis_found->setText(QString::fromStdString(emojis_found_text_p1 + emojis_found_text_p2));
}
