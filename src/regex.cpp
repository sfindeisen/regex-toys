#include <iostream>

#include "cfa/State.h"
#include "parser/Parser.h"
#include "throwable/RXAbstractThrowable.h"

using namespace std;
using namespace regexsf;

int main() {
    try {
        std::string rxs;
        cin >> rxs;
        RX_DEBUG("got RE: " << rxs);

        Parser p;
        AbstractRegex* rx = p.parse(rxs);
        RX_DEBUG("parsed RE: " << (*rx));

        RX_DELETE(rx);
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
