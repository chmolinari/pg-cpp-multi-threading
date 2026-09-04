#include "log_definitions.hpp"

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace cm::pg::cpp::mt::logging
{
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
