#pragma once

#include <MatroxDSXsdk.h>

namespace caspar {
	namespace matrox {

		struct SdiCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation     sHwInfo;
			std::vector<TMvSmartPtr<IMvSdiVideoOutputConnector> > vecpJSdiVideoOutputConnectors;
			std::vector<TMvSmartPtr<IMvSdiVideoInputConnector> >  vecpJSdiVideoInputConnectors;
		};

		struct SdiIpCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation     sHwInfo;
			std::vector<TMvSmartPtr<IMvSfpIp> > vecpJSfpIp;
			std::vector<TMvSmartPtr<IMvSdiIpOutputConnector> > vecpJSdiIpOutputConnectors;
			std::vector<TMvSmartPtr<IMvSdiIpInputConnector> >  vecpJSdiIpInputConnectors;

		};
	}
}