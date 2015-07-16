#include <iostream>

#include "automaton/State.h"
#include "parser/Parser.h"
#include "throwable/RXAbstractThrowable.h"

using namespace std;
using namespace regexsf;

int main() {
    try {
        std::string rx;
        cin >> rx;
        RX_DEBUG("got RE: " << rx);

        Parser p;
        p.parse(rx);

    } catch (regexsf::RXAbstractThrowable& e) {
        RX_ERROR(e);
    } catch (std::exception& e) {
        RX_ERROR("Top level: " << (e.what()));
    } catch (...) {
        RX_ERROR("Top level: unknown exception caught!");
    }

    MemoryManager::printMemoryInfo();
    RX_INFO("The end.");
    return 0;
}
