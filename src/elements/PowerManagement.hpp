#ifndef POWERMANAGEMENT_HPP
#define POWERMANAGEMENT_HPP

#include "../XmlAble.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace PowerManagementElements {

struct PowerManagement : LibvirtXMLGenerator::Interfaces::XmlAble {
	bool suspend_to_disk = false;
	bool suspend_to_mem = false;

	std::string getXml() const override;
};
} // namespace PowerManagementElements
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
