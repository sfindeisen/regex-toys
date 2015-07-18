#include <iostream>
#include <boost/regex.hpp>

#include "misc/Utils.h"

using namespace std;
using namespace boost;

int main() {
    try {
        std::string rxs, ms;
        getline(cin, ms);
        int k = regexsf::Utils::parseUInt(ms);
        getline(cin, rxs);
        regex rx(rxs);

        for (int i=0; i < k; ++i) {
            getline(cin, ms);
            cout << (regex_match(ms, rx) ? "YES" : "NO") << endl;
        }
    } catch (std::exception& e) {
        cerr << "Top level: " << (e.what());
    } catch (...) {
        cerr << "Top level: unknown exception caught!";
    }

    return 0;
}
