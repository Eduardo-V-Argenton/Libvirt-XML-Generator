#include "Disk.hpp"
#include <format>
#include <string>

std::string
LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk::Driver::getXml()
	const {
	return std::format("<driver name=\"{}\" type=\"{}\" />", name, type);
}

std::string
LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk::Target::getXml()
	const {
	return std::format("<target dev=\"{}\" bus=\"{}\" />", dev, bus);
}

std::string
LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk::getXml() const {
	return std::format(
		"<disk type=\"{}\" device=\"{}\">{}{}{}{}</disk>", type, device,
		driver.getXml(),
		std::visit([](auto &&arg) { return arg.getXml(); }, source),
		target.getXml(), readonly ? "</readonly>" : "");
}

std::string
LibvirtXMLGenerator::Elements::Devices::DiskElements::SourceLocal::getXml()
	const {
	return std::format("<source file=\"{}\" />", file);
}

std::string LibvirtXMLGenerator::Elements::Devices::DiskElements::
	SourceNetwork::Host::getXml() const {
	return std::format("<host name=\"{}\" port=\"{}\" />", name, port);
}

std::string LibvirtXMLGenerator::Elements::Devices::DiskElements::
	SourceNetwork::Auth::getXml() const {
	return std::format("<auth username=\"{}\" ><secret type=\"{}\" "
					   "usage=\"{}\" /></auth>",
					   username, passwordType, password);
}

std::string
LibvirtXMLGenerator::Elements::Devices::DiskElements::SourceNetwork::getXml()
	const {

	std::string xml =
		std::format("<source protocol=\"{}\" name=\"{}\"", protocol, name);

	// if (query != "") {
	// 	xml.append(std::format(" query=\"{}\" ", query));
	// }
	xml.append(">");
	xml.append(host.getXml());
	if (auth.username != "") {
		xml.append(auth.getXml());
	}
	// xml.append(std::format("<ssl verify=\"{}\"/>", ssl ? "yes" : "no"));
	xml.append("</source>");
	return xml;
}
