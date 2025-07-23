#include "User.h"


User::User(string n, string e, string p) {
    name = n;
    email = e;
    password = p;
}
User::User() {

}
//void  User::shg(int i) {
//    ArrayList a;
//    a.get(i).graph.displayGraph();
//}
void User::print() {
    cout << name << ", " << email << ", " << password << endl;
}

void ArrayList::add(User u) {
    if (size == capacity) resize();
    users[size++] = u;
}


ArrayList::ArrayList(int cap) {
    capacity = cap;
    size = 0;
    users = new User[capacity];
}

ArrayList::~ArrayList() {
    delete[] users;
}


User& ArrayList::get(int index) {
    if (index >= 0 && index < size)
        return users[index];
    throw out_of_range("Index out of bounds");
}

int ArrayList::getSize() {
    return size;
}

void ArrayList::resize() {
    capacity *= 2;
    User* newArr = new User[capacity];
    for (int i = 0; i < size; ++i)
        newArr[i] = users[i];
    delete[] users;
    users = newArr;
}

void ArrayList::printAll() {
    for (int i = 0; i < size; ++i) {
        users[i].print();
    }
}
User* ArrayList::searchByName(string name) {
    for (int i = 0; i < size; ++i) {
        if (users[i].name == name) {
            return &users[i];  // Return a pointer to the found user
        }
    }
    return nullptr; // Not found
}

User* ArrayList::searchByEmail(string email) {
    for (int i = 0; i < size; ++i) {
        if (users[i].email == email) {
            return &users[i];
        }
    }
    return nullptr;
}
User* ArrayList::searchByPassword(string password) {
    for (int i = 0; i < size; ++i) {
        if (users[i].password == password) {
            return &users[i];
        }
    }
    return nullptr;
}

void ArrayList::saveToFile(string file) {
    ofstream  writeFile(file);
    if (!writeFile) {
        cerr << "Error !!!\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        writeFile << users[i].name << "," << users[i].email << "," << users[i].password << "\n";

    }
    writeFile.close();
}
string ArrayList::hidePassword() {
    User a;
    int trial = 0;
    string password = "";
    char c;

    while (true) {
        c = _getch();
        if (c == 13) {
            cout << endl;
            break;

        }

        else if (c == 8) {
            password.pop_back();
            cout << "\b \b";
        }
        else {
            password += c;
            cout << "*";
        }
    }
    return password;
}
void ArrayList::loadFromFile(string file) {
    ifstream readFile(file);
    string line;
    while (getline(readFile, line)) {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);

        if (first != string::npos && second != string::npos) {
            string name = line.substr(0, first);
            string email = line.substr(first + 1, second - first - 1);
            string password = line.substr(second + 1);
            this->add(User(name, email, password));
        }
    }
    readFile.close();
}
void ArrayList::saveUserGraphsToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        User& user = users[i];

        out << "USER\n";
        out << user.name << "," << user.email << "," << user.password << "\n";
        // Delegate graph saving to Graph class
        user.graph.saveToStream(out);
    }

    out.close();
    std::cout << "All users and their graphs saved to '" << filename << "'.\n";
}

void ArrayList::loadUserGraphsFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error opening file for reading!\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line == "USER") {
            User user;

            // Read user info line: name,email,password
            if (!std::getline(in, line)) break;
            size_t first = line.find(',');
            size_t second = line.find(',', first + 1);
            if (first != std::string::npos && second != std::string::npos) {
                user.name = line.substr(0, first);
                user.email = line.substr(first + 1, second - first - 1);
                user.password = line.substr(second + 1);
            }

            // Load graph using the method from Graph class
            user.graph.loadFromStream(in);

            // Add the loaded user to the ArrayList
            this->add(user);
        }
    }

    in.close();
    std::cout << "All users and their graphs loaded from '" << filename << "'.\n";
}

int ArrayList::getUserIndex(User u) {
    for (int i = 0;i < this->getSize();i++) {
        if (this->get(i).name == u.name) {
            return i;
        }
        else continue;
    }
    return -1;
}
