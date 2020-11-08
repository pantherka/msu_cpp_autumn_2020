#pragma once

#include <iostream>
#include <cctype>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    Error process(bool& elem) 
    {
        if (!elem)
        {
            out_ << "false";
        }
        else
        {
            out_ << "true";
        }
        return Error::NoError;
    }

    Error process(uint64_t& elem) 
    {
        out_ << elem;
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T&& elem, Args&&... args)
    {
        process(elem);
        out_ << Separator;
        return process(args...);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(args...);
    }
    
private:
    std::ostream& out_;
};


class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    Error process(bool& value)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error process(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        if (text.length() == 0)
        {
            return Error::CorruptedArchive;
        }
        size_t answer = 0;
        for (size_t i = 0; i < text.length(); ++i)
        {
            if (!std::isdigit(text[i]))
            {
                return Error::CorruptedArchive;
            }
            answer *= 10;
            answer += (text[i] - '0');
        }
        value = answer;
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T&& elem, Args&&... args)
    {
        Error err = process(elem);
        if (err == Error::CorruptedArchive)
        {
            return err; 
        }
        return process(args...);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(args...);
    }
    
private:
    std::istream& in_;
};
