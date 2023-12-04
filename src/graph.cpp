#include "graph.hpp"
#include "gnode.hpp"
#include <queue>
#include <algorithm>
#include <iostream>
#include <fmt/core.h>

namespace graph {
    template <>
    void Graph<GNode>::addNode(std::shared_ptr<GNode> node) {
        nodes_.push_back(node);
    }

    template <>
    void Graph<GNode>::addEdge(std::shared_ptr<GNode> src,
                               std::shared_ptr<GNode> dst) {
        src->connectNode(dst);
    }

    template <>
    void Graph<GNode>::addNodeAndEdge(std::shared_ptr<GNode> src,
                                      std::shared_ptr<GNode> dst) {
        addNode(src);
        addNode(dst);
        addEdge(src, dst);
    }

    template <>
    void Graph<GNode>::buildRing(int m) {
        for (int i = 0; i < m; i++) {
            addNode(std::make_shared<GNode>());
        }
        for (int i = 0; i < m; i++) {
            addEdge(nodes_[i], nodes_[(i + 1) % m]);
        }
    }

    template <>
    uint64_t Graph<GNode>::selectNode() {
        // The probability of selecting each existing node is proportional to
        // the number of edges it already has.
        std::vector<uint64_t> nums;
        for (auto node : nodes_) {
            nums.push_back(node->getEdgeNums());
        }
        uint64_t sum = 0;
        for (auto num : nums) {
            sum += num;
        }
        int64_t rand = std::rand() % sum;
        uint64_t index = 0;
        while (rand > 0) {
            fmt::println("rand = {}, nums[{}] = {}", rand, index, nums[index]);
            rand -= nums[index];
            index++;
        }
        return (int64_t)(index - 1) >= 0 ? (index - 1) : 0;
    }

    template <>
    void Graph<GNode>::generateRandomGraph(int m, int t) {
        for (int i = 0; i < t; i++) {
            // Create a new node.
            auto node = std::make_shared<GNode>();
            // Add the new node to the graph.
            addNode(node);
            // Add a new node and randomly construct 𝑚 edges to connect the new
            // node with existing nodes. The probability of selecting each
            // existing node is proportional to the number of edges it already
            // has.
            for (int j = 0; j < m; j++) {
                // Select a node proportional to the number of edges it already
                // randomly has.
                uint64_t index = selectNode();
                // Make sure the selected node is not the new node.
                while (index == node->getId() || node->existConnection(index)) {
                    index = selectNode();
                }
                // fmt::println("Select node {} to connect with node {}", index,
                //              node->getId());
                // Add an edge between the new node and the selected node.
                addEdge(node, nodes_[index]);
            }
        }
    }

    // Implement Dijkstra's algorithm to find the shortest path between two
    // nodes and output the path trace.
    template <>
    uint64_t Graph<GNode>::dijkstra(uint64_t src, uint64_t dst) {
        std::priority_queue<std::pair<int, uint64_t>,
                            std::vector<std::pair<int, uint64_t>>,
                            std::greater<>>
            pq;
        std::vector<int> distance(nodes_.size(),
                                  std::numeric_limits<int>::max());
        std::vector<std::vector<uint64_t>> paths(nodes_.size());

        // 初始化源节点
        distance[src] = 0;
        paths[src].push_back(src);
        pq.push(std::make_pair(0, src));

        while (!pq.empty()) {
            uint64_t currNode = pq.top().second;
            pq.pop();

            if (currNode == dst) {
                break;  // 已找到目标节点，提前退出
            }

            int currDist = distance[currNode];

            for (const auto& nextNode : nodes_[currNode]->next_) {
                int edgeWeight = 1;  // 连通节点间距离为1
                int newDist = currDist + edgeWeight;

                if (newDist < distance[nextNode]) {
                    distance[nextNode] = newDist;
                    paths[nextNode] = paths[currNode];
                    paths[nextNode].push_back(nextNode);
                    pq.push(std::make_pair(newDist, nextNode));
                }
            }
        }

        // 打印路径
        std::cout << "Shortest path from Node " << src << " to Node " << dst
                  << ":" << std::endl;
        for (const auto& node : paths[dst]) {
            std::cout << node << " -> ";
        }

        std::cout << "End " << std::endl;

        // 打印距离
        std::cout << "Distance from Node " << src << " to Node " << dst << ": "
                  << distance[dst] << std::endl;
        return distance[dst];
    }

    template <>
    void Graph<GNode>::printGraph() {
        for (auto node : nodes_) {
            fmt::print("Node {} connects to: ", node->getId());
            for (auto next : node->next_) {
                fmt::print("{} ", next);
            }
            fmt::print("\n");
        }
    }
}  // namespace graph