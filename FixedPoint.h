#pragma once

#include <iostream>
#include <typealias.h>
#include <helpers.h>
#include <FP32.h>
#include <FP64.h>

using namespace std;





// 32ビット固定小数点小数の略称
template<uint32 bits>
using FP32=FixedPoint<uint32,bits>;

// 64ビット固定小数点小数の略称
template<uint32 bits>
using FP64=FixedPoint<uint64,bits>;


// friend ostream& operator<<(ostream& out,const Self& n){
        //     const uint32 digits=31-bits;

        //     // 整数部を取り出す
        //     int i=(n.data>>bits);
        //     if (i&(1<<digits)) i-=(1<<digits);

        //     out<<i<<'.';

        //     // 小数部を取り出す
        //     const uint32 mask=lsnbits(bits);
        //     int f=n.data&mask;

        //     do{
        //         uint mask=1u<<bits;
        //         int d=f*10/mask;
        //         cout<<d;
        //         f=f*10%mask;
        //     }while(f!=0);

        //     return out;
        // }
