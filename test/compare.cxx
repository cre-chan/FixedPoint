#include <FixedPoint.h>
#include <iostream>

using namespace std;

void test1(){
    /*
     case 0 0.0<3.0 精度落ちしない
     case 1 0.5>0.3 精度落ちしない
     case 2 1.5==1.5 精度落ちしない
     case 3 0.5625>0.5 精度が違う比較でも正しく作動する
     case 4 非常に大きいケースに対してシフトしたかをチェック
     */
    float op1[5]={0.,0.5,1.5,0.5+(1./16),(1<<23)+(1./16)};
    float op2[5]={3.,0.3,1.5,0.5,(1<<23)+(1./2)};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FP32<4> v3=FP32<4>::fromFloat(v1);
        auto v4=FP32<2>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<v1<<">"<<v2<<endl;
        }
    }
}

void test2(){
    // 負の数の比較ができるかどうかをチェック
    float op1[5]={-0.,0.,-1.5,0.5+(1./16),-5.6};
    float op2[5]={3.,0.3,1.5,-0.5,-3.};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FP32<4> v3=FP32<4>::fromFloat(v1);
        auto v4=FP32<2>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<v1<<">"<<v2<<endl;
        }
    }
}

void test3(){
    // 同じビット数の時正しい比較関数を選んだかをチェック
    float op1[5]={-0.,0.,-1.5,0.5+(1./16),-5.6};
    float op2[5]={3.,0.3,1.5,-0.5,-3.};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FP32<4> v3=FP32<4>::fromFloat(v1);
        auto v4=FP32<4>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<v1<<">"<<v2<<endl;
        }
    }
}

void test4(){
    // 同じビット数の時正しい比較関数を選んだかをチェック
    float op1[5]={-0.,0.,-1.5,0.5+(1./16),-5.6};
    float op2[5]={3.,0.3,1.5,-0.5,-3.};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto v4=FP64<4>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<v1<<">"<<v2<<endl;
        }
    }
}

void test5(){
    // 64ビットの比較ができるかどうかをチェック
    float op1[5]={-0.,0.,-1.5,0.5+(1./16),-5.6};
    float op2[5]={3.,0.3,1.5,-0.5,-3.};

    for(int i=0;i<5;i++){
        float v1=op1[i],v2=op2[i];
        float ans=v1+v2;
        FP64<4> v3=FP64<4>::fromFloat(v1);
        auto v4=FP64<2>::fromFloat(v2);

        if ((v1<=v2)==(v3<=v4)){
            cout<<"passed "<<i<<endl;
        }else{
            cout<<"failed "<<i<<v1<<">"<<v2<<endl;
        }
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