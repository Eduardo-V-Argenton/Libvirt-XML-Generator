#include "SystemClock.hpp"
#include <format>
#include <string>

std::string
PlaceHolder::Elements::SystemClockElements::SystemClock::Timer::getXml() const {
	std::string xml = std::format("<timer name=\"{}\" present=\"{}\"", name,
								  present ? "yes" : "no");
	if (tickpolicy != "") {
		xml.append(std::format(" tickpolicy=\"{}\"", tickpolicy));
	}
	xml.append(std::format("/>"));
	return xml;
}

std::string
PlaceHolder::Elements::SystemClockElements::SystemClock::getXml() const {
	std::string xml = std::format("<clock offset=\"{}\">", offset);
	for (const Timer &timer : timers) {
		xml.append(timer.getXml());
	}
	xml.append(std::format("</clock>"));
	return xml;
}
