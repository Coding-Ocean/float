#include<iostream>
#include"floatFunctions.h"
int main()
{
	float f = 10000.0f + 0.016f;

	dispFloat(f);

	dispBin(f);

	dispNormalized(f);

	dispBinIEEE754(f);
	explanation(f);

	system("pause>0");
}
