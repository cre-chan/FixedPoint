#include <iostream>
#include <FixedPoint.h>
#include <SFINAEtest.h>


using namespace std;

int main(){
    FixedPoint<uint32,0> zero(0);
    FixedPoint<uint32,1> half(1);
    FixedPoint<uint32,2> a(4),b(8);
    FixedPoint<uint32,16> c(1u<<20),d(1u<<20);

    // ゼロが正しく出力されるかを確認
    cout<<zero<<endl;

    // 0.5が正しく出力されるかを確認
    cout<<half<<endl;

    // 四則演算が正しいかどうかを確認
    cout<<half+half<<endl;
    cout<<half-half<<endl;
    cout<<a*b<<endl;
    cout<<b/b<<endl;

    // オーバーフローがある場合の動きを確認
    cout<<c*d<<endl;

    return 0;
}