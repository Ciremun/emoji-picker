#ifndef APP_H
#define APP_H
#include "tab.hpp"
#include "search_tab.hpp"

class EmojiPicker : public QFrame
{
public:
    EmojiPicker(QFrame *parent, int w, int h);
    QLabel *label;
    QLabel *emojis_found;
    QLabel *search_query;
    std::vector<Tab *> tabs;
    std::vector<QPushButton *> tab_buttons;
    Tab *current_tab;
    SearchTab *search_tab;

public slots:
    void toggleOnHotKey();
    void startSearch(std::string msg);

private:
    int window_width;
    int window_height;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};
#endif
