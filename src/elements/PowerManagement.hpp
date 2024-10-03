#ifndef POWERMANAGEMENT_HPP
#define POWERMANAGEMENT_HPP

#include "../XmlAble.hpp"
#include <string>

namespace PlaceHolder {
namespace Elements {
namespace PowerManagementElements {

struct PowerManagement : PlaceHolder::Interfaces::XmlAble {
	bool suspend_to_disk = false;
	bool suspend_to_mem = false;

	std::string getXml() const override;
};
} // namespace PowerManagementElements
} // namespace Elements
} // namespace PlaceHolder
#endif
