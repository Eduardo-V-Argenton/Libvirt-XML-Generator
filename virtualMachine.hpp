#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "elements.hpp"

struct VirtualMachine : XmlAble {
	Domain domain;
	Memory memory;
	Cpu cpu;
	Os os;
	Features features;
	SystemClock clock;
	PowerManagement powerManagemente;
	Device devices;

	std::string getXml() override {
		return std::format("{}{}{}{}{}{}{}{}</domain>", domain.getXml(),
						   memory.getXml(), cpu.getXml(), os.getXml(),
						   features.getXml(), clock.getXml(),
						   powerManagemente.getXml(), devices.getXml());
	}
};

#endif
