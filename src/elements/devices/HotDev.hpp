#ifndef HOTDEV_HPP
#define HOTDEV_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace HotDevElements {

struct HotDevUSBSource : LibvirtXMLGenerator::Interfaces::XmlAble {
	std::string vendor;
	std::string product;
	bool managed = true;

	std::string getXml() const override;
};

struct HotDevPCISource : LibvirtXMLGenerator::Interfaces::XmlAble {
	int domain;
	int bus;
	int slot;
	int function;
	bool managed = true;

	std::string getXml() const override;
};
} // namespace HotDevElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
