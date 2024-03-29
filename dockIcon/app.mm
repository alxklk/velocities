// clang -framework Cocoa app.m -o app
// ./app
#import <Cocoa/Cocoa.h>
#import "dockIcon.h"

void MakeIcon()
{
	id app = [NSApplication sharedApplication];
	[app dockTile].contentView=[
			[[DockIcon alloc]initWithFrame:NSMakeRect(0,0,128,128)]
			autorelease
		];
	[[app dockTile] display];
}

@interface BR : NSObject {}
@end

@implementation BR
- (void)button:(id)sender
{
	printf("Button pressed\n");
	MakeIcon();
}
@end

int main()
{
	[NSAutoreleasePool new];
	id app = [NSApplication sharedApplication];
	[app setActivationPolicy:NSApplicationActivationPolicyRegular];
	
	NSRect frame = NSMakeRect(0, 0, 300, 300);
	id window = [
			[[NSWindow alloc]
			initWithContentRect:frame
			styleMask:NSWindowStyleMaskTitled
			backing:NSBackingStoreBuffered
			defer:NO]
			autorelease
		];
	[window cascadeTopLeftFromPoint:NSMakePoint(10, 10)];
	[window setTitle:@"Hello"];
	[window makeKeyAndOrderFront:nil];

	id button = [[[NSButton alloc] initWithFrame:frame] autorelease];
	BR* br=[[BR alloc]init];
	[button setTarget:br];
	[button setAction:@selector(button:)];
	[button setTitle:@"Press"];
	[[window contentView] addSubview:button];

//	[app dockTile].showsApplicationBadge=true;
//	[app dockTile].badgeLabel=@"Scinc";

	[app activateIgnoringOtherApps:YES];
	[app setActivationPolicy:NSApplicationActivationPolicyRegular];
	[app run];
	return 0;
}