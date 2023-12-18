#include<process.h>
#include"floatFunctions.h"
int main()
{
	float f = pow(10, 1000000);

	dispFloat(f);

	dispBinIEEE754(f);

	system("pause>0");
}
