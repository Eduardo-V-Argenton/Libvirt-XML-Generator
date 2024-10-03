#include "HotDev.hpp"
#include <format>
#include <string>

std::string
PlaceHolder::Elements::Devices::HotDevElements::HotDevPCISource::getXml()
	const {
	return std::format(
		"<hostdev mode=\"subsystem\" type=\"pci\" "
		"managed=\"{}\"><source><address domain=\"{}\" bus=\"{}\" slot=\"{}\" "
		"function=\"{}\"/></source></hostdev>",
		managed?"yes":"no", domain, bus, slot, function);
}

std::string
PlaceHolder::Elements::Devices::HotDevElements::HotDevUSBSource::getXml()
	const {
	return std::format("<hostdev mode=\"subsystem\" type=\"usb\" "
					   "managed=\"{}\"><source><vendor id=\"{}\"/><product "
					   "id=\"{}\"/></source></hostdev>",
					   managed?"yes":"no", vendor, product);
}
