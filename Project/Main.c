/* I'm learninng C and practicing data structures and algorithms */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Display.h"
#include "AVLNode.h"
#include "File.h"

int main()
{
	AVLNode* root = NULL;
	Contact new_contact;
	const char* filename = "contacts.txt";
	char complete_name[50], name[25], last_name[25], phone_number[15], address[50], email[50], birthday[15];
	
	LoadContacts(&root, filename);

	while (1)
	{
		int choise = ShowDisplay();

		switch (choise)
		{
		case 1:
			printf("\n Estos son todos tus contactos: \n");
			PreOrder(root);

			break;
		case 2:
			printf("\n Input the name and last name only: ");
			scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
			printf("\n Input the phone number: ");
			scanf_s("%s", phone_number, (unsigned int)sizeof(phone_number));
			printf("\n Input the address: ");
			scanf_s("%s", address, (unsigned int)sizeof(address));
			printf("\n Input the email: ");
			scanf_s("%s", email, (unsigned int)sizeof(email));
			printf("\n Input the birthday: ");
			scanf_s("%s", birthday, (unsigned int)sizeof(birthday));

			strcpy_s(complete_name, 50, name);
			strcat_s(complete_name, 50, " ");
			strcat_s(complete_name, 50, last_name);
			strcpy_s(new_contact.name, sizeof(new_contact.name), complete_name);
			strcpy_s(new_contact.phone_number, sizeof(new_contact.phone_number), phone_number);
			strcpy_s(new_contact.address, sizeof(new_contact.address), address);
			strcpy_s(new_contact.email, sizeof(new_contact.email), email);
			strcpy_s(new_contact.birthday, sizeof(new_contact.birthday), birthday);

			root = Insert(root, new_contact);

			break;
		case 3:
			printf(" 3\n");
			break;
		case 4:
			printf(" 4\n");
			break;
		case 5:
			printf(" Insert de name and last name: ");
			scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
			
			strcpy_s(complete_name, 50, name);
			strcat_s(complete_name, 50, " ");
			strcat_s(complete_name, 50, last_name);

			AVLNode* found = Search(root, complete_name);

			if (found != NULL)
				printf("  %s:\n  Phone number: %s.\n  Address: %s.\n  Email: %s.\n  Birthday: %s.\n\n", found->contact.name, found->contact.phone_number, found->contact.address, found->contact.email, found->contact.birthday);
			else
				printf("  Contacto no encontrado.\n");

			break;
		case 6:
			SaveContacts(root, filename);
			printf("\n Contactos guardados en el archivo: %s.\n", filename);
			exit(0);
		default:
			break;
		}
	}

	return 0;
}