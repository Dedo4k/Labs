#pragma once
#include <iostream>
#include "Monoblock.h"
#include "MPhone.h"
#include "Notebook.h"
#include "Server.h"
#include "Computer.h"
#include "MyExc_Vvod.h"
#include "Portable.h"
#include "Server.h"
using namespace std;

template<class TYPE> struct Node
{
	int key;
	TYPE data;
	struct Node* left;
	struct Node* right;
	struct Node* parrent;
};

template<class TYPE> class Binary_tree
{
private:
	Node<TYPE>* root;
public:
	Binary_tree();
	Node<TYPE>* getRoot();
	Node<TYPE>* Create_node(int key, TYPE data);
	Node<TYPE>* FindKey(Node<TYPE>* root, int key);
	Node<TYPE>* FindParent(Node<TYPE>* root, int key);
	int CheckKey(Node<TYPE>* root, int key);
	void add(TYPE data);
	void print(Node<TYPE>* root);
	void printKey(Node<TYPE>* root, int level);
	void findByKey(Node<TYPE>* root);
	void deleteByKey(Node<TYPE>* root);
};