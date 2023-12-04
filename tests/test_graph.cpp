#include "gnode.hpp"
#include "graph.hpp"
#include <gtest/gtest.h>

using namespace graph;

TEST(Graph, dijkstra) {
    auto graph = std::make_shared<Graph<GNode> >();
    // Add nodes and edges.
    auto node0 = std::make_shared<GNode>();
    auto node1 = std::make_shared<GNode>();
    auto node2 = std::make_shared<GNode>();
    auto node3 = std::make_shared<GNode>();
    auto node4 = std::make_shared<GNode>();
    auto node5 = std::make_shared<GNode>();
    // Add nodes into graph.
    graph->addNode(node0);
    graph->addNode(node1);
    graph->addNode(node2);
    graph->addNode(node3);
    graph->addNode(node4);
    graph->addNode(node5);

    // Add edges into graph.
    graph->addEdge(node0, node1);
    graph->addEdge(node0, node2);
    graph->addEdge(node0, node3);
    graph->addEdge(node1, node4);
    graph->addEdge(node2, node4);
    graph->addEdge(node2, node5);
    graph->addEdge(node3, node5);
    graph->addEdge(node4, node5);

    // Test dijkstra.
    EXPECT_EQ(graph->dijkstra(0, 5), 2);
    EXPECT_EQ(graph->dijkstra(0, 4), 2);
    EXPECT_EQ(graph->dijkstra(0, 3), 1);
    EXPECT_EQ(graph->dijkstra(0, 2), 1);
    EXPECT_EQ(graph->dijkstra(0, 1), 1);
    EXPECT_EQ(graph->dijkstra(1, 5), 2);
}