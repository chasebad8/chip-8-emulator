#include <iostream>
#include "cpu.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

void log_file_init()
{
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("[main] [%^%l%$] %v");

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/main.log", true);
        file_sink->set_level(spdlog::level::trace);

        spdlog::sinks_init_list sink_list = { file_sink, console_sink };

        spdlog::logger logger("main", sink_list.begin(), sink_list.end());
        logger.set_level(spdlog::level::debug);

        // or you can even set multi_sink logger as default logger
        spdlog::set_default_logger(std::make_shared<spdlog::logger>("main", spdlog::sinks_init_list({console_sink, file_sink})));
}

int main()
{
   log_file_init();
   spdlog::info("Booting up Chip-8");

   CPU cpu;
   cpu.decode_execute();

   return 0;
}