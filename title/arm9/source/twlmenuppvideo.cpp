#include <nds.h>
#include <fat.h>
#include <stdio.h>
#include <maxmod9.h>

#include "common/twlmenusettings.h"
#include "common/systemdetails.h"
#include "common/gl2d.h"
#include "graphics/lodepng.h"
#include "graphics/graphics.h"
#include "graphics/color.h"
#include "sound.h"

//#include "logo_anniversary.h"
//#include "logoPhat_anniversary.h"
#include "icon_nds.h"
#include "icon_ndsl.h"
#include "icon_ndsi.h"
#include "icon_gba.h"
#include "iconPhat_gba.h"
#include "icon_gb.h"
#include "icon_a26.h"
#include "icon_int.h"
#include "icon_nes.h"
#include "icon_sms.h"
#include "icon_gg.h"
#include "icon_pce.h"
#include "icon_md.h"
#include "icon_snes.h"
#include "icon_present.h"

extern bool useTwlCfg;

//extern void loadROMselectAsynch(void);

extern u16 convertVramColorToGrayscale(u16 val);

//static int anniversaryTexID;
static int ndsTexID;
static int gbaTexID;
static int gbTexID;
static int a26TexID;
static int intTexID;
static int nesTexID;
static int smsTexID;
static int ggTexID;
static int pceTexID;
static int mdTexID;
static int snesTexID;

//static glImage anniversaryText[1];
static glImage ndsIcon[1];
static glImage gbaIcon[1];
static glImage gbIcon[1];
static glImage a26Icon[1];
static glImage intIcon[1];
static glImage nesIcon[1];
static glImage smsIcon[1];
static glImage ggIcon[1];
static glImage pceIcon[1];
static glImage mdIcon[1];
static glImage snesIcon[1];

extern u16 frameBuffer[2][256*192];
extern u16 frameBufferBot[2][256*192];
extern bool doubleBuffer;
extern bool doubleBufferTop;

extern bool fadeType;
extern bool fadeColor;
extern bool controlTopBright;

static int frameDelaySprite = 0;
static bool frameDelaySpriteEven = true;	// For 24FPS
static bool loadFrameSprite = true;

/*static int anniversaryTextYpos = -14;
static bool anniversaryTextYposMove = false;
static int anniversaryTextYposMoveSpeed = 9;
static int anniversaryTextYposMoveDelay = 0;
static bool anniversaryTextYposMoveDelayEven = true;	// For 24FPS */

static u16 twlColors[16] = {
	0x66F3,
	0x2193,
	0x359F,
	0x7A1F,
	0x323F,
	0x0B7F,
	0x0BF7,
	0x0BE2,
	0x270A,
	0x4351,
	0x7EEA,
	0x7DCB,
	0x7C42,
	0x7C53,
	0x7C58,
	0x5C17
};

static int zoomingIconXpos[11] = {-32, -32, 256, 256+16, -32, -32, 256, 256+16, -32, -32, 256+16};
static int zoomingIconYpos[11] = {-32, -48, -48, -32, 192+32, 192+48, 192+48, 192+32, -32, 192, -32};

void twlMenuVideo_loadTopGraphics(void) {
	// Anniversary
	/*glDeleteTextures(1, &anniversaryTexID);
	
	icon_Pal = (u16*)(sys().isDSPhat() ? logoPhat_anniversaryPal : logo_anniversaryPal);
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	anniversaryTexID =
	glLoadTileSet(anniversaryText, // pointer to glImage array
				256, // sprite width
				64, // sprite height
				256, // bitmap width
				64, // bitmap height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_256, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_64, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Load our 16 color tiles palette
				(u8*) (sys().isDSPhat() ? logoPhat_anniversaryBitmap : logo_anniversaryBitmap) // image data generated by GRIT
				);*/

	char currentDate[16];
	time_t Raw;
	time(&Raw);
	const struct tm *Time = localtime(&Raw);

	strftime(currentDate, sizeof(currentDate), "%m/%d", Time);

	bool december = (strncmp(currentDate, "12", 2) == 0
				   && strcmp(currentDate, "12/25") != 0
				   && strcmp(currentDate, "12/26") != 0
				   && strcmp(currentDate, "12/27") != 0
				   && strcmp(currentDate, "12/28") != 0
				   && strcmp(currentDate, "12/29") != 0
				   && strcmp(currentDate, "12/30") != 0
				   && strcmp(currentDate, "12/31") != 0);

	// NDS
	glDeleteTextures(1, &ndsTexID);

	u8* icon_Bitmap = (u8*)icon_ndsBitmap;
	u16* icon_Pal = (u16*)icon_ndsPal;
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else if (!sys().isRegularDS()) {
		icon_Bitmap = (u8*)icon_ndsiBitmap;
		icon_Pal = (u16*)icon_ndsiPal;
	} else if (!sys().isDSPhat()) {
		icon_Bitmap = (u8*)icon_ndslBitmap;
		icon_Pal = (u16*)icon_ndslPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	ndsTexID =
	glLoadTileSet(ndsIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap width
				32, // bitmap height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Load our 16 color tiles palette
				icon_Bitmap // image data generated by GRIT
				);

	// GBA
	glDeleteTextures(1, &gbaTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else {
		icon_Bitmap = (u8*)(sys().isDSPhat() ? iconPhat_gbaBitmap : icon_gbaBitmap);
		icon_Pal = (u16*)(sys().isDSPhat() ? iconPhat_gbaPal : icon_gbaPal);
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	gbaTexID =
	glLoadTileSet(gbaIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap width
				32, // bitmap height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Load our 16 color tiles palette
				icon_Bitmap // image data generated by GRIT
				);

	// GBC
	glDeleteTextures(1, &gbTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_gbBitmap;
		icon_Pal = (u16*)icon_gbPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	gbTexID =
	glLoadTileSet(gbIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// A26
	glDeleteTextures(1, &a26TexID);

	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_a26Bitmap;
		icon_Pal = (u16*)icon_a26Pal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	a26TexID =
	glLoadTileSet(a26Icon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// INT
	glDeleteTextures(1, &intTexID);

	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_intBitmap;
		icon_Pal = (u16*)icon_intPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	intTexID =
	glLoadTileSet(intIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// NES
	glDeleteTextures(1, &nesTexID);

	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_nesBitmap;
		icon_Pal = (u16*)icon_nesPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	nesTexID =
	glLoadTileSet(nesIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// SMS
	glDeleteTextures(1, &smsTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_smsBitmap;
		icon_Pal = (u16*)icon_smsPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	smsTexID =
	glLoadTileSet(smsIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// GG
	glDeleteTextures(1, &ggTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_ggBitmap;
		icon_Pal = (u16*)icon_ggPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	ggTexID =
	glLoadTileSet(ggIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// PCE
	glDeleteTextures(1, &pceTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_pceBitmap;
		icon_Pal = (u16*)icon_pcePal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	pceTexID =
	glLoadTileSet(pceIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// MD
	glDeleteTextures(1, &mdTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_mdBitmap;
		icon_Pal = (u16*)icon_mdPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	mdTexID =
	glLoadTileSet(mdIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);

	// SNES
	glDeleteTextures(1, &snesTexID);
	
	if (december) {
		icon_Bitmap = (u8*)icon_presentBitmap;
		icon_Pal = (u16*)icon_presentPal;
	} else 	{
		icon_Bitmap = (u8*)icon_snesBitmap;
		icon_Pal = (u16*)icon_snesPal;
	}
	if (ms().colorMode == 1) {
		for (int i2 = 0; i2 < 16; i2++) {
			*(icon_Pal+i2) = convertVramColorToGrayscale(*(icon_Pal+i2));
		}
	}
	snesTexID =
	glLoadTileSet(snesIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				icon_Pal, // Image palette
				icon_Bitmap // Raw image data
				);
}

extern char soundBank[];
extern bool soundBankInited;
mm_sound_effect bootJingle;

void twlMenuVideo_topGraphicRender(void) {
	glBegin2D();
	{
		// glColor(RGB15(31, 31-(3*ms().blfLevel), 31-(6*ms().blfLevel)));
		glColor(RGB15(31, 31, 31));
		//glSprite(0, anniversaryTextYpos, GL_FLIP_NONE, anniversaryText);

		glSprite(zoomingIconXpos[0], zoomingIconYpos[0], GL_FLIP_NONE, nesIcon);
		glSprite(zoomingIconXpos[1], zoomingIconYpos[1], GL_FLIP_NONE, gbIcon);
		glSprite(zoomingIconXpos[2], zoomingIconYpos[2], GL_FLIP_NONE, snesIcon);
		glSprite(zoomingIconXpos[3], zoomingIconYpos[3], GL_FLIP_NONE, gbaIcon);
		glSprite(zoomingIconXpos[4], zoomingIconYpos[4], GL_FLIP_NONE, smsIcon);
		glSprite(zoomingIconXpos[5], zoomingIconYpos[5], GL_FLIP_NONE, mdIcon);
		glSprite(zoomingIconXpos[6], zoomingIconYpos[6], GL_FLIP_NONE, ggIcon);
		glSprite(zoomingIconXpos[7], zoomingIconYpos[7], GL_FLIP_NONE, ndsIcon);
		glSprite(zoomingIconXpos[8], zoomingIconYpos[8], GL_FLIP_NONE, a26Icon);
		glSprite(zoomingIconXpos[9], zoomingIconYpos[9], GL_FLIP_NONE, pceIcon);
		glSprite(zoomingIconXpos[10], zoomingIconYpos[10], GL_FLIP_NONE, intIcon);
	}
	glEnd2D();
	GFX_FLUSH = 0;

	if (!loadFrameSprite) {
		frameDelaySprite++;
		loadFrameSprite = (frameDelaySprite == 1+frameDelaySpriteEven);
	}

	if (loadFrameSprite) {
		zoomingIconXpos[0] += 2;
		zoomingIconYpos[0] += 3;
		if (zoomingIconXpos[0] > 36) {
			zoomingIconXpos[0] = 36;
		}
		if (zoomingIconYpos[0] > 32) {
			zoomingIconYpos[0] = 32;
		}

		zoomingIconXpos[1] += 3;
		zoomingIconYpos[1] += 2;
		if (zoomingIconXpos[1] > 80) {
			zoomingIconXpos[1] = 80;
		}
		if (zoomingIconYpos[1] > 12) {
			zoomingIconYpos[1] = 12;
		}

		zoomingIconXpos[2] -= 3;
		zoomingIconYpos[2] += 2;
		if (zoomingIconXpos[2] < 154) {
			zoomingIconXpos[2] = 154;
		}
		if (zoomingIconYpos[2] > 12) {
			zoomingIconYpos[2] = 12;
		}

		zoomingIconXpos[3] -= 2;
		zoomingIconYpos[3] += 2;
		if (zoomingIconXpos[3] < 202) {
			zoomingIconXpos[3] = 202;
		}
		if (zoomingIconYpos[3] > 44) {
			zoomingIconYpos[3] = 44;
		}

		zoomingIconXpos[4] += 2;
		zoomingIconYpos[4] -= 3;
		if (zoomingIconXpos[4] > 32) {
			zoomingIconXpos[4] = 32;
		}
		if (zoomingIconYpos[4] < 120) {
			zoomingIconYpos[4] = 120;
		}

		zoomingIconXpos[5] += 3;
		zoomingIconYpos[5] -= 2;
		if (zoomingIconXpos[5] > 80) {
			zoomingIconXpos[5] = 80;
		}
		if (zoomingIconYpos[5] < 152) {
			zoomingIconYpos[5] = 152;
		}

		zoomingIconXpos[6] -= 3;
		zoomingIconYpos[6] -= 3;
		if (zoomingIconXpos[6] < 150) {
			zoomingIconXpos[6] = 150;
		}
		if (zoomingIconYpos[6] < 142) {
			zoomingIconYpos[6] = 142;
		}

		zoomingIconXpos[7] -= 2;
		zoomingIconYpos[7] -= 3;
		if (zoomingIconXpos[7] < 202) {
			zoomingIconXpos[7] = 202;
		}
		if (zoomingIconYpos[7] < 120) {
			zoomingIconYpos[7] = 120;
		}

		zoomingIconXpos[8] += 2;
		zoomingIconYpos[8] += 2;
		if (zoomingIconXpos[8] > 4) {
			zoomingIconXpos[8] = 4;
		}
		if (zoomingIconYpos[8] > 8) {
			zoomingIconYpos[8] = 8;
		}

		zoomingIconXpos[9] += 2;
		zoomingIconYpos[9] -= 2;
		if (zoomingIconXpos[9] > 8) {
			zoomingIconXpos[9] = 8;
		}
		if (zoomingIconYpos[9] < 192-40) {
			zoomingIconYpos[9] = 192-40;
		}

		zoomingIconXpos[10] -= 2;
		zoomingIconYpos[10] += 2;
		if (zoomingIconXpos[10] < 256-40) {
			zoomingIconXpos[10] = 256-40;
		}
		if (zoomingIconYpos[10] > 8) {
			zoomingIconYpos[10] = 8;
		}

		frameDelaySprite = 0;
		frameDelaySpriteEven = !frameDelaySpriteEven;
		loadFrameSprite = false;
	}
	
	/*if (rocketVideo_playVideo && rocketVideo_currentFrame >= 13) {
		if (!anniversaryTextYposMove) {
			anniversaryTextYposMoveDelay++;
			anniversaryTextYposMove = (anniversaryTextYposMoveDelay == 2+anniversaryTextYposMoveDelayEven);
		}

		if (anniversaryTextYposMove && anniversaryTextYpos < 40) {
			anniversaryTextYpos += anniversaryTextYposMoveSpeed;
			anniversaryTextYposMoveSpeed--;
			if (anniversaryTextYposMoveSpeed < 1) anniversaryTextYposMoveSpeed = 1;

			anniversaryTextYposMoveDelay = 0;
			anniversaryTextYposMoveDelayEven = !anniversaryTextYposMoveDelayEven;
			anniversaryTextYposMove = false;
		}
	}*/
}

void twlMenuVideo(void) {
	std::vector<unsigned char> image;
	unsigned width, height;

	char currentDate[16], logoPath[256];
	time_t Raw;
	time(&Raw);
	const struct tm *Time = localtime(&Raw);

	strftime(currentDate, sizeof(currentDate), "%m/%d", Time);

	if (strncmp(currentDate, "12", 2) == 0) {
		// Load christmas BG for December
		sprintf(logoPath, "nitro:/graphics/logo_twlmenuppXmas.png");
	} else if (strcmp(currentDate, "10/31") == 0) {
		// Load orange BG for Halloween
		sprintf(logoPath, "nitro:/graphics/logo_twlmenuppOrange.png");
	} else if (strcmp(currentDate, "02/14") == 0) {
		// Load heart-shaped BG for Valentine's Day
		sprintf(logoPath, "nitro:/graphics/logo_twlmenuppHeart.png");
	} else if (strcmp(currentDate, "03/17") == 0 || strcmp(currentDate, "04/22") == 0) {
		// Load green BG for St. Patrick's Day, or Earth Day
		sprintf(logoPath, "nitro:/graphics/logo_twlmenuppGreen.png");
	} else {
		// Load normal BG
		sprintf(logoPath, "nitro:/graphics/logo_twlmenupp.png");
	}

	// Load TWLMenu++ logo
	lodepng::decode(image, width, height, logoPath);
	bool alternatePixel = false;
	for(unsigned i=0;i<image.size()/4;i++) {
		image[(i*4)+3] = 0;
		if (alternatePixel) {
			if (image[(i*4)] >= 0x4) {
				image[(i*4)] -= 0x4;
				image[(i*4)+3] |= BIT(0);
			}
			if (image[(i*4)+1] >= 0x4) {
				image[(i*4)+1] -= 0x4;
				image[(i*4)+3] |= BIT(1);
			}
			if (image[(i*4)+2] >= 0x4) {
				image[(i*4)+2] -= 0x4;
				image[(i*4)+3] |= BIT(2);
			}
		}
		frameBuffer[0][i] = image[i*4]>>3 | (image[(i*4)+1]>>3)<<5 | (image[(i*4)+2]>>3)<<10 | BIT(15);
		if (alternatePixel) {
			if (image[(i*4)+3] & BIT(0)) {
				image[(i*4)] += 0x4;
			}
			if (image[(i*4)+3] & BIT(1)) {
				image[(i*4)+1] += 0x4;
			}
			if (image[(i*4)+3] & BIT(2)) {
				image[(i*4)+2] += 0x4;
			}
		} else {
			if (image[(i*4)] >= 0x4) {
				image[(i*4)] -= 0x4;
			}
			if (image[(i*4)+1] >= 0x4) {
				image[(i*4)+1] -= 0x4;
			}
			if (image[(i*4)+2] >= 0x4) {
				image[(i*4)+2] -= 0x4;
			}
		}
		frameBuffer[1][i] = image[i*4]>>3 | (image[(i*4)+1]>>3)<<5 | (image[(i*4)+2]>>3)<<10 | BIT(15);
		if ((i % 256) == 255) alternatePixel = !alternatePixel;
		alternatePixel = !alternatePixel;
	}
	image.clear();

	doubleBuffer = true;
	doubleBufferTop = true;

	lodepng::decode(image, width, height, "nitro:/graphics/TWL.png");

	u16* twlTextBuffer = new u16[60*14];
	int x = 19;
	int y = 81;
	for (int i=0; i<60*14; i++) {
		if (x >= 79) {
			x = 19;
			y++;
		}
		if (image[(i*4)+3] > 0) {
			const u16 color = twlColors[(int)(useTwlCfg ? *(u8*)0x02000444 : PersonalData->theme)];
			const u16 bgColor = frameBuffer[0][y*256+x];
			twlTextBuffer[i] = alphablend(color, bgColor, image[(i*4)+3]);
		} else {
			twlTextBuffer[i] = 0;
		}
		x++;
	}

	u16* src = twlTextBuffer;
	x = 19;
	y = 81;
	for (int i=0; i<60*14; i++) {
		if (x >= 79) {
			x = 19;
			y++;
		}
		u16 val = *(src++);
		if (image[(i*4)+3] > 0) {
			frameBuffer[0][y*256+x] = val;
			frameBuffer[1][y*256+x] = val;
		}
		x++;
	}

	delete[] twlTextBuffer;

	image.clear();

	if (ms().colorMode == 1) {
		for (int i=0; i<256*192; i++) {
			frameBuffer[0][i] = convertVramColorToGrayscale(frameBuffer[0][i]);
			frameBufferBot[1][i] = convertVramColorToGrayscale(frameBuffer[1][i]);
		}
	}

	fadeType = true;

	for (int i = 0; i < 15; i++)
	{
		swiWaitForVBlank();
	}

	snd();
	snd().beginStream();

	extern bool twlMenuSplash;
	twlMenuSplash = true;

	for (int i = 0; i < (60 * 3); i++)
	{
		scanKeys();
		if ((keysHeld() & KEY_START) || (keysHeld() & KEY_SELECT) || (keysHeld() & KEY_TOUCH)) return;
		//loadROMselectAsynch();
		snd().updateStream();
		swiWaitForVBlank();
	}
}