void sendInput(const wchar_t *msg, int size);
void loopInput(EmojiPicker *widget);
void setKeyboardHook(EmojiPicker *widget);
void loopInputHotKey(EmojiPicker *widget);
void registerHotKey(EmojiPicker *widget);
bool isLetter(unsigned int keycode);
bool isNumber(unsigned int keycode);
