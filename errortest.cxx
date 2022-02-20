#include <FixedPoint.h>
#include <algorithm>
#include <iostream>

using namespace std;



int main(){
    // 二進数で表し切れる小数
    float acclist[5]={0.f,1.f,1.5f,1.25f,0.75f};

    // fromFloatが正しく動作するかをテスト
    // 参考値 実際値　を一行に出力
    // 誤差が閾値を上回る場合abserr=?を出力

    // 二進数で表現できる有理数
    for(int i=0;i<5;i++){
        float v=acclist[i];
        FixedPoint<uint32,4> v2=FixedPoint<uint32,4>::fromFloat(v);
        cout<<v<<" "<<v2<<endl;
        double diff=abs(v-v2.toDouble());
        // これらの有理数はぴったり表現できるはず
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
        double diff=abs(v-v2.toDouble());

        // nビットで小数部を表す時に誤差は1/(2^n+1)以下
        // 誤差が出る場合切り捨てが正しく行われてない可能性ある
        const double eps=1./(1<<5);
        if (diff>=eps)
            cerr<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    cout<<"------------"<<endl;

    // 二進数で表し切れない小数
    for(int i=0;i<5;i++){
        float v=errlist[i];
        FixedPoint<uint32,8> v2=FixedPoint<uint32,8>::fromFloat(v);
        cout<<v<<" "<<v2<<endl;
        
        double diff=abs(v-v2.toDouble());

        // nビットで小数部を表す時に誤差は1/(2^n+1)以下
        // 誤差が出る場合切り捨てが正しく行われてない可能性ある
        const double eps=1./(1<<9);
        if (diff>=eps)
            cerr<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    cout<<"------------"<<endl;

    // minusの数を表現できるかを確認
    float minuslist[5]={-0.5,-0.25,-0.3,-0.7,-2.8};
    for(int i=0;i<5;i++){
        float v=minuslist[i];
        FixedPoint<uint32,8> v2=FixedPoint<uint32,8>::fromFloat(v);
        cout<<v<<" "<<v2<<endl;
        double diff=abs(v-v2.toDouble());

        // nビットで小数部を表す時に誤差は1/(2^n+1)以下
        // 誤差が出る場合切り捨てが正しく行われてない可能性ある
        const double eps=1./(1<<9);
        if (diff>=eps)
            cerr<<"abserr="<<abs(v-v2.toDouble())<<endl;
    }

    return 0;
}