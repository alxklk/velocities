#import "dockIcon.h"

@implementation DockIcon

-(void)drawRect : (NSRect) dirtyRect
{
	NSGraphicsContext* gc = [NSGraphicsContext currentContext];
	[gc saveGraphicsState];

	NSBezierPath* path = [NSBezierPath bezierPath];
	// [path appendBezierPathWithOvalInRect: NSMakeRect(10, 10, 100, 100)];

	[path appendBezierPathWithRoundedRect: NSMakeRect(10, 10, 108, 108)
		xRadius:10
		yRadius:10
	];
	[path moveToPoint: NSMakePoint(64,64)];
	[path relativeCurveToPoint: NSMakePoint(0,-20)
		controlPoint1:NSMakePoint(20,0)
		controlPoint2:NSMakePoint(20,-20)
	];
	[path relativeCurveToPoint: NSMakePoint(0,20)
		controlPoint1:NSMakePoint(-20,0)
		controlPoint2:NSMakePoint(-20,20)
	];

	[[NSColor whiteColor] setStroke];
	[[NSColor colorWithRed:0.5 green:0.8 blue: 0.6 alpha: 1.0] setFill];
	[path setLineWidth:10];
	[path stroke];
	[path fill];

	[gc restoreGraphicsState];
}

@end
