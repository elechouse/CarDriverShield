/**
  ******************************************************************************
  * @file    CarDriverShield.h
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

#ifndef __CAR_DRIVER_SHIELD_H
#define __CAR_DRIVER_SHIELD_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "wiring_private.h"

#define USE_T0

#ifdef USE_T0
	#define MOTOR_A_EN                      			/*!< Unconnected Arduino pin */
	#define MOTOR_A_DIS                     			/*!< Arduino pin */
	#define MOTOR_A_NPORT                   3    		/*!< PWM OC2B*/
	#define MOTOR_A_PPORT                   11			/*!< PWM OC2A */
	#define MOTOR_A_NPORT_REG				OCR2B		/*!< PWM OC2A output compare register*/
	#define MOTOR_A_PPORT_REG               OCR2A		/*!< PWM OC2B output compare register*/
	#define MOTOR_A_NPORT_PWM_ON()          sbi(TCCR2A, COM2B1);	/*!< enable portA negative pin PWM*/
	#define MOTOR_A_NPORT_PWM_OFF()         cbi(TCCR2A, COM2B1);	/*!< disable portA negative pin PWM*/
	#define MOTOR_A_PPORT_PWM_ON()          sbi(TCCR2A, COM2A1);	/*!< enable portA positive pin PWM*/
	#define MOTOR_A_PPORT_PWM_OFF()         cbi(TCCR2A, COM2A1);	/*!< disable portA positive pin PWM*/
	
	#define MOTOR_B_EN                      			/*!< Arduino pin */
	#define MOTOR_B_DIS                     			/*!< Arduino pin */
	#define MOTOR_B_NPORT                   6			/*!< PWM OC1A*/
	#define MOTOR_B_PPORT                   5			/*!< PWM OC1B*/
	#define MOTOR_B_NPORT_REG				OCR0A		/*!< PWM OC1A output compare register*/
	#define MOTOR_B_PPORT_REG               OCR0B		/*!< PWM OC1B output compare register*/
	#define MOTOR_B_NPORT_PWM_ON()          sbi(TCCR0A, COM0A1);	/*!< enable portB negative pin PWM*/
	#define MOTOR_B_NPORT_PWM_OFF()         cbi(TCCR0A, COM0A1);	/*!< disable portB negative pin PWM*/
	#define MOTOR_B_PPORT_PWM_ON()          sbi(TCCR0A, COM0B1);	/*!< enable portB positive pin PWM*/
	#define MOTOR_B_PPORT_PWM_OFF()         cbi(TCCR0A, COM0B1);	/*!< disable portB positive pin PWM*/
#else
	#define MOTOR_A_EN                      2			/*!< Arduino pin */
	#define MOTOR_A_DIS                     4			/*!< Arduino pin */
	#define MOTOR_A_NPORT                   3    		/*!< PWM OC2B*/
	#define MOTOR_A_PPORT                   11			/*!< PWM OC2A */
	#define MOTOR_A_NPORT_REG				OCR2B		/*!< PWM OC2A output compare register*/
	#define MOTOR_A_PPORT_REG               OCR2A		/*!< PWM OC2B output compare register*/

	#define MOTOR_B_EN                      8			/*!< Arduino pin */
	#define MOTOR_B_DIS                     7			/*!< Arduino pin */
	#define MOTOR_B_NPORT                   9			/*!< PWM OC1A*/
	#define MOTOR_B_PPORT                   10			/*!< PWM OC1B*/
	#define MOTOR_B_NPORT_REG				OCR1A		/*!< PWM OC1A output compare register*/
	#define MOTOR_B_PPORT_REG               OCR1B		/*!< PWM OC1B output compare register*/

	#define MOTOR_A_NPORT_PWM_ON()          sbi(TCCR2A, COM2B1);	/*!< enable portA negative pin PWM*/
	#define MOTOR_A_NPORT_PWM_OFF()         cbi(TCCR2A, COM2B1);	/*!< disable portA negative pin PWM*/
	#define MOTOR_A_PPORT_PWM_ON()          sbi(TCCR2A, COM2A1);	/*!< enable portA positive pin PWM*/
	#define MOTOR_A_PPORT_PWM_OFF()         cbi(TCCR2A, COM2A1);	/*!< disable portA positive pin PWM*/

	#define MOTOR_B_NPORT_PWM_ON()          sbi(TCCR1A, COM1A1);	/*!< enable portB negative pin PWM*/
	#define MOTOR_B_NPORT_PWM_OFF()         cbi(TCCR1A, COM1A1);	/*!< disable portB negative pin PWM*/
	#define MOTOR_B_PPORT_PWM_ON()          sbi(TCCR1A, COM1B1);	/*!< enable portB positive pin PWM*/
	#define MOTOR_B_PPORT_PWM_OFF()         cbi(TCCR1A, COM1B1);	/*!< disable portB positive pin PWM*/
#endif



#define MOTOR_SPEED_MAX                 230						/*!< motor maximum speed, embodied PWM duty cycle*/
#define MOTOR_SPEED_MIN                 85						/*!< motor minimum speed, embodied PWM duty cycle*/
#define MOTOR_SPEED_INIT                ((MOTOR_SPEED_MAX+MOTOR_SPEED_MIN)/2) /*!< motor initial speed */
#define MOTOR_SPEED_INC                 5						/*!< coefficient of decelerating and acccelerating */
#define MOTOR_SPEED_TURN_SLOW           67						/*!< slow side speed of turning */
#define MOTOR_SPEED_TURN_FAST           200						/*!< fast side speed of turning */

#define MOTOR_STA_STOP                  0			/*!< motor Stop state */
#define MOTOR_STA_FORWARD               1			/*!< motor FORWARD state */
#define MOTOR_STA_BACKWARD              2			/*!< motor BACKWARD state */
#define MOTOR_STA_TURN_LEFT_F           3			/*!< motor FORWARD TURN LEFT state */
#define MOTOR_STA_TURN_RIGHT_F          4			/*!< motor FORWARD TURN RIGHT state  */
#define MOTOR_STA_TURN_LEFT_B           5			/*!< motor BACKWARD TURN LEFT state */
#define MOTOR_STA_TURN_RIGHT_B          6			/*!< motor BACKWARD TURN RIGHT state */

/** LED related macros */
#define MOTOR_LED_OUTPUT(x)				pinMode(x, OUTPUT);						/*!< set mode */
#define MOTOR_LED_ON(x)					digitalWrite(x, HIGH)					/*!< write pin HIGH LEVEL */
#define MOTOR_LED_OFF(x)				digitalWrite(x, LOW)					/*!< write pin LOW LEVEL */
#define MOTOR_LED_V(x)					digitalWrite(x, \
										(digitalRead(x)==HIGH)? LOW : HIGH)		/*!< toggle pin level */
#define MOTOR_LED_TIME_PERIOD0			(500*64)
#define MOTOR_LED_TIME_PERIOD1			(200*64)
#define MOTOR_LED_TIME_PERIOD2			(50*64)

#define MOTOR_TIME_PERIOD				(2*64)			/*!< motor speed refresh period */


/** LED state type define*/
typedef enum{
	LED_STA_OFF, 				/*!< LED OFF state */
	LED_STA_ON, 				/*!< LED ON state */
	LED_STA_BLK, 				/*!< LED general BLINK state */
	LED_STA_BLK_QUICK, 			/*!< LED QUICK BLINK state */
	LED_STA_BLK_FAST			/*!< LED FAST BLINK state */
}led_sta_t;

/** motor channel define */
typedef enum{
    AB=0,	/*!< select both channel */
    A=1,	/*!< select A channel */
	B=2,	/*!< select B channel */
}motor_ch_type;

// typedef enum{
    // FORWARD,
    // REVERSE,
// }motor_direction_type;

class MOTOR{
public:
	MOTOR();
	void begin(int led_num = -32768);/** By default don't use LED */
	
	void forward();
	void backward();
	
	void accelerate();
	void decelerate();
	
	void turn_left();
	void turn_right();
	void stop();
	
	void evt_loop();
	
private:
	void set(motor_ch_type ch, int speed);
	void forward(uint8_t v);
	void backward(uint8_t v);
	void refresh(motor_ch_type ch, int speed);
	void close(motor_ch_type ch);
	void turn(uint8_t ls, uint8_t rs);
	
	/**LED*/
	void check_speed();
	void led_process();
	void led_set(led_sta_t sta);
	
	int expected_velocity_a;		/*!< A channel expected velocity */
	int expected_velocity_b;		/*!< B channel expected velocity */
	int current_velocity_a;			/*!< A channel current velocity */
	int current_velocity_b;			/*!< B channel current velocity */
	int velocity_a_inc;				/*!< A channel speed increament coefficient */
	int velocity_b_inc;				/*!< B channel speed increament coefficient */
	int velocity;					/*!< global velocity */
	
	/** event time count */
	unsigned long evt_time, evt_ms;
	
	/** MOTOR state */
	int state;
	
	/** LED part */
	uint8_t led;						/*!< LED pin record */
	led_sta_t led_sta;					/*!< LED state */
	unsigned long led_time, led_ms;		/*!< LED time count */
	
};

/** some alias */
typedef MOTOR CarDriverShield;
typedef MOTOR CarDriver;
typedef MOTOR CARDRIVER;

#endif/** __CAR_DRIVER_SHIELD_H */

/************************** (C) COPYRIGHT 2013 ELECHOUSE **********************/