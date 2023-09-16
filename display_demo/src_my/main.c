/*__________________________________________________________________________________
|       Embedded Systems - 2023-2
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab - Demo usage of LCD in the BoosterPack MKII
| __________________________________________________________________________________
*/

/**
 * @file     main.c
 * @author   Douglas Renaux
 * @brief    Basic demo presenting a text on the display
 * @version  v2023-09 for Keil
 ******************************************************************************/

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "grlib.h"
#include "driverlib/sysctl.h"
#include "Crystalfontz128x128_ST7735.h"

/*------------------------------------------------------------------------------
 *
 *      Typedefs and constants
 *
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *
 *      Global vars
 *
 *------------------------------------------------------------------------------*/
tContext grContext;
int16_t width;
int16_t height;

/*------------------------------------------------------------------------------
 *
 *      Functions
 *
 *------------------------------------------------------------------------------*/
/**
 * Initialize the LCD.
 *
 * @returns void    
 * @brief - init display and graphics lib
 */
void DisplaySetup() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    GrContextInit(&grContext, &g_sCrystalfontz128x128);
		GrFlush(&grContext);
    GrContextFontSet(&grContext, &g_sFontFixed6x8);

    width = GrContextDpyWidthGet(&grContext);
    height = GrContextDpyHeightGet(&grContext);
}



/**
 * Main function.
 *
 * @returns int    - never returns
 * @brief - simple demo presenting a text on LCD
 */
int main()
{
    uint32_t ui32SysClock;
		char str[20];

    //
    // Run from the PLL at 120 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    
    // see comments in sysctl.h regarding SYSCTL_CFG_VCO_480
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), 120000000);
																			 
																				

		DisplaySetup();
		
		
		GrContextForegroundSet(&grContext, ClrWhite);
		GrContextBackgroundSet(&grContext, ClrBlack);


		GrStringDraw(&grContext,"Exemplo", -1, 0, (grContext.psFont->ui8Height+2)*0, true);
		GrStringDraw(&grContext,"Tiva + BoosterPack", -1, 0, (grContext.psFont->ui8Height+2)*1, true);
		sprintf(str,"Proc. clock:%d MHz",ui32SysClock/1000000);
		GrStringDraw(&grContext,str, -1, 0, (grContext.psFont->ui8Height+2)*2, true);
		GrStringDraw(&grContext,"---------------------", -1, 0, (grContext.psFont->ui8Height+2)*3, true);
		GrFlush(&grContext);
		while (1) { }
}

