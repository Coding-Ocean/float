#include<process.h>
#include"floatFunctions.h"
int main()
{
	float f = 48.25f;

	dispFloat(f);

	dispBin(f);

	dispNormalized(f);

	dispBinIEEE754(f);
	explanation(f);

	system("pause>0");
}
