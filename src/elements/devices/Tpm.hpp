// ToDo
#ifndef TPM_HPP
#define TPM_HPP

#include "../../XmlAble.hpp"
#include <string>
#include <variant>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace TpmElements {

struct EmulatedTpmBackend : Interfaces::XmlAble {
	std::string version;

	std::string getXml() const override;
};

struct PassthroughTPMBackend : Interfaces::XmlAble {
	std::string hostsPath;

	std::string getXml() const override;
};

struct Tpm : Interfaces::XmlAble {

    std::string model;
	std::variant<EmulatedTpmBackend, PassthroughTPMBackend> backend;

	std::string getXml() const override;
};

} // namespace TpmElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
