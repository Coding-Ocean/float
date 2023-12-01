#include<iostream>

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
};
void dispBin(struct FLOAT& f)
{
	printf("%u", f.b31);
	printf("%u", f.b30);
	printf("%u", f.b29);
	printf("%u", f.b28);
	printf("%u", f.b27);
	printf("%u", f.b26);
	printf("%u", f.b25);
	printf("%u ", f.b24);
	printf("%u", f.b23);
	printf("%u", f.b22);
	printf("%u", f.b21);
	printf("%u", f.b20);
	printf("%u", f.b19);
	printf("%u", f.b18);
	printf("%u", f.b17);
	printf("%u ", f.b16);
	printf("%u", f.b15);
	printf("%u", f.b14);
	printf("%u", f.b13);
	printf("%u", f.b12);
	printf("%u", f.b11);
	printf("%u", f.b10);
	printf("%u", f.b09);
	printf("%u ", f.b08);
	printf("%u", f.b07);
	printf("%u", f.b06);
	printf("%u", f.b05);
	printf("%u", f.b04);
	printf("%u", f.b03);
	printf("%u", f.b02);
	printf("%u", f.b01);
	printf("%u", f.b00);
}
int main()
{
	struct FLOAT fd { 7.25f };
	dispBin(fd);
	printf("\n");
	float f{ 7.25f };
	if ((unsigned)f & 0x1)printf("1"); else printf("0");
	if ((unsigned)f & 0x2)printf("1"); else printf("0");
	if ((unsigned)f & 0x4)printf("1"); else printf("0");
	if ((unsigned)f & 0x8)printf("1"); else printf("0");

	system("pause>0");
}
