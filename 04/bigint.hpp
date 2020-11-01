#include <iostream>

#ifndef BIGINT_H
#define BIGINT_H

class BigInt {
    static const int BASE = 10;
    int* digits = nullptr;
    size_t len = 0;
    bool is_negative = false;
public:
    BigInt() = default;
    BigInt(const std::string& str);
    BigInt(int num);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other);
    BigInt& operator=(const BigInt& copied);
    BigInt& operator=(BigInt&& moved);
    friend std::ostream& operator<<(std::ostream& ostream, const BigInt& bigint);
    bool operator==(const BigInt& other) const;
    bool operator==(int other) const;
    bool operator!=(const BigInt& other) const;
    bool operator!=(int other) const;
    bool operator<(const BigInt& other) const;
    bool operator<(int other) const;
    bool operator<=(const BigInt& other) const;
    bool operator<=(int other) const;
    bool operator>(const BigInt& other) const;
    bool operator>(int other) const;
    bool operator>=(const BigInt& other) const;
    bool operator>=(int other) const;
    BigInt operator-() const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator+(int other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator-(int other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator*(int other) const;
    ~BigInt();
};

#endif
