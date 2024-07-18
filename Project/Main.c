/* I'm learninng C and practicing data structures and algorithms */
#include <stdio.h>

int main()
{
	printf(" 1. Show contacts.\n 2. Add a new contact.\n 3. Delete a contact.\n 4. Update a contact.\n 5. Show one contact.\n");
	int choise_num;
	int choise = scanf("%d", &choise_num);

	switch (choise_num)
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
			printf("Sos boludo?\n");
			break;
	}

	return 0;
}