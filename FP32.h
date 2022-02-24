#pragma once 

#include <iostream>
#include <helpers.h>
#include <typealias.h>


using namespace std;

/*
 32ビットを使って固定小数点を表現する
 */
template<uint32 bits>
class FixedPoint<uint32,bits>{
    static_assert(bits<=31,"Cannot specify more than 31 bits to represents float parts.");

    using Self=FixedPoint<uint32,bits>;

    public:
        // シフト操作の挙動を限定するために符号なし32ビット整数を使う
        uint32 data;

    public:
        // 二進数データをそのまま指定
        FixedPoint(uint32 dat):data(dat){}

        // コピー関数
        FixedPoint(const Self& another):data(another.data){}

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
                // シフトで省略されたbitの値を取得
                frac=rsWithCarry(frac,-offset);
            }

            if (sign!=0) frac=-frac;

            return FixedPoint(frac);
        }

        // e.g t=-t
        Self operator-(){
            return FixedPoint(-data);
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
            
            tmp=rsWithCarry(tmp,bits);
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
            tmp=rsWithCarry(tmp,offset);
            if (sign%2) tmp=-tmp;
            return FixedPoint(tmp);
        }

        bool operator==(const Self& another) const noexcept{
            return this->data==another.data;
        }

        Self operator+(int other) const noexcept{
            if (other<0){
                other=-other;
                other<<=bits;
                other=-other;
            }else {
                other<<=bits;
            }

            uint32 dat=data+other;
            return Self(dat);
        }

        Self operator-(int other) const noexcept{
            return (*this)-other;
        }

        Self operator*(int another) const noexcept{
            uint32 op1=this->data,op2=another;
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
            
            // tmp>>=bits;
            if (sign%2) tmp=-tmp;
            return FixedPoint(tmp);
        }

        Self operator/(int another) const{
            uint32 op1=this->data,op2=another;
            int sign=0;
            if (op1&(1<<31)) {
                sign++;
                op1=-op1;
            }
            if (op2&(1<<31)) {
                sign++;
                op2=-op2;
            }

            uint64 divisor=((uint64)op2)<<bits;
            uint64 tmp=(((uint64)op1)<<32)/divisor;
            int offset=32-bits;
            tmp=rsWithCarry(tmp,offset);
            if (sign%2) tmp=-tmp;
            return FixedPoint(tmp);
        }

        template<uint32 len>
        bool operator<=(const FixedPoint<uint32,len>& another) const noexcept{
            const uint32 thisint=((int)this->data)>>bits,anotherint=((int)another.data)>>len;
            const uint32 thisfrac=this->data<<(31-bits),anotherfrac=another.data<<(31-len);
            uint64 thisext=thisint*(1ull<<32)+thisfrac,anotherext=anotherint*(1ull<<32)+anotherfrac;
            long long int diff=anotherext-thisext;

            return diff>=0;
        }

        // 小数部の長さが同じの場合を特殊処理
        // 比較を早くできる
        bool operator<=(const Self& another) const noexcept{
            int thisdata=this->data,anotherdata=another.data;
            return thisdata<=anotherdata;
        }

        template<uint32 len>
        bool operator>=(const FixedPoint<uint32,len>& another) const noexcept{
            return another<=*this;
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

        // 小数部の長さを変える
        // 新しいFPを戻す
        template<uint32 target>
        FixedPoint<uint32,target> to() const noexcept{
            // 符号付き整数を使うことで右シフトの時の符号を処理s
            long long int tmp=(int)this->data;
            int sign=tmp>=0;
            if (!sign) tmp=-tmp;
            if (target>=bits){
                tmp<<=(target-bits);
            }else{
                tmp=rsWithCarry(tmp,bits-target);
            }

            if (!sign) tmp=-tmp;

            return FixedPoint<uint32,target>(tmp);
        }
};


template<uint32 bits>
FixedPoint<uint32,bits> operator+(int a,const FixedPoint<uint32,bits>& b){
    return b+a;
}

template<uint32 bits>
FixedPoint<uint32,bits> operator-(int a,const FixedPoint<uint32,bits>& b){
    return -b+a;
}

template<uint32 bits>
FixedPoint<uint32,bits> operator*(int a,const FixedPoint<uint32,bits>& b){
    return b*a;
}