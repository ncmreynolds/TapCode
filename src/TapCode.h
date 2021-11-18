/*
 *	A decoder for 'tap code' entered with a single button
 *
 *	https://github.com/ncmreynolds/TapCode
 *
 *	Released under LGPL-2.1 see https://github.com/ncmreynolds/TapCode/LICENSE for full license
 *
 */
#ifndef TapCode_h
#define TapCode_h
#include <Arduino.h>
#include <EasyButton.h>

class TapCode	{

	public:
		TapCode(uint8_t);														//Constructor function
		~TapCode();																//Destructor function
		void begin(uint8_t input_length = 64);									//Start the tap input
		void Housekeeping();													//Do housekeeping checking for pushes
		void Reset();															//Reset the accumulated string
		void Debug(Stream &);													//Enable debug output on a Serial stream
		uint8_t Length();														//Length of the input string
		char* Text();															//Returns a pointer to the text string
	protected:
	private:
		//void onPressed();														//Callback function for when button is pressed
		Stream *debug_uart_ = nullptr;											//The stream used for the terminal UART
		EasyButton tap_button_;
		uint8_t tap_pin_ = 0;													//The pin to read for tapping
		char polybius_square_[25] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',			//The square used for encoding/decoding
			'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
			'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
		uint8_t length_ = 0;														//The current length of the tapped string
		uint8_t max_length_ = 0;													//The maximum length of the tapped string, set in the contructor defaults to 64
		char* tapped_code_ = nullptr;											//Pointer to the current string
		uint8_t row_ = 0;														//Tapped row
		uint8_t column_ = 0;													//Tapped column
		bool pressed_ = false;													//Is the button currently pressed
		uint32_t press_time_ = 0;												//When was the button pressed
		uint32_t press_timeout_ = 1000;											//Timeout for presses
		uint8_t presses_ = 0;
};
#endif
