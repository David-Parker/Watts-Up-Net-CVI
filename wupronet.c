/***************************************************************************************
 * (c) Copyright 2014, National Instruments. All Rights Reserved.                      *
 ***************************************************************************************/
/***************************************************************************************
 * Watts Up Series                          
 * VXIPNP, LabWindows/CVI 2013 Instrument Driver
 *
 *  Original Release: 07/23/2014 
 *  By: David Parker
 *
 *  Modification History: 
 *
 *      07/14/2014  - Instrument Driver Created.
 ***************************************************************************************/
#include <utility.h>
#include <formatio.h>
#include <visa.h>
#include <ansi_c.h>
#include "wupronet.h"

/*= DEFINES ===========================================================================*/
#define WUPRONET_REVISION			 "Rev 1.0, 07/2014, CVI 2012" /*  Instrument driver revision */
#define WUPRONET_BUFFER_SIZE		  1024L         			  /*  File I/O buffer size 	     */
#define WUPRONET_BAUD_RATE			 115200                       /*  Baud Rate                  */
#define WUPRONET_BUFFER_SIZE_LARGE    4096L                       /*  Large buffer size          */
#define WUPRONET_TMO_VALUE            10000                       /*  Timeout Value              */

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
/* wupronet_stringValPair is used in the wupronet_errorMessage function				   */
/*=====================================================================================*/
typedef struct  wupronet_stringValPair
{
   ViStatus stringVal;
   ViString stringName;
}  wupronet_tStringValPair;


/***************************************************************************************/
/*= INSTRUMENT SPECIFIC UTILITY ROUTINE DECLARATIONS (Non-Exportable Functions) =======*/
/***************************************************************************************/
ViStatus wupronet_DefaultInstrSetup (ViSession vi);
ViStatus wupronet_CheckStatus (ViSession vi);
static ViBoolean wupronet_InvalidViBooleanRange (ViBoolean val);
static ViBoolean wupronet_InvalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max);
static ViBoolean wupronet_InvalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max);
static ViBoolean wupronet_InvalidPtr (void* value);
static ViStatus wupronet_addRecords(ViInt32 size, ViInt32 data[][size], ViChar str[], ViInt32 index);
static ViInt32 wupronet_GetNthParameter(ViChar rdBuf[], ViInt32 n);



/***************************************************************************************/
/*====== USER-CALLABLE FUNCTIONS (Exportable Functions) ===============================*/
/***************************************************************************************/

/***************************************************************************************
 *Function: wupronet_Initialize
 *Purpose:  Establishes communication with the instrument and optionally
			performs an instrument identification query and/or an
			instrument reset.  It also places the instrument in a default
			state needed for other instrument driver operations. 
			Therefore, call this function before calling other
			instrument driver functions for this instrument.  Generally, you need to 
			call the Initialize function only once at the beginning of an application.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_Initialize (ViRsrc VISAResourceName,
									   ViBoolean reset, 
									   ViSession* vi)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViSession rmSession = 0;
	ViUInt16  interface = VI_INTF_ASRL;

	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidViBooleanRange(reset),VI_ERROR_PARAMETER2);
	CheckParam (wupronet_InvalidPtr(vi),VI_ERROR_PARAMETER3);

	/*- Open instrument session ---------------------------------------------*/
	CheckErr (viOpenDefaultRM(&rmSession));
	if ((status = viOpen(rmSession, VISAResourceName, VI_NULL, VI_NULL, vi)) < 0) {
		viClose (rmSession);
		return status;
	}
	
	/*- Configure VISA Formatted I/O ----------------------------------------*/
	CheckErr (viSetAttribute(*vi, VI_ATTR_TMO_VALUE,WUPRONET_TMO_VALUE));
	CheckErr (viSetBuf(*vi, VI_READ_BUF|VI_WRITE_BUF,WUPRONET_BUFFER_SIZE_LARGE));
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
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_BAUD, WUPRONET_BAUD_RATE));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_FLOW_CNTRL, VI_ASRL_FLOW_NONE));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE));   
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_DATA_BITS,8));
		CheckErr (viSetAttribute(*vi, VI_ATTR_ASRL_STOP_BITS,VI_ASRL_STOP_ONE));
	}
	
	/*- Reset instrument ----------------------------------------------------*/
	if (reset)
		CheckErr (wupronet_Reset(*vi));
	else  /* - Send Default Instrument Setup --------------------------------- */
		CheckErr (wupronet_DefaultInstrSetup(*vi));   
Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_Close
 *Purpose:  Takes the instrument offline.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_Close (ViSession vi)
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
 * Function: Error Message                                                   
 * Purpose:  This function translates the error return value from the        
			 instrument driver into a user-readable string.                  
 **************************************************************************************/
ViStatus _VI_FUNC wupronet_ErrorMessage (ViSession vi, 
										ViInt32 statusCode,
										ViChar errorMessage[])
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViInt32 i;

	static wupronet_tStringValPair statusDescArray[] = {
	{VI_ERROR_PARAMETER1,                   "ERROR: Parameter 1 out of range" },
	{VI_ERROR_PARAMETER2,                   "ERROR: Parameter 2 out of range" },
	{VI_ERROR_PARAMETER3,                   "ERROR: Parameter 3 out of range" },
	{VI_ERROR_PARAMETER4,                   "ERROR: Parameter 4 out of range" },
	{VI_ERROR_PARAMETER5,                   "ERROR: Parameter 5 out of range" },
	{VI_NULL,VI_NULL}
	};

	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidPtr(errorMessage),VI_ERROR_PARAMETER3);
	
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
 *Function: wupronet_Reset
 *Purpose:  Resets the instrument and then sends a set of default setup
			commands to the instrument.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_Reset (ViSession vi)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;

	/*  Initialize the instrument to a known state.  */
	CheckErr (viPrintf(vi, "#I,Z,0;"));
	CheckErr (wupronet_DefaultInstrSetup(vi));
	CheckErr (wupronet_CheckStatus(vi));
Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_RevisionQuery
 *Purpose:  Queries the current instrument firmware revision and instrument
			driver revision. 
			Refer to the Readme file for detailed driver information including 
			modification history.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_RevisionQuery (ViSession vi, 
										  ViChar instrumentDriverRevision[], 
										  ViChar instrumentFirmwareRevision[])
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViChar rdBuf[WUPRONET_BUFFER_SIZE];
	
	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidPtr(instrumentDriverRevision),VI_ERROR_PARAMETER2);
	CheckParam (wupronet_InvalidPtr(instrumentFirmwareRevision),VI_ERROR_PARAMETER3);

	CheckErr (viQueryf(vi,"#V,R,0;","%s",rdBuf));
	strcpy (instrumentFirmwareRevision,rdBuf);
	instrumentFirmwareRevision[strlen(instrumentFirmwareRevision)-1] = '\0';
	strcpy (instrumentDriverRevision,WUPRONET_REVISION);

	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}


/***************************************************************************************
 *Function: wupronet_SelfTest
 *Purpose:  Runs the instrument's self-test routine and returns the test
			results.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_SelfTest (ViSession vi, 
									 ViInt32* selfTestResultCode, 
									 ViChar selfTestResultMessage[])
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViByte rdBuf[WUPRONET_BUFFER_SIZE];

	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidPtr(selfTestResultCode),VI_ERROR_PARAMETER2);
	CheckParam (wupronet_InvalidPtr(selfTestResultMessage),VI_ERROR_PARAMETER3);

	CheckErr (viQueryf(vi,"#T,T,1,1;","%s",rdBuf));
	Scan (rdBuf,"%s>%d",selfTestResultCode);
	Scan (rdBuf,"%s>%s",selfTestResultMessage);
	CheckErr (wupronet_CheckStatus(vi));
Error:
	return status;		
}

/***************************************************************************************
 *Function: wupronet_ConfigureUserParameters
 *Purpose:  Configures the rate, threshold and currency type for the Watts Up device.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ConfigureUserParameters (ViSession vi, 
												ViInt32 rate,
												ViInt32 threshold,
												ViInt32 currency)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	
	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidViInt32Range(rate,0,10000),VI_ERROR_PARAMETER2);
	CheckParam (wupronet_InvalidViInt32Range(threshold,0,1999),VI_ERROR_PARAMETER3);
	CheckParam (wupronet_InvalidViInt32Range(currency,0,1),VI_ERROR_PARAMETER4);
	
	//printf("Sending Command: #U,W,3,%d,%d,%d;\n",rate*WUPRONET_COST_RATE,threshold,currency);    
	CheckErr (viPrintf(vi,"#U,W,3,%d,%d,%d;",rate,threshold,currency));
	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_ConfigureDataLogging
 *Purpose:  Configure the logging type and the interval rate of the data capture for the Watts Up device.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ConfigureDataLogging (ViSession vi, 
												ViInt32 loggingType,
												ViInt32 interval)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViChar loggingName[2];
	
	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidViInt32Range(loggingType,0,2),VI_ERROR_PARAMETER2);
	CheckParam (wupronet_InvalidViInt32Range(interval,0,86400),VI_ERROR_PARAMETER3);

	switch(loggingType) {
		case WUPRONET_VAL_INTERNAL_LOG: strcpy(loggingName,"I");
			break;
		case WUPRONET_VAL_EXTERNAL_LOG: strcpy(loggingName,"E");
			break;
		case WUPRONET_VAL_TCP_LOG: strcpy(loggingName,"T");
			break;
		default: strcpy(loggingName,"");
	}
	  
	CheckErr (viPrintf(vi,"#L,W,3,%s,0,%d;",loggingName,interval));
	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_ConfigureMemoryFullHandling
 *Purpose:  Determines how new data will be recorded once the internal memory has filled up.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ConfigureMemoryFullHandling (ViSession vi, 
													ViInt32 policy)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	
	/*- Check input parameter ranges ----------------------------------------*/
	CheckParam (wupronet_InvalidViInt32Range(policy,0,2),VI_ERROR_PARAMETER2);
		
	CheckErr (viPrintf(vi,"#O,W,1,%d;",policy));
	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_ConfigureItemsToLog
 *Purpose:  Configures which items will be recorded on the Watts Up internal memory.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ConfigureItemsToLog (ViSession vi, ViBoolean Watts,
											ViBoolean Volts, ViBoolean Amps,
											ViBoolean Watt_Hours, ViBoolean Cost,
											ViBoolean Mo_Ave_KWhr, ViBoolean Mo_Ave_Cost,
											ViBoolean Max_Watts, ViBoolean Max_Volts, 
											ViBoolean Max_Amps,ViBoolean Min_Watts, 
											ViBoolean Min_Volts,ViBoolean Min_Amps, 
											ViBoolean Power_Factor,ViBoolean Duty_Cycle, 
											ViBoolean Power_Cycle,ViBoolean Line_Freq, 
											ViBoolean Volt_Amps)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	   
	CheckErr (viPrintf(vi,"#C,W,18,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",Watts,Volts,Amps,Watt_Hours, Cost,
																						   Mo_Ave_KWhr,Mo_Ave_Cost,Max_Watts,
																						   Max_Volts,Max_Amps,Min_Watts,
																						   Min_Volts,Min_Amps,Power_Factor,
																						   Duty_Cycle,Power_Cycle,Line_Freq,
																						   Volt_Amps));
	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_ReadMeterData
 *Purpose:  Reads all the data from the internal meter and stores it in Data.
			NOTE: If you use this function in an application remember to free Data when
			you are done with it.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ReadMeterData (ViSession vi, 
										void** Data,
										ViInt32* RecordNum)
{

	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViChar rdBuf[WUPRONET_BUFFER_SIZE];
	ViChar cancel[2] = {'\x18','\0'};
	ViInt32 size = 0;
	ViInt32 i;

	/* Get the record number */
	if((status = wupronet_ReadRecordNum(vi,&size))) return status;

	/* If there are no records, return */
	if(size <= 0) return status;

	ViInt32 readData[WUPRONET_NUM_RECORDS][size];

	/* Make sure the transfer requests have been cleared */
	CheckErr(viPrintf(vi,"%s",cancel));
	Delay(1);
	CheckErr(viClear(vi));

	/* Check if we get the correct header */
	CheckErr(viQueryf(vi,"#D,R,0;","%s",rdBuf));
	if(!strcmp(rdBuf,"")) return WUPRONET_ERROR_EXECUTION_ERROR;

	/* Gaurantee that we will get all the data, this is a last resort loop in case the meter is still */
	/* sending data from a previous #D,R,0; request.                                                  */
	while(rdBuf[1] != 'n') {
		viQueryf(vi,"#D,R,0;","%s",rdBuf);
	}

	/* Parse each record and store it into readData */
	for(i = 0; i < size; i++) {
		CheckErr(viQueryf(vi,"#D,R,0;","%s",rdBuf));
		CheckErr(wupronet_addRecords(size, readData,rdBuf,i));
	}

	/* Copy data off the stack into heap memory */
	*Data = malloc(sizeof(ViInt32)*WUPRONET_NUM_RECORDS*size);
	memcpy(*Data,&readData,sizeof(ViInt32)*WUPRONET_NUM_RECORDS*size);
	*RecordNum = size;

	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_ReadRecordNum
 *Purpose:  Reads the number of records in the Watts Up internal memory. Error handling
			has been disabled for viRead performance, but this function gaurantees success.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ReadRecordNum (ViSession vi,
										ViInt32* RecordNum)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViChar rdBuf[WUPRONET_BUFFER_SIZE];
	ViChar cancel[2] = {'\x18','\0'};

	/* Make sure the transfer requests have been cleared */
	CheckErr(viPrintf(vi,"%s",cancel));
	Delay(1);
	CheckErr(viClear(vi));

	/* Header that contains number of records (size) */
	viQueryf(vi,"#D,R,0;","%s",rdBuf);
	if(!strcmp(rdBuf,"")) return WUPRONET_ERROR_EXECUTION_ERROR;

	/* Gaurantee that we will get all the data, this is a last resort loop in case the meter is still */
	/* sending data from a previous #D,R,0; request.                                                  */
	while(rdBuf[1] != 'n') {
		viQueryf(vi,cancel,"%s",rdBuf);
		viQueryf(vi,"#D,R,0;","%s",rdBuf);
	}

	*RecordNum = wupronet_GetNthParameter(rdBuf,WUPRONET_VAL_RECORD_NUM);

Error:
	return status;

}

/***************************************************************************************
 *Function: wupronet_ReadInterval
 *Purpose:  Reads the current recording interval from the Watts Up device. Error handling
			has been disabled for viRead performance, but this function gaurantees success.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ReadInterval (ViSession vi,
									ViInt32* Interval)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViChar rdBuf[WUPRONET_BUFFER_SIZE];
	ViChar cancel[2] = {'\x18','\0'};

	/* Make sure the transfer requests have been cleared */
	CheckErr(viPrintf(vi,"%s",cancel));
	Delay(1);
	CheckErr(viClear(vi));

	viQueryf(vi,"#S,R,0;","%s",rdBuf);
	if(!strcmp(rdBuf,"")) return WUPRONET_ERROR_EXECUTION_ERROR;

	/* Gaurantee that we will get all the data, this is a last resort loop in case the meter is still */
	/* sending data from a previous #D,R,0; request.                                                  */
	while(rdBuf[1] != 's') {
		viQueryf(vi,cancel,"%s",rdBuf);
		viQueryf(vi,"#S,R,0;","%s",rdBuf);
	}

	*Interval = wupronet_GetNthParameter(rdBuf,WUPRONET_VAL_INTERVAL);

Error:
	return status;

}

/***************************************************************************************
 *Function: wupronet_ResetMeterData
 *Purpose:  Clears all the data from internal memory.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_ResetMeterData (ViSession vi)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	   
	CheckErr (viPrintf(vi,"#R,W,0;"));
	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/***************************************************************************************
 *Function: wupronet_SaveLogFile
 *Purpose:  Saves the internal meter data to a file that is recognized by other Watts Up
			software and programs.
 ***************************************************************************************/
ViStatus _VI_FUNC  wupronet_SaveLogFile (ViSession vi, 
									ViChar Path[],
									void* Data,
									ViInt32 RecordNum)
{
	/*Define local variables.*/
	ViStatus status = VI_SUCCESS;
	ViInt32 formats[18] = {2,3,3,2,3,2,3,2,2,3,2,3,3,1,1,1,1,3};
	ViReal64 percents[18] = {10,10,1000,10,1000,1000,1000,10,10,1000,10,10,1000,1,1,1,10,10};
	ViChar format[64];
	ViChar subChar[2] = {'\x1A','\0'};
	ViInt32 Interval = 0;
	ViReal64 Time = 0;
	ViInt32 i = 0;
	ViInt32 j = 0;
	
	/* Manual error checking, because goto statements would skip initialization of newData[][] */
	if((status = wupronet_ReadInterval(vi,&Interval))) return status;

	/* Get the data from Data which is a void* and put it into a usuable array */
	ViInt32 newData[18][RecordNum];
	memcpy(newData,(ViInt32*)Data,sizeof(ViInt32)*18*RecordNum);

	/* Output the data in the exact format as Watts Up USB software */
	FILE* fp = fopen(Path,"w+");
	fprintf(fp, "%s\n", "Time\tWatts\tVolts\tAmps\tWattHrs\tCost\tAvg Kwh\tMo Cost\tMax Wts\tMax Vlt\tMax Amp\tMin Wts\tMin Vlt\tMin Amp\tPwr Fct\tDty Cyc\tPwr Cyc\n");
	for(i = 0; i < RecordNum; i++) {
		Time = i*((ViReal64)Interval/(ViReal64)WUPRONET_DAY_IN_SECONDS);
		fprintf(fp, "%.8f\t", Time);
		for(j = 0; j < 18; j++) {
			if(j == 17) sprintf(format, "%%.%df",formats[j]);
			else sprintf(format, "%%.%df\t",formats[j]);
			fprintf(fp, format, (ViReal32)(newData[j][i]/percents[j]));
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "%s", subChar);
	fclose(fp);

	CheckErr (wupronet_CheckStatus(vi));

Error:
	return status;
}

/*************************************************************************************************/
/* Function: Boolean Value Out Of Range - ViBoolean                                              */
/* Purpose:  This function checks a Boolean to see if it is equal to VI_TRUE or VI_FALSE.        */
/*           If the value is out of range, the return value is VI_TRUE, otherwise the return     */
/*           the return value is VI_FALSE.                                                       */
/*************************************************************************************************/
static ViBoolean wupronet_InvalidViBooleanRange (ViBoolean val)
{
	return ((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                                    */
/* Purpose:  This function checks a long signed integer value to see if it lies between a        */
/*           minimum and maximum value.  If the value is out of range, the return value is       */
/*           VI_TRUE, otherwise the return value is VI_FALSE.                                    */
/*************************************************************************************************/
static ViBoolean wupronet_InvalidViInt32Range (ViInt32 val, ViInt32 min, ViInt32 max)
{
	return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Real (Double) Value Out Of Range - ViReal64                                         */
/* Purpose:  This function checks a real (double) value to see if it lies between a minimum      */
/*           and maximum value.  If the value is out of range, the return value is VI_TRUE,      */
/*           otherwise the return value is VI_FALSE.                                             */
/*************************************************************************************************/
static ViBoolean wupronet_InvalidViReal64Range (ViReal64 val, ViReal64 min, ViReal64 max)
{
	return ((val < min || val > max) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Pointer value is VI_NULL - void *                                                   */
/* Purpose:  This function checks an output parameter (pointer) to see if its value is VI_NULL.  */
/*           If the value is VI_NULL, the return value is VI_TRUE, otherwise the return value    */
/*           is VI_FALSE.                                                                        */
/*************************************************************************************************/
static ViBoolean wupronet_InvalidPtr (void *value)
{
	return ((value == VI_NULL) ? VI_TRUE : VI_FALSE);
}

/*************************************************************************************************/
/* Function: Add records from str[] into data[][]                                                */
/*************************************************************************************************/
static ViStatus wupronet_addRecords(ViInt32 size, ViInt32 data[][size], ViChar str[], ViInt32 index) {
	ViStatus status = VI_SUCCESS;

	ViChar * entry;
	ViInt32 val = 0;
	ViInt32 count = 0;
	entry = strtok(str," ,;");
	while(entry != NULL) {
		
		/* Only grab the data in between the header info */
		if(count > 2 && count < 21) {
			val = atoi(entry);
			data[count - 3][index] = val;
		}
		entry = strtok(NULL," ,;");
		count++;
	}

Error:
	return status;
}

/*************************************************************************************************/
/* Function: Find the Nth parameter                                                              */
/* Purpose:  This function parses the specified parameter from the rdBuf[] and returns that      */
/*           value.                                                                              */
/*************************************************************************************************/
static ViInt32 wupronet_GetNthParameter(ViChar rdBuf[], ViInt32 n) {
	ViInt32 val = 0;
	ViInt32 count = 0;
	ViChar * entry = strtok(rdBuf," ,;");

	while(entry) {
		if(count < n) {
			val = atoi(entry);
			count++;
		}
		entry = strtok(NULL," ,;");
	}
	return val;
}


/*****************************************************************************/
/*----------- INSERT INSTRUMENT-DEPENDENT UTILITY ROUTINES HERE -------------*/
/*****************************************************************************/

/*****************************************************************************************************/
/* Function: Default Instrument Setup                                                                */
/* Purpose:  This function sends a default setup to the instrument.  This function is called by      */
/*           the wupronet_reset operation and by the wupronet_init function if the reset option has    */
/*           not been selected.  This function is useful for configuring any  instrument settings    */
/*           that are required by the rest of the  instrument driver functions such as turning       */
/*           headers ON or OFF or using the long or short form for commands, queries, and data.      */
/*****************************************************************************************************/
ViStatus wupronet_DefaultInstrSetup (ViSession instrSession)
{
	ViStatus status = VI_SUCCESS;

	return status;
}

/***************************************************************************************
 * Function: wupronet_CheckStatus
 *
 * Purpose:  This function check if there is command error or command execution error by
 *           check the Event Status Register of the instrument.
 ***************************************************************************************/
ViStatus wupronet_CheckStatus (ViSession vi)
{
	ViStatus    status = VI_SUCCESS;
	ViUInt32    esrValue = 0;

	/*---------------- Check if any error or message bit was asserted -------*/
	if ((esrValue & WUPRONET_ESR_QUERY_ERROR) != 0)
	{
		CheckErr (WUPRONET_ESR_QUERY_ERROR);
	}
	if ((esrValue & WUPRONET_ESR_DEVICE_DEPENDENT_ERROR) != 0)
	{
		CheckErr (WUPRONET_ERROR_DEVICE_DEPENDENT_ERROR);
	}
	if ((esrValue & WUPRONET_ESR_EXECUTION_ERROR) != 0)
	{
		CheckErr (WUPRONET_ERROR_EXECUTION_ERROR);
	} 
	if ((esrValue & WUPRONET_ESR_COMMAND_ERROR) != 0)
	{
		CheckErr (WUPRONET_ERROR_COMMAND_ERROR);
	}

Error:
	return status;
}

/*****************************************************************************
 *-------------------------- End Instrument Driver Source Code --------------*
 *****************************************************************************/
