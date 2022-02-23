#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){

    // FP64<16>::fromFloatから得られたデータで足し算を行う
    // 参考値 実際値　を一行に出力
    // 誤差が閾値を上回る場合abserr=?を出力

    float operand1[5]={0.f,2.0f,-1.3f,4.4f,3.3f};
    float operand2[5]={-0.3f,1.3f,-1.3f,-0.25f,8.2f};

    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        float ans=v1+v2;
        FP64<16> v3=FP64<16>::fromFloat(v1),v4=FP64<16>::fromFloat(v2);

        auto tmp=v3+v4;
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(tmp.toDouble()-ans);
        // nビットで小数部を表す時に誤差は1/(2^n+1)以下
        // なので足し算する時誤差は1/(2^n)以下
        if (abserr>(1./(1<<16)))
            cerr<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;


    // FP64<16>::fromDoubleから得られたデータで足し算を行う
    // 参考値 実際値　を一行に出力
    // 誤差が閾値を上回る場合abserr=?を出力
    double dop1[5]={0.9,-0.33,999999999.75,1234567.66,-5432100.7};
    double dop2[5]={0.25,0.125,-0.375,-9.5,10.25};
    for(int i=0;i<5;i++){
        double v1=dop1[i],v2=dop2[i];
        double ans=v1+v2;
        FP64<16> v3=FP64<16>::fromDouble(v1),v4=FP64<16>::fromDouble(v2);

        auto tmp=v3+v4;
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(tmp.toDouble()-ans);
        // nビットで小数部を表す時に誤差は1/(2^n+1)以下
        // なので足し算する時誤差は1/(2^n)以下
        if (abserr>(1./(1<<16)))
            cerr<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;


    // FP64で割り算を行う
    // 参考値 実際値　を一行に出力
    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        // float ans=v1/v2;
        auto v3=FP64<16>::fromFloat(v1),v4=FP64<16>::fromFloat(v2);

        auto tmp=v3/v4;
        // 変換誤差は乗算する時に拡大されるため
        // 参考値は変換後の値の計算結果を採用
        float ans=v3.toDouble()/v4.toDouble();
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(ans-tmp.toDouble());
        if (abserr>(1./(1<<16)))
            cout<<"abserr="<<abserr<<endl;
    }

    cout<<"------------------"<<endl;

    // FP64で掛け算を行う
    // 参考値 実際値　を一行に出力
    for(int i=0;i<5;i++){
        float v1=operand1[i],v2=operand2[i];
        
        auto v3=FP64<16>::fromFloat(v1),v4=FP64<16>::fromFloat(v2);
        // 変換誤差は乗算する時に拡大されるため
        // 参考値は変換後の値の計算結果を採用
        float ans=v3.toDouble()*v4.toDouble();

        auto tmp=v3*v4;
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(ans-tmp.toDouble());
        if (abserr>(1./(1<<16)))
            cout<<"abserr="<<abserr<<endl;
    }

    // 結果が64ビットをオーバーする
    double overflow1[5]={10000.5,-2000.5,2000.56,1234.567,-5000.5};
    double overflow2[5]={10000.5,-2000.5,-1200,1234.567,3600.7};

    cout<<"------------------"<<endl;

    for(int i=0;i<5;i++){
        double v1=overflow1[i],v2=overflow2[i];
        // double ans=v1*v2;
        auto v3=FP64<8>::fromFloat(v1),v4=FP64<8>::fromFloat(v2);

        auto tmp=v3*v4;
        // 変換誤差は乗算する時に拡大されるため
        // 参考値は変換後の値の計算結果を採用
        double ans=v3.toDouble()*v4.toDouble();
        cout<<ans<<" "<<tmp<<endl;
        double abserr=abs(ans-tmp.toDouble());
        if (abserr>(1./(1<<8)))
            cout<<"abserr="<<abserr<<endl;
    }


    return 0;
}