#include "Tpm.hpp"
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

std::string
LibvirtXMLGenerator::Elements::Devices::TpmElements::Tpm::getXml() const {
	if (model != "crb" && model != "tis") {
		throw std::invalid_argument("Invalid TPM model");
	}
	return std::format(
		"<tpm model=\"tpm-{}\">{}</tpm>", model,
		std::visit([](auto &&arg) { return arg.getXml(); }, backend));
}

std::string LibvirtXMLGenerator::Elements::Devices::TpmElements::
	EmulatedTpmBackend::getXml() const {
	if (version != "2.0" && version != "1.2") {
		throw std::invalid_argument("Invalid TPM Version");
	}
	return std::format("<backend type=\"emulator\" version=\"{}\" ></backend>",
					   version);
}

std::string LibvirtXMLGenerator::Elements::Devices::TpmElements::
	PassthroughTPMBackend::getXml() const {
	return std::format(
		"<backend type=\"passthrough\"><device path=\"{}\"/></backend>",
		hostsPath);
}
