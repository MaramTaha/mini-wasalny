#include "Traversal.h"
#include <iostream>
using namespace std;

vector<string> Traversal::BFS(const unordered_map<string, vector<Edge>>& graph, const string& startCity) {
    unordered_set<string> visited;
    queue<string> q;
    vector<string> visitOrder;

    if (graph.find(startCity) == graph.end()) {
        cout << "City does not exist!" << endl;
        return visitOrder;
    }

    visited.insert(startCity);
    q.push(startCity);

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        visitOrder.push_back(current);

        for (const auto& adj : graph.at(current)) {
            string city = adj.destination;
            if (visited.find(city) == visited.end()) {
                visited.insert(city);
                q.push(city);
            }
        }
    }
    return visitOrder;
}

void Traversal::displayBFS(const unordered_map<string, vector<Edge>>& graph, const string& startCity) {
    vector<string> display = BFS(graph, startCity);
    for (size_t i = 0; i < display.size(); ++i) {
        cout << display[i];
        if (i != display.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void Traversal::DFS(const string& startNode, const unordered_map<string, vector<Edge>>& graph) {
    set<string> visited;
    stack<string> s;

    s.push(startNode);
    cout << "DFS Visit Order:\n";

    while (!s.empty()) {
        string current = s.top();
        s.pop();

        if (visited.count(current)) continue;

        visited.insert(current);
        cout << current << " -> ";

        if (graph.count(current)) {
            const auto& neighbors = graph.at(current);
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                const string& neighbor = neighbors[i].destination;
                if (!visited.count(neighbor)) {
                    s.push(neighbor);
                }
            }
        }
    }

    cout << endl;
}

void Traversal::traverse(const unordered_map<string, vector<Edge>>& graph) {
    int choice;
    cout << "1. DFS\n2. BFS\n";
    cin >> choice;

    string start;
    cout << "Enter the starting node (city name): ";
    cin >> start;

    if (graph.count(start) == 0) {
        cout << "Start node not found in the graph.\n";
        return;
    }

    if (choice == 1) {
        DFS(start, graph);
    }
    else if (choice == 2) {
        displayBFS(graph, start);
    }
    else {
        cout << "Invalid choice!\n";
    }
}
