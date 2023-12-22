/*
���������_�����������J�ɉ�����Ă���y�[�W
https://qiita.com/y-yoshinari/items/76260f6359d5b4418b33
���킹�Ē������摜
�݂񂿂肦�i https://min-chi.material.jp/ �j
*/
#include<iostream>
#include<format>
using namespace std;

void dispFloat(float f)
{
	cout << "[10�i����]\n";
	cout << fixed << f << endl << endl;
}
void dispBin(float f)
{
	cout << ("[�Q�i�����ɕϊ�]\n");

	//�G���[����
	if (isnan(f) || isinf(f)) { cout << f << endl << endl; return; }

	//�����\��
	cout << (f < 0 ? "-" : "");

	//���̏d�݂̊J�n�w��'e'�̌���
	float flt = fabsf(f);
	float e = 0;
	for (int i = 1; i <= 128; i++) {
		if (flt < pow(2, i)) {
			e = i - 1.0f;
			break;
		}
	}
	//���ʂɂQ�i���ɕϊ����Ȃ���1bit���\��
	while(e >= -48) {
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
		e--;
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
	//�G���[����
	if (isnan(f) || isinf(f) || f==0) { return; }

	cout << "[1.xxx�E�E�E�̌`�ɕό`]" << endl;
	//�r�b�g�̂Ȃ�т�unsigned u�ɕϊ�
	unsigned u = *reinterpret_cast<unsigned*>(&f);
	//���K�������l��\��
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
	//�G���[����
	if (isnan(f) || isinf(f) || f == 0) { return; }

	//�������炷��
	int e = exponent(f);
	//����
	cout << " " << "    ��         �@�@��" << endl;
	cout << " " << format("{:4}{:<7}", e, "+127");
	cout << "�����_��" << -e << "���炵����������" << endl;
}
