// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef SPDLOG_HEADER_ONLY
#include "spdlog/sinks/wincolor_sink.h"
#endif

#include "spdlog/common.h"

namespace spdlog {
namespace sinks {

template<typename TargetStream, typename ConsoleMutex>
SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::wincolor_sink(color_mode mode)
    : out_handle_(TargetStream::handle())
    , mutex_(ConsoleMutex::mutex())
{
    set_color_mode(mode);
    colors_[level::trace] = WHITE;
    colors_[level::debug] = CYAN;
    colors_[level::info] = GREEN;
    colors_[level::warn] = YELLOW | BOLD;
    colors_[level::err] = RED | BOLD;                         // red bold
    colors_[level::critical] = BACKGROUND_RED | WHITE | BOLD; // white bold on red background
    colors_[level::off] = 0;
}

template<typename TargetStream, typename ConsoleMutex>
SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::~wincolor_sink()
{
    this->flush();
}

// change the color for the given level
template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::set_color(level::level_enum level, WORD color)
{
    std::lock_guard<mutex_t> lock(mutex_);
    colors_[level] = color;
}

template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::log(const details::log_msg &msg)
{
    std::lock_guard<mutex_t> lock(mutex_);
    fmt::memory_buffer formatted;
    formatter_->format(msg, formatted);
    if (should_do_colors_ && msg.color_range_end > msg.color_range_start)
    {
        // before color range
        print_range_(formatted, 0, msg.color_range_start);

        // in color range
        auto orig_attribs = set_console_attribs(colors_[msg.level]);
        print_range_(formatted, msg.color_range_start, msg.color_range_end);
        ::SetConsoleTextAttribute(out_handle_,
            orig_attribs); // reset to orig colors
                           // after color range
        print_range_(formatted, msg.color_range_end, formatted.size());
    }
    else // print without colors if color range is invalid (or color is disabled)
    {
        print_range_(formatted, 0, formatted.size());
    }
}

template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::flush()
{
    // windows console always flushed?
}

template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::set_pattern(const std::string &pattern)
{
    std::lock_guard<mutex_t> lock(mutex_);
    formatter_ = std::unique_ptr<spdlog::formatter>(new pattern_formatter(pattern));
}

template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter)
{
    std::lock_guard<mutex_t> lock(mutex_);
    formatter_ = std::move(sink_formatter);
}

template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::set_color_mode(color_mode mode)
{
    switch (mode)
    {
    case color_mode::always:
    case color_mode::automatic:
        should_do_colors_ = true;
        break;
    case color_mode::never:
        should_do_colors_ = false;
        break;
    default:
        should_do_colors_ = true;
    }
}

// set color and return the orig console attributes (for resetting later)
template<typename TargetStream, typename ConsoleMutex>
WORD SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::set_console_attribs(WORD attribs)
{
    CONSOLE_SCREEN_BUFFER_INFO orig_buffer_info;
    ::GetConsoleScreenBufferInfo(out_handle_, &orig_buffer_info);
    WORD back_color = orig_buffer_info.wAttributes;
    // retrieve the current background color
    back_color &= static_cast<WORD>(~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
    // keep the background color unchanged
    ::SetConsoleTextAttribute(out_handle_, attribs | back_color);
    return orig_buffer_info.wAttributes; // return orig attribs
}

// print a range of formatted message to console
template<typename TargetStream, typename ConsoleMutex>
void SPDLOG_INLINE wincolor_sink<TargetStream, ConsoleMutex>::print_range_(const fmt::memory_buffer &formatted, size_t start, size_t end)
{
    auto size = static_cast<DWORD>(end - start);
    ::WriteConsoleA(out_handle_, formatted.data() + start, size, nullptr, nullptr);
}

} // namespace sinks
} // namespace spdlog