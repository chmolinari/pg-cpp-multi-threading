#ifndef MULTI_THREADING_LOG_DEFINITIONS_HPP
#define MULTI_THREADING_LOG_DEFINITIONS_HPP

#include <ostream>

#include <boost/log/core.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
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

    std::ostream& operator<<(std::ostream& out_stream, SeverityLevel severity_level);

    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(glog, boost::log::sources::severity_logger_mt<cm::pg::cpp::mt::logging::
                                           SeverityLevel>);

    using sink_t = boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend>;

    class Logger
    {
        static void set_console_sink();

    public:
        Logger();
        ~Logger();
    };
}

#endif //MULTI_THREADING_LOG_DEFINITIONS_HPP
