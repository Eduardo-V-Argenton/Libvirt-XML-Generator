#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace ControllerElements {

struct Controller : LibvirtXMLGenerator::Interfaces::XmlAble {
	std::string type;
	std::string model;
	int ports;

	std::string getXml() const override;
};
} // namespace ControllerElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
