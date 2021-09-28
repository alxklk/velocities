// clang -framework Cocoa app.m -o app
// ./app
#import <Cocoa/Cocoa.h>
#import "dockIcon.h"

int main()
{
  [NSAutoreleasePool new];
  id app = [NSApplication sharedApplication];
   [app setActivationPolicy:NSApplicationActivationPolicyRegular];
  
  NSRect frame = NSMakeRect(0, 0, 300, 300);
  id window = 
    [[[NSWindow alloc] initWithContentRect:frame
                                 styleMask:NSWindowStyleMaskTitled
                                   backing:NSBackingStoreBuffered
                                     defer:NO] autorelease];
  [window cascadeTopLeftFromPoint:NSMakePoint(10, 10)];
  [window setTitle:@"Hello"];
  [window makeKeyAndOrderFront:nil];

  id button = [[[NSButton alloc] initWithFrame:frame] autorelease];
  [button setTarget:app];
  [button setAction:@selector(terminate:)];
  [button setTitle:@"Quit"];
  [[window contentView] addSubview:button];

	[app dockTile].showsApplicationBadge=true;
	[app dockTile].badgeLabel=@"Scinc";

	[app dockTile].contentView=[[[DockIcon alloc]initWithFrame:NSMakeRect(0,0,128,128)]autorelease];
	[[app dockTile] display];
  [app activateIgnoringOtherApps:YES];
    [app setActivationPolicy:NSApplicationActivationPolicyRegular];
[app run];
  return 0;
}