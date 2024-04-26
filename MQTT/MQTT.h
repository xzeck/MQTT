#ifndef MQTT_H
#define MQTT_H

#include <stdio.h>
#include <cstdint>

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
	PUBACK = 4,
	PUBREC = 5,
	PUBREL = 6,
	PUBCOMP = 7,
	SUBSCRIBE = 8,
	SUBACK = 9,
	UNSUBSCRIBE = 10,
	UNSUBACK = 11,
	PINGREQ = 12,
	PINGRESP = 13,
	DISCONNECT = 14
};

enum QOS_LEVEL {
	AT_MOST_ONCE,
	AT_LEAST_ONCE,
	EXACTLY_ONCE
};

union mqtt_header {
	uint8_t  byte;

	struct {
		uint8_t retain : 1;
		uint8_t qos : 2;
		uint8_t dup : 3;
		uint8_t type : 4;
	} bits;
};

/*
CONNECT - Control Packet
Each CONNECT requires a CONNACK to be sent in response
https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180841
*/

struct mqtt_connect {
	union mqtt_header header;

	union {
		unsigned char bytes;

		// CONNECT flag bits
		// LSB -> MSB
		// along with bit sizes
		struct {
			int reserved : 1;
			uint8_t clean_session : 1;
			uint8_t will_flag : 1;
			uint8_t will_qos : 2;
			uint8_t will_retain : 1;
			uint8_t password : 1;
			uint8_t username : 1;

		} bits;
	};
	
	/*
	* Payload structure
	* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180844
	*/
	struct {
		unsigned short keepalive;
		uint8_t* client_id;
		uint8_t* username;
		uint8_t* password;
		uint8_t* will_topic;
		uint8_t* will_message;
	} payload;
};

/*
* Connection acknowledgement 
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180846
*/
struct mqtt_connack {
	union mqtt_header header;

	union {
		unsigned char bytes;
		struct {
			uint8_t session_present : 1;
			uint8_t reserved : 7;
		} bits;
	};

	unsigned char rc;
};

/*
* Subscribe request
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180876
*/
struct mqtt_subscribe {
	union mqtt_header header;
	
	uint8_t packet_id;
	uint8_t tuples_len;

		
	struct {
		uint8_t topic_len;
		unsigned char* topic;
		unsigned qos;
	} *tuples;

};

/*
* unsubscribe request
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180885
*/
struct mqtt_unsubscribe {
	union mqtt_header header;

	uint8_t packet_id;
	uint8_t tuples_len;


	struct {
		uint8_t topic_len;
		unsigned char* topic;
	} *tuples;

};

/*
* Subscription acknowledgement
* https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html#_Toc442180881
*/
struct mqtt_suback {

	union mqtt_header header;
	uint8_t packet_id;
	uint8_t rcslen; // response code length;

	// The order of return codes in the SUBACK Packet MUST 
	// match the order of Topic Filters in the SUBSCRIBE Packet - [MQTT - 3.9.3 - 1]
	uint8_t* rcs;

};



#endif