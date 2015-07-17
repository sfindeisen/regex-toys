#include "AbstractRegex.h"

using namespace std;
using namespace regexsf;

AbstractRegex::AbstractRegex() : multi(nullptr) {
}

AbstractRegex::~AbstractRegex() {
    if (nullptr != multi) {
        RX_DELETE(multi);
    }
}

bool AbstractRegex::hasMulti() const {
    return (nullptr != multi);
}

void AbstractRegex::setMulti(Multi* p) {
    if (nullptr != multi) {
        RX_DELETE(multi);
    }

    multi = p;
}

TString AbstractRegex::asString() const {
    return asString("");
}

TString AbstractRegex::asString_other(const AbstractRegex& other, const TString& indent) const {
    return other.asString(indent);
}

