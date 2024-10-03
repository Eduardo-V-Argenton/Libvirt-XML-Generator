#include "PowerManagement.hpp"
#include <format>

std::string
PlaceHolder::Elements::PowerManagementElements::PowerManagement::getXml()
	const {
	return std::format("<pm><suspend-to-mem enabled=\"{}\"/><suspend-to-disk "
					   "enabled=\"{}\"/></pm>",
					   suspend_to_mem ? "yes" : "no",
					   suspend_to_disk ? "yes" : "no");
}
