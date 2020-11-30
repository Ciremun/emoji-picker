#ifndef TAB_H
#define TAB_H
#include "flowlayout.hpp"

class Tab : QObject
{
public:
    Tab(QPushButton *tab_button, QLabel *label, QString label_text,
        std::vector<std::pair<const char*, const wchar_t *>> &emojis, bool visible = false);
    QHBoxLayout *centralLayout;
    QPushButton *tab_button;
    FlowLayout *flowLayout;
    void hide();
    void show();

private:
    QLabel *label;
    QString label_text;
    std::vector<std::pair<const char*, const wchar_t *>> emojis;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    void setLabelText(QString text);
};
#endif
