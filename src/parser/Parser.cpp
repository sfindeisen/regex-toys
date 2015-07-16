#include "Parser.h"
#include "../throwable/error/NotImplementedError.h"

using namespace std;
using namespace regexsf;

Parser::Parser() {
}

Parser::~Parser() {
}

AbstractRegex* Parser::parse(const TString& s) const {
    // TODO implement this!
    RX_THROW(NotImplementedError);
}

