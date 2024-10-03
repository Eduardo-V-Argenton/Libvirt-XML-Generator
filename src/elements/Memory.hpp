#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace MemoryElements {
struct Memory : PlaceHolder::Interfaces::XmlAble {
	std::string unit = "M";
	int memory;

	std::string getXml() const override;
};
} // namespace MemoryElements
} // namespace Elements

} // namespace PlaceHolder
#endif
