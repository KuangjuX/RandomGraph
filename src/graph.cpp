#include "graph.hpp"
#include "gnode.hpp"
#include <algorithm>
#include <iostream>

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
        std::vector<std::shared_ptr<GNode>> nodes;
        for (int i = 0; i < m; i++) {
            nodes.push_back(std::make_shared<GNode>(i));
        }
        for (int i = 0; i < m; i++) {
            addNodeAndEdge(nodes[i], nodes[(i + 1) % m]);
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
        uint64_t rand = std::rand() % sum;
        uint64_t index = 0;
        while (rand > 0) {
            rand -= nums[index];
            index++;
        }
        return index;
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
                while (index == node->getId()) {
                    index = selectNode();
                }
                // Add an edge between the new node and the selected node.
                addEdge(node, nodes_[index]);
            }
        }
    }

    template <>
    void Graph<GNode>::dijkstra(uint64_t src, uint64_t dst) {
        // Initialize the distance of each node to infinity.
        std::vector<uint64_t> distance(nodes_.size(),
                                       std::numeric_limits<uint64_t>::max());
        // Initialize the previous node of each node to itself.
        std::vector<uint64_t> previous(nodes_.size(),
                                       std::numeric_limits<uint64_t>::max());
        // Initialize the set of visited nodes to empty.
        std::vector<bool> visited(nodes_.size(), false);
        // Set the distance of the source node to 0.
        distance[src] = 0;
        // While the set of visited nodes is not equal to the set of all nodes.
        while (std::find(visited.begin(), visited.end(), false) !=
               visited.end()) {
            // Select the unvisited node with the smallest distance.
            uint64_t min = std::numeric_limits<uint64_t>::max();
            uint64_t index = 0;
            for (uint64_t i = 0; i < nodes_.size(); i++) {
                if (!visited[i] && distance[i] < min) {
                    min = distance[i];
                    index = i;
                }
            }
            // Mark the selected node as visited.
            visited[index] = true;
            // For each unvisited neighbor of the selected node.
            auto node = nodes_[index];
            while (node != nullptr) {
                if (!visited[node->getId()]) {
                    // Calculate the distance from the source node to the
                    // neighbor through the selected node.
                    uint64_t new_distance = distance[index] + 1;
                    // If the new distance is smaller than the current distance
                    // of the neighbor.
                    if (new_distance < distance[node->getId()]) {
                        // Update the distance of the neighbor.
                        distance[node->getId()] = new_distance;
                        // Update the previous node of the neighbor.
                        previous[node->getId()] = index;
                    }
                }
                node = node->next_;
            }
        }
        // Print the shortest path from the source node to the destination node.
        std::cout << "The shortest path from " << src << " to " << dst
                  << " is: ";
        uint64_t node = dst;
        while (node != src) {
            std::cout << node << " <- ";
            node = previous[node];
        }
        std::cout << src << std::endl;
    }
}  // namespace graph