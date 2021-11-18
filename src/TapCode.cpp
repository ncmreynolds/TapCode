/*
 *	A decoder for 'tap code' entered with a single button
 *
 *	https://github.com/ncmreynolds/TapCode
 *
 *	Released under LGPL-2.1 see https://github.com/ncmreynolds/TapCode/LICENSE for full license
 *
 */
#ifndef TapCode_cpp
#define TapCode_cpp
#include "TapCode.h"


TapCode::TapCode(uint8_t button)	//Constructor function
  : tap_button_(button)				//Calls constructor of class EasyButton
{
	tap_pin_ = button;
}

TapCode::~TapCode()	//Destructor function
{
}

#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::begin(uint8_t input_length)	{
#else
void TapCode::begin(uint8_t input_length)	{
#endif
	if(debug_uart_ != nullptr)
	{
		debug_uart_->print(F("Tap decoder running on pin "));
		debug_uart_->print(tap_pin_);
		debug_uart_->print(F(" maximum input length "));
		debug_uart_->println(input_length);
	}
	tapped_code_ = new char[input_length];
	max_length_ = input_length;
	this->tap_button_.begin();
	//this->tap_button_.onPressed(onPressed());
}


#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::Reset() {
#else
void TapCode::Reset() {
#endif
	length_ = 0;	//Reset the accumulated string
	tapped_code_[0] = char(0);
}

#if defined(ESP8266) || defined(ESP32)
void  ICACHE_FLASH_ATTR TapCode::Housekeeping(){
#else
void TapCode::Housekeeping(){
#endif
	this->tap_button_.read();
	if(this->tap_button_.isPressed() && pressed_ == false)
	{
		pressed_ = true;
		press_time_ = millis();
		presses_++;
		if(debug_uart_ != nullptr)
		{
			if(row_ == 0)
			{
				debug_uart_->print(F("Row "));
			}
			else
			{
				debug_uart_->print(F("Column "));
			}
			debug_uart_->println(presses_);
		}

	}
	if(this->tap_button_.isReleased() && pressed_ == true)
	{
		pressed_ = false;
		/*if(debug_uart_ != nullptr)
		{
			debug_uart_->println(F("Released"));
		}*/

	}
	if((presses_ > 0 && millis() - press_time_ > press_timeout_) || presses_ == 5)
	{
		if(row_ == 0)
		{
			row_ = presses_;
			presses_ = 0;
			press_time_ = millis();
			if(debug_uart_ != nullptr)
			{
				debug_uart_->print(F("Row "));
				debug_uart_->print(row_);
				debug_uart_->println(F(" selected"));
			}

		}
		else if(column_ == 0)
		{
			column_ = presses_;
			presses_ = 0;
			press_time_ = millis();
			if(debug_uart_ != nullptr)
			{
				debug_uart_->print(F("Column "));
				debug_uart_->print(column_);
				debug_uart_->println(F(" selected"));
			}
		}
		if(column_ > 0 && row_ > 0)
		{
			if(length_ < max_length_)
			{
				tapped_code_[length_++] = polybius_square_[(column_ - 1) + ((row_ - 1) * 5)];
				tapped_code_[length_] = char(0);	//Ensure null termination!
				column_ = 0;
				row_ = 0;
				if(debug_uart_ != nullptr)
				{
					debug_uart_->println(tapped_code_);
				}
			}
		}
	}
}

#if defined(ESP8266) || defined(ESP32)
uint8_t  ICACHE_FLASH_ATTR TapCode::Length(){
#else
uint8_t TapCode::Length(){
#endif
	return(length_);
}

#if defined(ESP8266) || defined(ESP32)
char*  ICACHE_FLASH_ATTR TapCode::Text(){
#else
char* TapCode::Text(){
#endif
	return(tapped_code_);
}

#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::Debug(Stream &terminalStream)
#else
void TapCode::Debug(Stream &terminalStream)
#endif
{
	debug_uart_ = &terminalStream;		//Set the stream used for the terminal
	#if defined(ESP8266)
	if(&terminalStream == &Serial)
	{
		  debug_uart_->write(17);			//Send an XON to stop the hung terminal after reset on ESP8266
	}
	#endif
}

/*#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::onPressed()
#else
void TapCode::onPressed()
#endif
{
	if(debug_uart_ != nullptr)
	{
		debug_uart_->println("Tap code button pressed");
	}
}*/
#endif
