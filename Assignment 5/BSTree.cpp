#include "BSTree.h"

BSTree::BSTree() 
{
	root = new Node();
	root->pAccount = new Account(1500, "dummy", "account");
	//this->root = new Node();
}
BSTree::~BSTree() {}

bool BSTree::Insert(Account *account)
{
	RecursiveInsert(root, account);
	return true;
}

bool BSTree::Retrieve(const Account &target, Account *&source) const
{
	Account *temp = RecursiveSearch(root, target);

	if (temp == NULL)
	{
		return false;
	}
	else
	{
		source = temp;
		return true;
	}
}

void BSTree::Display()
{

}

void BSTree::Empty()
{
	root = NULL;
}

bool BSTree::IsEmpty()
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Account * BSTree::RecursiveSearch(Node *node, const Account &target) const
{
	if (node == NULL) return NULL;

	else if (target == *(node->pAccount))
	{
		return (node->pAccount);
	}
	else if (target < *(node->pAccount))
	{
		return RecursiveSearch(node->left, target);
	}
	else
	{
		return RecursiveSearch(node->right, target);
	}
}

void BSTree::RecursiveInsert(Node *&node, Account *target)
{
	if (!node)
	{
		node = new Node();
		node->pAccount = target;
		return;
	}
	else if (*target < *node->pAccount)
	{
		RecursiveInsert(node->left, target);
	}
	else
	{
		RecursiveInsert(node->right, target);
	}
}