#include "gnode.hpp"
#include <iostream>

namespace graph {
    uint64_t GNode::next_id_ = 0;

    void GNode::connectNode(std::shared_ptr<GNode> node) {
        // next_.push_back(node->id_);
        // node->next_.push_back(id_);
        next_.insert(node->id_);
        node->next_.insert(id_);
    }

    uint64_t GNode::getEdgeNums() { return next_.size(); }

    bool GNode::existConnection(uint64_t id) {
        for (auto next : next_) {
            if (next == id) {
                return true;
            }
        }
        return false;
    }

}  // namespace graph