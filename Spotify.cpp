#include "Spotify.h"

#include <iostream>

bool Spotify::testToken() const {
    cpr::Response response = cpr::Get(cpr::Url{"https://api.Spotify.com/v1/me/player"},
                                      cpr::Header{{"Content-Length", "0"}},
                                      cpr::Bearer{oAuthToken});

    if (response.status_code == 200)return true;
    return false;

}

Spotify::Spotify()
        : playing(false) {
    generateVerifiedToken();
}

std::string Spotify::getToken() {
    auto raw = file_content(".cache-farbkecks26");
    raw = parseToken(raw);
    return raw;
}

std::string Spotify::file_content(const std::filesystem::path &path) {
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

std::string Spotify::parseToken(const std::string &input) {
    std::regex regexp("\\{\"access_token\": \"[\\w\\n-]*\",");
    std::smatch m;
    regex_search(input, m, regexp);
    return m.str().substr(18, 190);
}

void Spotify::generateToken(bool deleteChache) {
    std::cout << "generate new Token" << std::endl;
    //NICHT SO MACHEN
    //es ist super dumm das so zu machen
    if (deleteChache) {
        try {
            std::filesystem::remove(".cache-farbkecks26");
        } catch (...) {

        }
    }

    system("oauth.py");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Spotify::generateVerifiedToken() {
    try {
        oAuthToken = getToken();
    }
    catch (...) {
        generateToken();
    }

    while (!testToken()) {
        generateToken(true);
        oAuthToken = getToken();
    }
}

int Spotify::parseVolume(const std::string &input) {
    using namespace std;

    regex regexp("\"volume_percent\" : [0-9]+");
    smatch m;
    regex_search(input, m, regexp);
    regex regexp1("[0-9]+");
    smatch m1;
    string myStr = m.str();
    regex_search(myStr, m1, regexp1);
    return stoi(m1.str());
}

std::string Spotify::commandStats() const {
    return cpr::Get(cpr::Url{"https://api.Spotify.com/v1/me/player"},
                    cpr::Header{{"Content-Length", "0"}},
                    cpr::Bearer{oAuthToken}).text;

}

void Spotify::commandPause() {
    if (playing) {
        auto r = pausePlayback();
        playing = false;
        if (r.status_code != 204) {
            startPlayback();
            playing = true;
        }

    } else {
        auto r = startPlayback();
        playing = true;
        if (r.status_code != 204) {
            pausePlayback();
            playing = false;
        }
    }
}

cpr::Response Spotify::pausePlayback() const {
    return cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/pause"},
                    cpr::Header{{"Content-Length", "0"}},
                    cpr::Bearer{oAuthToken});
}

cpr::Response Spotify::startPlayback() const {
    return cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/play"},
                    cpr::Header{{"Content-Length", "0"}},
                    cpr::Bearer{oAuthToken});
}

void Spotify::commandSetVolume(int volume) const {
    cpr::Put(cpr::Url{"https://api.spotify.com/v1/me/player/volume?volume_percent=%2B" + std::to_string(volume)},
             cpr::Header{{"Content-Length", "0"}},
             cpr::Bearer{oAuthToken});
}

int Spotify::commandGetVolume() const {
    return parseVolume(commandStats());
}
