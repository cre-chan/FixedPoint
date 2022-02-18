#pragma once

/*
 このファイルはSFINAEに関するテスト用ファイルです
 */

using uint32 = unsigned int;
using uint64 = unsigned long long int;

template<uint32 i>
class Factorial{
    public:
        static const uint32 value=i*Factorial<i-1>::value;
};

template<>
class Factorial<0>{
    public:
        static const uint32 value=1;
};