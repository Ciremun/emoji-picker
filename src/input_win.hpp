LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
void updateKeyState(BYTE *keystate, int keycode);
void setKeyboardHook(EmojiPicker *widget);
void sendInput(const wchar_t *msg, int size);
void registerHotKey(WId wid);
void setSpecialWindowState(WId wid);
bool isLetter(int keycode);
bool isNumber(int keycode);
