#include "Node.h"

using namespace std;
using namespace regexsf;

Node::Node() : Printable(), counterId(0), incNode(0), exitNode(0), isAccept(false) {
    alphaTransitions.fill(0);
}

Node::~Node() {
}

void Node::setAlphaTransition(const TAlpha& c, const TNodeIdx& i) {
    alphaTransitions[alpha2idx(c)] = i;
}

TString Node::asString() const {
    TStringStream ss;
    ss << "Node";
    return ss.str();
}