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

/*============================ INCLUDES ======================================*/
#include ".\key.h"
#include ".\queue\queue.h"

/*============================ MACROS ========================================*/
//! \brief need to key sacn counter defined
#ifndef KEY_SCAN_COUNT
#error No defined KEY_SCAN_COUNT
#endif 

//! \brief need to key long pressed counter defined
#ifndef LONG_KEY_TIME
#error No defined LONG_KEY_TIME
#endif

//! \brief need to key repeat counter defined
#ifndef KEY_REPEAT_TIME
#error No defined KEY_REPEAT_TIME
#endif 

//! \brief need to queue size defined
#ifndef QUEUE_SIZE
#error No defined QUEUE_SIZE
#endif 
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
//! \brief key frontend buffer
static key_t s_tKeyFrontendBuff[QUEUE_SIZE]; 

//! \brief key detector buffer
static key_t s_tKeyDetectorBuff[QUEUE_SIZE]; 

//! \brief key frontend queue
static key_queue_t s_tKeyFrontendFIFO;

//! \brief key detector queue
static key_queue_t s_tKeyDetectorFIFO;

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
#define FILTER_RESET_FSM()  do {s_tState = START;} while (0) 

/*! \brief key filter and compare key value
 *! \param key value 
 *! \return state machine status
 */
static fsm_rt_t filter(uint8_t  chByte)
{
    static uint32_t s_wCount;
    static key_t s_tKey;
    static key_t s_tLastKey;
    static enum {
        START = 0,
        COMPARE,
    } s_tState = START;

    switch (s_tState) {
        case START:
            s_wCount = 0;
            s_tLastKey.chKeyValue = 0;
            s_tState = COMPARE;
            //break;

        case COMPARE:
            s_tKey.chKeyValue = chByte;
            if (s_tLastKey.chKeyValue == s_tKey.chKeyValue) {
                if (s_wCount < KEY_SCAN_COUNT) {
                    s_wCount++;                      
                } else {
                    FILTER_RESET_FSM();
                    return fsm_rt_cpl;
                }
            } else {
                if (s_wCount > 0) {
                    s_wCount--;
                } else {
                    s_tLastKey = s_tKey;
                }
            }
            break;
    }
   
    return fsm_rt_on_going;
}


#define KEY_FRONTEND_RESET_FSM()   do {s_tState = START;} while (0)

/*! \brief key frontend process
 *! \param none 
 *! \return state machine status
 */
static fsm_rt_t key_frontend(void)
{
    static key_t s_tKey;
    static key_t s_tLastKey;
    static enum {
        START = 0,
        GET_KEY_1,
        GET_KEY_2,
        CHECK_UP,
        CHECK_DOWN,
    } s_tState = START;

    switch (s_tState) {
        case START:
            s_tState = GET_KEY_1;
            //break;

        case GET_KEY_1:
            s_tKey.chKeyValue = GET_KEY_SCANED_VALUE();
            if (fsm_rt_cpl == filter(s_tKey.chKeyValue)) {
                s_tState = CHECK_DOWN;  
            }
            break;
        
        case CHECK_DOWN:
            if (KEY_NULL != s_tKey.chKeyValue) {
                s_tKey.tEvent = KEY_DOWN;
                KEY_ENQUEUE(&s_tKeyFrontendFIFO, s_tKey);
                s_tLastKey = s_tKey;
                s_tState = GET_KEY_2;  
            } else {
                s_tState = GET_KEY_1;
            }
            break;
        
        case GET_KEY_2:
            s_tKey.chKeyValue = GET_KEY_SCANED_VALUE();
            if (fsm_rt_cpl == filter(s_tKey.chKeyValue)) {
                s_tState = CHECK_UP;  
            }
            break;

        case CHECK_UP:
            if (s_tLastKey.chKeyValue != s_tKey.chKeyValue) {
                s_tLastKey.tEvent = KEY_UP;
                KEY_ENQUEUE(&s_tKeyFrontendFIFO, s_tLastKey);
                KEY_FRONTEND_RESET_FSM();
                return fsm_rt_cpl;
            } else {
                s_tState = GET_KEY_2;
            }
            break;  
    }

    return fsm_rt_on_going;
}


#define KEY_DETECTOR_RESET_FSM()    do {s_tState = START;} while (0)

/*! \brief key detector process
 *! \param none 
 *! \return state machine status
 */
fsm_rt_t key_detector(void)
{
    static key_t s_tKey;
    static uint32_t s_wTimeOut;
    static enum {
        START = 0,
        GET_KEY_1,
        GET_KEY_2,
        GET_KEY_3,
        CHECK_UP_1,
        CHECK_UP_2,
        CHECK_DOWN,
        CHECK_LONG_KEY,
        CHECK_REPEAT_KEY,
    } s_tState = START;

    switch (s_tState) {
        case START:
            s_wTimeOut = 0;
            s_tState = GET_KEY_1;
            //break;

        case GET_KEY_1:
            if (KEY_DEQUEUE(&s_tKeyFrontendFIFO, &s_tKey)) {
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);
                s_tState = CHECK_DOWN;
            }
            break;

        case CHECK_DOWN:
            if (KEY_DOWN == s_tKey.tEvent) {
                s_tState = CHECK_LONG_KEY;
            } else {
                KEY_DETECTOR_RESET_FSM();
            }
            break;

        case CHECK_LONG_KEY:
            if (LONG_KEY_TIME <= s_wTimeOut++) {
                s_tKey.tEvent = KEY_LONG_PRESSED;
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);   
                s_wTimeOut = 0;
                s_tState = GET_KEY_3;
            } else {
                s_tState = GET_KEY_2;
            }
            break;
            
        case GET_KEY_2:
            if (KEY_DEQUEUE(&s_tKeyFrontendFIFO, &s_tKey)) {
                s_tState = CHECK_UP_1;
            } else {
                s_tState = CHECK_LONG_KEY;
            }
            break;
            
        case CHECK_UP_1:
            if (KEY_UP == s_tKey.tEvent) {
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);
                s_tKey.tEvent = KEY_PRESSED;
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);
                KEY_DETECTOR_RESET_FSM();
                return fsm_rt_cpl;
            } else {
                KEY_DETECTOR_RESET_FSM();
            }
            break;

        case GET_KEY_3:
            if (KEY_DEQUEUE(&s_tKeyFrontendFIFO, &s_tKey)) {
                s_tState = CHECK_UP_2;
            } else {
                s_tState = CHECK_REPEAT_KEY;
            }
            break;

        case CHECK_UP_2:
            if (KEY_UP == s_tKey.tEvent) {
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);
                KEY_DETECTOR_RESET_FSM();
                return fsm_rt_cpl;      
            }
            s_tState = GET_KEY_3;
            break;

        case CHECK_REPEAT_KEY:
            if (KEY_REPEAT_TIME <= s_wTimeOut++) {
                s_wTimeOut = 0;
                s_tKey.tEvent = KEY_REPEAT;
                KEY_ENQUEUE(&s_tKeyDetectorFIFO, s_tKey);
            }
            s_tState = GET_KEY_3;
            break;
    }

    return fsm_rt_on_going;
}


/*! \brief key initialization
 *! \param none
 *! \return none
 */
void key_init(void)
{
    INIT_KEY_QUEUE(&s_tKeyFrontendFIFO,  s_tKeyFrontendBuff, QUEUE_SIZE);
    INIT_KEY_QUEUE(&s_tKeyDetectorFIFO, s_tKeyDetectorBuff, QUEUE_SIZE);
}


/*! \brief key task
 *! \param none
 *! \return none
 */
void key_task(void)
{
    key_frontend();
    key_detector();
}


/*! \brief get key event
 *! \param ptKey key_t type pointer
 *! \return true get key event success
 *! \return false get key event fail
 */
bool get_key(key_t *ptKey)
{
    if (NULL == ptKey) {
        return false;
    }

    if (KEY_DEQUEUE(&s_tKeyDetectorFIFO, ptKey)) {
        return true;
    }

    return false;
}


/* EOF */
