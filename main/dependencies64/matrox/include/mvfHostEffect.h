//$Archive: /VP/FLEXVIDEO/LIBS/mvfHostEffectBase/inc/mvfHostEffect.h $
//
//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved. 
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

#ifndef MVFHOSTEFFECT_H
#define MVFHOSTEFFECT_H

#include "MvFlexAPI.h"

//
// Summary:
//    This base class provides the basic tools for creating a host-based effect.
//    This class gives access to an instance of synchronous buffer engines for the derived classes (host-based effects).
//
class CMvfHostEffect
{
public:
   CMvfHostEffect(unsigned long  in_ulThreadPoolIndex,
                  unsigned long  in_ulThreadPoolPriority,
                  IMvFlexEngine* in_pIFlexEngine);

   virtual ~CMvfHostEffect() {}

protected:
   IMvSyncBufferEngine* m_pISyncBufferEngine;   // Pointer to the synchronous buffer engine  IMvSyncBufferEngine interface. 
};




#endif   //MVFHOSTEFFECT_H