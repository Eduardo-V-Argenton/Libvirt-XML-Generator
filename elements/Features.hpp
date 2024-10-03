#ifndef FEATURES_HPP
#define FEATURES_HPP

#include <format>
#include <string>
#include "XmlAble.hpp"

struct Features : XmlAble {
	struct SpinLocks : XmlAble {
		bool enabled = true;
		int retries = 8191;

		std::string getXml() override {
			return std::format("<spinlocks state=\"{}\" retries=\"{}\"/>",
							   enabled ? "on" : "off", retries);
		}
	};
	struct HyperV : XmlAble {
		bool relaxed = true;
		bool vapic = true;
		SpinLocks spinLocks;

		std::string getXml() override {
			return std::format("<hyperv><relaxed state=\"{}\"/><vapic "
							   "state=\"{}\"/>{}</hyperv>",
							   relaxed ? "on" : "off", vapic ? "on" : "off",
							   spinLocks.getXml());
		}
	};
	bool acpi = true;
	bool apic = true;
	bool vmport = false;
	std::string ioapic = "kvm";
	HyperV hyperv;

	std::string getXml() override {
		std::string xml = std::format("<features>");

		if (acpi) {
			xml.append("<acpi/>");
		}
		if (apic) {
			xml.append("<apic/>");
		}
		// ToDo dont append if not using hyperV
		xml.append(hyperv.getXml());
		xml.append(
			std::format("<vmport state=\"{}\"/>", vmport ? "on" : "off"));
		xml.append(std::format("</features>"));

		return xml;
	}
};
#endif