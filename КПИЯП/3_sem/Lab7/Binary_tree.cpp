#include "Binary_tree.h"

template<class TYPE> Binary_tree<TYPE>::Binary_tree()
{
	this->root = nullptr;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::getRoot()
{
	return root;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::Create_node(int key, TYPE data)
{
	Node<TYPE>* new_node = new Node<TYPE>;
	new_node->key = key;
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->parrent = nullptr;
	return new_node;
}

template<class TYPE> int Binary_tree<TYPE>::CheckKey(Node<TYPE>* root, int key)
{
	if (root->key == key)
		return 1;
	if (root->left)
		if (Binary_tree<TYPE>::CheckKey(root->left, key) == 1)
			return 1;
	if (root->right)
		if (Binary_tree<TYPE>::CheckKey(root->right, key) == 1)
			return 1;
	return 0;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::FindKey(Node<TYPE>* root, int key)
{
	if (!root)
	{
		system("CLS");
		cout << "Empty tree" << endl;
		return NULL;
	}
	if (root->key == key)
		return root;
	if (root->left)
		if (Binary_tree<TYPE>::FindKey(root->left, key))
			return Binary_tree<TYPE>::FindKey(root->left, key);
	if (root->right)
		if (Binary_tree<TYPE>::FindKey(root->right, key))
			return Binary_tree<TYPE>::FindKey(root->right, key);
	return NULL;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::FindParent(Node<TYPE>* root, int key)
{
	if (!root)
	{
		system("CLS");
		cout << "Empty tree" << endl;
		return NULL;
	}
	if (root->left && root->left->key == key || root->right && root->right->key == key)
		return root;
	if (root->left)
		if (Binary_tree<TYPE>::FindParent(root->left, key))
			return Binary_tree<TYPE>::FindParent(root->left, key);
	if (root->right)
		if (Binary_tree<TYPE>::FindParent(root->right, key))
			return Binary_tree<TYPE>::FindParent(root->right, key);
	return NULL;
}
 
template<class TYPE> void Binary_tree<TYPE>::add(TYPE t)
{
	cout << endl << "Enter parent key: ";
	int key = MyExc_Vvod::Check_int();
	if (!root)
	{
		root = Create_node(key, t);
		return;
	}
	else if (!CheckKey(root, key))
	{
		cout << endl << "This key doesn't exist" << endl;
		system("pause");
		return;
	}
	cout << endl << "Enter new key: ";
	int nkey = MyExc_Vvod::Check_int();
	if (CheckKey(root, nkey))
	{
		cout << endl << "This node already exists" << endl;
		system("pause");
		return;
	}
	cout << endl << "Enter [1] to add left child\n      [2] to add right child" << endl;
	int choose = MyExc_Vvod::Check_int();
	Node<TYPE>* new_node = Binary_tree<TYPE>::Create_node(nkey, t);
	Node<TYPE>* parent = Binary_tree<TYPE>::FindKey(root, key);
	if (parent == nullptr)
	{
		root = new_node;
		return;
	}
	switch (choose)
	{
	case 1:
		if (!parent->left)
		{
			new_node->parrent = parent;
			parent->left = new_node;
		}
		else
		{
			system("CLS");
			cout << "This node has left child" << endl;
			cout << endl;
			system("pause");
			break;
		}
		break;
	case 2:
		if (!parent->right)
		{
			new_node->parrent = parent;
			parent->right = new_node;
		}
		else
		{
			system("CLS");
			cout << "This node has right child" << endl;
			cout << endl;
			system("pause");
			break;
		}
		break;
	default:
		break;
	}
}

template<class TYPE> void Binary_tree<TYPE>::print(Node<TYPE>* root)
{
	if (!root)
		return;
	if (root->left)
	{
		cout << root->data;
		Binary_tree<TYPE>::print(root->left);
	}
	else
	{
		cout << root->data;
	}
	if (root->right)
	{
		Binary_tree<TYPE>::print(root->right);
	}
}

template<class TYPE> void Binary_tree<TYPE>::printKey(Node<TYPE>* root, int level)
{
	int i;
	if (root)
		printKey(root->right, level + 1);
	for (i = 0; i < level; i++)
		cout << "    ";
	if (root)
		cout << root->key << endl;
	else
		cout << "@" << endl;
	if (root)
		printKey(root->left, level + 1);
}

template<class TYPE> void Binary_tree<TYPE>::findByKey(Node<TYPE>* root)
{
	cout << "Enter key element: ";
	int key = MyExc_Vvod::Check_int();
	if (!FindKey(root, key))
	{
		system("CLS");
		cout << "This key doesn't exist" << endl;
		return;
	}
	Node<TYPE>* temp = FindKey(root, key);
	system("CLS");
	temp->data.shapka();
	cout << temp->data;
}

template<class TYPE> void Binary_tree<TYPE>::deleteByKey(Node<TYPE>* root)
{
	cout << "Enter key element: ";
	int key = MyExc_Vvod::Check_int();
	if (!FindKey(root, key))
	{
		system("CLS");
		cout << "This key doesn't exist" << endl;
		cout << endl;
		system("pause");
		return;
	}
	if (FindKey(root, key)->left && FindKey(root, key)->right)
	{
		system("CLS");
		cout << "You can't delete this element. It has 2 children." << endl;
		cout << endl;
		system("pause");
		return;
	}
	Node<TYPE>* parent = FindParent(root, key);
	Node<TYPE>* current = FindKey(root, key);
	if (!parent && current)
	{
		if (current->left||current->right)
		{
			system("CLS");
			cout << "You can't delete root element steel it has a children" << endl;
			cout << endl;
			system("pause");
			return;
		}
		else
		{
			this->root=NULL;
			return;
		}
	}
	if (current->left == nullptr && current->right == nullptr)
	{
		if (parent->left == current)
		{
			parent->left = nullptr;
			delete current;
			return;
		}
		else if (parent->right == current)
		{
			parent->right = nullptr;
			delete current;
			return;
		}
	}
	if (parent->left == current)
	{
		if (current->left)
		{
			current->left->parrent = parent;
			parent->left = current->left;
			delete current;
			return;
		}
		if (current->right)
		{
			current->right->parrent = parent;
			parent->left = current->right;
			delete current;
			return;
		}
	}
	else if (parent->right == current)
	{
		if (current->left)
		{
			current->left->parrent = parent;
			parent->right = current->left;
			delete current;
			return;
		}
		if (current->right)
		{
			current->right->parrent = parent;
			parent->right = current->right;
			delete current;
			return;
		}
	}
}
