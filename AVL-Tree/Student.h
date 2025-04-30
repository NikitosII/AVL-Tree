#pragma once
#include<string>

struct Student {    // структура, представл€юща€ студента
    int studentId;
    std::string fullName;
    int course;
    std::string enrollmentDate;
    std::string contactInfo;


    //  онструктор по умолчанию
    Student();

    //  онструктор с переменными
    Student(int id, std::string name, int crs, std::string date, std::string contact);
};
