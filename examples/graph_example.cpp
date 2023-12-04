#include "graph.hpp"
#include "gnode.hpp"
#include <iostream>

using namespace graph;

int main() {
    auto graph = std::make_shared<Graph<GNode> >();
    // Build a ring with 10 nodes.
    graph->buildRing(10);

    // Print the number of edges of each node.
    for (auto node : graph->nodes_) {
        std::cout << node->getId() << " " << node->getEdgeNums() << std::endl;
    }
    // Print the number of edges of each node.
    for (auto node : graph->nodes_) {
        std::cout << node->getId() << " " << node->getEdgeNums() << std::endl;
    }

    graph->generateRandomGraph(3, 20);
    // Print the number of edges of each node.
    for (auto node : graph->nodes_) {
        std::cout << node->getId() << " " << node->getEdgeNums() << std::endl;
    }
    return 0;
}