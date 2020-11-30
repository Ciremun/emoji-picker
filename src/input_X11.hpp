#include <QtWidgets>
#include <string>
#include "app.hpp"

class InputThread : public QObject
{
    Q_OBJECT
public:
    EmojiPicker *widget;
    void setOSHooks(EmojiPicker *widget);
    void registerHotKey();

public slots:
    void setKeyboardHook();

signals:
    void startSearch(std::string msg);
    void toggleOnHotKey();
};

void sendInput(const wchar_t *msg, int size);
bool isLetter(unsigned int keycode);
bool isNumber(unsigned int keycode);
