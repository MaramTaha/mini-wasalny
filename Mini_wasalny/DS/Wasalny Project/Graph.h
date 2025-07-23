#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm> 
using namespace std;

struct CityData {
    double x, y;
};

struct Edge {
    string destination;
    int distance;
    bool isCrowded;
};

class Graph {
private:
    unordered_map<string, vector<Edge>> graph;
    unordered_map<string, CityData> coordinates;

public:
    void addCity(const string& city, double x, double y);
    void addEdge(const string& city1, const string& city2, int distance, bool isCrowded);
    void displayGraph() const;
    void removeCity(const string& city);
    void removeEdge(const string& city1, const string& city2);

    const unordered_map<string, vector<Edge>>& getGraph() const;
    const unordered_map<string, CityData>& getCoordinates() const;

    void saveToStream(ostream& out) const;
    void loadFromStream(istream& in);

};

#endif
