#include <iostream>
#include <FixedPoint.h>
#include <SFINAEtest.h>


using namespace std;

int main(){
    FixedPoint<uint32,0> zero(0);
    FixedPoint<uint32,1> half(1);

    // ゼロが正しく出力されるかを確認
    cout<<zero<<endl;

    // 0.5が正しく出力されるかを確認
    cout<<half<<endl;

    cout<<half+half<<endl;
    cout<<half-half<<endl;


    return 0;
}