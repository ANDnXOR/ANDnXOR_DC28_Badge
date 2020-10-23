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

#ifndef WH_BENDER_H
#define WH_BENDER_H

#include <zephyr.h>

#define URL_LEADERBOARD 		"bit.ly/3egadD5\n"
#define URL_SLACK 				"bit.ly/3eRTR4B\n"
#define URL_END 				"bit.ly/2Aw1s9C\n"
#define MAP_CHAR_PLAYER 		"☻"
#define MAP_CHAR_LOCKED 		"°"
#define MAP_CHAR_UNLOCKED 		"°"
#define MAP_CHAR_WALL 			'*'
#define MAP_START_ROW 			15
#define MAP_START_COL 			11
#define MAP_MAX_ROWS 			18
#define MAP_MAX_COLS 			36
#define NUMBER_CHALLENGES 		21
#define NUMBER_MAIN_CHALLENGES 	10
#define NUMBER_LULZ_MAX 		20
#define NUMBER_ITEMS 			10
#define NUMBER_RECAPS 			11
#define BENDER_NAME_FLAG 		0x01
#define FREND_SYN_FLAG 			0x83
#define FREND_ACK_FLAG 			0x84

//Description Headers
#define BENDER_INTRO_MSG 	"Badge Enabled Non Directive Enigma Routine Portable Interface SyStem:\nBENDER~PISS\n\nWlcm 2 d sprawl!\n\nTyp \"bender\" 2 git started or RTFM.MD!"
#define BENDER_CMDZ 		"DeZ commands R wut U mostly uZ: hack, look, look at THING, loot, map, w a s d,\nfrend, name, reset, gender, &...\nbender statz\n"
#define BENDER_HACK 		"U eXplt things whch haz vulnz. Wen U hack stuff U must hack it w a tng it\niz vulnerable 2. hack TNG1 wit TNG2. 2 complEt a chaLenG U \"hack flag wit ANSWR\"\n"
#define BENDER_LOOT 		"2 C *.* U haz typ \"loot show\"\nItz not rly stealing f U found it right? So f U find som swEt\nsupa amazeballs TNG jst typ \"loot TNG\" & itz yorz\n"
#define BENDER_LOOT_SUCCESS "U luv stealing!\nU luv tkng tNgs!\n"
#define BENDER_LOOK 		"typ \"look\" 2 peep an area. f U wnt 2 git supa creepy & ^ clOs L%k @ an ITEM\ntyp \"look at ITEM\"\n"
#define BENDER_FREND 		"*Unlock Challngz!\n0 U giv ID 2 frend\n1 F $frend syn ID\n2 F giv U FLAG\n3 U $frend ack FLAG\n4 Both Profit!\n\n"
#define BENDER_FREND_SYN 	"Ax frend 4 bdge ID. datz thR public key.\nU nEd 2 encrypt it w yor prv8 key. DFIU!\n\nEx: $frend syn ID\n"
#define BENDER_FREND_ACK 	"Did SOME1 GIV U a frend FLAG?\nDecrypt it here, git thR bAs unlocks & a flag 4 points. DFIU!\n\nEx: $frend ack FLAG\n"
#define BENDER_RESET  		"2 reset BENDER~PISS 1st contemplate DIS Lyf choice whIl staring n d mirra\nshaming yorself. f stil kewl w it typ \"reset Y\"\n"
#define BENDER_RESET_Y 		"Init 0 ~ Hodl on 2 yor butts.\nRst Dun.\n"
#define BENDER_RESET_y 		"n U cnt uz lowR case y we sed uz UPPER CASE Y foLow instrcs o badge wiL explode\n"
#define BENDER_GENDER 		"B comfortable w hu U are, chAng yor gender f nEd B.\nU can b: M, F, or X\nTyp...\n\"gender MFX\"\n"
#define BENDER_GENDER_ERR 	"Dat doesnt mAk sense...U must b gender :#).\n"
#define BENDER_GENDER_M 	"SX chAng sucSful: Man-Bot!\n"
#define BENDER_GENDER_F 	"SX chAng sucSful: Fem-Bot!\n"
#define BENDER_GENDER_X 	"SX chAng sucSful: NonBinary-Bot!\n"
#define BENDER_GENDER_PRO_M "Mr "
#define BENDER_GENDER_PRO_F "Ms "
#define BENDER_GENDER_PRO_X "Mx "

//Main Storyling Thingz
#define CHALLENGE_MASTER_UNLOCK 		"NEVERGONNAGIVEYOUUPNEVERGONNALETYOUDOWN"
#define CHALLENGE_DESC_LOCKED 			"D chaLenG iz locked! Xchang frend flag 4 unlock!\n"
#define CHALLENGE_TARGET_HACKED 		"O damn, we hav a l337 haxor Ovr hEr. d louder U R d less U hEr.\ntAk a L%k @ yor pwned target.\n"
#define CHALLENGE_TARGET_NOT_HACKED_YET "Zzt. Derp. Cnt comply. U must drink aL d b%z & hack aL d thingz.\n"

//Main Challenge - OSINT #1 Twitter
#define CHALLENGE_FLGR_00 			0x64
#define CHALLENGE_DESC_00 			"Wut? Itz MrBill. Hes trying 2 coLec OSINT on Hs net of hard hat SD haXor fam.\nStA classy & giv him wot he wants.\n"
#define CHALLENGE_ANSW_00 			"420-69-1337" 	//OSINT - Most common reported SSN from BSSD
#define CHALLENGE_TARGET_00_0_NAME 	"OSINT"
#define CHALLENGE_TARGET_00_0_DESC 	"he pEpn SSN off W3s\n" 
#define CHALLENGE_TARGET_00_1_NAME 	"SSN"
#define CHALLENGE_TARGET_00_1_DESC 	"k not boomer, dat iz social security #\n"
#define CHALLENGE_TOOL_DESC_0 		"MALTEGO"		//THIS HACKS CHALLENGE_TARGET_00_0_NAME

//Main Challenge - CRYPTO/ENCODING #1 Keyboard Walk Encoding
#define CHALLENGE_FLGR_01 			0x65
#define CHALLENGE_DESC_01 			"U find a locked Q10 w tiny ENGRAVING.\nitz asking 4 a PW.\nA BIRB flies overhead, you l%k ^ & 2 d L.\n"
#define CHALLENGE_ANSW_01 			"canada" 			//CRYPTO - Keyboard shift cypher up and to the left from the engraving (with wraparound): tzizcz
#define CHALLENGE_TARGET_01_0_NAME 	"ENGRAVING"
#define CHALLENGE_TARGET_01_0_DESC 	"on d bak d following iz inscribed: tzizcz\n"
#define CHALLENGE_TARGET_01_1_NAME 	"BIRB"
#define CHALLENGE_TARGET_01_1_DESC 	"Itz not real, birbs R guvment survlnce drone dat wraprownd\nd globe ch1rpin \'key key\'\n"
#define CHALLENGE_TOOL_DESC_1 		"AMSCOPE"		//THIS HACKS CHALLENGE_TARGET_01_0_NAME

//Main Challenge - REVERSE ENGINEERING #1 Derbycon Trevor Firmware
#define CHALLENGE_FLGR_02 			0x66
#define CHALLENGE_DESC_02 			"Theres an elctrnk bug. ! d NSA kind bt d ROACH frm con kind.\nPrograMn INTRFAC exposed. f only U c%d hack dis HW.\n"
#define CHALLENGE_ANSW_02 			"ROUNDERS" 		//REVERSE ENGINEERING - Binary is hidden as DERBY.RAW, use strings or Ghidra on it
#define CHALLENGE_TARGET_02_0_NAME 	"INTRFAC"
#define CHALLENGE_TARGET_02_0_DESC 	"D mny bug badge blings raw whIl itz binary dumps.\nItz az f frm warez iz jst hidden n pln cite.\n"
#define CHALLENGE_TARGET_02_1_NAME 	"ROACH"
#define CHALLENGE_TARGET_02_1_DESC 	"U haz a senS of longing 4 Lulvil.\nTrevor 4get icing Dave whIl dressed az a *<|:).\n"
#define CHALLENGE_TOOL_DESC_2 		"ICEDEBUGGER"	//THIS HACKS CHALLENGE_TARGET_02_0_NAME

//Main Challenge - REVERSE ENGINEERING #2 Find the E-Mail Address
#define CHALLENGE_FLGR_03 			0x67
#define CHALLENGE_DESC_03 			"U cUm ax a supa secure medical LAPPY covered n stickers.\nIt hz a TACO_CORP_PROMPT on itz scrEn.\n"
#define CHALLENGE_ANSW_03 			"8GAT35@VAXX34.0RG"//REVERSE ENGINEERING - Binary is on flash under /usr/bin
#define CHALLENGE_TARGET_03_0_NAME 	"LAPPY"
#define CHALLENGE_TARGET_03_0_DESC 	"D credz auth binary wz XtractD. wot acownt iz Usd 2 login? Saved undR\nyouZer binz...\n"
#define CHALLENGE_TARGET_03_1_NAME 	"TACO_CORP_PROMPT"
#define CHALLENGE_TARGET_03_1_DESC 	"D prolly not HIPAA compliant login 4 Taco Corps medical rEsrch divisN.\nDid dey release d virus only 2 seL thR salsa vaccine az a cure?\n"
#define CHALLENGE_TOOL_DESC_3 		"RUBBER_DUCKY"		//THIS HACKS CHALLENGE_TARGET_03_0_NAME

//Main Challenge - CRYPTO/ENCODING #2 Morse Encoding where speed is related to temperature
#define CHALLENGE_FLGR_04 			0x68
#define CHALLENGE_DESC_04 			"A lRg comms tower itz n not powered, a PIGEON_HOLE gap exists whch needs somTIN\n4 cndctvity. l%kin awA U notic som CLOUDS. c%d DIS b d coz of it aL. d rona?\n"
#define CHALLENGE_ANSW_04 			"5GT0W3RZDuH" 	//5GT0W3RZDuH (HEX)-> 35 47 54 30 57 33 52 5a 44 75 48 (MORSE) -> CHALLENGE_HACK_04 (BELOW)
#define CHALLENGE_HACK_04 			"...-- .....  ....- --...   ..... ....-   ...-- -----   ..... --...   ...-- ...--   ..... ..---   ..... .-   ....- ....-   --... .....   ....- ---.."
#define CHALLENGE_TARGET_04_0_NAME 	"PIGEON_HOLE"
#define CHALLENGE_TARGET_04_0_DESC 	"woah, d bIrb ComplEtd d cIrcuit! a vanilla iCe trak starts playin &\nlyts r flashin waaa t% fst. nEd 2 lit'rally netflIx & Chill 2 slo\nthngz dwn b4 i git a hedakE\n"
#define CHALLENGE_TARGET_04_1_NAME 	"CLOUDS"
#define CHALLENGE_TARGET_04_1_DESC 	"R thOs clouds? problE not, thOs R chem trails.\nDey put a hex on U morse so thN U tink.\n"
#define CHALLENGE_TOOL_DESC_4 		"BIRB"		//THIS HACKS CHALLENGE_TARGET_04_0_NAME

//Main Challenge - CRYPTO/ENCODING #3 RS232 "Serial UART" blinks
#define CHALLENGE_FLGR_05 			0x69
#define CHALLENGE_DESC_05 			"u c Mt BER cn, sobr thotz :( mAbE U cn cure d rona by putn smTIN inside yo slf.\nU scratch BUTT whIl tinkiN bout it.\n"
#define CHALLENGE_ANSW_05 			"1NH@L3LY507"		//1NH@L3LY507 (BINARY) -> (RS232 Protocol) -> Prepend 0 Start Bit + Invert LSB/MSB Order + Append 1 Stop Bit
#define CHALLENGE_HACK_05 			"0100011001 0011100101 0000100101 0000000101 0001100101 0110011001 0001100101 0100110101 0101011001 0000011001 0111011001"
#define CHALLENGE_TARGET_05_0_NAME 	"BUTT"
#define CHALLENGE_TARGET_05_0_DESC 	"Yor gutz lite ^ & blink. Itz supa serial 2 stRt tink bout lEst & mst\nsigNfict tNgs thN stop, cuz DIS mA b d wrng cure.\n"
#define CHALLENGE_TARGET_05_1_NAME 	"BER"
#define CHALLENGE_TARGET_05_1_DESC 	"Modern tImz Fruitlands. datz a damn gud beR, despite it bn Mt.\n"
#define CHALLENGE_TOOL_DESC_5 		"UVLIGHT"		//THIS HACKS CHALLENGE_TARGET_05_0_NAME

//Main Challenge - PHREAKING - Elevator Hacking
#define CHALLENGE_FLGR_06 			0x6A
#define CHALLENGE_DESC_06 			"U entR a building & wiLCaruana runs awA az U apRch an OpN elvt0r. Yln he hz a\n:X & dropz a CELL. Thr iz l0kd CALLBOX bElO d flOr btNz.\n"
#define CHALLENGE_ANSW_06 			"OTIS"
#define CHALLENGE_HACK_06 			"LUG caL bawx iz n chaLenG 4 you, d trusT baL pik pWns it n 2nds.\n"
#define CHALLENGE_TARGET_06_0_NAME 	"CALLBOX"
#define CHALLENGE_TARGET_06_0_DESC 	"Bt hW u caL? Etchd w wot wz problE a hevE gauge wire U c ZXh0LjQxNzc=\n" //Ext 4177
#define CHALLENGE_TARGET_06_1_NAME 	"CELL"
#define CHALLENGE_TARGET_06_1_DESC 	"Therz only 1 fone # n d recnt caL lst 312d3333372d4d41542d492d4f4245592e2e2e4d6179422064726f7020442059\n"
#define CHALLENGE_TOOL_DESC_6 		"LOCKPICK"		//THIS HACKS CHALLENGE_TARGET_06_0_NAME 

///Main Challenge - SIGINT - POCSAG Payphone Challange
#define CHALLENGE_FLGR_07 			0x6B
#define CHALLENGE_DESC_07 			"A PAYPHONE by a run dwn gas statN. P$ shows -$1337 / gal.\nWUT?! wiLCaruana again, n he iz runN awA :-d & shooting a laser @ U.\n"
#define CHALLENGE_ANSW_07 			"DUALCORE"
#define CHALLENGE_HACK_07 			"d # U R clng cnt b rEchD pls hang ^ & try agen: 312d3333372d4d41542d492d4f4245592e2e2e4d6179422064726f7020442059\n"
#define CHALLENGE_TARGET_07_0_NAME 	"PAYPHONE"
#define CHALLENGE_TARGET_07_0_DESC 	"d fone worx bt itz auto dialing a messed ^ #. how Ls c%d U caL it?\n& u 1Dr wut ^ wit itz COINBOX...\n"
#define CHALLENGE_TARGET_07_1_NAME 	"COINBOX"
#define CHALLENGE_TARGET_07_1_DESC 	"it hz Bin pryed OpN & NE coins put n faL rght bak out.\nN bak u C msg: Rm9yIGEgZ29vZCB0aW1lIGNhbGwgZXh0LiAyMzIz\n" //Ext 2323
#define CHALLENGE_TOOL_DESC_7 		"QUARTER"			//THIS HACKS CHALLENGE_TARGET_07_0_NAME

//Main Challenge - CRYPTO/ENCODING #4 NTLM PASSWORD CRACKING
#define CHALLENGE_FLGR_08 			0x6C
#define CHALLENGE_DESC_08 			"Pon d flOr ther sits a glitter covered tink pad frm TyMkrs.\nItz old, runN win 2000, & evN hz an IOMEGA_DRIVE.\n"
#define CHALLENGE_ANSW_08 			"m3atl0af"
#define CHALLENGE_TARGET_08_0_NAME 	"IOMEGA_DRIVE"
#define CHALLENGE_TARGET_08_0_DESC 	"W a solid clik d disk snaps in2 plAc.\nUn4tuN8ly d files R credential locked by d win SAM\n"
#define CHALLENGE_TARGET_08_1_NAME 	"SAM"
#define CHALLENGE_TARGET_08_1_DESC 	"Navigating 2 d win SYS thirty two config SAM U find:\n0E7FDE76B8A417953D640D5CDB0D9B72\n"
#define CHALLENGE_TOOL_DESC_8 		"ZIP_DISK"		//THIS HACKS CHALLENGE_TARGET_08_0_NAME

//Main Challenge - CRYPTO/ENCODING #5 SLACKBOT
#define CHALLENGE_FLGR_09 			0x6D
#define CHALLENGE_DESC_09 			"Theres a robotic HED on d ground, bt it iz lacking d milliamps.\nFAC & reminds of U of pure annoyance.\n"
#define CHALLENGE_ANSW_09 			"iCanHazEncryptI0n?"
#define CHALLENGE_TARGET_09_0_NAME 	"HED"
#define CHALLENGE_TARGET_09_0_DESC 	"U cn ask me simpl questions bout how Slack works,\no jst typ a few keywords lIk \"m355@g3\" bt TLK 2\nyorself so others lIk guvment dun knO\n"
#define CHALLENGE_TARGET_09_1_NAME 	"FAC"
#define CHALLENGE_TARGET_09_1_DESC 	"Blu grEn red yeLo w two eyes som brows & wot d fuk iz dat a nose o mouth?!\n"
#define CHALLENGE_TOOL_DESC_9 		"BATTERY"		//THIS HACKS CHALLENGE_TARGET_09_0_NAME

//Recap Challenge - CRYPTO/ENCODING #6 RECAP
#define CHALLENGE_FLGR_20 0x85
#define CHALLENGE_DESC_20 "WTF hapnd 2 DIS world since DC27? WeL AND!XOR rOt it n a note, tore it up, &...\nitz randomly spred throughout d wrld. Hav :) putting it bak 2geder 4 recap\n"
#define CHALLENGE_ANSW_20 "DXDCABUUUUR"
#define BENDER_RECAP "WTF hapnd 2 DIS world since DC27? WeL AND!XOR rOt it n a note, tore it up, &...\nitz randomly spred throughout d wrld. Hav :) putting it bak 2geder 4 recap\n"
#define RECAP_HEADER "U find r3cap papR...\n"
#define RECAP_00 "44 20 64 63 32 37\n20 61 6e 64 21 58\n6f 72 20 6e 75 63\n6c 65 61 72 20 77\n6e 74 72 20 62 61\n64 67 65 20 26 20\n68 61 63 6b 66 6f\n72 73 61 74 61 6e\n20 70 61 6e 64 65\n"
#define RECAP_01 "6d 69 63 20 62 61\n64 67 65 20 67 6f\n74 20 64 72 75 6e\n6b 2c 20 68 6f 6f\n6b 64 20 75 70 2c\n20 26 20 63 61 75\n73 65 64 20 44 20\n72 6f 6e 61 20 66\n72 6d 20 73 6f 6d\n"
#define RECAP_02 "20 6d 65 73 73 65\n64 20 5e 20 73 74\n64 2e 20 74 68 6e\n20 64 65 66 20 43\n6f 6e 20 77 7a 20\n63 61 6e 63 65 6c\n6c 65 64 2e 20 34\n20 72 65 61 6c 73\n69 65 73 2e 20 73\n"
#define RECAP_03 "69 6e 63 65 20 74\n68 6e 20 77 65 76\n65 20 73 70 72 65\n64 20 72 75 6d 6f\n72 73 20 63 75 7a\n20 77 65 20 72 20\n3a 22 29 20 62 6f\n75 74 20 64 20 68\n25 6b 20 5e 2e 20\n"
#define RECAP_04 "72 75 6d 6f 72 73\n20 73 75 63 68 20\n6c 69 6b 20 69 74\n20 77 7a 20 62 61\n74 73 2c 20 35 20\n67 20 63 65 6c 20\n74 6f 77 65 72 73\n2c 20 62 69 72 64\n73 2c 20 62 69 6c\n"
#define RECAP_05 "6c 20 67 61 74 65\n73 20 74 72 79 69\n6e 67 20 32 20 6d\n41 6b 20 6d 6f 6e\n65 20 6f 66 66 20\n6f 66 20 76 61 63\n63 69 6e 65 73 2c\n20 63 6f 6e 76 69\n6e 63 69 6e 67 20\n"
#define RECAP_06 "70 6f 74 75 73 20\n32 20 63 6f 6e 76\n69 6e 63 65 20 75\n20 32 20 64 72 69\n6e 6b 20 42 6c 65\n61 63 68 2e 2e 2e\n20 66 20 55 20 62\n6c 65 76 20 6e 65\n20 6f 66 20 64 61\n"
#define RECAP_07 "74 20 55 20 72 20\n64 75 6d 62 2e 20\n31 30 30 30 25 20\n66 6b 6e 20 6c 75\n67 2e 20 63 6f 72\n6f 6e 61 76 69 72\n75 73 20 73 75 78\n20 26 20 64 65 2d\n72 61 69 6c 65 64\n"
#define RECAP_08 "20 6f 75 72 20 61\n6e 6e 75 61 6c 20\n63 6f 6e 20 78 70\n65 72 65 6e 73 2e\n20 69 67 6e 6f 72\n20 61 6c 20 64 61\n74 20 64 75 6d 62\n20 73 63 68 65 74\n20 26 20 68 61 76\n"
#define RECAP_09 "20 3a 29 20 68 61\n63 6b 69 6e 67 20\n64 69 73 20 62 61\n64 67 65 2e 20 77\n65 20 68 6f 70 20\n69 74 20 62 72 69\n6e 67 73 20 55 20\n3a 29 20 26 20 68\n61 70 65 6e 73 2e\n"
#define RECAP_10 "20 55 20 73 68 75\n64 20 68 61 63 6b\n20 66 6c 61 67 20\n77 69 74 2e 2e 2e\n75 70 70 52 20 63\n61 73 65 2e 2e 2e\n"

//Lulz Quiz
#define CHALLENGE_DESC_10 "~LULZ QUIZ~\n(0)EMACS\n(1)VIM\n(2)NANO\n$hack flag wit #\n"
#define CHALLENGE_ANSW_10 "1"
#define CHALLENGE_FLGR_10 0x6E
#define CHALLENGE_FLGW_10 0x6F

#define CHALLENGE_DESC_11 "~LULZ QUIZ~\nDid Carole Baskin kill her OM?\n(0)Yes\n(1)No\n$hack flag wit #\n"
#define CHALLENGE_ANSW_11 "0"
#define CHALLENGE_FLGR_11 0x70
#define CHALLENGE_FLGW_11 0x71

#define CHALLENGE_DESC_12 "~LULZ QUIZ~\nPineapple on pizza?\n(0)Yes\n(1)No\n$hack flag wit #\n"
#define CHALLENGE_ANSW_12 "0"
#define CHALLENGE_FLGR_12 0x72
#define CHALLENGE_FLGW_12 0x73

#define CHALLENGE_DESC_13 "~LULZ QUIZ~\n(0)OSX\n(1)Windows\n(2)Linux\n(3)BSD\n$hack flag wit #\n"
#define CHALLENGE_ANSW_13 "2"
#define CHALLENGE_FLGR_13 0x74
#define CHALLENGE_FLGW_13 0x75

#define CHALLENGE_DESC_14 "~LULZ QUIZ~\n(0)Red Team\n(1)Blu Team\n(2)Purpl Team\n$hack flag wit #\n"
#define CHALLENGE_ANSW_14 "2"
#define CHALLENGE_FLGR_14 0x76
#define CHALLENGE_FLGW_14 0x77

#define CHALLENGE_DESC_15 "~LULZ QUIZ~\n(0)Spaces\n(1)Tabs\n$hack flag wit #\n"
#define CHALLENGE_ANSW_15 "1"
#define CHALLENGE_FLGR_15 0x78
#define CHALLENGE_FLGW_15 0x79

#define CHALLENGE_DESC_16 "~LULZ QUIZ~\n(0)Drop 0-Day\n(1)Notify Vendor\n$hack flag wit #\n"
#define CHALLENGE_ANSW_16 "1"
#define CHALLENGE_FLGR_16 0x7A
#define CHALLENGE_FLGW_16 0x7B

#define CHALLENGE_DESC_17 "~LULZ QUIZ~\n(0)Hack\n(1)Slp\n(2)Et\n(3)showR\n$hack flag wit #\n"
#define CHALLENGE_ANSW_17 "3"
#define CHALLENGE_FLGR_17 0x7C
#define CHALLENGE_FLGW_17 0x7D

#define CHALLENGE_DESC_18 "~LULZ QUIZ~\n(0)tst n devlpmnt\n(1)tst n production\n(2)dun tst\n$hack flag wit #\n"
#define CHALLENGE_ANSW_18 "2"
#define CHALLENGE_FLGR_18 0x7E
#define CHALLENGE_FLGW_18 0x80

#define CHALLENGE_DESC_19 "~LULZ QUIZ~\n(0)Buffer Underflow\n(1)Buffer Overflow\n$hack flag wit #\n"
#define CHALLENGE_ANSW_19 "-1" //LOLZ
#define CHALLENGE_FLGR_19 0x81
#define CHALLENGE_FLGW_19 0x82

typedef struct{ 
    uint8_t index;
	bool challenge;
}challenge_tracker_t;

typedef struct{ 
	uint8_t location_row;
	uint8_t location_col;
	uint8_t flag_cmd_right;
	uint8_t flag_cmd_wrong;
	bool discovered;
	bool unlocked;
	bool hacked;
	bool solved;
	bool right;
	bool lulz;
}challenge_t;

typedef struct{ 
	uint8_t location_row;
	uint8_t location_col;
    bool haz;
}item_t;

typedef struct{ 
	uint8_t location_row;
	uint8_t location_col;
}recap_t;

typedef struct{
	char gender;
	uint8_t location_row;
	uint8_t location_col;
	uint8_t random_unlock_0;
	uint8_t random_unlock_1;
	uint8_t random_unlock_2;
	challenge_t challenges[NUMBER_CHALLENGES];
	item_t items[NUMBER_ITEMS];
	recap_t recap[NUMBER_RECAPS];
}bender_data_t;

extern void wh_bender_data_init();

#endif