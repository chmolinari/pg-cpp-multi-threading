#include <cstdlib>

#include <boost/log/trivial.hpp>

int main()
{
    BOOST_LOG_TRIVIAL(info) << "This is a test.\n";
    return EXIT_SUCCESS;
}
