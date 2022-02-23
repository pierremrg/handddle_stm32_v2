/* Handddle
 * Communication module
 * 2022
 */

#include "main.h"


/* @def MSG_SIZE
 *  @brief Message size. This variable controls the size expected for the message received, and the message size for those sent.
 */
#define MSG_SIZE 							20

/* Header information */
// Message identifier
#define MSG_HEADER_IDENTIFIER_FIRST_BYTE 	0x01
#define MSG_HEADER_IDENTIFIER_SECOND_BYTE	0x01

// Message size included in the header message
#define MSG_HEADER_SIZE_FIRST_BYTE 			0x00
#define MSG_HEADER_SIZE_SECOND_BYTE 		0x10

// Message Length
#define MSG_LENGTH_NUMBER_BYTE				0x02
#define MSG_LENGTH_FIRST_BYTE				0x00 // always equals to 0 while length is less than 256 (0xFF)
#define MSG_LENGTH_1_SECOND_BYTE			0x01 // 1 byte
#define MSG_LENGTH_2_SECOND_BYTE			0x02 // 2 bytes

// Two bytes containing id length
#define MSG_ID_LENGTH_BYTE					0x02


/* Bytes positions */
//Should be included in the whole system.
typedef enum {

	 IDENTIFIER_FIRST_BYTE					= 0,
	 IDENTIFIER_SECOND_BYTE					= 1,

	 LENGTH_FIRST_BYTE 						= 2,
	 LENGTH_SECOND_BYTE						= 3,

	 UID_1_TYPOLOGY 						= 4,
	 UID_2_MONTH							= 5,
	 UID_3_YEAR								= 6,
	 UID_4_ID								= 7,

	 MSG_TYPE								= 8,
	 INFORMATION_TYPE						= 9,

	 CONTENT_LENGTH_FIRST_BYTE				= 10,
	 CONTENT_LENGTH_SECOND_BYTE				= 11,

	 DATA 									= 12

} byte_position;


/* Misc data */
#define AUTO_VALUE 							0xFF
