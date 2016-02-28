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
 #include ".\key.h"

 
#define PRINT_RESET_FSM()   do {s_tState = START;} while(0)

fsm_rt_t print(uint8_t *pchStr) 
{
    static uint8_t *s_pchStr;
    static enum {
        START = 0,
        CHECK,
        PRINT,
    } s_tState = START;

    switch (s_tState) {
        case START:
            s_pchStr = pchStr;
            s_tState = CHECK;
            //break;

        case CHECK:
            if (0 != *s_pchStr) {
                s_tState = PRINT;
            } else {
                PRINT_RESET_FSM();
                return fsm_rt_cpl;
            }

        case PRINT:
            if (GENERAL_OUTPUT(*s_pchStr)) {
                s_pchStr ++;
                s_tState = CHECK;
            }
            break;
    }

    return fsm_rt_on_going;
}

#define KEY_1   1
#define KEY_2   2


uint8_t get_key_scaned_value()
{
    if (IS_KEY1_DOWN()) {
        return KEY_1;	 	
    } else if (IS_KEY2_DOWN() ) {
		return KEY_2;
    } else {
        return KEY_NULL;
    }
}



#define KEY_APP_RESET_FSM()     do {s_tState = START;} while(0)

fsm_rt_t key_app(void)
{
    static key_t s_tKey;
    static enum {
        START = 0,
        CHECK_KEY,
        KEY_1_UP,
        KEY_1_DOWN,
        KEY_1_PRESSED,
        KEY_1_LONG_PRESSED,
        KEY_1_REPEATE,
        KEY_2_UP,
        KEY_2_DOWN,
        KEY_2_PRESSED,
        KEY_2_LONG_PRESSED,
        KEY_2_REPEATE,
    } s_tState = START;

    switch (s_tState) {
        case START:
            s_tState = CHECK_KEY;
            //break;

        case CHECK_KEY:
            if (get_key(&s_tKey)) {
                if (KEY_1 == s_tKey.chKeyValue) {
                    if (KEY_UP == s_tKey.tEvent) {
                        s_tState = KEY_1_UP;
                    } else if (KEY_DOWN == s_tKey.tEvent) {
                        s_tState = KEY_1_DOWN;
                    } else if (KEY_PRESSED == s_tKey.tEvent) {
                        s_tState = KEY_1_PRESSED;
                    } else if (KEY_LONG_PRESSED == s_tKey.tEvent) {
                        s_tState = KEY_1_LONG_PRESSED;
                    } else if (KEY_REPEAT == s_tKey.tEvent) {
                        s_tState = KEY_1_REPEATE;
                    }
                } else if (KEY_2 == s_tKey.chKeyValue) {
                    if (KEY_UP == s_tKey.tEvent) {
                        s_tState = KEY_2_UP;
                    } else if (KEY_DOWN == s_tKey.tEvent) {
                        s_tState = KEY_2_DOWN;
                    } else if (KEY_PRESSED == s_tKey.tEvent) {
                        s_tState = KEY_2_PRESSED;
                    } else if (KEY_LONG_PRESSED == s_tKey.tEvent) {
                        s_tState = KEY_2_LONG_PRESSED;
                    } else if (KEY_REPEAT == s_tKey.tEvent) {
                        s_tState = KEY_2_REPEATE;
                    }
                }
            } 
            break;

        case KEY_1_UP:
            if (fsm_rt_cpl == print("KEY1 UP\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_1_DOWN:
            if (fsm_rt_cpl == print("KEY1 DOWN\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_1_PRESSED:
            if (fsm_rt_cpl == print("KEY1 PRESSED\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_1_LONG_PRESSED:
            if (fsm_rt_cpl == print("KEY1 LONG PRESSED\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_1_REPEATE:
            if (fsm_rt_cpl == print("KEY1 REPEAT\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_2_UP:
            if (fsm_rt_cpl == print("KEY2 UP\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_2_DOWN:
            if (fsm_rt_cpl == print("KEY2 DOWN\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_2_PRESSED:
            if (fsm_rt_cpl == print("KEY2 PRESSED\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_2_LONG_PRESSED:
            if (fsm_rt_cpl == print("KEY2 LONG PRESSED\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;

        case KEY_2_REPEATE:
            if (fsm_rt_cpl == print("KEY2 REPEAT\r\n")) {
                KEY_APP_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;
        
            
    }

    return fsm_rt_on_going; 
}


int main(void)
{
	
	key_init();
	
	for(;;) {
		
		key_task();

        key_app();
			
	}
		
}








