# emoji-picker
Microsoft Windows Emoji Picker clone  

![pajaDank.jpg](.github/pajaDank.jpg)&nbsp;&nbsp;&nbsp;&nbsp;![WAYTOODANK.jpg](.github/WAYTOODANK.jpg)

## Build

    cd emoji-picker
    mkdir build && cd build
    cmake ../
    cmake --build .

### Windows

if `cmake ../` throws `compiler not found` error, try:  

    rm CMakeCache.txt
    cmake -G"Unix Makefiles" ../

DLLs required in PATH or application root:  

    platforms/qwindows.dll
    Qt5Core.dll
    Qt5Gui.dll
    Qt5Widgets.dll
    libstdc++-6.dll

Qt specifically looks for Windows platform plugin (qwindows.dll) inside `platforms` folder  

## HotKey

| Keys | Description |
| --------| ------------- |
| Alt + / | Show/Hide window |
