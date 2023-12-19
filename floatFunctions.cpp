/*
浮動小数点をすごく丁寧に解説している
https://qiita.com/y-yoshinari/items/76260f6359d5b4418b33
*/
#include<iostream>
#include<format>
using namespace std;

void dispFloat(float f)
{
	cout << "[10進小数]\n";
	cout << f << endl << endl;
}
void dispBin(float f)
{
	cout << ("[２進小数に変換]\n");

	//エラー処理
	if (isnan(f) || isinf(f)) { cout << f << endl << endl; return; }

	//符号表示
	cout << (f < 0 ? "-" : "");

	//桁の重みの開始指数の決定
	float flt = fabsf(f);
	float startE = 0;
	if (flt < pow(2, 1))startE = 0;
	else if (flt < pow(2, 2))startE = 1;
	else if (flt < pow(2, 4))startE = 3;
	else if (flt < pow(2, 8))startE = 7;
	else if (flt < pow(2, 16))startE = 15;
	else if (flt < pow(2, 24))startE = 23;
	else if (flt < pow(2, 32))startE = 31;
	//普通に２進数に変換しながら1bitずつ表示
	for (float e = startE; e >= -48; e--) {
		float weight = powf(2, e);//桁の重み
		int bit = int(flt / weight);
		cout << bit;
		flt = fmod(flt, weight);
		if (e == 0) {
			cout << '.';
		}
		if (e < 0 && flt == 0) {
			break;
		}
	}
	cout << endl << endl;
}
int exponent(float f)
{
	//ビットのならびをunsigned uに変換
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//31番ビット(符号部)を０にする
	u &= ~(1 << 31);
	//指数部だけ
	u >>= 23;
	//何桁ずらすか
	return (int)u - 127;
}
void dispNormalized(float f)
{
	cout << "[1.xxx・・・の形に変形]" << endl;
	//ビットのならびをunsigned uに変換
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//正規化した値を表示
	cout << "1.";
	cout << format("{:023b}", u & 0x007fffff);//仮数部
	cout << format(" * 2^{:}", exponent(f));
	cout << endl << endl;
}
void dispBinIEEE754(float f)
{
	cout << "[IEEE754_浮動小数点]\n";
	//ビットのならびをunsigned uに変換
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//符号部・指数部・仮数部、区切って表示
	for (int n = 31; n >= 0; n--) {
		//最上位ビットから１ビットずつ表示
		cout << (u >> n & 1);
		//スペースで区切る
		if (n == 31 || n == 23)cout << ' ';
	}
	cout << endl;
}
void explanation(float f)
{
	//何桁ずらすか
	int e = exponent(f);
	//説明
	cout << " " << "    ↑         　　↑" << endl;
	cout << " " << format("{:4}{:<7}", e, "+127");
	cout << "小数点を" << e << "ずらした小数部分";
}
