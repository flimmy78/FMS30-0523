//==========================================================================;
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
//==========================================================================;
//                    IMVOUTPUTDEVICES.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
#ifndef IMVOUTPUTDEVICES_H
#define IMVOUTPUTDEVICES_H

interface  IMvOutputDevices : public IUnknown 
{
public:

    virtual HRESULT __stdcall GetOutputDeviceCount(unsigned long * out_pulDeviceCount) = 0;

    virtual HRESULT __stdcall EnumerateOutputDevices(EMvOutputDeviceType * out_paeInputDeviceType[],
            char * out_paszInputDeviceDescription[], unsigned long in_ulArraySize) = 0;

     virtual HRESULT __stdcall SetVideoOutputDevice(unsigned int in_uiVideoDeviceIndex) = 0;

    virtual HRESULT __stdcall ReleaseCurrentOutputDevice() = 0;
};


#endif //IMVOUTPUTSELECTION_H
