#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <format>
#include <string>
#include "XmlAble.hpp"

struct Domain : XmlAble {
	std::string domain = "kvm";
	std::string name;
	std::string description;

	std::string getXml() override {
		return std::format(
			"<domain "
			"type=\"{}\"><name>{}</name><description>{}</description>",
			domain, name, description);
	};
};
#endif
