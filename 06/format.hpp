#pragma once

#include <string>
#include <system_error>
#include <sstream>


struct ArgumentError : public std::exception // несоответствие числа аргументов требуемому
{
};

struct StringError : public std::exception // некорректное использование фигурных скобок
{
};

template <typename T, typename ... Args>
void process(std::stringstream& out, size_t n, T&& elem)
{
    if (n != 0)
    {
        throw ArgumentError();
    }
    out << elem;
}

template <typename T, typename ... Args>
void process(std::stringstream& out, size_t n, T&& elem, Args&&... args)
{
    if (n == 0)
    {
        out << elem;
        return;
    }
    process(out, n - 1, args...);
}

template <typename ... Args>
std::string format(std::string&& buf, Args&&... args) 
{
    std::stringstream out;
    size_t prev = 0;
    size_t open = buf.find("{");
    size_t close = buf.find("}");
    while (open != std::string::npos)
    {
        size_t index = 0;
        if (close == std::string::npos || close <= open + 1)
        {
            throw StringError();
        }
        out << buf.substr(prev, open - prev);
        std::string text = buf.substr(open + 1, close - open - 1);
        try
        {
            index = std::stoull(text);
            process(out, index, args...);
            prev = close + 1;
            open = buf.find("{", open + 1);
            close = buf.find("}", close + 1);
        }
        catch (const std::logic_error& e)
        {
            throw StringError();
        }
    }
    if (close != std::string::npos)
    {
        throw StringError();
    }
    out << buf.substr(prev);
    return out.str();
}
