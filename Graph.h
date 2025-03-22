// Graph.h
#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Edge {
    string to;
    double cost;
};
struct nodeInfo {
    pair<double, double>position;
    vector<Edge>edges;
};
class Graph {
public:
    void addNode(const string& name,const double &x,const double& y);
    void addEdge(const string& from, const string& to, double cost,bool bidirectional=false);
    const vector<Edge>& getNeighbors(const string& node) const;
    bool contains(const string& node) const;
    pair<double, double>getPosition(const string& node)const;

private:
    unordered_map<string, nodeInfo> nodes;
};