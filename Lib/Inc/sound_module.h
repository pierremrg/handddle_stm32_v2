/*
 * sound_module.h
 *
 *  Created on: Mar 22, 2022
 *      Author: handddle
 */

#include "main.h"

UART_HandleTypeDef huart5;

#define SOURCE      0x02  // TF CARD
#define BYTES_TO_TRANSMIT 10

typedef enum {
	sound_module_start_byte 	= 0x7E,
	sound_module_end_byte   	= 0xEF,
	sound_module_version    	= 0xFF,
	sound_module_cmd_len    	= 0x06,
	sound_module_feedback   	= 0x00 ,   //If need for Feedback: 0x01,  No Feedback: 0
	sound_module_eq				= 0x07,
	sound_module_select_track	= 0x03,
	sound_module_reset			= 0x0C,
	sound_module_init			= 0x3F,
	sound_module_volume			= 0x06,
	sound_module_next 			= 0x01,
	sound_module_previous		= 0x02,
	sound_module_pause 			= 0x0E,
	sound_module_playback		= 0x0D,
	sound_module_repeat			= 0x11,
	sound_module_no_parameter	= 0x00
} sound_module_commands;

#ifndef INC_SOUND_MODULE_H_
#define INC_SOUND_MODULE_H_

/*	@fn 	void send_cmd(uint8_t cmd, uint8_t parameter1, uint8_t parameter2);
 * 	@brief 	Function used to send the correct uart frame to the sound module
 * 	@param	cmd is the command to send
 * 	@param 	parameter1 is the first byte of the value to pass as a parameter
 * 	@param 	parameter2 is the second byte of the value to pass as a parameter
 */
void send_cmd(uint8_t cmd, uint8_t parameter1, uint8_t parameter2);

/*	@fn 	void sm_select_track(uint8_t track);
 * 	@brief 	Function used to select the track to play
 * 	@param 	track is the number of the track to play
 */
void sm_select_track(uint8_t track);

/*	@fn 	void sm_init (uint8_t volume);
 * 	@brief 	Function used to initialize the sound module with a volume
 * 	@param 	volume is the initialization value of the volume to pass to the sound module
 */
void sm_init (uint8_t volume);

/*	@fn 	void sm_change_volume(uint8_t volume);
 * 	@brief 	Function used to change the current volume
 * 	@param	volume is the desired volume to pass as a parameter
 */
void sm_change_volume(uint8_t volume);

/*	@fn 	void sm_next_track (void);
 * 	@brief 	Function used to play the next track
 */
void sm_next_track (void);

/*	@fn 	void sm_pause_track (void);
 * 	@brief 	Function used to pause the playback of the track
 */
void sm_pause_track (void);

/*	@fn 	void sm_playback_track (void);
 * 	@brief 	Function used to playback the track
 */
void sm_playback_track (void);

/*	@fn 	void sm_previous_track(void)
 * 	@brief 	Function used to play the previous track
 */
void sm_previous_track (void);

/*	@fn 	void sm_select_eq(uint8_t mode);
 * 	@brief 	Function used to select an equalizer mode
 * 	@param	mode is the number of the desired equalizer
 */
void sm_select_eq(uint8_t mode);

/*	@fn 	void sm_repeat_track(bool repeat);
 * 	@brief 	Function used to repeat or not the current track
 * 	@param	repeat is the boolean value to pass as a parameter
 */
void sm_repeat_track(bool repeat);

/*	@fn 	void sm_reset(void);
 * 	@brief 	Function used to reset the sound module
 */
void sm_reset(void);

#endif /* INC_SOUND_MODULE_H_ */
