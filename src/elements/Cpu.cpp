#include "Cpu.hpp"
#include <string>
#include <format>

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::VCpuPin::getXml() const {
	return std::format("<vcpupin vcpu=\"{}\" cpuset=\"{}\"/>", vcpu, cpuset);
}

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::IOThreadPin::getXml() const {
	return std::format("<iothreadpin iothread=\"{}\" cpuset=\"{}\"/>", ioThread,
					   cpuset);
}

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::getXml() const {
	std::string xml =
		std::format("<vcpu placement=\"{}\">{}</vcpu>", placement, quantVcpu);

	if (placement == "static") {
		xml.append("<cputune>");
		for (const VCpuPin &cpu : cpus) {
			xml.append(cpu.getXml());
		}
		for (const IOThreadPin &ioThread : ioThreads) {
			xml.append(ioThread.getXml());
		}
		xml.append(std::format("<emulatorpin cpuset=\"{}\"/>", emulatorPin));
		xml.append("</cputune>");
	}

	return xml;
}

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::Topology::getXml() const {
	return std::format(
		"<topology sockets=\"{}\" cores=\"{}\" threads=\"{}\" />", sockets,
		cores, threads);
}

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::Feature::getXml() const {
	return std::format("<feature policy=\"{}\" name=\"{}\" />", policy, name);
}

std::string LibvirtXMLGenerator::Elements::CpuElement::Cpu::getXml() const {
	std::string xml = std::format(
		"{}<cpu mode=\"{}\" check=\"{}\">{}<cache mode=\"{}\"/>",
		cpupin.getXml(), mode, cpuCheck, topology.getXml(), cache_mode);

	for (const Feature &feature : features) {
		xml.append(feature.getXml());
	}

	xml.append("</cpu>");
	return xml;
}
