#ifndef OS_HPP
#define OS_HPP

#include <format>
#include <string>
#include "XmlAble.hpp"

struct Os : XmlAble {
	struct BootDisk : XmlAble {
		std::string type = "hd";
		// disk??

		std::string getXml() override {
			return std::format("<boot dev=\"{}\"/>", type);
		}
	};

	struct BootMenu : XmlAble {
		bool enable = false;
		int timeout = 2;

		std::string getXml() override {
			return std::format("<bootmenu enable=\"{}\" timeout=\"{}\"/>",
							   enable ? "yes" : "no", timeout);
		}
	};

	struct Type : XmlAble {
		std::string arch = "x86_64";
		std::string machine = "q35";
		std::string type = "hvm";

		std::string getXml() override {
			return std::format("<type arch=\"{}\" machine=\"{}\">{}</type>",
							   arch, machine, type);
		}
	};

	std::string firmware = "efi";
	Type type;
	std::string secure = "no";
	BootDisk bootdisk;
	BootMenu bootmenu;

	std::string getXml() override {
		return std::format("<os firmware=\"{}\">{}{}{}</os>", firmware,
						   type.getXml(), bootdisk.getXml(), bootmenu.getXml());
	}
};
#endif