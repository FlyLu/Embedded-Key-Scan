/***************************************************************************
 *   Copyright(C)2014-2015 by FlyLu <Linch.Embedded@gmail.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*============================ MACROS ========================================*/
//! \brief you can modify this value to adapt your program
#define QUEUE_SIZE          (5)

//! \brief Key event time calculation
//!        KEY_SCAN_TIME: how long to run key_task() function. e.g 20ms once

//! \brief KEY_DOWN Event  
//!        KEY_DOWN = KEY_SCAN_COUNT + 2
//!        KEY_DOWN Time = KEY_DOWN * KEY_SCAN_TIME
#define KEY_SCAN_COUNT      (5)     

//! \brief KEY_LONG_PRESSED Event  
//!        KEY_LONG_PRESSED =  KEY_DOWN + LONG_KEY_TIME
//!        KEY_LONG_PRESSED Time = KEY_LONG_PRESSED * KEY_SCAN_TIME
#define LONG_KEY_TIME       (20)    

//! \brief KEY_REPEAT Event 
//!        Frist KEY_REPEAT = KEY_LONG_PRESSED + KEY_REPEAT_TIME + 1
//!        Frist KEY_REPEAT Time = Frist KEY_REPEAT * KEY_SCAN_TIME
//!        After KEY_REPEAT Time = (KEY_REPEAT_TIME + 1) * KEY_SCAN_TIME
#define KEY_REPEAT_TIME     (10)    

//! \brief if KEY_USING_OS = 1, indicate your program run on the os. 
#define KEY_USING_OS        0

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
//! \name key status enum type
//! @{ 
typedef enum {
    KEY_NULL  = 0,      //!< no key press
    KEY_DOWN ,          //!< key press down
    KEY_UP,             //!< key release
    KEY_PRESSED,        //!< key pressed
    KEY_LONG_PRESSED,   //!< key long pressed
    KEY_REPEAT,         //!< key repeat
} key_status;
//! @}

//! \name key type 
//! @{
typedef struct {
    key_status tEvent;  //!< key type event
    uint8_t chKeyValue; //!< key value
} key_t;
//! @}

//! \name finit state machine state
//! @{
typedef enum {
    fsm_rt_err          = -1,    //!< fsm error, error code can be get from other interface
    fsm_rt_cpl          = 0,     //!< fsm complete
    fsm_rt_on_going     = 1,     //!< fsm on-going
    fsm_rt_wait_for_obj = 2,     //!< fsm wait for object
    fsm_rt_asyn         = 3,     //!< fsm asynchronose complete, you can check it later.
} fsm_rt_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief key initialization
 *! \param none
 *! \return none
 */
extern void key_init(void);

/*! \brief key task
 *! \param none
 *! \return none
 */
extern void key_task(void);

/*! \brief get key event
 *! \param ptKey key_t type pointer
 *! \return true get key event success
 *! \return false get key event fail
 */
extern bool get_key(key_t *ptKey);

/*============================ IMPLEMENTATION ================================*/
//! \brief you must to implment this function, you can refer key example.
extern uint8_t get_key_scaned_value();

#if KEY_USING_OS

//! \brief if KEY_USING_OS = 1, you must to implment this function, 
//!        you can refer key example.
extern void os_key_event_send(void);

#endif 

#endif 
/* EOF */
