#include "tokenparser.h"

void TokenParser::Parse(const std::string &text) {
    std::string token;
    bool is_digit = true;
    RunHandlers(start, text);
    for (size_t i = 0; i < text.size(); ++i) {
        if (std::isspace(text[i])) {
            if (token.size() == static_cast<size_t>(0)) {
                continue;
            }
            TokenCall(token, is_digit);
            is_digit = true;
            token.clear();
        }
        else {
            if (!std::isdigit(text[i])) {
                is_digit = false;
            }
            token.push_back(text[i]);
        }
    }
    if (token.size() > static_cast<size_t>(0)) {
        TokenCall(token, is_digit);
    }
    RunHandlers(end, text);
}
void TokenParser::TokenCall(const std::string &token, bool is_digit) {
    RunHandlers(any_token, token);
    if (is_digit) {
        RunHandlers(digit_token, token);
    }
    else {
        RunHandlers(string_token, token);
    }
}

void TokenParser::RunHandlers(const std::vector<HandlerFunc> &callback, const std::string &token) {
    for (size_t i = 0; i < callback.size(); ++i) {
        callback[i](token);
    }
}

void TokenParser::SetStartCallback(HandlerFunc func) {
    start.push_back(func);
}
void TokenParser::SetAnyTokenCallback(HandlerFunc func) {
    any_token.push_back(func);
}
void TokenParser::SetDigitTokenCallback(HandlerFunc func) {
    digit_token.push_back(func);
}
void TokenParser::SetStringTokenCallback(HandlerFunc func) {
    string_token.push_back(func);
}
void TokenParser::SetEndCallback(HandlerFunc func) {
    end.push_back(func);
}

