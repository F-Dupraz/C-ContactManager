#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct Contact
{
	char name[50];
	char phone_number[15];
	char address[50];
	char email[50];
	char birthday[15];
} Contact;

typedef struct AVLNode
{
	Contact contact;
	struct AVLNode* left;
	struct AVLNode* right;
	int height;
} AVLNode;

int height(AVLNode* node)
{
	if (node == NULL)
		return 0;
	return node->height;
}

int max_h(int a, int b)
{
	return (a > b) ? a : b;
}

AVLNode* RightRotate(AVLNode* y)
{
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max_h(height(y->left), height(y->right)) + 1;
	x->height = max_h(height(x->left), height(x->right)) + 1;

	return x;
}

AVLNode* LeftRotate(AVLNode* x)
{
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max_h(height(x->left), height(x->right)) + 1;
	y->height = max_h(height(y->left), height(y->right)) + 1;

	return y;
}

int GetBalance(AVLNode* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

AVLNode* CreateNode(Contact contact)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->contact = contact;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

AVLNode* MinValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

AVLNode* Insert(AVLNode* node, Contact contact)
{
    if (node == NULL)
        return CreateNode(contact);

    if (strcmp(contact.name, node->contact.name) < 0)
        node->left = Insert(node->left, contact);
    else if (strcmp(contact.name, node->contact.name) > 0)
        node->right = Insert(node->right, contact);
    else
        return node;

    node->height = 1 + max_h(height(node->left), height(node->right));

    int balance = GetBalance(node);

    if (balance > 1 && strcmp(contact.name, node->left->contact.name) < 0)
        return RightRotate(node);

    if (balance < -1 && strcmp(contact.name, node->right->contact.name) > 0)
        return LeftRotate(node);

    if (balance > 1 && strcmp(contact.name, node->left->contact.name) > 0)
	{
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    if (balance < -1 && strcmp(contact.name, node->right->contact.name) < 0)
	{
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}

AVLNode* Search(AVLNode* root, char* name)
{
    if (root == NULL || strcmp(root->contact.name, name) == 0)
        return root;

    if (strcmp(name, root->contact.name) < 0)
        return Search(root->left, name);

    return Search(root->right, name);
}

AVLNode* Delete(AVLNode* root, char* name)
{
    if (root == NULL)
        return root;

    if (strcmp(name, root->contact.name) < 0)
        root->left = Delete(root->left, name);
    else if (strcmp(name, root->contact.name) > 0)
        root->right = Delete(root->right, name);
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            AVLNode* temp = MinValueNode(root->right);
            root->contact = temp->contact;
            root->right = Delete(root->right, temp->contact.name);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max_h(height(root->left), height(root->right));

    int balance = GetBalance(root);

    if (balance > 1 && GetBalance(root->left) >= 0)
        return RightRotate(root);

    if (balance > 1 && GetBalance(root->left) < 0)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    if (balance < -1 && GetBalance(root->right) <= 0)
        return LeftRotate(root);

    if (balance < -1 && GetBalance(root->right) > 0)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}
