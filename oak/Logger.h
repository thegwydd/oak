#pragma once

#include <map>

#define LOGGER_NAMESPACE    oak

#define DEFAULT_LOGGER      LOGGER_NAMESPACE::Logger::Get().GetLog("main")
#define SPECIFIC_LOGGER(x)  LOGGER_NAMESPACE::Logger::Get().GetLog(x)

#define DEFAULT_NUM_SLOTS   8192
#define DEFAULT
#ifdef _MSC_VER
#define TRACE_TRC(...)              DEFAULT_LOGGER->trace(__VA_ARGS__)
#define TRACE_DBG(...)              DEFAULT_LOGGER->debug(__VA_ARGS__)
#define TRACE_NFO(...)              DEFAULT_LOGGER->info(__VA_ARGS__)
#define TRACE_WRN(...)              DEFAULT_LOGGER->warn(__VA_ARGS__)
#define TRACE_ERR(...)              DEFAULT_LOGGER->error(__VA_ARGS__)
#define TRACE_CRT(...)              DEFAULT_LOGGER->critical(__VA_ARGS__)

#define TRACE_S_TRC(ln, ...)        SPECIFIC_LOGGER(ln)->trace(__VA_ARGS__)
#define TRACE_S_DBG(ln, ...)        SPECIFIC_LOGGER(ln)->debug(__VA_ARGS__)
#define TRACE_S_NFO(ln, ...)        SPECIFIC_LOGGER(ln)->info(__VA_ARGS__)
#define TRACE_S_WRN(ln, ...)        SPECIFIC_LOGGER(ln)->warn(__VA_ARGS__)
#define TRACE_S_ERR(ln, ...)        SPECIFIC_LOGGER(ln)->error(__VA_ARGS__)
#define TRACE_S_CRT(ln, ...)        SPECIFIC_LOGGER(ln)->critical(__VA_ARGS__)

#else
#define TRACE_TRC(args...)          DEFAULT_LOGGER->trace(## args)
#define TRACE_DBG(args...)          DEFAULT_LOGGER->debug(## args)
#define TRACE_NFO(args...)          DEFAULT_LOGGER->info(## args)
#define TRACE_WRN(args...)          DEFAULT_LOGGER->warn(## args)
#define TRACE_ERR(args...)          DEFAULT_LOGGER->error(## args)
#define TRACE_CRT(args...)          DEFAULT_LOGGER->critical(## args)

#define TRACE_S_TRC(ln, args...)    SPECIFIC_LOGGER(ln)->trace(## args)
#define TRACE_S_DBG(ln, args...)    SPECIFIC_LOGGER(ln)->debug(## args)
#define TRACE_S_NFO(ln, args...)    SPECIFIC_LOGGER(ln)->info(## args)
#define TRACE_S_WRN(ln, args...)    SPECIFIC_LOGGER(ln)->warn(## args)
#define TRACE_S_ERR(ln, args...)    SPECIFIC_LOGGER(ln)->error(## args)
#define TRACE_S_CRT(ln, args...)    SPECIFIC_LOGGER(ln)->critical(## args)
#endif

namespace oak
    {
    using log = std::shared_ptr<spdlog::logger>;

    //////////////////////////////////////////////////////////////////////////
    class Logger
        {
        public:
            Logger();
            ~Logger();

        public:
            static Logger & Get();
            static log GetLog(const std::string & name);

        private:
            log GetLogInternal(const std::string & name);

        private:
            std::map<std::string, log> m_loggers;

        };



    }
