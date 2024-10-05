#ifndef CHECKABLE_HPP
#define CHECKABLE_HPP

namespace LibvirtXMLGenerator {
namespace Interfaces {

struct Checkable {
	virtual void check() const = 0;
};
} // namespace Interfaces
} // namespace LibvirtXMLGenerator
#endif