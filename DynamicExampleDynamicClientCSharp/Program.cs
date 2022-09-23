using System.Runtime.InteropServices;


[DllImport("DynamicExample.DynamicLibrary.dll", SetLastError = true, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
static extern void fibonacci_init(ulong a, ulong b);

[DllImport("DynamicExample.DynamicLibrary.dll", SetLastError = true, CharSet = CharSet.Unicode)]
static extern bool fibonacci_next();

[DllImport("DynamicExample.DynamicLibrary.dll", SetLastError = true, CharSet = CharSet.Unicode)]
static extern ulong fibonacci_current();

[DllImport("DynamicExample.DynamicLibrary.dll", SetLastError = true, CharSet = CharSet.Unicode)]
static extern uint fibonacci_index();


// See https://aka.ms/new-console-template for more information
Console.WriteLine("Writing out first 90 numbers in fibonacci sequence");


// Initialize a Fibonacci relation sequence.
fibonacci_init(1, 1);
// Write out the sequence values until overflow.
do
{
    Console.WriteLine(fibonacci_index() + ": " + fibonacci_current());
} while (fibonacci_next());
// Report count of values written before overflow.

Console.WriteLine("Completed");