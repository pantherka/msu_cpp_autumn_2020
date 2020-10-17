#include "tokenparser.h"

void TokenParser::Parse(const std::string &text) {
    std::string token;
    bool is_digit = true;
    for (auto stage : start) {
        stage(text);
    }
    for (size_t i = 0; i < text.size(); ++i) {
        if (std::isspace(text[i]) != 0) {
            if (token.size() == static_cast<size_t>(0)) {
                continue;
            }
            TokenCall(token, is_digit);
            is_digit = true;
            token.clear();
        }
        else {
            if ('0' >= text[i] || text[i] >= '9') {
                is_digit = false;
            }
            token.push_back(text[i]);
        }
    }
    if (token.size() > static_cast<size_t>(0)) {
        TokenCall(token, is_digit);
    }
    for (auto stage : end) {
        stage(text);
    }
}
void TokenParser::TokenCall(const std::string &token, bool is_digit) {
    for (auto stage : any_token) {
        stage(token);
    }
    if (is_digit) {
        for (auto stage : digit_token) {
            stage(token);
        }
    }
    else {
        for (auto stage : string_token) {
            stage(token);
        }
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

/*TokenParser::~TokenParser() {
    ;
}*/
