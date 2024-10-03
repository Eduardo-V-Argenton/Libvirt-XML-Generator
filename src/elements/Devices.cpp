#include "Devices.hpp"
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
	xml.append("</devices>");
	return xml;
}
