#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){

    float operand1[5]={0.f,2.0f,-1.3f,4.4f,3.3f};
    float operand2[5]={-0.3f,1.3f,-1.3f,-0.25f,8.2f};

    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        float ans=v1+v2;
        FP64<16> v3=FP64<16>::fromDouble(v1),v4=FP64<16>::fromDouble(v2);

        
        auto tmp=v3+v4;
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(tmp.toDouble()-ans);
        // オーバーフローがない場合は変換誤差のみ考える
        if (abserr>(1./(1<<16)))
            cerr<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;

    double dop1[5]={0.9,-0.33,999999999.75,1234567.66,-5432100.7};
    double dop2[5]={0.25,0.125,-0.375,-9.5,10.25};
    for(int i=0;i<5;i++){
        double v1=dop1[i],v2=dop2[i];
        double ans=v1+v2;
        FP64<16> v3=FP64<16>::fromDouble(v1),v4=FP64<16>::fromDouble(v2);

        
        auto tmp=v3+v4;
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(tmp.toDouble()-ans);
        // オーバーフローがない場合は変換誤差のみ考える
        if (abserr>(1./(1<<16)))
            cerr<<"abserr="<<abserr<<endl;
    }


    return 0;
}