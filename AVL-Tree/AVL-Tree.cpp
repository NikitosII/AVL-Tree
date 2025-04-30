#include"AVL-TREE.h"
#include<iostream>

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    root = nullptr;
    clearH(root);
}

// Метод для удаления информации обо всех студентах
void AVLTree::clear() {
    clearH(root);
    root = nullptr;
}

// Вспомогательный метод для рекурсивного удаления узлов дерева
void AVLTree::clearH(Node* node) {
    if (node != nullptr) {
        clearH(node->left);
        clearH(node->right);
        delete node;
    }
}

// Функция для вывода бинарного дерева в консоль (вертикально)
void AVLTree::printTreeH(Node* root, std::string prefix, bool isLeft) {
    if (root != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        std::cout << root->data.studentId << std::endl;
        printTreeH(root->right, prefix + (isLeft ? "|   " : "    "), true);
        printTreeH(root->left, prefix + (isLeft ? "|   " : "    "), false);

    }
}
// Функция вызова вывода 1
void AVLTree::printTree() {
    return printTreeH(root, "", true);
}

// Вывод информации о студентах 
void AVLTree::display() {
    displayH(root);
}

// Вспомогательный метод для рекурсивного вывода информации о студентах
void AVLTree::displayH(Node* node) {
    if (node != nullptr) {
        displayH(node->left);
        std::cout << "Номер студенческого билета: " << node->data.studentId << "\n";
        std::cout << "ФИО студента: " << node->data.fullName << "\n";
        std::cout << "Курс: " << node->data.course << "\n";
        std::cout << "Дата зачисления: " << node->data.enrollmentDate << "\n";
        std::cout << "Контактная информация: " << node->data.contactInfo << "\n";
        std::cout << std::endl;
        displayH(node->right);
    }
}

// Функция возвращает высоту узла дерева.
int AVLTree::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Функия возвращает фактор равновесия - разница между высотой правой и левой ветви дерева.
int AVLTree::getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Функция выполняет правый поворот вокруг узла y. 
Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* z = x->right;

    x->right = y;
    y->left = z;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Функция выполняет левый поворот вокруг узла х. 
Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}


// Функция для добавления информации о студентах 
void AVLTree::insert(Student student) {
    root = insert(root, student);
}

// Вспомогательный метод для ввода информации о студентах
Node* AVLTree::insert(Node* node, Student student) {
    // Если текущий узел пустой, создаем новый узел с данными студента
    if (node == nullptr)
        return new Node(student);

    // Рекурсивно вставляем студента в левое или правое поддерево
    if (student.studentId < node->data.studentId)
        node->left = insert(node->left, student);
    else if (student.studentId > node->data.studentId)
        node->right = insert(node->right, student);
    else
        return node; // Если studentId уже существует, ничего не делаем


    // Обновляем высоту текущего узла
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalance(node);


    // Проверяем, нуждается ли дерево в балансировке
    // If Левое поддерево слишком высокое
    if (balanceFactor > 1) {
        // Левый левый случай
        if (student.studentId < node->left->data.studentId)
            return rotateRight(node); // Выполняем правый поворот
        // Левый правый случай
        else {
            node->left = rotateLeft(node->left); // Выполняем левый поворот на левом поддереве
            return rotateRight(node); // Затем выполняем правый поворот
        }
    }

    // If Правое поддерево слишком высокое
    if (balanceFactor < -1) {
        // Правый правый случай
        if (student.studentId > node->right->data.studentId)
            return rotateLeft(node); // Выполняем левый поворот

        // Правый левый случай
        else {

            node->right = rotateRight(node->right);// Выполняем правый поворот на правом поддереве
            return rotateLeft(node);  // // Затем выполняем левый поворот
        }
    }

    // Возвращаем обновленный узел
    return node;
}


// Функция возвращает узел с минимальным значением ключа в поддереве с корнем в узле node.
Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}
// Функция рекурсивно удаляет узел с заданным ключом из дерева.
// Если узел найден, то он удаляется, а дерево балансируется путем выполнения соответствующих поворотов.
Node* AVLTree::deleteNode(Node* root, int studentId) {

    // Если дерево пустое, возвращаем nullptr
    if (root == nullptr)
        return root;

    // Рекурсивно ищем узел для удаления
    if (studentId < root->data.studentId)
        root->left = deleteNode(root->left, studentId);
    else if (studentId > root->data.studentId)
        root->right = deleteNode(root->right, studentId);
    else {
        // Нашли узел then: 

        // Случай 1: У узла нет "детей" или только один "ребенок"
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right; // Сохраняем указатель на единственного "ребенка"

            // If ребенка нет, сохраняем текущий узел и устанавливаем root в nullptr
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp; // Копируем данные "ребенка" в текущий узел

            delete temp; // Удаляем временный указатель
        }

        // Случай 2: У узла два "ребенка" 
        else {
            Node* temp = minValueNode(root->right); // Находим минимальный узел в правом поддереве

            root->data = temp->data; // Копируем данные

            root->right = deleteNode(root->right, temp->data.studentId);
        }
    }


    // Если дерево стало пустым после удаления, возвращаем nullptr
    if (root == nullptr)
        return root;

    // Обновляем высоту текущего узла
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getBalance(root);

    // Проверяем, нуждается ли дерево в балансировке
    // Левое поддерево слишком высокое
    if (balanceFactor > 1) {
        if (getBalance(root->left) >= 0)
            return rotateRight(root);
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    // Правое поддерево слишком высокое
    if (balanceFactor < -1) {
        if (getBalance(root->right) <= 0)
            return rotateLeft(root);
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    // Возвращаем обновленный узел
    return root;
}

// Функция для удаления информации о студенте 
void AVLTree::remove(int studentId) {
    root = deleteNode(root, studentId);
}

// Функция для поиска информации о студенте 
Student* AVLTree::search(int studentId) {
    Node* current = root;

    while (current != nullptr) {
        // If нашли 
        if (studentId == current->data.studentId)
            return &(current->data);
        // Проходим по левому поддреву 
        if (studentId < current->data.studentId)
            current = current->left;
        else
            // Проходим по правому поддреву 
            current = current->right;
    }
    // If не нашли 
    return nullptr;
}
