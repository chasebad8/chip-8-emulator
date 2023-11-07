#include <iostream>
#include "cpu.h"
#include "gpu.h"
#include "opcodes.h"

#define SPDLOG_DEBUG_ON

using namespace std;
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

void log_file_init()
{
   spdlog::set_level(spdlog::level::debug);

   auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
   console_sink->set_level(spdlog::level::debug);
   console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");

   auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/main.log", true);
   file_sink->set_level(spdlog::level::debug);
   file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");

   spdlog::sinks_init_list sink_list = { file_sink, console_sink };

   spdlog::logger logger("main", sink_list.begin(), sink_list.end());
   logger.set_level(spdlog::level::debug);

   auto global_logger = std::make_shared<spdlog::logger>("main", spdlog::sinks_init_list({console_sink, file_sink}));
   spdlog::register_logger(global_logger);
   spdlog::set_default_logger(global_logger);

   init_log_opcodes();
	init_log_gpu();
}

int main(int argc,char *argv[])
{
   /* Initialize the logging library */
   log_file_init();
   std::shared_ptr<spdlog::logger> logger = spdlog::get("main");

   logger->info("Booting up Chip-8 ...");

   if(argc != 2)
   {
      logger->error("No .ch8 ROM file path supplied");
   }
   /* Initialize the SDL2 Library and window */
	else if(gpu_init() == false)
	{
		gpu_shutdown();
	}
   else
   {
      CPU cpu(argv[1]);
      cpu.run();
      gpu_shutdown();
   }


   return 0;
}