#include "Os.hpp"
#include <format>

std::string PlaceHolder::Elements::OsElements::Os::BootDisk::getXml() const {
	return std::format("<boot dev=\"{}\"/>", type);
}

std::string PlaceHolder::Elements::OsElements::Os::BootMenu::getXml() const {
	return std::format("<bootmenu enable=\"{}\" timeout=\"{}\"/>",
					   enable ? "yes" : "no", timeout);
}

std::string PlaceHolder::Elements::OsElements::Os::Type::getXml() const {
	return std::format("<type arch=\"{}\" machine=\"{}\">{}</type>", arch,
					   machine, type);
}

std::string PlaceHolder::Elements::OsElements::Os::getXml() const {
	return std::format("<os firmware=\"{}\">{}{}{}</os>", firmware,
					   type.getXml(), bootdisk.getXml(), bootmenu.getXml());
}
