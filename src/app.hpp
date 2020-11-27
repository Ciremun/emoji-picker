#include "tab.hpp"

class EmojiPicker : public QFrame
{
public:
    EmojiPicker(QFrame *parent, int w, int h);
    void toggleOnHotKey();
    QLabel *label;
    QLineEdit *search_bar;
    std::vector<Tab *> tabs;

private:
    int window_width;
    int window_height;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};