//
//  HashTable.h
//  MivneWet2edit
//
//  Created by Ori Razon on 29/5/2023.
//

#ifndef HashTable_h
#define HashTable_h

#include "Tree.h"

const int DOUBLE = 2;
const int HALF = 0.5;

template <class T>
class hashTable
{
private:
    int table_size;
    Tree<T, int>** tree_array; //an array of pointers to trees
    int hashFunction(int ID)
    {
        return ID % table_size;
    }
public:
    explicit hashTable(int size) : table_size(size), tree_array(new Tree<T, int>*[size])
    {
        for (int i = 0; i < size; ++i)
            tree_array[i] = new Tree<T, int>();
    }

    ~hashTable()
    {
        for (int i = 0; i < table_size; ++i)
            delete tree_array[i];
        delete[] tree_array;
    }
    
    void doubleSize()
    {
        modifySize(DOUBLE);
    }
    
    void halfSize()
    {
        modifySize(HALF);
    }
    
    void modifySize(int size_change_factor)
    {
        int new_size = size_change_factor*table_size;
        Tree<T, int>** new_array = new Tree<T, int>*[new_size];
        for (int i = 0; i < new_size; i++)
            new_array[i] = new Tree<T, int>();
        for (int i = 0; i < table_size; i++)
        {
            Tree<T, int>* current = tree_array[i];
            modifySizeAux(new_array, current->getRoot(), new_size);
            delete tree_array[i];
        }
        delete[] tree_array;
        tree_array = new_array;
        table_size = new_size;
    }
    
    void modifySizeAux(Tree<T, int>** new_array, node<T, int>* N, int new_size)
    {
        if(N)
        {
            modifySizeAux(new_array, N->right, new_size);
            modifySizeAux(new_array, N->left, new_size);
            int newIndex = (N->data.get()->getID) % new_size;
            new_array[newIndex]->insert(N);
        }
    }

    bool insert(T& object)
    {
        int ID = object.get()->getID();
        int index = hashFunction(ID);
        try
        {
            tree_array[index]->insert(object, ID);
            return true; 
        }
        catch(Failure& e)
        {
            return false;
        }
    }

    bool remove(int ID)
    {
        int index = hashFunction(ID);
        try
        {
            tree_array[index]->remove(ID);
            return true;
        }
        catch(Failure& e)
        {
            return false;
        }
    }

    
    T findObject(int ID)
    {
        int index = hashFunction(ID);
        return (tree_array[index]->findNode(ID))->data;
    }
    
    void zeroCustomerDebt()
    {
        for(int i = 0; i < table_size; i++)
        {
            zeroCustomerDebtAux(tree_array[i]->getRoot());
        }
    }
    
    void zeroCustomerDebtAux(node<T, int>* N)
    {
        if(N)
        {
            zeroCustomerDebtAux(N->right);
            zeroCustomerDebtAux(N->left);
            N->data.get()->zeroCustomerDebt(); 
        }
    }
    
    int getSize()
    {
        return table_size; 
    }
};

#endif /* HashTable_h */
