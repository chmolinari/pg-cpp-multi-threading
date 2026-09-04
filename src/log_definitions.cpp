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

    void Logger::set_console_sink()
    {
        auto get_backend = [](std::ostream& _destination) -> boost::shared_ptr<boost::log::sinks::text_ostream_backend>
        {
            const auto backend{boost::make_shared<boost::log::sinks::text_ostream_backend>()};
            backend->add_stream(boost::shared_ptr<std::ostream>(&_destination, boost::null_deleter()));
            backend->auto_flush(true);
            return backend;
        };

        auto get_frontend = [get_backend](std::ostream& destination)
        {
            auto sink{boost::make_shared<sink_t>(get_backend(destination))};
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
            return std::move(sink);
        };

        boost::log::add_common_attributes();
        auto const logger{boost::log::core::get()};

        // stdout.
        auto const stdout_sink{get_frontend(std::cout)};
        logger->add_sink(stdout_sink);
    }

    Logger::Logger()
    {
        set_console_sink();
    }

    Logger::~Logger()
    {
        boost::log::core::get()->flush();
    }
}
