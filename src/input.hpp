LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
void updateKeyState(BYTE *keystate, int keycode);
void setWindowsKeyboardHook();
void windowsSendInput(const wchar_t *msg, int size);