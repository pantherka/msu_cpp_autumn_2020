#include "serializer.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct FakeData
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

int main()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    std::stringstream stream1;
    Serializer serializer1(stream1);
    Deserializer deserializer1(stream1);


    FakeData y1 {1, 2, 3};
    serializer1.save(x);
    
    const Error err1 = deserializer1.load(y1);
    assert(err1 == Error::CorruptedArchive);

    deserializer1.load(y1);
    std::cout << "All tests passed." << std::endl;
    return 0;
}
