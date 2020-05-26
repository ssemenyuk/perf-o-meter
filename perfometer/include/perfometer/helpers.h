/* Copyright 2020 Volodymyr Nikolaichuk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#pragma once

#include <perfometer/perfometer.h>

namespace perfometer
{
    enum zero_length_work_policy
    {
        allow,
        skip
    };
    // work_logger expects const string as name

    template <zero_length_work_policy zero_length_policy>
    class work_logger
    {
    public:
        work_logger(const char name[])
        {
            m_start_time = get_time();
            m_name = name;
        }

        ~work_logger()
        {
            time end_time = get_time();

            if (zero_length_policy == zero_length_work_policy::allow ||
                m_start_time != end_time )
            {
                log_work(m_name, m_start_time, end_time);
            }
        }

    private:
        const char* m_name;
        time m_start_time;
    };
}

#if defined(__PRETTY_FUNCTION__)
#   define PERFOMETER_FUNCTION     __PRETTY_FUNCTION__
#else
#   define PERFOMETER_FUNCTION     __FUNCTION__
#endif

#define PERFOMETER_CONCAT(x, y)             x##y
#define PERFOMETER_CONCAT_WRAPPER(x, y)     PERFOMETER_CONCAT(x, y)

#define PERFOMETER_LOG_SCOPE(name)                                              \
        perfometer::work_logger<perfometer::zero_length_work_policy::skip>      \
            PERFOMETER_CONCAT_WRAPPER(func_logger, __LINE__)(name)
        
#define PERFOMETER_LOG_FUNCTION()           PERFOMETER_LOG_SCOPE(PERFOMETER_FUNCTION)

#define PERFOMETER_EVENT(name)              perfometer::log_event(name, perfometer::get_time())
