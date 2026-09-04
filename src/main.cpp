#include <cstdlib>

#include "../include/log_definitions.hpp"

using sl   = cm::pg::cpp::mt::logging::SeverityLevel;
using glog = cm::pg::cpp::mt::logging::glog;

int main()
{
    BOOST_LOG_SEV(glog::get(), sl::fatal) << "Hello, World!";
    return EXIT_SUCCESS;
}
