#include"Student.h"

// Конструктор по умолчанию
Student::Student() {
    studentId = 0;
    fullName = "";
    course = 0;
    enrollmentDate = "";
    contactInfo = "";

}

// Конструктор с переменными
Student::Student(int id, std::string name, int crs, std::string date, std::string contact) {
    studentId = id;
    fullName = name;
    course = crs;
    enrollmentDate = date;
    contactInfo = contact;
};