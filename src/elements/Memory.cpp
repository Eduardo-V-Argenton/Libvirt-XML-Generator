#include "Memory.hpp"
#include <format>

std::string LibvirtXMLGenerator::Elements::MemoryElements::Memory::getXml() const {
	return std::format("<memory unit=\"{}\">{}</memory>", unit, memory);
}
