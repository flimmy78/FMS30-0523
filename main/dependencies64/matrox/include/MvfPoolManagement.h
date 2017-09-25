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

#pragma once

#include "mvBaseCOM.h"
#include "mvfPoolManagerAPI.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// TMvfPoolAllocator
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

template <class TOp>
class TMvfPoolAllocator : public CMvLightUnknown, public IMvPoolAllocator
{
public:
   TMvfPoolAllocator(wchar_t * in_pwszName) : CMvLightUnknown(in_pwszName, NULL) {};
   virtual ~TMvfPoolAllocator() {};

   //
   // interface IUnknown 
   //
   MVDECLARE_IUNKNOWN;

   //
   // interface IMvPoolAllocator
   //

   unsigned long __stdcall GetSize()
   {
      return (sizeof(TOp));

   };

   HRESULT __stdcall Allocate(IUnknown ** io_pIElement)
   {
      HRESULT   hr;
      TOp     * pOperation;

      // Allocate the new operation
      pOperation = new TOp;

      if (pOperation == NULL)
      {
         return E_FAIL;
      }

      // Get IUnknown interface
      hr = pOperation->QueryInterface(IID_IUnknown, (void **)io_pIElement);

      // Release the settings interface
      pOperation->Release();

      return hr;
   };

private:
   TMvfPoolAllocator(TMvfPoolAllocator&) : CMvLightUnknown(NULL, NULL){}
   void operator=(TMvfPoolAllocator&){}
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// TMvfPoolManager
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

template <class TOp> 
class TMvfPoolManager : public CMvPoolManager
{
public:
   TMvfPoolManager(wchar_t          * in_pwszName,
                   unsigned long      in_ulInitialCount,
                   IMvPoolAllocator * in_pIPoolAllocator)
   : CMvPoolManager(in_pwszName, in_ulInitialCount, in_pIPoolAllocator) {};

   static IMvPoolManager * CreatePoolManager(const wchar_t * in_pwszName,
                                             unsigned long   in_ulInitialCount)
   {
      IMvPoolManager   * pIManager;
      IMvPoolAllocator * pIAllocator;
      wchar_t            wszName[256];

      _snwprintf_s(wszName, _countof(wszName), _countof(wszName)-1, L"%ls - Pool Allocator", in_pwszName);

      pIAllocator = new TMvfPoolAllocator <TOp> (wszName);

      _snwprintf_s(wszName, _countof(wszName), _countof(wszName)-1, L"%ls - Pool Manager", in_pwszName);

      pIManager = new TMvfPoolManager(wszName, in_ulInitialCount, pIAllocator);

      pIAllocator->Release();

      return pIManager;
   }

   virtual ~TMvfPoolManager() {};
};


