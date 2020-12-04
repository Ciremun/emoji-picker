#ifndef SEARCH_TAB_H
#define SEARCH_TAB_H
#include "flowlayout.hpp"

class SearchTab : QObject
{
public:
    SearchTab(QLabel *search_query);
    QHBoxLayout *centralLayout;
    FlowLayout *flowLayout;
    QLabel *search_query;
    void hide();
    void show();
    void update(std::vector<std::wstring> &emojis);
    void clear();

private:
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
};
#endif
