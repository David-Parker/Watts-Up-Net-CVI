s��         �/     v�  �   �   ����                               WUS                             Watts Up Series                                                                                       � � ��ViInt16  �  � ��ViInt32  � � ��ViUInt16  � � ��ViUInt32  � � ��ViReal64     	�  ViInt16[]     	�  ViInt32[]     
�  	ViReal64[]     � ��ViRsrc  � 	� 	��ViSession     �  ViChar[]  �  � ��ViStatus  � 	� 	��ViBoolean     � 	 
ViBoolean[]     � ��ViConstString  � � ��ViInt8  � � ��ViUInt8     	�  ViUInt8[]     
�  	ViUInt16[]     
�  	ViUInt32[]  � � ��ViReal32     
�  	ViReal32[]     �  ViInt8[]  � � ��ViInt64  �   ��ViUInt64     	  ViInt64[]     
  	ViUInt64[]  s    This instrument module provides programming support for the Stanford Research CG635 2.05 GHz Synthesized Clock Generator.  The module is divided into the following functions:
      
Functions/Classes:
      
(1) Initialize:
This function initializes the instrument and sets it to a default configuration.

(2) Action/Status Functions: (Class)
This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.
      
(3) Configuration Functions: (Class)
This class of functions configures the instrument by setting acquisition and system configuration parameters.
      
(4) Utility Functions: (Class)
This class of functions provides lower level functions to communicate with the instrument, and change instrument parameters.
      
(5) Close:
This function takes the instrument offline.    �    This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.

Functions:

(1) Step Up or Down:
Steps up or down on the selected component. Will increase or decrease the value by the number specified by the step size.

(2) Wait:
Waits until all previosuly queued commands have completed finishing before preceeding.    3    This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.

Functions (Subclasses):

(1) Configure Data Logging:
Configure the logging type and the interval rate of the data capture for the Watts Up device.

(2) Configure Memory Full Handling:
TODO

(3) Configure User Parameters:
Configures the rate, threshold and currency type for the Watts Up device.

(4) Configure Items To Log:
Configures which items to log in the internal storage of the Watts Up Meter.     w    This class includes configurations specific to the Watts Up .Net device.

Functions:

(1) TODO:
TODO

(2) TODO:
TODO
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

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    � U   �  �    Resource Name                     < U � �  �    Reset                             � �  �  �    Instrument Handle                 ` �_���  �    Status                          ����  w��                                            "GPIB0::22::INSTR"   True 1 False 0    	           	           FCopyright 2014 National Instruments Corporation. All rights reserved.    �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    �   �  �    Instrument Handle                 :����  �    Status                                 	           �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
0: Internal     _   �  �    Instrument Handle                  �����  �    Status                            %� {  �  �    Interval                          '] %  � �    Logging Type                           	           0               (Internal 0 External 1 TCP (.Net only) 2    R    Determines how new data will be recorded once the internal memory has filled up.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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

<b>Valid Values:</b>
0: Stop
1: Overwrite
2: Automatic

Default Value:
0: Stop

Description:
0: Stop - Once the internal memory is full, the Watts Up device will stop recording data.

1: Overwrite - Once the internal memory is full, the Watts Up device will start to overwrite</b> the earliest recorded data (this data will be lost and output might not be as expected).

2: Automatic - Once the internal memory is full, the Watts Up device will condense all the current data. At every memory-full condition, the interval is doubled and the logged data is condensed by one-half. Note that the precision the data previously had will be lost during this compression.    )d   �  �    Instrument Handle                 *����  �    Status                            .� 7  � �    Memory Full Handling Policy            	                      Stop 0 Overwrite 1 Automatic 2    �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    2~ %  �  �    Instrument Handle                 3����  �    Status                          ���� % % �  �    Rate                            ���� p % �  �    Threshold                       ���� %� � �    Currency                               	           0    0               Dollar 0 Euro 1    �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    9   �  �    Instrument Handle                 9�����  �    Status                          ���� W� �  �    RecordNum                              	           	            �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    ?%   �  �    Instrument Handle                 ?�����  �    Status                          ���� O� �  �    Interval                               	           	            �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    E   �  �    Instrument Handle                 E�����  �    Status                                 	           �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    J�   �  �    Instrument Handle                 Km����  �    Status                          ���� Q�    �    Data                            ���� �� �  �    Record Count                           	           
        0    	            F    This function reads an error code from the instrument's error queue.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     O    This control returns the error code read from the instrument's error queue.

     E    This control interprets the error code as a user readable string. 
    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    Qc"   �  �    Instrument Handle                 R  ]  �  �    Error Code                        RW _� �  �    Error Message                     R�����  �    Status                                 	            	           	           �    This function takes the Status Code returned by the instrument driver functions, interprets it and returns it as a user readable string.      �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     $    This return value is always zero.
     V    This control accepts the Status Code returned from the instrument driver functions.
     T    This control returns the interpreted Error Code as a user readable message string.    X�"   �  �    Instrument Handle                 Y{{���  �    Status                            Y� >  �  �    Error Code                        Z >z �  �    Error Message                          	               	            Y    Resets the instrument and then sends a set of default setup commands to the instrument.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    [�"   �  �    Instrument Handle                 \S����  �    Status                                 	           �    Queries the current instrument firmware revision and instrument driver revision.

Refer to the Readme file for detailed driver information including modification history.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     ?    This control returns the Instrument Driver Software Revision.     8    This control returns the Instrument Firmware Revision.    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    b,"   �  �    Instrument Handle                 b� O  �  �    Instrument Driver Revision        c W� �  �    Instrument Firmware Revision      cP����  �    Status                                 	           	           	           G    Runs the instrument's self-test routine and returns the test results.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None     �    Contains the value returned from the instrument self test.  Zero means success.  For any other code, see the instrument's operation manual.     �    Returns the self-test response ViChar Array from the instrument. Since this instrument does return a test result message, we just copy the test result code.
    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    iF"   �  �    Instrument Handle                 i� A  �  �    Self Test Result Code             jx A� �  �    Self Test Result Message          k����  �    Status                                 	            	           	               Takes the instrument offline.     �    The ViSession handle that you obtain from the WUS_Initialize function. The handle identifies a particular instrument session.

Default Value:  None    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the WUS_ErrorMessage function to obtain the most recent error information.

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
BFFC0000 to BFFCFFFF     VXIPnP   Driver Errors    p�"   �  �    Instrument Handle                 q�����  �    Status                                 	        ����         &               K.        Initialize                                                                                                                              ����       ����  �             K.        ResetMeterData                                                                                                                          ����       ����  '�             K.        ConfigureDataLogging                                                                                                                    ����       ����  )j              K.        ConfigureItemsToLog                                                                                                                     ����         )
  1�             K.        ConfigureMemoryFullHandling                                                                                                             ����       ����  7�             K.        ConfigureUserParameters                                                                                                                 ����       ����  >P             K.        ReadRecordNum                                                                                                                           ����       ����  DS             K.        ReadInterval                                                                                                                            ����       ����  JV             K.        TestCommands                                                                                                                            ����       ����  P             K.        ReadMeterData                                                                                                                           ����         Q  WO             K.        ErrorQuery                                                                                                                              ����         XK  Za             K.        ErrorMessage                                                                                                                            ����         [U  `�             K.        Reset                                                                                                                                   ����         ax  g�             K.        RevisionQuery                                                                                                                           ����         h�  o�             K.        SelfTest                                                                                                                                ����         p�  v5             K.        Close                                                                                                                                         �                                                                                     �Initialize                                                                          sAction/Status Functions                                                              �Reset Meter Data                                                                    Configure Functions                                                                  �Configure Data Logging                                                               �Configure Items To Log                                                               �Configure Memory Full Handling                                                       �Configure User Parameters                                                           
U.Net                                                                              ����                                                                                  ����Data                                                                                 �Read Record Num                                                                      �Read Interval                                                                        �Test Commands                                                                        �Read Meter Data                                                                     
�Utility Functions                                                                    �Error Query                                                                          �Error Message                                                                        �Reset                                                                                �Revision Query                                                                       �Self Test                                                                            �Close                                                                           