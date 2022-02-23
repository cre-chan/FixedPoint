#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){
    float op1[5]={0.,0.5,1.5,2.0,1.6};
    float op2[5]={3.,0.3,1.5,2.1,1.7};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FixedPoint<uint32,4> v3=FixedPoint<uint32,4>::fromFloat(v1);
        auto v4=FixedPoint<uint32,4>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<endl;
        }
    }


    return 0;
}