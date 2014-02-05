/* 
 * File:   Functions.h
 * Author: synaps
 *
 * Created on February 5, 2014, 9:10 PM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include "Variables.h"

//Initialize.c
extern UChar *MemoryCopy(UChar *dest, const UChar *src, int count);
extern UChar *MemorySet8(UChar *dest, UChar val, int count);
extern UShort *MemorySet16(UChar *dest, UShort val, int count);
extern int StringLenght(const char *str);
extern UChar InPortb (UShort pPort);
extern void OutPortb (UShort pPort, UChar pData);

//Screen.c
extern void Scroll(void);
extern void MoveCursor(void);
extern void ClearScreen(void);
extern void PrintCharacter(UChar c);
extern void PrintString(UChar *text);
extern void SetTextColor(UChar pForegroundColor, UChar pBackgroundColor);
extern void InitializeVideo(void);

#endif	/* FUNCTIONS_H */

