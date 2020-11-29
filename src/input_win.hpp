LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
void updateKeyState(BYTE *keystate, int keycode);
void setKeyboardHook(EmojiPicker *widget);
void sendInput(const wchar_t *msg, int size);
void registerHotKey(HWND hwnd);
void setSpecialWindowState(HWND hwnd);
bool isLetter(int keycode);
bool isNumber(int keycode);
void setOSHooks(EmojiPicker *widget);
