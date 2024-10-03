#ifndef FEATURES_HPP
#define FEATURES_HPP

#include "../XmlAble.hpp"
#include <string>

namespace Placeholder {
namespace Elements {
namespace FeaturesElements {

struct Features : PlaceHolder::Interfaces::XmlAble {
	struct SpinLocks : XmlAble {
		bool enabled = true;
		int retries = 8191;

		std::string getXml() const override;
	};

	struct HyperV : XmlAble {
		bool relaxed = true;
		bool vapic = true;
		SpinLocks spinLocks;

		std::string getXml() const override;
	};
	bool acpi = true;
	bool apic = true;
	bool vmport = false;
	std::string ioapic = "kvm";
	HyperV hyperv;

	std::string getXml() const override;
};
} // namespace FeaturesElements

} // namespace Elements

} // namespace Placeholder
#endif
