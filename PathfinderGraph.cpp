// PathfinderGraph.cpp
#include "PathfinderGraph.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include<iostream>
struct Node {
    string name;
    double g, h;
    string parent;

    double f() const { return g + h; }
    bool operator>(const Node& other) const { return f() > other.f(); }
};
static double heuristic(const Graph& graph, const string& from, const string& to) {
    auto [x1, y1] = graph.getPosition(from);
    auto [x2, y2] = graph.getPosition(to);
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
optional<vector<string>> aStarSearch(const Graph& graph, const string& start, const string& goal) {
    if (!graph.contains(start) || !graph.contains(goal)) return nullopt;
  
    priority_queue<Node, vector<Node>, greater<Node>> openlist;
    unordered_map<string, double> gCost;
    unordered_map<string, string> cameFrom;

    openlist.push({ start, 0, 0, "" });
    gCost[start] = 0;

    while (!openlist.empty()) {
        Node current = openlist.top(); openlist.pop();
        if (current.name == goal) {
            vector<string> path;
            for (string at = goal; !at.empty(); at = cameFrom[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : graph.getNeighbors(current.name)) {
            double newG = gCost[current.name] + edge.cost;
            if (!gCost.count(edge.to) || newG < gCost[edge.to]) {
                gCost[edge.to] = newG;
                cameFrom[edge.to] = current.name;
                openlist.push({ edge.to, newG, 0, current.name});
            }
        }
    }

    return nullopt;
}
