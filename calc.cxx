#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){

    float operand1[5]={0.f,2.0f,-1.3f,4.4f,3.3f};
    float operand2[5]={-0.3f,1.3f,-1.3f,-0.25f,8.2f};

    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        float ans=v1+v2;
        FixedPoint<uint32,8> v3=FixedPoint<uint32,8>::fromFloat(v1),v4=FixedPoint<uint32,8>::fromFloat(v2);

        double op1err=abs(v1-v3.toDouble()),op2err=abs(v2-v4.toDouble());

        FixedPoint<uint32,8> tmp=v3+v4,ansFixed=FixedPoint<uint32,8>::fromFloat(ans);
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs((ansFixed-tmp).toDouble());
        // オーバーフローがない場合は変換誤差のみ考える
        if (abserr>(1./(1<<7)))
            cerr<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;

    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        float ans=v1*v2;
        FixedPoint<uint32,8> v3=FixedPoint<uint32,8>::fromFloat(v1),v4=FixedPoint<uint32,8>::fromFloat(v2);

        FixedPoint<uint32,8> tmp=v3*v4,ansFixed=FixedPoint<uint32,8>::fromFloat(ans);
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs((ansFixed-tmp).toDouble());
        cout<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;

    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        float ans=v1/v2;
        FixedPoint<uint32,16> v3=FixedPoint<uint32,16>::fromFloat(v1),v4=FixedPoint<uint32,16>::fromFloat(v2);

        FixedPoint<uint32,16> tmp=v3/v4,ansFixed=FixedPoint<uint32,16>::fromFloat(ans);
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs((ansFixed-tmp).toDouble());
        cout<<"abserr="<<abserr<<endl;
    }


    return 0;
}