#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "../XmlAble.hpp"
#include <format>
#include <string>

struct Emulator : XmlAble {
	std::string emulator;

	std::string getXml() override {
		return std::format("<emulator>{}</emulator>", emulator);
	}
};
#endif
