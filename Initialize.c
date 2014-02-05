#include "Include/Functions.h"
#include "Include/Variables.h"
#include "Include/Screen.h"


UChar *MemoryCopy(UChar *pDestination, const UChar *pSource, int count)
{
    const char *Source_ptr = (const char *)pSource;
    char *Destination_ptr = (char *)pDestination;
    for(; count != 0; count--) *Destination_ptr++ = *Source_ptr++;
    return pDestination;
}

UChar *MemorySet8(UChar *pDestination, UChar pValue, int pCount)
{
    char *temp = (char *)pDestination;
    for( ; pCount != 0; pCount--) *temp++ = pValue;
    return temp;
}

UShort *MemorySet16(UChar *pDestination, UShort pValue, int pCount)
{
    UShort *temp = (UShort *)pDestination;
    for( ; pCount != 0; pCount--) *temp++ = pValue;
    return temp;
}

int StringLenght(const char *pString)
{
    int ReturningValue;
    for(ReturningValue = 0; *pString != '\0'; pString++) ReturningValue++;
    return ReturningValue;
}


UChar InPortb (UShort pPort)
{
    UChar rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (pPort));
    return rv;
}


void OutPortb (UShort pPort, UChar pData)
{
    asm volatile ("outb %1, %0" : : "dN" (pPort), "a" (pData));
}


int Main(/*struct multiboot *mboot_ptr*/void *mboot_ptr)
{
	ClearScreen();
	SetTextColor(4, 9);
	PrintString("something interesting here");
  // All our initialization calls will go in here.
	return 0xDEADBABA;
} 
