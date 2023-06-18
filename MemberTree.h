//
//  Tree.h
//  MivneWet2edit
//
//  Created by Ori Razon on 7/6/2023.
//

#ifndef MemberTree_h
#define MemberTree_h

#include <exception>
#include <iostream>
#include "Tree.h"
#include "Customer.h"
#include <memory>



class MemberTree : public Tree<std::shared_ptr<Customer>, int>
{

    
public:

    MemberTree() : Tree<std::shared_ptr<Customer>,int>() {}
    ~MemberTree() {}

    node<std::shared_ptr<Customer>, int>* rightRotate(node<std::shared_ptr<Customer>, int>* node_a) override {
        node<std::shared_ptr<Customer>, int>* node_b = node_a->left;
        node_a->left = node_b->right;
        node_b->right = node_a;

        double temp = node_b->data->get_prize();

        node_b->data->add_extra(node_a->data->get_prize());
        if(node_a->left)
            node_a->left->data->add_extra(temp);
        node_a->data->add_extra(-1*node_a->data->get_prize() - 1*temp);


        node_a->height = max(height(node_a->left), height(node_a->right))+1;
        node_b->height = max(height(node_b->left), height(node_b->right))+1;
        return node_b;
    }


    node<std::shared_ptr<Customer>, int>* leftRotate(node<std::shared_ptr<Customer>, int>* node_a) override {
        node<std::shared_ptr<Customer>, int>* node_b = node_a->right;
        node_a->right = node_b->left;
        node_b->left = node_a;
        double temp = node_b->data->get_prize();

        node_b->data->add_extra(node_a->data->get_prize());
        if(node_a->right)
            node_a->right->data->add_extra(temp);
        node_a->data->add_extra(-1*node_a->data->get_prize() - 1*temp);


        node_a->height = max(height(node_a->left), height(node_a->right))+1;
        node_b->height = max(height(node_b->left), height(node_b->right))+1;
        return node_b;

    }

    double CalculateDiscount(int c_id, node<std::shared_ptr<Customer>,int>* N, double discount)
    {
        discount += N->data->get_prize();
        if (c_id > N->data->getID()){
            return CalculateDiscount(c_id,N->right,discount);
        } else if(c_id < N->data->getID()){
            return CalculateDiscount(c_id,N->left,discount);
        } else
            return discount;

    }

    void insert(std::shared_ptr<Customer>& data, int& key) override
    {
        if(root == nullptr || key > rightLeaf(root)->key)
            largest_node_ID = data.get()->getID();
        root = insert_recursion(root, data, key,0);
        node_count++;
    }

    node<std::shared_ptr<Customer>,int>* insert_recursion(node<std::shared_ptr<Customer>,int>* Node, std::shared_ptr<Customer>& data, int& key, int prevkey)
    {
        if(Node == nullptr)
        {
            node<std::shared_ptr<Customer>,int>* new_node =  new node<std::shared_ptr<Customer>,int>(data, key);
            if(root!=nullptr)
                new_node->data->add_extra(-1*CalculateDiscount(prevkey,root,0));
            return new_node;
        }
        if (key < Node->key)
            Node->left = insert_recursion(Node->left, data, key,Node->key);
        else if (key > Node->key)
            Node->right = insert_recursion(Node->right, data, key,Node->key);
        else
        {
            throw Failure();
        }

        // Update parent node's height
        Node->height = 1 + max(height(Node->left), height(Node->right));
        // Get balance of parent
        int balance = getBalance(Node);
        // Check if parent is unbalanced and split into LL, RR, LR, RL rotation cases
        // LL
        if (balance > 1 && key < Node->left->key)
            return rightRotate(Node);
        // RR
        if (balance < -1 && key > Node->right->key)
            return leftRotate(Node);

        // LR
        if (balance > 1 && key > Node->left->key)
        {
            Node->left = leftRotate(Node->left);
            return rightRotate(Node);
        }

        // RL
        if (balance < -1 && key < Node->right->key)
        {
            Node->right = rightRotate(Node->right);
            return leftRotate(Node);
        }
        return Node;
    }


};

#endif /* MemberTree_h */
