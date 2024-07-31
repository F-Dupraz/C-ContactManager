#pragma once

#include <stdio.h>

int ShowDisplay()
{
	printf("\n 1. Show contacts.\n 2. Add a new contact.\n 3. Delete a contact.\n 4. Update a contact.\n 5. Show one contact.\n 6. Save and exit.\n");
	int choise_num;
	printf("\n\n Your choise is: ");
	int choise = scanf("%d", &choise_num);
	int gc = getchar();

	if (choise_num < 7 && choise_num > 0)
		return choise_num;
	else
		printf("Option not avaiable. \n");
		return ShowDisplay();
}
