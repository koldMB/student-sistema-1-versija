#include <string>

using std::string;

bool isInteger(const string& s)
{
    if (s.empty()) return false;

    const int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidžia +/- ženklus

    for (size_t i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
}
