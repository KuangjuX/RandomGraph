#include "graph.hpp"
#include "gnode.hpp"
#include <fmt/core.h>

using namespace graph;

int main() {
    auto graph = std::make_shared<Graph<GNode> >();
    // Build a ring with 10 nodes.
    graph->buildRing(3);

    // Print the number of edges of each node.
    for (auto node : graph->nodes_) {
        fmt::println("Node {} has {} edges", node->getId(),
                     node->getEdgeNums());
    }

    graph->generateRandomGraph(2, 17);
    // Print the number of edges of each node.

    graph->printGraph();
    graph->dijkstra(4, 19);
    graph->dijkstra(3, 19);
    graph->dijkstra(2, 19);
    graph->dijkstra(1, 19);
    graph->dijkstra(0, 19);
    graph->dijkstra(19, 19);
    graph->dijkstra(18, 19);

    return 0;
}