#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "../XmlAble.hpp"
#include "devices/Console.hpp"
#include "devices/Controller.hpp"
#include "devices/Disk.hpp"
#include "devices/Emulator.hpp"
#include "devices/Filesystem.hpp"
#include "devices/Graphics.hpp"
#include "devices/HotDev.hpp"
#include "devices/Network.hpp"
#include "devices/Tpm.hpp"
#include "devices/Video.hpp"
#include <string>
#include <vector>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace DeviceElements {

struct Devices : LibvirtXMLGenerator::Interfaces::XmlAble {

	LibvirtXMLGenerator::Elements::Devices::EmulatorElements::Emulator emulator;
	std::vector<LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk> disks;
	std::vector<LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevUSBSource> hotDevUSBs;
	std::vector<LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevPCISource> hotDevPCIs;
	LibvirtXMLGenerator::Elements::Devices::TpmElements::Tpm tpm;
	std::vector<LibvirtXMLGenerator::Elements::Devices::ControllerElements::Controller>
		controllers;
	std::vector<LibvirtXMLGenerator::Elements::Devices::NetworkElements::Network> networks;

	std::string getXml() const override;
};
} // namespace DeviceElements
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
