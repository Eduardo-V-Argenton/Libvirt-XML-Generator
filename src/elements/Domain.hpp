#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "../XmlAble.hpp"
#include "../Checkable.hpp"
#include <string>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace DomainElement {

struct Domain : Interfaces::XmlAble,Interfaces::Checkable {
	std::string domain = "kvm";
	std::string name;
	std::string description;

	std::string getXml() const override;
	void check() const override;
};
} // namespace DomainElement
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
