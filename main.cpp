#include<iostream>
using namespace std;
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
	FLOAT(float f):f(f){}
	void dispFloat()
	{
		printf("%f\n", f);
	}
	void dispBin()
	{
		//�Q�i���\��
		unsigned char bits[] = { b31,b30,
			b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,
			b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,
			b09,b08,b07,b06,b05,b04,b03,b02,b01,b00,
		};
		printf("�Q�i�ɕϊ�\n");
		for (int i = 0; i < 32; i++) {
			printf("%u", bits[i]);
			if (i == 0 || i == 8)printf(" ");
		}
		printf("\n");
	}
	void dispDec()
	{
		//�Q�i���\��
		unsigned char bits[] = { b31,b30,
			b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,
			b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,
			b09,b08,b07,b06,b05,b04,b03,b02,b01,b00,
		};
		printf("10�i�ɕϊ�\n");
		//����
		int s = bits[0];
		//�w�����˂P�O�i��
		int e = 0;
		for (int i = 1; i <= 8; i++) {
			e += bits[i] * (int)pow(2, 8 - i);
		}
		//�������˂P�O�i��
		int m = 0;
		for (int i = 9; i < 32; i++) {
			m += bits[i] * (int)pow(2, 31 - i);
		}
		printf("%d %d-127=%d %d/%.0f+1=%f\n", s, e, e - 127, m, pow(2, 23), 1 + m / pow(2, 23));
		printf("%1.f * %f * %f = %f\n",
			pow(-1, s), //����
			pow(2, e - 127), //�w����
			1 + m / pow(2, 23), //������
			pow(-1, s) * pow(2, e - 127) * (1 + m / pow(2, 23)));

	}
};
void toBin(float f)
{
	printf("%f\n",f);

	int sign = f < 0 ? 1 : 0;
	cout << (sign ? "minus" : "plus") << endl;

	//�������Q�i��������
	f = fabsf(f);
	int Int = int(f);
	f -= Int;//�����_�ȉ������o���B��Ŏg��
	char c1[16 + 32 + 1]{};
	for (int i = 15; i >= 0; i--) {
		c1[i] = Int % 2 + '0';
		Int /= 2;
	}
	//�������Q�i��������
	for (int i = 16; i < 16 + 31; i++) {
		f *= 2;
		c1[i] = int(f) + '0';
		if (int(f) == 1)f -= 1.0f;
	}
	//���r�b�g�V�t�g���邩���߂�
	bool flag = true;
	int e = 0;
	int disp = 0;
	for (int i = 0; i < 16 + 32; i++) {
		if (flag && c1[i] == '1') { e = 15 - i; disp = i + 1; flag = false; }
	}
	cout << e << "�r�b�g�V�t�g����\n";
	//�������\��
	for (int i = 0; i < 16; i++) {
		cout << c1[i];
	}
	//�������\��
	cout << '.';
	for (int i = 16; i < 16 + 32; i++) {
		cout << c1[i];
	}
	cout << endl;

	e += 127;
	char e_[8 + 1]{};
	for (int i = 7; i >= 0; i--) {
		e_[i] = e % 2 + '0';
		e /= 2;
	}

	//float�r�b�g�\��
	cout << sign << ' ';
	cout << e_ << ' ';
	for (int i = disp; i < 23 + disp; i++) {
		cout << c1[i];
	}
	cout << endl;
}
int main()
{
	struct FLOAT f { .2f };
	f.dispFloat();
	f.dispBin();

	cout << endl;
	toBin(f.f);

	system("pause>0");
}
