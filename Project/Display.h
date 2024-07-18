#pragma once

#include <stdio.h>

int ShowDisplay()
{
	printf(" 1. Show contacts.\n 2. Add a new contact.\n 3. Delete a contact.\n 4. Update a contact.\n 5. Show one contact.\n");
	int choise_num;
	printf("\n\n Your choise is: ");
	int choise = scanf("%d", &choise_num);

	if (choise_num < 6)
		return choise_num;
	else
		ShowDisplay();
}
