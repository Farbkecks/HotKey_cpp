#include <windows.h>
#include <iostream>


int main()
{
    using namespace std;
    enum{ONE_KEYID = 1, TWO_KEYID = 2};
    RegisterHotKey(0, ONE_KEYID, MOD_NOREPEAT, 0x31); // register 1 key as hotkey
    RegisterHotKey(0, TWO_KEYID, MOD_NOREPEAT, 0x32); // register 2 key as hotkey
    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        PeekMessage(&msg, 0, 0, 0, 0x0001);
        switch(msg.message)
        {
            case WM_HOTKEY:
                if(msg.wParam == ONE_KEYID)
                {
                    std::cout << "Test" << std::endl;
                }
                else if(msg.wParam == TWO_KEYID)
                {
                    std::cout << "Test2" << std::endl;
                }
        }
    }
    return 0;
}