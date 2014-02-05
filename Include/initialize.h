/*
 * File:   initialize.h
 * Author: rustam
 *
 * Created on February 5, 2014, 1:39 AM
 */

#ifndef INITIALIZE_H
#define	INITIALIZE_H

#include "Variables.h"

extern UChar *MemoryCopy(UChar *dest, const UChar *src, int count);
extern UChar *MemorySet8(UChar *dest, UChar val, int count);
extern UShort *MemorySet16(UChar *dest, UShort val, int count);
extern int StringLenght(const char *str);
extern UChar InPortb (UShort pPort);
extern void OutPortb (UShort pPort, UChar pData);

#endif	/* INITIALIZE_H */
