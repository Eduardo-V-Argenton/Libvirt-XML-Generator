#include "Disk.hpp"
#include <format>
#include <string>

std::string
PlaceHolder::Elements::Devices::DiskElements::Disk::Source::getXml() const {
	return "";
}

std::string
PlaceHolder::Elements::Devices::DiskElements::Disk::Driver::getXml() const {
	return std::format("<driver name=\"{}\" type=\"{}\" />", name, type);
}

std::string
PlaceHolder::Elements::Devices::DiskElements::Disk::Target::getXml() const {
	return std::format("<target dev=\"{}\" bus=\"{}\" />", dev, bus);
}

std::string PlaceHolder::Elements::Devices::DiskElements::Disk::getXml() const {
	return std::format("<disk type=\"{}\" device=\"{}\">{}{}{}{}</disk>", type,
					   device, driver.getXml(), source.getXml(),
					   target.getXml(), readonly ? "</readonly>" : "");
}

std::string
PlaceHolder::Elements::Devices::DiskElements::DiskLocal::Source::getXml()
	const {
	return std::format("<source file=\"{}\" />", file);
}

std::string PlaceHolder::Elements::Devices::DiskElements::DiskNetwork::Source::
	Host::getXml() const {
	return std::format("<host name=\"{}\" port=\"{}\" />", name, port);
}

std::string PlaceHolder::Elements::Devices::DiskElements::DiskNetwork::Source::
	Auth::getXml() const {
	return std::format("<auth username=\"{}\" ><secret type=\"{}\" "
					   "usage=\"{}\" /></auth>",
					   username, type, usage);
}

std::string
PlaceHolder::Elements::Devices::DiskElements::DiskNetwork::Source::getXml()
	const {

	std::string xml =
		std::format("<source protocol=\"{}\" name=\"{}\"", protocol, name);

	if (query != "") {
		xml.append(std::format(" query=\"{}\" ", query));
	}
	xml.append(">");
	xml.append(host.getXml());
	if (auth.username != "") {
		xml.append(auth.getXml());
	}
	xml.append(std::format("<ssl verify=\"{}\"/>", ssl ? "yes" : "no"));
	xml.append("</source>");
	return xml;
}
