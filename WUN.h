/***************************************************************************************
 *
 * (c) Copyright 2014, National Instruments. All Rights Reserved.
 *
 * Title:    WUN.h
 *
 * Purpose:  
 *           VXIPNP instrument driver declarations.
 *
/***************************************************************************************/


#ifndef _WUN_HEADER_
#define _WUN_HEADER_
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
#define WUN_ERROR_DEVICE_DEPENDENT_ERROR                   (VI_ERROR_INSTR_OFFSET + 0x10L)
#define WUN_ERROR_EXECUTION_ERROR                          (VI_ERROR_INSTR_OFFSET + 0x20L)
#define WUN_ERROR_COMMAND_ERROR                            (VI_ERROR_INSTR_OFFSET + 0x30L)

/***************************************************************************************/
/*= INSTRUMENT CONSTANTS ==============================================================*/
/***************************************************************************************/

/* Defined values for Standard Event Status Register */
#define WUN_ESR_QUERY_ERROR                                 	0x04
#define WUN_ESR_DEVICE_DEPENDENT_ERROR                      	0x08
#define WUN_ESR_EXECUTION_ERROR                             	0x10
#define WUN_ESR_COMMAND_ERROR                               	0x20
#define WUN_BAUD_RATE                                       	0x1C200
#define WUN_NUM_RECORDS						0x12

/* Configure User Parameters*/
#define WUN_VAL_COST_RATE					1000

/* Configure Data Logging*/
#define WUN_VAL_INTERNAL_LOG					0x00
#define WUN_VAL_EXTERNAL_LOG					0x01
#define WUN_VAL_TCP_LOG						0x02	

/* Read Interval */
#define WUN_VAL_INTERVAL					0x05

/* Read Record Num */
#define WUN_VAL_RECORD_NUM					0x06

/* Save Log File */
#define WUN_DAY_IN_SECONDS    					0x15180

#define printf                                              DebugPrintf // TODO Delete this when done.
ViStatus _VI_FUNC  WUN_TestCommands (ViSession vi); // TODO Delete this prototype


/***************************************************************************************/
/*= GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions) =================*/
/***************************************************************************************/

ViStatus _VI_FUNC  WUN_Initialize (ViRsrc VISAResourceName,  
        							ViBoolean reset, 
        							ViSession* vi);

ViStatus _VI_FUNC  WUN_Close (ViSession vi);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Action-Status--------------------------------------*/
/*-------------------------------------------------------------------------------------*/

ViStatus _VI_FUNC  WUN_ResetMeterData (ViSession vi);
ViStatus _VI_FUNC  WUN_SaveLogFile (ViSession vi, 
                                    ViChar Path[],
                                    void* Data);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Configure------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUN_ConfigureUserParameters (ViSession vi, 
                                                ViInt32 rate,
                                                ViInt32 threshold,
                                                ViInt32 currency);

ViStatus _VI_FUNC  WUN_ConfigureDataLogging (ViSession vi, 
                                                ViInt32 loggingType,
                                                ViInt32 interval);

ViStatus _VI_FUNC  WUN_ConfigureMemoryFullHandling (ViSession vi, 
                                                    ViInt32 policy);

ViStatus _VI_FUNC  WUN_ConfigureItemsToLog (ViSession vi, ViBoolean Watts,
                                            ViBoolean Volts, ViBoolean Amps,
                                            ViBoolean Watt_Hours, ViBoolean Cost,
                                            ViBoolean Mo_Ave_KWhr, ViBoolean Mo_Ave_Cost,
                                            ViBoolean Max_Watts, ViBoolean Max_Volts, 
                                            ViBoolean Max_Amps,ViBoolean Min_Watts, 
                                            ViBoolean Min_Volts,ViBoolean Min_Amps, 
                                            ViBoolean Power_Factor,ViBoolean Duty_Cycle, 
                                            ViBoolean Power_Cycle,ViBoolean Line_Freq, 
                                            ViBoolean Volt_Amps);

/*-------------------------------------------------------------------------------------*/
/*------------------------------------Data---------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUN_ReadMeterData (ViSession vi, 
                                        void** Data,
                                        ViInt32* RecordNum);

ViStatus _VI_FUNC  WUN_ReadRecordNum (ViSession vi,
                                        ViInt32* RecordNum);

ViStatus _VI_FUNC  WUN_ReadInterval (ViSession vi,
                                    ViInt32* Interval);

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Low-level------------------------------------------*/
/*-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------*/
/*--------------------------------- Utility--------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
ViStatus _VI_FUNC  WUN_ErrorQuery (ViSession vi, 
        							   ViInt32* errorCode, 
        							   ViChar errorMessage[]);

ViStatus _VI_FUNC WUN_ErrorMessage (ViSession vi, 
        								ViInt32 statusCode,
        								ViChar errorMessage[]);

ViStatus _VI_FUNC  WUN_Reset (ViSession vi);

ViStatus _VI_FUNC  WUN_RevisionQuery (ViSession vi, 
                                          ViChar instrumentDriverRevision[], 
                                          ViChar instrumentFirmwareRevision[]);

ViStatus _VI_FUNC  WUN_SelfTest (ViSession vi, 
        							 ViInt32* selfTestResultCode, 
        							 ViChar selfTestResultMessage[]);



#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif


/***************************************************************************************/
/*=== END INCLUDE FILE ================================================================*/
/***************************************************************************************/
