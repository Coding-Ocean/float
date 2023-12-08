#include<iostream>
#include<format>
struct FLOAT
{
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
	void dispFloat()
	{
		printf("%f\n", f);
	}
	void dispBin()
	{
		unsigned char bits[] = { b31,b30,
			b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,
			b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,
			b09,b08,b07,b06,b05,b04,b03,b02,b01,b00,
		};
		for (int i = 0; i < 32; i++) {
			printf("%u", bits[i]);
			if (i == 0 || i == 8)printf(" ");
		}
		printf("\n");
		int s = bits[0];
		int e = 0;
		for (int i = 1; i <= 8; i++) {
			e += bits[i] * (int)pow(2, 8 - i);
		}
		int m = 0;
		for (int i = 9; i < 32; i++) {
			m += bits[i] * (int)pow(2, 31 - i);
		}
		printf("%d %d-127=%d %d/%.0f+1=%f\n", s, e, e - 127, m, pow(2, 23), 1 + m / pow(2, 23));
		printf("%1.f * %f * %f = %f\n", pow(-1, s), pow(2, e - 127), 1 + m / pow(2, 23), pow(-1, s) * pow(2, e - 127) * (1 + m / pow(2, 23)));
	}
};
void dispBin(struct FLOAT& f)
{
	unsigned char bits[] = { f.b31,f.b30,
		f.b29,f.b28,f.b27,f.b26,f.b25,f.b24,f.b23,f.b22,f.b21,f.b20,
		f.b19,f.b18,f.b17,f.b16,f.b15,f.b14,f.b13,f.b12,f.b11,f.b10,
		f.b09,f.b08,f.b07,f.b06,f.b05,f.b04,f.b03,f.b02,f.b01,f.b00,
	};
	for (int i = 0; i < 32; i++) {
		printf("%u", bits[i]);
		if (i == 0 || i == 8)printf(" ");
	}
	printf("\n");

	//printf("%u ", f.b31);
	//printf("%u", f.b30);
	//printf("%u", f.b29);
	//printf("%u", f.b28);
	//printf("%u", f.b27);
	//printf("%u", f.b26);
	//printf("%u", f.b25);
	//printf("%u", f.b24);
	//printf("%u ", f.b23);
	//printf("%u", f.b22);
	//printf("%u", f.b21);
	//printf("%u", f.b20);
	//printf("%u", f.b19);
	//printf("%u", f.b18);
	//printf("%u", f.b17);
	//printf("%u", f.b16);
	//printf("%u", f.b15);
	//printf("%u", f.b14);
	//printf("%u", f.b13);
	//printf("%u", f.b12);
	//printf("%u", f.b11);
	//printf("%u", f.b10);
	//printf("%u", f.b09);
	//printf("%u", f.b08);
	//printf("%u", f.b07);
	//printf("%u", f.b06);
	//printf("%u", f.b05);
	//printf("%u", f.b04);
	//printf("%u", f.b03);
	//printf("%u", f.b02);
	//printf("%u", f.b01);
	//printf("%u", f.b00);
	//printf("\n");
	int s = bits[0];
	int e = 0;
	for (int i = 1; i <= 8; i++) {
		e += bits[i] * (int)pow(2, 8 - i);
	}
	int m = 0;
	for (int i = 9; i < 32; i++) {
		m += bits[i] * (int)pow(2, 31 - i);
	}
	//int e = f.b30 * 128 + f.b29 * 64 + f.b28 * 32 + f.b27 * 16 + f.b26 * 8 + f.b25 * 4 + f.b24 * 2 + f.b23 * 1;
	//int m =	
	//	f.b22 * pow(2, 22) +
	//	f.b21 * pow(2, 21) +
	//	f.b20 * pow(2, 20) +
	//	f.b19 * pow(2, 19) +
	//	f.b18 * pow(2, 18) +
	//	f.b17 * pow(2, 17) +
	//	f.b16 * pow(2, 16) +
	//	f.b15 * pow(2, 15) +
	//	f.b14 * pow(2, 14) +
	//	f.b13 * pow(2, 13) +
	//	f.b12 * pow(2, 12) +
	//	f.b11 * pow(2, 11) +
	//	f.b10 * pow(2, 10) +
	//	f.b09 * pow(2, 9) +
	//	f.b08 * pow(2, 8) +
	//	f.b07 * pow(2, 7) +
	//	f.b06 * pow(2, 6) +
	//	f.b05 * pow(2, 5) +
	//	f.b04 * pow(2, 4) +
	//	f.b03 * pow(2, 3) +
	//	f.b02 * pow(2, 2) +
	//	f.b01 * pow(2, 1) +
	//	f.b00 * pow(2, 0);

	printf("%d %d-127=%d %d/%.0f+1=%f\n", s, e, e - 127, m, pow(2, 23), 1 + m / pow(2, 23));
	printf("%1.f * %f * %f = %f\n", pow(-1,s), pow(2, e - 127), 1 + m / pow(2, 23), pow(-1,s)* pow(2, e - 127)* (1 + m / pow(2, 23)));
}
int main()
{
	struct FLOAT f { 9.875f };
	
	f.dispFloat();
	f.dispBin();


	//using std::cout;
	//cout << fd << '\n';
	//cout << std::format("{:24b}", (unsigned)pow(2, 22)) << '\n';
	//cout << std::format("{:24b}", (unsigned)pow(2, 23)) << '\n';
	//cout << std::format("{:f}",pow(2, 20) / pow(2, 23)) << '\n';

	//printf("\n");

	//for (float f = 0; f < 1.1f; f += 0.1f) {
	//	std::cout << std::format("{:.1f}\n",f);
	//}

	system("pause>0");
}
