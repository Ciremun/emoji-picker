#ifndef SEARCH_TAB_H
#define SEARCH_TAB_H
#include "flowlayout.hpp"

class SearchTab : QObject
{
public:
    SearchTab();
    QHBoxLayout *centralLayout;
    FlowLayout *flowLayout;
    void hide();
    void show();
    void update(std::vector<std::wstring> &emojis);
    void clear();

private:
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
};
#endif
