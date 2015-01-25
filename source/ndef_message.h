/*==============================================================================================
 *         Copyright (c), NXP Semiconductors
 *
 *       All rights are reserved. Reproduction in whole or in part is
 *      prohibited without the written consent of the copyright owner.
 *  NXP reserves the right to make changes without notice at any time.
 * NXP makes no warranty, expressed, implied or statutory, including but
 * not limited to any implied warranty of merchantability or fitness for any
 *particular purpose, or that the use will not infringe any third party patent,
 * copyright or trademark. NXP must not be liable for any loss or damage
 *                          arising from its use.
 */

/*==============================================================================================
 *
 *   File name:  ndef_message.h
 *
 *  Created on:  March, 2013
 *      Author:  Miroslav Kajan
 *
 *     Hystory:  2013.03.26  ver 1.00    initial version
 */

#ifndef NDEF_MESSAGE_H_
#define NDEF_MESSAGE_H_

#endif /* NDEF_MESSAGE_H_ */

#define	SNEP_HEADER          6
/* NDEF file size */
#define NDEF_FILE_SIZE        256

#define	LANG_NO			      0	// index for message withou language type
#define	LANG_EN			      1	// index for English language
#define	LANG_GR			      2	// index for German language
#define	LANG_FR			      3	// index for France language

#define  NDEF_TYPE_TEXT       0x54 // code for text message
#define  NDEF_TYPE_URI        0x55 // code for URI message
#define  NDEF_TYPE_IMAGE      0xf1 // code for Picture

#define	NDEF_URI_NA          0x00 // code for no specific URI message
#define	NDEF_URI_WWW         0x01 // code for for URI message begin with http://www.
#define	NDEF_URI_HTTP        0x03 // code for for URI message begin with http://
#define	NDEF_URI_TEL         0x05 // code for for URI message phone number

#define  NDEF_IMAGE_JPEG      0x00
#define  NDEF_IMAGE_PNG       0x01
#define  NDEF_IMAGE_GIF       0x02
#define  NDEF_IMAGE_TIFF      0x03

#define  NDEF_PARAM_LEN       2  // first two byte of message are totally length of message
#define  DEFAULT_TEXT_LEN     4  // default length for text Short message
#define  DEFAULT_URI_LEN      5  // default length for URI Short message

// type can be: NDEF_TYPE_TEXT or NDEF_TYPE_URI
// if type is NDEF_TYPE_TEXT param can be: LANG_NO or LANG_EN or LANG_GR or LANG_FR
// if type id NDEF_TYPE_URI param can be: NDEF_TYPE_URI or NDEF_URI_WWW or NDEF_URI_HTTP or NDEF_URI_TEL
typedef struct
{
   uint8_t        type;
   uint8_t        param;
   const uint8_t  *str;
   uint16_t       str_size;
}NDEF_messages;

// structure for Short TEXT NDEF message
typedef	struct
{
   uint8_t  flags;
   uint8_t  typelen;
   uint8_t  paylen[4];
   uint8_t  type;
   uint8_t  codelen;
   uint8_t  codechar[2];
   uint8_t  textstr[];
}*pNDEF_text;

// structure for Short URI NDEF message
typedef	struct
{
   uint8_t  flags;
   uint8_t  typelen;
   uint8_t  paylen[4];
   uint8_t  type;
   uint8_t  uri_identifier;
   uint8_t  textstr[];
}*pNDEF_uri;

// structure for Short URI NDEF message
typedef	struct
{
   uint8_t  flags;
   uint8_t  typelen;
   uint8_t  paylen[4];
   uint8_t  type[];
}*pNDEF_mime;

typedef	struct
{
   uint8_t  payload_start;
   uint8_t	ndef_param;
   uint32_t payload_len;
   uint32_t	snep_len;
   uint8_t  *buffer;
   const uint8_t 	*typestr;
   const uint8_t 	*picture;
}snep_st;

typedef union
{
	uint8_t		field[4];
	uint32_t	val;
}Convert32To4;

extern NDEF_messages n_mess[];
extern	snep_st st_snep;
/* return pointer to structure from  n_mess[] table depend of input index
   if index is too high return NULL */
extern NDEF_messages *	Ndef_Get_Mess(uint16_t index);

// Choose nedef message depend of index and fill array of NDEF message
extern uint32_t Ndef_Decide(snep_st *snepData, NDEF_messages *pndef);

extern void reverse32( uint8_t* buf, Convert32To4* conv);
