#include <FixedPoint.h>
#include <iostream>

using namespace std;

int main(){


    auto a=FP32<4>::fromFloat(1.6);
    auto a_copy=a;
    assert(a==a_copy);

    auto b=FP64<4>::fromFloat(1.9);
    auto b_copy=b;
    assert(b==b_copy);


    return 0;
}