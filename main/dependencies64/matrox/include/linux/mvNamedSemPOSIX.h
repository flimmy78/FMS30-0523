#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

#include <string>
#include <memory>

#include "mvHResult.h"
#include "mvLinuxDefinitions.h"

class CMvNamedSemPOSIX
{
 public:
  ~CMvNamedSemPOSIX();

   const char* GetName();

   bool Post();
   bool Wait(unsigned long in_ulTimeoutInMs);
   bool WasAlreadyCreated();

   static HRESULT STATIC_Create(const char* in_kszFilename, unsigned int in_uiInitialCount, std::shared_ptr<CMvNamedSemPOSIX>* out_rNamedSemPOSIX);
   static bool STATIC_Destroy(const char* in_kszFilename);

private:
   CMvNamedSemPOSIX(const char* in_kszFilename, sem_t* in_i32Handle, bool in_bWasAlreadyCreated);
   CMvNamedSemPOSIX(const CMvNamedSemPOSIX&);
   CMvNamedSemPOSIX &operator= (const CMvNamedSemPOSIX&);
   
   std::string m_sFilename;
   sem_t* m_i32Handle;
   bool m_bWasAlreadyCreated;
};
