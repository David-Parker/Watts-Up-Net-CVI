        ��  ��                  �       �� ��     0 	        <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" />|      �� ��     0 	        |4   V S _ V E R S I O N _ I N F O     ���                 ?                        �   S t r i n g F i l e I n f o   �   0 4 0 9 0 4 b 0   &   C o m p a n y N a m e     N I     H   F i l e D e s c r i p t i o n     W U N   ( D e b u g   x 8 6 )   (   F i l e V e r s i o n     1 . 0   (   I n t e r n a l N a m e   W U N   L   L e g a l C o p y r i g h t   C o p y r i g h t   �   N I   2 0 1 4   8   O r i g i n a l F i l e n a m e   W U N . d l l   .   P r o d u c t N a m e     N I   W U N     ,   P r o d u c t V e r s i o n   1 . 0   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	��  X   C V I D L L P R O T O T Y P E S   C V I D L L E X P O R T S         0 	        long WUN_CheckStatus(unsigned long vi);
long WUN_Close(unsigned long vi);
long WUN_ConfigureDataLogging(unsigned long vi, long loggingType, long interval);
long WUN_ConfigureItemsToLog(unsigned long vi, unsigned short Watts, unsigned short Volts, unsigned short Amps, unsigned short Watt_Hours, unsigned short Cost, unsigned short Mo_Ave_KWhr, unsigned short Mo_Ave_Cost, unsigned short Max_Watts, unsigned short Max_Volts, unsigned short Max_Amps, unsigned short Min_Watts, unsigned short Min_Volts, unsigned short Min_Amps, unsigned short Power_Factor, unsigned short Duty_Cycle, unsigned short Power_Cycle, unsigned short Line_Freq, unsigned short Volt_Amps);
long WUN_ConfigureMemoryFullHandling(unsigned long vi, long policy);
long WUN_ConfigureUserParameters(unsigned long vi, long rate, long threshold, long currency);
long WUN_DefaultInstrSetup(unsigned long instrSession);
long WUN_ErrorMessage(unsigned long vi, long statusCode, char *errorMessage);
long WUN_ErrorQuery(unsigned long vi, long *errorCode, char *errorMessage);
long WUN_Initialize(char *VISAResourceName, unsigned short reset, unsigned long *vi);
long WUN_ReadInterval(unsigned long vi, long *Interval);
long WUN_ReadMeterData(unsigned long vi, void **Data, long *RecordNum);
long WUN_ReadRecordNum(unsigned long vi, long *RecordNum);
long WUN_Reset(unsigned long vi);
long WUN_ResetMeterData(unsigned long vi);
long WUN_RevisionQuery(unsigned long vi, char *instrumentDriverRevision, char *instrumentFirmwareRevision);
long WUN_SaveLogFile(unsigned long vi, char *Path, void *Data);
long WUN_SelfTest(unsigned long vi, long *selfTestResultCode, char *selfTestResultMessage);
long WUN_TestCommands(unsigned long vi);
            �� ��     0	                                        