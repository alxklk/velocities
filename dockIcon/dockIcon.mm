#import "dockIcon.h"
#include "../../Cumulus/src/RT.h"
#include "../../Cumulus/Scrip/svg_bind.h"

@implementation DockIcon

-(void)drawRect : (NSRect) dirtyRect
{
	NSGraphicsContext* gc = [NSGraphicsContext currentContext];
	[gc saveGraphicsState];

	int W=128;
	int H=128;
	uint8_t pixelBuf[W*H*4];
	CGDataProvider* dataprovider=CGDataProviderCreateWithData(0, pixelBuf, W*H*4, NULL);
	CGColorSpace* cspace=CGColorSpaceCreateDeviceRGB();
	CGImage* image=CGImageCreate(W, H, 8, 32, 4*W, cspace,
		kCGImageAlphaFirst|kCGBitmapByteOrder32Host,
		dataprovider, NULL, NO, kCGRenderingIntentDefault);
	CGContext* context = (CGContext*)[gc graphicsPort];
	RT rt((rgba8*)pixelBuf,W,H);
	rt.Fill(0x00000000);
	int svg=CScincSVGBind::Instance().LoadSVG("Scinc.svg");
	CScincSVGBind::Instance().defBackend.vgs.quality=3;
	CScincSVGBind::Instance().Draw(rt, svg);

	CGContextDrawImage(context, NSMakeRect(0, 0, W, H), image);
	CGContextFlush(context);
	//delete[] pixelBuf;

	[gc restoreGraphicsState];
}

@end
