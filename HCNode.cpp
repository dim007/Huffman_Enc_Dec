#include "HCNode.hpp"
#include <queue>

HCNode::~HCNode() {
}

bool HCNode::operator<(HCNode const& other) {
	if(this->count != other.count) {
		return count > other.count;
	} else {
		return this->symbol < other.symbol;
	}
}

//bool HCNode::comp(HCNode* one, HCNode* other) {
	//return one->count == other->count;
//}
