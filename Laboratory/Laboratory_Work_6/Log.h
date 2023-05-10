#pragma once
#include <fstream>
#include <iostream>
#include <chrono>
#include <windows.h>

//1. Вывод в консоль и в файл
//2. Возможность отключения части логов
//3. Логи разного уровня (Info, Debug, Error и т.п.)
//4. Вывод времени записи лога

enum class LogLevel{
    DEBUG,
    RELEASE
};

class Log
{
private:
    static std::ofstream m_out; // RAII
    static LogLevel m_logLevel;
    static HANDLE m_h;
public:
    Log()
    {
        std::cout << "Constructor" << std::endl;
    }

    static void SetLogLevel(LogLevel logLevel)
    {
        m_logLevel = logLevel;
    }

    static void SetLogPath(const std::string& path)
    {
        m_out.open(path);
    }

    static void Write(const std::string& msg)
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        if(m_logLevel == LogLevel::DEBUG)
        {
            m_h = GetStdHandle(STD_OUTPUT_HANDLE); //получаем наше окно, в котором нужно изменить цвет
            SetConsoleTextAttribute(m_h, 46);
            std::cerr << dt << msg << std::endl;
        }
        m_out << dt<< msg << std::endl;
        m_out.flush();
    }

    static void Info(const std::string& msg)
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        if (m_logLevel == LogLevel::DEBUG) {

            std::cerr << dt << msg << std::endl;
        }
        m_out << dt << msg << std::endl;
        m_out.flush();
    }

    static void Error(const std::string& msg)
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        if (m_logLevel == LogLevel::DEBUG)
        {
            m_h = GetStdHandle(STD_OUTPUT_HANDLE); //получаем наше окно, в котором нужно изменить цвет
            SetConsoleTextAttribute(m_h, 01);
            std::cerr << dt << msg << std::endl;
        }
        m_out <<dt<< msg << std::endl;
        m_out.flush();
    }

    ~Log()
    {
        std::cout << "Destr" << std::endl;
    }
};