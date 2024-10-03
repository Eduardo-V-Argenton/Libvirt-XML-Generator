#ifndef DISK_HPP
#define DISK_HPP

#include "../XmlAble.hpp"
#include <format>
#include <string>

struct Disk : XmlAble {
  protected:
	Disk() = default;

  public:
	struct Source : XmlAble {
		std::string getXml() override { return ""; }
	};

	struct Driver : XmlAble {
		std::string name = "qemu";
		std::string type;

		std::string getXml() override {
			return std::format("<driver name=\"{}\" type=\"{}\" />", name,
							   type);
		}
	};

	struct Target : XmlAble {
		std::string dev;
		std::string bus;

		std::string getXml() override {
			return std::format("<target dev=\"{}\" bus=\"{}\" />", dev, bus);
		}
	};

	std::string type = "file";
	std::string device = "disk";
	// std::string snapshot = "";  /ToDo implementar snapshot
	bool readonly = false;
	Target target;
	Source source;
	Driver driver;

	std::string getXml() override {
		return std::format("<disk type=\"{}\" device=\"{}\">{}{}{}{}</disk>",
						   type, device, driver.getXml(), source.getXml(),
						   target.getXml(), readonly ? "</readonly>" : "");
	}
};

struct DiskLocal : Disk {

	struct Source : Disk::Source {
		std::string file;

		std::string getXml() override {
			return std::format("<source file=\"{}\" />", file);
		}
	};
	Source source;
};

struct DiskNetwork : Disk {

	struct Source : Disk::Source {
		struct Host : XmlAble {
			std::string name = "";
			std::string port = "";

			std::string getXml() override {
				return std::format("<host name=\"{}\" port=\"{}\" />", name,
								   port);
			}
		};

		struct Auth : XmlAble {
			std::string username = "";
			std::string type = "";
			std::string usage = "";

			std::string getXml() override {
				return std::format("<auth username=\"{}\" ><secret type=\"{}\" "
								   "usage=\"{}\" /></auth>",
								   username, type, usage);
			}
		};

		std::string protocol;
		std::string name;
		std::string query = "";
		bool ssl;
		Host host;
		Auth auth;

		std::string getXml() override {
			std::string xml = std::format("<source protocol=\"{}\" name=\"{}\"",
										  protocol, name);

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
	};
	Source source;
};
#endif
