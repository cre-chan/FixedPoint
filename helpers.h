#pragma once

#include <typealias.h>

// 下nビットを獲得するマスクの生成
constexpr uint64 lsnbits(int n){
    return ~((~0ull)<<n);
}

// valueを右にshiftビットシフトする
// 誤差を考慮する
template<class ui>
ui rsWithCarry(ui value,uint32 shift){
    if (shift==0) return value;
    uint32 bit=((value>>(shift-1))&1u);
    value>>=shift;
    if (bit) value++;
    return value;
}

bool plusOverflowed(ll a,ll b,ll out){
    if (a>=0&&b>=0&&out<0) return true;
    if (a<0&&b<0&&out>=0) return true;
    return false;
}