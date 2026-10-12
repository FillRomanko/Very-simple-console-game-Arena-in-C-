#pragma once
#include <iostream>

class MyMethods {
public:
    static constexpr int int_buf_size = 13;

    static char getChar(const char *request, const char *repeatRequest, const char *overLength);
    static int getInt(const char *request, const char *repeatRequest, const char *overLength, const char *notInt, const char *overIntValue);

    static bool getCharOnce(const char *request, char &buf);
    static bool getIntOnce(const char *request, int &res); 
};

