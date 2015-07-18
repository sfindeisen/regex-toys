#include "Node.h"

using namespace std;
using namespace regexsf;

Node::Node()
    : Printable(), counterId(0), incNode(0), exitNode(0), isAccept(false)
{
    alphaTransitions.fill(0);
}

Node::~Node() {
}

TString Node::asString() const {
    TStringStream ss;
    ss << "Node: CTR(" << counterId << "; inc=" << incNode << " exit=" << exitNode << ") ACC=" << isAccept;

    for (int i=0; i < AlphaLen; ++i) {
        if (alphaTransitions.at(i))
            ss << endl << " " << idx2alpha(i) << "/" << i << " -> " << alphaTransitions.at(i);
    }

    if (! nilTransitions.empty()) {
        ss << endl << "  nil:";
        for (std::vector<TNodeIdx>::const_iterator it = nilTransitions.begin(); it != nilTransitions.end(); ++it)
            ss << " " << (*it);
    }

    return ss.str();
}
