#include <stdlib.h>
#include <stdio.h> 
#include <strsafe.h>
#include <windows.h>
#include <stdbool.h>

void logLastError() 
{ 
    LPTSTR errorText = NULL;
    
    FormatMessage(
       FORMAT_MESSAGE_FROM_SYSTEM
       |FORMAT_MESSAGE_ALLOCATE_BUFFER
       |FORMAT_MESSAGE_IGNORE_INSERTS,  
       NULL,
       GetLastError(),
       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
       (LPTSTR)&errorText,
       0,
       NULL);
       
    if ( NULL != errorText )
    {
       printf("failure: %s", errorText);
       LocalFree(errorText);
       errorText = NULL;
    }
}

void triggerCtrlC(int pid)
{
    printf("Triggering CTRL+C on PID %d", pid)
    FreeConsole();
    if (AttachConsole(pid))
    {
        SetConsoleCtrlHandler(NULL, true);
        GenerateConsoleCtrlEvent(CTRL_C_EVENT , 0);
    }
    else {
        logLastError();
    }
}

int main( int argc, const char* argv[] ) {
    int pid = atoi(argv[1]);
    triggerCtrlC(pid);
}