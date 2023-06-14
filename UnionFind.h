//
//  Tree.h
//  MivneWet2edit
//
//  Created by Ori Razon on 7/6/2023.
//

#ifndef UnionFind_h
#define UnionFind_h

#include <exception>
#include <iostream>
#include "Record.h"

class UnionFind{

    int size;
    int* parent;
    int* rank;
    int* height_to_parent;
    int* height_of_stack;

public:
    UnionFind(int n): size(n) {
        parent = new int[size];
        rank = new int[size];
        height_to_parent = new int[size];
        height_of_stack = new int[size];


        for (int i = 0; i < size; i++){
            parent[i] = i;
            rank [i] = 0;
            height_to_parent[i] = 0;
            height_of_stack[i] = 1;
        }
    }

    ~UnionFind(){
        delete[] parent;
        delete[] rank;
        delete[] height_to_parent;
        delete[] height_of_stack;
    }

    UnionFind& operator=(const UnionFind& other){
        if(this == &other)
            return *this;

        size = other.size;

        delete[] parent;
        delete[] rank;
        delete[] height_to_parent;
        delete[] height_of_stack;

        parent = new int[size];
        rank = new int[size];
        height_to_parent = new int[size];
        height_of_stack = new int[size];

        for (int i = 0; i < size; i++){
            parent[i] = other.parent[i];
            rank[i] = other.rank[i];
            height_to_parent[i] = other.height_to_parent[i];
            height_of_stack[i] = other.height_of_stack[i];
        }

        return *this;


    }

    int find (int index){

        if (parent[index]==index){
            return index;
        } else{
            height_to_parent[index]+= height_to_parent[parent[index]];
            parent[index] = find(parent[index]);
        }
        return parent[index];

    }

    void unite (int index1, int index2){

        int root1 = find(index1);
        int root2 = find(index2);

        if(root1 == root2){
            return;
        }

        if(rank[root1]>rank[root2]){
            parent[root2] = root1;
            height_to_parent[root2] = height_of_stack[root1];
            height_of_stack[root1]+=height_of_stack[root2];
        } else if(rank[root1]<rank[root2]){
            parent[root1] = root2;
            height_to_parent[root1] = height_of_stack[root2];
            height_of_stack[root2]+=height_of_stack[root1];

        } else{
            parent[root1] = root2;
            height_to_parent[root1] = height_of_stack[root2];
            rank[root2]++;
            height_of_stack[root2]+=height_of_stack[root1];
        }

    }

    int getHeight(int index){
        if (parent[index]==index){
            return height_to_parent[index] + 1;
        } else{
            height_to_parent[index]+= height_to_parent[parent[index]];
            parent[index] = find(parent[index]);
        }
        return height_to_parent[index] + 1;
    };

};

#endif /* UnionFind_h */
