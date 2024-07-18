/* I'm learninng C and practicing data structures and algorithms */

#include <stdio.h>

#include "Display.h"

int main()
{
	int choise = ShowDisplay();

	switch (choise)
	{
		case 1:
			printf(" 1\n");
			break;
		case 2:
			printf(" 2\n");
			break;
		case 3:
			printf(" 3\n");
			break;
		case 4:
			printf(" 4\n");
			break;
		case 5:
			printf(" 5\n");
			break;
		default:
			break;
	}

	return 0;
}