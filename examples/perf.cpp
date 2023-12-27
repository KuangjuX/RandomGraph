#include "graph.hpp"
#include "gnode.hpp"
#include <fmt/core.h>
#include <chrono>
#include <random>
#include <assert.h>

using namespace graph;

const int ITER = 100;

int main(int argc, char* argv[]) {
    assert(argc == 2);
    uint64_t T0 = atoi(argv[1]);

    fmt::println("T0: {}", T0);

    auto graph = std::make_shared<Graph<GNode> >();
    // Build a ring with 10 nodes.
    graph->buildRing(3);

    // Print the number of edges of each node.
#ifdef DEBUG
    for (auto node : graph->nodes_) {
        fmt::println("Node {} has {} edges", node->getId(),
                     node->getEdgeNums());
    }
#endif

    auto start = std::chrono::high_resolution_clock::now();
    graph->generateRandomGraph(2, T0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double milliseconds = duration.count() * 1000.0;
    double seconds = milliseconds / 1000.0;
    double milliseconds2 = milliseconds - seconds * 1000.0;
    fmt::println("Random Graph Generation Time: {}.{}s", seconds,
                 milliseconds2);

    fmt::println("Graph generated.");
    // Print the number of edges of each node.

    // graph->printGraph();
    // graph->dijkstra(4, 19);
    // graph->dijkstra(3, 19);
    // graph->dijkstra(2, 19);
    // graph->dijkstra(1, 19);
    // graph->dijkstra(0, 19);
    // graph->dijkstra(19, 19);
    // graph->dijkstra(18, 19);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, T0);

    double totalMilliseconds = 0.0;

    for (int i = 0; i < ITER; i++) {
        // 生成两个随机数
#ifdef ACC
        int random1 = 1;
        int random2 = T0;
#else
        int random1 = dist(gen);
        int random2 = dist(gen);
#endif

        // 记录开始时间点
        auto start = std::chrono::high_resolution_clock::now();

        // 调用 Dijkstra 算法函数，并传递随机数作为参数
        graph->dijkstra(random1, random2);

        // 记录结束时间点
        auto end = std::chrono::high_resolution_clock::now();

        // 计算执行时间
        std::chrono::duration<double> duration = end - start;
        double milliseconds = duration.count() * 1000.0;

        // 累计总执行时间
        totalMilliseconds += milliseconds;
    }

    double averageMilliseconds = totalMilliseconds / ITER;

    fmt::println("Average time: {} ms", averageMilliseconds);

    return 0;
}