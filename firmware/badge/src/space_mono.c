#include "lvgl.h"

/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef SPACE_MONO
#define SPACE_MONO 1
#endif

#if SPACE_MONO

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+0 "\u0000" */
    0x0,

    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xf4,

    /* U+22 "\"" */
    0xb0,

    /* U+23 "#" */
    0xdf, 0xc0,

    /* U+24 "$" */
    0x5d, 0xf4,

    /* U+25 "%" */
    0x4a, 0x57, 0x33,

    /* U+26 "&" */
    0x64, 0x24, 0xf9, 0x78,

    /* U+27 "'" */
    0xc0,

    /* U+28 "(" */
    0x3c, 0x88, 0x88, 0xc3,

    /* U+29 ")" */
    0xc3, 0x11, 0x11, 0x3c,

    /* U+2A "*" */
    0x23, 0xbe, 0x40,

    /* U+2B "+" */
    0x5d, 0x0,

    /* U+2C "," */
    0xc0,

    /* U+2D "-" */
    0xe0,

    /* U+2E "." */
    0x80,

    /* U+2F "/" */
    0x29, 0x29, 0x20,

    /* U+30 "0" */
    0x69, 0x9b, 0x96,

    /* U+31 "1" */
    0x65, 0x28, 0x42, 0x7c,

    /* U+32 "2" */
    0x69, 0x16, 0x8f,

    /* U+33 "3" */
    0x78, 0x8d, 0x18, 0xb8,

    /* U+34 "4" */
    0x66, 0xaa, 0xf2,

    /* U+35 "5" */
    0xe8, 0xfd, 0x9e,

    /* U+36 "6" */
    0x69, 0xe9, 0x96,

    /* U+37 "7" */
    0xf1, 0x24, 0x48,

    /* U+38 "8" */
    0x69, 0x96, 0x9f,

    /* U+39 "9" */
    0x69, 0x97, 0x96,

    /* U+3A ":" */
    0x90,

    /* U+3B ";" */
    0x98,

    /* U+3C "<" */
    0xec, 0x30,

    /* U+3D "=" */
    0xfc,

    /* U+3E ">" */
    0xe3, 0xc0,

    /* U+3F "?" */
    0x69, 0x92, 0x2,

    /* U+40 "@" */
    0x65, 0xbb, 0xf0,

    /* U+41 "A" */
    0x62, 0x94, 0xa7, 0x44,

    /* U+42 "B" */
    0xe9, 0x9e, 0x9f,

    /* U+43 "C" */
    0x79, 0x88, 0x97,

    /* U+44 "D" */
    0xe9, 0x99, 0x9e,

    /* U+45 "E" */
    0xf8, 0x8f, 0x8f,

    /* U+46 "F" */
    0xf8, 0x8f, 0x88,

    /* U+47 "G" */
    0x69, 0x8b, 0x97,

    /* U+48 "H" */
    0x99, 0x9f, 0x99,

    /* U+49 "I" */
    0xe9, 0x25, 0xc0,

    /* U+4A "J" */
    0x31, 0x11, 0x97,

    /* U+4B "K" */
    0x9a, 0xac, 0xa9,

    /* U+4C "L" */
    0x88, 0x88, 0x8f,

    /* U+4D "M" */
    0xff, 0xff, 0xfd,

    /* U+4E "N" */
    0xdd, 0xdd, 0xbb,

    /* U+4F "O" */
    0x69, 0x99, 0x96,

    /* U+50 "P" */
    0xe9, 0x9e, 0x88,

    /* U+51 "Q" */
    0x69, 0x99, 0x96, 0x20,

    /* U+52 "R" */
    0xe9, 0x9e, 0x99,

    /* U+53 "S" */
    0x69, 0x87, 0x97,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x10,

    /* U+55 "U" */
    0x99, 0x99, 0x96,

    /* U+56 "V" */
    0x8c, 0x94, 0xa6, 0x30,

    /* U+57 "W" */
    0xef, 0x7b, 0xe7, 0x28,

    /* U+58 "X" */
    0xb7, 0x2b, 0x40,

    /* U+59 "Y" */
    0x8a, 0x94, 0xc2, 0x10,

    /* U+5A "Z" */
    0xf3, 0x24, 0xcf,

    /* U+5B "[" */
    0xea, 0xab,

    /* U+5C "\\" */
    0x91, 0x24, 0x48,

    /* U+5D "]" */
    0xd5, 0x57,

    /* U+5E "^" */
    0x54, 0x0,

    /* U+5F "_" */
    0xe0,

    /* U+60 "`" */
    0x80,

    /* U+61 "a" */
    0x79, 0x9f,

    /* U+62 "b" */
    0x88, 0xe9, 0x9f,

    /* U+63 "c" */
    0x78, 0x87,

    /* U+64 "d" */
    0x11, 0x79, 0x9f,

    /* U+65 "e" */
    0x7f, 0x96,

    /* U+66 "f" */
    0x74, 0xf4, 0x44,

    /* U+67 "g" */
    0x79, 0x97, 0x17,

    /* U+68 "h" */
    0x88, 0xf9, 0x99,

    /* U+69 "i" */
    0x43, 0x25, 0xc0,

    /* U+6A "j" */
    0x63, 0x92, 0x4f,

    /* U+6B "k" */
    0x88, 0xac, 0xca,

    /* U+6C "l" */
    0xc9, 0x25, 0xc0,

    /* U+6D "m" */
    0xfd, 0x6b, 0x50,

    /* U+6E "n" */
    0xf9, 0x99,

    /* U+6F "o" */
    0x69, 0x96,

    /* U+70 "p" */
    0xe9, 0x9f, 0x88,

    /* U+71 "q" */
    0x79, 0x9f, 0x11,

    /* U+72 "r" */
    0xf5, 0x4e,

    /* U+73 "s" */
    0xf1, 0xf0,

    /* U+74 "t" */
    0x44, 0xf4, 0x46,

    /* U+75 "u" */
    0x99, 0x9f,

    /* U+76 "v" */
    0x95, 0x56,

    /* U+77 "w" */
    0xef, 0x7c, 0xe0,

    /* U+78 "x" */
    0xb9, 0x50,

    /* U+79 "y" */
    0x99, 0x9f, 0x17,

    /* U+7A "z" */
    0xf2, 0x4f,

    /* U+7B "{" */
    0x69, 0x44, 0x93,

    /* U+7C "|" */
    0xff,

    /* U+7D "}" */
    0xc9, 0x14, 0x96,

    /* U+7E "~" */
    0x43,

    /* U+A0 " " */
    0x0,

    /* U+A1 "¡" */
    0xbc,

    /* U+A2 "¢" */
    0x27, 0xa9, 0x66, 0x0,

    /* U+A3 "£" */
    0xda, 0x60,

    /* U+A4 "¤" */
    0xf9, 0x9f,

    /* U+A5 "¥" */
    0xbb, 0xf0,

    /* U+A6 "¦" */
    0xff,

    /* U+A7 "§" */
    0xf7,

    /* U+A8 "¨" */
    0xa0,

    /* U+A9 "©" */
    0x6d, 0xdd, 0x60,

    /* U+AA "ª" */
    0xf5, 0x80,

    /* U+AB "«" */
    0x1e, 0xe5,

    /* U+AC "¬" */
    0xe0,

    /* U+AE "®" */
    0x69, 0xd9, 0x60,

    /* U+AF "¯" */
    0xe0,

    /* U+B0 "°" */
    0x55, 0x0,

    /* U+B1 "±" */
    0x5d, 0x70,

    /* U+B2 "²" */
    0xc0,

    /* U+B3 "³" */
    0x6c,

    /* U+B4 "´" */
    0x80,

    /* U+B5 "µ" */
    0x99, 0x9f, 0x88,

    /* U+B6 "¶" */
    0xfd, 0xb0,

    /* U+B7 "·" */
    0x80,

    /* U+B8 "¸" */
    0xc0,

    /* U+B9 "¹" */
    0xe0,

    /* U+BA "º" */
    0xd7, 0x0,

    /* U+BB "»" */
    0xa7, 0x7a,

    /* U+BC "¼" */
    0xcd, 0x61, 0x10,

    /* U+BD "½" */
    0xc2, 0x3e, 0x90, 0x8c,

    /* U+BE "¾" */
    0x88, 0x96, 0x33,

    /* U+BF "¿" */
    0x20, 0x49, 0x96,

    /* U+C0 "À" */
    0x3, 0x14, 0xa5, 0x3a, 0x20,

    /* U+C1 "Á" */
    0x23, 0x14, 0xa5, 0x3a, 0x20,

    /* U+C2 "Â" */
    0x23, 0x14, 0xa5, 0x3a, 0x20,

    /* U+C3 "Ã" */
    0x73, 0x14, 0xa5, 0x3a, 0x20,

    /* U+C4 "Ä" */
    0x53, 0x14, 0xa5, 0x3a, 0x20,

    /* U+C5 "Å" */
    0x21, 0x8, 0xa5, 0x29, 0xf1,

    /* U+C6 "Æ" */
    0x76, 0xab, 0xeb,

    /* U+C7 "Ç" */
    0x79, 0x88, 0x97, 0x22,

    /* U+C8 "È" */
    0xf, 0x88, 0xf8, 0xf0,

    /* U+C9 "É" */
    0x2f, 0x88, 0xf8, 0xf0,

    /* U+CA "Ê" */
    0x6f, 0x88, 0xf8, 0xf0,

    /* U+CB "Ë" */
    0xaf, 0x88, 0xf8, 0xf0,

    /* U+CC "Ì" */
    0x5d, 0x24, 0xb8,

    /* U+CD "Í" */
    0x5d, 0x24, 0xb8,

    /* U+CE "Î" */
    0x5d, 0x24, 0xb8,

    /* U+CF "Ï" */
    0xbd, 0x24, 0xb8,

    /* U+D0 "Ð" */
    0xe9, 0x9d, 0x9e,

    /* U+D1 "Ñ" */
    0x6d, 0xdd, 0xdb, 0xb0,

    /* U+D2 "Ò" */
    0x6, 0x99, 0x99, 0x60,

    /* U+D3 "Ó" */
    0x26, 0x99, 0x99, 0x60,

    /* U+D4 "Ô" */
    0x6, 0x99, 0x99, 0x60,

    /* U+D5 "Õ" */
    0x66, 0x99, 0x99, 0x60,

    /* U+D6 "Ö" */
    0x56, 0x99, 0x99, 0x60,

    /* U+D7 "×" */
    0xaa, 0x80,

    /* U+D8 "Ø" */
    0x6b, 0xdd, 0xd6, 0x0,

    /* U+D9 "Ù" */
    0x9, 0x99, 0x99, 0x60,

    /* U+DA "Ú" */
    0x29, 0x99, 0x99, 0x60,

    /* U+DB "Û" */
    0x9, 0x99, 0x99, 0x60,

    /* U+DC "Ü" */
    0x59, 0x99, 0x99, 0x60,

    /* U+DD "Ý" */
    0x24, 0x54, 0xa6, 0x10, 0x80,

    /* U+DE "Þ" */
    0x8e, 0x99, 0xe8,

    /* U+DF "ß" */
    0xea, 0xaa, 0x9f,

    /* U+E0 "à" */
    0x40, 0x79, 0x9f,

    /* U+E1 "á" */
    0x0, 0x79, 0x9f,

    /* U+E2 "â" */
    0x60, 0x79, 0x9f,

    /* U+E3 "ã" */
    0x42, 0x79, 0x9f,

    /* U+E4 "ä" */
    0x50, 0x79, 0x9f,

    /* U+E5 "å" */
    0x46, 0x79, 0x97,

    /* U+E6 "æ" */
    0x77, 0xa6,

    /* U+E7 "ç" */
    0x78, 0x87, 0x22,

    /* U+E8 "è" */
    0x40, 0x7f, 0x96,

    /* U+E9 "é" */
    0x20, 0x7f, 0x96,

    /* U+EA "ê" */
    0x60, 0x7f, 0x96,

    /* U+EB "ë" */
    0xa0, 0x7f, 0x96,

    /* U+EC "ì" */
    0x43, 0x25, 0xc0,

    /* U+ED "í" */
    0x43, 0x25, 0xc0,

    /* U+EE "î" */
    0xe3, 0x25, 0xc0,

    /* U+EF "ï" */
    0xa3, 0x25, 0xc0,

    /* U+F0 "ð" */
    0x42, 0x79, 0x96,

    /* U+F1 "ñ" */
    0x56, 0xf9, 0x99,

    /* U+F2 "ò" */
    0x0, 0x69, 0x96,

    /* U+F3 "ó" */
    0x0, 0x69, 0x96,

    /* U+F4 "ô" */
    0x60, 0x69, 0x96,

    /* U+F5 "õ" */
    0x42, 0x69, 0x96,

    /* U+F6 "ö" */
    0x50, 0x69, 0x96,

    /* U+F7 "÷" */
    0x43, 0xa0,

    /* U+F8 "ø" */
    0x6d, 0xd6,

    /* U+F9 "ù" */
    0x0, 0x99, 0x9f,

    /* U+FA "ú" */
    0x20, 0x99, 0x9f,

    /* U+FB "û" */
    0x60, 0x99, 0x9f,

    /* U+FC "ü" */
    0x0, 0x99, 0x9f,

    /* U+FD "ý" */
    0x20, 0x99, 0x9f, 0x17,

    /* U+FE "þ" */
    0x88, 0xe9, 0x9f, 0x88,

    /* U+FF "ÿ" */
    0xa0, 0x99, 0x9f, 0x17
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 78, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 78, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 4, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 6, .adv_w = 78, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 78, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 16, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 27, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 29, .adv_w = 78, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 31, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 78, .box_w = 1, .box_h = 4, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 78, .box_w = 1, .box_h = 5, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 78, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 71, .adv_w = 78, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 72, .adv_w = 78, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 74, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 133, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 166, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 169, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 171, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 173, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 174, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 175, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 78, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 202, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 218, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 221, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 240, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 78, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 245, .adv_w = 78, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 246, .adv_w = 78, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 249, .adv_w = 78, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 250, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 78, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 252, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 258, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 260, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 262, .adv_w = 78, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 263, .adv_w = 78, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 264, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 265, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 268, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 270, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 273, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 276, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 277, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 279, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 78, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 282, .adv_w = 78, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 283, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 284, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 287, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 289, .adv_w = 78, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 290, .adv_w = 78, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 291, .adv_w = 78, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 292, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 294, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 309, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 78, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 346, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 403, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 407, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 457, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 78, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 504, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 522, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 526, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 0, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 2,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 160, .range_length = 13, .glyph_id_start = 97,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 174, .range_length = 82, .glyph_id_start = 110,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
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
lv_font_t space_mono = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if SPACE_MONO*/

