#include "bigint.hpp"

BigInt::BigInt(const std::string& str) {
    if (str.length() == 0) {
        return;
    }
    std::string str1 = str;
    if (str1[0] == '-') {
        this->is_negative = true;
        str1 = str1.substr(1);
    }
    size_t index = 0;
    while (index < str1.length() && str1[index] == '0') { ++index; };
    str1 = str1.substr(index);
    if (str1.length() == 0) {
        return;
    }
    index = str1.length();
    this->len = index;
    this->digits = new int[index];
    for (int i = static_cast<int>(str1.length()) - 1; i >= 0; --i) {
        digits[len - i - 1] = static_cast<int>(str1[i] - '0');
    }
}

BigInt::BigInt(int num) {
    if (num == 0) {
        return;
    }
    if (num < 0) {
        this->is_negative = true;
        num = -num;
    }
    size_t i = 0;
    int num1 = num;
    for (; num1 > 0; ++i) { num1 /= BigInt::BASE; }
    this->len = i;
    this->digits = new int[i];

    i = 0;
    for(; num > 0; ++i) {
        digits[i] = num % BigInt::BASE;
        num /= BigInt::BASE;
    }
}

BigInt::BigInt(const BigInt& other) : len(other.len), is_negative(other.is_negative) {
    digits = new int[len];
    std::copy(other.digits, other.digits + len, digits);
}

BigInt& BigInt::operator=(const BigInt& copied) {
    if (this == &copied) {
        return *this;
    }
    len = copied.len;
    is_negative = copied.is_negative;
    if (digits) {
        delete[] digits;
    }
    digits = new int[len];
    std::copy(copied.digits, copied.digits + len, digits);
    return *this;
}

BigInt::BigInt(BigInt&& other) : len(other.len), is_negative(other.is_negative) {
    digits = new int[len];
    digits = other.digits;
    other.digits = nullptr;
    other.len = 0;
    other.is_negative = false;
}

BigInt& BigInt::operator=(BigInt&& moved) {
    if (this == &moved) {
        return *this;
    }
    len = std::move(moved.len);
    is_negative = std::move(moved.is_negative);
    digits = moved.digits;
    moved.digits = nullptr;
    moved.len = 0;
    moved.is_negative = false;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const {
    if (this->is_negative != other.is_negative) {
        return false;
    }
    if (this->len != other.len) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (this->digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator==(int other) const {
    return *this == BigInt(other);
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(this == &other);
}

bool BigInt::operator!=(int other) const {
    return *this != BigInt(other);
}

BigInt BigInt::operator-() const {
    BigInt answer = *this;
    if (len == 0) {
        return answer;
    }
    answer.is_negative = !is_negative;
    return answer;
}

bool BigInt::operator<(const BigInt& other) const {
    if (is_negative) {
        if (other.is_negative) {
            return (-other) < (-*this);
        }
        return true;
    }
    if (other.is_negative) {
        return false;
    }
    if (len != other.len) {
        return len < other.len;
    }
    for (int i = static_cast<int>(len); i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool BigInt::operator<(int other) const {
    return *this < BigInt(other);
}

bool BigInt::operator<=(const BigInt& other) const {
    return ((*this) < other || (*this) == other);
}
bool BigInt::operator<=(int other) const {
    return *this <= BigInt(other);
}

bool BigInt::operator>(const BigInt& other) const {
    return !((*this) <= other);
}
bool BigInt::operator>(int other) const {
    return *this > BigInt(other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !((*this) < other);
}
bool BigInt::operator>=(int other) const {
    return *this >= BigInt(other);
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (this->is_negative) {
        if (other.is_negative) {
            return -((-other) + (-*this));
        }
        return other - (-*this);
    }
    if (other.is_negative) {
        return *this - (-other);
    }
    BigInt answer;
    answer.digits = new int[std::max(len, other.len) + 1];
    int carry = 0;
    size_t i = 0;
    for (; i < std::max(len, other.len); ++i) {
        answer.digits[i] = carry;
        if (i < len) {
            answer.digits[i] += digits[i];
        }
        if (i < other.len) {
            answer.digits[i] += other.digits[i];
        }
        carry = (answer.digits[i] >= BigInt::BASE);
        if (carry != 0) {
            answer.digits[i] -= BigInt::BASE;
        }    
    }
    if (carry != 0) {
        answer.digits[i] = carry;
        ++i;
    }
    answer.len = i;
    return answer;
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (other.is_negative) {
        return *this + (-other);
    }
    if (this->is_negative) {
        return -(other + (-*this));
    }
    if (*this < other) {
        return -(other - *this);
    }
    BigInt answer;
    answer.len = std::max(len, other.len);
    answer.digits = new int[answer.len];
    int carry = 0;
    bool flag = true;
    for (size_t i = 0; i < other.len || carry != 0; ++i) {
        answer.digits[i] = digits[i] - carry - (i < other.len ? other.digits[i] : 0);
        carry = (answer.digits[i] < 0);
        if (carry != 0) {
            answer.digits[i] += BigInt::BASE;
        }
        if (flag) {
            if (answer.digits[i] == 0) {
                answer.len--; // учёт ведущих нулей
            }
            else {
                flag = false;
            }
        }
    }
    return answer;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt answer;
    answer.digits = new int[len + other.len];
    answer.len = 0;
    size_t real_len = 0;
    for (size_t i = 0; i < len; ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.len || carry != 0; ++j) {
            int cur = answer.digits[i + j] +
                            digits[i] * (j < other.len ? other.digits[j] : 0) + carry;
            answer.digits[i + j] = cur % BigInt::BASE;
            carry = cur / BigInt::BASE;
            if (i + j > real_len) {
                real_len = i + j; // подсчёт реальной длины числа
            }
        }
    }
    answer.len = real_len + 1;
    answer.is_negative = (is_negative != other.is_negative);
    return answer;
}

BigInt BigInt::operator+(int other) const {
    return *this + BigInt(other);
}

BigInt BigInt::operator-(int other) const {
    return *this - BigInt(other);
}

BigInt BigInt::operator*(int other) const {
    return *this * BigInt(other);
}

std::ostream& operator<<(std::ostream& ostream, const BigInt& bigint) {
    if (bigint.len == 0){
        return ostream << 0;
    }
    if (bigint.is_negative) {
        ostream << '-';
    }
    for(size_t i = bigint.len; i > 0; --i) {
        ostream << bigint.digits[i - 1];
    }
    return ostream;
}

BigInt::~BigInt() {
    if (this->digits) {
        delete[] this->digits;
    }
}
