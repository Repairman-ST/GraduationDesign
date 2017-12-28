/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.28 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "bsp.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Define the available number of bytes available for the GUI
//
#define EX_SRAM   0  /*1 used extern sram, 0 used internal sram */

#if EX_SRAM
#define GUI_NUMBYTES  (1024*256)
#else
#define GUI_NUMBYTES  (70*1024)
#endif

/* Define the average block size */
#define GUI_BLOCKSIZE 0x80

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
void GUI_X_Config(void) 
{
#if EX_SRAM
	static U32 *aMemory;
	aMemory = (U32 *)BSP_SRAM_BASE;
	
	/*  Assign memory to emWin */
	GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
#else	
	/* 32 bit aligned memory area */
	static U32 aMemory[GUI_NUMBYTES / 4];
	
	/*  Assign memory to emWin */
	GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
#endif
}

/*************************** End of file ****************************/
