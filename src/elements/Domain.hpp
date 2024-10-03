#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace DomainElement {

struct Domain : PlaceHolder::Interfaces::XmlAble {
	std::string domain = "kvm";
	std::string name;
	std::string description;

	std::string getXml() const override;
};
} // namespace DomainElement
} // namespace Elements
} // namespace Ph
#endif
