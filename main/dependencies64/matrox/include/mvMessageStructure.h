//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvMessageStructure.h $
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

#ifndef MV_MESSAGE_STRUCTURE
#define MV_MESSAGE_STRUCTURE

#pragma once

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF ENUMS
//


/**
*  Defines the severity of error messages. 
* <H3>Enumerators:</H3>
* <VAR>keFatalError</VAR>: A fatal error stops the graph.    <BR><BR>
* <VAR>keNonFatalError </VAR>: A non-fatal error does not change the state ofthe graph. <BR><BR>
* <VAR>keMessage </VAR>: A message pertaining to graph issues.      <BR><BR>
* @enum
*/
enum EMvMessageSeverity
{
	keFatalError,
	keNonFatalError,
	keMessage
};

/**
*  Defines the source of the error messages. 
* <H3>Enumerators:</H3>
* <VAR>keOsHRESULT</VAR>: An error from the operating system.    <BR><BR>
* <VAR>keDirectShowSDK </VAR>: An error coming from DirectShow. <BR><BR>
* <VAR>keMatroxError </VAR>: An error coming from Matrox.      <BR><BR>
* @enum
*/
enum EMvMessageInterpretation
{
	keOsHRESULT,
	keDirectShowSDK,
	keMatroxError
};

const int g_iLengthOfFileName = 64;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF STRUCTURES
//


/**
* Provides debugging information for error messages.
* @struct
*/
struct SMvDebugInfo
{
   /**
   * Size of this structure.
   */
	size_t size;

   /**
   * lMatroxPackage
   */
   long lMatroxPackage;

   /**
   * lMatroxFunctionality
   */
   long lMatroxFunctionality;
	
   /**
   * szMatroxSourceFileName
   */
   char szMatroxSourceFileName[g_iLengthOfFileName];
	
   /**
   * iMatroxFileLineNumber
   */
   int iMatroxFileLineNumber;
};

#endif
// END OF INCLUDE

