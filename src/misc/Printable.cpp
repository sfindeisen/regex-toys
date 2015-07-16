#include "Printable.h"

using namespace regexsf;

Printable::Printable() {
}

namespace regexsf {
    std::ostream& operator<<(std::ostream& stream, const regexsf::Printable& p) {
        return stream << (p.asString());
    }
};
