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

namespace PlaceHolder {
namespace Main {

struct VirtualMachine : PlaceHolder::Interfaces::XmlAble {
	PlaceHolder::Elements::DomainElement::Domain domain;
	PlaceHolder::Elements::MemoryElements::Memory memory;
	PlaceHolder::Elements::CpuElement::Cpu cpu;
	PlaceHolder::Elements::OsElements::Os os;
	Placeholder::Elements::FeaturesElements::Features features;
	PlaceHolder::Elements::SystemClockElements::SystemClock clock;
	PlaceHolder::Elements::PowerManagementElements::PowerManagement pm;
	Elements::DeviceElements::Devices devices;

	std::string getXml() const override;
};
} // namespace Main

} // namespace PlaceHolder

#endif
