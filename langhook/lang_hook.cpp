#include <windows.h>
#include <winuser.h>
#include <stdio.h>

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if((nCode==HC_ACTION)&&((wParam==WM_KEYDOWN)||(wParam==WM_SYSKEYDOWN)))
	{
		PKBDLLHOOKSTRUCT kbdstruct=(KBDLLHOOKSTRUCT*)lParam;
		if(kbdstruct->vkCode==VK_PAUSE)
		{
			puts("SW");
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
			return 1;
		}
		else if((kbdstruct->flags&(1<<5))&&(kbdstruct->vkCode==VK_OEM_MINUS))
		{
			printf("ALT MINUS\n");
			PostMessage(GetForegroundWindow(), WM_KEYDOWN, 'a', 1);
			PostMessage(GetForegroundWindow(), WM_KEYDOWN, 'A', 1);
			return 1;
		}
		else if(kbdstruct->vkCode==VK_OEM_MINUS)
		{
			printf("MINUS\n");
			SendMessage(GetForegroundWindow(), WM_KEYDOWN, 'a', 1);
			SendMessage(GetForegroundWindow(), WM_KEYDOWN, 'A', 1);
			PostMessage(GetForegroundWindow(), WM_KEYDOWN, 'a', 1);
			PostMessage(GetForegroundWindow(), WM_KEYDOWN, 'A', 1);
			SendMessage(GetForegroundWindow(), WM_CHAR, 'a', 1);
			SendMessage(GetForegroundWindow(), WM_CHAR, 'A', 1);
			PostMessage(GetForegroundWindow(), WM_CHAR, 'a', 1);
			PostMessage(GetForegroundWindow(), WM_CHAR, 'A', 1);
			return 1;
		}
		else
		{
			printf("%02x f:%02x\n", kbdstruct->vkCode, kbdstruct->flags);
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
