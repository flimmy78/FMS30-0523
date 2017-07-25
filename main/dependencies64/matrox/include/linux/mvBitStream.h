
#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_

//#include <windows.h>
//#include "mvTypes.h"
#ifndef ASSERT
//   #include <crtDbg.h>
//   #include <assert.h> // this defines the lower case assert
   #define ASSERT _ASSERTE
#endif
#include "mvErrors.h"
#include "mvThread.h"


class CMvMPEGParserException : public CMvBaseException
{
public:
   // Constructor
   explicit CMvMPEGParserException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {};
};



class CMpegBitStream
{
public:
   // constructors

   CMpegBitStream
   ( 
      void 
   );

   CMpegBitStream
   ( 
      unsigned char *pucSrcBuffer,   // [in] the memory
      unsigned long ulSrcBufferSize,
      unsigned long ulStartBitLocation = 0
   );

   CMpegBitStream
   (
      CMpegBitStream & bitstream 
   );

   CMpegBitStream
   (
      CMpegBitStream * pbitstream 
   );


   ~CMpegBitStream();

   uint64_t GetBitOffset()
   {
      return m_dlBitOffset ;
   };

public:

   //member functions to manage the bitstream
   void operator++(int);
   void operator+=( uint64_t dlBitOffset );
   void operator= ( uint64_t dlBitOffset );
   void operator= ( CMpegBitStream &bitstream );

   operator uint32_t ();
   operator BYTE();
   operator uint64_t ();

   // get some number of bits from current position.
   HRESULT GetData
   ( 
      unsigned long   ulBits ,    // [in]Number of bits to get.
      LPVOID  pVoid       // [in/out] memory to hold the data .
   );

   unsigned long GetBufferSize(){return m_ulSrcBufferSize;};

protected:

   // the memory for the bitstream 
   unsigned char     *m_pucSrcBuffer ;    
   unsigned long     m_ulSrcBufferSize;
// CMvCriticalSection                 m_Lock ;

   // current bit offset ;
   uint64_t         m_dlBitOffset ;
};


inline unsigned char ReadBits8(CMpegBitStream * io_poBitStream, unsigned long ulBitCount, bool bThrowOnError = true)
{
   ASSERT(ulBitCount <= 8);
   unsigned char ucVal = 0; 

   HRESULT hrs = io_poBitStream->GetData(ulBitCount, &ucVal); 
   if (FAILED(hrs) && bThrowOnError)
   {
      throw CMvMPEGParserException("MPEG Parser error");
   }

   *io_poBitStream += ulBitCount;
   return ucVal;
}

inline uint16_t ReadBits16(CMpegBitStream * io_poBitStream, unsigned long ulBitCount, bool bThrowOnError = true)
{
   ASSERT(ulBitCount <= 16);
   uint16_t usVal = 0; 
   
   HRESULT hrs = io_poBitStream->GetData(ulBitCount, &usVal); 
   if (FAILED(hrs) && bThrowOnError)
   {
      throw CMvMPEGParserException("MPEG Parser error");
   }

   *io_poBitStream += ulBitCount;
   return usVal;
}

inline unsigned long ReadBits32(CMpegBitStream * io_poBitStream, unsigned long ulBitCount, bool bThrowOnError = true)
{
   ASSERT(ulBitCount <= 32);
   unsigned long ulVal = 0; 
   
   HRESULT hrs = io_poBitStream->GetData(ulBitCount, &ulVal); 
   if (FAILED(hrs) && bThrowOnError)
   {
      throw CMvMPEGParserException("MPEG Parser error");
   }

   *io_poBitStream += ulBitCount;
   return ulVal;
}

template <typename __type__>
inline HRESULT ReadBits(CMpegBitStream & io_poBitStream, unsigned long in_ulBitCount, __type__ & out_value)
{
   ASSERT(in_ulBitCount <= (sizeof(out_value) * 8));
   out_value = 0;

   HRESULT hrs = io_poBitStream.GetData(in_ulBitCount, &out_value);

   if (SUCCEEDED(hrs))
   {
      io_poBitStream += in_ulBitCount;
   }
   else
   {
      hrs = MV_E_INVALID_DATA;
   }

   return hrs;
}




#endif