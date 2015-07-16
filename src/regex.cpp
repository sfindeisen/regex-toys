#include "common.h"

using namespace regexsf;

int main() {
    try {
        RX_INFO("Program start");
        MemoryManager::printMemoryInfo();
        RX_INFO("Program complete!");
    } catch (std::exception& e) {
        RX_ERROR("Top level: " << (e.what()));
    } catch (...) {
        RX_ERROR("Top level: unknown exception caught!");
    }

    return 0;
}
