#include "Binary_tree.h"
#include "Interface.h"

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
	if (!root)
		return 0;
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

template<class TYPE> void Binary_tree<TYPE>::add(TYPE data, int key)
{
	Node<TYPE>* new_node = Binary_tree<TYPE>::Create_node(key, data);
	Node<TYPE>* parent = root;
	if (!root)
		root = new_node;
	else 
	{
		Node<TYPE>* current = root;
		while (current) 
		{
			parent = current;
			if (new_node->key > current->key) current = current->right;
			else current = current->left;
		}
		if (new_node->key < parent->key)
		{
			new_node->parrent = parent;
			parent->left = new_node;
		}
		else
		{
			new_node->parrent = parent;
			parent->right = new_node;
		}
	}
}

template<class TYPE> void Binary_tree<TYPE>::print(Node<TYPE>* root)
{
	if (!root)
		return;
	if (root->left)
	{
		Binary_tree<TYPE>::print(root->left);
	}
	cout << root->data;
	if (root->right)
	{
		Binary_tree<TYPE>::print(root->right);
	}
}

template<class TYPE> int Binary_tree<TYPE>::numberNode(Node<TYPE>* root)
{
	if (root != NULL)
		return numberNode(root->right) + numberNode(root->left) + 1;
	return 0;
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
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите парковочное место:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	int key = MyExc_Vvod::Check_int(0,101);
	if (!FindKey(root, key))
	{
		system("CLS");
		Interface<TYPE>::draw_parking();
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tЭто место свобно." << endl;
		return;
	}
	Node<TYPE>* temp = FindKey(root, key);
	system("CLS");
	Interface<TYPE>::draw_parking();
	cout << "\t\t\t\t\t\t\t\t  _______________________________________________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t  |                          <<<ИНФОРМАЦИЯ О КЛИЕНТЕ>>>                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t  |_____________________________________________________________________________|" << endl;
	temp->data.shapka();
	cout << "\t\t\t\t\t\t\t\t  |____________|____________|____________|____________|____________|____________|" << endl;
	cout << temp->data;
	cout << "\t\t\t\t\t\t\t\t  |=============================================================================|" << endl;
}

template<class TYPE> void Binary_tree<TYPE>::findByKey(Node<TYPE>* root, int key)
{
	if (!FindKey(root, key))
	{
		system("CLS");
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tЭто место свободно." << endl;
		return;
	}
	Node<TYPE>* temp = FindKey(root, key);
	system("CLS");
	Interface<TYPE>::draw_parking();
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

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::deleteByKey(Node<TYPE>* root, int key)
{
		if (root == NULL) return root;
		else if (key < root->key)
		{
			Node<TYPE>* temp = deleteByKey(root->left, key);
			if (temp)
			{
				temp->parrent = root;
				root->left = temp;
			}
			else root->left = nullptr;
		}
		else if (key > root->key)
		{
			Node<TYPE>* temp = deleteByKey(root->right, key);
			if (temp)
			{
				temp->parrent = root;
				root->right = temp;
			}
			else root->right = nullptr;
		}
		else
		{
			//No child
			if (root->right == NULL && root->left == NULL)
			{
				if(root->parrent==nullptr)
					this->root = NULL;
				else
				{
					delete root;
					root = nullptr;
				}
				return root;
			}
			//One child 
			else if (root->right == NULL)
			{
				if (root->parrent == nullptr)
				{
					Node<TYPE>* temp = root;
					root->left->parrent = nullptr;
					this->root = root->left;
					delete temp;
					return root;
				}
				else
				{
					Node<TYPE>* temp = root;
					root = root->left;
					delete temp;
					return root;
				}
			}
			else if (root->left == NULL)
			{
				if (root->parrent == nullptr)
				{
					Node<TYPE>* temp = root;
					root->right->parrent = nullptr;
					this->root = root->right;
					delete temp;
				}
				else
				{
					Node<TYPE>* temp = root;
					root = root->right;
					delete temp;
				}
			}
			//Two child
			else
			{
				if (root->parrent == nullptr)
				{
					Node<TYPE>* temp = FindMax(root->left);
					this->root->key = temp->key;
					this->root->data = temp->data;
					root->left = deleteByKey(root->left, temp->key);
				}
				else
				{
					Node<TYPE>* temp = FindMax(root->left);
					root->key = temp->key;
					root->data = temp->data;
					root->left = deleteByKey(root->left, temp->key);
				}
			}
		}
		return root;
}

template<class TYPE> int Binary_tree<TYPE>::getPlace(Node<TYPE>* root, int key)
{
	int k = key;
	if (!root)
		return k;
	while (CheckKey(root, k))
	{
		k++;
	}
	return k;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::findMinNode(Node<TYPE>* root)
{
	if (root == NULL)
		return NULL;
	while (root->left != nullptr)
		root = root->left;
	return root;
}

template<class TYPE> Node<TYPE>* Binary_tree<TYPE>::FindMax(Node<TYPE>* root)
{
	if (root == NULL)
		return NULL;

	while (root->right != NULL)
	{
		root = root->right;
	}
	return root;
}

template<class TYPE> void Binary_tree<TYPE>::printIterUp()
{
	if (!root)
		return;
	Binary_tree<TYPE>::TreeIterator it;
	for (it = this->Begin(); it != this->End(); it++)
	{
		cout << *it;
	}
	cout << *it;
}

template<class TYPE> void Binary_tree<TYPE>::printIterDown()
{
	if (!root)
		return;
	Binary_tree<TYPE>::TreeIterator it;
	for (it = this->End(); it != this->Begin(); it--)
	{
		cout << *it;
	}
	cout << *it;
}