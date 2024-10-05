#ifndef DISK_HPP
#define DISK_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace DiskElements {

struct Disk : LibvirtXMLGenerator::Interfaces::XmlAble {
  protected:
	Disk() = default;

  public:
	struct Source : LibvirtXMLGenerator::Interfaces::XmlAble {
		std::string getXml() const override;
	};
	
	struct Driver : LibvirtXMLGenerator::Interfaces::XmlAble {
		std::string name = "qemu";
		std::string type;

		std::string getXml() const override;
	};

	struct Target : LibvirtXMLGenerator::Interfaces::XmlAble {
		std::string dev;
		std::string bus;

		std::string getXml() const override;
	};

	std::string type = "file";
	std::string device = "disk";
	// std::string snapshot = "";  /ToDo implementar snapshot
	bool readonly = false;
	Target target;
	Source source;
	Driver driver;

	std::string getXml() const override;
};

struct DiskLocal : Disk {

	struct Source : Disk::Source {
		std::string file;

		std::string getXml() const override;
	};
	Source source;
};

struct DiskNetwork : Disk {

	struct Source : Disk::Source {
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
	Source source;
};
} // namespace DiskElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
