#ifndef SYSTEMCLOCK_HPP
#define SYSTEMCLOCK_HPP

#include "../XmlAble.hpp"
#include <string>
#include <vector>

namespace PlaceHolder {
namespace Elements {
namespace SystemClockElements {

struct SystemClock : PlaceHolder::Interfaces::XmlAble {
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
} // namespace PlaceHolder
#endif
