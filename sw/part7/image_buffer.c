

#include <stdint.h>
#include <xil_cache.h>
#include "image_buffer.h"


typedef struct {
	uint16_t image[1920*1080];
} image_t;

static image_t image_buffer[32];

static uint32_t image_idx = 0;

static uint32_t image_tracking_idx = 0;

static int start_idx = -1;
static int end_idx = 0;

void image_buffer_add_image(uint16_t* image) {

	image_tracking_idx = image_idx;

	end_idx = image_idx;

	if (end_idx == start_idx) {
		start_idx++;
		start_idx %= 32;
	} else if (start_idx == -1)
		start_idx = 0;

	Xil_DCacheFlush();
	image_buffer[image_idx++] = *((image_t*) image);

	image_idx %= 32;
}

void image_buffer_copy_image(uint16_t* dest) {

	*((image_t*) dest) = image_buffer[image_tracking_idx];
	Xil_DCacheFlush();

}

void image_buffer_track_right() {

	if (image_tracking_idx == end_idx)
		return;

	image_tracking_idx++;
	image_tracking_idx %= 32;
}

void image_buffer_track_left() {

	if (image_tracking_idx == start_idx)
		return;

	image_tracking_idx = image_tracking_idx == 0 ? 31 : image_tracking_idx - 1;
}
