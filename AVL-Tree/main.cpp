#include<iostream>
#include"Windows.h"
#include"AVL-TREE.h"
#include <regex>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AVLTree items;

    int choice;
    do {
        std::cout << "  Меню:\n";
        std::cout << "1) Добавление студента\n";
        std::cout << "2) Вывод информации о студентах\n";
        std::cout << "3) Удаление информации о студентах\n";
        std::cout << "4) Поиск студента\n";
        std::cout << "5) Удаление студента\n";
        std::cout << "0) Выход из программы\n";
        std::cout << "Выберите пункт меню: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Ввод данных
            int id;
            std::string name;
            int course;
            std::string date;
            std::string contact;

            std::cout << "Введите информацию о студенте:\n";

            // Проверка номера студенческого билета
            do {
                std::cout << "Введите номер студенческого:  ";
                std::cin >> id;
            } while (std::cin.fail());
            std::cin.ignore();

            // Проверка ФИО студента
            do {
                std::cout << "ФИО студента: ";
                std::getline(std::cin, name);
                if (name.empty()) {
                    std::cout << "Некорректный ввод. Пожалуйста, введите ФИО студента.\n";
                }
            } while (name.empty());

            // Проверка курса
            do {
                std::cout << "Курс: ";
                std::cin >> course;
            } while (std::cin.fail());
            std::cin.ignore();

            // Проверка даты зачисления
            do {
                std::cout << "Дата зачисления: ";
                std::getline(std::cin, date);

            } while (date.empty());

            // Проверка контактной информации
            do {
                std::cout << "Контактная информация: ";
                std::getline(std::cin, contact);
            } while (contact.empty());

            items.insert(Student(id, name, course, date, contact));
            std::cout << std::endl;
            std::cout << " \n";
            items.printTree();
            std::cout << std::endl;
            break;

        }

        case 2: {
            // Вывод исходных данных
            items.display();
            std::cout << std::endl;

            break;
        }


        case 3: {
            items.clear();
            std::cout << std::endl;
            break;
        }



        case 4: {
            int id;
            std::cout << "Введите номер студенческого билета для поиска: ";
            std::cin >> id;

            Student* student = items.search(id);
            if (student != nullptr) {
                std::cout << "Информация о студенте:\n";
                std::cout << "Номер студенческого билета: " << student->studentId << "\n";
                std::cout << "ФИО студента: " << student->fullName << "\n";
                std::cout << "Курс: " << student->course << "\n";
                std::cout << "Дата зачисления: " << student->enrollmentDate << "\n";
                std::cout << "Контактная информация: " << student->contactInfo << "\n";
            }
            else {
                std::cout << "Студент с номером студенческого билета " << id << " не найден.\n";
            }
            std::cout << std::endl;
            break;


        }

        case 5: {
            int id;
            std::cout << "Введите номер студенческого билета для удаления: ";
            std::cin >> id;

            items.remove(id);
            std::cout << std::endl;
            break;

        }


        case 0: {// Выход из программы
            choice = 0;
            break;

        }

        default: {
            std::cout << "Некорректный выбор. Пожалуйста, выберите пункт от 0 до 5";
            std::cout << std::endl;

            break;

        }

        }
    } while (choice != 0);

    return 0;
}


