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
    Node<TYPE>* Create_node(TYPE data);
	Node<TYPE>* FindKey(Node<TYPE>* root, int key);
	Node<TYPE>* FindParent(Node<TYPE>* root, int key);
	int CheckKey(Node<TYPE>* root, int key);
	void add(TYPE data);
    void add(TYPE data, int key);
	void print(Node<TYPE>* root);
	void printKey(Node<TYPE>* root, int level);
	void findByKey(Node<TYPE>* root);
	void deleteByKey(Node<TYPE>* root);
    void printIterUp();
    void printIterDown();

    class TreeIterator
    {
    public:
        Node<TYPE>* mem;
        TreeIterator()
        {
            mem = NULL;
        }
        TreeIterator(Node<TYPE>* mem)
        {
            this->mem = mem;
        }
        void make(Node<TYPE>*& q)
        {
            mem = q;
        }
        void operator = (TreeIterator itr)
        {
            this->mem = itr.mem;
        }
        bool operator ==(TreeIterator itr)
        {
            return this->mem == itr.mem;
        }
        //TreeIterator operator +(int k)
        //{
        //    while (k-- && mem != NULL)
        //    {
        //        mem = mem->next;
        //    }
        //    return *this;
        //}
        //TreeIterator operator -(int k)
        //{
        //    while (k-- && mem != NULL)
        //    {
        //        mem = mem->prev;
        //    }
        //    return *this;
        //}
        TYPE& operator *()
        {
            return this->mem->data;
        }
        TreeIterator operator[](int k)
        {
            return *(*(this) + k);
        }
        void operator ++(int k)
        {
            if (this->mem->right)
            {
                this->mem = this->mem->right;
                while (this->mem->left != nullptr)
                    this->mem = this->mem->left;
            }
            else if (this->mem->parrent->right == this->mem)
            {
                while(this->mem->parrent->right == this->mem)
                    this->mem = this->mem->parrent;
                this->mem = this->mem->parrent;
            }
            else
            {
                this->mem = this->mem->parrent;
            }
        }
        void operator--(int k)
        {
            if (this->mem->left)
            {
                this->mem = this->mem->left;
                while (this->mem->right != nullptr)
                    this->mem = this->mem->right;
            }
            else if (this->mem->parrent->left == this->mem)
            {
                while (this->mem->parrent->left == this->mem)
                    this->mem = this->mem->parrent;
                this->mem = this->mem->parrent;
            }
            else
            {
                this->mem = this->mem->parrent;
            }
        }
        bool operator !=(TreeIterator itr)
        {
            return !(*this == itr);
        }
    };

    TreeIterator Begin()
    {
        Node<TYPE>* node = root;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    TreeIterator End()
    {
        Node<TYPE>* node = root;
        while (node->right != nullptr)
            node = node->right;
        return TreeIterator::TreeIterator(node);
    }
};