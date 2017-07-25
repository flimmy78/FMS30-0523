//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvMessageIF.h $
/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

#ifndef IMvMessage_h_h
#define IMvMessage_h_h

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <initguid.h> //For DEFINE_GUID
   #include <unknwn.h> //For IUnknown
   #include <winerror.h> //For HRESULT
#endif   

#include "mvMessageStructure.h"

/**
 * This interface is used to retrieve information about the message. To create message, the user will have to link with the lib and call new on a CMvMessage.
 * A message consists of the following (which must be given during construction and are constant):
 * ?	m_eSeverity : EMvMessageSeverity
 * Flag if Fatal Error, Non-Fatal Error, or normal message.
 * ?	m_eInterpretation : EMvMessageInterpretation
 * Interpretation to allow us to interpret the message code.
 * ?	m_lMessageCode : long
 * Such as the actual HRESULT
 * ?	m_pIMessageInfo : IUnknown
 * Extra Message Info. This parameter can be NULL for messages that do not wish to report specific errors. Otherwise, any interface can be passed to the construction of the CMvMessage. As a rule, we will have one interface constant for each type of message. For example, disk full errors will take a IMvPositionInfo parameter. When retrieving the error, the user will retrieve the Message info as an IUnknown*. He will then Query it for the IMvPositionInfo interface and thus have access to the Position of the graph at the time of the error, the node ID and the sub-cutlist ID.
 */
interface IMvMessage
{
	
public:
	virtual HRESULT __stdcall GetContent( EMvMessageSeverity* out_peSeverity, EMvMessageInterpretation* out_peInterpretation, long* out_plMessageCode, IUnknown** out_ppIMessageInfo ) const = 0;

	virtual EMvMessageSeverity __stdcall GetSeverity( ) const = 0;	
	virtual EMvMessageInterpretation __stdcall GetInterpretation( ) const = 0;
	virtual long __stdcall GetMessageCode( ) const = 0;
	virtual HRESULT __stdcall GetMessageInfo( IUnknown** out_ppIMessageInfo ) const = 0;

	virtual SMvDebugInfo __stdcall GetDebugInfo( ) const = 0;	
	
	#ifdef LINUX_PLATFORM
	   virtual ~IMvMessage() {};
	#endif
};

#endif
