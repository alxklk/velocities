#include <windows.h>
#include <winuser.h>
#include <stdio.h>

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	bool key=(wParam==WM_KEYDOWN);
	bool sys=(wParam==WM_SYSKEYDOWN);
	if(key||sys)
	{
		bool winPressed=(GetKeyState(VK_RWIN)&0x8000);
		bool altPressed=(GetKeyState(VK_RMENU)&0x8000);
		bool rshftPressed=(GetKeyState(VK_RSHIFT)&0x8000);
		bool lshftPressed=(GetKeyState(VK_LSHIFT)&0x8000);
		bool shiftPressed=lshftPressed||rshftPressed;
		bool meta=altPressed;

		PKBDLLHOOKSTRUCT kbdstruct=(KBDLLHOOKSTRUCT*)lParam;
		if(kbdstruct->vkCode==VK_SCROLL)
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
				case VK_OEM_6: // ] or }
				{
					if(lshftPressed)
						subst=0x042a;
					else
						subst=0x044a;
				}break;
				case VK_OEM_7: // ' or "
				{
					if(lshftPressed)
						subst=0x042d;
					else
						subst=0x044d;
				}break;
				case 'S':
				{
					if(lshftPressed)
						subst=0x042b;
					else
						subst=0x044b;
				}break;
				case 'T':
				{
					if(lshftPressed)
						subst=0x0401;
					else
						subst=0x0451;
				}break;
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
