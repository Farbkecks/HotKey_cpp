#include <windows.h>
#include "Spotify.h"

using namespace std;

int hotkey(Spotify spotify) {
    enum {
        UP = 1, DOWN = 2, PAUSE = 3
    };
    // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    RegisterHotKey(0, UP, MOD_NOREPEAT, 0x86); //F23
    RegisterHotKey(0, DOWN, MOD_NOREPEAT, 0x87); //F24
    RegisterHotKey(0, PAUSE, MOD_NOREPEAT, 0x85); //F22
    MSG msg;
    cout << "start mainloop" << endl;
    while (GetMessage(&msg, 0, 0, 0)) {
        PeekMessage(&msg, 0, 0, 0, 0x0001);
        switch (msg.message) {
            case WM_HOTKEY:
                if (msg.wParam == UP) {
                    cout << "Volume UP" << endl;
                    spotify.commandSetVolume(spotify.commandGetVolume() + 10);
                } else if (msg.wParam == DOWN) {
                    cout << "Volume Down" << endl;
                    spotify.commandSetVolume(spotify.commandGetVolume() - 10);
                } else if (msg.wParam == PAUSE) {
                    cout << "Pause" << endl;
                    spotify.commandPause();
                }
        }
    }
    return 0;
}


int main() {

    Spotify spotify;
    hotkey(spotify);
    return 0;
}