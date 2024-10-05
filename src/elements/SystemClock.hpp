#ifndef SYSTEMCLOCK_HPP
#define SYSTEMCLOCK_HPP

#include "../XmlAble.hpp"
#include <string>
#include <vector>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace SystemClockElements {

struct SystemClock : LibvirtXMLGenerator::Interfaces::XmlAble {
	struct Timer : XmlAble {
		std::string name;
		std::string tickpolicy = "";
		bool present = true;

		std::string getXml() const override;
	};

	std::string offset = "localtime";
	std::vector<Timer> timers;

	std::string getXml() const override;
};
} // namespace SystemClockElements
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
