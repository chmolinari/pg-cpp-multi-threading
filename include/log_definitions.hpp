#ifndef MULTI_THREADING_LOG_DEFINITIONS_HPP
#define MULTI_THREADING_LOG_DEFINITIONS_HPP

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace cm::pg::cpp::mt::logging
{
    enum class SeverityLevel
    {
        trace   = -1,
        debug   = -2,
        info    = 0,
        warning = 1,
        error   = 2,
        fatal   = 3
    };

    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(glog, boost::log::sources::severity_logger_mt<cm::pg::cpp::mt::logging::
                                           SeverityLevel>);
}

#endif //MULTI_THREADING_LOG_DEFINITIONS_HPP
