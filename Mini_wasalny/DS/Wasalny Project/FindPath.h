#ifndef FINDPATH_H
#define FINDPATH_H

#include "Graph.h"
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>

class FindPath {
private:
    const Graph& graph;

    struct Node {
        std::string city;
        double cost;
        double priority;
        bool operator>(const Node& other) const {
            return priority > other.priority;
        }
    };

    double heuristic(const CityData& a, const CityData& b);

public:
    FindPath(const Graph& g);

    void dijkstra(const std::string& start, const std::string& end);
    void AStar(const std::string& start, const std::string& end, bool considerTraffic);
};

#endif 
