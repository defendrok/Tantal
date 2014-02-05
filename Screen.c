#include "Include/Functions.h"
#include "Include/Variables.h"

/* These define our textpointer, our background and foreground
*  colors (attributes), and x and y cursor coordinates */
UShort *VideoMemory;
int Attribute = 0x0F;
int x = 0, y = 0;

/* Scrolls the screen */
void Scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (Attribute << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(x >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = x - 25 + 1;
        MemoryCopy ((UChar *)VideoMemory, (UChar *)VideoMemory + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        MemorySet16 ((UChar *)VideoMemory + (25 - temp) * 80, blank, 80);
        y = 25 - 1;
    }
}

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void MoveCursor(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = y * 80 + x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    OutPortb(0x3D4, 14);
    OutPortb(0x3D5, temp >> 8);
    OutPortb(0x3D4, 15);
    OutPortb(0x3D5, temp);
}

/* Clears the screen */
void ClearScreen(void)
{
    /*
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color 
    blank = 0x20 | (Attribute << 8);

    /* Sets the entire screen to spaces in our current
    *  color 
    for(i = 0; i < 25; i++)
        MemorySet16 ((UChar *)VideoMemory + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor 
    x = 0;
    y = 0;
    MoveCursor();
    */
    
    	UShort *VideoMemory = (UShort *)0xb8000;
	Int i;
	for(i = 0; i < 25*80; ++i)
		VideoMemory[i] = 32 | (Attribute << 8);
	x = y = 0;
	MoveCursor();
}

/* Puts a single character on the screen */
void PrintCharacter(UChar c)
{
    UShort *where;
    unsigned att = Attribute << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(x != 0) x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        x = (x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        x = 0;
        y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = VideoMemory + (y * 80 + x);
        *where = c | att;	/* Character AND attributes: color */
        x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(x >= 80)
    {
        x = 0;
        y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    Scroll();
    MoveCursor();
}

/* Uses the above routine to output a string... */
void PrintString(UChar *text)
{
    int i;

    for (i = 0; i < StringLenght(text); i++)
    {
        PrintCharacter(text[i]);
    }
}

/* Sets the forecolor and backcolor that we will use */
void SetTextColor(UChar pForegroundColor, UChar pBackgroundColor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    Attribute = (pBackgroundColor << 4) | (pForegroundColor & 0x0F);
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void InitializeVideo(void)
{
    VideoMemory = (UShort *)0xB8000;
    ClearScreen();
}