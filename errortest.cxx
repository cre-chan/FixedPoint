#include <FixedPoint.h>
#include <algorithm>
#include <iostream>

using namespace std;



int main(){
    // 二進数で表し切れる小数
    float acclist[5]={0.f,1.f,1.5f,1.25f,0.75f};
    uint32 bins[5]={0,1<<4,0x18,0x14,0xC};

    for(int i=0;i<5;i++){
        float v=acclist[i];
        FixedPoint<uint32,4> v2=FixedPoint<uint32,4>::fromFloat(v),ans(bins[i]);
        cout<<v<<" "<<v2<<endl;
        double diff=abs(v-v2.toDouble());
        if (diff)
            cerr<<"abserr="<<diff<<endl;
    }

    cout<<"------------"<<endl;

    // 二進数で表し切れない小数
    float errlist[5]={0.1f,1.1f,1.7f,4.6f,5.05f};
    for(int i=0;i<5;i++){
        float v=errlist[i];
        FixedPoint<uint32,4> v2=FixedPoint<uint32,4>::fromFloat(v);
        cout<<v<<" "<<v2<<endl;
        const double eps=1./(1<<4);
        double diff=abs(v-v2.toDouble());

        if (diff>=eps)
            cerr<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    cout<<"------------"<<endl;

    // 二進数で表し切れない小数
    for(int i=0;i<5;i++){
        float v=errlist[i];
        FixedPoint<uint32,8> v2=FixedPoint<uint32,8>::fromFloat(v);
        cout<<v<<" "<<v2<<endl;
        const double eps=1./(1<<8);
        double diff=abs(v-v2.toDouble());

        if (diff>=eps)
            cerr<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    return 0;
}