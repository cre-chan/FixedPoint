#include <FixedPoint.h>
#include <iostream>

using namespace std;

void test1(){
    /*
    固定小数点小数と整数の足し算
     */
    float op1[5]={0.,3.,-5.5,5.6,-7.};
    int op2[5]={0,-2,3,3,5};

    for(int i=0;i<5;i++){
        float v1=op1[i];
        int v2=op2[i];
        float ans=v1+v2;
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto tmp=v3+v2;
        cout<<ans<<" "<<tmp<<endl;
        const double abserr=abs(tmp.toDouble()-ans);
        if (abserr>(1./(1<<5)))
            cout<<"abserr="<<abserr<<endl;
    }
}

void test2(){
    /*
    整数と固定小数点小数の足し算
     */
    float op1[5]={0.,3.,-5.5,5.6,-7.};
    int op2[5]={0,-2,3,3,5};

    for(int i=0;i<5;i++){
        float v1=op1[i];
        int v2=op2[i];
        float ans=v1+v2;
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto tmp=v2+v3;
        cout<<ans<<" "<<tmp<<endl;
        const double abserr=abs(tmp.toDouble()-ans);
        if (abserr>(1./(1<<5)))
            cout<<"abserr="<<abserr<<endl;
    }
}

void test3(){
    /*
    逆数を取る操作
     */
    float op1[5]={0.,3.,-5.5,5.6,-7.};

    for(int i=0;i<5;i++){
        float v1=op1[i];
        float ans=-v1;
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto tmp=-v3;
        cout<<ans<<" "<<tmp<<endl;
        const double abserr=abs(tmp.toDouble()-ans);
        if (abserr>(1./(1<<5)))
            cout<<"abserr="<<abserr<<endl;
    }
}

void test4(){
    /*
    整数と固定小数点小数の掛け算
     */
    float op1[5]={0.,3.,-5.5,5.6,-7.};
    int op2[5]={0,-2,3,3,5};

    for(int i=0;i<5;i++){
        float v1=op1[i];
        int v2=op2[i];
        
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto tmp=v2*v3;
        // 掛け算の誤差計算に要注意
        float ans=v3.toDouble()*v2;
        cout<<ans<<" "<<tmp<<endl;
        const double abserr=abs(tmp.toDouble()-ans);
        if (abserr>(1./(1<<5)))
            cout<<"abserr="<<abserr<<endl;
    }
}

void test5(){
    /*
    整数と固定小数点小数の掛け算
     */
    float op1[5]={0.,3.,-5.5,5.6,-7.};
    int op2[5]={1,-2,3,3,5};

    for(int i=0;i<5;i++){
        float v1=op1[i];
        int v2=op2[i];
        
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto tmp=v3/v2;
        // 掛け算の誤差計算に要注意
        float ans=v3.toDouble()/v2;
        cout<<ans<<" "<<tmp<<endl;
        const double abserr=abs(tmp.toDouble()-ans);
        if (abserr>(1./(1<<5)))
            cout<<"abserr="<<abserr<<endl;
    }
}

int main(){
    

    test1();
    cout<<"-------------------"<<endl;
    test2();
    cout<<"-------------------"<<endl;
    test3();
    cout<<"-------------------"<<endl;
    test4();
    cout<<"-------------------"<<endl;
    test5();
    

    return 0;
}