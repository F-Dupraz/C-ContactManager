#pragma once

#include <stdio.h>
#include <string.h>

#include "Contacts.h"

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

int max(int a, int b)
{
	return (a > b) ? a : b;
}

AVLNode* RightRotate(AVLNode* y)
{
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

AVLNode* LeftRotate(AVLNode* x)
{
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

AVLNode* RightRotate(AVLNode* y)
{
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	y->height = max(height(x->left), height(x->right)) + 1;

	return x;
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
