/***************************************************************************************
 *
 * (c) Copyright 2014, National Instruments. All Rights Reserved.
 *
 * Title:    WUS.h
 *
 * Purpose:  
 *           VXIPNP instrument driver declarations.
 *
/***************************************************************************************/


#ifndef _WUS_HEADER_
#define _WUS_HEADER_
#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif


/***************************************************************************************/
/*= Instrument Driver Specific Error/Warning Codes ====================================*/
/***************************************************************************************/
#define VI_ERROR_INSTR_FILE_OPEN                	           (_VI_ERROR+0x3FFC0800L)
#define VI_ERROR_INSTR_FILE_WRITE               	           (_VI_ERROR+0x3FFC0801L)
#define VI_ERROR_INSTR_INTERPRETING_RESPONSE    	           (_VI_ERROR+0x3FFC0803L)
#define VI_ERROR_INSTR_PARAMETER9               	           (_VI_ERROR+0x3FFC0809L)
#define VI_ERROR_INSTR_PARAMETER10              	           (_VI_ERROR+0x3FFC080AL)
#define VI_ERROR_INSTR_PARAMETER11              	           (_VI_ERROR+0x3FFC080BL)
#define VI_ERROR_INSTR_PARAMETER12              	           (_VI_ERROR+0x3FFC080CL)
#define VI_ERROR_INSTR_PARAMETER13              	           (_VI_ERROR+0x3FFC080DL)
#define VI_ERROR_INSTR_PARAMETER14              	           (_VI_ERROR+0x3FFC080EL)
#define VI_ERROR_INSTR_PARAMETER15              	           (_VI_ERROR+0x3FFC080FL)

/***************************************************************************************/
/*= Instrument Specific Error/Warning Codes ===========================================*/
/***************************************************************************************/
#define VI_WARNING_INSTR_OFFSET						           (0x3FFC0900L)
#define VI_ERROR_INSTR_OFFSET						           (_VI_ERROR+0x3FFC0900L)
#define WUS_ERROR_DEVICE_DEPENDENT_ERROR                   (VI_ERROR_INSTR_OFFSET + 0x10L)
#define WUS_ERROR_EXECUTION_ERROR                          (VI_ERROR_INSTR_OFFSET + 0x20L)
#define WUS_ERROR_COMMAND_ERROR                            (VI_ERROR_INSTR_OFFSET + 0x30L)

/***************************************************************************************/
/*= INSTRUMENT CONSTANTS ==============================================================*/
/***************************************************************************************/

/* Defined values for Standard Event Status Register */
#define WUS_ESR_QUERY_ERROR                                 0x04
#define WUS_ESR_DEVICE_DEPENDENT_ERROR                      0x08
#define WUS_ESR_EXECUTION_ERROR                             0x10
#define WUS_ESR_COMMAND_ERROR                               0x20
#define WUS_BAUD_RATE                                       0x1C200

/* Configure User Parameters*/
#define WUS_COST_RATE                                       1000
#define printf                                              DebugPrintf // TODO Delete this when done.


/***************************************************************************************/
/*= GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions) =================*/
/***************************************************************************************/

ViStatus _VI_FUNC  WUS_Initialize (ViRsrc VISAResourceName,  
        							ViBoolean reset, 
        							ViSession* vi);

ViStatus _VI_FUNC  WUS_Close (ViSession vi);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Action-Status--------------------------------------*/
/*-------------------------------------------------------------------------------------*/

ViStatus _VI_FUNC  WUS_Wait (ViSession vi);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Configure------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUS_ConfigureUserParameters (ViSession vi, 
                                                ViInt32 rate,
                                                ViInt32 threshold,
                                                ViInt32 currency);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Low-level------------------------------------------*/
/*-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Utility--------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUS_ErrorQuery (ViSession vi, 
        							   ViInt32* errorCode, 
        							   ViChar errorMessage[]);

ViStatus _VI_FUNC WUS_ErrorMessage (ViSession vi, 
        								ViInt32 statusCode,
        								ViChar errorMessage[]);

ViStatus _VI_FUNC  WUS_Reset (ViSession vi);

ViStatus _VI_FUNC  WUS_RevisionQuery (ViSession vi, 
        								  ViChar instrumentDriverRevision[], 
        								  ViChar instrumentFirmwareRevision[]);

ViStatus _VI_FUNC  WUS_SelfTest (ViSession vi, 
        							 ViInt32* selfTestResultCode, 
        							 ViChar selfTestResultMessage[]);



#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif


/***************************************************************************************/
/*=== END INCLUDE FILE ================================================================*/
/***************************************************************************************/
