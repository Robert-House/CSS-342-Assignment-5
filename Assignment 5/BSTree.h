#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"

struct Node
{
	Account *pAccount;
	Node *left;
	Node *right;
};

class BSTree
{
public:
	BSTree::BSTree();
	BSTree::~BSTree();

	bool Insert(Account*);
	bool Retrieve(const Account &, Account * &) const;

	void Display();
	void Empty();
	bool IsEmpty();

private:
	Node *root = NULL;
	Account * RecursiveSearch(Node *root, const Account &target) const;
	void BSTree::RecursiveInsert(Node *&root, Account *target);
};

#endif