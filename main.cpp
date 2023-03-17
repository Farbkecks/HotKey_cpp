//#include <windows.h>
#include <iostream>
#include <cpr/cpr.h>
#include <chrono>
#include <thread>
#include <string>



using namespace std;

//int hotkey(){
//    enum{ONE_KEYID = 1, TWO_KEYID = 2};
//    RegisterHotKey(0, ONE_KEYID, MOD_NOREPEAT, 0x31); // register 1 key as hotkey
//    RegisterHotKey(0, TWO_KEYID, MOD_NOREPEAT, 0x32); // register 2 key as hotkey
//    MSG msg;
//    while(GetMessage(&msg, 0, 0, 0))
//    {
//        PeekMessage(&msg, 0, 0, 0, 0x0001);
//        switch(msg.message)
//        {
//            case WM_HOTKEY:
//                if(msg.wParam == ONE_KEYID)
//                {
//                    std::cout << "Test" << std::endl;
//                }
//                else if(msg.wParam == TWO_KEYID)
//                {
//                    std::cout << "Test2" << std::endl;
//                }
//        }
//    }
//    return 0;
//}


int main(int argc, char** argv) {

    string oAuth_Tocken = "";

    cpr::Response r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/pause"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});

    cout << r.status_code << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/play"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});


    cout << r.status_code << endl;

    return 0;
}