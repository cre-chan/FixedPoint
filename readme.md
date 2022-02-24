# Fixed Point
## 概要
C++のテンプレートを使った固定小数点ライブラリである。小数部の長さはコンパイル時のみ存在する。コンパイラが小数部の長さを処理してくれるから手動で小数部の処理をする必要はない。

## 動作環境
c++17 以上をサポートするc++コンパイラ
e.g. clang-1200.0.32.29

## 導入の仕方
- ソースファイルの先頭に以下の文を追加する
    ```c++
    #include <FixedPoint.h>
    ```
- FixedPointのフォルダをコンパイラのincludePathに追加
    ```bash
    clang++ file -std=c++17 -lc++ -I path/to/FixedPoint/
    ```

## ドキュメント
## クラス
### **FP32\<bits\>**
32ビットを使って符号付きの固定小数点小数を表現する。bitsは小数部の長さを表す。bitsは31以下でないと行けない。bitsが31を超える場合コンパイルエラーを起こす。
#### **構造関数**
#### FP32\<bits\>(uint32 data)
固定小数点数の二進数表現を指定することで32ビット符号付き小数点を初期化する。fromFloatの使用を推奨する。
#### 使用例：
```c++
// 小数部を4ビットで表現する場合の0.5
// 0.5=0.1000 a=0.5
FP32<4> a(0x08);
```

#### **静的メソッド**
#### FP32\<bits\> fromFloat(float f)
浮動小数fをFP32\<bits\>に変換する。オーバーフローの可能性ある。オーバーフローの場合例外を投げない。オーバーフローがない場合、変換により生じる絶対誤差は$1/(2^{bits+1})$以下である。 

#### 使用例：
```c++
// a = 0.1000b
FP32<4> a=FP32<4>::fromFloat(0.5f);
// b = 0.1000b bの型を推測してもらう
auto b=FP32<4>::fromFloat(0.5f);
```
#### **メソッド**
#### FP32\<n\> to\<n\>()
今の固定小数点数が表している値を小数部がnビットの固定小数点数に変換する。オーバーフローの可能性ある。オーバーフローの場合例外を投げない。オーバーフローがない場合、変換により生じる絶対誤差は$1/(2^{n+1})$以下である。 

#### 使用例：
```c++
// a = 0.1000b
FP32<4> a=FP32<4>::fromFloat(0.5f);
// b = 0.10b 2ビットで0.5を表現
FP32<2> b=a.to<2>();
```

#### double toDouble()
固定小数点数の値を倍精度浮動小数点に変換する。変換する時精度落ちやオーバーフローは一切発生しない（doubleは53ビットを使って値を表現するため）。
#### 使用例：
```c++
// a = 0.1000b
FP32<4> a=FP32<4>::fromFloat(0.5f);
// b = 0.5
double b=a.toDouble();
```

#### **演算子**
#### operator +
固定小数点数同士の足し算および固定小数点数とint型の足し算。交換則を満たしている。固定小数点数同士の足し算の場合、引数の小数部は同じ長さでないと行けない。引数の小数部の長さが違う時にコンパイルエラーを起こす。

オーバーフローの可能性ある。例外を投げることはない。オーバーフローがない場合精度は落ちない。
#### 使用例：
```c++
int a = -5
// a = 0.1000b
auto b=FP32<4>::fromFloat(0.5f),
     c=FP32<4>::fromFloat(0.5f);

// int + FP32<4>
auto tmp1=a+b;
// FP32<4> + int
auto tmp2=b+a;
// 交換則を満たすこと
assert(tmp1==tmp2)

// FP32<4> + FP32<4>
auto tmp3=b+c;
// FP32<4> + FP32<4>
auto tmp4=c+b;
// 交換則を満たすこと
assert(tmp3==tmp4)

auto d=FP32<2>::fromFloat(0.5f);
// 出力 1.0
// 小数部の長さが同じになるようにtoを使って
// dを4ビットにする
cout<<b+d.to<4>()<<endl;
```
#### operator -
固定小数点数同士の引き算および固定小数点数とint型の引き算。固定小数点数同士の引き算の場合、引数の小数部は同じ長さでないと行けない。引数の小数部の長さが違う時にコンパイルエラーを起こす。

オーバーフローの可能性ある。例外を投げることはない。オーバーフローがない場合精度は落ちない。
#### 使用例：
```c++
int a = -5
// a = 0.1000b
auto b=FP32<4>::fromFloat(0.5f),
     c=FP32<4>::fromFloat(0.5f);

// int - FP32<4>
auto tmp1=a-b;
// FP32<4> - int
auto tmp2=b-a;
// 交換則を満たすこと
assert(tmp1==tmp2)

// FP32<4> - FP32<4>
auto tmp3=b-c;
// FP32<4> - FP32<4>
auto tmp4=c-b;
// 交換則を満たすこと
assert(tmp3==tmp4)

auto d=FP32<2>::fromFloat(0.5f);
// 出力 0.0
// 小数部の長さが同じになるようにtoを使って
// dを4ビットにする
cout<<b-d.to<4>()<<endl;
```
#### (単項) operator -
固定小数点数の反数を求める。

オーバーフローの可能性ある。例外を投げることはない。オーバーフローがない場合精度は落ちない。
#### 使用例：
```c++
auto b=FP32<4>::fromFloat(0.5f),
     c=FP32<4>::fromFloat(-0.5f);

// -b=-0.5
assert(-b==c);
```

#### operator *
固定小数点数同士の掛け算および固定小数点数とint型の掛け算。交換則を満たしている。固定小数点数同士の掛け算の場合、引数の小数部は同じ長さでないと行けない。引数の小数部の長さが違う時にコンパイルエラーを起こす。

オーバーフローの可能性ある。例外を投げることはない。オーバーフローがない場合誤差は$1/2^{bits+1}$以下である。
#### 使用例：
```c++
int a = -5
// a = 0.1000b
auto b=FP32<4>::fromFloat(0.5f),
     c=FP32<4>::fromFloat(0.5f);

// int * FP32<4>
auto tmp1=a*b;
// FP32<4> + int
auto tmp2=b*a;
// 交換則を満たすこと
assert(tmp1==tmp2)

// FP32<4> * FP32<4>
auto tmp3=b*c;
// FP32<4> * FP32<4>
auto tmp4=c*b;
// 交換則を満たすこと
assert(tmp3==tmp4)

auto d=FP32<2>::fromFloat(0.5f);
// 出力 0.25
// 小数部の長さが同じになるようにtoを使って
// dを4ビットにする
cout<<b*d.to<4>()<<endl;
```

#### operator /
固定小数点数同士の割り算および固定小数点数とint型の割り算。固定小数点数同士の割り算の場合、引数の小数部は同じ長さでないと行けない。引数の小数部の長さが違う時にコンパイルエラーを起こす。

オーバーフローの可能性ある。例外を投げることはない。オーバーフローがない場合誤差は$1/2^{bits+1}$以下である。
#### 使用例：
```c++
int a = -5
// a = 0.1000b
auto b=FP32<4>::fromFloat(0.5f),
     c=FP32<4>::fromFloat(0.5f);

// FP32<4> / int
auto tmp2=b/a;

// FP32<4> / FP32<4>
auto tmp3=b/c;
// FP32<4> / FP32<4>
auto tmp4=c/b;

auto d=FP32<2>::fromFloat(0.5f);
// 出力 1.0
// 小数部の長さが同じになるようにtoを使って
// dを4ビットにする
cout<<b/d.to<4>()<<endl;
```

#### operator <<
固定小数点数を出力する。toDouble()を使って浮動小数に変換しているため、通常方式で出力の有効桁数をコントロルできる。

#### operator ==
二つの固定小数点数が等しいかを判別する。現在では小数部の長さが同じのもの同士のみ比較できる。

#### operator <=
二つの固定小数点の大小比較を行う。引数の小数部の長さは必ず同じじゃなくてもいいです。ただし、小数部の長さが同じの場合は小数部の長さが違う場合より効率高いです。

比較の際精度落ちは起こらない。
#### 使用例：
```c++
auto a=FP32<4>::from(0.5),
     b=a=FP32<4>::from(0.7);

// 小数部長さが同じな比較
assert(a<=b);

auto c=FP32<2>::from(0.5)；
auto d=a=FP32<4>::from(0.5625);
// 小数部長さが違う比較
assert(c<=d);
```

#### operator >=
\>=と同じです。