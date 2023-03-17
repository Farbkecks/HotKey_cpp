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

    string oAuth_Tocken = "BQB7Ne8EoBFdZSa_xjqPIrbZFY_AodlOXKW_D_Jfx6k2Ktgik6tceRSN0Wdt0uT1LO4QmYQ7lCWv3DteX2SEOFnwXFq49jK-Yr2SULvTLJJSHbp2KWWvdiE2F3GvAXHsfVl2xQkCOTO3VINI69qYI38Ww0Gm9DOi5-Fti1eSLUzWm6fexuswVbp94w";

//    cpr::Response r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/volume?volume_percent=%2B50"},
//                               cpr::Header{{"Content-Length", "0"}},
//                               cpr::Bearer{oAuth_Tocken});
//
//    cout << r.status_code << endl;

//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
    cpr::Response r = cpr::Get(cpr::Url{"https://api.spotify.com/v1/me/player"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});
    string resulte = r.text;
    cout << resulte << endl;
    auto pos = resulte.find("volume_percent");
    auto volumeString = resulte.substr(pos+18,3);
    int volume = std::stoi(volumeString);
    return 0;
}