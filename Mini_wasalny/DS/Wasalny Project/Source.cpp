#include <iostream>
#include "Graph.h"
#include "Traversal.h"
#include "FindPath.h"
#include"User.h"

using namespace std;
int main() {
    Graph g;
    Traversal t;
    
    bool isTrue = false;
    ArrayList a;
    ArrayList *b;
    int userIndex=0;

    a.loadUserGraphsFromFile("C:\\Users\\hp\\source\\repos\\Mini_wasalny-main02\\DS\\Wasalny Project\\user1.txt");
    User u1;
    int e = 0;
    FindPath f(g);
    while (e != 3)

    {

        cout << "Welcome!!\n1.Login\n2.Sign Up\n3.End\n";
        cin >> e;
        if (e == 1) {
            bool correct = false;
            int trial = 0;
            while (trial != 3) {
                cout << "Enter username " << endl;
                cin >> u1.name;
                cout << "Enter password " << endl;

                u1.password = a.hidePassword();
                if ((a.searchByName(u1.name) == nullptr) || (a.searchByPassword(u1.password) == nullptr)) {
                    cout << "Invalid name or password!!" << endl;
                    trial++;
                }
                else {
                    cout << "Success.\n";
                    userIndex = a.getUserIndex(u1);
                    cout << userIndex<<endl;
                    correct = true;
                    break;
                }
            }
            if (correct) {
                isTrue = true;
                break;
            }

            //search about email and password
        }
        else if (e == 2) {
            string n;
            string e;
            string p;
            cout << "Enter Name: ";
            cin >> u1.name;
            cout << "Enter email: ";
            cin >> u1.email;
            cout << "Enter password: ";
            u1.password = a.hidePassword();
            
            userIndex = a.getUserIndex(u1);
            if (userIndex != -1) {
                cout << "user already exist !!!" << endl;
            }
            else {
                cout << "Success.\n";
                a.add(u1);
                userIndex = a.getUserIndex(u1);
                isTrue = true;
                break;
            }
           
        }
    }
    g = a.get(userIndex).graph;
    int c = 0;
    while ((c != 9) && (isTrue == true))
    {
        cout << "_______________________________________\n";
        cout << "1.add city\n2.add edge\n3.display graph\n4.remove city\n5.remove edge\n6.Traverce\n7.Find Path\n8.End" << endl;
        cin >> c;
        switch (c)
        {

        case 1: {
            cout << "Enter city: ";
            string cs;cin >> cs;
            int x, y;
            cout << "Enter X coordinate of '" << cs << "': ";
            cin >> x;
            cout << "Enter Y coordinate of '" << cs << "': ";
            cin >> y;
            g.addCity(cs, x, y);
            break;
        }
        case 2: {
            int d;
            string c1, c2;
            cout << "Enter first city: ";
            cin >> c1;
            cout << "Enter scound city: ";
            cin >> c2;
            cout << "Enter distant: ";
            cin >> d;
            char isTraffic;
            cout << "\nIs the road between '" << c1 << "' and '" << c2 << "' congested? (y/n): ";
            cin >> isTraffic;
            bool congested = (isTraffic == 'y' || isTraffic == 'Y');

            g.addEdge(c1, c2, d, congested);
            break;

        }
        case 3: {
            if (g.getGraph().empty())
                cout << "Graph is empty!" << endl;
            else
                g.displayGraph();
            break;

        }
        case 4: {
            string c;
            cout << "Enter city: ";
            cin >> c;
            g.removeCity(c);
            break;
        }
        case 5: {
            string c1, c2;
            cout << "Enter first city: ";
            cin >> c1;
            cout << "Enter scound city: ";
            cin >> c2;
            g.removeEdge(c1, c2);
            break;
        }
        case 6: {
            if (g.getGraph().empty())
                cout << "Graph is empty!" << endl;
            else
                t.traverse(g.getGraph());
            break;
        }
        case 7: {
            if (g.getGraph().empty())
                cout << "Graph is empty!" << endl;
            else 
            {
                int s;
                cout << "\n1.dijkestra\n2.A*" << endl;
                cin >> s;
                if (s == 1) {
                    string c1, c2;
                    cout << "Enter Start city: ";
                    cin >> c1;
                    cout << "Enter Goal city: ";
                    cin >> c2;
                    f.dijkstra(c1, c2);

                }
                else if (s == 2) {
                    int a;bool x;
                    cout << "\n1.Shortest Path\n2.Fastest Path\n";
                    cin >> a;
                    if (a == 1)x = false;
                    else if (a == 2)x = true;
                    else
                    {
                        cout << "Invalid Choise!\n";
                        break;
                    }
                    string c1, c2;
                    cout << "Enter Start city: ";
                    cin >> c1;
                    cout << "Enter Goal city: ";
                    cin >> c2;
                    f.AStar(c1, c2, x);

                }
            }
            break;

        }

        case 8: {
            isTrue = false;
            break;
        }




        default:
            cout << "Invalid Choise!\n";
            break;
        }
    }
    
    a.get(userIndex).graph = g;
   
    
    a.saveUserGraphsToFile("C:\\Users\\hp\\source\\repos\\Mini_wasalny-main02\\DS\\Wasalny Project\\user1.txt");

}