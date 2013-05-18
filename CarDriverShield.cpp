/**
  ******************************************************************************
  * @file    CarDriverShield.cpp
  * @author  Elechouse Team
  * @version V1.0
  * @date    2013-05-16
  * @brief   This file provides all the CarDriverShield firmware functions.
  ******************************************************************************
    @note
         This driver is for elechouse Car Driver Shield(LINKS here)
  ******************************************************************************
  * @section  HISTORY
  
    V1.0    Initial version.

  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ELECHOUSE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 ELECHOUSE</center></h2>
  ******************************************************************************
  */

#include "CarDriverShield.h"

/**
	@brief MOTOR class constructor
*/
MOTOR :: MOTOR()
{

}

/**
	@brief begin function of MOTOR class, must called in Arduino **setup** funciton.
	@param led_num --> led pin number(any pin number except Arduino PWM pins)
				@arg -32768 -- do not use led indicating.
				@arg other valid pin number to set a pin as indicated led.
*/
void MOTOR :: begin(int led_num)
{
	/** LED config */
	led_sta = LED_STA_OFF;
	led_time = millis();
	MOTOR_LED_OUTPUT(led_num);
	led = led_num;
	
#ifdef USE_T0
	/** Timer0 PWM phase correct 8-bit, CLKio/8 */
	TCCR0A = 0;
    TCCR0B = 0;
	sbi(TCCR0A, WGM01);
    sbi(TCCR0A, WGM00);
    sbi(TCCR0B, CS00);
#else
	/** Timer1 PWM phase correct 8-bit, CLKio/8 */
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1C = 0;
	sbi(TCCR1A, WGM10);
	sbi(TCCR1B, CS10);
#endif

	/** Timer2 PWM phase correct 8-bit, CLKio/8 */
	TCCR2A = 0;
	TCCR2B = 0;
	sbi(TCCR2A, WGM20);
	sbi(TCCR2B, CS20);
	
#if 0
	/** EN and DIS pins are unconnected */
	pinMode(MOTOR_A_EN, OUTPUT);
	pinMode(MOTOR_A_DIS, OUTPUT);
	pinMode(MOTOR_B_EN, OUTPUT);
	pinMode(MOTOR_B_DIS, OUTPUT);

	digitalWrite(MOTOR_A_DIS, LOW);
	digitalWrite(MOTOR_B_DIS, LOW);
	digitalWrite(MOTOR_A_EN, HIGH);
	digitalWrite(MOTOR_B_EN, HIGH);
#endif

	/** PWM pin configurate */
	pinMode(MOTOR_A_NPORT, OUTPUT);
	pinMode(MOTOR_A_PPORT, OUTPUT);
	pinMode(MOTOR_B_NPORT, OUTPUT);
	pinMode(MOTOR_B_PPORT, OUTPUT);

	digitalWrite(MOTOR_A_NPORT, HIGH);
	digitalWrite(MOTOR_A_PPORT, HIGH);
	digitalWrite(MOTOR_B_NPORT, HIGH);
	digitalWrite(MOTOR_B_PPORT, HIGH);

	evt_time = millis();
	
	expected_velocity_a=0;
	expected_velocity_b=0;
	current_velocity_a=0;
	current_velocity_b=0;
	velocity_a_inc = 1;
	velocity_b_inc = 1;
	velocity = MOTOR_SPEED_INIT;
	state = MOTOR_STA_STOP;
	
	digitalWrite(9, LOW);
	digitalWrite(10, LOW);
	pinMode(9, INPUT);
	pinMode(10, INPUT);
	
}

/**
	@brief motor control function, set expected speed.
	@param ch --> channel selected.
				@arg AB -- both channel
				@arg A  -- A channel
				@arg B  -- B channel
	@param speed --> speed level to be set, the value can be -255~255.
					the bigger absolute value, the faster speed.
				@arg 0: stop, 
				@arg 1 - 255: forward speed.
				@arg -255 - -1: backward speed
*/
void MOTOR::set(motor_ch_type ch, int speed)
{
	switch(ch){
		case AB:
			expected_velocity_a = speed;
			expected_velocity_b = speed;
			break;
		case A:
			expected_velocity_a = speed;
			break;
		case B:
			expected_velocity_b = speed;
			break;
	}
}

/**
	@brief write speed to relevant register of specified channel.
	@param ch --> channel selected.
				@arg AB -- both channel
				@arg A  -- A channel
				@arg B  -- B channel
	@param speed --> speed level to be set, the value can be -255~255
					the bigger absolute value, the faster speed.
				@arg 0: stop, 
				@arg 1 - 255: forward speed.
				@arg -255 - -1: backward speed
*/
void MOTOR :: refresh(motor_ch_type ch, int speed)
{
	uint8_t sp;		/*!< speed's absolute value*/
	uint8_t dir;	/*!< direction */
	
	/** analyse speed value */
	if(speed > 0){
		sp = speed;
		dir = 1; // forward
	}else if(speed <0){
		sp = (0-speed);
		dir = 2; // backward
	}else{
		sp = 0;
		dir = 0; // stop
	}

	sp = ~sp;
	
	switch(ch){
		case AB:
			switch(dir){
				case 1:
					MOTOR_A_NPORT_REG = sp;
					MOTOR_A_NPORT_PWM_ON();
					MOTOR_A_PPORT_PWM_OFF();
					digitalWrite(MOTOR_A_PPORT, HIGH);
					MOTOR_B_PPORT_REG = sp;
					MOTOR_B_PPORT_PWM_ON();
					MOTOR_B_NPORT_PWM_OFF();
					digitalWrite(MOTOR_B_NPORT, HIGH);
					
					break;
				case 2:
					MOTOR_A_PPORT_REG = sp;
					MOTOR_A_PPORT_PWM_ON();
					MOTOR_A_NPORT_PWM_OFF();
					digitalWrite(MOTOR_A_NPORT, HIGH);
					MOTOR_B_NPORT_REG = sp;
					MOTOR_B_NPORT_PWM_ON();
					MOTOR_B_PPORT_PWM_OFF();
					digitalWrite(MOTOR_B_PPORT, HIGH);
					break;
				case 0:
					MOTOR_A_NPORT_PWM_OFF();
					MOTOR_A_PPORT_PWM_OFF();
					digitalWrite(MOTOR_A_NPORT, HIGH);
					digitalWrite(MOTOR_A_PPORT, HIGH);
					
					MOTOR_B_NPORT_PWM_OFF();
					MOTOR_B_PPORT_PWM_OFF();
					digitalWrite(MOTOR_B_NPORT, HIGH);
					digitalWrite(MOTOR_B_PPORT, HIGH);
					break;
			}
			break;
		case A:
			switch(dir){
				case 1:
					MOTOR_A_NPORT_REG = sp;
					MOTOR_A_NPORT_PWM_ON();
					MOTOR_A_PPORT_PWM_OFF();
					digitalWrite(MOTOR_A_PPORT, HIGH);
					break;
				case 2:
					MOTOR_A_PPORT_REG = sp;
					MOTOR_A_PPORT_PWM_ON();
					MOTOR_A_NPORT_PWM_OFF();
					digitalWrite(MOTOR_A_NPORT, HIGH);
					break;
				case 0:
					MOTOR_A_NPORT_PWM_OFF();
					MOTOR_A_PPORT_PWM_OFF();
					digitalWrite(MOTOR_A_NPORT, HIGH);
					digitalWrite(MOTOR_A_PPORT, HIGH);
					break;
			}
			break;
		case B:
			switch(dir){
				case 1:
					MOTOR_B_PPORT_REG = sp;
					MOTOR_B_PPORT_PWM_ON();
					MOTOR_B_NPORT_PWM_OFF();
					digitalWrite(MOTOR_B_NPORT, HIGH);
					break;
				case 2:
					MOTOR_B_NPORT_REG = sp;
					MOTOR_B_NPORT_PWM_ON();
					MOTOR_B_PPORT_PWM_OFF();
					digitalWrite(MOTOR_B_PPORT, HIGH);
					break;
				case 0:
					MOTOR_B_NPORT_PWM_OFF();
					MOTOR_B_PPORT_PWM_OFF();
					digitalWrite(MOTOR_B_NPORT, HIGH);
					digitalWrite(MOTOR_B_PPORT, HIGH);
					break;
			}
			break;
	}
	
}

/**
	@brief close motor driver output
	@param ch --> channel to close, the value must be A or B.
*/
void MOTOR::close(motor_ch_type ch)
{
	set(ch, 0);
}

/**
	@brief event loop. Refresh motor speed , process led state
			must called in arduino loop funciton
	NOTE: the funciton of refreshing motor speed 
			is for smooth accelerating and decelerating.
*/
void MOTOR :: evt_loop(void)
{
	led_process();
	
	evt_ms = millis();
	if( (evt_ms - evt_time) > MOTOR_TIME_PERIOD ){
		evt_time = evt_ms;
		
		if(expected_velocity_a > current_velocity_a){
			current_velocity_a += velocity_a_inc;
			if(current_velocity_a > expected_velocity_a){
				current_velocity_a = expected_velocity_a;
			}
			/** fresh speed */
			refresh(A, current_velocity_a);
		}else if(expected_velocity_a < current_velocity_a){
			current_velocity_a -= velocity_a_inc;
			if(current_velocity_a < expected_velocity_a){
				current_velocity_a = expected_velocity_a;
			}
			/** fresh speed */
			refresh(A, current_velocity_a);
		}
		
		if(expected_velocity_b > current_velocity_b){
			current_velocity_b += velocity_b_inc;
			if(current_velocity_b > expected_velocity_b){
				current_velocity_b = expected_velocity_b;
			}
			/** fresh speed */
			refresh(B, current_velocity_b);
		}else if(expected_velocity_b < current_velocity_b){
			current_velocity_b -= velocity_b_inc;
			if(current_velocity_b < expected_velocity_b){
				current_velocity_b = expected_velocity_b;
			}
			/** fresh speed */
			refresh(B, current_velocity_b);
		}
	}
}

/**
	@brief set forward speed, private function
	@param v --> speed value
				@arg 1-255
*/
void MOTOR :: forward(uint8_t v)
{
	state = MOTOR_STA_FORWARD;
	set(AB, v);
}

/**
	@brief set backward speed, private function
	@param v --> speed value 
*/
void MOTOR :: backward(uint8_t v)
{
	state = MOTOR_STA_BACKWARD;
	set(AB, 0-v);
}

/**
	@brief run forward, public function
*/
void MOTOR :: forward()
{
	velocity_a_inc=1;
	velocity_b_inc=1;
	forward(velocity);
	check_speed();
}

/**
	@brief run backward, public function
*/
void MOTOR :: backward()
{
	velocity_a_inc=1;
	velocity_b_inc=1;
	backward(velocity);
	check_speed();
}

/**
	@brief accelerate, public function
*/
void MOTOR :: accelerate()
{
	if( (state != MOTOR_STA_FORWARD) && (state != MOTOR_STA_BACKWARD)){
		return;
	}
	
	velocity += MOTOR_SPEED_INC;
	if(velocity > MOTOR_SPEED_MAX) {
		velocity = MOTOR_SPEED_MAX;
	}
	check_speed();

	switch(state) {
	case MOTOR_STA_FORWARD:
		forward();
		break;
	case MOTOR_STA_BACKWARD:
		backward();
		break;
	}

}

/**
	@brief decelerate, public function
*/
void MOTOR :: decelerate()
{
	if( (state != MOTOR_STA_FORWARD) && (state != MOTOR_STA_BACKWARD)){
		return;
	}
	velocity -= MOTOR_SPEED_INC;
	if(velocity < MOTOR_SPEED_MIN) {
		velocity = MOTOR_SPEED_MIN;
	}
	check_speed();

	switch(state) {
	case MOTOR_STA_FORWARD:
		forward();
		break;
	case MOTOR_STA_BACKWARD:
		backward();
		break;
	}
}

/**
	@brief check current speed, and
*/
void MOTOR :: check_speed()
{
	if(velocity == MOTOR_SPEED_MAX) {
		led_set(LED_STA_ON);
		//Serial.println("SpeedMax");
	} else if(velocity > ((2*MOTOR_SPEED_MAX+MOTOR_SPEED_MIN)/3)) {
		led_set(LED_STA_BLK_FAST);
		//Serial.println("SpeedMax2");
	} else if(velocity > ((MOTOR_SPEED_MAX+2*MOTOR_SPEED_MIN)/3)) {
		led_set(LED_STA_BLK_QUICK);
		//Serial.println("SpeedMax3");
	} else if(velocity == MOTOR_SPEED_MIN) {
		led_set(LED_STA_ON);
		//Serial.println("SpeedMax4");
	} else {
		led_set(LED_STA_BLK);
		//Serial.println("SpeedMax5");
	}
}

/**
	@brief turn direction funciton
	@param ls --> left side wheels speed
				@arg --> 0 - 255
	@param rs --> right side wheels speed
				@arg --> 0 - 255
*/
void MOTOR :: turn(uint8_t ls, uint8_t rs)
{
	if(rs>ls){
		velocity_a_inc=3;
		velocity_b_inc=1;
	}else{
		velocity_a_inc=1;
		velocity_b_inc=3;
	}
	set(A,rs);
	set(B,ls);
}

/**
	@brief turn left
*/
void MOTOR :: turn_left()
{
	state = MOTOR_STA_TURN_LEFT_F;
	turn(MOTOR_SPEED_TURN_SLOW, MOTOR_SPEED_TURN_FAST);
}

/**
	@brief turn right
*/
void MOTOR :: turn_right()
{
	state = MOTOR_STA_TURN_RIGHT_F;
	turn(MOTOR_SPEED_TURN_FAST, MOTOR_SPEED_TURN_SLOW);
}

/**
	@brief stop 
*/
void MOTOR :: stop()
{
	/** car stop */
	state = MOTOR_STA_STOP;
	close(AB);
	led_set(LED_STA_OFF);
}

/**
	@brief set led state
	@param sta --> new state of led
				@arg LED_STA_OFF		-- turn off led
				@arg LED_STA_ON			-- turn on led
				@arg LED_STA_BLK		-- set led blink, blinking slowly
				@arg LED_STA_BLK_QUICK	-- blinking quickly
				@arg LED_STA_BLK_FAST	-- blinking fast
*/
void MOTOR :: led_set(led_sta_t sta)
{
	if(led == -32768){
		return;
	}

	if(sta == led_sta) {
		return;
	}
	led_sta = sta;
	switch(sta) {
	case LED_STA_OFF:
		MOTOR_LED_OFF(led);
		break;
	case LED_STA_ON:
		MOTOR_LED_ON(led);
		break;
	case LED_STA_BLK:
	case LED_STA_BLK_QUICK:
	case LED_STA_BLK_FAST:
		MOTOR_LED_ON(led);
		led_time = millis();
		break;
	}
}

/**
	@brief led state handle, called in evt_loop, private function
*/
void MOTOR :: led_process()
{
	if(led == -32768){
		return;
	}
	switch(led_sta) {
	case LED_STA_OFF:
		break;
	case LED_STA_ON:
		break;
	case LED_STA_BLK:
		led_ms = millis();
		if( (led_ms-led_time) > MOTOR_LED_TIME_PERIOD0) {
			led_time = led_ms;
			MOTOR_LED_V(led);
		}
		break;
	case LED_STA_BLK_QUICK:
		led_ms = millis();
		if( (led_ms-led_time) > MOTOR_LED_TIME_PERIOD1) {
			led_time = led_ms;
			MOTOR_LED_V(led);
		}
		break;
	case LED_STA_BLK_FAST:
		led_ms = millis();
		if( (led_ms-led_time) > MOTOR_LED_TIME_PERIOD2) {
			led_time = led_ms;
			MOTOR_LED_V(led);
		}
		break;
	}

}

/************************** (C) COPYRIGHT 2013 ELECHOUSE **********************/


