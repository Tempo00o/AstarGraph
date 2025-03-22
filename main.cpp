#include "Graph.h"
#include "PathfinderGraph.h"
#include <iostream>

int main() {
    Graph graph;

    graph.addNode("A", 0, 0);
    graph.addNode("B", 2, 0);
    graph.addNode("C", 5, 0);
    graph.addNode("D", 1, 2);
    graph.addNode("E", 3, 3);
    graph.addNode("F", 5, 5);

    graph.addEdge("A", "B", 1);
    graph.addEdge("B", "C", 1);
    graph.addEdge("A", "D", 1);
    graph.addEdge("D", "E", 1);
    graph.addEdge("E", "F", 1);
    graph.addEdge("F", "C", 10);  

    auto path = aStarSearch(graph, "A", "C");

    if (path) {
        std::cout << "Path: ";
        for (const std::string& node : *path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
