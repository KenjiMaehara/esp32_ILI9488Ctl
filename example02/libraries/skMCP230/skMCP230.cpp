/*******************************************************************************
*  skMCP230 - MCP23017(I2C)�֐����C�u����                                      *
*             ���̃f�o�C�X�́A16�`�����l���̔ėpI/O�Ɋg���o����IC�ł��B        *
*                                                                              *
*    skMCP230 - ���̊֐����C�u�����𐶐����鎞�̏���������                     *
*    Init     - �f�o�C�X�̏��������s������                                     *
*    pinMode  - �w��s���̓������͂��o�͂ɐݒ肷�鏈��                       *
*    Read     - �w�肵���s���̏�Ԃ𓾂鏈��                                   *
*    Write    - �w�肵���s���ɏo�͂��s������                                   *
*    ReadINTF - �w�肵���s���̊��荞�ݏ��(INTF)�𓾂鏈��                     *
*    Send     - �f�o�C�X�Ɏw����̃f�[�^�𑗐M���鏈��                       *
*    Receive  - �f�o�C�X����w����̃f�[�^����M���鏈��                     *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   1.00     2015-11-15  ���ޒ��H�[     Create                                 *
* ============================================================================ *
*   Arduino IDE 1.7.3 (Ardino Duemilanove 328/UNO ZERO/M0)                     *
*******************************************************************************/
#include <Wire.h>
#include "arduino.h"
#include "skMCP230.h"


/*******************************************************************************
*  skMCP230(address)                                                           *
*    ���̊֐����C�u�����𐶐����鎞�̏���������(�R���X�g���N�^)                *
*    address : �f�o�C�X(�X���[�u)��I2C�A�h���X���w�肵�܂�                     *
*******************************************************************************/
skMCP230::skMCP230(int address)
{
     device_adrs = address ;
}
/*******************************************************************************
*  ans = Init()                                                                *
*    �f�o�C�X�̏��������s������                                                *
*    �f�o�C�X�̃s������"skMCP230.h"�ɋL�q���܂��B                            *
*    ans  : �߂�l�A0=����I���@����ȊOI2C�ʐM�G���[���L                      *
*                   1=���낤�Ƃ����f�[�^�����M�o�b�t�@�̃T�C�Y�𒴂���         *
*                   2=�X���[�u�E�A�h���X�𑗐M���ANACK����M����               *
*                   3=�f�[�^�E�o�C�g�𑗐M���ANACK����M����                   *
*                   4=���̑��̃G���[                                           *
*                   5=�f�[�^��M�G���[                                         *
*******************************************************************************/
int skMCP230::Init()
{
     int  ans ;
     unsigned char data[10] ;

     // I/O�R���t�B�O���[�V�������s��
     data[0] = IOCON ;
     ans = Send(IOCON_ADRS,data,1) ;
     if (ans == 0) {
          // �f�o�C�X�̃s������ݒ肷��
          data[0] = IODIRA ;       // GPA0-GPA7�s����I/O�������W�X�^�l
          data[1] = IODIRB ;       // GPB0-GPB7�s����I/O�������W�X�^�l
          data[2] = IPOLA ;        // GPA0-GPA7�s���̓��͋ɐ��|�[�g���W�X�^�l
          data[3] = IPOLB ;        // GPB0-GPB7�s���̓��͋ɐ��|�[�g���W�X�^�l
          // �s���̊��荞�ݏ���ݒ肷��
          data[4] = GPINTENA ;     // GPA0-GPA7�s���̏�ԕω������݋����W�X�^�l
          data[5] = GPINTENB ;     // GPB0-GPB7�s���̏�ԕω������݋����W�X�^�l
          data[6] = DEFVALA ;      // GPA0-GPA7�s���̕ω�������r���W�X�^�l
          data[7] = DEFVALB ;      // GPB0-GPB7�s���̕ω�������r���W�X�^�l
          data[8] = INTCONA ;      // GPA0-GPA7�s���̏�ԕω������ݐ��䃌�W�X�^�l
          data[9] = INTCONB ;      // GPB0-GPB7�s���̏�ԕω������ݐ��䃌�W�X�^�l
          Send(IODIRA_ADRS,data,10) ;
          data[0] = GPPUA ;        // GPA0-GPA7�s���̃v���A�b�v���W�X�^�l
          data[1] = GPPUB ;        // GPB0-GPB7�s���̃v���A�b�v���W�X�^�l
          Send(GPPUA_ADRS,data,2) ;
          // �f�o�C�X��I/O�ɓ��o�͖�킸�O���o�͂��Ēu��
          data[0] = data[1] = 0 ;
          Send(OLATA_ADRS,data,2) ;
          // ��ԕω������݂��N���A���Ēu��
          while(1) {
               Receive(INTFA_ADRS,data,2) ;
               if (data[0]==0 && data[1]==0) break ;
               Receive(INTCAPA_ADRS,data,2) ;
          }
     }

     return ans ;
}
/*******************************************************************************
*  ans = Send(reg_adrs,*data,kosu)                                             *
*  �f�o�C�X�Ɏw����̃f�[�^�𑗐M���鏈��                                    *
*    reg_adrs : ���o���f�[�^�̃��W�X�^�A�h���X���w�肷��                       *
*               �A���I�ɏ��o���ꍇ�́A���o�����W�X�^�̐擪�A�h���X���w��       *
*    *data    : ���o���f�[�^�̊i�[����w�肷��                                 *
*    kosu     : ���o���f�[�^�̃o�C�g�����w�肷��                               *
*    ans      : �߂�l�A0=����I���@����ȊO Init() ��ans�l���Q��              *
*******************************************************************************/
int skMCP230::Send(char reg_adrs,unsigned char *data,char kosu)
{
     int  ans , i ;

     Wire.beginTransmission(device_adrs) ;        // �ʐM�̊J�n
     Wire.write(reg_adrs) ;                       // ���W�X�^�̃A�h���X��ʒm
     for (i=0 ; i<kosu ; i++) {
          Wire.write(*data) ;                     // �f�[�^��ʒm
          data++ ;
     }
     ans = Wire.endTransmission() ;               // �f�[�^�̑��M�ƒʐM�̏I��
     return ans ;
}
/*******************************************************************************
*  ans = Receive(reg_adrs,*data,kosu)                                          *
*  �f�o�C�X����w����̃f�[�^����M���鏈��                                  *
*    reg_adrs : �Ǐo���f�[�^�̃��W�X�^�A�h���X���w�肷��                       *
*               �A���I�ɓǏo���ꍇ�́A�Ǐo�����W�X�^�̐擪�A�h���X���w��       *
*    *data    : �Ǐo�����f�[�^�̊i�[����w�肷��                               *
*    kosu     : �Ǐo���f�[�^�̃o�C�g�����w�肷��                               *
*    ans      : 0=����@1=�ُ�(���肩��ACK���Ԃ��Ă��Ȃ�)                      *
*    ans      : �߂�l�A0=����I���@����ȊO Init() ��ans�l���Q��              *
*******************************************************************************/
int skMCP230::Receive(char reg_adrs,unsigned char *data,char kosu)
{
     int  ans , i ;

     Wire.beginTransmission(device_adrs) ;             // �ʐM�̊J�n
     Wire.write(reg_adrs) ;                            // ���W�X�^�A�h���X���w��
     ans = Wire.endTransmission() ;                    // �f�[�^�̑��M�ƒʐM�̏I��
     if (ans == 0) {
          ans = Wire.requestFrom(device_adrs,kosu) ;   // �f�[�^�̎�M���s��
          if (ans == kosu) {
               for (i=0 ; i<kosu ; i++) {
                    *data = Wire.read() ;
                    data++ ;
               }
               ans = 0 ;
          } else ans = 5 ;                             // ��M�o�C�g�������������H
     }
     return ans ;
}
/*******************************************************************************
*  pinMode(port,pin,mode)                                                      *
*  �w��s���̓������͂��o�͂ɐݒ肷�鏈��                                    *
*    port  : �|�[�g���w�肷��  0=GPA  1=GPB                                    *
*    pin   : �s���̃r�b�g�̈ʒu�A�E�[(LSB)���琔���ĉ��r�b�g�ڂ�               *
*    mode  : ���샂�[�h���w�� INPUT/OUTPUT/INPUT_PULLUP                        *
*******************************************************************************/
void skMCP230::pinMode(int port,int pin,uint8_t mode)
{
     unsigned char dt[4] ;
     int x1 , x2 , a1 , a2 ;

     if (port == 0) {
          // GPA�|�[�g�ւ̃A�N�Z�X
          a1 = IODIRA_ADRS ;
          a2 = GPPUA_ADRS ;
     } else {
          // GPB�|�[�g�ւ̃A�N�Z�X
          a1 = IODIRB_ADRS ;
          a2 = GPPUB_ADRS ;
     }
     Receive(a1,&dt[1],1) ;        // �����I/O�������W�X�^��ǂݏo��
     x1 = dt[1] ;
     Receive(a2,&dt[2],1) ;        // ����̃v���A�b�v���W�X�^��ǂݏo��
     x2 = dt[2] ;
     x2 &= ~(1 << pin) ;           // ��U�v���A�b�v�����ŃZ�b�g
     if (mode == OUTPUT) {
          // �o�̓��[�h�̐ݒ���s��
          x1 &= ~(1 << pin) ;      // �w��s���̓r�b�g0(output)
     } else {
          // ���̓��[�h�̐ݒ���s��
          x1 |= (1 << pin) ;       // �w��s���̓r�b�g1(input)
          if (mode == INPUT_PULLUP) {
               // �v���A�b�v�͗L���ɐݒ���s��
               x2 |= (1 << pin) ;
          }
     }
     dt[1] = x1 ;
     Send(a1,&dt[1],1) ;           // I/O�������W�X�^�ɏ�������
     dt[2] = x2 ;
     Send(a2,&dt[2],1) ;           // �v���A�b�v���W�X�^�ɏ�������
}
/*******************************************************************************
*  Write(port,pin,value)                                                       *
*  �w�肵���s���ɏo�͂��s������                                                *
*    port  : �|�[�g���w�肷��  0=GPA  1=GPB                                    *
*    pin   : �Z�b�g����r�b�g�̈ʒu�A�E�[(LSB)���琔���ĉ��r�b�g�ڂ�           *
*    value : �Z�b�g����ΏۂƂȂ鐔�l�A�Oor�P                                  *
*******************************************************************************/
void skMCP230::Write(int port,int pin,int value)
{
     unsigned char dt[2] ;
     int x , a1 , a2 ;

     if (port == 0) {
          // GPA�|�[�g�ւ̃A�N�Z�X
          a1 = GPIOA_ADRS ;
          a2 = OLATA_ADRS ;
     } else {
          // GPB�|�[�g�ւ̃A�N�Z�X
          a1 = GPIOB_ADRS ;
          a2 = OLATB_ADRS ;
     }
     Receive(a1,dt,1) ;                 // �����ǂݏo��
     x = dt[0] ;
     if (value == 1) x |= (1 << pin) ;  // �r�b�g���P�ɂ���
     else            x &= ~(1 << pin) ; // �r�b�g���O�ɂ���
     dt[0] = x ;
     Send(a2,dt,1) ;                    // GPA�|�[�g�ɏ�������
}
/*******************************************************************************
*  ans = Read(port,pin)                                                        *
*  �w�肵���s���̏�Ԃ𓾂鏈��                                                *
*    port  : �|�[�g���w�肷��  0=GPA  1=GPB                                    *
*    pin   : �ǂݎ��r�b�g�̈ʒu�A�E�[(LSB)���琔���ĉ��r�b�g�ڂ�             *
*    ans   : �Ԃ��l�͓ǂݎ�����r�b�g�l �O���P                                 *
*******************************************************************************/
int skMCP230::Read(int port,int pin)
{
     unsigned char dt[2] ;
     int x , a1 ;

     if (port == 0) {
          // GPA�|�[�g����ǂݍ���
          a1 = GPIOA_ADRS ;
     } else {
          // GPB�|�[�g����ǂݍ���
          a1 = GPIOB_ADRS ;
     }
     Receive(a1,dt,1) ;
     x = dt[0] ;
     return (x >> pin) & 0x01 ;
}
/*******************************************************************************
*  ans = ReadINTF(port)                                                        *
*  �w�肵���|�[�g�̊��荞�ݏ��(INTF)�𓾂鏈��                                *
*    port  : �|�[�g���w�肷��  0=GPA  1=GPB                                    *
*    ans   : �Ԃ��l��INTF���W�X�^�̒l                                          *
*******************************************************************************/
char skMCP230::ReadINTF(int port)
{
     unsigned char dt[2] ;
     int a1 , a2 ;

     if (port == 0) {
          // GPA���荞�݃t���O����ǂݍ���
          a1 = INTFA_ADRS ;
          a2 = INTCAPA_ADRS ;
     } else {
          // GPB���荞�݃t���O����ǂݍ���
          a1 = INTFB_ADRS ;
          a2 = INTCAPB_ADRS ;
     }
     Receive(a1,&dt[0],1) ;   // INTF���W�X�^��Ǎ���
     Receive(a2,&dt[1],1) ;   // INTCAP���W�X�^��Ǎ���(�����݂̃N���A)

     return dt[0] ;
}