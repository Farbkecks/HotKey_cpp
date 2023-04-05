#pragma once

#include <string>
#include <cpr/cpr.h>
#include <regex>
#include <Python.h>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include "iostream"
#include <chrono>
#include <thread>


class Spotify {
public:
    //functions
    Spotify();

    void generateVerifiedToken();

    std::string commandStats() const;

    void commandPause();

    void commandSetVolume(int volume) const;

    int commandGetVolume() const;

//private:
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
