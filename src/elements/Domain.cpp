#include "Domain.hpp"
#include <string>
#include <format>

std::string PlaceHolder::Elements::DomainElement::Domain::getXml() const {
	return std::format(
		"<domain "
		"type=\"{}\"><name>{}</name><description>{}</description>",
		domain, name, description);
};
