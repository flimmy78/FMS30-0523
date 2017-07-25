//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvTimeSpanEventObserver.h $
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


#ifndef CMvTimeSpanEventObserver_h_h
#define CMvTimeSpanEventObserver_h_h

#include "mvObserver.h" //For CMvObserver

#include "mvManagerDefinitions.h"

/*
*	CMvTimeSpanEventObserver
Header: "mvTimeSpanEventObserver.h"
Library: "mvManagerTools.lib"
Observer base class that observes time span events. To observe a time span event, the user has to derive an object from it and implement its Notify function.
void AddObservedTimeSpanEvent( const int in_iTimeSpanEventID);
Adds a time span event to the list of time span events the observer will be notified on.
Parameters
in_iTimeSpanEventID
ID of the time span event that has been returned during registration.
void RemoveObservedTimeSpanEvent( const int in_iTimeSpanEventID);
Removes a time span event to the list of time span events the observer will be notified on.
Parameters
in_iTimeSpanEventID
ID of the time span event that has been returned during registration.
virtual void Notify( const int in_iTimeSpanEventSignaledID, const EMvTimeSpanSpecification in_eTimeSpanSpecification ) = 0;
Notify function the user-derived class must implement. This function will be a called when one of the time span events of the observer has been set.
Parameters
in_iTimeSpanEventID
ID of the time span event that was set.
in_eTimeSpanSpecification
enumeration to inform whether it is the start, stop, or still event of the Time Span.
*/
class CMvTimeSpanEventObserver : public CMvObserver
{
	
public:
	CMvTimeSpanEventObserver();

	void AddObservedTimeSpanEvent( const int in_iTimeSpanEventID);
	void RemoveObservedTimeSpanEvent( const int in_iTimeSpanEventID);

protected:
	virtual void SubNotify( const IMvObservationCondition* in_pIObservationCondition, const CMvSubjectContext* in_poSubjectContext );

protected:
	//User must implement the following callback function
	virtual void Notify( const int in_iTimeSpanEventSignaledID, const EMvTimeSpanSpecification in_eTimeSpanSpecification ) = 0;

};

#endif
