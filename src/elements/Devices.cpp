#include "Devices.hpp"
#include "devices/HotDev.hpp"
#include <string>

std::string PlaceHolder::Elements::DeviceElements::Devices::getXml() const {
	std::string xml = "<devices>";
	for (const PlaceHolder::Elements::Devices::ControllerElements::Controller
			 &controller : controllers) {
		xml.append(controller.getXml());
	}
	for (const PlaceHolder::Elements::Devices::DiskElements::Disk &disk :
		 disks) {
		xml.append(disk.getXml());
	}
	for (const PlaceHolder::Elements::Devices::HotDevElements::HotDevPCISource &hotdev :
		 hotDevPCIs) {
		xml.append(hotdev.getXml());
	}
	
	for (const PlaceHolder::Elements::Devices::HotDevElements::HotDevUSBSource &hotdev :
		 hotDevUSBs) {
		xml.append(hotdev.getXml());
	}
	xml.append("</devices>");
	return xml;
}
