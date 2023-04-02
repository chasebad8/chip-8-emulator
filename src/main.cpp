#include <iostream>
#include "cpu.h"
#include "opcodes.h"
#include <SDL2/SDL.h>

#define SPDLOG_DEBUG_ON

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
}

int main()
{
   log_file_init();
   std::shared_ptr<spdlog::logger> logger = spdlog::get("main");
   logger->info("Booting up Chip-8 ...");

   if(SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      std::cout << "Failed to initialize the SDL2 library\n";
      return -1;
   }

   SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       680, 480,
                                       0);

   if(!window)
   {
      std::cout << "Failed to create window\n";
      return -1;
   }

   SDL_Surface *window_surface = SDL_GetWindowSurface(window);

   if(!window_surface)
   {
      std::cout << "Failed to get the surface from the window\n";
      return -1;
   }

   SDL_UpdateWindowSurface(window);

   SDL_Delay(5000);
   
   CPU cpu;

   cpu.run();

   return 0;
}