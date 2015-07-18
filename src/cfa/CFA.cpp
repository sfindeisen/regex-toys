#include "CFA.h"

using namespace std;
using namespace regexsf;

CFA::CFA() : Printable() {
}

CFA::~CFA() {
}

Node& CFA::getNode(const TNodeIdx& i) {
    if ((1 <= i) && (i <= nodes.size()))
        return nodes.at(i-1);
    RX_THROW_STREAM(IllegalArgumentException, "index out of range: " << i);
}

void CFA::setStartNode(const TNodeIdx& i) {
    if ((1 <= i) && (i <= nodes.size()))
        startNode = i;
    else
        RX_THROW_STREAM(IllegalArgumentException, "index out of range: " << i);
}

TNodeIdx CFA::appendNode() {
    return appendNode(Node());
}

TNodeIdx CFA::appendNode(const Node& node) {
    nodes.push_back(node);
    return nodes.size();
}

TCounterIdx CFA::appendCounter(const Counter& ctr) {
    counters.push_back(ctr);
    return counters.size();
}

TString CFA::asString() const {
    TStringStream ss;
    ss << "CFA: " << nodes.size() << " nodes, " << counters.size() << " counters";

    for (unsigned int j=0; j < counters.size(); ++j)
        ss << endl << (1+j) << ": " << (counters.at(j));
    for (unsigned int j=0; j < nodes.size(); ++j)
        ss << endl << ((startNode == (1+j)) ? "S " : "") << (1+j) << ": " << (nodes.at(j));
    
    return ss.str();
}
