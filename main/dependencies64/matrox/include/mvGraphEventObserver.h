//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvGraphEventObserver.h $
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


#ifndef CMvGraphEventObserver_h_h
#define CMvGraphEventObserver_h_h

#include "mvMessageStackIF.h" //For IMvMessage
#include "mvObserver.h" //For CMvObserver

/*
*	CMvGraphEventObserver
Header: "mvGraphEventObserver.h"
Library: "mvManagerTools.lib"
Observer base class that observes all graph event of a single graph based on an ID (specified in the SetObservedGraph() function). To observe a graph event, the user has to derive an object from it and implement its Notify function.
Data members
m_uiGraphIdToObserve
Graph ID of the graph observed by the observer.
bool SetObservedGraph (const unsigned int in_uiGraphIdToObserve);
Function to set the ID of the graph that is to be observed. If the observer is added to the AEM before this function has been called, the call will fail. If this function is called the user-derived class must implement. This function will be a called when a module sends a graph event with the ID of the observer.
Parameters
in_uiGraphIdToObserve
Graph ID of the graph observed by the observer.
Return values
bool values:
*	True if the ID has been set successfully.
*	False if the supplied ID is 0 or if this function is called more than once.
virtual void Notify( IMvMessageStack* io_pIMessageStack, const bool in_bStateChanged ) = 0;
Notify function the user-derived class must implement. This function will be a called when a module sends a graph event with the ID of the observer.
Parameters
io_pIMessageStack
Message stack of the caller at the time of the call. It should contain the message that triggered the caller to decide to notify the observers. Even though it is a message stack, it not part of the message context at the time of the Notification (see “Message Manager”)
in_bStateChanged
Indicates whether or not the graph has changed state (has stopped) as a result of the event.
*/
class CMvGraphEventObserver : public CMvObserver
{
	
public:
	CMvGraphEventObserver();
	~CMvGraphEventObserver();

	bool SetObservedGraph ( const unsigned int in_uiGraphIdToObserve );

	bool RemoveObservedGraph ( const unsigned int in_uiGraphIdToRemove );

protected:
	virtual void SubNotify( const IMvObservationCondition* in_pIObservationCondition, const CMvSubjectContext* in_poSubjectContext );

	//User must implement the following callback function
	virtual void Notify( IMvMessageStack* io_pIMessageStack, const bool in_bStateChanged ) = 0;
	
private:
	bool __stdcall IsReady();

	unsigned int m_uiGraphIdToObserve;

	//To remove Warnings
	void operator=( CMvGraphEventObserver &){}
};

#endif
