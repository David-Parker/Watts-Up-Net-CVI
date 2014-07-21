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
#define WUS_ESR_QUERY_ERROR                                 	0x04
#define WUS_ESR_DEVICE_DEPENDENT_ERROR                      	0x08
#define WUS_ESR_EXECUTION_ERROR                             	0x10
#define WUS_ESR_COMMAND_ERROR                               	0x20
#define WUS_BAUD_RATE                                       	0x1C200
#define WUS_NUM_RECORDS						0x12

/* Configure User Parameters*/
#define WUS_VAL_COST_RATE					1000

/* Configure Data Logging*/
#define WUS_VAL_INTERNAL_LOG					0x00
#define WUS_VAL_EXTERNAL_LOG					0x01
#define WUS_VAL_TCP_LOG						0x02	

/* Read Interval */
#define WUS_VAL_INTERVAL					0x05

/* Read Record Num */
#define WUS_VAL_RECORD_NUM					0x06

#define printf                                              DebugPrintf // TODO Delete this when done.
ViStatus _VI_FUNC  WUS_TestCommands (ViSession vi); // TODO Delete this prototype


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

ViStatus _VI_FUNC  WUS_ResetMeterData (ViSession vi);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Configure------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUS_ConfigureUserParameters (ViSession vi, 
                                                ViInt32 rate,
                                                ViInt32 threshold,
                                                ViInt32 currency);

ViStatus _VI_FUNC  WUS_ConfigureDataLogging (ViSession vi, 
                                                ViInt32 loggingType,
                                                ViInt32 interval);

ViStatus _VI_FUNC  WUS_ConfigureMemoryFullHandling (ViSession vi, 
                                                    ViInt32 policy);

ViStatus _VI_FUNC  WUS_ConfigureItemsToLog (ViSession vi, 
                                                    ViInt32 temp); // TODO

/*-------------------------------------------------------------------------------------*/
/*------------------------------------Data---------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUS_ReadMeterData (ViSession vi, 
                                        void* Data,
                                        ViInt32* RecordNum);

ViStatus _VI_FUNC  WUS_ReadRecordNum (ViSession vi,
                                        ViInt32* RecordNum);

ViStatus _VI_FUNC  WUS_ReadInterval (ViSession vi,
                                    ViInt32* Interval);

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
