#ifndef POWERMANAGEMENT_HPP
#define POWERMANAGEMENT_HPP

#include <format>
#include <string>
#include "XmlAble.hpp"

struct PowerManagement : XmlAble {
	bool suspend_to_disk = false;
	bool suspend_to_mem = false;

	std::string getXml() override {
		return std::format(
			"<pm><suspend-to-mem enabled=\"{}\"/><suspend-to-disk "
			"enabled=\"{}\"/></pm>",
			suspend_to_mem ? "yes" : "no", suspend_to_disk ? "yes" : "no");
	}
};
#endif