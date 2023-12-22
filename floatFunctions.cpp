/*
浮動小数点をすごく丁寧に解説しているページ
https://qiita.com/y-yoshinari/items/76260f6359d5b4418b33
つかわせて頂いた画像
みんちりえ（ https://min-chi.material.jp/ ）
*/
#include<iostream>
#include<format>
using namespace std;

void dispFloat(float f)
{
	cout << "[10進小数]\n";
	cout << fixed << f << endl << endl;
}
void dispBin(float f)
{
	cout << ("[２進小数に変換]\n");

	//エラー処理
	if (isnan(f) || isinf(f)) { cout << f << endl << endl; return; }

	//符号表示
	cout << (f < 0 ? "-" : "");

	//桁の重みの開始指数'e'の決定
	float flt = fabsf(f);
	float e = 0;
	for (int i = 1; i <= 128; i++) {
		if (flt < pow(2, i)) {
			e = i - 1.0f;
			break;
		}
	}
	//普通に２進数に変換しながら1bitずつ表示
	while(e >= -48) {
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
		e--;
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
	//エラー処理
	if (isnan(f) || isinf(f) || f==0) { return; }

	cout << "[1.xxx・・・の形に変形]" << endl;
	//ビットのならびをunsigned uに変換
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//正規化した値を表示
	cout << "1.";
	u &= 0x007fffff;
	string b = format("{:023b}", u);
	for (int i = 22; i >= 1; i--) {
		if (b[i] == '0')
			b[i] = '\0';
		else
			break;
	}
	cout << b;
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
	//エラー処理
	if (isnan(f) || isinf(f) || f == 0) { return; }

	//何桁ずらすか
	int e = exponent(f);
	//説明
	cout << " " << "    ↑         　　↑" << endl;
	cout << " " << format("{:4}{:<7}", e, "+127");
	cout << "小数点を" << -e << "ずらした小数部分" << endl;
}
