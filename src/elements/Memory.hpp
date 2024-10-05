#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../XmlAble.hpp"
#include "../Checkable.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace MemoryElements {
struct Memory : Interfaces::XmlAble {
	std::string unit = "M";
	int memory;

	std::string getXml() const override;
};
} // namespace MemoryElements
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
