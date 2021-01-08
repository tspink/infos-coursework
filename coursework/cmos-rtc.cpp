/*
 * CMOS Real-time Clock
 * SKELETON IMPLEMENTATION -- TO BE FILLED IN FOR TASK (1)
 */

/*
 * STUDENT NUMBER: s
 */
#include <infos/drivers/timer/rtc.h>

using namespace infos::drivers;
using namespace infos::drivers::timer;

class CMOSRTC : public RTC {
public:
	static const DeviceClass CMOSRTCDeviceClass;

	const DeviceClass& device_class() const override
	{
		return CMOSRTCDeviceClass;
	}

	/**
	 * Interrogates the RTC to read the current date & time.
	 * @param tp Populates the tp structure with the current data & time, as
	 * given by the CMOS RTC device.
	 */
	void read_timepoint(RTCTimePoint& tp) override
	{
		// FILL IN THIS METHOD - WRITE HELPER METHODS IF NECESSARY
	}
};

const DeviceClass CMOSRTC::CMOSRTCDeviceClass(RTC::RTCDeviceClass, "cmos-rtc");

RegisterDevice(CMOSRTC);
