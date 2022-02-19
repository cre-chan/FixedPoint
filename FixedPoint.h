#pragma once

#include <iostream>

using namespace std;

using uint32 = unsigned int;
using uint64 = unsigned long long int;

template<class INTLIKE,uint32 bits>
class FixedPoint;

// 下nビットを獲得するマスクの生成
constexpr uint32 lsnbits(int n){
    return ~((~0u)<<n);
}

/*
 32ビットを使って固定小数点を表現する
 */
template<uint32 bits>
class FixedPoint<uint32,bits>{
    static_assert(bits<=32,"Cannot specify more than 32 bits to represents float parts.");

    using Self=FixedPoint<uint32,bits>;

    private:
        // シフト操作の挙動を限定するために符号なし32ビット整数を使う
        uint32 data;

    public:
        // 二進数データをそのまま指定
        FixedPoint(uint32 dat):data(dat){}

        static Self fromFloat(float v){
            if (v==0.f) return FixedPoint(0);
            // vの中身をそのままbにコピー
            uint32 b=(*(uint32*)(&v));
            // 単精度浮動小数の仮数は下23位
            uint32 frac=b&lsnbits(23);
            // 負の数に対応するため
            uint32 sign=(1u<<31)&b;
            // 仮数に省略された1を補足
            frac=frac|(1<<23);
            // 指数部の桁履きをなくす
            int exp=((b>>23)&lsnbits(8))-127;
            
            // 左にシフトのビット数を算出
            // 今小数点は23ビットにいる
            // なので左にexp位シフトした後右に23-bitsビットシフトすべき
            int offset=exp-(23-bits);

            if (offset>=0){
                frac<<=offset;
            }else{
                frac>>=(-offset);
            }

            if (sign!=0) frac=-frac;

            return FixedPoint(frac);
        }

        Self operator+(const Self& another) const noexcept{
            uint32 tmp=another.data+this->data;
            return FixedPoint(tmp);
        }

        Self operator-(const Self& another) const noexcept{
            uint32 tmp=this->data-another.data;
            return FixedPoint(tmp);
        }

        Self operator*(const Self& another) const noexcept{
            uint32 op1=this->data,op2=another.data;
            int sign=0;
            if (op1&(1<<31)) {
                sign++;
                op1=-op1;
            }
            if (op2&(1<<31)) {
                sign++;
                op2=-op2;
            }

            uint64 tmp=((uint64)op1)*((uint64)op2);
            
            tmp>>=bits;
            if (sign%2) tmp=-tmp;
            return FixedPoint(tmp);
        }

        Self operator/(const Self& another) const{
            uint32 op1=this->data,op2=another.data;
            int sign=0;
            if (op1&(1<<31)) {
                sign++;
                op1=-op1;
            }
            if (op2&(1<<31)) {
                sign++;
                op2=-op2;
            }
            uint64 tmp=(((uint64)op1)<<32)/op2;
            int offset=32-bits;
            tmp>>=offset;
            if (sign%2) tmp=-tmp;
            return FixedPoint(tmp);
        }

        bool operator==(const Self& another) const noexcept{
            return this->data==another.data;
        }

        double toDouble() const{
            if (data==0) return 0.;

            
            uint64 exppart=0;
            uint32 tmp=data;
            uint32 sign=(1<<31)&data;
            // 負の数の場合に対応
            if (sign!=0) tmp=-tmp;

            uint32 dataDup=tmp;

            while(tmp>1) {
                exppart++;
                tmp>>=1;
            }

            

            uint64 frac=lsnbits(exppart)&dataDup;

            frac<<=(52-exppart);
            exppart-=bits;
            exppart+=1023;
            uint64 value=(exppart<<52)|frac;

            // 符号ビットを設定する
            // ullを使うことで63ビットのシフトを許す
            if (sign) value|=(1ull<<63);
            
            double ret;
            // ポインタを使って型変換を回避
            *((uint64*)(&ret))=value;

            return ret;
        }

        friend ostream& operator<<(ostream& out,const Self& n){
            out<<n.toDouble();
            return out;
        }

        
};


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
