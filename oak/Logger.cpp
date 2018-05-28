#include "stdafx.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/sinks/ansicolor_sink.h>

#include <memory>

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    Logger::Logger()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    Logger::~Logger()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    Logger & Logger::Get()
        {
        static Logger * m_instance;
        if (m_instance == nullptr)
            m_instance = new Logger;
        return *m_instance;
        }

    //////////////////////////////////////////////////////////////////////////
    log Logger::GetLog(const std::string & name)
        {
        return Logger::Get().GetLogInternal(name);
        }

    //////////////////////////////////////////////////////////////////////////
    log Logger::GetLogInternal(const std::string & name)
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
