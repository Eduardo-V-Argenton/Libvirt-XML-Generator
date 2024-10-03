#ifndef OS_HPP
#define OS_HPP

#include "../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace OsElements {

struct Os : PlaceHolder::Interfaces::XmlAble {
	struct BootDisk : XmlAble {
		std::string type = "hd";
		// disk??

		std::string getXml() const override;
	};

	struct BootMenu : XmlAble {
		bool enable = false;
		int timeout = 2;

		std::string getXml() const override;
	};

	struct Type : XmlAble {
		std::string arch = "x86_64";
		std::string machine = "q35";
		std::string type = "hvm";

		std::string getXml() const override;
	};
	std::string firmware = "efi";
	Type type;
	std::string secure = "no";
	BootDisk bootdisk;
	BootMenu bootmenu;

	std::string getXml() const override;
};
} // namespace OsElements
} // namespace Elements
} // namespace PlaceHolder
#endif
