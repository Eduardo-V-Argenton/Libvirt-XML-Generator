#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace Devices {
namespace ControllerElements {

struct Controller : PlaceHolder::Interfaces::XmlAble {
	std::string type;
	std::string model;
	int ports;

	std::string getXml() const override;
};
} // namespace ControllerElements
} // namespace Devices
} // namespace Elements
} // namespace PlaceHolder
#endif
