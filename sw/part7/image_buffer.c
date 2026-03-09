

#include <stdint.h>

typedef struct {
	uint16_t image[1920*1080];
} image_t;

static image_t image_buffer[32];

static uint32_t image_idx = 0;

static int image_tracking_idx = 0;




void image_buffer_add_image(uint16_t* image) {

	image_tracking_idx = image_idx;

	image_buffer[image_idx++] = *((image_t*) image);
	image_idx %= 32;
}
