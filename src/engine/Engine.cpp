#include "Engine.h"
#include "../parser/ast/RegexChar.h"
#include "../parser/ast/RegexChoice.h"
#include "../parser/ast/RegexSequence.h"
#include "../throwable/runtime/IllegalArgumentException.h"
#include "../throwable/runtime/IllegalStateException.h"

using namespace std;
using namespace regexsf;

TState* Engine::initState(const CFA& cfa, const TNodeIdx& ni) const {
    const Node& node = cfa.nodes[ni];
    if (node.counterId) {
        return new TState(ni, cfa.counters.size());
    } else {
        return new TState(ni);
    }
}

void Engine::followNilTransitions(const CFA& cfa, const TState *s, const Node& node, TQueue& queue) const {
    if (node.counterId) {
        const Counter& ctr = cfa.counters[node.counterId-1];   // counter
        const unsigned int v = s->counters[s->cc-1];           // current value

        // Follow increment edge
        if ((! ctr.hasUpperBound()) || (v < ctr.hi)) {
            TState* t = copyState(cfa, *s);
            t->node = node.incNode;
            t->counters[t->cc-1]++;
            queue.push_back(t);
            RX_DEBUG("  Follow  inc: " << asString(*t));
        }

        // Follow exit edge
        if (ctr.lo <= v) {
            TState* t = copyState(cfa, *s);
            t->node = node.exitNode;
            t->counters[--(t->cc)]=0;
            queue.push_back(t);
            RX_DEBUG("  Follow exit: " << asString(*t));
        }
    }

    // Follow counter-agnostic nil transitions
    for (std::vector<TNodeIdx>::const_iterator it = node.nilTransitions.begin(); it != node.nilTransitions.end(); ++it) {
        TState* t = copyState(cfa, *s);
        t->node = *it;
        queue.push_back(t);
        RX_DEBUG("  Follow  nil: " << asString(*t));
    }
}

/**
 * queue: current queue
 * q2 : new queue (to contain states reachable by alpha transitions)
 * alphaIdx : current char
 */
void Engine::bfs(const CFA& cfa, TQueue& queue, TQueue& q2, const TAlphaIdx& alphaIdx) const {
    for (unsigned int j=0; j < queue.size(); ++j) {
        TState* s = queue[j];
        const Node& node = cfa.nodes[s->node-1];
        RX_DEBUG("j=" << j << ": " << asString(*s));

        // Follow nil transitions
        followNilTransitions(cfa, s, node, queue);

        // Follow the alpha transition
        const TNodeIdx& nx = node.alphaTransitions[alphaIdx];
        if (nx) {
            TState* t = copyState(cfa, *s);
            t->node = nx;
            q2.push_back(t);
            RX_DEBUG("  Follow char: " << asString(*t));
        }
    }
}

/**
 * queue: current queue
 */
bool Engine::checkAccept(const CFA& cfa, TQueue& queue) const {
    for (unsigned int j=0; j < queue.size(); ++j) {
        TState* s = queue[j];
        RX_DEBUG("(A) j=" << j << ": " << asString(*s));
        const Node& node = cfa.nodes[s->node-1];

        if (node.isAccept)
            return true;

        // Follow nil transitions
        followNilTransitions(cfa, s, node, queue);
    }

    return false;
}
inline void Engine::clearQueue(TQueue& q) const {
    for (unsigned int j=0; j < q.size(); ++j)
        delete q[j];
    q.clear();
}

bool Engine::checkMatch(const CFA& cfa, const TString& z) const {
    const int ZLen = z.length();
    TQueue queue;
    TQueue q2;
    queue.push_back(initState(cfa, cfa.startNode));

    for (int i=0; i < ZLen; ++i) {
        const char c = z[i];
        TAlphaIdx ca = alpha2idx(c);
        RX_DEBUG("i=" << i << ": " << c << "/" << ca);

        // bfs from states stored in queue
        bfs(cfa, queue, q2, ca);
        // q2 now contains states reached by alpha transitions

        // replace queue with q2
        queue.swap(q2);
        clearQueue(q2);

        if (queue.empty()) {
            // unable to consume this char
            RX_DEBUG("fail early");
            clearQueue(queue);
            return false;
        }
    }

    // all input is now consumed, follow remaining nil transitions
    bool res = checkAccept(cfa, queue);
    clearQueue(queue);
    return res;
}

bool Engine::match(const CFA& cfa, const TString& s) const {
    const int SLen = s.length();

    for (int i=0; i < SLen; ++i) {
        // TODO what if not ASCII?...
        if (! ((('A' <= s[i]) && (s[i] <= 'Z')) || (('a' <= s[i]) && (s[i] <= 'z'))))
            RX_THROW_STREAM(IllegalArgumentException, "illegal character at position " << i << ": " << ((int) s[i]));
    }

    return checkMatch(cfa, s);
}


TString Engine::asString(const TState& t) const {
    TStringStream ss;
    ss << "St: " << t.node;
    if (t.cc) {
        ss << " " << t.cc << " ctrs:";
        for (unsigned int i=0; i < t.cc; ++i) {
            ss << " " << t.counters[i];
        }
    }
    return ss.str();
}
