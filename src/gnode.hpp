#include <memory>

namespace graph {
    class GNode {
       public:
        GNode() : id_(next_id_++) { next_ = nullptr; }
        GNode(uint64_t id) : id_(id) { next_ = nullptr; }
        uint64_t id_;
        std::shared_ptr<GNode> next_;
        uint64_t getId() { return id_; }
        void connectNode(std::shared_ptr<GNode> node);
        uint64_t getEdgeNums();

       private:
        static uint64_t next_id_;
        void addNext(std::shared_ptr<GNode> next);
    };
}  // namespace graph