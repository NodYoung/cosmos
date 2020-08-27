

#include "botsys_logger.h"


std::ostream& operator<<(std::ostream& oss, const std::vector<double>& vals) {
    for (size_t i = 0; i < vals.size(); i++) {
        oss << vals[i];
        if (i + 1 < vals.size()) {
            oss << ", ";
        }
    }
    return oss;
}

namespace botsys {


Logger::MessageWrapper::MessageWrapper(const MessageWrapper& r)
        : logger(r.logger) {
}

Logger::MessageWrapper::MessageWrapper(const std::string& e, Logger& r, LoggerLevel level)
        : logger(r) {
    //添加当前时间信息。
    std::tm tm = {0};
    auto tp = std::chrono::system_clock::now() + std::chrono::hours(8);
    auto tt = std::chrono::system_clock::to_time_t(tp);

#ifdef WIN32
    tm = *gmtime(&tt);
#else
    gmtime_r(&tt, &tm);
#endif

    std::chrono::duration<double> sec = tp - std::chrono::system_clock::from_time_t(tt) +
                                        std::chrono::seconds(tm.tm_sec);
    double secDisp;
    secDisp = sec.count();

    oss << "[";
    oss << std::setw(5) << toString(level);
    oss << "] ";


    oss << tm.tm_year + 1900 << "-"
        << std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << "-"
        << std::setw(2) << tm.tm_mday << " "
        << std::setw(2) << tm.tm_hour << ":"
        << std::setw(2) << tm.tm_min << ":"
        << std::fixed << std::setprecision(3) << std::setw(6) << secDisp << " "
        << std::setfill(' ');

    if (e.size()) {
        oss << "[";
        oss << std::setw(logger.prefixWidth()) << e;
        oss << "] ";
    }
}

Logger::MessageWrapper::~MessageWrapper() {
    auto strfinal = oss.str();
    if (strfinal.size()) {
        if (strfinal.at(strfinal.size() - 1) != '\n') {
            strfinal.push_back('\n');
        }
    }
    logger.append(strfinal);
}

void Logger::MessageWrapper::endl() {
    oss << std::endl;
}


Logger::Logger() {
    m_log_to_cout = false;
    m_cache_log_message = true;
    m_prefix_width = 12;
}

void Logger::append(const std::string& message) {
    std::map<void*, std::function<void(const std::string&)> > obs;
    m_res_mutex.lock();
    obs = m_observers;

    if (m_cache_log_message)
        m_logs.push_back(message);

    if (m_append_filter)
        m_append_filter(message);

    if (m_log_to_cout) {
        std::cout << message;
    }
    m_res_mutex.unlock();

    for (auto& ob : obs) {
        ob.second(message);
    }
}

void Logger::setAppendFilter(std::function<void(const std::string& message)> filter) {
    if (filter) {
        m_append_filter = filter;
        for (auto& iter : m_logs) {
            m_append_filter(iter);
        }
    } else {
        m_append_filter = nullptr;
    }
}

Logger& Logger::instance() {
    static Logger logger;
    static bool first_init = true;
    if (first_init) {
        first_init = false;
        logger.logToCout(true);
        logger.m_prefix_width = 12;
        logger.m_cache_log_message = true;
    }
    return logger;
}

Logger::MessageWrapper Logger::message(const std::string& module_, LoggerLevel level) {
    return MessageWrapper(module_, *this, level);
}

Logger::MessageWrapper Logger::error(const std::string& module_) {
    return message(module_, LoggerLevel::Error);
}

Logger::MessageWrapper Logger::fatal(const std::string& module_) {
    return message(module_, LoggerLevel::Fatal);
}

Logger::MessageWrapper Logger::warning(const std::string& module_) {
    return message(module_, LoggerLevel::Warning);
}

Logger::MessageWrapper Logger::notice(const std::string& module_) {
    return message(module_, LoggerLevel::Notice);
}

Logger::MessageWrapper Logger::info(const std::string& module_) {
    return message(module_, LoggerLevel::Info);
}


Logger::MessageWrapper Logger::debug(const std::string& module_) {
    return message(module_, LoggerLevel::Debug);
}

void Logger::setCurrentInstanceName(const std::string& s) {
    m_current_instance_name = s;
}

void Logger::addFilter(void* obj, std::function<void(const std::string& message)> filter) {
    if (obj && filter) {
        m_res_mutex.lock();
        m_observers[obj] = filter;
        m_res_mutex.unlock();

        for (auto& iter : m_logs) {
            filter(iter);
        }
    }
}

void Logger::clrFilter(void* obj) {
    std::lock_guard<std::mutex> lockctx(m_res_mutex);
    m_observers.erase(obj);
}


std::string toString(LoggerLevel level) {
    switch (level) {
    case botsys::LoggerLevel::Debug: return "DEBUG";
        break;
    case botsys::LoggerLevel::Info: return "INFO";
        break;
    case botsys::LoggerLevel::Notice: return "NOTIC";
        break;
    case botsys::LoggerLevel::Warning:return "WARN";
        break;
    case botsys::LoggerLevel::Error: return "ERROR";
        break;
    case botsys::LoggerLevel::Fatal: return "FATAL";
        break;
    }
    return std::string();
}
}

botsys::Logger::MessageWrapper& endl(botsys::Logger::MessageWrapper& mwp) {
    mwp.endl();
    return mwp;
}
