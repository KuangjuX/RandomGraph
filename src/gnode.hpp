#include <memory>
#include <set>

namespace graph {
    class GNode {
       public:
        uint64_t id_;
        std::set<uint64_t> next_;

        GNode() : id_(next_id_++) { next_ = std::set<uint64_t>(); }
        GNode(uint64_t id) : id_(id) { next_ = std::set<uint64_t>(); }
        uint64_t getId() { return id_; }
        void connectNode(std::shared_ptr<GNode> node);
        uint64_t getEdgeNums();
        bool existConnection(uint64_t id);

       private:
        static uint64_t next_id_;
        // void addNext(std::shared_ptr<GNode> next);
    };
}  // namespace graph