class Tab : QObject
{
public:
    Tab(QPushButton *tab_button, QLabel *label, QString label_text,
        std::vector<const wchar_t*> &emojis, int button_width, 
        int button_height, int font_size, bool visible = true);
    QHBoxLayout *centralLayout;
    QPushButton *tab_button;
    void hide();
    void show();
private:
    QLabel *label;
    QString label_text;
    std::vector<const wchar_t*> emojis;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    void setLabelText(QString text);
    void sendInput(const wchar_t* msg, int size);
};