// DynamicExample.DynamicClientCPPExplicitLink.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// A simple program that uses LoadLibrary and 
// GetProcAddress to access myPuts from Myputs.dll. 
#include <iostream>
#include <windows.h> 
#include <stdio.h> 

typedef int(__cdecl* MYPROC)(LPCWSTR);

int main(void)
{
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("DynamicExample.DynamicLibrary.dll"));

    // If the handle is valid, try to get the function address.

    if (hinstLib != NULL)
    {
        //1    0 0001100A fibonacci_current = @ILT + 5(fibonacci_current)
        //2    1 000112DA fibonacci_index = @ILT + 725(fibonacci_index)
        //3    2 0001123A fibonacci_init = @ILT + 565(fibonacci_init)
        //4    3 0001129E fibonacci_next = @ILT + 665(fibonacci_next)
        //
        typedef auto fibonacci_init_p(const unsigned long long const, const unsigned long long) -> void;
        auto fibonacci_init = (fibonacci_init_p*)::GetProcAddress(hinstLib, "fibonacci_init");

        typedef auto fibonacci_next_p() -> bool;
        auto fibonacci_next = (fibonacci_next_p*)::GetProcAddress(hinstLib, "fibonacci_next");

        typedef auto fibonacci_current_p() -> unsigned long long;
        auto fibonacci_current = (fibonacci_current_p*)::GetProcAddress(hinstLib, "fibonacci_current");

        typedef auto fibonacci_index_p() -> unsigned;
        auto fibonacci_index = (fibonacci_index_p*)::GetProcAddress(hinstLib, "fibonacci_index");


        std::cout << "Writing out first 90 numbers in fibonacci sequence" << std::endl;
        // Initialize a Fibonacci relation sequence.
        fibonacci_init(1, 1);
        // Write out the sequence values until overflow.
        do {
            std::cout << fibonacci_index() << ": "
                << fibonacci_current() << std::endl;
        } while (fibonacci_next());
        // Report count of values written before overflow.
        std::cout << "Completed" << std::endl;

        fFreeResult = FreeLibrary(hinstLib);
    }
    else {
        std::cout << "Unable to load library at runtime" << std::endl;
    }


    return 0;

}

