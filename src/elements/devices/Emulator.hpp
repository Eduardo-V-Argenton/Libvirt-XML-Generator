#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace EmulatorElements {
    
struct Emulator : LibvirtXMLGenerator::Interfaces::XmlAble {
	std::string emulator;

	std::string getXml() const override;
};

} // namespace EmulatorElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
