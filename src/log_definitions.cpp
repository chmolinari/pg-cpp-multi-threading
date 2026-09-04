#include "log_definitions.hpp"

#include <iomanip>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace cm::pg::cpp::mt::logging
{
    std::ostream& operator<<(std::ostream& out_stream, SeverityLevel const severity_level)
    {
        switch (severity_level)
        {
        case SeverityLevel::trace:
            return out_stream << "TRC";
        case SeverityLevel::debug:
            return out_stream << "DBG";
        case SeverityLevel::info:
            return out_stream << "INF";
        case SeverityLevel::warning:
            return out_stream << "WRN";
        case SeverityLevel::error:
            return out_stream << "ERR";
        case SeverityLevel::fatal:
            return out_stream << "FTL";
        }
        return out_stream << static_cast<int>(severity_level);
    }

    namespace
    {
        void init_logging()
        {
            auto const logger{boost::log::core::get()};
            boost::log::add_common_attributes();

            /* === SINKS === */

            // Console sink.
            const auto backend{boost::make_shared<boost::log::sinks::text_ostream_backend>()};
            backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
            backend->auto_flush(true);
            using sync_t = boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend>;
            const auto sink{boost::make_shared<sync_t>(backend)};
            sink->set_filter(boost::log::expressions::attr<SeverityLevel>("Severity") >= SeverityLevel::trace);
            sink->set_formatter(
                                boost::log::expressions::stream
                                << boost::log::expressions::format_date_time<boost::posix_time::ptime>(
                                 "TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                                << " [" << boost::log::expressions::attr<SeverityLevel>("Severity") << ", "
                                << "P: " << boost::log::expressions::attr<
                                    boost::log::attributes::current_process_id::value_type>("ProcessID") << ", "
                                << "T: " << boost::log::expressions::attr<
                                    boost::log::attributes::current_thread_id::value_type>("ThreadID") << "] "
                                << boost::log::expressions::smessage);
            logger->add_sink(sink);
            /* === END OF SINKS === */
        }
    }

    Logger::Logger()
    {
        init_logging();
    }

    Logger::~Logger()
    {
        boost::log::core::get()->flush();
    }
}
