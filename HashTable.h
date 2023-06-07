//
//  HashTable.h
//  MivneWet2edit
//
//  Created by Ori Razon on 29/5/2023.
//

#ifndef HashTable_h
#define HashTable_h

#include "Tree.h"

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
    
    hashTable resize()
    {
        //TODO;
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
