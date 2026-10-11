#pragma once
#include <iostream>

class MyMethods {
public:
    static constexpr int int_buf_size = 13;

    static int getInt(const char *request, const char *repeatRequest, const char *overLength, const char *notInt, const char *overIntValue);
    static char getChar(const char *request, const char *repeatRequest, const char *overLength);
};

