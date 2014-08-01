
/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "AACI.h"

#if DEVICE_AACI

namespace mbed {

AACI *AACI::_owner = NULL;

AACI::AACI(PinName sda, PinName scl) {
    // The init function also set the frequency to 100000
    audio_aaci_init(&_aaci);
    _hz = 100000;

    // Used to avoid unnecessary frequency updates
    _owner = this;
}

void AACI::aquire() {
    if (_owner != this) {
        _owner = this;
    }
}

unsigned char AACI::AACI_INIT() {
	aquire();
    return audio_aaci_init(&_aaci);
}
// write - Master Transmitter Mode
void AACI::AACI_WRITE_SINE(){ //unsigned char reg_addr, unsigned char data_byte, unsigned char sadr) {
    aquire();

    audio_aaci_out_sine(); //reg_addr, data_byte, sadr);

}


// read - Master Reciever Mode
unsigned int AACI::AACI_READ() {
		unsigned int rxdata;
    aquire();

		rxdata = audio_aaci_read();
		
		return rxdata;
}

// read - Master Reciever Mode
void AACI::AACI_WRITE(unsigned int data) {
    aquire();

		audio_aaci_write(data);
}

void AACI::AACI_VOLUME(unsigned int data) {
    aquire();

		audio_aaci_volume(data);
}

unsigned char AACI::AUDIO_I2C_READ (unsigned char reg_addr, unsigned char sadr)
{
	return audio_i2c_read(reg_addr,sadr);
}

void AACI::AUDIO_I2C_WRITE(unsigned char reg_addr, unsigned char data_byte, unsigned char sadr)
{
	audio_i2c_write(reg_addr,data_byte,sadr);		
}




} // namespace mbed

#endif
