# AND!XOR "DEF CON IS CANCELED" 28 Badge
Made with beer and late nights in California.
​
TLDR: This year's badge provides bling, an embedded CTF text-based adventure, and a port of MyBASIC extended to the hardware to make it hackable.
​
AND!XOR (@andnxor)
 * @zappbrandnxor
 * @hyr0n1
 * @bender_andnxor
 * @lacosteaef
 * @f4nci3
 * @Cr4bf04m​

Artwork for PCB Silkscreen, Acrylic, Bandanna, & Lanyard: Doc

VOIP Service Puzzle, Greetings, and Lulz: Alethe Denis (@AletheDenis) at Penguin

Puzzle Design & Intern of the Month Award Jun: Will Caruana (@WillCaruana)

Puzzle Design & Beta Testing: Kur3us (@kur3us)

Filming & Editing: Mike Laan (@mlaan)

Sponsors: Urbane Security, Penguin, inspectAR, & Philanthropists

Hackaday: https://hackaday.io/project/173627-andxor-dc28-badge

GitHub: https://github.com/ANDnXOR/ANDnXOR_DC28_Badge
# Badge Hardware #
Hardware information about the badge
## BOM ##
* PCBA: MacroFab 
* Acrylic Faceplate: Ponoko
* MCU: STM32F412RET6
* Screen (OLED): ER-OLED0.96-1.3B-1655
* Screen (TFT): ST7735 128x160
* LEDS: APA-102C-NEW
* Keyboard: Blackberry Q10 (BBKB)
* Keyboard Connector: BM14B(0.8)-24DS-0.4V(53)
* 8 MHz Crystal (STM32): X50328MSB2GI
* USB-C: TYPE-C-31-M-12
* Battery Holder: Keystone 1020
​
## Inspect AR ##
Want to inspect the badge without disassembling the acrylic faceplate?
​
We've partnered with InspectAR to leverage augment reality to just do that. 
​
* Website: https://www.inspectar.com/
* Google Play Store: https://play.google.com/store/apps/details?id=com.inspectar.app
* Apple App Store: https://apps.apple.com/us/app/inspectar-pcb-tools/id1478936899
* Nokia Sidekick Store: http://bit.ly/2PToehb
​

After installing the app on your phone, login and select "Sponsored" projects, search for "AND!XOR DC28," and download.
​
# Badge Interface Usage #

* Move Up: SYM+W
* Left: SYM+A
* Down: SYM+S
* Right: SYM+D
* Quit/back: SYM+Q
* Delete: ALT+Backspace
* Use ALT to type alternate characters _(e.g., ALT+B == !)_
* Special Characters
  * { : SYM+U
  * } : SYM+I
  * \ : SYM+G
  * = : SYM+L
  * [ : SYM+T
  * ] : SYM+Y
  * % : SYM+P
  * ~ : SYM+V
  * & : SYM+$
  * ^ : SYM+C
  * < : SYM+N
  * \> : SYM+M
  * | : SYM+F
* Bling Rager Mode: SYM+R (while in bling app)
​
# Capture The Flag Scoreboard #
​
https://nevergonnagiveyouupnevergonnaletyoudown.com/
​
# AND!XOR Public Slack #
Over the past couple of years, hackers engaged in the CTF have setup slack environments to collaborate and learn from one another. We think this is awesome and decided to setup an open slack to support this. There will be channels dedicated to each badge, i.e. DEF CON 28 (WHICH IS CANCELED, THE SAD LOLZ!) is under #dc28. We ask that you abide by only a couple cardinal rules:
* Rule 0 - Don't be an asshole
* Rule 1 - No spoilers...
​
So Rule 1 is kind of an extension of Rule 0, but it's the grey area. You're going in to slack for many reasons (which will be explained below, see BENDERPISS "frend"), and one of them may be to ask for hints because you want to learn. If you are gonna just spoil it and another wants to know how you completed a challenge, do the world some good and direct message them. Use the channel to be Socratic, answer questions by asking questions leading in the right direction, critical thinking is key to building your hacking proficiency (but if you just want to give it away, be kind enough to use direct messaging). It's a CTF with a scoreboard, so if you just dump an answer into a chat channel, you're only hurting your own score :P
​

AND!XOR Public Slack Sign Up: [https://bit.ly/3eRTR4B](https://bit.ly/3eRTR4B)
​
# Badge Enabled Non Directive Enigma Routine Portable Interface SyStem (BENDER~PISS) #
A variant of the BENDER CTF has been created such that it can be played standalone with the BBKB, on the badge, without the use of a serial terminal client. However, the back-end magic MITM wizardry which exists allows you to do both, as whatever you do in BENDERPISS is mirrored over the RS232 connect and vice versa. In fact, we prefer you check it out because it's pretty damn cool. This means you can take BENDERPISS on the go and when you get back to your mother's basement, you can plug it right back in to your 386 DX 66 with turbo button enabled and continue on.
​
* Recommended Clients
    * Putty (GUI based, there's no shame in using a GUI for efficiency) 
    * Screen (CLI based. 1337 Hax0r sauce. To quit screen terminal, press ctrl+a then press \ )
  * Note: Do NOT use minicom as it does not support extended ASCII or CP437
  * Note: On Debian based systems this will mount typically as /dev/ttyACM0
  * Note: There is a maintenance terminal as well, which can be ignored. It is mounted as ttyACM1 (nix) / COMX+1 (windows)
* Serial Connection Settings
  * USB Type C physical interface
  * Baud: 115200
  * Data Bits: 8
  * Stop Bits: 1
  * Parity: None
  * Flow Control: None
  
BENDERPISS is a collection of REDACTED hacking challenges which span encoding, encryption, static analysis binary reverse engineering, phreaking, SIGINT, OSINT, and LULZ. Traditionally this is delivered in the text based adventured format (i.e. Colossal Cave), however has been modernized slightly for ergonomics and fun. For example, to traverse the world you no longer type N S E W to move north, south, east, and west; rather W A S D. Also doing this will display an ASCII/ANSI map to give you a sense of your place in the world. To start, the badge will boot you straight into the command line terminal and recommend you type "bender" to get started. While the CTF has CLI help embedded, this file will double as a more detailed explanation given it's hard to fit everything on just one screen.
​
## CLI: bender ## 
```
and!xor:~$ bender
```
* Provides list of all available commands: hack, look, loot, map, w a s d, frend, name, reset & gender.
* Typing a command by itself also provides help in its proper usage.
​
## CLI: hack ##
```
and!xor:~$ hack
and!xor:~$ hack TARGET wit TOOL
and!xor:~$ hack flag wit ANSWER
```
* $ hack - provides help on how to use the command
* $ hack TARGET wit TOOL - by hacking a challenge TARGET (which is identified in all caps) with a TOOL things happen... sometimes the badge will do something special...sometimes it unlocks the TARGET further so you can look at it for more information about the TARGET and assist you in completing the challenge. In the latter case you will be told that the hack works and should look at your recently hacked TARGET.
* $ hack flag wit ANSWER - once you believe you have the answer to one of the CTF challenges, type "hack flag wit ANSWER" (whatever you believe that answer is). If it was correct a flag will be generated which you can enter for points on the CTF scoreboard. You must do this at the same location as the challenge (duh).
​
## CLI: look ##
```
and!xor:~$ look
and!xor:~$ look at THING
```
* $ look - provides general information about your location including a hacking challenge (i.e. You walk in to a bar and see a SHOTGLASS)
* $ look at THING - provides specific information about a THING you may see when you look (i.e. The SHOTGLASS is filled with booze)
* THINGS are identified by being in ALLCAPS. Some THINGS cannot be looked at unless you first "hack" them wit a tool you've looted. Challenges and tools are randomly scattered throughout the world so you should look everywhere...
​
## CLI: loot ##
```
and!xor:~$ loot
and!xor:~$ loot TOOL
```
* $ loot - provides help on how to use the command
* $ loot TOOL - lets you loot a TOOL you find while looking and add it to your personal loot (see that loot is a verb and a noun, because looting is awesome!)
​
## CLI: map ##
```
and!xor:~$ map
 *     *     *   *
 * * * *** * *****
 * * *   * *   *
 * * ***** *** * *
 * *   * * *   * *
 *** *** * *** ****
 *   *     * ☻
 *   * °   *
 ******************
```
* $ map - displays an ASCII map of where you are in the world
* Key ☻ - That's you!
* Key * - That's a wall!
* Key ° - That's a challenge which you have discovered!
​
## CLI: w a s d ##
```
and!xor:~$ w
and!xor:~$ a
and!xor:~$ s
and!xor:~$ d
```
* $ w - walks north in the world
* $ a - walks west in the world
* $ s - walks south in the world
* $ d - walks east in the world
* Before you get all traditional and bitch about why it isn't N S E and W...keep in mind the traditional system was invented before we had tiny keyboards on phones. It just isn't ergonomic. You will be pleased to use your left thumb to navigate and right thumb for hitting return.
​
## CLI: frend ##
```
and!xor:~$ frend
and!xor:~$ frend syn BADGEID
and!xor:~$ frend ack X0 X1 X2 X3 X4 X5 X5 X6 X7 X8
```
* TLDR: First you type frend to see your ID, share it with someone, they frend syn your ID, get a frend flag and share it with you, you frend ack that flag, get an unlock and a CTF socialization flag for points which you enter on the scoreboard. At this point, you and your new friend should swap roles to reciprocate the unlock and earn more points...or not, we're not the boss of you.
​
* $ frend - provides help on how to use the command. Not all of the BENDERPISS CTF challenges are unlocked by default. A certain number are available to everyone, while some are randomly unlocked on each badge, leaving a handful which each person cannot hack...unless they make frendz who can share their initial unlocked challenges with them... A player runs frend to obtain their BadgeID and gives it to another friend through any means; i.e. carrier pigeon, US Postal Service, HAM Radio, or the AND!XOR public slack. Below you see Hyr0n's BadgeID which he will proceed to give to Zapp.
​
  ```
  and!xor:~$ frend
  *Unlock Challngz!
  0 U giv ID 2 frend
  1 F $frend syn ID
  2 F giv U FLAG
  3 U $frend ack FLAG
  4 Both Profit!
  
  Ur BadgeID: f3c5bd
  Giv dat ID 2 Frendz
  Deetz in RTFM.MD
  ```

* $ frend syn - provides help on how to use the syn subcommand. Using a third argument to insert the BadgeID will then generate a frend flag for exchanging unlocks. This is the first step to generate a frend flag so you can share your unique unlock challenges with your new frend. They tell you their BADGEID (obtained by typing frend). This results in a 9-word flag (e.g. X0 X1 X2 X3 X4 X5 X5 X6 X7 X8) which they must frend ack. Do not confuse this with a flag which is entered on the CTF scoreboard site for points, you can try and nothing will happen. You need to give this flag back to the person who gave you the BadgeID so they can obtain the challenges which you originally had unlocked. Below Zapp is generating a frend flag for Hyr0n (BadgeID f3c5bd).
​
  ```
  and!xor:~$ frend syn
  Ax frend 4 bdge ID. datz thR public key.
  U nEd 2 encrypt it w yor prv8 key. DFIU!
  Ex: $frend syn ID
  
  and!xor:~$ frend syn f3c5bd
  FREND FLAG:
  lucky peons aimed color tweak sling grind lurks fired 
  
  Giv Bak 2 Frend 4:                                                              
  $frend ack FLAG   
  ```

* $ frend ack - provides help on how to use the ack subcommand. Using a third argument to insert ack X0 X1 X2 X3 X4 X5 X5 X6 X7 X8 will unlock whatever challenge was unlocked by default from your frend (whoever syn'd it to you). Since the frend flag is encoded by your frendz BADGEID (i.e. public key), and decrypted with their private key, it can't be used by others. This is one sexy symmetric non-reputable relationship. There is a chance that you are making frendz with someone who has the same unlock as you, so you may get somewhere between 0..3 challenges unlocked (like below). That's okay, go make MORE friends. Once a syn ack is complete a score board flag is created, that's right, you and your new frend get points for socializing. Also, if you both then syn/ack in reverse, you get double points and both have the same uniquely generated unlocks from one another's badges! That's your motivation to be a good human and not a dick.  Below Hyr0n is performing an ack of the frend flag send to him from Zapp.
​
  ```
  and!xor:~$ frend ack                                                            
  Did SOME1 GIV U a frend FLAG?                                                   
  Decrypt it here, git thR bAs unlocks & a flag 4 points. DFIU!
  Ex: $frend ack FLAG 
  
  and!xor:~$ frend ack lucky peons aimed color tweak sling grind lurks fired
  Succesful ACK!
  1 Chlngz unlocked go find dem
  Sc0r3brd Points:
  plaid whams fouls recur blood braid seats scarf idler
  bit.ly/3egadD5
  ```

## CLI: name ##
```
and!xor:~$ name
and!xor:~$ name XXXXXXX
```
* $ name - provides help on how to use the command
* $ name XXXXXX - sets your name (max length 6 characters) and generates a flag
* Enter that flag on the score board to associate your name
​
## CLI: reset ##
```
and!xor:~$ reset
and!xor:~$ reset Y
```
* $ reset - provides help on how to use the command
* $ reset Y - resets the BENDER CTF to its default factory (our garage) settings
​
## CLI: gender ##
```
and!xor:~$ gender
and!xor:~$ gender X
and!xor:~$ gender F
and!xor:~$ gender M
```
* $ gender - provides help on how to use the command
* $ gender X - sets the profile gender to non-binary
* $ gender F - sets the profile gender to female
* $ gender M - sets the profile gender to male
* This customizes the output header when viewing your loot
​
# Bling #
The badge allows you to change the bling mode, LED blink modes, add custom bling, and photos.
​
## Shortcuts ##
The keyboard changes the bling and LED modes.
Rager Mode Toggle (SYM+R)

Bling (Animations) Modes
* (A) Aeon Flux Eye
* (B) Nyan Cat
* (D) Dance
* (E) Eye
* (F) Flames
* (G) Hypnotoad
* (R) Rick Astley
* (S) Remember Me!
* (T) Netscape
* (v) Bender
* (W) Fry
* (X) Custom Bling
* (Y) Rick & Morty
* (Z) Max Headroom​

LED Modes
* (C) Bling kills COVID19
* (I) Sparkle
* (J) Evil Grin
* (K) Meteor
* (O) Rainbow
* (P) Fade
* (Q) Demonstration
* (U) DEF CON is canceled
​
## Custom Bling ##
​
Generate your own RAW file from MP4, PNG, or GIF using the following ffmpeg command:
​
```
ffmpeg -i <INPUTFILE.GIF> -y -vf "scale=128:64:force_original_aspect_ratio=decrease,pad=128:64:(ow-iw)/2:(oh-ih)/2"  -r 16 -f rawvideo -s 128x64 -pix_fmt monob CUSTOM.RAW
```
​
Goto Settings and select the "Pause Bling" toggle.
​
Overwrite `CUSTOM.RAW` file in `BLING_BW/` on the badge.
​
Run custom bling using `x` key while in the Bling app.
​
# Decoder #
​
Did you find a 6-digit code hidden by AND!XOR on the badge, phone service, bathroom stall, or out on the information superhighway? 
​
Enter it here for a scoreboard flag unique to your ID.
​
# Photos #
Photos app browses pictures (.RAW files) in `PIX/` on the badge. The badge can only display raw RGB565 files due to limited processing power.
​
## Generating RAWs from Photos ##
```
ffmpeg -i <INPUT_FILE> -y -vf "scale=160:128:force_original_aspect_ratio=decrease,pad=160:128:(ow-iw)/2:(oh-ih)/2"  -r 5 -f rawvideo -s 160x128 -pix_fmt rgb565be <OUTPUT_FILE>.RAW
```
Goto Settings and select the "Pause Bling" toggle.
​
Next, copy the .RAW file to `PIX/` folder on the badge.
​
Finally run the Photos app view the photo. Cycle photos with `n`, `p`, `a`, or `d`.
​
# MY-BASIC #
​
Run MY-BASIC programs (.BAS) located on the SPI flash storage. 
​
Yep. The badge runs MY-BASIC and has been extended to control the badge hardware (LEDs, Screen, Temperature Sensor, & Voltage Sensor) as well! The badge is now hackable with a simple programming language. MY-BASIC is limited compared to traditional BASIC, but very powerful.
​
Source: https://github.com/paladin-t/my_basic
​
# MY-BASIC Edit #
​
Edit BASIC program (.BAS) located on the SPI flash storage from the badge. For detailed information about how MY-BASIC works and coding practices...
​
RTFM: https://paladin-t.github.io/my_basic/MY-BASIC%20Quick%20Reference.pdf
​
Our portable MY-BASIC IDE native to the badge makes it easy to tweak your code on the badge. You can develop an entire program without anything else but the badge, but this may present a challenge given the screen size and language format (i.e. subroutines and loops require indentation of 8 spaces). It may be a stretch to call this an IDE, but it is MY-BASIC... Note that all changes are saved upon exit. If you mess something up, download the originals from GitHub.
​
## Debugging ##
Edit the files here and when you run them, if there is an error you will be presented with useful information:
* Debug Message: The error which is occurring
* Position: The number of characters from the beginning of the file to where the error exists
* Row: The file line where the error exists
* Col: The number of characters from the beginning of the line to where the error exists
​
Special Note: The editor will translate traditionally non-viewable characters into something viewable. 
* Windows based new line characters appear as ASCII Music Note ♪
* Linux & Windows based tabs appear as ASCII Dot ° (so in this case, using 8 spaces is a win over tab)
​
## Examples ##
The BAS folder on SPI flash contains example MY-BASIC files for you to learn from.
* BASFUK: There's something wrong with this, maybe you can fix it...
* COUNT: How to print messages to the output screen
* INPUT: How to get input from the user as well as use subroutines
* KEY: How to poll key press actions when INPUT isn't specifically used
* LED: How to blink the LEDs and change their color
* LOOP: How to use a loop
* RICK: How to play animations located in the /BLING_BW directory
* TEMP: How to read the ADC Temperature sensor value in Fahrenheit
* VOLTAGE: How to read the ADC Battery voltage sensor value
​
# Settings #

* Name Change : 6 characters max and a flag will be generated to associate your handle on the scoreboard
​
* Brightness : Use (SYM+A) to decrease and (SYM+D) to increase the LED brightness
​
* Pause & Resume Bling: Toggle this button by hitting enter to temporarily pause or resume bling. Bling is auto-resumed upon exit. This feature exists to mitigate potential SPI Flash corruption when copying or replacing custom files (e.g. RAW Animations, BAS) and Bling is playing. Essentially, if you plan on copying files to the badge's flash storage, you would be dumb to engage in a game of file system tug of war and willingly not pause the opposing party in your favor. We highly recommend you do this, or don't...we're not the boss of you.
​
# About #
* Thanks to all the hackers & philanthropists that helped us bring this badge project together. 
​
* Hugs to our sponsor frendz at Urbane Security, Penguin, & InspectAR.
​
* Hax0r contributors to this year's project: Doc, Kur3us, Alethe Denis, & Will Caruana.
​
* AND!XOR: Zapp, Hyr0n, Bender, 8Bit, Cr4bf04m, & F4nci3
​
* Thank you @arturo182 for your Blackberry Q10 research!
​
* Thank you Paladin-T (Tony Wang) for My-BASIC!
​
# Factory Reset #

* Reset the badge settings to factory (i.e. our garage) defaults. 
​
* This will not format the SPI Flash storage.