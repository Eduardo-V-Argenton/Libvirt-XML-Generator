#include "Emulator.hpp"
#include <format>

std::string
PlaceHolder::Elements::Devices::EmulatorElements::Emulator::getXml() const {
	return std::format("<emulator>{}</emulator>", emulator);
}
