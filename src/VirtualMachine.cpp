#include "VirtualMachine.hpp"
#include <format>

std::string LibvirtXMLGenerator::VirtualMachine::getXml() const {
	return std::format("{}{}{}{}{}{}{}{}</domain>", domain.getXml(),
					   memory.getXml(), cpu.getXml(), os.getXml(),
					   features.getXml(), clock.getXml(), pm.getXml(),
					   devices.getXml());
}
