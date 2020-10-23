#include "lvgl.h"

/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef IBM_BIOS
#define IBM_BIOS 1
#endif

#if IBM_BIOS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+0 "\u0000" */
    0x0,

    /* U+1 "\u0001" */
    0x7e, 0x81, 0xa5, 0x81, 0xbd, 0x99, 0x81, 0x7e,

    /* U+2 "\u0002" */
    0x7e, 0xff, 0xdb, 0xff, 0xc3, 0xe7, 0xff, 0x7e,

    /* U+3 "\u0003" */
    0x6d, 0xff, 0xff, 0xf7, 0xc7, 0x4, 0x0,

    /* U+4 "\u0004" */
    0x10, 0x71, 0xf7, 0xf7, 0xc7, 0x4, 0x0,

    /* U+5 "\u0005" */
    0x38, 0xf8, 0xe7, 0xff, 0xef, 0x8e, 0x3e,

    /* U+6 "\u0006" */
    0x10, 0x20, 0xe3, 0xef, 0xef, 0x8e, 0x3e,

    /* U+7 "\u0007" */
    0x6f, 0xf6,

    /* U+8 "\b" */
    0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0xff,

    /* U+9 "\t" */
    0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+A "\n" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+B "\u000b" */
    0xf, 0x7, 0xf, 0x7d, 0xcc, 0xcc, 0xcc, 0x78,

    /* U+C "\f" */
    0x7b, 0x3c, 0xf3, 0x78, 0xcf, 0xcc,

    /* U+D "\r" */
    0x3f, 0x33, 0x3f, 0x30, 0x30, 0x70, 0xf0, 0xe0,

    /* U+E "\u000e" */
    0x7f, 0x63, 0x7f, 0x63, 0x63, 0x67, 0xe6, 0xc0,

    /* U+F "\u000f" */
    0x99, 0x5a, 0x3c, 0xe7, 0xe7, 0x3c, 0x5a, 0x99,

    /* U+10 "\u0010" */
    0x81, 0xc3, 0xe7, 0xff, 0x9c, 0x20, 0x0,

    /* U+11 "\u0011" */
    0x2, 0x1c, 0xff, 0xf3, 0xe1, 0xc0, 0x80,

    /* U+12 "\u0012" */
    0x31, 0xef, 0xcc, 0x33, 0xf7, 0x8c,

    /* U+13 "\u0013" */
    0xcf, 0x3c, 0xf3, 0xcc, 0xc, 0xc0,

    /* U+14 "\u0014" */
    0x7f, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b,

    /* U+15 "\u0015" */
    0x3e, 0x63, 0x38, 0x6c, 0x6c, 0x38, 0xcc, 0x78,

    /* U+16 "\u0016" */
    0xff, 0xff, 0xc0,

    /* U+17 "\u0017" */
    0x18, 0x3c, 0x7e, 0x18, 0x7e, 0x3c, 0x18, 0xff,

    /* U+18 "\u0018" */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0,

    /* U+19 "\u0019" */
    0x30, 0xc3, 0xc, 0xfd, 0xe3, 0x0,

    /* U+1A "\u001a" */
    0x18, 0x1b, 0xf8, 0x61, 0x80,

    /* U+1B "\u001b" */
    0x30, 0xc3, 0xfb, 0x3, 0x0,

    /* U+1C "\u001c" */
    0xc1, 0x83, 0x7, 0xf0,

    /* U+1D "\u001d" */
    0x24, 0x66, 0xff, 0x66, 0x24,

    /* U+1E "\u001e" */
    0x18, 0x3c, 0x7e, 0xff, 0xff,

    /* U+1F "\u001f" */
    0xff, 0xff, 0x7e, 0x3c, 0x18,

    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0x6f, 0xf6, 0x60, 0x60,

    /* U+22 "\"" */
    0xde, 0xf6,

    /* U+23 "#" */
    0x6c, 0xdb, 0xfb, 0x6f, 0xed, 0x9b, 0x0,

    /* U+24 "$" */
    0x31, 0xfc, 0x1e, 0xf, 0xe3, 0x0,

    /* U+25 "%" */
    0xc7, 0x98, 0x61, 0x86, 0x78, 0xc0,

    /* U+26 "&" */
    0x38, 0xd8, 0xe3, 0xbd, 0xd9, 0x9d, 0x80,

    /* U+27 "'" */
    0x6f, 0x0,

    /* U+28 "(" */
    0x36, 0xcc, 0xc6, 0x30,

    /* U+29 ")" */
    0xc6, 0x33, 0x36, 0xc0,

    /* U+2A "*" */
    0x66, 0x3c, 0xff, 0x3c, 0x66,

    /* U+2B "+" */
    0x30, 0xcf, 0xcc, 0x30,

    /* U+2C "," */
    0x6f, 0x0,

    /* U+2D "-" */
    0xfc,

    /* U+2E "." */
    0xf0,

    /* U+2F "/" */
    0x6, 0x18, 0x61, 0x86, 0x18, 0x20, 0x0,

    /* U+30 "0" */
    0x7d, 0x8f, 0x3e, 0xff, 0x7c, 0xdf, 0x0,

    /* U+31 "1" */
    0x31, 0xc3, 0xc, 0x30, 0xcf, 0xc0,

    /* U+32 "2" */
    0x7b, 0x30, 0xce, 0x63, 0x3f, 0xc0,

    /* U+33 "3" */
    0x7b, 0x30, 0xce, 0xf, 0x37, 0x80,

    /* U+34 "4" */
    0x1c, 0x79, 0xb6, 0x6f, 0xe1, 0x87, 0x80,

    /* U+35 "5" */
    0xff, 0xf, 0x83, 0xf, 0x37, 0x80,

    /* U+36 "6" */
    0x39, 0x8c, 0x3e, 0xcf, 0x37, 0x80,

    /* U+37 "7" */
    0xff, 0x30, 0xc6, 0x30, 0xc3, 0x0,

    /* U+38 "8" */
    0x7b, 0x3c, 0xde, 0xcf, 0x37, 0x80,

    /* U+39 "9" */
    0x7b, 0x3c, 0xdf, 0xc, 0x67, 0x0,

    /* U+3A ":" */
    0xf0, 0xf0,

    /* U+3B ";" */
    0x6c, 0x6, 0xf0,

    /* U+3C "<" */
    0x19, 0x99, 0x86, 0x18, 0x60,

    /* U+3D "=" */
    0xfc, 0x0, 0x3f,

    /* U+3E ">" */
    0xc3, 0xc, 0x33, 0x33, 0x0,

    /* U+3F "?" */
    0x7b, 0x30, 0xc6, 0x30, 0x3, 0x0,

    /* U+40 "@" */
    0x7d, 0x8f, 0x7e, 0xfd, 0xf8, 0x1e, 0x0,

    /* U+41 "A" */
    0x31, 0xec, 0xf3, 0xff, 0x3c, 0xc0,

    /* U+42 "B" */
    0xfc, 0xcd, 0x9b, 0xe6, 0x6c, 0xff, 0x0,

    /* U+43 "C" */
    0x3c, 0xcf, 0x6, 0xc, 0xc, 0xcf, 0x0,

    /* U+44 "D" */
    0xf8, 0xd9, 0x9b, 0x36, 0x6d, 0xbe, 0x0,

    /* U+45 "E" */
    0xfe, 0xc5, 0xa3, 0xc6, 0x8c, 0x7f, 0x80,

    /* U+46 "F" */
    0xfe, 0xc5, 0xa3, 0xc6, 0x8c, 0x3c, 0x0,

    /* U+47 "G" */
    0x3c, 0xcf, 0x6, 0xc, 0xec, 0xcf, 0x80,

    /* U+48 "H" */
    0xcf, 0x3c, 0xff, 0xcf, 0x3c, 0xc0,

    /* U+49 "I" */
    0xf6, 0x66, 0x66, 0xf0,

    /* U+4A "J" */
    0x1e, 0x18, 0x30, 0x6c, 0xd9, 0x9e, 0x0,

    /* U+4B "K" */
    0xe6, 0xcd, 0xb3, 0xc6, 0xcc, 0xf9, 0x80,

    /* U+4C "L" */
    0xf0, 0xc1, 0x83, 0x6, 0x2c, 0xff, 0x80,

    /* U+4D "M" */
    0xc7, 0xdf, 0xff, 0xfd, 0x78, 0xf1, 0x80,

    /* U+4E "N" */
    0xc7, 0xcf, 0xde, 0xfc, 0xf8, 0xf1, 0x80,

    /* U+4F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x6d, 0x8e, 0x0,

    /* U+50 "P" */
    0xfc, 0xcd, 0x9b, 0xe6, 0xc, 0x3c, 0x0,

    /* U+51 "Q" */
    0x7b, 0x3c, 0xf3, 0xdd, 0xe1, 0xc0,

    /* U+52 "R" */
    0xfc, 0xcd, 0x9b, 0xe6, 0xcc, 0xf9, 0x80,

    /* U+53 "S" */
    0x7b, 0x3e, 0x1c, 0x1f, 0x37, 0x80,

    /* U+54 "T" */
    0xfe, 0xd3, 0xc, 0x30, 0xc7, 0x80,

    /* U+55 "U" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xc0,

    /* U+56 "V" */
    0xcf, 0x3c, 0xf3, 0xcd, 0xe3, 0x0,

    /* U+57 "W" */
    0xc7, 0x8f, 0x1e, 0xbf, 0xfd, 0xf1, 0x80,

    /* U+58 "X" */
    0xc7, 0x8d, 0xb1, 0xc3, 0x8d, 0xb1, 0x80,

    /* U+59 "Y" */
    0xcf, 0x3c, 0xde, 0x30, 0xc7, 0x80,

    /* U+5A "Z" */
    0xff, 0x8e, 0x30, 0xc3, 0x2c, 0xff, 0x80,

    /* U+5B "[" */
    0xfc, 0xcc, 0xcc, 0xf0,

    /* U+5C "\\" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80,

    /* U+5D "]" */
    0xf3, 0x33, 0x33, 0xf0,

    /* U+5E "^" */
    0x10, 0x71, 0xb6, 0x30,

    /* U+5F "_" */
    0xff,

    /* U+60 "`" */
    0xd9, 0x80,

    /* U+61 "a" */
    0x78, 0x19, 0xf6, 0x67, 0x60,

    /* U+62 "b" */
    0xe0, 0xc1, 0x83, 0xe6, 0x6c, 0xf7, 0x0,

    /* U+63 "c" */
    0x7b, 0x3c, 0x33, 0x78,

    /* U+64 "d" */
    0x1c, 0x18, 0x33, 0xec, 0xd9, 0x9d, 0x80,

    /* U+65 "e" */
    0x7b, 0x3f, 0xf0, 0x78,

    /* U+66 "f" */
    0x39, 0xb6, 0x3c, 0x61, 0x8f, 0x0,

    /* U+67 "g" */
    0x77, 0x9b, 0x33, 0xe0, 0xdf, 0x0,

    /* U+68 "h" */
    0xe0, 0xc1, 0xb3, 0xb6, 0x6c, 0xf9, 0x80,

    /* U+69 "i" */
    0x60, 0xe6, 0x66, 0xf0,

    /* U+6A "j" */
    0xc, 0x0, 0xc3, 0xf, 0x3c, 0xde,

    /* U+6B "k" */
    0xe0, 0xc1, 0x9b, 0x67, 0x8d, 0xb9, 0x80,

    /* U+6C "l" */
    0xe6, 0x66, 0x66, 0xf0,

    /* U+6D "m" */
    0xcd, 0xff, 0xfe, 0xbc, 0x60,

    /* U+6E "n" */
    0xfb, 0x3c, 0xf3, 0xcc,

    /* U+6F "o" */
    0x7b, 0x3c, 0xf3, 0x78,

    /* U+70 "p" */
    0xdc, 0xcd, 0x9b, 0xe6, 0x1e, 0x0,

    /* U+71 "q" */
    0x77, 0x9b, 0x33, 0xe0, 0xc3, 0xc0,

    /* U+72 "r" */
    0xdc, 0xed, 0x9b, 0xf, 0x0,

    /* U+73 "s" */
    0x7f, 0x7, 0x83, 0xf8,

    /* U+74 "t" */
    0x23, 0x3e, 0xc6, 0x34, 0xc0,

    /* U+75 "u" */
    0xcd, 0x9b, 0x36, 0x67, 0x60,

    /* U+76 "v" */
    0xcf, 0x3c, 0xde, 0x30,

    /* U+77 "w" */
    0xc7, 0xaf, 0xff, 0xf6, 0xc0,

    /* U+78 "x" */
    0xc6, 0xd8, 0xe3, 0x6c, 0x60,

    /* U+79 "y" */
    0xcf, 0x3c, 0xdf, 0xf, 0xe0,

    /* U+7A "z" */
    0xfe, 0x63, 0x19, 0xfc,

    /* U+7B "{" */
    0x1c, 0xc3, 0x38, 0x30, 0xc1, 0xc0,

    /* U+7C "|" */
    0xfc, 0xfc,

    /* U+7D "}" */
    0xe0, 0xc3, 0x7, 0x30, 0xce, 0x0,

    /* U+7E "~" */
    0x77, 0xb8,

    /* U+7F "" */
    0x10, 0x71, 0xb6, 0x3c, 0x7f, 0xc0,

    /* U+A0 " " */
    0x0,

    /* U+A1 "¡" */
    0xf3, 0xfc,

    /* U+A2 "¢" */
    0x18, 0x31, 0xfe, 0xc, 0xf, 0xc6, 0xc,

    /* U+A3 "£" */
    0x38, 0xd9, 0x97, 0x86, 0x1c, 0xff, 0x0,

    /* U+A5 "¥" */
    0xcf, 0x37, 0xbf, 0x33, 0xf3, 0xc,

    /* U+A7 "§" */
    0x3e, 0x63, 0x38, 0x6c, 0x6c, 0x38, 0xcc, 0x78,

    /* U+AA "ª" */
    0x7b, 0x6d, 0x9f, 0x3, 0xf0,

    /* U+AB "«" */
    0x33, 0x66, 0xcc, 0x66, 0x33,

    /* U+AC "¬" */
    0xfc, 0x30, 0xc0,

    /* U+B0 "°" */
    0x76, 0xf6, 0xe0,

    /* U+B1 "±" */
    0x30, 0xcf, 0xcc, 0x30, 0xf, 0xc0,

    /* U+B2 "²" */
    0xe3, 0x6c, 0xf0,

    /* U+B5 "µ" */
    0x66, 0xcd, 0x9b, 0x37, 0xcc, 0x30, 0x0,

    /* U+B6 "¶" */
    0x7f, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b,

    /* U+B7 "·" */
    0xc0,

    /* U+BA "º" */
    0x76, 0xf6, 0xe0, 0x7c,

    /* U+BB "»" */
    0xcc, 0x66, 0x33, 0x66, 0xcc,

    /* U+BC "¼" */
    0xc3, 0xc6, 0xcc, 0xdb, 0x37, 0x6f, 0xcf, 0x3,

    /* U+BD "½" */
    0xc3, 0xc6, 0xcc, 0xde, 0x33, 0x66, 0xcc, 0xf,

    /* U+BF "¿" */
    0x30, 0x3, 0x18, 0xc3, 0x37, 0x80,

    /* U+C4 "Ä" */
    0xc6, 0x71, 0xb6, 0x3f, 0xf8, 0xf1, 0x80,

    /* U+C5 "Å" */
    0x30, 0xc0, 0x1e, 0xcf, 0xfc, 0xc0,

    /* U+C6 "Æ" */
    0x3e, 0xdb, 0x37, 0xfc, 0xd9, 0xb3, 0x80,

    /* U+C7 "Ç" */
    0x7b, 0x3c, 0x33, 0x78, 0x60, 0xde,

    /* U+C9 "É" */
    0x1c, 0xf, 0xd8, 0x79, 0x8f, 0xc0,

    /* U+D1 "Ñ" */
    0xfc, 0xc, 0xfb, 0xff, 0x7c, 0xc0,

    /* U+D6 "Ö" */
    0xc3, 0x18, 0x3c, 0x66, 0x66, 0x3c, 0x18,

    /* U+DC "Ü" */
    0xcc, 0xc, 0xf3, 0xcf, 0x37, 0x80,

    /* U+DF "ß" */
    0x7b, 0x3f, 0xb3, 0xfb, 0xc, 0x0,

    /* U+E0 "à" */
    0xe0, 0x1, 0xe0, 0x67, 0xd9, 0x9f, 0x80,

    /* U+E1 "á" */
    0x1c, 0x1, 0xe0, 0x67, 0xd9, 0x9f, 0x80,

    /* U+E2 "â" */
    0x7e, 0xc3, 0x3c, 0x6, 0x3e, 0x66, 0x3f,

    /* U+E4 "ä" */
    0xcc, 0x1, 0xe0, 0x67, 0xd9, 0x9f, 0x80,

    /* U+E5 "å" */
    0x30, 0x61, 0xe0, 0x67, 0xd9, 0x9f, 0x80,

    /* U+E6 "æ" */
    0x7f, 0xc, 0x7f, 0xcc, 0x7f,

    /* U+E7 "ç" */
    0x7b, 0xc, 0x1e, 0xc, 0xe0,

    /* U+E8 "è" */
    0xe0, 0x7, 0xb3, 0xff, 0x7, 0x80,

    /* U+E9 "é" */
    0x1c, 0x7, 0xb3, 0xff, 0x7, 0x80,

    /* U+EA "ê" */
    0x7e, 0xc3, 0x3c, 0x66, 0x7e, 0x60, 0x3c,

    /* U+EB "ë" */
    0xcc, 0x7, 0xb3, 0xff, 0x7, 0x80,

    /* U+EC "ì" */
    0xe0, 0x1c, 0x63, 0x19, 0xe0,

    /* U+ED "í" */
    0x70, 0xe6, 0x66, 0xf0,

    /* U+EE "î" */
    0x7d, 0x8c, 0xe0, 0xc1, 0x83, 0xf, 0x0,

    /* U+EF "ï" */
    0xcc, 0x7, 0xc, 0x30, 0xc7, 0x80,

    /* U+F1 "ñ" */
    0xf8, 0xf, 0xb3, 0xcf, 0x30,

    /* U+F2 "ò" */
    0xe0, 0x7, 0xb3, 0xcd, 0xe0,

    /* U+F3 "ó" */
    0x1c, 0x7, 0xb3, 0xcd, 0xe0,

    /* U+F4 "ô" */
    0x7b, 0x30, 0x1e, 0xcf, 0x37, 0x80,

    /* U+F6 "ö" */
    0xcc, 0x7, 0xb3, 0xcd, 0xe0,

    /* U+F7 "÷" */
    0x30, 0xc0, 0x3f, 0x0, 0xc3, 0x0,

    /* U+F9 "ù" */
    0xe0, 0x3, 0x36, 0x6c, 0xcf, 0xc0,

    /* U+FA "ú" */
    0x1c, 0x3, 0x36, 0x6c, 0xcf, 0xc0,

    /* U+FB "û" */
    0x79, 0x98, 0x6, 0x6c, 0xd9, 0x9f, 0x80,

    /* U+FC "ü" */
    0xcc, 0x3, 0x36, 0x6c, 0xcf, 0xc0,

    /* U+FF "ÿ" */
    0xcc, 0xc, 0xf3, 0x7c, 0x3f, 0x80,

    /* U+192 "ƒ" */
    0xe, 0x1b, 0x18, 0x3c, 0x18, 0x18, 0xd8, 0x70,

    /* U+393 "Γ" */
    0xff, 0x3c, 0x30, 0xc3, 0x0,

    /* U+398 "Θ" */
    0x38, 0xdb, 0x1f, 0xfc, 0x6d, 0x8e, 0x0,

    /* U+3A3 "Σ" */
    0xff, 0x36, 0xc, 0x63, 0x3f, 0xc0,

    /* U+3A6 "Φ" */
    0xfc, 0xc7, 0xb3, 0xcd, 0xe3, 0x3f,

    /* U+3A9 "Ω" */
    0x38, 0xdb, 0x1e, 0x36, 0xcd, 0xbb, 0x80,

    /* U+3B1 "α" */
    0x77, 0xbb, 0x26, 0xe7, 0x60,

    /* U+3B4 "δ" */
    0x1c, 0xc1, 0x9f, 0xcf, 0x37, 0x80,

    /* U+3B5 "ε" */
    0x3b, 0x31, 0xfc, 0x30, 0xe0,

    /* U+3C0 "π" */
    0xfe, 0xd9, 0xb3, 0x66, 0xcd, 0x80,

    /* U+3C3 "σ" */
    0x7f, 0xb3, 0x66, 0xc7, 0x0,

    /* U+3C4 "τ" */
    0x77, 0xb8, 0x60, 0xc1, 0x83, 0x0,

    /* U+3C6 "φ" */
    0x6, 0xc, 0x7e, 0xdb, 0xdb, 0x7e, 0x60, 0xc0,

    /* U+2022 "•" */
    0x6f, 0xf6,

    /* U+203C "‼" */
    0xcf, 0x3c, 0xf3, 0xcc, 0xc, 0xc0,

    /* U+207F "ⁿ" */
    0xf6, 0xf7, 0xbd, 0x80,

    /* U+20A7 "₧" */
    0xf8, 0xcc, 0xcc, 0xfa, 0xc6, 0xcf, 0xc6, 0xc7,

    /* U+2190 "←" */
    0x30, 0xc3, 0xfb, 0x3, 0x0,

    /* U+2191 "↑" */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0,

    /* U+2192 "→" */
    0x18, 0x1b, 0xf8, 0x61, 0x80,

    /* U+2193 "↓" */
    0x30, 0xc3, 0xc, 0xfd, 0xe3, 0x0,

    /* U+2194 "↔" */
    0x24, 0x66, 0xff, 0x66, 0x24,

    /* U+2195 "↕" */
    0x31, 0xef, 0xcc, 0x33, 0xf7, 0x8c,

    /* U+21A8 "↨" */
    0x18, 0x3c, 0x7e, 0x18, 0x7e, 0x3c, 0x18, 0xff,

    /* U+2219 "∙" */
    0xf0,

    /* U+221A "√" */
    0xf, 0xc, 0xc, 0xc, 0xec, 0x6c, 0x3c, 0x1c,

    /* U+221E "∞" */
    0x7e, 0xdb, 0xdb, 0x7e,

    /* U+221F "∟" */
    0xc1, 0x83, 0x7, 0xf0,

    /* U+2229 "∩" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+2248 "≈" */
    0x77, 0xb8, 0x3, 0xbd, 0xc0,

    /* U+2261 "≡" */
    0xfc, 0xf, 0xc0, 0xfc,

    /* U+2264 "≤" */
    0x18, 0xc6, 0xc, 0x18, 0xf, 0xc0,

    /* U+2265 "≥" */
    0x60, 0xc1, 0x8c, 0x60, 0xf, 0xc0,

    /* U+2302 "⌂" */
    0x10, 0x71, 0xb6, 0x3c, 0x7f, 0xc0,

    /* U+2310 "⌐" */
    0xff, 0xc, 0x0,

    /* U+2320 "⌠" */
    0x76, 0xf7, 0x8c, 0x63, 0x18,

    /* U+2321 "⌡" */
    0x18, 0xc6, 0x31, 0xef, 0x6e,

    /* U+2500 "─" */
    0xff,

    /* U+2502 "│" */
    0xff, 0xff,

    /* U+250C "┌" */
    0xfe, 0x31, 0x80,

    /* U+2510 "┐" */
    0xf8, 0xc6, 0x30,

    /* U+2514 "└" */
    0xc6, 0x31, 0x8f, 0x80,

    /* U+2518 "┘" */
    0x18, 0xc6, 0x3f, 0x80,

    /* U+251C "├" */
    0xc6, 0x31, 0x8f, 0xe3, 0x18,

    /* U+2524 "┤" */
    0x18, 0xc6, 0x3f, 0x8c, 0x63,

    /* U+252C "┬" */
    0xff, 0x18, 0x18, 0x18,

    /* U+2534 "┴" */
    0x18, 0x18, 0x18, 0x18, 0xff,

    /* U+253C "┼" */
    0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,

    /* U+2550 "═" */
    0xff, 0x0, 0xff,

    /* U+2551 "║" */
    0xde, 0xf7, 0xbd, 0xef, 0x7b,

    /* U+2552 "╒" */
    0xfe, 0x3f, 0x8c, 0x60,

    /* U+2553 "╓" */
    0xff, 0x6d, 0xb6,

    /* U+2554 "╔" */
    0xff, 0xd, 0xf6, 0xdb, 0x60,

    /* U+2555 "╕" */
    0xf8, 0xfe, 0x31, 0x8c,

    /* U+2556 "╖" */
    0xfe, 0x6c, 0xd9, 0xb0,

    /* U+2557 "╗" */
    0xfe, 0xf, 0xd9, 0xb3, 0x66, 0xc0,

    /* U+2558 "╘" */
    0xc6, 0x3f, 0x8f, 0x80,

    /* U+2559 "╙" */
    0xdb, 0x6d, 0xb6, 0xfc,

    /* U+255A "╚" */
    0xdb, 0x6d, 0xf0, 0xfc,

    /* U+255B "╛" */
    0x18, 0xfe, 0x3f, 0x80,

    /* U+255C "╜" */
    0x36, 0x6c, 0xd9, 0xbf, 0xe0,

    /* U+255D "╝" */
    0x36, 0x6f, 0xd8, 0x3f, 0xe0,

    /* U+255E "╞" */
    0xc6, 0x3f, 0x8f, 0xe3, 0x18,

    /* U+255F "╟" */
    0xdb, 0x6d, 0xb6, 0xdf, 0x6d, 0xb6,

    /* U+2560 "╠" */
    0xdb, 0x6d, 0xf0, 0xdf, 0x6d, 0xb6,

    /* U+2561 "╡" */
    0x18, 0xfe, 0x3f, 0x8c, 0x63,

    /* U+2562 "╢" */
    0x36, 0x6c, 0xd9, 0xbf, 0x66, 0xcd, 0x9b,

    /* U+2563 "╣" */
    0x36, 0x6f, 0xd8, 0x3f, 0x66, 0xcd, 0x9b,

    /* U+2564 "╤" */
    0xff, 0x0, 0xff, 0x18, 0x18, 0x18,

    /* U+2565 "╥" */
    0xff, 0x36, 0x36, 0x36,

    /* U+2566 "╦" */
    0xff, 0x0, 0xf7, 0x36, 0x36, 0x36,

    /* U+2567 "╧" */
    0x18, 0x18, 0xff, 0x0, 0xff,

    /* U+2568 "╨" */
    0x36, 0x36, 0x36, 0x36, 0xff,

    /* U+2569 "╩" */
    0x36, 0x36, 0xf7, 0x0, 0xff,

    /* U+256A "╪" */
    0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0x18, 0x18,

    /* U+256B "╫" */
    0x36, 0x36, 0x36, 0x36, 0xff, 0x36, 0x36, 0x36,

    /* U+256C "╬" */
    0x36, 0x36, 0xf7, 0x0, 0xf7, 0x36, 0x36, 0x36,

    /* U+2580 "▀" */
    0xff, 0xff, 0xff, 0xff,

    /* U+2584 "▄" */
    0xff, 0xff, 0xff, 0xff,

    /* U+2588 "█" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+258C "▌" */
    0xff, 0xff, 0xff, 0xff,

    /* U+2590 "▐" */
    0xff, 0xff, 0xff, 0xff,

    /* U+2591 "░" */
    0x23, 0x10, 0x8c, 0x42, 0x31, 0x8, 0xc4,

    /* U+2592 "▒" */
    0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa,

    /* U+2593 "▓" */
    0xdb, 0x77, 0xdb, 0xee, 0xdb, 0x77, 0xdb, 0xee,

    /* U+25A0 "■" */
    0xff, 0xff,

    /* U+25AC "▬" */
    0xff, 0xff, 0xc0,

    /* U+25B2 "▲" */
    0x18, 0x3c, 0x7e, 0xff, 0xff,

    /* U+25BA "►" */
    0x81, 0xc3, 0xe7, 0xff, 0x9c, 0x20, 0x0,

    /* U+25BC "▼" */
    0xff, 0xff, 0x7e, 0x3c, 0x18,

    /* U+25C4 "◄" */
    0x2, 0x1c, 0xff, 0xf3, 0xe1, 0xc0, 0x80,

    /* U+25CB "○" */
    0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+25D8 "◘" */
    0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0xff,

    /* U+25D9 "◙" */
    0xff, 0xc3, 0x99, 0xbd, 0xbd, 0x99, 0xc3, 0xff,

    /* U+263A "☺" */
    0x7e, 0x81, 0xa5, 0x81, 0xbd, 0x99, 0x81, 0x7e,

    /* U+263B "☻" */
    0x7e, 0xff, 0xdb, 0xff, 0xc3, 0xe7, 0xff, 0x7e,

    /* U+263C "☼" */
    0x99, 0x5a, 0x3c, 0xe7, 0xe7, 0x3c, 0x5a, 0x99,

    /* U+2640 "♀" */
    0x7b, 0x3c, 0xf3, 0x78, 0xcf, 0xcc,

    /* U+2642 "♂" */
    0xf, 0x7, 0xf, 0x7d, 0xcc, 0xcc, 0xcc, 0x78,

    /* U+2660 "♠" */
    0x10, 0x20, 0xe3, 0xef, 0xef, 0x8e, 0x3e,

    /* U+2663 "♣" */
    0x38, 0xf8, 0xe7, 0xff, 0xef, 0x8e, 0x3e,

    /* U+2665 "♥" */
    0x6d, 0xff, 0xff, 0xf7, 0xc7, 0x4, 0x0,

    /* U+2666 "♦" */
    0x10, 0x71, 0xf7, 0xf7, 0xc7, 0x4, 0x0,

    /* U+266A "♪" */
    0x3f, 0x33, 0x3f, 0x30, 0x30, 0x70, 0xf0, 0xe0,

    /* U+266B "♫" */
    0x7f, 0x63, 0x7f, 0x63, 0x63, 0x67, 0xe6, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 17, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 38, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 45, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 47, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 55, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 68, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 90, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 98, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 106, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 126, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 147, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 158, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 175, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 180, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 184, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 189, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 194, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 199, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 206, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 234, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 247, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 251, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 253, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 254, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 128, .box_w = 2, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 128, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 329, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 337, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 545, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 546, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 548, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 587, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 604, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 634, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 640, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 678, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 128, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 696, .adv_w = 128, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 698, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 128, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 714, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 727, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 735, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 740, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 745, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 748, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 751, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 128, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 760, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 767, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 128, .box_w = 2, .box_h = 1, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 775, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 779, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 784, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 792, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 800, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 832, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 863, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 870, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 903, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 908, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 949, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 955, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 960, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 965, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 970, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 976, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 981, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 993, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 999, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1012, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1018, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1026, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1031, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1038, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1050, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1062, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1068, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1079, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1084, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1090, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1098, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 1100, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1110, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1118, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1123, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1129, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1134, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1140, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1145, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1151, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1159, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 1160, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1168, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1172, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1176, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1182, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1187, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1191, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1197, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1203, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1209, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1212, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1217, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1222, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1223, .adv_w = 128, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1225, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1228, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1231, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 1235, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1239, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1244, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1249, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1253, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1258, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1266, .adv_w = 128, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1269, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1274, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1278, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1281, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1286, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1290, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1294, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1300, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 1304, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1308, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1312, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1316, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1321, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1326, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1331, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1337, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1343, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1348, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1355, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1362, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1368, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1372, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1378, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1383, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1388, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1393, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1401, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1409, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1417, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1421, .adv_w = 128, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1425, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1433, .adv_w = 128, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1437, .adv_w = 128, .box_w = 4, .box_h = 8, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 1441, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1448, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1456, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1464, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 1466, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1469, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1474, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1481, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1486, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1493, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1498, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1506, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1514, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1522, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1530, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1538, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1544, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1552, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1559, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1566, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1573, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1580, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1588, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x2, 0x3, 0x5, 0x7, 0xa, 0xb,
    0xc, 0x10, 0x11, 0x12, 0x15, 0x16, 0x17, 0x1a,
    0x1b, 0x1c, 0x1d, 0x1f, 0x24, 0x25, 0x26, 0x27,
    0x29, 0x31, 0x36, 0x3c, 0x3f, 0x40, 0x41, 0x42,
    0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
    0x4c, 0x4d, 0x4e, 0x4f, 0x51, 0x52, 0x53, 0x54,
    0x56, 0x57, 0x59, 0x5a, 0x5b, 0x5c, 0x5f, 0xf2,
    0x2f3, 0x2f8, 0x303, 0x306, 0x309, 0x311, 0x314, 0x315,
    0x320, 0x323, 0x324, 0x326, 0x1f82, 0x1f9c, 0x1fdf, 0x2007,
    0x20f0, 0x20f1, 0x20f2, 0x20f3, 0x20f4, 0x20f5, 0x2108, 0x2179,
    0x217a, 0x217e, 0x217f, 0x2189, 0x21a8, 0x21c1, 0x21c4, 0x21c5,
    0x2262, 0x2270, 0x2280, 0x2281, 0x2460, 0x2462, 0x246c, 0x2470,
    0x2474, 0x2478, 0x247c, 0x2484, 0x248c, 0x2494, 0x249c
};

static const uint16_t unicode_list_3[] = {
    0x0, 0x4, 0x8, 0xc, 0x10, 0x11, 0x12, 0x13,
    0x20, 0x2c, 0x32, 0x3a, 0x3c, 0x44, 0x4b, 0x58,
    0x59, 0xba, 0xbb, 0xbc, 0xc0, 0xc2, 0xe0, 0xe3,
    0xe5, 0xe6, 0xea, 0xeb
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 0, .range_length = 128, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 160, .range_length = 9373, .glyph_id_start = 129,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 103, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 9552, .range_length = 29, .glyph_id_start = 232,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 9600, .range_length = 236, .glyph_id_start = 261,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 28, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t ibm_bios = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 8,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if IBM_BIOS*/

