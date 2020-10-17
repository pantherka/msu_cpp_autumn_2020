#include "tokenparser.h"
#include <iostream>
#include <cassert>

int start = 0;
int token = 0;
int digit = 0;
int string = 0;
int end = 0;

void test_start(const std::string &) {
    start++;
}

void test_token(const std::string &) {
    token++;
}

void test_digit(const std::string &) {
    digit++;
}

void test_string(const std::string &) {
    string++;
}
void test_end(const std::string &) {
    end++;
}

int main() {
    std::string test = "123 01ab  abcd\tJHG7\n jad12hug";
    TokenParser parser = TokenParser();
    parser.SetStartCallback(test_start);
    parser.Parse(static_cast<std::string>("")); // проверка, что можно часть функций и не давать
    assert(start == 1);

    parser.SetAnyTokenCallback(test_token);
    parser.SetDigitTokenCallback(test_digit);
    parser.SetStringTokenCallback(test_string);
    parser.SetEndCallback(test_end);
    parser.Parse(test);
    assert(start == 2);
    assert(token == 5); // проверка на двойные разделители, что нет пустых токенов
    assert(digit == 1); // проверка на цифры в начале, середине и конце фразы
    assert(string == 4); // проверка на распознавание строк
    assert(end == 1); // проверка на обработку после парсинга

    parser.SetStartCallback(test_start); // второе добавление функции
    parser.SetDigitTokenCallback(test_digit);
    parser.Parse(static_cast<std::string>("abc "));
    assert(start == 4);
    assert(end == 2);
    assert(digit == 1);
    assert(string == 5);
    assert(token == digit + string);

    std::cout << "All tests passed." << std::endl;
    return 0;
}