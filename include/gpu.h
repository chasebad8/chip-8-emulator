#ifndef __GPU_H__
#define __GPU_H__

#include <SDL2/SDL.h>
#include "common_types.h"

#define PIXEL_SIZE     10

typedef struct
{
   SDL_Window   *window;
   SDL_Surface  *surface;
   SDL_Renderer *renderer;

} gpu_t;

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
bool gpu_init();

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
void init_log_gpu();

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
bool gpu_update_display(pixel_map_t pixel_map);

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
void gpu_shutdown();

#endif /* __GPU_H__ */