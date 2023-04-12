#include <iostream>
#include "cpu.h"
#include "opcodes.h"
#include <SDL2/SDL.h>

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
}

int main()
{
   log_file_init();
   std::shared_ptr<spdlog::logger> logger = spdlog::get("main");
   logger->info("Booting up Chip-8 ...");

	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	// Pointers to our window and surface
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	} 

	// Create our window
	window = SDL_CreateWindow( "CHIP-8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );

	// Make sure creating the window succeeded
	if ( !window ) {
		cout << "Error creating window: " << SDL_GetError()  << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Get the surface from the window
	winSurface = SDL_GetWindowSurface( window );

	// Make sure getting the surface succeeded
	if ( !winSurface ) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Fill the window with a white rectangle
	SDL_FillRect( winSurface, NULL, SDL_MapRGB( winSurface->format, 0, 0, 0 ) );

	// Update the window display
	SDL_UpdateWindowSurface( window );

	// Wait
	sleep(10);

	// Destroy the window. This will also destroy the surface
	SDL_DestroyWindow( window );

	// Quit SDL
	SDL_Quit();
   
   CPU cpu;

   cpu.run();

   return 0;
}