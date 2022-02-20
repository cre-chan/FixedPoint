#include <FixedPoint.h>
#include <algorithm>
#include <iostream>

using namespace std;



int main(){

    float acclist[5]={0.25,0.125,-0.375,-9.5,10.25};

    // 二進数で表現できる有理数
    for(int i=0;i<5;i++){
        float v=acclist[i];
        FP64<16> a=FP64<16>::fromFloat(v);
        cout<<v<<" "<<a<<endl;
        float abserr=abs(a.toDouble()-v);
        if (abserr!=0.)
            cout<<"abserr="<<abserr<<endl;
    }

    cout<<"--------------"<<endl;

    // 二進数で表現しきれない有理数の誤差をチェック
    float errlist[5]={0.9,10.007,8.567,-9.99,-0.67};
    for(int i=0;i<5;i++){
        float v=errlist[i];
        FP64<16> a=FP64<16>::fromFloat(v);
        cout<<v<<" "<<a<<endl;
        float abserr=abs(a.toDouble()-v);
        if (abserr>=(1./(1<<16)))
            cout<<"abserr="<<abserr<<endl;
    }

    cout<<"--------------"<<endl;

    double doublelist[5]={0.9,-0.33,999999999.75,1234567.66,-5432100.7};
    for(int i=0;i<5;i++){
        double v=doublelist[i];
        FP64<16> a=FP64<16>::fromDouble(v);
        cout<<v<<" "<<a<<endl;
        float abserr=abs(a.toDouble()-v);
        if (abserr>=(1./(1<<16)))
            cout<<"abserr="<<abserr<<endl;
    }

    cout<<"--------------"<<endl;

    double doubleacclist[5]={0.25,0.125,-0.375,-9.5,10.25};
    for(int i=0;i<5;i++){
        double v=doubleacclist[i];
        FP64<16> a=FP64<16>::fromDouble(v);
        cout<<v<<" "<<a<<endl;
        float abserr=abs(a.toDouble()-v);
        if (abserr>=(1./(1<<16)))
            cout<<"abserr="<<abserr<<endl;
    }

    return 0;
}