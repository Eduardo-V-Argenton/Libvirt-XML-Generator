#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "XmlAble.hpp"
#include "elements/Cpu.hpp"
#include "elements/Devices.hpp"
#include "elements/Domain.hpp"
#include "elements/Features.hpp"
#include "elements/Memory.hpp"
#include "elements/Os.hpp"
#include "elements/PowerManagement.hpp"
#include "elements/SystemClock.hpp"

namespace LibvirtXMLGenerator {
namespace Main {

struct VirtualMachine : LibvirtXMLGenerator::Interfaces::XmlAble {
	LibvirtXMLGenerator::Elements::DomainElement::Domain domain;
	LibvirtXMLGenerator::Elements::MemoryElements::Memory memory;
	LibvirtXMLGenerator::Elements::CpuElement::Cpu cpu;
	LibvirtXMLGenerator::Elements::OsElements::Os os;
	LibvirtXMLGenerator::Elements::FeaturesElements::Features features;
	LibvirtXMLGenerator::Elements::SystemClockElements::SystemClock clock;
	LibvirtXMLGenerator::Elements::PowerManagementElements::PowerManagement pm;
	Elements::DeviceElements::Devices devices;

	std::string getXml() const override;
};
} // namespace Main

} // namespace LibvirtXMLGenerator

#endif
