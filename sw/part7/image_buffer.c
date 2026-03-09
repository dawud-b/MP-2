

#include <stdint.h>
#include <string.h>
#include "image_buffer.h"

typedef struct {
	uint16_t image[1920*1080];
} image_t;

static image_t image_buffer[32];

static uint32_t image_idx = 0;

static uint32_t count = 0;

static uint32_t image_tracking_idx = 0;


void image_buffer_add_image(uint16_t* image) {

	image_tracking_idx = image_idx;

	memcpy(&image_buffer[image_idx++], image, sizeof(image_t));
	image_idx %= 32;
	count++;
}

void image_buffer_copy_image(uint16_t* dest) {
	memcpy(dest, &image_buffer[image_tracking_idx], sizeof(image_t));
}

void image_buffer_track_right() {
	if (image_tracking_idx + 1 >= count)
		return;

	image_tracking_idx++;
	image_tracking_idx %= 32;
}

void image_buffer_track_left() {
	if (image_tracking_idx == 0 && count <= 31)
		return;

	image_tracking_idx = image_tracking_idx == 0 ? 31 : image_tracking_idx - 1;
}
