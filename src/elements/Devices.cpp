#include "Devices.hpp"
#include "devices/HotDev.hpp"
#include <string>

std::string LibvirtXMLGenerator::Elements::DeviceElements::Devices::getXml() const {
	std::string xml = "<devices>";
	for (const LibvirtXMLGenerator::Elements::Devices::ControllerElements::Controller
			 &controller : controllers) {
		xml.append(controller.getXml());
	}
	for (const LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk &disk :
		 disks) {
		xml.append(disk.getXml());
	}
	for (const LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevPCISource &hotdev :
		 hotDevPCIs) {
		xml.append(hotdev.getXml());
	}
	
	for (const LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevUSBSource &hotdev :
		 hotDevUSBs) {
		xml.append(hotdev.getXml());
	}
	xml.append("</devices>");
	return xml;
}
