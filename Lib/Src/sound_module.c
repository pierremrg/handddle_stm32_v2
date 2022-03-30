/*
 * sound_module.c
 *
 *  Created on: Feb. 04, 2022
 *      Author: Handddle
 */

#include "../Inc/sound_module.h"

void send_cmd (uint8_t cmd, uint8_t parameter1, uint8_t parameter2) // Parameter = 16 bits, so divided into 2 8-bit paramaters
{
	uint16_t checksum = sound_module_version + sound_module_cmd_len + cmd + sound_module_feedback + parameter1 + parameter2;
	checksum = ZERO-checksum;

	uint8_t cmd_sequence[BYTES_TO_TRANSMIT] = {
			sound_module_start_byte,
			sound_module_version,
			sound_module_cmd_len,
			cmd,
			sound_module_feedback,
			parameter1,
			parameter2,
			(uint8_t)(checksum>>BYTE_OFFSET),
			(uint8_t)(checksum),
			sound_module_end_byte};

	HAL_UART_Transmit(&huart5, cmd_sequence, BYTES_TO_TRANSMIT, DEFAULT_TIMEOUT);

}

void sm_select_track(uint8_t track)
{
  send_cmd(sound_module_select_track,sound_module_no_parameter,track);
}

void sm_select_eq(uint8_t mode)
{
  send_cmd(sound_module_eq,sound_module_no_parameter,mode);
}


void sm_init (uint8_t volume)
{
	send_cmd(sound_module_init, sound_module_no_parameter, SOURCE);
	HAL_Delay(DEFAULT_TIMEOUT);
	send_cmd(sound_module_volume, sound_module_no_parameter, volume);
}

void sm_next_track (void)
{
	send_cmd(sound_module_next, sound_module_no_parameter, sound_module_no_parameter);
}

void sm_pause_track (void)
{
	send_cmd(sound_module_pause, sound_module_no_parameter, sound_module_no_parameter);
}

void sm_stop_track (void)
{
	send_cmd(sound_module_stop, sound_module_no_parameter, sound_module_no_parameter);
}

void sm_previous_track (void)
{
	send_cmd(sound_module_previous, sound_module_no_parameter, sound_module_no_parameter);
}

void sm_change_volume(uint8_t volume)
{
	send_cmd(sound_module_volume, sound_module_no_parameter, volume);
}

void sm_repeat_track(bool repeat)
{
	send_cmd(sound_module_repeat, sound_module_no_parameter, repeat);
}

void sm_playback_track (void)
{
	send_cmd(sound_module_playback, sound_module_no_parameter, sound_module_no_parameter);
}



