#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H


#define H_RES             1024
#define V_RES		          768
/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);


/**
 * @brief Sets pixel color
 *
 * @param x     x coordinate
 * @param y     y coordinate
 * @param color pixel color
 */

void set_pixel( short x,  short y, unsigned long color);

/**
 * @brief Gets the horizontal resolution
 * @return horizontal resolution
 */
unsigned getHorResolution();

/**
 * @brief Gets the vertical resolution
 *
 * @return vertical resolution
 */

unsigned getVerResolution();

/**
 * @brief Gets the graphics buffer
 * @return video_mem
 */
unsigned char * getGraphicsBuffer();

/**
 * @brief Gets double buffer
 * @return second_buffer
 */
unsigned char * getSecondBuffer();

/**
 * @brief Copies block of memory from second_buffer to video_mem
 */
void flipBuffer();
 /** @} end of video_gr */
#endif /* __VIDEO_GR_H */
