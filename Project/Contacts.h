#pragma once

#include <stdio.h>

typedef struct Contact
{
	char name[50];
	char phone_number[15];
	char address[50];
	char email[50];
	char birthday[10];
} Contact;

void CreateContact(Contact cont)
{
	FILE* file = fopen("contacts.dat", "ab");
	if (file != NULL)
	{
		printf("%s", cont.name);
		fwrite(&cont, sizeof(Contact), 1, file);
		fclose(file);
	}
	else
		printf(" Error opening the file contacts.dat.\n You have to create a file with that name.");
}

// void ReadAllUsers()
