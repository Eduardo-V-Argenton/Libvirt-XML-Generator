#include "Controller.hpp"
#include <format>
#include <string>

std::string
LibvirtXMLGenerator::Elements::Devices::ControllerElements::Controller::getXml() const {
	std::string xml =
		std::format("<controller type=\"{}\" model=\"{}\" ", type, model);
	if (type == "usb") {
		xml.append(std::format("ports=\"{}\" ", ports));
	}
	xml.append("/>");
	return xml;
};
