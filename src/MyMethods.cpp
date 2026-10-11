#include "MyMethods.h"

void ClearBadInput(const char* overLength) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << overLength <<".\n";
}

int MyMethods::getInt(const char* request, const char* repeatRequest, const char* overLength, const char* notInt, const char* overIntValue) {
    char buf[int_buf_size];

    bool firstTry = true;
    while (true) {
        std::cout << (firstTry ? request : repeatRequest) << '\n';
        std::cin.getline(buf, int_buf_size);

        if (std::cin.fail()) {
            ClearBadInput(overLength);
            firstTry = false;
            continue;
        }

        int i = 0;
        bool neg = false;
        if (buf[0] == '-') { neg = true; i = 1; }

        if (buf[i] == '\0') {
            std::cout << notInt << '\n';
            firstTry = false;
            continue;
        }

        bool ok = true;
        for (int j = i; buf[j] != '\0'; ++j) {
            if (buf[j] < '0' || buf[j] > '9') { ok = false; break; }
        }
        if (!ok) {
            std::cout << notInt << '\n';
            firstTry = false;
            continue;
        }

        long val = 0;
        const long long limit = neg ? 2147483647LL  + 1 : 2147483647LL;
        for (; buf[i] != '\0'; ++i) {
            if (val >  (limit - buf[i] - '0') / 10) { ok = false; break; }
            val = val * 10 + (buf[i] - '0');
        }
        if (!ok) {
            std::cout << overIntValue << '\n';
            firstTry = false;
            continue;
        }

        return neg ? (int)(-val) : (int)val;
    }
}