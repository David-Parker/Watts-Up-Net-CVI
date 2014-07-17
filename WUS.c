/***************************************************************************************
 * (c) Copyright 2014, National Instruments. All Rights Reserved.                      *
 ***************************************************************************************/
/***************************************************************************************
 * Watts Up Series                          
 * VXIPNP, LabWindows/CVI 2012 Instrument Driver
 *
 *  Original Release: TODO 
 *  By: David Parker
 *
 *  Modification History: 
 *
 *      TODO  - Instrument Driver Created.
 ***************************************************************************************/
#include <utility.h> // TODO Delete me
#include <formatio.h>
#include <visa.h>
#include <ansi_c.h>
#include "WUS.h"

/*= DEFINES ===========================================================================*/
#define WUS_REVISION			 "Rev 1.0, 07/2014, CVI 2012" /*  Instrument driver revision */
#define WUS_BUFFER_SIZE		     512L         			  	  /*  File I/O buffer size 	     */
#define WUS_BAUD_RATE			 115200                         /*  Baud Rate                  */
#define WUS_BUFFER_SIZE_LARGE    1024L                        /*  Large buffer size          */
#define WUS_TMO_VALUE            10000                        /*  Timeout Value              */

/*= MACROS ============================================================================*/
		
/*- Error Checking ------------------------------------------------------------*/
#ifndef CheckErr
#define CheckErr(fCall) \
        if (status = (fCall), (status = (status < 0) ? status : VI_SUCCESS)) \
        { \
            goto Error; \
        } \
        else
#endif

/*- Invalid Param Reporting ---------------------------------------------------*/
#ifndef CheckParam
#define CheckParam(fCall, errorCode) \
        if (fCall) \
        { \
            status = (errorCode); \
            goto Error; \
        } \
        else
#endif


/***************************************************************************************/
/*= INSTRUMENT-DEPENDENT STATUS/RANGE STRUCTURE  ======================================*/
/***************************************************************************************/
/* WUS_stringValPair is used in the WUS_errorMessage function				   */
/*=====================================================================================*/
typedef struct  WUS_stringValPair
{
   ViStatus stringVal;
   ViString stringName;
}  WUS_tStringValPair;


/***************************************************************************************/
/*= INSTRUMENT SPECIFIC UTILITY ROUTINE DECLARATIONS (Non-Exportable Functions) =======*/
/***************************************************************************************/
ViStatus WUS_DefaultInstrSetup (ViSession vi);
ViStatus WUS_CheckStatus (ViSession vi);
static ViBoolean WUS_InvalidViBooleanRange (ViBoolean val);
static ViBoolean WUS_InvalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max);
static ViBoolean WUS_InvalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max);
static ViBoolean WUS_InvalidPtr (void* value);
static ViBoolean WUS_InvalidPositiveViInt32(ViInt32 val);



/***************************************************************************************/
/*====== USER-CALLABLE FUNCTIONS (Exportable Functions) ===============================*/
/***************************************************************************************/

/***************************************************************************************
 *Function: WUS_Initialize
 *Purpose:  Establishes communication with the instrument and optionally
            performs an instrument identification query and/or an
            instrument reset.  It also places the instrument in a default
            state needed for other instrument driver operations. 
            Therefore, call this function before calling other
            instrument driver functions for this instrument.  Generally, you need to 
            call the Initialize function only once at the beginning of an application.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_Initialize (ViRsrc VISAResourceName,
        							   ViBoolean reset, 
        							   ViSession* vi)
{
    /*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViSession rmSession = 0;
	ViUInt16  interface = VI_INTF_ASRL;

	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (WUS_InvalidViBooleanRange(reset),VI_ERROR_PARAMETER2);
	CheckParam (WUS_InvalidPtr(vi),VI_ERROR_PARAMETER3);

	/*- Open instrument session ---------------------------------------------*/
    CheckErr (viOpenDefaultRM(&rmSession));
    if ((status = viOpen(rmSession, VISAResourceName, VI_NULL, VI_NULL, vi)) < 0) {
        printf("ERROR at viOpen: %d, Session: %d\n", status, rmSession);
        viClose (rmSession);
        return status;
	}
	
	/*- Configure VISA Formatted I/O ----------------------------------------*/
    CheckErr (viSetAttribute(*vi, VI_ATTR_TMO_VALUE,WUS_TMO_VALUE));
    CheckErr (viSetBuf(*vi, VI_READ_BUF|VI_WRITE_BUF,WUS_BUFFER_SIZE_LARGE));
    CheckErr (viSetAttribute(*vi, VI_ATTR_WR_BUF_OPER_MODE,VI_FLUSH_ON_ACCESS));
    CheckErr (viSetAttribute(*vi, VI_ATTR_RD_BUF_OPER_MODE,VI_FLUSH_ON_ACCESS));
	
	/*- Configure VISA Serial Interface -----------------------------------------------*/
	CheckErr (viGetAttribute(*vi, VI_ATTR_INTF_TYPE, &interface));
    
    if (interface == VI_INTF_ASRL)
    {
		CheckErr (viSetAttribute(*vi, VI_ATTR_TERMCHAR_EN, VI_TRUE));
		CheckErr (viSetAttribute(*vi, VI_ATTR_SEND_END_EN, VI_TRUE));
		CheckErr (viSetAttribute(*vi, VI_ATTR_TERMCHAR,0xA));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_END_OUT,VI_ASRL_END_TERMCHAR));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_END_IN,VI_ASRL_END_TERMCHAR));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_BAUD, WUS_BAUD_RATE));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_FLOW_CNTRL, VI_ASRL_FLOW_RTS_CTS));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE));   
        CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_DATA_BITS,8));
        CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_STOP_BITS,VI_ASRL_STOP_ONE));
    }
	
    /*- Reset instrument ----------------------------------------------------*/
    if (reset)
        CheckErr (WUS_Reset(*vi));
    else  /* - Send Default Instrument Setup --------------------------------- */
        CheckErr (WUS_DefaultInstrSetup(*vi));   
Error:
	return status;
}

/***************************************************************************************
 *Function: WUS_Close
 *Purpose:  Takes the instrument offline.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_Close (ViSession vi)
{
	/*Define local variables.*/
	ViSession rmSession;
	ViStatus status = VI_SUCCESS;	

	/*- Check input parameter ranges ----------------------------------------*/
	CheckErr (viGetAttribute(vi, VI_ATTR_RM_SESSION, &rmSession));
	
	status = viClose (vi);
	viClose (rmSession);

Error:
    return status;
}


/***************************************************************************************
 *Function: WUS_Wait
 *Purpose:  Waits until all previously queued commands have completed finishing
            before proceeding.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_Wait (ViSession vi)
{
    /*Define local variables.*/
	ViStatus status = VI_SUCCESS;

	CheckErr (viPrintf(vi,"*WAI;"));
	CheckErr (WUS_CheckStatus(vi));

Error:
	return status;
}


/***************************************************************************************
 * Function: Error Message                                                   
 * Purpose:  This function translates the error return value from the        
             instrument driver into a user-readable string.                  
 **************************************************************************************/
ViStatus _VI_FUNC WUS_ErrorMessage (ViSession vi, 
										ViInt32 statusCode,
        								ViChar errorMessage[])
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    ViInt32 i;

    static WUS_tStringValPair statusDescArray[] = {
    {VI_ERROR_PARAMETER1,                   "ERROR: Parameter 1 out of range" },
    {VI_ERROR_PARAMETER2,                   "ERROR: Parameter 2 out of range" },
    {VI_ERROR_PARAMETER3,                   "ERROR: Parameter 3 out of range" },
    {VI_ERROR_PARAMETER4,                   "ERROR: Parameter 4 out of range" },
    {VI_ERROR_PARAMETER5,                   "ERROR: Parameter 5 out of range" },
    {VI_NULL,VI_NULL}
    };

	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (WUS_InvalidPtr(errorMessage),VI_ERROR_PARAMETER3);
    
    status = viStatusDesc (vi,statusCode,errorMessage);
    if (status == VI_WARN_UNKNOWN_STATUS){
   		for (i = 0; statusDescArray[i].stringName; i++){
   			if (statusDescArray[i].stringVal==statusCode){
   				sprintf(errorMessage,"%s",statusDescArray[i].stringName);
   				return VI_SUCCESS;
   			}
   		}
   		sprintf (errorMessage,"Unknown Error 0x%x", statusCode);
   		return VI_WARN_UNKNOWN_STATUS;
   }

Error:
   status = VI_SUCCESS;
   return status;
}

/***************************************************************************************
 *Function: WUS_Reset
 *Purpose:  Resets the instrument and then sends a set of default setup
            commands to the instrument.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_Reset (ViSession vi)
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;

    /*  Initialize the instrument to a known state.  */
    CheckErr (viPrintf(vi, "#I,Z,0;"));
    CheckErr (WUS_DefaultInstrSetup(vi));
    CheckErr (WUS_CheckStatus(vi));
Error:
    return status;
}

/***************************************************************************************
 *Function: WUS_RevisionQuery
 *Purpose:  Queries the current instrument firmware revision and instrument
            driver revision. 
            Refer to the Readme file for detailed driver information including 
            modification history.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_RevisionQuery (ViSession vi, 
        								  ViChar instrumentDriverRevision[], 
        								  ViChar instrumentFirmwareRevision[])
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    ViChar rdBuf[WUS_BUFFER_SIZE];
    
    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidPtr(instrumentDriverRevision),VI_ERROR_PARAMETER2);
    CheckParam (WUS_InvalidPtr(instrumentFirmwareRevision),VI_ERROR_PARAMETER3);

    CheckErr (viQueryf(vi,"*IDN?\n","%256[^\r]",rdBuf));
    strcpy (instrumentFirmwareRevision,strstr(rdBuf,"ver"));
    instrumentFirmwareRevision[strlen(instrumentFirmwareRevision)-1] = '\0';
    strcpy (instrumentDriverRevision,WUS_REVISION);
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}


/***************************************************************************************
 *Function: WUS_SelfTest
 *Purpose:  Runs the instrument's self-test routine and returns the test
            results.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_SelfTest (ViSession vi, 
        							 ViInt32* selfTestResultCode, 
        							 ViChar selfTestResultMessage[])
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    ViByte rdBuf[WUS_BUFFER_SIZE];

    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidPtr(selfTestResultCode),VI_ERROR_PARAMETER2);
    CheckParam (WUS_InvalidPtr(selfTestResultMessage),VI_ERROR_PARAMETER3);

    CheckErr (viQueryf(vi,"*TST?","%s",rdBuf));
    Scan (rdBuf,"%s>%d",selfTestResultCode);
    Scan (rdBuf,"%s>%s",selfTestResultMessage);
    CheckErr (WUS_CheckStatus(vi));
Error:
    return status;		
}

/***************************************************************************************
 *Function: WUS_ConfigureUserParameters
 *Purpose:  Configures the rate, threshold and currency type for the Watts Up device.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_ConfigureUserParameters (ViSession vi, 
                                                ViInt32 rate,
                                                ViInt32 threshold,
                                                ViInt32 currency)
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    
    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidViInt32Range(rate,0,10),VI_ERROR_PARAMETER2);
    CheckParam (WUS_InvalidViInt32Range(threshold,0,1999),VI_ERROR_PARAMETER3);
    CheckParam (WUS_InvalidViInt32Range(currency,0,1),VI_ERROR_PARAMETER4);
    
    //printf("Sending Command: #U,W,3,%d,%d,%d;\n",rate*WUS_COST_RATE,threshold,currency);    
    CheckErr (viPrintf(vi,"#U,W,3,%d,%d,%d;",rate*WUS_VAL_COST_RATE,threshold,currency));
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}

/***************************************************************************************
 *Function: WUS_ConfigureDataLogging
 *Purpose:  Configure the logging type and the interval rate of the data capture for the Watts Up device.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_ConfigureDataLogging (ViSession vi, 
                                                ViInt32 loggingType,
                                                ViInt32 interval)
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    ViChar loggingName[2];
    
    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidViInt32Range(loggingType,0,2),VI_ERROR_PARAMETER2);
    CheckParam (WUS_InvalidViInt32Range(interval,0,86400),VI_ERROR_PARAMETER3);

    switch(loggingType) {
        case WUS_VAL_INTERNAL_LOG: strcpy(loggingName,"I");
            break;
        case WUS_VAL_EXTERNAL_LOG: strcpy(loggingName,"E");
            break;
        case WUS_VAL_TCP_LOG: strcpy(loggingName,"T");
            break;
        default: strcpy(loggingName,"");
    }
    
    //printf("Sending Command: #L,W,3,%s,0,%d;\n",loggingName,interval);    
    CheckErr (viPrintf(vi,"#L,W,3,%s,0,%d;\n",loggingName,interval));
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}

/***************************************************************************************
 *Function: WUS_ConfigureMemoryFullHandling
 *Purpose:  Determines how new data will be recorded once the internal memory has filled up.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_ConfigureMemoryFullHandling (ViSession vi, 
                                                    ViInt32 policy)
{
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    
    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidViInt32Range(policy,0,2),VI_ERROR_PARAMETER2);
    
    printf("Sending Command: #O,W,1,%d;\n",policy);    
    CheckErr (viPrintf(vi,"#O,W,1,%d;\n",policy));
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}

/***************************************************************************************
 *Function: WUS_ConfigureItemsToLog
 *Purpose:  Configures which items will be recorded on the Watts Up internal memory.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_ConfigureItemsToLog (ViSession vi, 
                                                    ViInt32 temp)
{
    // TODO
    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    
    /*- Check input parameter ranges ----------------------------------------*/
    CheckParam (WUS_InvalidViInt32Range(temp,0,2),VI_ERROR_PARAMETER2);
    
   // printf("Sending Command: #O,W,1,%d;\n",policy);    
    CheckErr (viPrintf(vi,"#O,W,1,%d;\n",temp));
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}

/***************************************************************************************
 *Function: WUS_ReadMeterData
 *Purpose:  Reads all the data from the internal meter and stores it in Data.
 ***************************************************************************************/
ViStatus _VI_FUNC  WUS_ReadMeterData (ViSession vi, 
                                        void* Data)
{

    /*Define local variables.*/
    ViStatus status = VI_SUCCESS;
    ViChar rdBuf[WUS_BUFFER_SIZE];
    ViInt32 size = 0;
    ViInt32 i;
    ViInt32 j;

    viClear(vi);
    //Delay(1);

    /* Header that contains number of records (size) */
    CheckErr(viQueryf(vi,"#D,R,0;","%s",rdBuf));
    printf("Buffer %s\n", rdBuf);

    /* Gaurantee that we will get all the data */
    while(rdBuf[1] != 'n') {
        if(!strcmp(rdBuf,"")) return status;
        viQueryf(vi,"#D,R,0;","%s",rdBuf);
    }

    /* Parse the size variable from the header */
    char * entry;
    entry = strtok(rdBuf," ,;");
    while(entry != NULL) {
        size = atoi(entry);
        entry = strtok(NULL," ,;");
    }

    printf("Buffer: %s, Size: %d\n",rdBuf,size);

    /* If there are no records, return */
    if(size <= 0) return status;

    //ViInt32 readData[18][size];

    for(i = 0; i < size; i++) {
        CheckErr(viQueryf(vi,"#D,R,0;","%s",rdBuf));
        printf("[%d] Record: %s\n",i,rdBuf);
    }

    
    
   // printf("Sending Command: #O,W,1,%d;\n",policy);    
    //CheckErr (viPrintf(vi,"#O,W,1,%d;\n",temp));
    CheckErr (WUS_CheckStatus(vi));

Error:
    return status;
}

ViStatus _VI_FUNC  WUS_TestCommands (ViSession vi)
{

ViStatus status = VI_SUCCESS;
ViChar rdBuf[256];

viClear(vi);

CheckErr(viPrintf(vi,"#V,R,0;"));
CheckErr(viScanf(vi,"%s",rdBuf));
//CheckErr(viQueryf(vi,"#V,R,0;","%s",rdBuf));
printf("Buffer %s\n", rdBuf);

Error:
    return status; 
}


/*************************************************************************************************/
/* Function: Boolean Value Out Of Range - ViBoolean                                              */
/* Purpose:  This function checks a Boolean to see if it is equal to VI_TRUE or VI_FALSE.        */
/*           If the value is out of range, the return value is VI_TRUE, otherwise the return     */
/*           the return value is VI_FALSE.                                                       */
/*************************************************************************************************/
static ViBoolean WUS_InvalidViBooleanRange (ViBoolean val)
{
    return ((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                                    */
/* Purpose:  This function checks a long signed integer value to see if it lies between a        */
/*           minimum and maximum value.  If the value is out of range, the return value is       */
/*           VI_TRUE, otherwise the return value is VI_FALSE.                                    */
/*************************************************************************************************/
static ViBoolean WUS_InvalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Real (Double) Value Out Of Range - ViReal64                                         */
/* Purpose:  This function checks a real (double) value to see if it lies between a minimum      */
/*           and maximum value.  If the value is out of range, the return value is VI_TRUE,      */
/*           otherwise the return value is VI_FALSE.                                             */
/*************************************************************************************************/
static ViBoolean WUS_InvalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max)
{
    return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Pointer value is VI_NULL - void *                                                   */
/* Purpose:  This function checks an output parameter (pointer) to see if its value is VI_NULL.  */
/*           If the value is VI_NULL, the return value is VI_TRUE, otherwise the return value    */
/*           is VI_FALSE.                                                                        */
/*************************************************************************************************/
static ViBoolean WUS_InvalidPtr (void *value)
{
    return ((value == VI_NULL) ? VI_TRUE : VI_FALSE);
}

static ViBoolean WUS_InvalidPositiveViInt32(ViInt32 val)
{
    return val > 0;
}


/*****************************************************************************/
/*----------- INSERT INSTRUMENT-DEPENDENT UTILITY ROUTINES HERE -------------*/
/*****************************************************************************/

/*****************************************************************************************************/
/* Function: Default Instrument Setup                                                                */
/* Purpose:  This function sends a default setup to the instrument.  This function is called by      */
/*           the WUS_reset operation and by the WUS_init function if the reset option has    */
/*           not been selected.  This function is useful for configuring any  instrument settings    */
/*           that are required by the rest of the  instrument driver functions such as turning       */
/*           headers ON or OFF or using the long or short form for commands, queries, and data.      */
/*****************************************************************************************************/
ViStatus WUS_DefaultInstrSetup (ViSession instrSession)
{
    ViStatus status = VI_SUCCESS;

    return status;
}

/***************************************************************************************
 * Function: WUS_CheckStatus
 *
 * Purpose:  This function check if there is command error or command execution error by
 *           check the Event Status Register of the instrument.
 ***************************************************************************************/
ViStatus WUS_CheckStatus (ViSession vi)
{
    ViStatus    status = VI_SUCCESS;
    ViUInt32    esrValue = 0;

    //CheckErr (viQueryf(vi, "*ESR?\n", "%d", &esrValue));

    /*---------------- Check if any error or message bit was asserted -------*/
    if ((esrValue & WUS_ESR_QUERY_ERROR) != 0)
    {
        CheckErr (WUS_ESR_QUERY_ERROR);
    }
    if ((esrValue & WUS_ESR_DEVICE_DEPENDENT_ERROR) != 0)
    {
        CheckErr (WUS_ERROR_DEVICE_DEPENDENT_ERROR);
    }
    if ((esrValue & WUS_ESR_EXECUTION_ERROR) != 0)
    {
        CheckErr (WUS_ERROR_EXECUTION_ERROR);
    } 
	if ((esrValue & WUS_ESR_COMMAND_ERROR) != 0)
    {
        CheckErr (WUS_ERROR_COMMAND_ERROR);
    }

Error:
    return status;
}
/*****************************************************************************
 *-------------------------- End Instrument Driver Source Code --------------*
 *****************************************************************************/
