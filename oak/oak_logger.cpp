#include "stdafx.h"
#include "oak_logger.h"

#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/sinks/ansicolor_sink.h>

#include <memory>

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    logger::logger()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    logger::~logger()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    logger & logger::get()
        {
        static logger * m_instance;
        if (m_instance == nullptr)
            m_instance = new logger;
        return *m_instance;
        }

    //////////////////////////////////////////////////////////////////////////
    log logger::get_log(const std::string & name)
        {
        return logger::get().get_log_internal(name);
        }

    //////////////////////////////////////////////////////////////////////////
    log logger::get_log_internal(const std::string & name)
        {
        log ret = m_loggers[name];
        if (ret == nullptr)
            {
            std::vector<spdlog::sink_ptr> sinks;
            sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
            sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());

            std::shared_ptr<spdlog::logger> l = std::make_shared<spdlog::logger>(name, std::begin(sinks), std::end(sinks));
            m_loggers[name] = ret = l;
            }
        return ret;
        }




    }
