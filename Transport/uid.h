/* Handddle
 * Communication module
 * 2022
 */

/*
 * The UID is the Unique Identifier for the SMT32
 * This value is hardcoded and never changed
 */

#define TYPE_MACHINE_TOIT 			0xC1
#define TYPE_MACHINE_RACK 			0xC2
#define TYPE_MP 		  			0xC3
#define TYPE_POST_TREATMENT 		0xC4

#define MSG_HEADER_UID_BROADCAST 	0xFF
#define MSG_HEADER_UID_1_BROADCAST 	0xCF

#define MSG_HEADER_UID_1_TYPOLOGY	TYPE_MACHINE_TOIT
#define MSG_HEADER_UID_2_MONTH		0x00
#define MSG_HEADER_UID_3_YEAR		0x00
#define MSG_HEADER_UID_4_ID			0x01
