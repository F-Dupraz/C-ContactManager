#pragma once

#include <stdio.h>
#include <string.h>

typedef struct Contact
{
	char name[50];
	char phone_number[15];
	char address[50];
	char email[50];
	char birthday[15];
} Contact;

void SaveContact(Contact cont)
{
	FILE* file = fopen("contacts.txt", "wb");

	if (file != NULL)
	{
		fseek(file, 3L, SEEK_SET);
		fprintf_s(file, "%s, %s, %s, %s, %s\n", cont.name, cont.phone_number, cont.address, cont.email, cont.birthday);
		fclose(file);
	}
	else
		printf(" Error opening the file contacts.dat.\n You have to create a file with that name.");
}

// void ReadAllUsers()
