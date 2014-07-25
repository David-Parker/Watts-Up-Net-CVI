s��         �     ��  �   �   ����                               wupronet                        Watts Up PRO Net Series                                                                               � � ��ViInt16  �  � ��ViInt32  � � ��ViUInt16  � � ��ViUInt32  � � ��ViReal64     	�  ViInt16[]     	�  ViInt32[]     
�  	ViReal64[]     � ��ViRsrc  � 	� 	��ViSession     �  ViChar[]  �  � ��ViStatus  � 	� 	��ViBoolean     � 	 
ViBoolean[]     � ��ViConstString  � � ��ViInt8  � � ��ViUInt8     	�  ViUInt8[]     
�  	ViUInt16[]     
�  	ViUInt32[]  � � ��ViReal32     
�  	ViReal32[]     �  ViInt8[]  � � ��ViInt64  �   ��ViUInt64     	  ViInt64[]     
  	ViUInt64[]  �    This instrument module provides programming support for the Watts Up PRO & .Net Watt Meters. The module is divided into the following functions:
      
Functions/Classes:
      
(1) Initialize:
This function initializes the instrument and sets it to a default configuration.

(2) Action/Status Functions: (Class)
This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.
      
(3) Configuration Functions: (Class)
This class of functions configures the instrument by setting acquisition and system configuration parameters.

(4) Data Functions: (Class)
This class of functions acquires data from the instrument and places it into a usable data structure.
      
(4) Utility Functions: (Class)
This class of functions provides lower level functions to communicate with the instrument, and change instrument parameters.
      
(5) Close:
This function takes the instrument offline.    �    This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.

Functions:

(1) Reset Meter Data:
Clears all of the currently logged data in the internal meter memory of the Watts Up device.

(2) Save Log File:
Saves all the data into a formatted file that can be read by the Watts Up USB software.

Note: This VI may take several minutes to complete.    :    This class of functions configures certain properties of the instrument and how data will be recorded.

Functions:

(1) Configure Data Logging:
Configure the logging type and the interval rate of the data capture for the Watts Up device.

(2) Configure Items To Log:
Configures which items to log in the internal storage of the Watts Up Meter.

(3) Configure Memory Full Handling:
Determines how new data will be recorded once the internal memory has filled up.

(4) Configure User Parameters:
Configures the rate, threshold and currency type for the Watts Up device.
    ?    This class of functions reads certain information from the Watts Up device. 

Functions:

(1) Read Interval:
Clears all of the currently logged data in the internal meter memory of the Watts Up device.

(2) Read Meter Data:
Reads the data from the internal meter of the Watts Up device. Outputs a 2D array of values, where each row is its own 1D array of the data points for each different measurement type (Watts,Volts,Amps,etc).

Note: This VI may take several minutes to complete.

(3) Read Record Num:
Reads the number of logged records on the internal Watts Up meter.
    J    This class of functions provides lower level functions to communicate with the instrument, and change instrument parameters.

Functions:

(1) Error Query:
Reads an error code from the instrument's error queue.

(2) Error Message:
This function takes the Status Code returned by the instrument driver functions, interprets it and returns it as a user readable string. 

(3) Reset:
Resets the instrument and then sends a set of default setup commands to the instrument.

(4) Revision Query:
Queries the current instrument firmware revision and instrument driver revision.

(5) Save Recall Instrument Settings:
Recalls or Saves Instrument settings depending on parameter Recall or Save. Recalls or saves from or to the save file Save Number, respectively. 

(6) Self-Test:
Runs the instrument's self-test routine and returns the test results.
    �    Establishes communication with the instrument and optionally performs an instrument identification query and/or an instrument reset.  It also places the instrument in a default state needed for other instrument driver operations.  Therefore, call this function before calling other instrument driver functions for this instrument.  Generally, you need to call the Initialize function only once at the beginning of an application.    W    Pass the resource name of the device to initialize.

Enter the instrument descriptor using the following format:
Interface Type[board index]::Address::INSTR.

Examples:
GPIB:    GPIB::22::INSTR,  GPIB board 0, primary address 22
Serial:  COM1
VISA Alias:  "SampleInstr" - Alias names are configured in MAX

Default Value:  "GPIB0::22::INSTR"    E    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_OFF (0) - Don't Reset
VI_ON  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset, set this control value to VI_FALSE while initializing the instrument.
    �    Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Notes:

(1) This function creates a new session each time you invoke it.  This is useful if you have multiple physical instances of the same type of instrument.

(2) Avoid creating multiple concurrent sessions to the same physical instrument.  Although you can create more than one IVI session for the same resource, it is best not to do so.    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    4 U   �  �    Resource Name                     � U � �  �    Reset                             � �  �  �    Instrument Handle                 � �_���  �    Status                          ����  w��                                            "COM4"   True 1 False 0    	           	           FCopyright 2014 National Instruments Corporation. All rights reserved.    �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    �   �  �    Instrument Handle                 �����  �    Status                                 	           �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors     H    Path to the file for saving the logged data.

Default Value:
C:\WU.txt     �    2D array of data from the Watts Up device. This input should come from the Read Meter Data function.

Default Value:
0 (data will be read from the meter automatically, altering this input will not have any effect)    "�   �  �    Instrument Handle                 #[����  �    Status                            ( %  �  �    Path                              ([ p     �    Data                            ���� �  �  �    Record Number                          	           "C:/WU.txt"        0    �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    �    Set the interval level for the Watts Up device. The interval is in seconds, and specifies how often the Watts Up device will log the data. 

Valid Range:
0 - 86400 s

Default Value:
1 s

Note: The more frequently the instrument records data, the faster the internal memory (if set to internal logging mode) will fill up. Once filled, the configured memory handling policy from Configure Memory Handling.vi will take into effect.     �    Set the logging mode for the Watts Up Device.

Valid Values:
0: Internal
1: External
2: TCP (.Net only)

Default Value:
0: Internal    *k   �  �    Instrument Handle                 +����  �    Status                            /� {  �  �    Interval                          1s %  � �    Logging Type                           	           10               (Internal 0 External 1 TCP (.Net only) 2    �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors     _    Turns On or Off Watts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     _    Turns On or Off Volts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     ^    Turns On or Off Amps for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     d    Turns On or Off Watt Hours for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     ^    Turns On or Off Cost for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     x    Turns On or Off Monthly Average KiloWatt hours for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     n    Turns On or Off Monlthy Average Cost for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     c    Turns On or Off Max Volts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     c    Turns On or Off Max Watts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     b    Turns On or Off Max Amps for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     c    Turns On or Off Min Watts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     c    Turns On or Off Min Volts for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     b    Turns On or Off Min Amps for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     f    Turns On or Off Power Factor for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     d    Turns On or Off Duty Cycle for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     e    Turns On or Off Power Cycle for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     h    Turns On or Off Line Frequency for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On     c    Turns On or Off Volt Amps for internal logging.

Valid Values:
0: Off
1: On

Default Value:
1: On    3!   �  �    Instrument Handle                 3�����  �    Status                            8s #  �       Watts                             8� # > �       Volts                             9A # p �       Amps                              9� # � �       Watt Hours                        : # � �       Cost                              :y #" �       Mo Ave KWhr                       :� #o �       Mo Ave Cost                       ;o #� �       Max Volts                         ;� #� 	�       Max Watts                         <E �  
�       Max Amps                          <� � F �       Min Watts                         = � | �       Min Volts                         =� � � �       Min Amps                          =� � � �       Power Factor                      >] �0 �       Duty Cycle                        >� �r �       Power Cycle                       ?6 �� �       Line Freq                         ?� �� �       Volt Amps                              	          On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0   On 1 Off 0    R    Determines how new data will be recorded once the internal memory has filled up.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    �    Sets the policy for handling the logging of data once the internal memory is full.

Valid Values:
0: Stop
1: Overwrite
2: Automatic

Default Value:
0: Stop

Description:
0: Stop - Once the internal memory is full, the Watts Up device will stop recording data.

1: Overwrite - Once the internal memory is full, the Watts Up device will start to overwrite</b> the earliest recorded data (this data will be lost and output might not be as expected).

2: Automatic - Once the internal memory is full, the Watts Up device will condense all the current data. At every memory-full condition, the interval is doubled and the logged data is condensed by one-half. Note that the precision the data previously had will be lost during this compression.    E�   �  �    Instrument Handle                 F=����  �    Status                            J� 7  � �    Memory Full Handling Policy            	                      Stop 0 Overwrite 1 Automatic 2    �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors     w    Cost per KWH in the set currency, precision in tenths of a penny.

Valid Values:
0 - 10.000 $

Default Value:
0.000 $        Duty cycle threshold. The Watts Up meter will only log values above the specified threshold. This is useful when attempting to monitor specific thresholds of watt usage. For example if the lightbulb of a refrigarator uses 10W and the compressor uses 25W, setting the threshold to 25W would only log data when the compressor is running.

Valid Range:
0  - 1999 W

Default Value:
0 W     z    Configures which currency base the cost will be displayed in.

Valid Values:
0: Dollar
1: Euro

Default Value:
0: Dollar    N� %  �  �    Instrument Handle                 OZ����  �    Status                            T
 % % �  �    Rate                              T� p % �  �    Threshold                         V %� � �    Currency                               	           0    0               Dollar 0 Euro 1    �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    W�%   �  �    Instrument Handle                 Xv����  �    Status                          ���� O� �  �    Interval                               	           	            �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    ]�   �  �    Instrument Handle                 ^�����  �    Status                          ���� Q�    �    Data                            ���� �� �  �    Record Count                           	           
        0    	            �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    d0   �  �    Instrument Handle                 d�����  �    Status                          ���� W� �  �    RecordNum                              	           	            F    This function reads an error code from the instrument's error queue.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     O    This control returns the error code read from the instrument's error queue.

     E    This control interprets the error code as a user readable string. 
    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    j�"   �  �    Instrument Handle                 k- ]  �  �    Error Code                        k� _� �  �    Error Message                     k�����  �    Status                                 	            	           	           �    This function takes the Status Code returned by the instrument driver functions, interprets it and returns it as a user readable string.      �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     $    This return value is always zero.
     V    This control accepts the Status Code returned from the instrument driver functions.
     T    This control returns the interpreted Error Code as a user readable message string.    r"   �  �    Instrument Handle                 r�{���  �    Status                            r� >  �  �    Error Code                        s< >z �  �    Error Message                          	               	            Y    Resets the instrument and then sends a set of default setup commands to the instrument.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    t�"   �  �    Instrument Handle                 u�����  �    Status                                 	           �    Queries the current instrument firmware revision and instrument driver revision.

Refer to the Readme file for detailed driver information including modification history.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    {m"   �  �    Instrument Handle                 |����  �    Status                          ���� p� �  �    Instrument Firmware Revision    ���� p  �  �    Instrument Driver Revision             	           	            	            G    Runs the instrument's self-test routine and returns the test results.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     �    Contains the value returned from the instrument self test.  Zero means success.  For any other code, see the instrument's operation manual.     �    Returns the self-test response ViChar Array from the instrument. Since this instrument does return a test result message, we just copy the test result code.
    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    �
"   �  �    Instrument Handle                 �� A  �  �    Self Test Result Code             �A A� �  �    Self Test Result Message          ������  �    Status                                 	            	           	               Takes the instrument offline.     �    The ViSession handle that you obtain from the wupronet_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the wupronet_ErrorMessage function to obtain the most recent error information.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:

Status    Description
-------------------------------------------------
No defined status codes.

This instrument driver also returns errors and warnings defined by other sources. The following table defines the ranges of additional status codes that this driver can return.

Numeric Range (in Hex)   Status Code Types
-------------------------------------------------
3FFF0000 to 3FFFFFFF     VISA     Warnings
3FFC0000 to 3FFCFFFF     VXIPnP   Driver Warnings

BFFF0000 to BFFFFFFF     VISA     Errors
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    ��"   �  �    Instrument Handle                 �]����  �    Status                                 	        ����         }  g             K.        Initialize                                                                                                                              ����       ����  "?             K.        ResetMeterData                                                                                                                          ����       ����  ):             K.        SaveLogFile                                                                                                                             ����       ����  2              K.        ConfigureDataLogging                                                                                                                    ����       ����  @             K.        ConfigureItemsToLog                                                                                                                     ����         EA  M�             K.        ConfigureMemoryFullHandling                                                                                                             ����       ����  V�             K.        ConfigureUserParameters                                                                                                                 ����       ����  ]&             K.        ReadInterval                                                                                                                            ����       ����  c3             K.        ReadMeterData                                                                                                                           ����       ����  i�             K.        ReadRecordNum                                                                                                                           ����         j=  p�             K.        ErrorQuery                                                                                                                              ����         q}  s�             K.        ErrorMessage                                                                                                                            ����         t�  z?             K.        Reset                                                                                                                                   ����         z�  ��             K.        RevisionQuery                                                                                                                           ����         ��  ��             K.        SelfTest                                                                                                                                ����         ��  �             K.        Close                                                                                                                                         �                                                                                     �Initialize                                                                          �Action/Status Functions                                                              �Reset Meter Data                                                                     �Save Log File                                                                       �Configure Functions                                                                  �Configure Data Logging                                                               �Configure Items To Log                                                               �Configure Memory Full Handling                                                       �Configure User Parameters                                                           
�Data                                                                                 �Read Interval                                                                        �Read Meter Data                                                                      �Read Record Num                                                                     +Utility Functions                                                                    �Error Query                                                                          �Error Message                                                                        �Reset                                                                                �Revision Query                                                                       �Self Test                                                                            �Close                                                                           