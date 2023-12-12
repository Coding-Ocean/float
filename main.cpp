/*
���������_�����������J�ɉ�����Ă���
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
		cout << ("�P�O�i����\n");
		cout << fixed << f << endl;
	}
	void dispBin() const
	{
		//�Q�i���\��
		cout << "��������̃f�[�^�����̂܂ܕ\��\n";
		for (int i = 0; i < 32; i++) {
			cout << (unsigned)bits[i];
			//�������A�w�����A�������̋�؂�X�y�[�X
			if (i == 0 || i == 8)cout << ' ';
		}
		cout << endl;
	}
	void toBin() const
	{
		//�����̊J�n�w��
		int startN = 0;
		if (f < pow(2, 4))startN = 3;
		else if (f < pow(2, 8))startN = 7;
		else if (f < pow(2, 16))startN = 15;
		else if (f < pow(2, 24))startN = 23;
		else startN = 31;

		//���ʂɂQ�i���ɕϊ����ĕ\��
		cout << ("�Q�i����(��Βl)\n");
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

		//IEEE754�K�i�̒P���x���������_
		flt = fabsf(f);
		bool first = false;
		int expornent = 0;
		char mantissa[23 + 1]{ "00000000000000000000000" };
		int i = 0;//mantissa�z��̃C���f�b�N�X
		//������
		int sign = f < 0 ? 1 : 0;
		//������
		for (float n = startN; n >= -48; n--) {
			float pw = powf(2, n);
			int bit = int(flt / pw);
			//�]������߂Ă���
			flt = flt - bit * pw;
			//�͂��߂�bit���P�ɂȂ���
			if (!first && bit == 1) {
				first = true;
				//�w�����F�����_�����炷����
				expornent = int(n);
			}
			//�P���o�Ă������̃��[�v����mantissa�z���'1'or'0'����ׂĂ���
			else if (first) {
				mantissa[i] = bit + '0';
				i++;
				if (i == 23) {
					break;
				}
			}
		}

		std::cout << "IEEE754�K�i�̒P���x���������_\n";
		std::cout << "�������F" << sign << " (" << (sign ? "�}�C�i�X" : "�v���X") << "��\��)\n";
		std::cout << "�w�����F" << expornent << "+127=" << expornent + 127;
		std::cout << " (�ō���1�̎��܂ŏ����_��" << expornent << "���ړ�����B127�𑫂��Ǝw�����B)\n";
		std::cout << "�������F�ړ����������_���E����23�r�b�g\n";

		//������
		std::cout << sign << ' ';
		//�w�����F���炷������127�𑫂����l
		std::cout << format("{:08b} ", f == 0.0f ? 0 : expornent + 127);
		//������
		std::cout << mantissa << endl << endl;
	}

	void toDec() const
	{
		printf("\n10�i�ɖ߂��Ă݂�\n");
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

		//cout << pow(-1, s) << " * ";//����
		//cout << fixed << pow(2, e - 127) << " * "; //�w����
		//cout << fixed << 1 + m / pow(2, 23) << " = "; //������
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
