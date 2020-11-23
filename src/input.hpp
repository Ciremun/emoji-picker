void setWindowsKeyboardHook();
void updateKeyState(BYTE *keystate, int keycode);
LRESULT CALLBACK windowsHookCallback(int nCode, WPARAM wParam, LPARAM lParam);