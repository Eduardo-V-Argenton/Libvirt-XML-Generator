#include "Domain.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <format>
#include <vector>

std::string LibvirtXMLGenerator::Elements::DomainElement::Domain::getXml() const {
	return std::format(
		"<domain "
		"type=\"{}\"><name>{}</name><description>{}</description>",
		domain, name, description);
};

void LibvirtXMLGenerator::Elements::DomainElement::Domain::check() const {
    std::vector<std::string> validDomainTypes= {"kvm","xen","hvf","qemu", "lxc"};
    if (std::find(validDomainTypes.begin(),validDomainTypes.end(),domain) == validDomainTypes.end()){
        throw std::invalid_argument("Invalid domain type");
    }
    if (name.empty()){
        throw std::invalid_argument("VM's name can not be null");
    }
}