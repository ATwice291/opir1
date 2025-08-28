FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://spi.cfg \
	file://0001-Enable-SPI1-port-for-LCD.patch \
"
