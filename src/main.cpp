#include <cstdlib>

#include "../include/log_definitions.hpp"

using sl   = cm::pg::cpp::mt::logging::SeverityLevel;
using glog = cm::pg::cpp::mt::logging::glog;

int main()
{
    cm::pg::cpp::mt::logging::Logger const logging_guard;
    BOOST_LOG_SEV(glog::get(), sl::trace) << "Program started.";
    BOOST_LOG_SEV(glog::get(), sl::trace) << "Program finished.";
    return EXIT_SUCCESS;
}
