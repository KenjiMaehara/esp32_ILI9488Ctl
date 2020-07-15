/*******************************************************************************
*  skMCP230.h - MCP23017(I2C)�֐����C�u�����̃w�b�_�t�@�C��                    *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY                    CHANGE/COMMENT                  *
* ---------------------------------------------------------------------------- *
*   1.00     2015-11-15  ���ޒ��H�[     Create                                 *
* ============================================================================ *
*   Arduino IDE 1.7.3 (Ardino Duemilanove 328/UNO ZERO/M0)                     *
*******************************************************************************/
#ifndef _SKMCP230_H_
#define _SKMCP230_H_

#include "arduino.h"


// �f�o�C�X�̂h�^�n���W�X�^�R���t�B�O
#define IODIRA			0b00000000	// GPA0-GPA7�s���͑S�ďo��(0=OUTPUT 1=INPUT)
#define IODIRB			0b00000000	// GPB0�͓��́AGPB1-GPB7�s���͏o�͂Ɋ����Ă�
#define IPOLA			0b00000000	// GPA0-GPA7�s���͑S�Đ��ɐ�(0=���ɐ� 1=�t�ɐ�)
#define IPOLB			0b00000000	// GPB0-GPB7�s���͑S�Đ��ɐ��ɐݒ�
#define GPPUA			0b00000000	// GPA0-GPA7�s���͑S�ăv���A�b�v����(0=���� 1=�L��)
#define GPPUB			0b00000000	// GPB0�͗L���AGPB1-GPB7�s���̓v���A�b�v�����Ƃ���
// ���荞�݃��W�X�^�֘A�̃R���t�B�O
#define GPINTENA		0b00000000	// GPA0-GPA7�s���͑S�Ċ����ݖ���(0=���� 1=�L��)
#define GPINTENB		0b00000000	// GPB0-GPB7�s���͑S�Ċ����ݖ����ɐݒ�
#define DEFVALA 		0b00000000	// GPA�s��(0="�P"�Ŋ�����  1="�O"�Ŋ�����)
#define DEFVALB 		0b00000000	// GPB�s�������ݎ��̕�����r�l  0b00000001
#define INTCONA 		0b00000000	// GPA�s��(0=�ω����Ɋ�����  1=DEFVAL�l�Ŋ�����)
#define INTCONB 		0b00000000	// GPB�s���ω������̊����ݐ���  0b00000001
// I/O�R���t�B�O���[�V�������W�X�^
// BANK0,�����C���N�������g�L��,SDA�̃X���[���[�gON,INT�o�͂̓A�N�e�B�uHIGH,INTA/INTB�ʏo��
#define IOCON			0b00000010


// �f�o�C�X�̃��W�X�^�A�h���X(BANK=0)
#define IODIRA_ADRS		0x00			// GPA�s����I/O�������W�X�^�A�h���X
#define IODIRB_ADRS		0x01			// GPB�s����I/O�������W�X�^�A�h���X
#define IPOLA_ADRS		0x02			// GPA�s���̓��͋ɐ��|�[�g���W�X�^�A�h���X
#define IPOLB_ADRS		0x03			// GPB�s���̓��͋ɐ��|�[�g���W�X�^�A�h���X
#define GPPUA_ADRS		0x0C			// GPA�s���̃v���A�b�v���W�X�^�A�h���X
#define GPPUB_ADRS		0x0D			// GPB�s���̃v���A�b�v���W�X�^�A�h���X
#define GPIOA_ADRS		0x12			// GPA�s���̃|�[�g���W�X�^�A�h���X
#define GPIOB_ADRS		0x13			// GPB�s���̃|�[�g���W�X�^�A�h���X
#define OLATA_ADRS		0x14			// GPA�s���̃��b�`���W�X�^�A�h���X
#define OLATB_ADRS		0x15			// GPB�s���̃��b�`���W�X�^�A�h���X
// ��ԕω������݊֘A���W�X�^�A�h���X(BANK=0)
#define GPINTENA_ADRS	0x04			// GPA�s���̏�ԕω������݋����W�X�^�A�h���X
#define GPINTENB_ADRS	0x05			// GPB�s���̏�ԕω������݋����W�X�^�A�h���X
#define DEFVALA_ADRS	0x06			// GPA�s���̕ω�������r���W�X�^�A�h���X
#define DEFVALB_ADRS	0x07			// GPB�s���̕ω�������r���W�X�^�A�h���X
#define INTCONA_ADRS	0x08			// GPA�s���̏�ԕω������ݐ��䃌�W�X�^�A�h���X
#define INTCONB_ADRS	0x09			// GPB�s���̏�ԕω������ݐ��䃌�W�X�^�A�h���X
#define INTFA_ADRS  	0x0E			// GPA�s���̊����݃t���O���W�X�^�A�h���X
#define INTFB_ADRS  	0x0F			// GPB�s���̊����݃t���O���W�X�^�A�h���X
#define INTCAPA_ADRS	0x10			// GPA�s���̊����ݎ��̃r�b�g�l���W�X�^�A�h���X
#define INTCAPB_ADRS	0x11			// GPB�s���̊����ݎ��̃r�b�g�l���W�X�^�A�h���X
// I/O�R���t�B�O���[�V�������W�X�^�A�h���X(BANK=0)
#define IOCON_ADRS		0x0A			// I/O�R���t�B�O���[�V�������W�X�^�A�h���X

// �s���̒萔��`
#define GPA			0
#define GPA0			0
#define GPA1			1
#define GPA2			2
#define GPA3			3
#define GPA4			4
#define GPA5			5
#define GPA6			6
#define GPA7			7
#define GPB			1
#define GPB0			0
#define GPB1			1
#define GPB2			2
#define GPB3			3
#define GPB4			4
#define GPB5			5
#define GPB6			6
#define GPB7			7


// �֐��̃v���g�^�C�v�錾
/*******************************************************************************
*	�N���X�̒�`                                                           *
*******************************************************************************/
class skMCP230
{
  private:
     int  device_adrs ;

     int  Send(char reg_adrs,unsigned char *data,char kosu) ;
     int  Receive(char reg_adrs,unsigned char *data,char kosu) ;

  public:
          skMCP230(int address) ;
     int  Init() ;
     void pinMode(int port,int pin,uint8_t mode) ;
     void Write(int port,int pin,int value) ;
     int  Read(int port,int pin) ;
     char ReadINTF(int port) ;
} ;

#endif