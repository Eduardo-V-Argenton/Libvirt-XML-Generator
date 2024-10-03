#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "../../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace Devices {
namespace EmulatorElements {
    
struct Emulator : PlaceHolder::Interfaces::XmlAble {
	std::string emulator;

	std::string getXml() const override;
};

} // namespace EmulatorElements
} // namespace Devices
} // namespace Elements
} // namespace PlaceHolder
#endif
