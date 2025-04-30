#pragma once
struct Node {     // структура, представляющая узел AVL-дерева
	Student data;
	Node* left;
	Node* right;
	int height;

	Node();
	Node(Student student);
};
