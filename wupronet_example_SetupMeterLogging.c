/*****************************************************************************/  
/*  Copyright 2014 National Instruments Corporation.  All Rights Reserved.   */
/*****************************************************************************/

/*****************************************************************************/
/*  Watts Up PRO .Net Series Watt Meter             						 */
/*  Developed with LabWindows/CVI 2013										 */
/*  Original Release: July 2014 											 */
/*																			 */
/*  Purpose:  This example will set up the Watts Up meter for logging.  	 */
/*																			 */
/*            To run this sample program, do the following:					 */
/*            1) Create a new project in LabWindows/CVI.					 */
/*            2) Add this file to the project.  To add files to the project, */
/*               select the Add Files To Project from the Edit menu of the   */
/*               Project window.											 */
/*            3) Add one of the following files to the project:				 */
/*               wupronet.fp, wupronet.c, or wupronet.lib.	     		     */
/*            4) Check that the resource name used in wupronet_initialize()	 */
/*               is correct. If simulating, change flag to simulate.		 */
/*            5) Run the project.											 */
/*																			 */
/*            VCC or Borland Users:											 */
/*            This example uses CVI's MessagePopup() to display the			 */
/*            measured value.  Replace this MessagePopup() function with a   */
/*            printf() or similar display function.  Remove the include		 */
/*            statement: #include <userint.h> from the source code.  Follow  */
/*            the directions for CVI users given above.						 */
/* 																			 */
/*****************************************************************************/

#include <utility.h> 
#include <ansi_c.h>
#include <stdio.h>
#include <userint.h>
#include "wupronet.h"

/* -------------------------------------------------------------------------- */
/* ================================= Macros ================================= */
/* -------------------------------------------------------------------------- */
#ifndef CheckErr
#define CheckErr(fCall) \
        if (status = (fCall), (status = (status < 0) ? status : VI_SUCCESS)) \
        { \
            goto Error; \
        } \
        else
#else
    #error Macro: CheckErr re-definition.
#endif

/* -------------------------------------------------------------------------- */
/* ============================== Pre-processors ============================ */
/* -------------------------------------------------------------------------- */

/* Change to match the resource name in wupronet_initialize() */
#define wupronet_EXAMPLE_RESOURCE_ADDRESS "COM3"
typedef enum {STOP,OVERWRITE,AUTOMATIC} policy;
typedef enum {INTERNAL,EXTERNAL,TCP} logging;
typedef enum {DOLLAR,EURO} currency;

int main()
{
	ViSession wupronet;
	ViStatus status = VI_SUCCESS;
	ViChar szMsg[1024] = {0};

	policy full = STOP;

	logging logMode = INTERNAL;
	ViInt32 interval = 10;

	ViInt32 rate = 0;
	ViInt32 threshold = 0;
	currency curr = DOLLAR;

	/* Initialize */
	CheckErr (wupronet_Initialize(wupronet_EXAMPLE_RESOURCE_ADDRESS,VI_TRUE,&wupronet));

	/* Clear all existsing data */
	CheckErr (wupronet_ResetMeterData(wupronet));

	/* Configure Memory Handling */
	CheckErr (wupronet_ConfigureMemoryFullHandling(wupronet,full));
	
	Delay(1);

	/* Configure Logging Mode */
	CheckErr (wupronet_ConfigureDataLogging(wupronet,logMode,interval));
	
	Delay(1);

	/* Configure User Parameters */
	CheckErr (wupronet_ConfigureUserParameters(wupronet,rate,threshold,curr));

	Delay(1);

	/* Configure Items to Log */
	CheckErr (wupronet_ConfigureItemsToLog(wupronet,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,
										VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE,VI_TRUE));

	/* Close */
	CheckErr (wupronet_Close(wupronet));

	sprintf (szMsg, "Setup Complete!\n The meter is now logging data.");

#if defined(_CVI_)  
    MessagePopup("Message", szMsg); 
#endif
    
Error:
    if (status != VI_SUCCESS)
    {
    	/* Watts Up Meters don't support Error Query, so just print the status code. */
        ViChar  errMsg[256];
        sprintf(errMsg, "%d", status);

    #if defined(_CVI_)  
        MessagePopup ("Error!", errMsg);
    #endif 
    }
    
    if(wupronet)
        wupronet_Close (wupronet);
    
    return 0;
}
