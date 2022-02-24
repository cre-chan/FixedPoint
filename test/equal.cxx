#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){
    // 等しい数の比較が正しいどうかをチェック
    auto a=FP32<4>::fromFloat(1.5);
    auto b=FP32<2>::fromFloat(1.5);
    assert(a==b);

    // 右シフトすると精度落ちで等しいになるケース
    auto c=FP32<4>::fromFloat(0.5625);
    auto d=FP32<2>::fromFloat(0.5);

    assert(c!=d);

    // 等しい数の比較が正しいどうかをチェック
    auto e=FP64<4>::fromFloat(1.5);
    auto f=FP64<2>::fromFloat(1.5);
    assert(e==f);

    // 右シフトすると精度落ちで等しいになるケース
    auto g=FP64<4>::fromFloat(0.5625);
    auto h=FP64<2>::fromFloat(0.5);

    assert(g!=h);


    return 0;
}