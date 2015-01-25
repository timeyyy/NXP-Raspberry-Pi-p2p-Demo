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

#include	<stdint.h>
#include	<string.h>
#include	"ndef_message.h"

/* select the required type of transported data */
//#include <c_tabletxt.h>
//#include	<c_tablepng.h>
//#include <c_tablepng_NXP_QR.h>
#include <c_tablejpg_NXP_logo.h>

const char *language[]={"no", "en", "gr", "fr"};
const char *images[]={"image/jpeg", "image/png", "image/gif","image/tiff"};

/* NDEF messages URI, type 0x01 http://www. */
//uint8_t uri_11[] = "nxp.com/news/press-releases/2011/10/NFC-Enables-Secure-Wireless-Access-to-Smart-Meters.html";
//uint8_t uri_12[] = "nxp.com/news/press-releases/2011/11/nxp-achieves-quantum-leap-with-infrastructure-reader-ic-clrc663.html";
//uint8_t uri_13[] = "nxp.com/news/press-releases/2012/06/nxp-deploys-nfc-in-nexus-7.html";
//uint8_t uri_14[] = "nxp.com/news/press-releases/2012/05/nxp-powers-nfc-in-the-samsung-galaxy-s-iii.html";
const uint8_t uri_14[] = "rec-global.com";
const uint8_t uri_12[] = "nxp.com";
const uint8_t uri_11[] = "ediscomp.sk/produkt/Samsung-GalaxyTab2-P5100,10%22-16GB-Titanium-silver-958880000295/";
const uint8_t uri_13[] = "ediscomp.sk/produkt/TomTom-PRO-5150-Truck-LIVE-EU-LIFETIME-mapy-219701028/";

/* NDEF messages URI, type 0x03 http://*/
const uint8_t uri_31[] = "blog.nxp.com/nfc-a-new-era-of-proximity-marketing/";
const uint8_t uri_32[] = "blog.nxp.com/yes-it-was-a-great-summer-for-nfc/";

/* NDEF messages URI, type 0x05 phone number */
const uint8_t uri_51[] = "0435382001";
const uint8_t uri_52[] = "00421911902887";
const uint8_t uri_53[] = "004215650254";
const uint8_t uri_54[] = "0904901723";

/* NDEF messages TEXT */
const uint8_t text1[] = "This is message No1";
const uint8_t text2[] = "This is message No2";
const uint8_t text3[] = "This is message No3";
const uint8_t text4[] = "This is message No4";
const uint8_t text5[] = "This is message No5";
const uint8_t text6[] = "SNEP test string PN-512";
const uint8_t text7[] = "SNEP test string RC-663";

snep_st st_snep;

/* from this table function "Ndef_Decide" choose kind and body of message */
NDEF_messages n_mess[]={ /* type, parameter, string */
      {NDEF_TYPE_IMAGE,NDEF_IMAGE_JPEG,c_table, sizeof(c_table)},
//      {NDEF_TYPE_IMAGE,NDEF_IMAGE_PNG,c_table, sizeof(c_table)},
//      {NDEF_TYPE_IMAGE,NDEF_IMAGE_TIFF,c_table, sizeof(c_table)},
//      {'T', LANG_NO, text1, sizeof(text1)},
//      {'T', LANG_EN, c_table, sizeof(c_table)},
//      {'T', LANG_EN, text1, sizeof(text1)},
//      {'T', LANG_GR, text2, sizeof(text2)},
//      {'T', LANG_FR, text3, sizeof(text3)},
//      {'T', LANG_EN, text6, sizeof(text6)},
//      {'T', LANG_EN, text6, sizeof(text7)},
//      {'U', NDEF_URI_WWW, uri_11, sizeof(uri_11)},
//      {'U', NDEF_URI_WWW, uri_12, sizeof(uri_12)},
//      {'U', NDEF_URI_WWW, uri_13, sizeof(uri_13)},
//      {'U', NDEF_URI_HTTP, uri_13, sizeof(uri_13)},
//      {'U', NDEF_URI_TEL, uri_52, sizeof(uri_52)},
};

/* Prepare Short NDEF text record with language extension or without */
uint32_t	Ndef_Prepare_Text(snep_st *snepData)
{
	uint32_t 		status = 0;
	Convert32To4	con32;

	pNDEF_text p_ndef;

	/* pointer to NDEF structure now pointed to buffer */
	p_ndef = (pNDEF_text)snepData->buffer;

	// copy language text
	memcpy(&p_ndef->codechar, language[snepData->ndef_param], 2);

	p_ndef->codelen = 2;
	con32.val = snepData->payload_len + 3;

	/* fill structure of TEXT NDEF message */
	p_ndef->flags = 0xc1;
	reverse32(p_ndef->paylen, &con32);
	p_ndef->typelen = 0x01;
	p_ndef->type = 'T';

	snepData->payload_len = con32.val - 3;	// size of NDEF payload without language part
	snepData->payload_start = 10; // index start payload

	return status;
}

uint32_t	Ndef_Prepare_Image(snep_st *snepData)
{
	Convert32To4 sui32;
	pNDEF_mime p_ndef;
	const char *str;

	p_ndef = (pNDEF_mime)snepData->buffer;
	str = images[snepData->ndef_param];

	p_ndef->flags = 0xc2;
	p_ndef->typelen = strlen(str);
	memcpy(p_ndef->type, str, p_ndef->typelen);

	sui32.val = snepData->payload_len;// + p_ndef->typelen;	// set payload len
	reverse32(p_ndef->paylen, &sui32);
	snepData->payload_start = p_ndef->typelen + 6;
	return 0;
}

/* Prepare Short NDEF URI record with type extension or without */
uint32_t	Ndef_Prepare_Uri(snep_st *snepData)
{
	uint32_t status = 0;
	Convert32To4	con32;

	pNDEF_uri p_ndef;

	/* pointer to URI message now pointed to buffer */
	p_ndef = (pNDEF_uri)snepData->buffer;
	con32.val = snepData->payload_len + 1;

	/* fill structure of URI NDEF message */
	p_ndef->flags = 0xc1;
	p_ndef->typelen = 0x01;

	reverse32( p_ndef->paylen, &con32);
	p_ndef->type = 'U';
	p_ndef->uri_identifier = snepData->ndef_param;

	snepData->payload_len = con32.val - 1;
	snepData->payload_start = 8;

	return status;
}

/* return pointer to structure from  n_mess[] table depend of input index
   if index is too high return NULL */
NDEF_messages *	Ndef_Get_Mess(uint16_t index)
{
	if(index >= sizeof(n_mess)/sizeof(NDEF_messages))
		return NULL;

	return (&n_mess[index]);
}

/* fill array of NDEF message depend of input index */
uint32_t Ndef_Decide(snep_st *snepData, NDEF_messages *pndef)
{
	uint32_t status = 0;

	snepData->picture = pndef->str;
	snepData->ndef_param = pndef->param;
	snepData->payload_len = pndef->str_size;

	switch(pndef->type)
	{
		case NDEF_TYPE_TEXT:
			status = Ndef_Prepare_Text(snepData);
			break;
		case NDEF_TYPE_URI:
			status = Ndef_Prepare_Uri(snepData);
			break;
		case NDEF_TYPE_IMAGE:
			status = Ndef_Prepare_Image(snepData);
			break;
		default:
			status = 0xff;
			break;
	}

	return status;
}

void reverse32( uint8_t* buf, Convert32To4* conv)
{
	buf[0] = conv->field[3];
	buf[1] = conv->field[2];
	buf[2] = conv->field[1];
	buf[3] = conv->field[0];
}

