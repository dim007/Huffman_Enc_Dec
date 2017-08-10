#include "HCTree.hpp"
#include <queue>

using namespace std;

HCTree::~HCTree() {
	deleteAll(root);
}

void HCTree::build(const vector<int>& freqs) {
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
	for(int i = 0; i < 256; i++) {
		if(freqs[i] == 0){
			continue;
		}
		leaves[i] = new HCNode(freqs[i], i);
		pq.push(leaves[i]);
	}
	while (pq.size()) {
		HCNode* c0 = NULL;
		HCNode* c1 = NULL;
		c0 = pq.top();
		pq.pop();
		if(!pq.empty()){
			c1 = pq.top();
			pq.pop();
		}
		else {
			this->root = c0;
			return;
		}

		HCNode* parent = new HCNode((c1->count + c0->count), c0->symbol, c1, c0);
		c1->p = parent;
		c0->p = parent;
		
		pq.push(parent);
	}
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
	HCNode* currNode = leaves[symbol];
	HCNode* parent = currNode->p;
	int counter = 0;
	int bits[8] = {-1,-1,-1,-1,-1,-1,-1,-1};

	while(parent != NULL){
		HCNode* pC1 = parent->c1;
		HCNode* pC0 = parent->c0;
		if(currNode->symbol == pC1->symbol) {
			bits[counter] = 1;
			counter++;
		}
		else if(currNode->symbol == pC0->symbol) {
			bits[counter] = 0;
			counter++;
		}
		else {
			cerr << "Error! Could not write bit!" << endl;
			return;
		}
		currNode = parent;
		parent = currNode->p;
	}
	for(int i = 0; i < counter; i++){
		out.writeBit(bits[counter-1 - i]);
	}
}


int HCTree::decode(BitInputStream& in) const {
	HCNode* currNode = root;
	int decodedBit;

	while(currNode->c0 != NULL && currNode->c1 != NULL) {

		decodedBit = in.readBit();
		if(decodedBit == 0) {
			currNode = currNode->c0;
		}
		else if(decodedBit == 1) {
			currNode = currNode->c1;
		}
		else {
			cerr << "Error in decode" << endl;
			return -1;
		}
	}
	return currNode->symbol;
}


