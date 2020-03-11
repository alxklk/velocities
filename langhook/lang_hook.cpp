#include <windows.h>
#include <winuser.h>
#include <stdio.h>


void unalt()
{
	INPUT inp;
	inp.type=INPUT_KEYBOARD;
	inp.ki.wVk=VK_MENU;
	inp.ki.wScan=0;
	inp.ki.dwFlags=KEYEVENTF_KEYUP;
	inp.ki.time=0;
	inp.ki.dwExtraInfo=0;
	int res=SendInput(1,&inp,sizeof(inp));
	printf("UnAlt = %i\n", res);
}

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if((nCode==HC_ACTION)&&((wParam==WM_KEYDOWN)
	//||(wParam==WM_SYSKEYDOWN)
	))
	{
		bool winPressed=(GetKeyState(VK_RWIN)&0x8000);
		bool altPressed=(GetKeyState(VK_LMENU)&0x8000);
		bool shftPressed=(GetKeyState(VK_RSHIFT)&0x8000);
		bool meta=shftPressed;

		PKBDLLHOOKSTRUCT kbdstruct=(KBDLLHOOKSTRUCT*)lParam;
		if(kbdstruct->vkCode==VK_PAUSE)
		{
			puts("SW");
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
			return 1;
		}

		// printf("%02x f:%02x\n", kbdstruct->vkCode, kbdstruct->flags);
		// if(kbdstruct->flags&(1<<5)) // Alt pressed
		if(meta)
		{
			int subst=-1;
			switch(kbdstruct->vkCode)
			{
				case VK_OEM_MINUS: subst=0x2014;break;
				case '5': subst=0x00b0;break;
				case VK_OEM_COMMA: subst=0x00ab;break;
				case VK_OEM_PERIOD: subst=0x0bb;break;
				default:;
			}
			if(subst!=-1)
			{
					INPUT inp;
					inp.type=INPUT_KEYBOARD;
					inp.ki.wVk=0;
					inp.ki.wScan=subst;
					inp.ki.dwFlags=KEYEVENTF_UNICODE;
					inp.ki.time=0;
					inp.ki.dwExtraInfo=0;
					//unalt();
					int res=SendInput(1,&inp,sizeof(inp));
					printf("SendInput = %i\n", res);
					return 1;
			}
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

int main(int argc, char** argv)
{
	HHOOK hook=SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookCallback, 0,  0);
	PostMessage(0, 0, 0, 0);
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
	{
	}
	return 0;
}
