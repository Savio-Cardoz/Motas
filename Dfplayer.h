/*
 * dfplayer.h
 *
 * Created: 5/20/2017 12:38:12 AM
 *  Author: Cardoz
 */ 


#ifndef DFPLAYER_H_
#define DFPLAYER_H_


/************************************************************************/
/*	Commands listed are only the ones that'll be used in the system		*/
/************************************************************************/
#define CMD_STRT_BYTE	0x7E
#define CMD_VER			0xFF
#define CMD_END_BYTE	0xEF
#define CMD_NEXT		0x01
#define CMD_PREV		0x02
#define CMD_PLY_TRCK	0x03
#define CMD_VOL_UP		0x04
#define CMD_VOL_DN		0x05
#define CMD_PLY_MODE	0x08
#define CMD_RESET		0x0C
#define CMD_PLY			0x0D
#define	CMD_PAUSE		0x0E
#define CMD_STOP		0x16
#define CMD_TF_FILES	0x47

#define CMD_RECV_FB		0x01
#define CMD_RECV_NFB	0x00
#define CMD_BUFFER_SIZE 8

uint8_t cmdbuffer[CMD_BUFFER_SIZE];




#endif /* DFPLAYER_H_ */