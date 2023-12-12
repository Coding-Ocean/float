/*
浮動小数点をすごく丁寧に解説している
https://qiita.com/y-yoshinari/items/76260f6359d5b4418b33
*/
#include<iostream>
#include<format>
using namespace std;
class FLOAT
{
public:
	//Data
	union
	{
		float f;
		struct {
			unsigned char b00 : 1;
			unsigned char b01 : 1;
			unsigned char b02 : 1;
			unsigned char b03 : 1;
			unsigned char b04 : 1;
			unsigned char b05 : 1;
			unsigned char b06 : 1;
			unsigned char b07 : 1;
			unsigned char b08 : 1;
			unsigned char b09 : 1;
			unsigned char b10 : 1;
			unsigned char b11 : 1;
			unsigned char b12 : 1;
			unsigned char b13 : 1;
			unsigned char b14 : 1;
			unsigned char b15 : 1;
			unsigned char b16 : 1;
			unsigned char b17 : 1;
			unsigned char b18 : 1;
			unsigned char b19 : 1;
			unsigned char b20 : 1;
			unsigned char b21 : 1;
			unsigned char b22 : 1;
			unsigned char b23 : 1;
			unsigned char b24 : 1;
			unsigned char b25 : 1;
			unsigned char b26 : 1;
			unsigned char b27 : 1;
			unsigned char b28 : 1;
			unsigned char b29 : 1;
			unsigned char b30 : 1;
			unsigned char b31 : 1;
		};
	};
	unsigned char bits[32];
	
	//Functions
	FLOAT(float f):f(f)
	{
		bits[0] = b31;
		bits[1] = b30;
		bits[2] = b29;
		bits[3] = b28;
		bits[4] = b27;
		bits[5] = b26;
		bits[6] = b25;
		bits[7] = b24;
		bits[8] = b23;
		bits[9] = b22;
		bits[10] = b21;
		bits[11] = b20;
		bits[12] = b19;
		bits[13] = b18;
		bits[14] = b17;
		bits[15] = b16;
		bits[16] = b15;
		bits[17] = b14;
		bits[18] = b13;
		bits[19] = b12;
		bits[20] = b11;
		bits[21] = b10;
		bits[22] = b09;
		bits[23] = b08;
		bits[24] = b07;
		bits[25] = b06;
		bits[26] = b05;
		bits[27] = b04;
		bits[28] = b03;
		bits[29] = b02;
		bits[30] = b01;
		bits[31] = b00;
	}
	void dispFloat() const
	{
		cout << ("１０進小数\n");
		cout << fixed << f << endl;
	}
	void dispBin() const
	{
		//２進数表示
		cout << "メモリ上のデータをそのまま表示\n";
		for (int i = 0; i < 32; i++) {
			cout << (unsigned)bits[i];
			//符号部、指数部、仮数部の区切りスペース
			if (i == 0 || i == 8)cout << ' ';
		}
		cout << endl;
	}
	void toBin() const
	{
		//整数の開始指数
		int startN = 0;
		if (f < pow(2, 4))startN = 3;
		else if (f < pow(2, 8))startN = 7;
		else if (f < pow(2, 16))startN = 15;
		else if (f < pow(2, 24))startN = 23;
		else startN = 31;

		//普通に２進数に変換して表示
		cout << ("２進小数(絶対値)\n");
		float flt = fabsf(f);
		for (float n = startN; n >= -48; n--) {
			float pw = powf(2, n);
			int bit = int(flt / pw);
			flt = flt - bit * pw;
			std::cout << bit;
			if (n == 0) {
				std::cout << '.';
			}
		}
		cout << endl << endl;

		//IEEE754規格の単精度浮動小数点
		flt = fabsf(f);
		bool first = false;
		int expornent = 0;
		char mantissa[23 + 1]{ "00000000000000000000000" };
		int i = 0;//mantissa配列のインデックス
		//符号部
		int sign = f < 0 ? 1 : 0;
		//仮数部
		for (float n = startN; n >= -48; n--) {
			float pw = powf(2, n);
			int bit = int(flt / pw);
			//余りを求めておく
			flt = flt - bit * pw;
			//はじめてbitが１になった
			if (!first && bit == 1) {
				first = true;
				//指数部：小数点をずらす桁数
				expornent = int(n);
			}
			//１が出てきた次のループからmantissa配列に'1'or'0'を並べていく
			else if (first) {
				mantissa[i] = bit + '0';
				i++;
				if (i == 23) {
					break;
				}
			}
		}

		std::cout << "IEEE754規格の単精度浮動小数点\n";
		std::cout << "符号部：" << sign << " (" << (sign ? "マイナス" : "プラス") << "を表す)\n";
		std::cout << "指数部：" << expornent << "+127=" << expornent + 127;
		std::cout << " (最左の1の次まで小数点を" << expornent << "桁移動する。127を足すと指数部。)\n";
		std::cout << "仮数部：移動した小数点より右側の23ビット\n";

		//符号部
		std::cout << sign << ' ';
		//指数部：ずらす桁数に127を足した値
		std::cout << format("{:08b} ", f == 0.0f ? 0 : expornent + 127);
		//仮数部
		std::cout << mantissa << endl << endl;
	}

	void toDec() const
	{
		printf("\n10進に戻してみる\n");
		//符号
		int s = bits[0];
		//指数部⇒１０進数
		int e = 0;
		for (int i = 1; i <= 8; i++) {
			e += bits[i] * (int)pow(2, 8 - i);
		}
		//仮数部⇒１０進数
		int m = 0;
		for (int i = 9; i < 32; i++) {
			m += bits[i] * (int)pow(2, 31 - i);
		}
		printf("%d %d-127=%d %d/%.0f+1=%f\n", s, e, e - 127, m, pow(2, 23), 1 + m / pow(2, 23));
		printf("%1.f * %f * %f = %f\n",
			pow(-1, s), //符号
			pow(2, e - 127), //指数部
			1 + m / pow(2, 23), //仮数部
			pow(-1, s) * pow(2, e - 127) * (1 + m / pow(2, 23))
		);

		//cout << pow(-1, s) << " * ";//符号
		//cout << fixed << pow(2, e - 127) << " * "; //指数部
		//cout << fixed << 1 + m / pow(2, 23) << " = "; //仮数部
		//cout << fixed << pow(-1, s) * pow(2, e - 127) * (1 + m / pow(2, 23));
	}
};

int main()
{
	FLOAT f = -0.425f;
	f.dispFloat();
	f.toBin();
	f.dispBin();
	f.toDec();

	system("pause>0");
}
