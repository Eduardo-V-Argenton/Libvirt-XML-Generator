#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../XmlAble.hpp"
#include <format>
#include <string>

struct Controller : XmlAble {
	std::string type;
	std::string model;
	int ports;

	std::string getXml() override {
		std::string xml =
			std::format("<controller type=\"{}\" model=\"{}\" ", type, model);
		if (type == "usb") {
			xml.append(std::format("ports=\"{}\" ", ports));
		}
		xml.append("/>");
		return xml;
	};
};
#endif
