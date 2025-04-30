#pragma once
#include "Student.h"
#include "Node.h"

class AVLTree {   // Класс, который управляет AVL-деревом
private:
    Node* root;

    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, Student student);
    Node* minValueNode(Node* node);
    Node* deleteNode(Node* root, int studentId);

public:
    AVLTree();
    ~AVLTree();
    Student* search(int studentId);
    void insert(Student student);
    void remove(int studentId);
    void clear();
    void clearH(Node* node);
    void display();
    void displayH(Node* node);
    void printTreeH(Node* root, std::string prefix, bool isLeft);
    void printTree();

};