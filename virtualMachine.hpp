#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "elements.hpp"
#include <format>
#include <string>

struct VirtualMachine : XmlAble {
	Domain domain;
	Memory memory;
	Cpu cpu;
	Os os;
	Features features;
	SystemClock clock;
	PowerManagement powerManagemente;
	vector<Devices> devices;

	string getXml() override {
		std::string xml = std::format(
			"{}{}{}{}{}{}{}</domain>", domain.getXml(), memory.getXml(),
			cpu.getXml(), os.getXml(), features.getXml(), clock.getXml(),
			powerManagemente.getXml());
		return xml;
	}
};
#endif
