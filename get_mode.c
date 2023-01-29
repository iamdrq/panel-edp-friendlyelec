#include <stdio.h>

/* -------------------------------------------------------------- */
/*
 * struct lcd_polarity
 * @rise_vclk:	if 1, video data is fetched at rising edge
 * @inv_hsync:	if HSYNC polarity is inversed
 * @inv_vsync:	if VSYNC polarity is inversed
 * @inv_vden:	if VDEN polarity is inversed
 */
struct lcd_polarity {
	int	rise_vclk;
	int	inv_hsync;
	int	inv_vsync;
	int	inv_vden;
};

/*
 * struct lcd_timing
 * @h_fp:	horizontal front porch
 * @h_bp:	horizontal back porch
 * @h_sw:	horizontal sync width
 * @v_fp:	vertical front porch
 * @v_fpe:	vertical front porch for even field
 * @v_bp:	vertical back porch
 * @v_bpe:	vertical back porch for even field
 */
struct lcd_timing {
	int	h_fp;
	int	h_bp;
	int	h_sw;
	int	v_fp;
	int	v_fpe;
	int	v_bp;
	int	v_bpe;
	int	v_sw;
};

/*
 * struct lcd_desc
 * @width:	horizontal resolution
 * @height:	vertical resolution
 * @p_width:	width of lcd in mm
 * @p_height:	height of lcd in mm
 * @bpp:	bits per pixel
 * @freq:	vframe frequency
 * @timing:	timing values
 * @polarity:	polarity settings
 */
struct lcd_desc {
	int	width;
	int	height;
	int	p_width;
	int	p_height;
	int	bpp;
	int	freq;
	struct	lcd_timing timing;
	struct	lcd_polarity polarity;
};

static struct lcd_desc k116e = {
	.width = 1920,
	.height = 1080,
	.p_width = 256,
	.p_height = 144,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 48,
		.h_bp = 80,
		.h_sw = 32,
		.v_fp = 3,
		.v_fpe = 1,
		.v_bp = 23,
		.v_bpe = 1,
		.v_sw = 5,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

int main()
{
	struct lcd_desc *lcd=&k116e;
    printf("hdisplay：%d\n", lcd->width);
    printf("hsync_start：%d+%d\n", lcd->width,lcd->timing.h_fp);
    printf("hsync_end：%d+%d+%d\n", lcd->width,lcd->timing.h_fp,lcd->timing.h_sw);
	printf("htotal：%d+%d+%d+%d\n", lcd->width,lcd->timing.h_fp,lcd->timing.h_sw,lcd->timing.h_bp);
	
	
	printf("vdisplay：%d\n", lcd->height);
    printf("vsync_start：%d+%d\n", lcd->height,lcd->timing.v_fp);
    printf("vsync_end：%d+%d+%d\n", lcd->height,lcd->timing.v_fp,lcd->timing.v_sw);
	printf("vtotal：%d+%d+%d+%d\n", lcd->height,lcd->timing.v_fp,lcd->timing.v_sw,lcd->timing.v_bp);
   
	printf("clock：%d\n", (lcd->width+lcd->timing.h_fp+lcd->timing.h_sw+lcd->timing.h_bp)*(lcd->height+lcd->timing.v_fp+lcd->timing.v_sw+lcd->timing.v_bp)*60/1000);
    
	printf("flags：%s | %s\n",lcd->polarity.inv_hsync? "DRM_MODE_FLAG_NHSYNC":"DRM_MODE_FLAG_PHSYNC",lcd->polarity.inv_vsync? "DRM_MODE_FLAG_NVSYNC":"DRM_MODE_FLAG_PVSYNC");
	return 0;
}
