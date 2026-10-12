#include "MyMethods.h"

void ClearBadInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int MyMethods::getInt(const char* request, const char* repeatRequest, const char* overLength, const char* notInt, const char* overIntValue) {
    char buf[int_buf_size];
    bool firstTry = true;

    while (true) {
        std::cout << (firstTry ? request : repeatRequest) << '\n';
        std::cin.getline(buf, int_buf_size);

        if (std::cin.fail()) {
            ClearBadInput();
            std::cout << overLength <<".\n";
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
            if (val >  (limit - (buf[i] - '0')) / 10) { ok = false; break; }
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

char MyMethods::getChar(const char* request, const char* repeatRequest, const char* overLength) {
    char buf;
    bool firstTry = true;

    while (true) {
        std::cout << (firstTry ? request : repeatRequest) << '\n';
        std::cin.get(buf);

        if (std::cin.fail() || std::cin.peek() != '\n') {
            ClearBadInput();
            std::cout << overLength <<".\n";
            firstTry = false;
            continue;
        }

        std::cin.ignore();
        return buf;
    }
}

bool MyMethods::getCharOnce(const char* request, char& buf) {

    std::cout << request << '\n';

    std::cin.get(buf);

    if (std::cin.fail() || std::cin.peek() != '\n') {
        ClearBadInput();
        return false;
    }


    std::cin.ignore();
    return true;
}

bool MyMethods::getIntOnce(const char* request, int& res) {
    char buf[int_buf_size];

    std::cout << request << '\n';
    std::cin.getline(buf, int_buf_size);

    if (std::cin.fail()) {
        ClearBadInput();
        return false;
    }

    int i = 0;
    bool neg = false;
    if (buf[0] == '-') { neg = true; i = 1; }

    if (buf[i] == '\0') {
        return false;
    }

    bool ok = true;
    for (int j = i; buf[j] != '\0'; ++j) {
        if (buf[j] < '0' || buf[j] > '9') { ok = false; break; }
    }
    if (!ok) {
        return false;;
    }

    long val = 0;
    const long long limit = neg ? 2147483647LL  + 1 : 2147483647LL;
    for (; buf[i] != '\0'; ++i) {
        if (val >  (limit - (buf[i] - '0')) / 10) { ok = false; break; }
        val = val * 10 + (buf[i] - '0');
    }
    if (!ok) {
        return false;
    }

    res =  neg ? (int)(-val) : (int)val;
    return true;
}