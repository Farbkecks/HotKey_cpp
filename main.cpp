//#include <windows.h>
#include <iostream>
#include <cpr/cpr.h>
#include <chrono>
#include <thread>
#include <string>
#include <regex>


using namespace std;

int parseVolume(const string& input){
    regex regexp("\"volume_percent\" : [0-9]+");
    smatch m;
    regex_search(input, m, regexp);
    regex regexp1("[0-9]+");
    smatch m1;
    string myStr = m.str();
    regex_search(myStr, m1, regexp1);
    return stoi(m1.str());
}

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

    string oAuth_Tocken = "BQCo4UjUY6Dk3ESZXjTPvjw-RvKn0pQNCo7aJNGAIZrizbziGvkKCBvxGoxq14JYA7fyb46eykzkQZ327YH48SXpT8jhS3N7aokMsCzXohbfkbFiz8XV0tr1yl5hBU01UA8FjhxNKrSL7jV9oHa1NsQBwL82YXdnHHjN54fAL3axz4B_vIvSkiZFBw";

    cpr::Response r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/volume?volume_percent=%2B50"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});

    cout << r.status_code << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
    cpr::Response m = cpr::Get(cpr::Url{"https://api.spotify.com/v1/me/player"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});
  cout << m.text << endl;
    cout << parseVolume(r.text) << endl;





    return 0;
}