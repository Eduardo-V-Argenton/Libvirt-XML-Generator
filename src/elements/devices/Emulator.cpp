#include "Emulator.hpp"
#include <format>

std::string
LibvirtXMLGenerator::Elements::Devices::EmulatorElements::Emulator::getXml() const {
	return std::format("<emulator>{}</emulator>", emulator);
}
