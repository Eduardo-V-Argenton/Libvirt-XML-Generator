#ifndef HOTDEV_HPP
#define HOTDEV_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace Devices {
namespace HotDevElements {

struct HotDevUSBSource : PlaceHolder::Interfaces::XmlAble {
	std::string vendor;
	std::string product;
	bool managed = true;

	std::string getXml() const override;
};

struct HotDevPCISource : PlaceHolder::Interfaces::XmlAble {
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
} // namespace PlaceHolder
#endif
