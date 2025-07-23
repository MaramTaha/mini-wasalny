#include "Graph.h"

void Graph::addCity(const string& city, double x, double y) {
    if (this->graph.find(city) == this->graph.end()) {
        this->graph[city] = {};
        this->coordinates[city] = { x, y };
        cout << "City '" << city << "' added at coordinates (" << x << ", " << y << ").\n";
    }
    else {
        cout << "City '" << city << "' already exists.\n";
    }
}

void Graph::addEdge(const string& city1, const string& city2, int distance, bool isCrowded) {
    if (graph.find(city1) != graph.end() && graph.find(city2) != graph.end()) {
        graph[city1].push_back({ city2, distance, isCrowded });
        graph[city2].push_back({ city1, distance, isCrowded });
        cout << "Edge added between '" << city1 << "' and '" << city2 << "' with distance " << distance << " km.\n";
        if (isCrowded) {
            cout << "The road is crowded.\n";
        }
        else {
            cout << "The road is not crowded.\n";
        }
    }
    else {
        cout << "One or both cities do not exist.\n";
    }
}

void Graph::displayGraph() const {
    cout << "Graph data:\n";
    for (const auto& pair : this->graph) {
        const string& city = pair.first;
        const vector<Edge>& neighbors = pair.second;

        cout << city << " --> ";
        for (const auto& neighbor : neighbors) {
            cout << "(" << neighbor.destination << ", " << neighbor.distance << " km";
            if (neighbor.isCrowded) {
                cout << ", Crowded";
            }
            cout << ") ";
        }
        cout << endl;
    }
}

void Graph::removeCity(const string& city) {
    if (graph.erase(city)) {
        cout << "City '" << city << "' removed successfully.\n";
        coordinates.erase(city);
    }
    else {
        cout << "City '" << city << "' not found in graph.\n";
    }

    for (auto& pair : graph) {
        auto& neighbors = pair.second;
        neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [&](const Edge& edge) {
            return edge.destination == city;
            }), neighbors.end());
    }
}

void Graph::removeEdge(const string& city1, const string& city2) {
    bool removed = false;

    if (graph.find(city1) != graph.end()) {
        auto& neighbors = graph[city1];
        size_t before = neighbors.size();
        neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [&](const Edge& edge) {
            return edge.destination == city2;
            }), neighbors.end());
        if (neighbors.size() < before) {
            removed = true;
        }
    }

    if (graph.find(city2) != graph.end()) {
        auto& neighbors = graph[city2];
        size_t before = neighbors.size();
        neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [&](const Edge& edge) {
            return edge.destination == city1;
            }), neighbors.end());
        if (neighbors.size() < before) {
            removed = true;
        }
    }

    if (removed) {
        cout << "Edge between '" << city1 << "' and '" << city2 << "' removed successfully.\n";
    }
    else {
        cout << "Edge between '" << city1 << "' and '" << city2 << "' was not found.\n";
    }
}

const unordered_map<string, vector<Edge>>& Graph::getGraph() const {
    return graph;
}

const unordered_map<string, CityData>& Graph::getCoordinates() const {
    return coordinates;
}
// for std::minmax
//void Graph::saveToStream(std::ostream& out) const {
//    out << "CITIES\n";
//    for (const auto& [city, coord] : getCoordinates()) {
//        out << city << " " << coord.x << " " << coord.y << "\n";
//    }
//
//    out << "EDGES\n";
//    std::set<std::pair<std::string, std::string>> written;
//    for (const auto& [city, edges] : getGraph()) {
//        for (const auto& edge : edges) {
//            auto pairKey = std::minmax(city, edge.destination);
//            if (written.insert(pairKey).second) {
//                out << city << " " << edge.destination << " " << edge.distance << " " << edge.isCrowded << "\n";
//            }
//        }
//    }
//
//    out << "END\n";
//}

void Graph::saveToStream(ostream& out) const {
    out << "CITIES\n";
    for (const auto& pair : this->coordinates) {
        const string& city = pair.first;
        const CityData& coord = pair.second;
        out << city << " " << coord.x << " " << coord.y << "\n";
    }

    out << "EDGES\n";

    set<pair<string, string>> writtenEdges;

    for (const auto& pair : this->graph) {
        const string& city = pair.first;
        const vector<Edge>& edges = pair.second;

        for (const auto& edge : edges) {
            auto edgeKey = std::minmax(city, edge.destination);
            if (writtenEdges.count(edgeKey) == 0) {
                out << city << " " << edge.destination << " "
                    << edge.distance << " " << edge.isCrowded << "\n";
                writtenEdges.insert(edgeKey);
            }
        }
    }

    out << "END\n";
}


void Graph::loadFromStream(istream& in) {
    graph.clear();
    coordinates.clear();
    
    string line;
    string section;

    while (getline(in, line)) {
        if (line == "CITIES" || line == "EDGES") {
            section = line;
        }
        else if (line == "END") {
            break;
        }
        else if (section == "CITIES") {
            istringstream iss(line);
            string city;
            double x, y;
            if (iss >> city >> x >> y) {
                addCity(city, x, y);
            }
        }
        else if (section == "EDGES") {
            istringstream iss(line);
            string city1, city2;
            int distance;
            bool isCrowded;
            if (iss >> city1 >> city2 >> distance >> isCrowded) {
                addEdge(city1, city2, distance, isCrowded);
            }
        }
    }
}
