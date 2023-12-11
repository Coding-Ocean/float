#include<iostream>
using namespace std;
class FLOAT
{
public:
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

	FLOAT(float f):f(f){
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
	void dispFloat()
	{
		printf("%f\n", f);
	}
	void dispBin()
	{
		//�Q�i���\��
		for (int i = 0; i < 32; i++) {
			printf("%u", bits[i]);
			if (i == 0 || i == 8)printf(" ");
		}
		printf("\n");
	}
	void dispDec()
	{
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
			pow(-1, s) * pow(2, e - 127) * (1 + m / pow(2, 23))
		);
	}
};

void toBin(float f)
{
	//�������̐�������-32768�`32767�ł��邱�ƁI
	if (int(f) < -32768 || int(f) > 32767) {
		printf("�͈͊O�̈���\n");
		return;
	}

	printf("%f\n",f);

	//����
	int sign = f < 0 ? 1 : 0;
	printf("%s\n", (sign ? "minus" : "plus"));

	//�z�񂃂ɁA�������Ə������𕪂��āA2�i��������������ׂĂ����܂��B
	const int n1 = 16;//�������̌���
	const int n2 = 64;//�������̌���
	char c[n1 + n2]{};
	//�������Q�i���z��
	f = fabsf(f);//��Βl������
	int Int = int(f);//�����������o��
	for (int i = n1-1; i >= 0; i--) {
		c[i] = Int % 2;
		Int /= 2;
	}
	//�������Q�i���z��
	f -= int(f);//�����_�ȉ������o��
	for (int i = n1; i < (n1 + n2); i++) {
		f *= 2;
		c[i] = int(f);
		if (int(f) == 1) {
			f -= 1.0f;
		}
	}

	//�������\��
	for (int i = 0; i < n1; i++) {
		printf("%d",c[i]);
	}
	//�������\��
	printf(".");
	for (int i = n1; i < (n1 + n2); i++) {
		printf("%d", c[i]);
	}
	printf("\n");

	//�����������邩���߂�
	int shift = 0;
	int disp = 0;
	for (int i = 0; i < n1 + n2; i++) {
		if (c[i] == 1) {
			shift = n1 - 1 - i;
			disp = i + 1;
			break;
		}
	}
	cout << shift << "����������\n";
	//�w�����̂Q�i�z��
	shift += 127;
	char e[8 + 1]{};
	for (int i = 7; i >= 0; i--) {
		e[i] = shift % 2;
		shift /= 2;
	}

	//float�r�b�g�\��
	printf("%d ", sign);
	for (int i = 0; i < 8; i++) {
		printf("%d", e[i]);
	}
	printf(" ");
	for (int i = disp; i < disp+23; i++) {
		printf("%d", c[i]);
	}
	printf("\n");
}

int main()
{
	FLOAT f { 0.125f };
	f.dispFloat();
	f.dispBin();
	//f.dispDec();

	cout << endl;
	toBin(f.f);

	system("pause>0");
}
