#include "Features.hpp"
#include <format>

std::string
Placeholder::Elements::FeaturesElements::Features::SpinLocks::getXml() const {
	return std::format("<spinlocks state=\"{}\" retries=\"{}\"/>",
					   enabled ? "on" : "off", retries);
}

std::string
Placeholder::Elements::FeaturesElements::Features::HyperV::getXml() const {
	return std::format("<hyperv><relaxed state=\"{}\"/><vapic "
					   "state=\"{}\"/>{}</hyperv>",
					   relaxed ? "on" : "off", vapic ? "on" : "off",
					   spinLocks.getXml());
}

std::string Placeholder::Elements::FeaturesElements::Features::getXml() const {
	std::string xml = std::format("<features>");

	if (acpi) {
		xml.append("<acpi/>");
	}
	if (apic) {
		xml.append("<apic/>");
	}
	// ToDo dont append if not using hyperV
	xml.append(hyperv.getXml());
	xml.append(std::format("<vmport state=\"{}\"/>", vmport ? "on" : "off"));
	xml.append(std::format("</features>"));

	return xml;
}
