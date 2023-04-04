#include <Python.h>
#include <windows.h>
#include <iostream>
#include <cpr/cpr.h>
#include <chrono>
#include <thread>
#include <string>
#include <regex>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include "iostream"
#include <chrono>
#include <thread>

using namespace std;

int parseVolume(const string &input) {
    regex regexp("\"volume_percent\" : [0-9]+");
    smatch m;
    regex_search(input, m, regexp);
    regex regexp1("[0-9]+");
    smatch m1;
    string myStr = m.str();
    regex_search(myStr, m1, regexp1);
    return stoi(m1.str());
}

string parseToken(const string &input) {
    regex regexp("\\{\"access_token\": \"[\\w\\n-]*\",");
    smatch m;
    regex_search(input, m, regexp);
    return m.str().substr(18, 190);
}

std::string
file_contents(const std::filesystem::path &path) {
    // Sanity check
    if (!std::filesystem::is_regular_file(path))
        return {};

    // Open the file
    // Note that we have to use binary mode as we want to return a string
    // representing matching the bytes of the file on the file system.
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return {};

    // Read contents
    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    // Close the file
    file.close();

    return content;
}

int hotkey() {
    enum {
        ONE_KEYID = 1, TWO_KEYID = 2
    };
    RegisterHotKey(0, ONE_KEYID, MOD_NOREPEAT, 0x31); // register 1 key as hotkey
    RegisterHotKey(0, TWO_KEYID, MOD_NOREPEAT, 0x32); // register 2 key as hotkey
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        PeekMessage(&msg, 0, 0, 0, 0x0001);
        switch (msg.message) {
            case WM_HOTKEY:
                if (msg.wParam == ONE_KEYID) {
                    std::cout << "Test" << std::endl;
                } else if (msg.wParam == TWO_KEYID) {
                    std::cout << "Test2" << std::endl;
                }
        }
    }
    return 0;
}

void generateToken() {
    system("oauth.py");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

string getToken() {
    auto raw = file_contents(".cache-farbkecks26");
    raw = parseToken(raw);
    return raw;
}

int main() {

    generateToken();
    cout << getToken() << endl;

    return 0;

    string oAuth_Tocken = "BQBd1ggJ26CSzGB0lV5lxQ3uq_OWjBU0ckDt60-a6hb6UojKQiBTW_hliVWcKNv45rOYbC5foBel2k_WG5sgUjc18PsOrUs01PAyjwDYmA9jvhPg0VufrL_aPXeKZIDbXvarohrhpBwUEfyerd6Fd6ezsUBSZnhIujjXIlBXWeaek4jmUVoAZBGPx7pDEQ";

//    cpr::Response r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/volume?volume_percent=%2B50"},
//                               cpr::Header{{"Content-Length", "0"}},
//                               cpr::Bearer{oAuth_Tocken});

    cpr::Response r = cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/pause"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});
    cout << r.status_code << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    cpr::Response m = cpr::Get(cpr::Url{"https://api.spotify.com/v1/me/player"},
                               cpr::Header{{"Content-Length", "0"}},
                               cpr::Bearer{oAuth_Tocken});
    cout << m.text << endl;
    cout << parseVolume(r.text) << endl;


    return 0;
}