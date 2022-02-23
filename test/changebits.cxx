#include <FixedPoint.h>
#include <iostream>

using namespace std;



int main(){

    float testcases[5]={(1./(1<<4)),0.5,-(1./(1<<4)),-0.5,0.};
    // 二進数で表現できる有理数
    for(int i=0;i<5;i++){
        float v=testcases[i];
        FP32<4> v2=FP32<4>::fromFloat(v);
        // コンパイルエラーが出ないことは型があっていること
        FP32<3> v3=v2.to<3>();
        cout<<v3<<" "<<v2<<endl;
        double diff=abs(v3.toDouble()-v2.toDouble());
        // これらの有理数はぴったり表現できるはず
        if (diff>(1./(1<<4)))
            cerr<<"abserr="<<diff<<endl;
    }

    cout<<"----------------------------"<<endl;

    float doublecases[5]={(1./(1<<4)),0.5,-(1./(1<<4)),-0.5,0.};
    // 二進数で表現できる有理数
    for(int i=0;i<5;i++){
        double v=testcases[i];
        FP64<4> v2=FP64<4>::fromFloat(v);
        // コンパイルエラーが出ないことは型があっていること
        FP64<3> v3=v2.to<3>();
        cout<<v3<<" "<<v2<<endl;
        double diff=abs(v3.toDouble()-v2.toDouble());
        // これらの有理数はぴったり表現できるはず
        if (diff>(1./(1<<4)))
            cerr<<"abserr="<<diff<<endl;
    }



    return 0;
}