/* 
 * File:   Screen.h
 * Author: synaps
 *
 * Created on February 5, 2014, 10:55 PM
 */

#ifndef SCREEN_H
#define	SCREEN_H

//Screen.c
void Scroll(void);
void MoveCursor(void);
void ClearScreen(void);
void PrintCharacter(UChar c);
void PrintString(UChar *text);
void SetTextColor(UChar pForegroundColor, UChar pBackgroundColor);
void InitializeVideo(void);

#endif	/* SCREEN_H */

