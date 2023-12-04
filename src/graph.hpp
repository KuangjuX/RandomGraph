#include <memory>
#include <vector>

namespace graph {
    template <class Node>
    class Graph {
       public:
        std::vector<std::shared_ptr<Node> > nodes_;

        Graph() {}
        Graph(std::vector<std::shared_ptr<Node> > nodes) : nodes_(nodes) {}

        void addNode(std::shared_ptr<Node> node);

        void addEdge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst);
        void addNodeAndEdge(std::shared_ptr<Node> src,
                            std::shared_ptr<Node> dst);

        void buildRing(int m);

        uint64_t selectNode();

        void generateRandomGraph(int m, int t);

        void dijkstra(uint64_t src, uint64_t dst);
    };
}  // namespace graph