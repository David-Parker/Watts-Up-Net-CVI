        ��  ��                  �       �� ��     0 	        <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" />|      �� ��     0 	        |4   V S _ V E R S I O N _ I N F O     ���                 ?                        �   S t r i n g F i l e I n f o   �   0 4 0 9 0 4 b 0   &   C o m p a n y N a m e     N I     H   F i l e D e s c r i p t i o n     W U S   ( D e b u g   x 8 6 )   (   F i l e V e r s i o n     1 . 0   (   I n t e r n a l N a m e   W U S   L   L e g a l C o p y r i g h t   C o p y r i g h t   �   N I   2 0 1 4   8   O r i g i n a l F i l e n a m e   W U S . d l l   .   P r o d u c t N a m e     N I   W U S     ,   P r o d u c t V e r s i o n   1 . 0   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	��  X   C V I D L L P R O T O T Y P E S   C V I D L L E X P O R T S         0 	        long WUS_CheckStatus(unsigned long vi);
long WUS_Close(unsigned long vi);
long WUS_DefaultInstrSetup(unsigned long instrSession);
long WUS_ErrorMessage(unsigned long vi, long statusCode, char *errorMessage);
long WUS_ErrorQuery(unsigned long vi, long *errorCode, char *errorMessage);
long WUS_Initialize(char *VISAResourceName, unsigned short IDQuery, unsigned short reset, unsigned long *vi);
long WUS_Reset(unsigned long vi);
long WUS_RevisionQuery(unsigned long vi, char *instrumentDriverRevision, char *instrumentFirmwareRevision);
long WUS_SelfTest(unsigned long vi, long *selfTestResultCode, char *selfTestResultMessage);
long WUS_Wait(unsigned long vi);
           �� ��     0	                                        