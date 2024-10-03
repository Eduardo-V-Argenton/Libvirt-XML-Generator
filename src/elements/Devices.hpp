#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "../XmlAble.hpp"
#include "devices/Console.hpp"
#include "devices/Controller.hpp"
#include "devices/Disk.hpp"
#include "devices/Emulator.hpp"
#include "devices/Filesystem.hpp"
#include "devices/GraphicalFrameBuffer.hpp"
#include "devices/HotDev.hpp"
#include "devices/Network.hpp"
#include "devices/Tpm.hpp"
#include "devices/Video.hpp"
#include <string>
#include <vector>

namespace PlaceHolder {
namespace Elements {
namespace DeviceElements {

struct Devices : PlaceHolder::Interfaces::XmlAble {

	PlaceHolder::Elements::Devices::EmulatorElements::Emulator emulator;
	std::vector<PlaceHolder::Elements::Devices::DiskElements::Disk> disks;
	std::vector<PlaceHolder::Elements::Devices::HotDevElements::HotDevUSBSource> hotDevUSBs;
	std::vector<PlaceHolder::Elements::Devices::HotDevElements::HotDevPCISource> hotDevPCIs;
	std::vector<PlaceHolder::Elements::Devices::ControllerElements::Controller>
		controllers;

	std::string getXml() const override;
};
} // namespace DeviceElements
} // namespace Elements
} // namespace PlaceHolder
#endif
