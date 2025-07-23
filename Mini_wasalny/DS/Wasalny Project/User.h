#ifndef USER_H
#define USER_H
#pragma once
#include <functional>
#include<list>
#include <fstream>
#include "Graph.h"
#include <conio.h>
using namespace std;

class User {
public:
    string name;
    string email;
    string password;
    Graph graph;
    User();
    User(string n, string e, string p);
    void print();
   // void shg(int i);

};

class ArrayList {
    User* users;
    int capacity;
    int size;

public:
    ArrayList(int cap = 10);

    ~ArrayList();

    void add(User u);

    User &get(int index);

    int getSize();

    void resize();

    void printAll();
    User* searchByName(string name);
    User* searchByEmail(string email);
    User* searchByPassword(string password);
    int getUserIndex(User u);
    string hidePassword();

    void saveToFile(string file);
    void loadFromFile(string file);

    void saveUserGraphsToFile(const std::string& filename);
    void loadUserGraphsFromFile(const std::string& filename);
};

#endif