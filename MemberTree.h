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

};

#endif /* MemberTree_h */
