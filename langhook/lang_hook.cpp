#include <windows.h>
#include <winuser.h>

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if((nCode==HC_ACTION)&&(wParam==WM_KEYDOWN))
	{
		PKBDLLHOOKSTRUCT kbdstruct=(KBDLLHOOKSTRUCT*)lParam;
		if(kbdstruct->vkCode==VK_PAUSE)
		{
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
			return 1;
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
