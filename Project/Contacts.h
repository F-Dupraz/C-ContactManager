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

void CreateContact(Contact cont)
{
	FILE* file = fopen("contacts.txt", "a+");

	long seek_offset = 0L;

	char cr[50];
	char cr_name[25];
	char cr_last_name[25];

	if (file != NULL)
	{
		fseek(file, seek_offset, SEEK_SET);
		fscanf_s(file, "%s %s", cr_name, (unsigned int)sizeof(cr_name), cr_last_name, (unsigned int)sizeof(cr_last_name));
		strcpy_s(cr, 50, cr_name);
		strcat_s(cr, 50, " ");
		strcat_s(cr, 50, cr_last_name);
		printf("\n %s", cr);
		fprintf_s(file, "%s, %s, %s, %s, %s\n", cont.name, cont.phone_number, cont.address, cont.email, cont.birthday);
		fclose(file);
	}
	else
		printf(" Error opening the file contacts.dat.\n You have to create a file with that name.");
}

// void ReadAllUsers()
