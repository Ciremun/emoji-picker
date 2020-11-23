class EmojiPicker : public QWidget
{
public:
    EmojiPicker(QWidget *parent, int w, int h);
private:
    int window_width;
    int window_height;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};