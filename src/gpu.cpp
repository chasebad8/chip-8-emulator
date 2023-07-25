#include "gpu.h"
#include "spdlog/spdlog.h"

std::shared_ptr<spdlog::logger> gpu_logger;

gpu_t gpu = { 0 };

/**
 * ============================================================================
 *
 * @name       gpu_init
 *
 * @brief      Initialize the display (In this project we render from CPU
 *             not the GPU but it is fun to pretend)
 *
 * @return    void
 *
 * ============================================================================
*/
bool gpu_init()
{
	bool rc = false;

   gpu_logger->info("Initializing GPU ...");
   
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		gpu_logger->error("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else if((gpu.window = SDL_CreateWindow("CHIP 8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN)) == NULL)
	{
		gpu_logger->error("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else if((gpu.renderer = SDL_CreateRenderer(gpu.window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
	{
		gpu_logger->error( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
   }
	else
	{
		rc = true;
	}

   return rc;
}

/**
 * ============================================================================
 *
 * @name       init_log_gpu
 *
 * @brief      Initialize the log for gpu functions
 *
 * @return     void
 *
 * ============================================================================
*/
void init_log_gpu()
{
   gpu_logger = spdlog::get("main");
}

/**
 * ============================================================================
 *
 * @name       gpu_update_display
 *
 * @brief      Update the screen
 *
 *
 * @param[in]  pixel_map - a 64 by 32 map of the pixels to update in the next
 *                         frame
 *
 * @return     bool
 *
 * ============================================================================
*/
bool gpu_update_display(pixel_map_t pixel_map)
{
   bool rc = true;

	if(pixel_map == NULL)
	{
		rc = false;
	}
   else
   {
      /* Background is cleared */
      SDL_SetRenderDrawColor(gpu.renderer, 0, 0, 0, 255);
      SDL_RenderClear(gpu.renderer);

      /* Set drawing color to white for the new pixels */
      SDL_SetRenderDrawColor(gpu.renderer, 255, 255, 255, 255); // White color

      for (int x = 0; x < SCREEN_WIDTH; x++) {
         for (int y = 0; y < SCREEN_HEIGHT; y++) {
            if (pixel_map[x][y] == PIXEL_ON)
            {
                  int pixelX         = x * PIXEL_SIZE;
                  int pixelY         = y * PIXEL_SIZE;
                  SDL_Rect pixelRect = {pixelX, pixelY, PIXEL_SIZE, PIXEL_SIZE};
                  SDL_RenderFillRect(gpu.renderer, &pixelRect);
            }
         }
      }

      SDL_RenderPresent(gpu.renderer);
   }

   return rc;
}

/**
 * ============================================================================
 *
 * @name       gpu_shutdown
 *
 * @brief      Delete the SDL window and quit out of SDL
 *
 * @return    void
 *
 * ============================================================================
**/
void gpu_shutdown()
{
	SDL_DestroyWindow(gpu.window);
	SDL_Quit();
}