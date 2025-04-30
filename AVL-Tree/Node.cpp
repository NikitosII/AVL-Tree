#include"Student.h"
#include"Node.h"
// Конструктор по умолчанию
Node::Node() {
	data;
	left = nullptr;
	right = nullptr;
	height = 1;
}
// Конструктор с переменными
Node::Node(Student student) {
	data = student;
	left = nullptr;
	right = nullptr;
	height = 1;
}

