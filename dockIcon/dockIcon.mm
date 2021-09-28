#import "dockIcon.h"

@implementation DockIcon

-(void)drawRect : (NSRect) dirtyRect
{
	NSGraphicsContext* gc = [NSGraphicsContext currentContext];
	[gc saveGraphicsState];

	[[NSColor blackColor] setStroke];
	[[NSColor greenColor] setFill];

	NSRect rect = NSMakeRect(10, 10, 100, 100);
	NSBezierPath* circlePath = [NSBezierPath bezierPath];
	[circlePath appendBezierPathWithOvalInRect: rect];

	[circlePath stroke];
	[circlePath fill];

	[gc restoreGraphicsState];
}

@end
