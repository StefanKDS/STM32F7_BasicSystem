/*
 * SDView.c
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#include "SDView.h"

#include "stm32746g_discovery_lcd.h"
#include "BaseView.h"
#include "../FATFS/App/fatfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char stringList[10][256];
int listSize = 0;
int yPos = 40;
char lastDir[256] ;
char currentDir[256] = "/";

void ClearListArea();
void ShowSDMenuPoints();
void InitMenuScreen(uint8_t* headerString);

// Methods
FRESULT scan_files (char* path, int offset, int* readElements)
{
    FRESULT res;
    DIR dir;
    static FILINFO fno;

    int nbrOfElements = 0;
    int readedElements = 0;

    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0)
            	break;  /* Break on error or end of dir */

            if (nbrOfElements >=  offset)
            {
            	if (fno.fattrib & AM_DIR) {                    /* It is a directory */
            		sprintf(stringList[readedElements], "/%s", fno.fname);
            	}
            	else
            	{
            		sprintf(stringList[readedElements], "%s", fno.fname);
            	}

            	readedElements++;
            }

            nbrOfElements++;

            if(readedElements >= 10)
            	break;
        }
        *readElements = readedElements;
        f_closedir(&dir);
    }

    return res;
}

void ShowSDDirectories(uint8_t* headerString)
{
	DrawBaseScreen(headerString, LCD_COLOR_ST_ORANGE);
	ShowSDMenuPoints();

	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);

	uint8_t SD_state = MSD_OK;
	SD_state = BSP_SD_Init();

	  if (SD_state != MSD_OK)
	  {
	    if(SD_state == MSD_ERROR_SD_NOT_PRESENT)
	    {
	      BSP_LCD_DisplayStringAt(60, 50, (uint8_t *)"SD shall be inserted before running", LEFT_MODE);
	    }
	    else
	    {
	    BSP_LCD_DisplayStringAt(60, 50, (uint8_t *)"SD Initialization : FAIL.", LEFT_MODE);
	    }

	    BSP_LCD_DisplayStringAt(60, 50, (uint8_t *)"SD Comm Aborted.", LEFT_MODE);
	  }
	  else
	  {
		  BSP_LCD_DisplayStringAt(60, 50, (uint8_t *)"SD Initialization : OK.", LEFT_MODE);
	  }

	  // Search in root directory
	  ClearListArea();
	  FATFS fs;
	  FRESULT res;
	  char buff[100];
	  int readFiles = 0;

	  res = f_mount(&fs, "", 1);
	  if (res == FR_OK) {
	      strcpy(buff, "/");
	      res = scan_files(buff,0,&readFiles);
	  }
	  f_mount(0, "", 0);

	  listSize = readFiles;

	  for(int i=0; i<readFiles; i++)
	  {
		  BSP_LCD_DisplayStringAt(60, yPos, (uint8_t *)stringList[i], LEFT_MODE);
		  yPos += 20;
	  }

	  yPos = 40;

	  BSP_LCD_SetTextColor(oldColor);
}

void ShowFileList(char* path)
{
	ClearListArea();
	FATFS fs;
	FRESULT res;
	int readFiles = 0;
    listSize = 0;

	res = f_mount(&fs, "", 1);
	if (res == FR_OK)
	{
	    res = scan_files(path,0,&readFiles);
	}
	f_mount(0, "", 0);

	listSize = readFiles;

	for(int i=0; i<readFiles; i++)
	{
		BSP_LCD_DisplayStringAt(60, yPos, (uint8_t *)stringList[i], LEFT_MODE);
		yPos += 20;
	}

	yPos = 40;
}

void SDCardTouchDetected(uint16_t x, uint16_t y)
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);

	// Menu click
	if(x < 60)
	{
		// Zurück
		if((y > 120) && (y < 152))
		{
			ShowFileList(lastDir);
		}

		// Home
		if((y > 38) && (y < 119))
		{
			InitMenuScreen((uint8_t *)"SEYERSOFT");
			//MainMenu();
		}
	}

	// List click
	if(x > 60)
	{
		double selectedItem = (y - 40) / 20;
		if ((selectedItem < listSize) && (stringList[(int)selectedItem][0] == '/'))
		{
			ShowFileList(stringList[(int)selectedItem]);
		}
	}
	BSP_LCD_SetTextColor(oldColor);
}

void ClearListArea()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(59,39,BSP_LCD_GetXSize()-60,BSP_LCD_GetYSize()-60);
	BSP_LCD_SetTextColor(oldColor);
}

void ShowSDMenuPoints()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_ST_GREEN);

	BSP_LCD_SetBackColor(LCD_COLOR_ST_SKIN);
	BSP_LCD_DisplayStringAt(18, 70, (uint8_t *)"H", LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_ST_GREEN);
	BSP_LCD_DisplayStringAt(18, 126, (uint8_t *)"<", LEFT_MODE);
	//BSP_LCD_DisplayStringAt(18, 158, (uint8_t *)">", LEFT_MODE);
	BSP_LCD_SetTextColor(oldColor);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}



