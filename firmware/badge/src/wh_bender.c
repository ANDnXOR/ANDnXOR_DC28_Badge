/*****************************************************************************
 * Made with beer and late nights in California.
 *
 * (C) Copyright 2017-2020 AND!XOR LLC (https://andnxor.com/).
 *
 * PROPRIETARY AND CONFIDENTIAL UNTIL AUGUST 11th, 2020 then,
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
 *
 * ADDITIONALLY:
 * If you find this source code useful in anyway, use it in another electronic
 * conference badge, or just think it's neat. Consider buying us a beer
 * (or two) and/or a badge (or two). We are just as obsessed with collecting
 * badges as we are in making them.
 *
 * Contributors:
 * 	@andnxor
 * 	@zappbrandnxor
 * 	@hyr0n1
 * 	@bender_andnxor
 * 	@lacosteaef
 *  @f4nci3
 *  @Cr4bf04m
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <drivers/led_strip.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <lvgl.h>
#include <shell/shell.h>
#include <zephyr.h>
#include "system.h"
#include "wh_app.h"
#include "wh_bender.h"
#include "wh_flag.h"
#include "wh_led.h"
#include "wh_settings.h"
#include "wh_shell.h"
#include "wh_ui.h"
#include "wh_util.h"

LOG_MODULE_REGISTER(wh_bender, CONFIG_WH_BENDER_LOG_LEVEL);

static lv_obj_t* m_bender_screen;
static lv_obj_t* m_bender_output_label;
static lv_obj_t* m_bender_input_ta;
static lv_group_t* m_bender_input_group;
static char m_bender_output[256];
static bool m_bender_running = false;

static char *challenge_desc_answ[21][2] = {
	{CHALLENGE_DESC_00, CHALLENGE_ANSW_00},{CHALLENGE_DESC_01, CHALLENGE_ANSW_01},{CHALLENGE_DESC_02, CHALLENGE_ANSW_02},
  {CHALLENGE_DESC_03, CHALLENGE_ANSW_03},{CHALLENGE_DESC_04, CHALLENGE_ANSW_04},{CHALLENGE_DESC_05, CHALLENGE_ANSW_05},
  {CHALLENGE_DESC_06, CHALLENGE_ANSW_06},{CHALLENGE_DESC_07, CHALLENGE_ANSW_07},{CHALLENGE_DESC_08, CHALLENGE_ANSW_08},
  {CHALLENGE_DESC_09, CHALLENGE_ANSW_09},{CHALLENGE_DESC_10, CHALLENGE_ANSW_10},{CHALLENGE_DESC_11, CHALLENGE_ANSW_11},
  {CHALLENGE_DESC_12, CHALLENGE_ANSW_12},{CHALLENGE_DESC_13, CHALLENGE_ANSW_13},{CHALLENGE_DESC_14, CHALLENGE_ANSW_14},
  {CHALLENGE_DESC_15, CHALLENGE_ANSW_15},{CHALLENGE_DESC_16, CHALLENGE_ANSW_16},{CHALLENGE_DESC_17, CHALLENGE_ANSW_17},
  {CHALLENGE_DESC_18, CHALLENGE_ANSW_18},{CHALLENGE_DESC_19, CHALLENGE_ANSW_19},{CHALLENGE_DESC_20, CHALLENGE_ANSW_20}
};

static char *challenge_targetz[10][4] = {
	{CHALLENGE_TARGET_00_0_NAME,CHALLENGE_TARGET_00_0_DESC, CHALLENGE_TARGET_00_1_NAME, CHALLENGE_TARGET_00_1_DESC},
	{CHALLENGE_TARGET_01_0_NAME,CHALLENGE_TARGET_01_0_DESC, CHALLENGE_TARGET_01_1_NAME, CHALLENGE_TARGET_01_1_DESC},
	{CHALLENGE_TARGET_02_0_NAME,CHALLENGE_TARGET_02_0_DESC, CHALLENGE_TARGET_02_1_NAME, CHALLENGE_TARGET_02_1_DESC},
	{CHALLENGE_TARGET_03_0_NAME,CHALLENGE_TARGET_03_0_DESC, CHALLENGE_TARGET_03_1_NAME, CHALLENGE_TARGET_03_1_DESC},
	{CHALLENGE_TARGET_04_0_NAME,CHALLENGE_TARGET_04_0_DESC, CHALLENGE_TARGET_04_1_NAME, CHALLENGE_TARGET_04_1_DESC},
	{CHALLENGE_TARGET_05_0_NAME,CHALLENGE_TARGET_05_0_DESC, CHALLENGE_TARGET_05_1_NAME, CHALLENGE_TARGET_05_1_DESC},
	{CHALLENGE_TARGET_06_0_NAME,CHALLENGE_TARGET_06_0_DESC, CHALLENGE_TARGET_06_1_NAME, CHALLENGE_TARGET_06_1_DESC},
	{CHALLENGE_TARGET_07_0_NAME,CHALLENGE_TARGET_07_0_DESC, CHALLENGE_TARGET_07_1_NAME, CHALLENGE_TARGET_07_1_DESC},
	{CHALLENGE_TARGET_08_0_NAME,CHALLENGE_TARGET_08_0_DESC, CHALLENGE_TARGET_08_1_NAME, CHALLENGE_TARGET_08_1_DESC},
	{CHALLENGE_TARGET_09_0_NAME,CHALLENGE_TARGET_09_0_DESC, CHALLENGE_TARGET_09_1_NAME, CHALLENGE_TARGET_09_1_DESC}	
};

static char *challenge_tool_desc[10] = {
  CHALLENGE_TOOL_DESC_0, CHALLENGE_TOOL_DESC_1, CHALLENGE_TOOL_DESC_2, CHALLENGE_TOOL_DESC_3, CHALLENGE_TOOL_DESC_4, 
  CHALLENGE_TOOL_DESC_5, CHALLENGE_TOOL_DESC_6, CHALLENGE_TOOL_DESC_7, CHALLENGE_TOOL_DESC_8, CHALLENGE_TOOL_DESC_9
};

static char *challenge_recap[11] = {
  RECAP_00, RECAP_01, RECAP_02, RECAP_03, RECAP_04, RECAP_05, RECAP_06, RECAP_07, RECAP_08, RECAP_09, RECAP_10 
};

static char entropy[21][6] = {"pJLHrV","yjRt9X","w9HEcA","2Gnl1g","xwHZL5","SVFbnG","LsTqVP","CGmbrE","lX5IP3","tUGOtR",
	"PUFfiy","elFNKq","m5gMtG","dZD4i0","fFHwKJ","OgYDsn","MEggXm","THM9XS","QeG8EI","0lb03A","6sG03H"}; 

static char world[MAP_MAX_ROWS][MAP_MAX_COLS] = {
"************************************",
"* *   *     * *                    *",
"* *** ***** * * * ******* * * * ****",
"*   * *         * *       * * *    *",
"* *** *** * *** ***** ******* * ****",
"*     *   * *   *       *     *    *",
"* * ********* ***** *** * *** *** **",
"* * *           * *   * *   * * *  *",
"* *** * ***** *** *** *** *** * ****",
"*     *     *   * * *   * * *   *  *",
"* * * *** * ***** * ***** * * * *  *",
"* * *   * *   *   *   * * *   *    *",
"* * ***** *** * * * * * ***** ***  *",
"* *   * * *   * *   *     *   * *  *",
"*** *** * *** *********** *** * ****",
"*   *     *                 *      *",
"*   *     *                 *      *",
"************************************",
};

/*********************************************************************************************
 * @brief BACKEND FUNCTION TO RETRIEVE B.E.N.D.E.R.P.I.S.S. STATE SETTINGS
**********************************************************************************************/ 
bender_data_t* wh_bender_ptr_get() {return wh_settings_bender_ptr_get();}

/*********************************************************************************************
 * @brief BACKEND FUNCTION TO PRINT OUTPUT DIRECTLY TO BADGE SCREEN & SERIAL TERMINAL
**********************************************************************************************/ 
void printb(char* msg){
  //Print to screen
  sprintf(m_bender_output, "%s", msg);
  k_sleep(10);
  lv_obj_invalidate(m_bender_output_label);

  //Print to serial
  shell_print(wh_shell_ctx_get(), "%s", msg);
}

/*********************************************************************************************
 * @brief EVERYTHING IN THIS SECTION IS FOR DEBUG AND TESTING
**********************************************************************************************/ 
/*
static int cmd_flagz(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get(); 
  char msg[250];

  //Winning Flags
  for(int i = 0; i < NUMBER_CHALLENGES; i++){
    strcpy(msg,"");
    wh_flag_t flag;
    flag.badge_id = wh_util_badge_id_get();
    memcpy(&flag.data, entropy[i], WH_FLAG_DATA_LEN);
    flag.command = p_state->challenges[i].flag_cmd_right;
    wh_flag_encoded_t encoded_flag;
    wh_flag_encode(&flag, &encoded_flag);
    shell_fprintf(shell, SHELL_INFO, "Winning Flag for ");
    if(i<10){shell_fprintf(shell, SHELL_INFO, "0");}
    shell_fprintf(shell, SHELL_INFO, "%d: ",i);
    for (uint8_t j = 0; j < WH_FLAG_SYMBOL_COUNT; j++) {
      shell_fprintf(shell, SHELL_INFO, "%s ",encoded_flag.symbols[j]);
    }
    shell_fprintf(shell, SHELL_INFO, "\n");
  }
  //Losing Lulz Flags
  for(int i = 10; i < NUMBER_LULZ_MAX; i++){
    strcpy(msg,"");
    wh_flag_t flag;
    flag.badge_id = wh_util_badge_id_get();
    memcpy(&flag.data, entropy[i], WH_FLAG_DATA_LEN);
    flag.command = p_state->challenges[i].flag_cmd_wrong;
    wh_flag_encoded_t encoded_flag;
    wh_flag_encode(&flag, &encoded_flag);
    shell_fprintf(shell, SHELL_INFO, "*Losing Flag for %d: ",i);
    for (uint8_t j = 0; j < WH_FLAG_SYMBOL_COUNT; j++) {
      shell_fprintf(shell, SHELL_INFO, "%s ",encoded_flag.symbols[j]);
    }
    shell_fprintf(shell, SHELL_INFO, "\n");
  }

  return 0;
}
SHELL_CMD_REGISTER(dbg_flagz, NULL, "Print all flagz", cmd_flagz);

static int cmd_dbg_loc_recap(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  
  for(int i=0; i < NUMBER_MAIN_CHALLENGES; i++){  //Main Challenges are out of the way
    p_state->challenges[i].location_col = 0;
    p_state->challenges[i].location_row = 0;
    p_state->items[i].location_col = 0;
    p_state->items[i].location_row = 0;
  }
  for(int i=10; i < NUMBER_LULZ_MAX; i++){    //Lulz Challenges are out of the way
    p_state->challenges[i].location_col = 0;
    p_state->challenges[i].location_row = 0;
  }
  for(int i=0; i < NUMBER_RECAPS; i++){    //Recap Challenge
    p_state->recap[i].location_col = MAP_START_COL + i;
    p_state->recap[i].location_row = MAP_START_ROW;
  }

  p_state->challenges[20].location_col = MAP_START_COL;
  p_state->challenges[20].location_row = MAP_START_ROW+1;

  printb("DBG: RECAPS(ROW) SET AT ROW:15 COL:11\n");

  return 0;
}
SHELL_CMD_REGISTER(dbg_loc_recap, NULL, "SET RECAP LOCATIONS", cmd_dbg_loc_recap);

static int cmd_dbg_loc_set(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  
  for(int i=0; i < NUMBER_MAIN_CHALLENGES; i++){  //Main Challenges
    p_state->challenges[i].location_col = MAP_START_COL+i;
    p_state->challenges[i].location_row = MAP_START_ROW;
    p_state->items[i].location_col = MAP_START_COL+i;
    p_state->items[i].location_row = MAP_START_ROW;
  }

  for(int i=10; i < NUMBER_LULZ_MAX; i++){    //Lulz Challenges
    p_state->challenges[i].location_col = MAP_START_COL + i-10;
    p_state->challenges[i].location_row = MAP_START_ROW + 1;
  }

  //Recap Challenge
  p_state->challenges[20].location_col = MAP_START_COL+11;
  p_state->challenges[20].location_row = MAP_START_ROW;
  printb("DBG: CHAL & ITEMS(ROW+1) SET AT ROW:15 COL:11\n");

  return 0;
}
SHELL_CMD_REGISTER(dbg_loc_set, NULL, "SET CHALLENGE AND ITEM LOCATIONS", cmd_dbg_loc_set);

static int cmd_dbg_loc_get(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  
  shell_fprintf(shell, SHELL_INFO, "CHALLENGE LOCATIONS:\n");
  for(int i=0; i < NUMBER_MAIN_CHALLENGES; i++){  //Main Challenges
    shell_fprintf(shell, SHELL_INFO, "MAIN#%d ROW:%d COL:%d UNLOKD:%d\n",i, p_state->challenges[i].location_row, p_state->challenges[i].location_col, p_state->challenges[i].unlocked);
    shell_fprintf(shell, SHELL_INFO, "ITEM#%d ROW:%d COL:%d UNLOKD:X\n", i, p_state->items[i].location_row, p_state->items[i].location_col);
  }
  
  for(int i=10; i < NUMBER_LULZ_MAX; i++){    //Lulz Challenges
    shell_fprintf(shell, SHELL_INFO, "LULZ#%d ROW:%d COL:%d UNLOKD:%d\n",i, p_state->challenges[i].location_row, p_state->challenges[i].location_col, p_state->challenges[i].unlocked);
  }

  shell_fprintf(shell, SHELL_INFO, "RECAP CHLG ROW:%d COL:%d UNLOKD:%d\n", p_state->challenges[20].location_row, p_state->challenges[20].location_col, p_state->challenges[20].unlocked);
  for(int i=0; i < NUMBER_RECAPS; i++){    //Recap Notes
    shell_fprintf(shell, SHELL_INFO, "RECAP#%d ROW:%d COL:%d\n",i, p_state->recap[i].location_row, p_state->recap[i].location_col);
  }

  return 0;
}
SHELL_CMD_REGISTER(dbg_loc_get, NULL, "DISPLAY CHALLENGE AND ITEM LOCATIONS", cmd_dbg_loc_get);
 
static int cmd_dbg_show_all(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  
  for(int i=0; i < NUMBER_CHALLENGES; i++){
    p_state->challenges[i].discovered = true;
    p_state->challenges[i].unlocked = true;
  }

  return 0;
}
SHELL_CMD_REGISTER(dbg_show_all, NULL, "UNLOCK AND DISCOVER EVERYTHING", cmd_dbg_show_all);
*/

/*********************************************************************************************
 * @brief EVERYTHING IN THIS SECTION IS FOR THE B.E.N.D.E.R HACKING FRAMEWORK
**********************************************************************************************/ 
/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR SAVING BENDER DATA
**********************************************************************************************/ 
void _save_bender_data(){
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");

  //Pause bling to avoid read/write to SPI errorz
  k_thread_suspend(bling_thread);

  //Save Settings
  wh_settings_save();

  //Wait a sec...
  k_sleep(100);

  //Resume bling to avoid read/write to SPI errorz
  k_thread_resume(bling_thread);
}
/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR DETECTING WHETHER OR NOT THE CURRENT POSTION IS A CHALLENGE
**********************************************************************************************/ 
static challenge_tracker_t _detect_challenge(){
  bender_data_t* p_state = wh_bender_ptr_get();
  challenge_tracker_t temp;

  for(int k=0; k<NUMBER_CHALLENGES; k++){
    if((p_state->challenges[k].location_row==p_state->location_row)&&  //if a challenge exists on the row player is on &&
        (p_state->challenges[k].location_col==p_state->location_col)){  //if a challenge exists on the col player is on
      temp.challenge = true;
      temp.index = k;
      break;
    }
    else
    {
      temp.challenge = false;
      temp.index = -1;
    }
  }  
  return temp;
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR DETECTING WHETHER OR NOT THE ROW/COL CONTAINS A CHALLENGE
**********************************************************************************************/ 
static bool _challenge_detector(int row, int col){
  bender_data_t* p_state = wh_bender_ptr_get();
  bool result = false;

  for(int k=0; k<NUMBER_CHALLENGES; k++){
    if((p_state->challenges[k].location_row==row)&&(p_state->challenges[k].location_col==col)){ 
      result = true;  
      break;
    }
  }  
  return result;
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR DETECTING WHETHER OR NOT THE ROW/COL CONTAINS AN ITEM
**********************************************************************************************/ 
static bool _item_detector(int row, int col){
  bender_data_t* p_state = wh_bender_ptr_get();
  bool result = false;

  for(int k=0; k<NUMBER_MAIN_CHALLENGES; k++){
    if((p_state->items[k].location_row==row)&&(p_state->items[k].location_col==col)){ 
      result = true;  
      break;
    }
  }  
  return result;
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR DETECTING WHETHER OR NOT THE ROW/COL CONTAINS A RECAP MSG
**********************************************************************************************/ 
static bool _recap_detector(int row, int col){
  bender_data_t* p_state = wh_bender_ptr_get();
  bool result = false;

  for(int k=0; k<NUMBER_RECAPS; k++){
    if((p_state->recap[k].location_row==row)&&(p_state->recap[k].location_col==col)){ 
      result = true;  
      break;
    }
  }  
  return result;
}

/*********************************************************************************************
 * @brief COMMAND FOR CHANGING BADGE NAME
**********************************************************************************************/ 
static int cmd_name(const struct shell *shell, size_t argc, char **argv) {
  settings_t* p_settings = wh_settings_ptr_get();
  char msg[160];
  int result = 2;
  strcpy(msg,"");

  switch(argc){
    case 1:
      strcat(msg, "*Current: ");
      strcat(msg, p_settings->name);
      strcat(msg, "\n*2Change: $name XXX\n*Limited to " STRINGIFY(CONFIG_WH_NAME_MAX_LENGTH) " charz\n");
    break;

    case 2:
      result = wh_settings_set_name(argv[1]);
      LOG_DBG("Set name result %d", result);
      if(result == 0){ //name updated
        strcat(msg, "*Success!\nName: ");
        strcat(msg, argv[1]);
        strcat(msg, "\n\n");
        _save_bender_data();
      }
      else if (result == 1){
        strcat(msg, "*Err0r!\nName > " STRINGIFY(CONFIG_WH_NAME_MAX_LENGTH) " charz!\n");
      }
      else {
        strcat(msg, "*Err0r!\nName blank!\n");
      }
    break;
  }

  if(result == 0){
    //Create the flag
    wh_flag_t flag;
    flag.badge_id = wh_util_badge_id_get();
    memcpy(&flag.data, p_settings->name, WH_FLAG_DATA_LEN);
    flag.command = BENDER_NAME_FLAG;
    //Encode the flag
    wh_flag_encoded_t encoded_flag;
    wh_flag_encode(&flag, &encoded_flag);
    //Build the output message
    for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
      strcat(msg,encoded_flag.symbols[i]);
      strcat(msg," ");
    }
    strcat(msg,"\n\nEntR flag @ ");
    strcat(msg, URL_LEADERBOARD);
    strcat(msg,"\n");
  }
  printb(msg);
  return 0;
}
SHELL_CMD_REGISTER(name, NULL, "Change your badge handle", cmd_name);

/*********************************************************************************************
 * @brief COMMAND FOR LOOTING ITEMS FOUND IN AN AREA
**********************************************************************************************/ 
static int cmd_loot(const struct shell *shell, size_t argc, char **argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  settings_t* p_settings = wh_settings_ptr_get();
  bool error_flag = false;
  bool loot_taken = false;
  char msg[200];

  if(argc == 1){ //Display help
    printb(BENDER_LOOT);
  }
  else if(argc == 2){//Player is attempting to loot an item they found
    if(strcmp(argv[1], "show") == 0){
      //Build & print the players title
      strcpy(msg,"**");
      switch (p_state->gender){
        case 'X': strcat(msg,BENDER_GENDER_PRO_X); break;
        case 'F': strcat(msg,BENDER_GENDER_PRO_F); break;
        case 'M': strcat(msg,BENDER_GENDER_PRO_M); break;
      }
      strcat(msg, p_settings->name);
      strcat(msg," L00T**\n");
        
      //Build the list of current l00t 
      for(int i = 0; i < NUMBER_ITEMS; i++){
        if (p_state->items[i].haz == true){
          strcat(msg, challenge_tool_desc[i]);
          strcat(msg," ");
        }
      }
      strcat(msg,"& datz aL...\n");
      printb(msg);       
    }
    else{
      for(int i=0; i<NUMBER_ITEMS; i++){
        //If what they are trying to take is an item AND it exists in the same location as the player
        if((strcmp(argv[1], challenge_tool_desc[i]) == 0) && (p_state->items[i].haz == false) &&
          (p_state->items[i].location_col == p_state->location_col) && (p_state->items[i].location_row == p_state->location_row)){
          printb(BENDER_LOOT_SUCCESS);
          p_state->items[i].haz = true;
          loot_taken = true;
          _save_bender_data();
          break;
        }
        else{
          error_flag = true;
        }
      }
    }
  }
  else error_flag = true;
  
  if((error_flag)&&(loot_taken==false)) printb("You iz the err0r!\n");

  return 0;
}
SHELL_CMD_REGISTER(loot, NULL, "c yor loot o loot things U find", cmd_loot);

/*********************************************************************************************
 * @brief COMMAND FOR CHANGING GENDER
**********************************************************************************************/ 
static int cmd_gender(const struct shell* shell, size_t argc, char** argv) {
  bender_data_t* p_state = wh_bender_ptr_get();

  bool error_flag = false;

  if (argc == 1){
    printb(BENDER_GENDER);
  }
  else if (argc == 2){
    if ((strcmp(argv[1], "M") == 0) || (strcmp(argv[1], "m") == 0)) {
      p_state->gender = 'M';
      printb(BENDER_GENDER_M);
      _save_bender_data();
    } else if ((strcmp(argv[1], "F") == 0) || (strcmp(argv[1], "f") == 0)) {
      p_state->gender = 'F';
      printb(BENDER_GENDER_F);
      _save_bender_data();
    } else if ((strcmp(argv[1], "X") == 0) || (strcmp(argv[1], "x") == 0)) {
      p_state->gender = 'X';
      printb(BENDER_GENDER_X);
      _save_bender_data();
    } else
      error_flag = true;
  } else
    error_flag = true;

  if (error_flag) {
    printb(BENDER_GENDER_ERR);
  }
  return 0;
}
SHELL_CMD_REGISTER(gender, NULL, "Change your gender", cmd_gender);

/*********************************************************************************************
 * @brief COMMAND FOR PERFORMING A GAME RESET
**********************************************************************************************/ 
static int cmd_reset(const struct shell* shell, size_t argc, char** argv) {
  if(argc == 1)
    printb(BENDER_RESET);
  else if (argc == 2){
    if(strcmp(argv[1], "Y") == 0){
      wh_bender_data_init();
      printb(BENDER_RESET_Y);
      _save_bender_data();
    }
    else if(strcmp(argv[1], "y") == 0){
      printb(BENDER_RESET_y);
    }
  }
  return 0;
}
SHELL_CMD_REGISTER(reset, NULL, "Reset the game\n", cmd_reset);

/*********************************************************************************************
 * @brief COMMAND FOR GETTING STARTED / INITIAL HELP
**********************************************************************************************/ 
static int cmd_bender(const struct shell* shell, size_t argc, char** argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  uint8_t completion_percentage = 0;
  char buf[5];
  char msg[250];
  strcpy(msg,"");

  if(argc == 1){ //Display bender help
    printb(BENDER_CMDZ);
  }
  else if((argc == 2)&&(strcmp(argv[1], "statz") == 0)){//Show Game Status
    //10 Main worth 7% Each
    //10 Item worth 1% Each
    //10 Lulz worth 1% Each
    //1 Recap worth 10%

    for(int i=0; i < NUMBER_MAIN_CHALLENGES; i++){  //Main Challenges Solved
      if(p_state->challenges[i].solved == true)
        completion_percentage += 7;
    }

    for(int i=0; i < NUMBER_ITEMS; i++){            //Items Collected
      if(p_state->items[i].haz == true)
        completion_percentage += 1;
    }

    for(int i=10; i < NUMBER_LULZ_MAX; i++){        //Lulz Challenges Solved
      if(p_state->challenges[i].solved == true)
        completion_percentage += 1;
    }

    if(p_state->challenges[20].solved == true)      //Recap Challenge
      completion_percentage += 10;

    //Percentage complEt
    strcat(msg,"C0mpl37!0n: ");
    itoa(completion_percentage, buf, 10);
    strcat(msg, buf);
    strcat(msg,"%\n");

    if(completion_percentage != 100){
      strcat(msg,"kEp Hax0riNg!\n");
    }
    else{
      strcat(msg,"Congratz! U iz dn!\n");
      strcat(msg, URL_END);
    }
    printb(msg);
  }
  return 0;
}
SHELL_CMD_REGISTER(bender, NULL, "Intro help screen about available commands\n", cmd_bender);

/*********************************************************************************************
 * @brief COMMAND FOR MAKING FRENDZ AND EXCHANGING CHALLENGE UNLOCKS
**********************************************************************************************/ 

int _bitModified(int n, int p, int b){ 
  //Given a number n, a position p and a binary value b, we need to change the bit at position p in n to value b.
  //Give credit where credit is due: https://www.geeksforgeeks.org/modify-bit-given-position/
  int mask = 1 << p; 
  return (n & ~mask) | ((b << p) & mask); 
} 

int _bitExtracted(int number, int k, int p){ 
  //Function to extract k bits from p position 
  //Give credit where credit is due: https://www.geeksforgeeks.org/extract-k-bits-given-position-number/
  return (((1 << k) - 1) & (number >> (p - 1))); 
} 

static int __cmd_frend_ack(const struct shell *shell, size_t argc, char **argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  wh_flag_encoded_t encoded_frend_flag;
  wh_flag_encoded_t encoded_scoreboard_flag;
  wh_flag_t frend_flag;
  wh_flag_t scoreboard_flag;
  uint8_t u0 = -1;
  uint8_t u1 = -1;
  uint8_t u2 = -1;
  uint8_t unlock_count = 0;
  uint8_t valid_flag_symbol_length = 5;
  uint32_t frend_source_id = 0;
  uint32_t frend_target_id = 0;
  bool valid_flag_size = true;
  char frend_id_str[4];
  char temp[100];
  char msg[250];
  strcpy(msg,"");
  strcpy(frend_id_str,"");

  if(argc == 1){
    printb(BENDER_FREND_ACK);
  }
  else if(argc == 10){
    //Re-build & validate the encoded frend flag from ARGV
    for(int i=1; i<10; i++){
      strcpy(encoded_frend_flag.symbols[i-1],argv[i]);
      if(strlen(argv[i]) != valid_flag_symbol_length) valid_flag_size = false;
    }

    if(valid_flag_size){
      //Decode & Decrypt the flag
      wh_flag_decode(&frend_flag, &encoded_frend_flag);

      //Obtain unlocks from the frend_syn_flag
      u0 = frend_flag.data[0];
      u1 = frend_flag.data[1];
      u2 = frend_flag.data[2];

      //Obtain the Frend Flag Source ID (who it came from)
      frend_source_id = frend_flag.badge_id; 
      
      //Obtain the Frend Flag Target ID (who it is intended for)
      uint8_t bit = 0;
      for(int i=1; i< 9; i++){ //Target Badge ID Lower 8 Bits
        bit = _bitExtracted(frend_flag.data[5], 1, i);
        frend_target_id = _bitModified(frend_target_id, i-1, bit);
      }
      for(int i=1; i< 9; i++){ //Target Badge ID Middle 8 Bits
        bit = _bitExtracted(frend_flag.data[4], 1, i);
        frend_target_id = _bitModified(frend_target_id, i-1+8, bit);
      }
      for(int i=1; i< 9; i++){ //Target Badge ID Upper 8 Bits
        bit = _bitExtracted(frend_flag.data[3], 1, i);
        frend_target_id = _bitModified(frend_target_id, i-1+16, bit);
      }

      //Check if the id containted in flag data is the same as this badge_id: i.e. is this flag intended for this badge?
      if(wh_util_badge_id_get() == frend_target_id){
        //Unlock the shared challenges if they aren't unlocked already
        if(p_state->challenges[u0].unlocked == false){
          p_state->challenges[u0].unlocked = true;
          unlock_count++;
        }
        if(p_state->challenges[u1].unlocked == false){
          p_state->challenges[u1].unlocked = true;
          unlock_count++;
        }
        if(p_state->challenges[u2].unlocked == false){
          p_state->challenges[u2].unlocked = true;
          unlock_count++;
        }
        _save_bender_data();
        sprintf(temp,"Succesful ACK!\n%d Chlngz unlocked go find dem\n\n",unlock_count); 
        strcat(msg,temp);

        if(frend_source_id != frend_target_id){
          //Create a scoreboard flag for succesful syn~ack frending
          scoreboard_flag.badge_id = wh_util_badge_id_get();
          scoreboard_flag.command = FREND_ACK_FLAG;
          scoreboard_flag.data[0] = u0; //Padding with the unlock allows us to track as well as add miniscule entropy
          scoreboard_flag.data[1] = u1; //Padding with the unlock allows us to track as well as add miniscule entropy
          scoreboard_flag.data[2] = u2; //Padding with the unlock allows us to track as well as add miniscule entropy
          scoreboard_flag.data[3] = _bitExtracted(frend_source_id,8,17);  //Source Badge ID Upper 8 Bits
          scoreboard_flag.data[4] = _bitExtracted(frend_source_id,8,9);   //Source Badge ID Middl 8 Bits
          scoreboard_flag.data[5] = _bitExtracted(frend_source_id,8,1);   //Source Badge ID Lower 8 Bits

          //Encode the scoreboard flag
          wh_flag_encode(&scoreboard_flag, &encoded_scoreboard_flag);

          //Print the scoreboard flag
          strcat(msg,"Sc0r3brd Points:\n"); 
          for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
            strcat(msg,encoded_scoreboard_flag.symbols[i]);
            strcat(msg," ");
          }
          strcat(msg,"\n");
          strcat(msg,URL_LEADERBOARD);
        }
        else 
          strcat(msg,"L00PBAK: Quit playing w yorself & go mAk real frendz!\n");

        printb(msg);
      }
      else{
        printb("Er0r: Fl@g N07 M3@n7 4 U!\n");
      }
    }
    else{
      strcat(msg,"Er0r:Unv@l!d Fl@g Syz3\n");
      printb(msg);
    }
  }
  else{
    strcat(msg,"Er0r:Inpt != A Argz\n");
    strcat(msg,"INNNNNPUUUUUUUT!\n");
    printb(msg);
  }
  return 0;
}

static int __cmd_frend_syn(const struct shell *shell, size_t argc, char **argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  wh_flag_t flag;
  uint32_t target_id = 0;
  bool valid_hex = true;
  bool valid_length = false;
  char msg[250];
  char syn_badge_id[8];
  strcpy(msg,"");

  if(argc == 1){
    printb(BENDER_FREND_SYN);
  }
  else if(argc == 2){ 
    //Validate the target badge id for length
    if(strlen(argv[1]) <= 6){
      valid_length = true;
      sprintf(syn_badge_id,"%s",argv[1]);
    }

    //Validate the target badge id for hexidecimal
    for(int i=0; i < strlen(syn_badge_id); i++){
      if(isxdigit((unsigned char)syn_badge_id[i]) == 0) 
        valid_hex = false;
    }

    if((valid_length)&&(valid_hex)){ 
      //Zero the payload storage to be safe, who knows what rando shit is floating in memory
      for(int i = 0; i < WH_FLAG_DATA_LEN; i++) flag.data[i] = 0; 

      //Convert the string of the target id into actual hex
      target_id = (uint32_t)strtol(syn_badge_id, NULL, 16);

      //Create the frend flag
      flag.badge_id = wh_util_badge_id_get();
      flag.command = FREND_SYN_FLAG;
      flag.data[0] = p_state->random_unlock_0;      //Random Unlock 0
      flag.data[1] = p_state->random_unlock_1;      //Random Unlock 1
      flag.data[2] = p_state->random_unlock_2;      //Random Unlock 2
      flag.data[3] = _bitExtracted(target_id,8,17);  //Target Badge ID Upper 8 Bits
      flag.data[4] = _bitExtracted(target_id,8,9);   //Target Badge ID Middl 8 Bits
      flag.data[5] = _bitExtracted(target_id,8,1);   //Target Badge ID Lower 8 Bits
      strcat(msg,"FREND FLAG:\n");

      //Encode the frend flag
      wh_flag_encoded_t encoded_flag;
      wh_flag_encode(&flag, &encoded_flag);
      //Build the output message
      for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
        strcat(msg,encoded_flag.symbols[i]);
        strcat(msg," ");
      }
      strcat(msg,"\n\nGiv Bak 2 Frend 4:\n$frend ack FLAG\n");
      printb(msg);
    }
    else {
      strcat(msg,"Er0r: ID ! Valud\n");
      printb(msg);
    }
  }
  else{
    strcat(msg,"Er0r:Inpt > 2 Argz\n");
    strcat(msg,"INNNNNPUUUUUUUT!\n");
    printb(msg);
  }
  return 0;
}

static int cmd_frend(const struct shell* shell, size_t argc, char** argv) {
  char msg[250];
  char msg_badge_id[24];
  strcpy(msg,"");
  strcat(msg,BENDER_FREND);
  sprintf(msg_badge_id,"Ur BadgeID: %06x\n",wh_util_badge_id_get());
  strcat(msg,msg_badge_id); 
  strcat(msg,"Giv dat ID 2 Frendz\nDeetz in RTFM.MD\n");
  printb(msg);
  return 0;
}
SHELL_STATIC_SUBCMD_SET_CREATE(sub_frend,
    SHELL_CMD(syn, NULL, "Generate a frend code\n", __cmd_frend_syn),
    SHELL_CMD(ack, NULL, "Enter a frend code\n", __cmd_frend_ack), SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(frend, &sub_frend, "Frend System for sharing challenge unlocks\n", cmd_frend);

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR BLINKING LEDS WITH MORSE ENCODING
**********************************************************************************************/ 
static void __hack_action_display_morse(char* m_code) {
  //Morse base duration: dot = d, pause = d, dash = 3*d ~ https://science.howstuffworks.com/innovation/inventions/morse-code.htm
  uint16_t d = 400;
  size_t len = strlen(m_code);

  //Obtain current ambient temperature
  struct sensor_value temp;
  struct device* dev_sense = device_get_binding("WH_ADC_SENSE");

  if (!dev_sense) {
    //So if we cant pickup the thermistor give them a duration of default d 400ms
    LOG_ERR("ADC Sensor not available");
  }
  else { //change duration to correlate with temperature i.e. they have to chill the thermistor to slow the blink rate
    sensor_sample_fetch(dev_sense);
    sensor_channel_get(dev_sense, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    switch(temp.val1) {
      case  1 ... 50: d = 400; break;
      case 51 ... 55: d = 300; break;
      case 56 ... 60: d = 200; break;
      case 61 ... 65: d = 150; break;
      default:        d =  50; break;
    }
  }

  //Turn off all LEDs and initial pause
  wh_led_set_all(WH_LED_COLOR_BLACK); //SPACE BETWEEN CHARACHTERS
  wh_led_show();
  k_sleep(3*d);

  // Process each character
  for (int i = 0; i < len; i++) {
    switch (m_code[i]) {
      case '.': {
        wh_led_set_all(WH_LED_COLOR_GREEN);
        wh_led_show();
        k_sleep(d);                         //DOT
        wh_led_set_all(WH_LED_COLOR_BLACK); 
        wh_led_show();
        k_sleep(d);                         //PAUSE
      } break;

      case '-': {
        wh_led_set_all(WH_LED_COLOR_MAGENTA);
        wh_led_show();
        k_sleep(3*d);                       //DASH
        wh_led_set_all(WH_LED_COLOR_BLACK);
        wh_led_show();
        k_sleep(d);                         //PAUSE
      } break;

      case ' ': {
        wh_led_set_all(WH_LED_COLOR_BLACK); //SPACE BETWEEN CHARACHTERS
        wh_led_show();
        k_sleep(3*d);
      } break;

      default: break;
    }
  }
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR BLINKING LEDS WITH RS232 ENCODING
**********************************************************************************************/ 
static void __hack_action_display_rs232(char* rs232_code) {
  uint16_t d = 500;
  size_t len = strlen(rs232_code);

  //Turn off all LEDs and initial pause
  wh_led_set_all(WH_LED_COLOR_BLACK); //SPACE BETWEEN CHARACHTERS
  wh_led_show();
  k_sleep(3*d);

  // Process each character
  for (int i = 0; i < len; i++) {
    switch (rs232_code[i]) {
      case '1': {
        wh_led_set_all(WH_LED_COLOR_GREEN);
        wh_led_show();
        k_sleep(d);                        
        wh_led_set_all(WH_LED_COLOR_BLACK); 
        wh_led_show();
        k_sleep(d);                         
      } break;

      case '0': {
        wh_led_set_all(WH_LED_COLOR_MAGENTA);
        wh_led_show();
        k_sleep(d);                       
        wh_led_set_all(WH_LED_COLOR_BLACK);
        wh_led_show();
        k_sleep(d);                         
      } break;

      case ' ': {
        wh_led_set_all(WH_LED_COLOR_BLACK); 
        wh_led_show();
        k_sleep(3*d);
      } break;

      default: break;
    }
  }
}

/*********************************************************************************************
 * @brief OPTIONAL FUNCTION TO TRIGGER EXTRA ACTIONS WHEN HACK COMMAND EXECUTES 
**********************************************************************************************/ 
static void _hack_action(const struct shell *shell, int challenge_id){
  k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
  
  switch(challenge_id){ 
    case 4: //BLINKY MORSE CODE CHALLENGE
      if (bling_thread != NULL) {
        k_thread_suspend(bling_thread);
        __hack_action_display_morse(CHALLENGE_HACK_04);
        k_thread_resume(bling_thread);
      }
    break;
      
    case 5: //BLINKY RS232 CHALLENGE
      if (bling_thread != NULL) {
        k_thread_suspend(bling_thread);
        __hack_action_display_rs232(CHALLENGE_HACK_05);
        k_thread_resume(bling_thread);
      }
    break;

    case 6: //ELEVATOR PHREAKING CHALLENGE
      k_sleep(3000);   
      printb(CHALLENGE_HACK_06);
    break;

    case 7: //ELEVATOR PHREAKING & PAYPHONE CHALLENGE
      k_sleep(3000);   
      printb(CHALLENGE_HACK_07);
    break;

    default: break;
  }
}

/*********************************************************************************************
 * @brief COMMAND FOR HACKING A TARGET ITEM WITH A TOOL IN INVENTORY
**********************************************************************************************/ 
static int cmd_hack(const struct shell* shell, size_t argc, char** argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  challenge_tracker_t current_location = _detect_challenge();
  bool error_flag = false;

  if((argc == 4) && (strcmp(argv[2], "wit") == 0) && (p_state->challenges[current_location.index].solved == false) &&
    (p_state->challenges[current_location.index].discovered == true)&&(p_state->challenges[current_location.index].unlocked==true)){
    //e.g. hack ITEM1 with ITEM2 , which isnt solved and has been discovered and is unlocked
    if(current_location.challenge==true){
      //Check if the hack solves the challenge by going after the "flag"
      if(strcmp(argv[1], "flag") == 0){
        if(strcmp(argv[3],challenge_desc_answ[current_location.index][1]) == 0){
          //If the answer submitted matches for either main or lulz challenges, close out and give credit
          p_state->challenges[current_location.index].solved = true;
          p_state->challenges[current_location.index].right = true;
          printb("Ans Submitted.\nL%k 2 C flag.\n"); 
          _save_bender_data();
        }
        else{
          if (p_state->challenges[current_location.index].lulz==true){
            //If the answer is wrong and lulz challenge, you get a flag for negative points
            p_state->challenges[current_location.index].solved = true;
            p_state->challenges[current_location.index].right = false;
            printb("Ans Submitted.\nL%k 2 C flag.\n"); 
            _save_bender_data();
          }
          else{
            //Otherwise a wrong answer was submitted to a main challange
            printb("U R incredibly wrng!\nTry agen!\n"); 
          }
        }
      }
      else{ //otherwise the player is trying to hack an area thing with another item which they haz
        //By reference a challenge area thing is vulnerable to exploitation by the item with the same index
        //e.g. challenge[x] has thing[x] which is vulnerable to item[x]...doing this without OOP is FUCT ¯\_(ツ)_/¯ I'm lazy and it works
        if((strcmp(argv[1], challenge_targetz[current_location.index][0]) == 0) //target is a valid thing in this area to hack
        && (strcmp(argv[3], challenge_tool_desc[current_location.index]) == 0)  //tool is valid to use in this area for hacking with
        && (p_state->items[current_location.index].haz)){                       // the player has the tool in their possession
          printb(CHALLENGE_TARGET_HACKED);
          _hack_action(shell,current_location.index);                          //Execute any peripheral actions
          if(p_state->challenges[current_location.index].hacked == false){
            p_state->challenges[current_location.index].hacked = true;          //Set state to true if never been hacked
            _save_bender_data();                                                 //Save settings
          }
        }
        else error_flag = true;
      }
    }
    else{
      error_flag = true;
    } 
  }
  else if((argc == 4) && (strcmp(argv[2], "wit") == 0) && (strcmp(argv[3],CHALLENGE_MASTER_UNLOCK) == 0)){ //Master Unlock
    for(int i=0; i < NUMBER_CHALLENGES; i++){
      p_state->challenges[i].unlocked = true;
    }
    printb("aL Chall3nge5 Unl0cked!\n"); 
    _save_bender_data();
  }
  else if (argc == 1){ //Display Help
    printb(BENDER_HACK);
  }
  else {
    error_flag = true;
  }

  if (error_flag) printb("You iz the err0r!\n");
  
  return 0;
}
SHELL_CMD_REGISTER(hack, NULL, "Hack all the things...", cmd_hack);

/*********************************************************************************************
 * @brief COMMAND FOR LOOKING IN A GENERAL AREA OR AT A SPECIFIC ITEM IN A LOCATION
**********************************************************************************************/  
static int cmd_look(const struct shell* shell, size_t argc, char** argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  uint8_t challenge_tracker = -1;
  uint8_t recap_tracker = -1;
  bool error_flag = false;
  bool new_challenge = false;
  bool same_location_as_challenge = false;
  bool recap_here = false;
  char msg[250];
  strcpy(msg,"");

  //Check to see if you discovered a new challenge (locked or unlocked)
  for(int k=0; k<NUMBER_CHALLENGES; k++){
    if((p_state->challenges[k].location_row==p_state->location_row)&&   //if a challenge exists on the row player is on
        (p_state->challenges[k].location_col==p_state->location_col)&&  //if a challenge exists on the col player is on
        (p_state->challenges[k].discovered == false))                   //if a challenge has not been discovered yet...
    {
      p_state->challenges[k].discovered = true;                         //It has now been discovered and will appear on the map
      new_challenge = true;
      printb("A nu Hax0r chaLenG Appears!\n");
      _save_bender_data();
    }
  }

  //Parse look command
  if(new_challenge == false){
    switch(argc){
      case 1://User typed "look"
        for(int k=0; k<NUMBER_CHALLENGES; k++){ //First lookup if this is a challange
          if((p_state->challenges[k].location_row==p_state->location_row)&&  //if a challenge exists on the row player is on
              (p_state->challenges[k].location_col==p_state->location_col)){  //if a challenge exists on the col player is on
            same_location_as_challenge = true;
            challenge_tracker = k;
          }
        }

        for(int k=0; k<NUMBER_RECAPS; k++){     //Second lookup if there is a recap note here
          if((p_state->recap[k].location_col == p_state->location_col) && (p_state->recap[k].location_row == p_state->location_row)){
            recap_here = true;
            recap_tracker = k;
          }
        }

        if(same_location_as_challenge == true){ //If it is a challange...(nest if statements to give Zapp an aneurysm)
          if(p_state->challenges[challenge_tracker].solved == true){
            strcat(msg, "ChaLenG Complete!\n");
            //Create the flag
            wh_flag_t flag;
            flag.badge_id = wh_util_badge_id_get();
            memcpy(&flag.data, entropy[challenge_tracker], WH_FLAG_DATA_LEN);
            if(p_state->challenges[challenge_tracker].right == true){
              flag.command = p_state->challenges[challenge_tracker].flag_cmd_right;
            }
            else{
              flag.command = p_state->challenges[challenge_tracker].flag_cmd_wrong;
            }
            wh_flag_encoded_t encoded_flag;
            wh_flag_encode(&flag, &encoded_flag);
            //Build the output message
            for (uint8_t i = 0; i < WH_FLAG_SYMBOL_COUNT; i++) {
              strcat(msg,encoded_flag.symbols[i]);
              strcat(msg," ");
            }
            strcat(msg,"\n\nEntR flag @\n");
            strcat(msg, URL_LEADERBOARD);
          }
          else if((p_state->challenges[challenge_tracker].discovered==true)&&(p_state->challenges[challenge_tracker].unlocked==true)){
            strcat(msg, challenge_desc_answ[challenge_tracker][0]);
          }
          else{
            strcat(msg, CHALLENGE_DESC_LOCKED);
            strcat(msg, URL_SLACK);
          }
        }
        else if (recap_here){
          strcat(msg, RECAP_HEADER);
          strcat(msg, challenge_recap[recap_tracker]);
        }
        else {
          strcat(msg, "Nuthin...\n");
        }

        //List out items in this area
        for(int i = 0; i<NUMBER_ITEMS; i++){//Show items which exist where player is, that they havent taken yet
          if((p_state->items[i].location_col == p_state->location_col) && 
            (p_state->items[i].location_row == p_state->location_row) &&
            (p_state->items[i].haz == false)){
            strcat(msg, "\nU c sum t00L: \n");
            strcat(msg, challenge_tool_desc[i]);
            strcat(msg, "\n");
          }
        }
        
        //Print what was seen
        printb(msg); 
      break;

      case 3://User typed "look at XXX"
        //First lookup if this is a challange
        for(int k=0; k<NUMBER_CHALLENGES; k++){
          if((p_state->challenges[k].location_row==p_state->location_row)&&  //if a challenge exists on the row player is on
              (p_state->challenges[k].location_col==p_state->location_col)){  //if a challenge exists on the col player is on
            same_location_as_challenge = true;
            challenge_tracker = k;
          }
        }   

        if ((strcmp(argv[1], "at") == 0)&&(same_location_as_challenge == true)){
          if((strcmp(argv[2], challenge_targetz[challenge_tracker][0]) == 0)&&(p_state->challenges[challenge_tracker].hacked==true))  {
            //The 0 item in each area is the one which needs to be hacked by other items
            //You can't look at it unless it has been hacked
            printb(challenge_targetz[challenge_tracker][1]);
          }
          else if((strcmp(argv[2], challenge_targetz[challenge_tracker][0]) == 0)&&(p_state->challenges[challenge_tracker].hacked==false))  {
            //The 0 item in each area is the one which needs to be hacked by other items
            //You can't look at it unless it has been hacked
            printb(CHALLENGE_TARGET_NOT_HACKED_YET);
          }
          else if(strcmp(argv[2], challenge_targetz[challenge_tracker][2]) == 0){
            //The 2 item in each area can always be looked at, its either a hint or lulzy
            printb(challenge_targetz[challenge_tracker][3]);
          }
          else{
            error_flag = true;
          }
        }
        else {
          error_flag = true;
        }
      break;

      default: error_flag = true;
    }  
  }

  if (error_flag) printb("You iz the err0r!\n");

  return 0;
}
SHELL_CMD_REGISTER(look, NULL, "Look around an area", cmd_look);

/*********************************************************************************************
 * @brief COMMAND FOR WALKING NORTH
**********************************************************************************************/ 
static int cmd_w(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  if(world[p_state->location_row - 1][p_state->location_col] != MAP_CHAR_WALL) {
    p_state->location_row -= 1;
    shell_execute_cmd(shell, "map 1 n");
  }
  else{shell_execute_cmd(shell, "map 0 n");;}
  return 0;
}
SHELL_CMD_REGISTER(w, NULL, "Walk North", cmd_w);

/*********************************************************************************************
 * @brief COMMAND FOR WALKING SOUTH
**********************************************************************************************/ 
static int cmd_s(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  if(world[p_state->location_row+1][p_state->location_col] != MAP_CHAR_WALL){
    p_state->location_row += 1;
    shell_execute_cmd(shell, "map 1 s");
  }
  else{shell_execute_cmd(shell, "map 0 s");;}
  return 0;
}
SHELL_CMD_REGISTER(s, NULL, "Walk South", cmd_s);

/*********************************************************************************************
 * @brief COMMAND FOR WALKING EAST
**********************************************************************************************/ 
static int cmd_d(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  if(world[p_state->location_row][p_state->location_col+1] != MAP_CHAR_WALL){
    p_state->location_col += 1;
    shell_execute_cmd(shell, "map 1 e");
  }
  else{shell_execute_cmd(shell, "map 0 e");;}
  return 0;
}
SHELL_CMD_REGISTER(d, NULL, "Walk East", cmd_d);

/*********************************************************************************************
 * @brief COMMAND FOR WALKING WEST
**********************************************************************************************/ 
static int cmd_a(const struct shell* shell, size_t argc, char** argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);
  bender_data_t* p_state = wh_bender_ptr_get();
  if(world[p_state->location_row][p_state->location_col-1] != MAP_CHAR_WALL){
    p_state->location_col -= 1;
    shell_execute_cmd(shell, "map 1 w");
  }
  else{shell_execute_cmd(shell, "map 0 w");;}
  return 0;
}
SHELL_CMD_REGISTER(a, NULL, "Walk West", cmd_a);

/*********************************************************************************************
 * @brief COMMAND FOR DISPLAYING MAP
**********************************************************************************************/ 
static int cmd_map(const struct shell* shell, size_t argc, char** argv) {
  bender_data_t* p_state = wh_bender_ptr_get();
  bool visible_challenge_here = false;
  bool player_here = false;
  bool q1 = false; //TOP LEFT
  bool q2 = false; //TOP RIGHT
  bool q3 = false; //BOTTOM LEFT
  bool q4 = false; //BOTTOM RIGHT
  uint8_t row_offset;
  uint8_t col_offset;
  char map[250];
  char cToStr[2];
  cToStr[1]='\0';
  strcpy(map, "");

  //Find player location to determine which quadrant
  if((p_state->location_row < (MAP_MAX_ROWS/2)) && (p_state->location_col < (MAP_MAX_COLS/2))){q1 = true;}
  else if((p_state->location_row < (MAP_MAX_ROWS/2)) && (p_state->location_col >= (MAP_MAX_COLS/2))){q2 = true;}
  else if((p_state->location_row >= (MAP_MAX_ROWS/2)) && (p_state->location_col < (MAP_MAX_COLS/2))){q3 = true;}
  else{q4 = true;}

  //Set Loop Offsets
  if (q1){row_offset = 0;col_offset = 0;}
  else if (q2){row_offset = 0;col_offset = (MAP_MAX_COLS/2);}
  else if (q3){row_offset = (MAP_MAX_ROWS/2);col_offset = 0;}
  else if (q4){row_offset = (MAP_MAX_ROWS/2);col_offset = (MAP_MAX_COLS/2);}

  //World Map
  for(int i=0; i < (MAP_MAX_ROWS/2); i++){
    //Left Border Padding
    strcat(map, " ");

    for(int j=0; j < (MAP_MAX_COLS/2); j++){
      //Reset trackers
      player_here = false;
      visible_challenge_here = false;

      //Print the player char
      if((p_state->location_row==i+row_offset)&&(p_state->location_col==j+col_offset)){
        strcat(map, MAP_CHAR_PLAYER);
        player_here = true;
      }

      //Print the challenge markers char if the player isn't standing here
      for(int k=0; k<NUMBER_CHALLENGES; k++){
        if((p_state->challenges[k].location_row==i+row_offset)&&(p_state->challenges[k].location_col==j+col_offset)
        &&(p_state->challenges[k].discovered == true)&&(player_here==false)){
          if(p_state->challenges[k].unlocked == true){
            strcat(map, MAP_CHAR_UNLOCKED);
          }
          else{
            strcat(map, MAP_CHAR_LOCKED);
          }
          visible_challenge_here = true;
        }
      }
      
      //Print the map tile
      if((visible_challenge_here==false)&&(player_here==false)){
        cToStr[0] = world[i+row_offset][j+col_offset];
        strcat(map, cToStr);
      }
    }
    //Right Border Padding
    strcat(map,"\n");
  }  

  //If the map was created due to player walking...
  if(argc == 3){
    switch (argv[1][0]){
      case '1' :
        switch (argv[2][0]){
          case 'n' : strcat(map," Wlkn nth...\n"); break;
          case 's' : strcat(map," Wlkn south...\n"); break;
          case 'e' : strcat(map," Wlkn east...\n"); break;
          case 'w' : strcat(map," Wlkn west...\n"); break;
        }
      break;
      case '0' :
        strcat(map," U hit D fir3 w@ll\n");
      break;
    }
  }
  printb(map); 
  return 0;
}
SHELL_CMD_REGISTER(map, NULL, "Show a map", cmd_map);

/*********************************************************************************************
 * @brief EVERYTHING BELOW PERTAINS TO BACKEND RIGGING OF KEYBOARD, HANDLER, & INITIALIZATION
**********************************************************************************************/ 
/*********************************************************************************************
 * @brief SENDS COMMANDS ENTERED ON BBKB TO THE SHELL HANDLER
**********************************************************************************************/ 
static void __bender_cmd(const char* cmd) {
  LOG_INF("Running command '%s'", cmd);

  //Grab the pointer to the shell
  const struct shell *p_shell = wh_shell_ctx_get();

  //Print the shell prompt to the badge screen
  sprintf(m_bender_output, "and!xor:~$ %s", cmd); 

  //Route the command typed on BB Keyboard to the shell
  int ret = shell_execute_cmd(p_shell, cmd);

  //Handles blank and invalid commands
  if(strncmp(cmd,"\n",1)==0)
    shell_fprintf(p_shell, SHELL_NORMAL, "\n");       //Just hit enter
  else{
    if(ret != 0)
      sprintf(m_bender_output, "and!xor:~$ %s> command not found", cmd); 
  }

  lv_label_set_static_text(m_bender_output_label, m_bender_output);
}

/*********************************************************************************************
 * @brief BACKEND STARTUP HANDLER FOR BENDER APP
 * @param data POINTER TO USER DATA PROVIDED FROM INITIALIZATION APP
**********************************************************************************************/ 
static void __bender_handler(void* data) {
  // This gets called every time the user starts the app
  LOG_DBG("BENDER handler running");
  // Show the screen
  lv_scr_load(m_bender_screen);
  k_sleep(100);
  wh_ui_input_group_set(m_bender_input_group);

  m_bender_running = true;

  while (m_bender_running) {
    k_sleep(10);
  }

  LOG_DBG("BENDER handler done");
}

/*********************************************************************************************
 * @brief BACKEND CALLBACK FUNCTION FOR UI SIGNALS
**********************************************************************************************/ 
static wh_ui_signal_result_t __signal_callback(wh_ui_signal_t signal) {
  LOG_DBG("Signal received %s", wh_ui_signal_decode(signal));
  switch (signal) {
    case wh_ui_signal_key_ready:
      return wh_ui_signal_result_okay;
      break;
    case wh_ui_signal_exit:
      m_bender_running = false;
      return wh_ui_signal_result_okay;
      break;
  }
  return 0;
}

/*********************************************************************************************
 * @brief BACKEND FUNCTION FOR HANDLING SPECIAL EVENTS FROM BENDER INPUT TEXT AREA
**********************************************************************************************/ 
static void __input_event_handler(lv_obj_t* obj, lv_event_t event) {
  LOG_DBG("Input event = %d", event);
  if (event == LV_EVENT_RELEASED && m_bender_running) {
    __bender_cmd(lv_ta_get_text(m_bender_input_ta));
    lv_ta_set_text(m_bender_input_ta, "");
    k_sleep(200);
  }
}

/*********************************************************************************************
 * @brief INITIALIZATION FUNCTION FOR B.E.N.D.E.R.P.I.S.S. DEFAULT DATA
**********************************************************************************************/ 
void wh_bender_data_init(){
  // This gets called only the first time the game is ran OR game over OR reset
  bender_data_t* p_state = wh_bender_ptr_get();

  //Default gender is non binary
  p_state->gender = 'X';

  //Starting location of player
  p_state->location_row = MAP_START_ROW;
  p_state->location_col = MAP_START_COL; 

  //Random Challenge and Item Pre-Staging - Initialize at -1 incase there is weird shit in memmory
  for(int i=0; i < NUMBER_CHALLENGES; i++){     
    p_state->challenges[i].location_col = -1;
    p_state->challenges[i].location_row = -1;
    if(i < NUMBER_ITEMS){
      p_state->items[i].location_col = -1;
      p_state->items[i].location_row = -1;
    }
  }

  //Seed RNG based on badge ID such that the unlock is consistent every time
  srand(wh_util_badge_id_get());
  int random_row;
  int random_col;
  bool empty_map_space;

  //Main & Lulz Challenges - Random Placement
  for(int i=0; i < NUMBER_CHALLENGES; i++){  
    empty_map_space = false; //Assume the world map space is filled initially
    while (empty_map_space == false){     //Keep iterating through random rows/cols until you get an empty space
      random_row = rand() % MAP_MAX_ROWS; //Generate Random ROW
      random_col = rand() % MAP_MAX_COLS; //Generate Random COL
      if((world[random_row][random_col] != MAP_CHAR_WALL) && (!_challenge_detector(random_row, random_col))){
        //Does a world map wall AND another challenge not occupy this space?
        empty_map_space = true;
      }
    }
    //Assign the location to the challange
    p_state->challenges[i].location_col = random_col;
    p_state->challenges[i].location_row = random_row;
  }

  //Tools for Challenges - Random Placement
  for(int i=0; i < NUMBER_ITEMS; i++){  
    empty_map_space = false; //Assume the world map space is filled initially
    while (empty_map_space == false){     //Keep iterating through random rows/cols until you get an empty space
      random_row = rand() % MAP_MAX_ROWS; //Generate Random ROW
      random_col = rand() % MAP_MAX_COLS; //Generate Random COL
      if((world[random_row][random_col] != MAP_CHAR_WALL)&&(!_challenge_detector(random_row, random_col))&&(!_item_detector(random_row, random_col))){
        //Does a world map wall AND another challenge AND another item not occupy this space?
        empty_map_space = true;
      }
    }
    //Assign the location to the challange
    p_state->items[i].location_col = random_col;
    p_state->items[i].location_row = random_row;
  }

  //Recap Note Challenge - Random Placement
  for(int i=0; i < NUMBER_RECAPS; i++){  
    empty_map_space = false; //Assume the world map space is filled initially
    while (empty_map_space == false){     //Keep iterating through random rows/cols until you get an empty space
      random_row = rand() % MAP_MAX_ROWS; //Generate Random ROW
      random_col = rand() % MAP_MAX_COLS; //Generate Random COL
      if((world[random_row][random_col] != MAP_CHAR_WALL)&&(!_challenge_detector(random_row, random_col))
          &&(!_item_detector(random_row, random_col))&&(!_recap_detector(random_row, random_col))){
        //Does a world map wall AND another challenge AND another item not occupy this space?
        empty_map_space = true;
      }
    }
    //Assign the location to the recap msg
    p_state->recap[i].location_col = random_col;
    p_state->recap[i].location_row = random_row;
  }

  //Assign Flag Right & Wrong Values
  p_state->challenges[0].flag_cmd_right = CHALLENGE_FLGR_00;
  p_state->challenges[1].flag_cmd_right = CHALLENGE_FLGR_01;
  p_state->challenges[2].flag_cmd_right = CHALLENGE_FLGR_02;
  p_state->challenges[3].flag_cmd_right = CHALLENGE_FLGR_03;
  p_state->challenges[4].flag_cmd_right = CHALLENGE_FLGR_04;
  p_state->challenges[5].flag_cmd_right = CHALLENGE_FLGR_05;
  p_state->challenges[6].flag_cmd_right = CHALLENGE_FLGR_06;
  p_state->challenges[7].flag_cmd_right = CHALLENGE_FLGR_07;
  p_state->challenges[8].flag_cmd_right = CHALLENGE_FLGR_08;
  p_state->challenges[9].flag_cmd_right = CHALLENGE_FLGR_09;
  p_state->challenges[10].flag_cmd_right = CHALLENGE_FLGR_10;
  p_state->challenges[10].flag_cmd_wrong = CHALLENGE_FLGW_10;
  p_state->challenges[11].flag_cmd_right = CHALLENGE_FLGR_11;
  p_state->challenges[11].flag_cmd_wrong = CHALLENGE_FLGW_11;
  p_state->challenges[12].flag_cmd_right = CHALLENGE_FLGR_12;
  p_state->challenges[12].flag_cmd_wrong = CHALLENGE_FLGW_12;
  p_state->challenges[13].flag_cmd_right = CHALLENGE_FLGR_13;
  p_state->challenges[13].flag_cmd_wrong = CHALLENGE_FLGW_13;
  p_state->challenges[14].flag_cmd_right = CHALLENGE_FLGR_14;
  p_state->challenges[14].flag_cmd_wrong = CHALLENGE_FLGW_14;
  p_state->challenges[15].flag_cmd_right = CHALLENGE_FLGR_15;
  p_state->challenges[15].flag_cmd_wrong = CHALLENGE_FLGW_15;
  p_state->challenges[16].flag_cmd_right = CHALLENGE_FLGR_16;
  p_state->challenges[16].flag_cmd_wrong = CHALLENGE_FLGW_16;
  p_state->challenges[17].flag_cmd_right = CHALLENGE_FLGR_17;
  p_state->challenges[17].flag_cmd_wrong = CHALLENGE_FLGW_17;
  p_state->challenges[18].flag_cmd_right = CHALLENGE_FLGR_18;
  p_state->challenges[18].flag_cmd_wrong = CHALLENGE_FLGW_18;
  p_state->challenges[19].flag_cmd_right = CHALLENGE_FLGR_19;
  p_state->challenges[19].flag_cmd_wrong = CHALLENGE_FLGW_19;
  p_state->challenges[20].flag_cmd_right = CHALLENGE_FLGR_20;

  //All locations are initially hidden and locked
  for(int i=0; i < NUMBER_CHALLENGES; i++){
    p_state->challenges[i].discovered = false; 
    p_state->challenges[i].unlocked = false;
    p_state->challenges[i].hacked = false;
    p_state->challenges[i].solved = false;
    p_state->challenges[i].right = false;
  }

  //Assign Lulz Quiz Identifiers & Unlock
  for(int i=10; i < NUMBER_LULZ_MAX; i++){ 
    p_state->challenges[i].lulz = true;
    p_state->challenges[i].unlocked = true;
  }

  //Assign Tool Descriptions & Haz State
  for (int i=0; i<NUMBER_ITEMS; i++){
    p_state->items[i].haz = false;
  }

  //Unlock 4/11 Main Challenges everyone has access to
  p_state->challenges[0].unlocked = true;  //SIGINT CHALLENGE
  p_state->challenges[2].unlocked = true;  //RE#1 CHALLENGE
  p_state->challenges[9].unlocked = true;  //SLACKBOT CHALLENGE
  p_state->challenges[20].unlocked = true; //RECAP CHALLENGE
  
  //Randomly unlock 3/11 more Main Challenges - Reseed RNG based on badge ID such that the unlock is consistent every time
  srand(wh_util_badge_id_get());
  int failsafe = 0;
  int random_challenge = 0;
  bool unlocked = true; 
  //Incase the RNG picks something which is already unlocked  
  while (unlocked == true){  //Unlock first challenge
    random_challenge = rand() % (NUMBER_MAIN_CHALLENGES);
    if(p_state->challenges[random_challenge].unlocked == false){
      unlocked = false;
    }
    if(failsafe >= 100){    //Infinite Loop Failsafe - dont unlock anything they obviously have all unlocks
      unlocked = false;
    }
    failsafe++;
  }
  p_state->challenges[random_challenge].unlocked = true; 
  p_state->random_unlock_0 = random_challenge;

  failsafe = 0;             //Unlock second challenge
  unlocked = true; 
  while (unlocked == true){
    random_challenge = rand() % (NUMBER_MAIN_CHALLENGES);
    if(p_state->challenges[random_challenge].unlocked == false){
      unlocked = false;
    }
    if(failsafe >= 100){    //Infinite Loop Failsafe - dont unlock anything they obviously have all unlocks
      unlocked = false;
    }
    failsafe++;
  }
  p_state->challenges[random_challenge].unlocked = true; 
  p_state->random_unlock_1 = random_challenge;

  failsafe = 0;             //Unlock third challenge
  unlocked = true; 
  while (unlocked == true){ 
    random_challenge = rand() % (NUMBER_MAIN_CHALLENGES);
    if(p_state->challenges[random_challenge].unlocked == false){
      unlocked = false;
    }
    if(failsafe >= 100){    //Infinite Loop Failsafe - dont unlock anything they obviously have all unlocks
      unlocked = false;
    }
    failsafe++;
  }
  p_state->challenges[random_challenge].unlocked = true; 
  p_state->random_unlock_2 = random_challenge;
}

/*********************************************************************************************
 * @brief INITIALIZATION FUNCTION FOR STARTING B.E.N.D.E.R.P.I.S.S. APPLICATION
**********************************************************************************************/ 
static void __bender_init() {
  //Setup LVGL - Mutex locking is REQUIRED here to avoid UI glitches
  k_mutex_lock(&g_mutex_ui, K_FOREVER);
  m_bender_screen = lv_obj_create(NULL, NULL);
  m_bender_output_label = lv_label_create(m_bender_screen, NULL);
  lv_label_set_long_mode(m_bender_output_label, LV_LABEL_LONG_BREAK); /*Break the long lines*/
  lv_obj_set_width(m_bender_output_label, 160);
  lv_obj_align(m_bender_output_label, m_bender_screen, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  sprintf(m_bender_output, BENDER_INTRO_MSG);
  lv_label_set_static_text(m_bender_output_label, m_bender_output);
  m_bender_input_ta = lv_ta_create(m_bender_screen, NULL);
  lv_obj_set_size(m_bender_input_ta, 160, 30);
  lv_ta_set_cursor_type(m_bender_input_ta, LV_CURSOR_BLOCK);
  lv_ta_set_one_line(m_bender_input_ta, true);
  lv_ta_set_text(m_bender_input_ta, "");
  lv_obj_align(m_bender_input_ta, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_event_cb(m_bender_input_ta, __input_event_handler);

  //Create an input group to support the keyboard
  m_bender_input_group = lv_group_create();
  lv_group_add_obj(m_bender_input_group, m_bender_input_ta);

  //Release the MUTEX, also REQUIRED
  k_mutex_unlock(&g_mutex_ui);

  LOG_DBG("B.E.N.D.E.R. Initialized");
}

WH_APP_REGISTER("B.E.N.D.E.R.", __bender_init, __bender_handler, __signal_callback, NULL, 10);

const app_t app_bender = {"B.E.N.D.E.R.", __bender_init, __bender_handler, __signal_callback, NULL};