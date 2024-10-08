#pragma once

#include <stdio.h>
#include <string.h>

#include "AVLNode.h"

void SaveToFile(AVLNode* root, FILE* file)
{
    if (root == NULL) return;
    fwrite(&(root->contact), sizeof(Contact), 1, file);
    SaveToFile(root->left, file);
    SaveToFile(root->right, file);
}

void SaveContacts(AVLNode* root, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }
    SaveToFile(root, file);
    fclose(file);
}

void LoadFromFile(AVLNode** root, FILE* file)
{
    Contact contact;
    while (fread(&contact, sizeof(Contact), 1, file))
    {
        *root = Insert(*root, contact);
    }
}

void LoadContacts(AVLNode** root, const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }
    LoadFromFile(root, file);
    fclose(file);
}
