#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "lazy.h"
#include "balls.h"
#include "../../../../Desktop/kdmaper/intel_driver.hpp"
#include "../../../../Desktop/kdmaper/kdmapper.hpp"
#include "bytes.h"
#include "bytes5.h"
#include <shellapi.h>
#include <random>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_CANCEL 0x03
#define VK_MBUTTON 0x04 /* NOT contiguous with L &amp; RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1 0x05 /* NOT contiguous with L &amp; RBUTTON */
#define VK_XBUTTON2 0x06 /* NOT contiguous with L &amp; RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0x07 : unassigned
 */

#define VK_BACK 0x08
#define VK_TAB 0x09

 /*
  * 0x0A - 0x0B : reserved
  */

#define VK_CLEAR 0x0C
#define VK_RETURN 0x0D

#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_CAPITAL 0x14

#define VK_KANA 0x15
#define VK_HANGEUL 0x15 /* old name - should be here for compatibility */
#define VK_HANGUL 0x15
#define VK_JUNJA 0x17
#define VK_FINAL 0x18
#define VK_HANJA 0x19
#define VK_KANJI 0x19

#define VK_ESCAPE 0x1B

#define VK_CONVERT 0x1C
#define VK_NONCONVERT 0x1D
#define VK_ACCEPT 0x1E
#define VK_MODECHANGE 0x1F

#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_SELECT 0x29
#define VK_PRINT 0x2A
#define VK_EXECUTE 0x2B
#define VK_SNAPSHOT 0x2C
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HELP 0x2F

  /*
   * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
   * 0x40 : unassigned
   * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
   */

#define VK_LWIN 0x5B
#define VK_RWIN 0x5C
#define VK_APPS 0x5D

   /*
    * 0x5E : reserved
    */

#define VK_SLEEP 0x5F

#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SEPARATOR 0x6C
#define VK_SUBTRACT 0x6D
#define VK_DECIMAL 0x6E
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F14 0x7D
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define VK_F20 0x83
#define VK_F21 0x84
#define VK_F22 0x85
#define VK_F23 0x86
#define VK_F24 0x87


#define ANSI_RED "\x1b[31m" 
#define ANSI_GREEN "\x1b[32m" 
#define ANSI_YELLOW "\x1b[33m" 
#define ANSI_BLUE "\x1b[34m" 
#define ANSI_MAGENTA "\x1b[35m" 
#define ANSI_RESET "\x1b[0m" 

#define COM1_PORT   0x03f8
#define COM2_PORT   0x02f8
#define COM3_PORT   0x03e8
#define COM4_PORT   0x02e8
using namespace std;

#pragma comment(lib, "mpr.lib")

bool DoFreeze = false;

void me()
{
    while (DoFreeze == true)
    {
        SetCursorPos(1200, 1200);
    }
}

namespace driver
{
    bool load_driver = false;
}



void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}



BOOL load_driver2()
{
    Sleep(2000);
    LI_FN(system)(skCrypt("cls"));


    HANDLE device_handle = intel_driver::Load();
    Sleep(200);

    if (!device_handle || device_handle == INVALID_HANDLE_VALUE)
    {
        LI_FN(printf)(skCrypt("Couldn't Map Driver"));
        return false;
    }

    if (!kdmapper::MapDriver(device_handle, rawData))
    {
        LI_FN(printf)(skCrypt("Couldn't Map Driver"));
        intel_driver::Unload(device_handle);
        return false;
    }

    Sleep(500);
    intel_driver::Unload(device_handle);


    unsigned char rawData[6144] = { 0 };

    return true;
}

BOOL load_driver3()
{
    Sleep(2000);
    LI_FN(system)(skCrypt("cls"));


    HANDLE device_handle = intel_driver::Load();
    Sleep(200);

    if (!device_handle || device_handle == INVALID_HANDLE_VALUE)
    {
        LI_FN(printf)(skCrypt("Couldn't Map Driver"));
        return false;
    }

    if (!kdmapper::MapDriver(device_handle, rawData))
    {
        LI_FN(printf)(skCrypt("Couldn't Map Driver"));
        intel_driver::Unload(device_handle);
        return false;
    }

    Sleep(500);
    intel_driver::Unload(device_handle);


    unsigned char rawData2[17925] = { 0 };

    return true;
}

void Purple() {
    printf("\033[0;35m");
}

std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%^&*()";

    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s + ".exe";
}
std::string path()
{
    char shitter[_MAX_PATH]; // defining the path
    GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
    return std::string(shitter); //returning the path
}

struct slowly_printing_string {
    std::string data;
    long int delay;
};
std::ostream& operator<<(std::ostream& out, const slowly_printing_string& s) {
    for (const auto& c : s.data) {
        out << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
    }
    return out;
}

void setRandomizedConsoleTitle() {
    constexpr int length = 25;
    const auto characters = TEXT("0.12345$678$9ABCDE>FGHIJK_|LMNOPQ!RSTUVWX#YZ012?34#56789AB;CDEFGH#IJKLMN:OPQRSTUVWXYZ");
    TCHAR title[length + 1]{};

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (true) {
        for (int j = 0; j < length; j++) {
            title[j] = characters[std::rand() % 55];
        }

        SetConsoleTitle(title);
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 100 milliseconds
    }
}

void MoveWindow(int posx, int posy)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter()
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
        posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

        MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}


int main()
{
    
    MoveWindow(430, 300);
    

    std::thread titleThread(setRandomizedConsoleTitle); // Create a separate thread for title setting

    ShowConsoleCursor(false);

   
    Sleep(1500);


    LI_FN(printf)(ANSI_RESET"[" ANSI_BLUE"#" ANSI_RESET"]");
    std::string s = " Connecting To Server...";

    for (const auto c : s) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << std::endl;
    Sleep(750);

    LI_FN(system)(skCrypt("cls"));
    LI_FN(printf)(ANSI_RESET"[" ANSI_BLUE"#" ANSI_RESET"] Connected!");
    LI_FN(Beep)(500, 500);
    LI_FN(Sleep)(1500);
    LI_FN(system)(skCrypt("cls"));
    LI_FN(printf)(skCrypt(ANSI_MAGENTA ""));
spoofer:
    std::cout << R"(
       $$\      $$\                    $$\   $$\     $$\       $$$$$$$\                                 $$\     
       $$ | $\  $$ |                   \__|  $$ |    $$ |      $$  __$$\                                $$ |    
       $$ |$$$\ $$ | $$$$$$\  $$$$$$\  $$\ $$$$$$\   $$$$$$$\  $$ |  $$ |$$\   $$\  $$$$$$$\  $$$$$$\ $$$$$$\   
       $$ $$ $$\$$ |$$  __$$\ \____$$\ $$ |\_$$  _|  $$  __$$\ $$$$$$$  |\$$\ $$  |$$  _____|$$  __$$\\_$$  _|  
       $$$$  _$$$$ |$$ |  \__|$$$$$$$ |$$ |  $$ |    $$ |  $$ |$$  __$$<  \$$$$  / \$$$$$$\  $$$$$$$$ | $$ |     
       $$$  / \$$$ |$$ |     $$  __$$ |$$ |  $$ |$$\ $$ |  $$ |$$ |  $$ | $$  $$<   \____$$\ $$   ____| $$ |$$\ 
       $$  /   \$$ |$$ |     \$$$$$$$ |$$ |  \$$$$  |$$ |  $$ |$$ |  $$ |$$  /\$$\ $$$$$$$  |\$$$$$$$\  \$$$$  |
       \__/     \__|\__|      \_______|\__|   \____/ \__|  \__|\__|  \__|\__/  \__|\_______/  \_______|  \____/ 
___________________________________________________________________________________________________________________                                                                                                                                                                                           
)";
    LI_FN(printf)(ANSI_BLUE"[#]\n\n\n");
    LI_FN(printf)(skCrypt(ANSI_RESET""));
    LI_FN(printf)(ANSI_GREEN"[!] This Product Can Only Be Commercialized At [https://wraithrxset.xyz/]\n\n");
    LI_FN(printf)(skCrypt(ANSI_RESET""));

    LI_FN(printf)(ANSI_BLUE"[ F1 ]" ANSI_RESET " Null Spoofing (" ANSI_BLUE"EAC/BE" ANSI_RESET ")\n");
    LI_FN(printf)(ANSI_BLUE"[ F2 ]" ANSI_RESET " Randomize Spoofing (" ANSI_BLUE"EAC/BE Optimized" ANSI_RESET ")\n");
    LI_FN(printf)(ANSI_BLUE"[ F3 ]" ANSI_RESET " Clean Others (" ANSI_BLUE"Uuid/Guid/Smbios/Registry" ANSI_RESET ")\n");
    LI_FN(printf)(ANSI_BLUE"[ F4 ]" ANSI_RESET " Check Serials (" ANSI_BLUE"Check If Disk & Bios Changed" ANSI_RESET ")\n");

    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\Network.bat >nul 2>&1"));
    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\Mac.bat >nul 2>&1"));
    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\4.bat >nul 2>&1"));
    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\regedit_change.bat >nul 2>&1"));
    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\Registry.bat >nul 2>&1"));
    LI_FN(system)(skCrypt("del  C:\\Windows\\INF\\Smbios.exe >nul 2>&1"));

    while (1)
    {
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD NumInputs = 0;
        DWORD InputsRead = 0;
        bool running = true;

        INPUT_RECORD irInput;

        GetNumberOfConsoleInputEvents(hInput, &NumInputs);

        ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

        switch (irInput.Event.KeyEvent.wVirtualKeyCode)
        {
        case VK_F1:
        {
            LI_FN(Beep)(500, 500); 
            LI_FN(system)("cls");
            BlockInput(TRUE);
            driver::load_driver = load_driver2();
            if (!driver::load_driver)
                
            LI_FN(system)("cls");
            {
                LI_FN(system)("cls");
                LI_FN(printf)(skCrypt("\n Failed to load driver \n"));
                LI_FN(Sleep)(1);
                LI_FN(system)("cls");
            }
            LI_FN(system)("cls");
            LI_FN(printf)(skCrypt(ANSI_MAGENTA""));
            Sleep(5000);
            BlockInput(FALSE);

            goto spoofer;
            break;

        }







        case VK_F2:
        {

            LI_FN(Beep)(500, 500);
            Sleep(2500);
            LI_FN(system)("cls");
            BlockInput(TRUE);
            driver::load_driver = load_driver2();
            if (!driver::load_driver)
   
            LI_FN(system)("cls");
            {
                LI_FN(system)("cls");
                LI_FN(printf)(skCrypt("\n Failed to load driver \n"));
                LI_FN(Sleep)(1);
                LI_FN(system)("cls");
            }
            LI_FN(system)("cls");
            LI_FN(printf)(skCrypt(ANSI_MAGENTA ""));
            Sleep(5000);
            BlockInput(FALSE);

            goto spoofer;
            break;
        }
            



           
       
        case VK_F3: 
        {
        
            LI_FN(system)(skCrypt("curl  https://cdn.discordapp.com/attachments/1115724000052641868/1148818637545803857/Smbios.exe -o C:\\Windows\\INF\\Smbios.exe --silent"));

            LI_FN(system)(skCrypt("start /B C:\\Windows\\INF\\Smbios.exe >nul 2>nul"));
            Sleep(15000);
            LI_FN(system)("cls");
            LI_FN(printf)(skCrypt(ANSI_MAGENTA""));
            goto spoofer;
            break;
        }

        case VK_F4: 
        
        {
            LI_FN(system)("cls");
            LI_FN(printf)(skCrypt("\n BIOS \n"));
            LI_FN(printf)(skCrypt("\n------------\n"));
            system("wmic bios get serialnumber");
            system("wmic csproduct get uuid");
            LI_FN(printf)(skCrypt("\nCPU\n"));
            LI_FN(printf)(skCrypt("\n------------\n"));
            system("wmic cpu get serialnumber");
            system("wmic cpu get processorid");
            LI_FN(printf)(skCrypt("\nDiskDrive\n"));
            LI_FN(printf)(skCrypt("\n------------\n"));
            system("wmic diskdrive get serialnumber");
            LI_FN(printf)(skCrypt("\nBASEBOARD\n"));
            LI_FN(printf)(skCrypt("\n------------\n"));
            system("wmic baseboard get serialnumber");


            cout << "Press Enter To Continue";
            getchar();
            LI_FN(system)("cls");
            LI_FN(printf)(skCrypt(ANSI_MAGENTA""));
            goto spoofer;
            break;

        }


          

        
        }
    }

    titleThread.join(); // Wait for the console title thread to finish
    return 0;
}


