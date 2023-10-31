#include <windows.h>
#include <iostream>

void WatchFileChanges(const char* dirPath) {
    HANDLE dirChange = FindFirstChangeNotification(
        dirPath,
        FALSE,
        FILE_NOTIFY_CHANGE_LAST_WRITE
    );

    if (dirChange == INVALID_HANDLE_VALUE) {
        std::cerr << "Error finding first change notification: " << GetLastError() << std::endl;
        CloseHandle(dirChange);
        return;
    }

    HANDLE handles[2];
    handles[0] = dirChange;

    while (true) {
        DWORD waitResult = WaitForMultipleObjects(1, handles, FALSE, INFINITE);

        if (waitResult == WAIT_OBJECT_0) {
            std::cout << "Changes." << std::endl;
             if ( FindNextChangeNotification(handles[0]) == FALSE )
             {
               printf("\n ERROR: FindNextChangeNotification function failed.\n");
               ExitProcess(GetLastError()); 
             }
        }
         else {
            std::cerr << "Wait for change notification failed: " << GetLastError() << std::endl;
            break;
        }
    }

    FindCloseChangeNotification(dirChange);
}

int main() {
    const char* dirToWatch = "d:\\wrk\\tests\\fw";

    WatchFileChanges(dirToWatch);

    return 0;
}
