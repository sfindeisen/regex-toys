#include <iostream>

#include "misc/Utils.h"
#include "engine/CFABuilder.h"
#include "engine/Engine.h"
#include "parser/Parser.h"
#include "throwable/RXAbstractThrowable.h"

using namespace std;
using namespace regexsf;

int main() {
    try {
        std::string rxs, ms;
        getline(cin, ms);
        int k = Utils::parseUInt(ms);
        RX_DEBUG("Number of test cases: " << k);
        getline(cin, rxs);
        RX_DEBUG("got RE: " << rxs << "#");

        Parser p;
        AbstractRegex *rx = p.parse(rxs);
        RX_DEBUG("parsing done.");
        RX_INFO("parsed RE: " << (*rx));

        CFA *cfa = CFABuilder().compile(rx);
        RX_INFO("compiled RE: " << (*cfa));
        RX_DELETE(rx);      // it is safe to delete this regex tree now

        for (int i=0; i < k; ++i) {
            getline(cin, ms);
            RX_DEBUG("check: " << ms << "#");
            cout << (Engine().match(*cfa, ms) ? "YES" : "NO") << endl;
        }

        RX_DELETE(cfa);
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
