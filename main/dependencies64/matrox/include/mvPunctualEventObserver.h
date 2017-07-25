//$Archive: /VP/END-USER/LIBS/mvManagerTools/inc/mvPunctualEventObserver.h $

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
// changes in specifications and code at any time and without notice. 
// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
// its use; nor for any infringements of patents or other rights of 
// third parties resulting from its use. No license is granted under 
// any patents or patent rights of Matrox Electronic Systems Ltd.
//
//-------------------------------------------------------------------------------

#ifndef CMvPunctualEventObserver_h_h
#define CMvPunctualEventObserver_h_h

#include "mvObserver.h" //For CMvObserver

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base class that observes punctual events. To observe a punctual event, 
//    the user-derived object must implement the CMvPunctualEventObserver::Notify function.
// Remarks:
//    Requires the following libraries: mvManagerTools.lib and mvCommonMechanisms.lib
//
//////////////////////////////////////////////////////////////////////////
class CMvPunctualEventObserver : public CMvObserver
{
	
public:
   //
   // Summary:
   //    This is the constructor of the CMvPunctualEventObserver class.
	CMvPunctualEventObserver();

   //
   // Summary:
   //    Adds an event to the list of punctual events of which the observer will be notified.
	void AddObservedPunctualEvent
      ( 
      const int in_iPunctualEvent // ID of the punctual event that is returned during registration.
      );

   //
   // Summary:
   //    Removes an event from the list of punctual events of which the observer will be notified.
	void RemoveObservedPunctualEvent
      ( 
      const int in_iPunctualEvent // ID of the punctual event that is returned during registration.
      );

protected:
   //
   // Summary:
   //    This method is for Matrox internal purposes only.
	virtual void SubNotify( const IMvObservationCondition* in_pIObservationCondition, const CMvSubjectContext* in_poSubjectContext );
	
protected:

   //
   // Summary:
   //     This is the Notify function that the user-derived class must implement. 
   //     It is called when an observer's punctual event is set.
   // Remarks:
   //    - User must implement this callback function
   virtual void Notify
      ( 
      const int in_iPunctualEvent // ID of the punctual event that is set. 
      ) = 0;
	
};

#endif
