#ifndef SYSTEMCLOCK_HPP
#define SYSTEMCLOCK_HPP

#include <format>
#include <string>
#include <vector>
#include "XmlAble.hpp"

struct SystemClock : XmlAble {
	struct Timer : XmlAble {
		std::string name;
		std::string tickpolicy = "";
		bool present = true;

		std::string getXml() override {
			std::string xml = std::format("<timer name=\"{}\" present=\"{}\"",
										  name, present ? "yes" : "no");
			if (tickpolicy != "") {
				xml.append(std::format(" tickpolicy=\"{}\"", tickpolicy));
			}
			xml.append(std::format("/>"));
			return xml;
		}
	};

	std::string offset = "localtime";
	std::vector<Timer> timers;

	std::string getXml() override {
		std::string xml = std::format("<clock offset=\"{}\">", offset);
		for (Timer timer : timers) {
			xml.append(timer.getXml());
		}
		xml.append(std::format("</clock>"));
		return xml;
	}
};
#endif