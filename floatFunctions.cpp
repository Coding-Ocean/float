/*
���������_�����������J�ɉ�����Ă���
https://qiita.com/y-yoshinari/items/76260f6359d5b4418b33
*/
#include<iostream>
#include<format>
using namespace std;

void dispFloat(float f)
{
	cout << "[10�i����]\n";
	cout << f << endl << endl;
}
void dispBin(float f)
{
	cout << ("[�Q�i�����ɕϊ�]\n");

	//�G���[����
	if (isnan(f) || isinf(f)) { cout << f << endl << endl; return; }

	//�����\��
	cout << (f < 0 ? "-" : "");

	//���̏d�݂̊J�n�w���̌���
	float flt = fabsf(f);
	float startE = 0;
	if (flt < pow(2, 1))startE = 0;
	else if (flt < pow(2, 2))startE = 1;
	else if (flt < pow(2, 4))startE = 3;
	else if (flt < pow(2, 8))startE = 7;
	else if (flt < pow(2, 16))startE = 15;
	else if (flt < pow(2, 24))startE = 23;
	else if (flt < pow(2, 32))startE = 31;
	//���ʂɂQ�i���ɕϊ����Ȃ���1bit���\��
	for (float e = startE; e >= -48; e--) {
		float weight = powf(2, e);//���̏d��
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
	//�r�b�g�̂Ȃ�т�unsigned u�ɕϊ�
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//31�ԃr�b�g(������)���O�ɂ���
	u &= ~(1 << 31);
	//�w��������
	u >>= 23;
	//�������炷��
	return (int)u - 127;
}
void dispNormalized(float f)
{
	cout << "[1.xxx�E�E�E�̌`�ɕό`]" << endl;
	//�r�b�g�̂Ȃ�т�unsigned u�ɕϊ�
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//���K�������l��\��
	cout << "1.";
	cout << format("{:023b}", u & 0x007fffff);//������
	cout << format(" * 2^{:}", exponent(f));
	cout << endl << endl;
}
void dispBinIEEE754(float f)
{
	cout << "[IEEE754_���������_]\n";
	//�r�b�g�̂Ȃ�т�unsigned u�ɕϊ�
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//�������E�w�����E�������A��؂��ĕ\��
	for (int n = 31; n >= 0; n--) {
		//�ŏ�ʃr�b�g����P�r�b�g���\��
		cout << (u >> n & 1);
		//�X�y�[�X�ŋ�؂�
		if (n == 31 || n == 23)cout << ' ';
	}
	cout << endl;
}
void explanation(float f)
{
	//�������炷��
	int e = exponent(f);
	//����
	cout << " " << "    ��         �@�@��" << endl;
	cout << " " << format("{:4}{:<7}", e, "+127");
	cout << "�����_��" << e << "���炵����������";
}
