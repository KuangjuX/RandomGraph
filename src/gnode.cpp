#include "gnode.hpp"

namespace graph {
    uint64_t GNode::next_id_ = 0;

    void GNode::connectNode(std::shared_ptr<GNode> node) {
        while (next_ != nullptr) {
            next_ = next_->next_;
        }
        next_ = node;
    }

    void GNode::addNext(std::shared_ptr<GNode> next) { next_ = next; }

    uint64_t GNode::getEdgeNums() {
        uint64_t nums = 0;
        auto node = next_;
        while (node != nullptr) {
            nums++;
            node = node->next_;
        }
        return nums;
    }

}  // namespace graph