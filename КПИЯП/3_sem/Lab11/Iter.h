#pragma once
#include "Binary_tree.h"

template<class TYPE>
class Iter
{
	Node<TYPE>* mem;
public:
    Iter()
    {
        mem = NULL;
    }
    Iter(Node<TYPE>* mem)
    {
        this->mem = mem;
    }
    Node<TYPE>* getMem();
    void make(Node<TYPE>*& q)
    {
        mem = q;
    }
    void operator = (Iter itr)
    {
        this->mem = itr.mem;
    }
    bool operator ==(Iter itr)
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
    Iter operator[](int k)
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
            while (this->mem->parrent->right == this->mem)
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
    bool operator !=(Iter itr)
    {
        return !(*this == itr);
    }
};

template<class TYPE>
inline Node<TYPE>* Iter<TYPE>::getMem()
{
    return mem;
}
