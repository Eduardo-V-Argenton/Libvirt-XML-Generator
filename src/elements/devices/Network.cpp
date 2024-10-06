#include "Network.hpp"
#include <format>
#include <string>

std::string LibvirtXMLGenerator::Elements::Devices::NetworkElements::NATSource::
	getInterface() const {

	return "network";
}

std::string
LibvirtXMLGenerator::Elements::Devices::NetworkElements::NATSource::getXml()
	const {

	return std::format("<source network=\"{}\" />", network);
}

std::string LibvirtXMLGenerator::Elements::Devices::NetworkElements::
	BridgeSource::getInterface() const {

	return "bridge";
}

std::string
LibvirtXMLGenerator::Elements::Devices::NetworkElements::BridgeSource::getXml()
	const {

	return std::format("<source bridge=\"{}\" />", bridge);
}

std::string LibvirtXMLGenerator::Elements::Devices::NetworkElements::
	DirectSource::getInterface() const {

	return "direct";
}

std::string
LibvirtXMLGenerator::Elements::Devices::NetworkElements::DirectSource::getXml()
	const {

	return std::format("<source dev=\"{}\" mode=\"{}\"/>", dev, mode);
}

std::string
LibvirtXMLGenerator::Elements::Devices::NetworkElements::Network::getXml()
	const {

	std::string xml = std::format(
		"<interface type=\"{}\">{}<model type=\"{}\"/>",
		std::visit([](auto &&arg) { return arg.getInterface(); }, source),
		std::visit([](auto &&arg) { return arg.getXml(); }, source), model);

	if (!mac.empty()) {
		xml.append(std::format("<mac address=\"{}\" />", mac));
	}

	xml.append("</interface>");

	return xml;
}
