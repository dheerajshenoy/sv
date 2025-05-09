#include "sv.hpp"

int main(int argc, char *argv[])
{
    dj::string_view sv("HELLO dd WORLD dd ");

    auto split = sv.split(" dd ");
    for (const auto &s : split)
        std::cout << s << "\n";
    return 0;
}
