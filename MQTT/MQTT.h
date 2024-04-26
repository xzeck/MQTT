#ifndef MQTT_H
#define MQTT_H

#include <stdio.h>

constexpr int MQTT_HEADER_LEN = 2;
constexpr int MQTT_ACK_LEN = 4;

/*
* FLAGS
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180835
*/
constexpr int CONNACK_BYTE = 0x20;
constexpr int PUBLISH_BYTE = 0x30;
constexpr int PUBACK_BYTE = 0x40;
constexpr int PUBREC_BYTE = 0x50;
constexpr int PUBREL_BYTE = 0x60;
constexpr int PUBCOMP_BYTE = 0x70;
constexpr int SUBACK_BYTE = 0x90;
constexpr int USUBACK_BYTE = 0xB0;
constexpr int PINGRESP_BYTE = 0xD0;

/*
* PACKET TYPES
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180834
*/
enum packet_type {
	CONNECT = 1,
	CONNACK = 2,
	PUBLISH = 3,
};




#endif