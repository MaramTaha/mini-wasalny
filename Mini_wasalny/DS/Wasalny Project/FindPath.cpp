#include "FindPath.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

FindPath::FindPath(const Graph& g) : graph(g) {}

double FindPath::heuristic(const CityData& a, const CityData& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void FindPath::dijkstra(const std::string& start, const std::string& end) {
    const auto& g = graph.getGraph();
    unordered_map<string, int> distance;
    unordered_map<string, string> prev;
    unordered_map<string, bool> visited;

    for (const auto& node : g) {
        distance[node.first] = INT_MAX;
        visited[node.first] = false;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    distance[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        pair<int, string> top = pq.top(); pq.pop();
        int dist = top.first;
        string city = top.second;
        if (visited[city]) continue;
        visited[city] = true;

        for (const auto& edge : g.at(city)) {
            if (!visited[edge.destination]) {
                int newDist = distance[city] + edge.distance;
                if (newDist < distance[edge.destination]) {
                    distance[edge.destination] = newDist;
                    prev[edge.destination] = city;
                    pq.push({ newDist, edge.destination });
                }
            }
        }
    }

    if (distance[end] == INT_MAX) {
        cout << "No path found between " << start << " and " << end << ".\n";
        return;
    }

    cout << "Shortest path from " << start << " to " << end << " is " << distance[end] << " km.\n";
    cout << "Path: ";

    stack<string> path;
    string curr = end;
    while (curr != start) {
        path.push(curr);
        curr = prev[curr];
    }
    path.push(start);

    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

void FindPath::AStar(const string& start, const string& end, bool considerTraffic) {
    const auto& g = graph.getGraph();
    const auto& coords = graph.getCoordinates();

    if (!coords.count(start) || !coords.count(end)) {
        cout << "Start or end city not found in coordinates.\n";
        return;
    }

    unordered_map<string, double> cost;
    unordered_map<string, string> parent;
    priority_queue<Node, vector<Node>, greater<>> pq;

    cost[start] = 0;
    pq.push({ start, 0, heuristic(coords.at(start), coords.at(end)) });

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();

        if (current.city == end) break;

        for (const Edge& edge : g.at(current.city)) {
            double trafficFactor = considerTraffic && edge.isCrowded ? 1.5 : 1.0;
            double newCost = cost[current.city] + edge.distance * trafficFactor;

            if (!cost.count(edge.destination) || newCost < cost[edge.destination]) {
                cost[edge.destination] = newCost;
                parent[edge.destination] = current.city;
                double priority = newCost + heuristic(coords.at(edge.destination), coords.at(end));
                pq.push({ edge.destination, newCost, priority });
            }
        }
    }

    if (!cost.count(end)) {
        cout << "No path found from " << start << " to " << end << ".\n";
        return;
    }

    cout << "A* Path from " << start << " to " << end << ": ";
    vector<string> path;
    string current = end;
    while (current != start) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Distance: " << cost[end];
    if (considerTraffic)
        cout << " (Fastest Path)\n";
    else
        cout << " (Shortest Path)\n";
}
