#ifndef DISK_HPP
#define DISK_HPP

#include "../../XmlAble.hpp"
#include <string>
#include <variant>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace DiskElements {

struct SourceLocal : Interfaces::XmlAble {

	std::string file;
	std::string getXml() const override;
};

struct SourceNetwork : Interfaces::XmlAble {
	struct Host : XmlAble {
		std::string name = "";
		std::string port = "";

		std::string getXml() const override;
	};

	struct Auth : XmlAble {
		std::string username = "";
		std::string type = "";
		std::string usage = "";

		std::string getXml() const override;
	};

	std::string protocol;
	std::string name;
	std::string query = "";
	bool ssl;
	Host host;
	Auth auth;

	std::string getXml() const override;
};

struct Disk : Interfaces::XmlAble {
    
	struct Driver : LibvirtXMLGenerator::Interfaces::XmlAble {
		std::string name = "qemu";
		std::string type;

		std::string getXml() const override;
	};

	struct Target : LibvirtXMLGenerator::Interfaces::XmlAble {
		std::string dev;
		std::string bus = "sata";

		std::string getXml() const override;
	};

	std::string type = "file";
	std::string device = "disk";
	// std::string snapshot = "";  /ToDo implementar snapshot
	bool readonly = false;
	Target target;
	std::variant<SourceLocal, SourceNetwork> source;
	Driver driver;

	std::string getXml() const override;
};

} // namespace DiskElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
