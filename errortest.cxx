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
        cout<<v<<" "<<v2<<" "<<ans<<endl;
        cout<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    return 0;
}