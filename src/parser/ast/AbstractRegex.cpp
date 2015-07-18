#include "AbstractRegex.h"
#include "../../throwable/runtime/IllegalStateException.h"

using namespace std;
using namespace regexsf;

AbstractRegex::AbstractRegex() : Printable() {
}

AbstractRegex::~AbstractRegex() {
    for (std::vector<Multi*>::iterator it = multi.begin(); it != multi.end(); ++it) {
        RX_DELETE(*it);
    }
    multi.clear();
}

bool AbstractRegex::hasMulti() const {
    return (! multi.empty());
}

void AbstractRegex::pushMulti(Multi* p) {
    // RX_DEBUG(p);
    // RX_DEBUG(*p);
    multi.push_back(p);
}

TString AbstractRegex::asString_multi() const {
    TStringStream ss;
    for (std::vector<Multi*>::const_iterator it = multi.begin(); it != multi.end(); ++it) {
        ss << (**it);
    }
    return ss.str();
}

