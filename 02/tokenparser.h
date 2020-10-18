#include <string>
#include <functional>
#include <vector>

using HandlerFunc = std::function<void (const std::string &)>;

class TokenParser
{
    std::vector<HandlerFunc> start = {};    
    std::vector<HandlerFunc> any_token = {};
    std::vector<HandlerFunc> string_token = {};
    std::vector<HandlerFunc> digit_token = {};
    std::vector<HandlerFunc> end = {};
    
    public:
        TokenParser() {;};
        void Parse(const std::string &text);
        void TokenCall(const std::string &token, bool is_digit);
        void RunHandlers(const std::vector<HandlerFunc> &callback, const std::string &token);
        void SetStartCallback(HandlerFunc func);
        void SetAnyTokenCallback(HandlerFunc func);
        void SetDigitTokenCallback(HandlerFunc func);
        void SetStringTokenCallback(HandlerFunc func);
        void SetEndCallback(HandlerFunc func);
};
