#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "elements/Domain.hpp"
#include "elements/Memory.hpp"
#include "elements/Cpu.hpp"
#include "elements/Os.hpp"
#include "elements/Features.hpp"
#include "elements/SystemClock.hpp"
#include "elements/PowerManagement.hpp"
#include "elements/devices/Devices.hpp"

struct VirtualMachine : XmlAble {
	Domain domain;
	Memory memory;
	Cpu cpu;
	Os os;
	Features features;
	SystemClock clock;
	PowerManagement powerManagemente;
	Devices devices;

	std::string getXml() override {
		return std::format("{}{}{}{}{}{}{}{}</domain>", domain.getXml(),
						   memory.getXml(), cpu.getXml(), os.getXml(),
						   features.getXml(), clock.getXml(),
						   powerManagemente.getXml(), devices.getXml());
	}
};

#endif
