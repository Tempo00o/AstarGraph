
#include "Graph.h"
#include<cmath>
void Graph::addNode(const string& name, const double& x, const double& y) {
    if (!nodes.count(name))
    {
        nodes[name] = nodeInfo{ {x,y},{} };
    }
    else {
        nodes[name].position = { x,y };
    }
}
void Graph::addEdge(const string& from, const string& to, double cost, bool bidirectional) {
    if (!nodes.count(from)) nodes[from] = nodeInfo{ {0.0,0.0},{} };
    if (!nodes.count(to)) nodes[to] = nodeInfo{ {0.0,0.0},{} };
    nodes[from].edges.push_back(Edge{to, cost});
    if (bidirectional) {
        nodes[to].edges.push_back(Edge{ from, cost });
    }
}
const vector<Edge>& Graph::getNeighbors(const string& node) const {
    static const vector<Edge> empty ;
    auto it = nodes.find(node);
    return it != nodes.end() ? it->second.edges : empty;
}


bool Graph::contains(const string& node) const {
    return nodes.count(node) > 0;
}
pair<double, double> Graph::getPosition(const string& node)const
{
    auto it = nodes.find(node);
    if (it != nodes.end()) return it->second.position;
    else return make_pair(0.0, 0.0);
}