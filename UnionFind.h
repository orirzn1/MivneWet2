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
public:
    int size;
    int* num_of_copies;
    int* parent;
    int* rank;
    int* height_to_parent;
    int* height_of_stack;
    int* column;

public:
    UnionFind(int n): size(n) {
        num_of_copies = new int[size];
        parent = new int[size];
        rank = new int[size];
        height_to_parent = new int[size];
        height_of_stack = new int[size];
        column = new int[size];


        for (int i = 0; i < size; i++){
            parent[i] = i;
            rank [i] = 0;
            height_to_parent[i] = 0;
            height_of_stack[i] = 0;
            column[i] = i;
        }
    }

    ~UnionFind(){
        delete[] num_of_copies;
        delete[] parent;
        delete[] rank;
        delete[] height_to_parent;
        delete[] height_of_stack;
        delete[] column;
    }

    UnionFind& operator=(const UnionFind& other){
        if(this == &other)
            return *this;

        size = other.size;

        delete[] num_of_copies;
        delete[] parent;
        delete[] rank;
        delete[] height_to_parent;
        delete[] height_of_stack;
        delete[] column;

        num_of_copies = new int[size];
        parent = new int[size];
        rank = new int[size];
        height_to_parent = new int[size];
        height_of_stack = new int[size];
        column = new int[size];


        for (int i = 0; i < size; i++){
            parent[i] = other.parent[i];
            rank[i] = other.rank[i];
            height_to_parent[i] = other.height_to_parent[i];
            height_of_stack[i] = other.height_of_stack[i];
            column[i] = other.column[i];
        }

        return *this;


    }

    void getArray (int* arr){
        for (int i = 0; i<size; i++){
            num_of_copies[i] = arr[i];
            height_of_stack[i] = arr[i];
        }

    }

    int find (int index){

        if (parent[index]==index){
            return index;
        } else{
            //if(parent[parent[index]]!=parent[index])
             //   height_to_parent[index] += (height_to_parent[parent[index]]);
            //column[index] = column[parent[index]];
            //parent[index] = find(parent[index]);
            return find(parent[index]);
        }
        return parent[index];

    }

    void unite (int index1, int index2){

        int root1 = find(index1);
        int root2 = find(index2);

        if(root1 == root2){
            return;
        }

        column[root1] = column[root2];

        if(rank[root1]>rank[root2]){
            parent[root2] = root1;
            rank[root1]++;
            height_to_parent[root2] -= (height_of_stack[root2] + height_to_parent[root1]);
            height_to_parent[root1] += height_of_stack[root2];
            height_of_stack[root1] += height_of_stack[root2];
        } else if(rank[root1]<rank[root2]){
            parent[root1] = root2;
            rank[root1]++;
            height_to_parent[root1] += (height_of_stack[root2] - height_to_parent[root2]);
            height_of_stack[root2] += height_of_stack[root1];


        } else{
            parent[root1] = root2;
            height_to_parent[root1] += (height_of_stack[root2] - height_to_parent[root2]);
            rank[root2]++;
            height_of_stack[root2]+=height_of_stack[root1];
        }

    }

    int getHeight(int index, int height){
        if (parent[index]==index){
            height += height_to_parent[index];
            return height;
        } else{
            height += (height_to_parent[index] + getHeight(parent[index],height));
        }
        return height;
    };

    int getColumn(int index){
        if (parent[index]==index){
            return column[index];
        } else {
            return getColumn(parent[index]);
        }
    }

};

#endif /* UnionFind_h */
