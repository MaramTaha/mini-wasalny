#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include "Graph.h"

class Traversal {
public:
    void traverse(const std::unordered_map<std::string, std::vector<Edge>>& graph);
private:
    std::vector<std::string> BFS(const std::unordered_map<std::string, std::vector<Edge>>& graph, const std::string& startCity);
    void displayBFS(const std::unordered_map<std::string, std::vector<Edge>>& graph, const std::string& startCity);
    void DFS(const std::string& startNode, const std::unordered_map<std::string, std::vector<Edge>>& graph);
};
