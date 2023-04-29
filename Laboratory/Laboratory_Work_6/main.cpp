#include <iostream>
#include "Log.h"

int main() {
    Log::SetLogPath("log.txt");
    Log::SetLogLevel(LogLevel::DEBUG);


    Log::Info("Hi");
    Log::Write("Hello");
    //Log::Error("11111111111111");

    return 0;
}