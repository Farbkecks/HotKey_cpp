#pragma once

#include <string>
#include <cpr/cpr.h>
#include <regex>
#include <iostream>
#include <filesystem>


class Spotify {
public:
    //functions
    Spotify();

    std::string commandStats() const;

    bool commandPause();

    bool commandSetVolume(int volume) const;

    int commandGetVolume() const;

    bool commandChangeVolume(int change) const;

    void generateVerifiedToken();

private:

    //functions
    bool testToken() const;

    static std::string getToken();

    static std::string file_content(const std::filesystem::path &path);

    static std::string parseToken(const std::string &input);

    static int parseVolume(const std::string &input);

    static void generateToken(bool deleteCache = false);

    cpr::Response pausePlayback() const;

    cpr::Response startPlayback() const;

private:
    //variables
    std::string oAuthToken;
    bool playing;
};
