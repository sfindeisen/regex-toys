#include "Engine.h"

using namespace regexsf;

Engine::Engine(const AbstractRegex *regex) : cfa(nullptr) {
    cfa = buildCFA(regex);
}

Engine::~Engine() {
    if (nullptr != cfa) {
        RX_DELETE(cfa);
    }
}

CFA* Engine::buildCFA(const AbstractRegex *regex) const {
    // TODO
    return nullptr;
}

TString Engine::asString() const {
    TStringStream ss;
    ss << "Engine";
    return ss.str();
}

