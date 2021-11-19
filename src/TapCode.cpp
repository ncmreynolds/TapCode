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
void ICACHE_FLASH_ATTR TapCode::begin(uint8_t max_length, uint32_t press_timeout, uint32_t word_timeout)	{
#else
void TapCode::begin(uint8_t max_length, uint32_t press_timeout, uint32_t word_timeout)	{
#endif
	if(debug_uart_ != nullptr)
	{
		debug_uart_->print(F("Tap decoder running on pin "));
		debug_uart_->print(tap_pin_);
		debug_uart_->print(F(" maximum input length "));
		debug_uart_->println(max_length);
		if(press_timeout != press_timeout_)
		{
			debug_uart_->print(F("Button press timeout "));
			debug_uart_->print(press_timeout);
			debug_uart_->println("ms");
		}
		if(word_timeout != word_timeout_)
		{
			debug_uart_->print(F("Word entry timeout "));
			debug_uart_->print(word_timeout);
			debug_uart_->println("ms");
		}
	}
	tapped_code_ = new char[max_length];
	max_length_ = max_length;
	press_timeout_ = press_timeout;
	word_timeout_ = word_timeout;
	this->tap_button_.begin();
}


#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::reset() {
#else
void TapCode::reset() {
#endif
	row_ = 0;
	column_ = 0;
	changed_ = false;
	finished_ = false;
	length_ = 0;	//Reset the accumulated string
	tapped_code_[0] = char(0);
}

#if defined(ESP8266) || defined(ESP32)
void  ICACHE_FLASH_ATTR TapCode::read(){
#else
void TapCode::read(){
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
	if(presses_ == 0 && millis() - press_time_ > word_timeout_)	//Letter or word timeout
	{
		if(row_ != 0)	//Letter timeout
		{
			if(debug_uart_ != nullptr)
			{
				debug_uart_->println(F("Letter timeout"));
			}
			row_ = 0;
		}
		else if(length_ > 0 && finished_ == false)
		{
			if(debug_uart_ != nullptr)
			{
				debug_uart_->println(F("Word finished"));
			}
			finished_ = true;
		}
	}
}

#if defined(ESP8266) || defined(ESP32)
uint8_t  ICACHE_FLASH_ATTR TapCode::length(){
#else
uint8_t TapCode::length(){
#endif
	return(length_);
}

#if defined(ESP8266) || defined(ESP32)
bool  ICACHE_FLASH_ATTR TapCode::changed(){
#else
bool TapCode::changed(){
#endif
	if(changed_ == true)
	{
		changed_ = false;
		return(true);
	}
	return(false);
}

#if defined(ESP8266) || defined(ESP32)
bool  ICACHE_FLASH_ATTR TapCode::finished(){
#else
bool TapCode::finished(){
#endif
	if(finished_ == true)
	{
		finished_ = false;
		press_time_ = millis();
		return(true);
	}
	return(false);
}

#if defined(ESP8266) || defined(ESP32)
bool  ICACHE_FLASH_ATTR TapCode::matches(char* stringToMatch){
#else
bool TapCode::matches(char* stringToMatch){
#endif
	if(stringToMatch == nullptr)
	{
		return(false);
	}
	if(strlen(stringToMatch) != length_)
	{
		return(false);
	}
	for(uint8_t index = 0; index < length_ ; index++)
	{
		char characterToMatch = toupper(stringToMatch[index]);
		if(characterToMatch == 'K') {
			characterToMatch = 'C';
		}
		if(characterToMatch != tapped_code_[index])
		{
			return(false);
		}
	}	
	return(true);
}


#if defined(ESP8266) || defined(ESP32)
char*  ICACHE_FLASH_ATTR TapCode::word(){
#else
char* TapCode::word(){
#endif
	return(tapped_code_);
}

#if defined(ESP8266) || defined(ESP32)
void ICACHE_FLASH_ATTR TapCode::debug(Stream &terminalStream)
#else
void TapCode::debug(Stream &terminalStream)
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

#endif
