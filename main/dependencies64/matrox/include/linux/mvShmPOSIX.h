#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

#include <string>
#include <memory>

#include "mvHResult.h"
#include "mvLinuxDefinitions.h"

class CMvShmPOSIX
{
 public:
  ~CMvShmPOSIX();

   uint32_t GetSize();
   const char* GetName();
   BYTE* GetData();
   bool WasAlreadyCreated();

   static HRESULT STATIC_Create(const char* in_kszFilename, uint32_t in_ui32Size, std::shared_ptr<CMvShmPOSIX>* out_rSShmPosix);
   static bool STATIC_Destroy(const char* in_kszFilename);

private:
   CMvShmPOSIX(const char* in_kszFilename, uint32_t in_size, int32_t in_i32Handle, bool in_bWasAlreadyCreated, BYTE* in_pucRawData);
   CMvShmPOSIX(const CMvShmPOSIX&);
   CMvShmPOSIX &operator= (const CMvShmPOSIX&);

   std::string m_sFilename;
   uint32_t m_ui32Size;
   int32_t m_i32Handle;
   bool m_bWasAlreadyCreated;
   BYTE* m_pucRawData;
};
