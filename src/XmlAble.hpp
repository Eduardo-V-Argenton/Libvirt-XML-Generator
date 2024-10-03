#ifndef XMABLE_HPP
#define XMABLE_HPP

#include <string>

namespace PlaceHolder {
namespace Interfaces {

struct XmlAble {
	virtual std::string getXml() const = 0;
};
} // namespace Interfaces
} // namespace PlaceHolder
#endif
