#include "interval.h"

std::ostream& operator<<(std::ostream &out, const Interval &interval)
{
    out << "(" << interval.begin() << ", " << interval.end() << ")" << std::endl;
    return out;
}