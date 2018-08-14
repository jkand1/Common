
#ifndef DEF_8583_H
#define DEF_8583_H

#define ICBC_LOAD_TXN           "86510"
#define ICBC_LOAD_REVERSE_TXN   "86511"
#define ICBC_LOAD_QUREY_TXN      "86200"



#define IS_DIGIT(x)         (x >= '0' && x <= '9')
#define ICBC_TERM_NO        "77777777"
#define ICBC_MERCHNT_NO     "888888888888888"
/*==========================================*
 *           D E F I N I T I O N S          *
 *==========================================*/
#define ISO8583type_Cnst 0x00 /* type Const                  */
#define ISO8583type_Var  0x08 /* type Variable - 99/999      */
#define ISO8583type_BIN  0x10 /* type Binary - 'b','h'       */
#define ISO8583type_ASC  0x20 /* type ASCII  - 'a','an','ans'*/
#define ISO8583type_BCD  0x40 /* type BCD    - 'n','z'       */

#define ISO8583BufLen     1024 /* number of bytes for a message */
#define MAX_COMBUF_SIZE   1024
#define N_MAX_FLD         131 
#define FALSE   0
#define TRUE    1
/*function return code*/
#define BANK_CCBOIL       3  /* CCB oil card*/
#define BANK_REDONE       2  /*re-do it success*/
#define BANK_CONNECT      1  /*connection built*/
#define BANK_OK           0  /*success*/
#define BANK_ABORT       -1  /*user break*/
#define BANK_TIMEOUT     -2  /*timeout reached*/
#define BANK_FAIL        -3  /*operation failed*/
#define BANK_DB_FOUND    -4  /*record found in database*/
#define BANK_DB_NOTFOUND -5  /*record not found in database*/
#define BANK_DB_FAIL     -6  /*database operation failed*/
#define BANK_DB_EMPTY    -7  /*empty file*/
#define BANK_DB_NOFILE   -8  /*no such file exist*/
#define BANK_NOCONNECT   -9  /*making connection failed*/
#define BANK_PACKERROR   -10 /*pack frame error*/
#define BANK_SENDERROR   -11 /*send frame error*/
#define BANK_COMMERROR   -12 /*recvive data or unpack error, DO REVERSAL LATER*/
#define BANK_MACERROR    -13 /*communication MAC field error*/
#define BANK_UNPACKERROR -14 /*unpack frame error*/
#define BANK_HOSTERROR -15 /*host error*/
#define BANK_CONTINUEDIAL  -16 /*host error*/
#define BANK_CONFIG           -17  /*need to logon */

/*==========================================*
 *       P R I V A T E  T Y P E S           *
 *==========================================*/
typedef short                   INT16;
typedef unsigned short          UINT16;
typedef char                    INT8;
typedef unsigned char           byte;
typedef int                     INT32;
typedef unsigned int            UINT32;
typedef long                    INT64;






/*--------------------------------------------------------------
 * TYPE   .....................................fld_descr
 * DESCR. ....................field descriptor structure
 *-------------------------------------------------------------*/
typedef struct
{
  byte  type; /* (Cnst or Var) | (BIN or ASC or BCD) */
  UINT16 size; /* length of the field (1-999) */
}fld_descr;


/*--------------------------------------------------------------
 * TYPE   .....................................frame_str
 * DESCR. ....................application frame structure
 *-------------------------------------------------------------*/
typedef struct
{
	byte  nLen[2];
  byte  TPDU[5];    /* '60' + Dest ID + Orig ID */
  byte  HeadBuf[6];      /* 6 bytes 12 digits in BCD format*/
  byte  msgID[2];      /* 2 bytes - 4 digits in BCD format */
  byte  bitmap[8];  /* 64 bits, i.e. 8 bytes, i.e. 2 longs */
  byte  heap[ISO8583BufLen];   /*rest of a frame,b1-b128*/
}frame_str;

typedef struct
{
  byte  msgID[2];         /* 2 bytes - 4 digits in BCD format */
  byte  procCode[3];   /* 3 byte of processing code */
  byte  Condition;       /* user extended code,ISO8583 not use it */
  byte  mask[16];       /* 4 * 8 = 128 bits */
} msgtype_str;

typedef enum
{
	BTYPE_INITIALIZATION  = 0,        /*INITIALIZATION*/
	ICBC_LOAD,                        /*ICBC_LOAD*/
	ICBC_LOAD_REVERSE,                /*ICBC_LOAD_REVERSE*/
	ICBC_LOAD_QUREY,                  /*ICBC_LOAD_QUREY*/
	
	BTYPE_MAX_TRANTYPE ,              /*MAX TRAN TYPE */
}Bank_TranType;


typedef struct
{
  char txcode[5+1];/*交易代码---公司与工行公用*/
  char cityno[4+1];/*城市代码---公司与工行公用*/
  char cmpdate[8+1];/*公司发起交易日期*/
  char cmptime[6+1];/*公司发起交易时间*/
  char txdate[8+1]; /*工行发起交易日期*/
  char txtime[6+1]; /*工行发起交易时间*/
  char cmptxsno[20+1];/*公司发起交易带入的公司流水号*/
  char settledate[8+1];/*结算日期----公司与工行公用*/
  char icbctxsno[8+1];/*工行发起交易时的流水号*/
  char retcode[5+1];/*返回代码---公司与工行公用*/
  char retmsg[100+1];/*返回信息---公司与工行公用*/
}DataPubDef;

typedef struct
{
  char czcardnoflg[1+1];
  char czcardno[40+1];/*充值卡卡号*/
  char czcardpwdflg[1+1];
  char czcardpwd[128+1];/*充值卡密码*/
  char acctnoflg[1+1];
  char acctno[40+1]; /*工行卡号*/
  char amountflg[1+1];
  char amount[16+1];/*充值金额*/
  char icbcotxsnoflg[1+1];
  char icbcotxsno[20+1];/*原工行流水号,应该是8位，文档上20位*/
  char icbctxsnoflg[1+1];
  char icbctxsno[9+1];/*工行流水号,工行应答返回*/
  char balanceflg[1+1];
  char balance[16+1];/*充值卡余额*/
  char depositquotaflg[1+1];
  char depositquota[16+1];/*单笔充值上线*/
  char feerateflg[1+1];
  char feerate[16+1];/*充值卡费率*/
  char cmptxsnoflg[1+1];
  char cmptxsno[20+1];/*商盟流水号,作为响应工行请求交易的返回*/
  char resultflg[1+1];
  char result[2+1];/*交易结果*/
}DataPrivDef;

typedef struct
{
	DataPubDef  straPubInf;
	DataPrivDef straPrivInf;
}ComDataDef;


void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);
void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen);
int nBcd2Num( void *vvpSrcBuf, unsigned short* vvpDesBuf,int nSrcBufLen);
int nNum2Bcd( UINT16 vvpSrcBuf, void* vvpDesBuf, UINT16 nSrcBufLen);
void GetBitFld(void *dest, void *src);
void vBcd2Asc( unsigned char *vspAscStr, unsigned char* vspBcdStr, int vnConLen, unsigned char *vspType );
void vAsc2Bcd( unsigned char *vspBcdStr, unsigned char* vspAscStr, int vnConLen, unsigned char* vspType );
int CvtBitMapMd(void *dest, void *src);
void GetCurrentTime(char *sCurrentTime);

/*debug*/
#define SET_COM_DATA(x) \
memcpy(x->straPubInf.txcode,"86510", 5); \
memcpy(x->straPubInf.cityno,"1202", 4); \
memcpy(x->straPubInf.cmpdate,"11111111", 8); \
memcpy(x->straPubInf.cmptime,"222222", 6); \
memcpy(x->straPubInf.txdate,"33333333", 8); \
memcpy(x->straPubInf.txtime,"444444", 6); \
memcpy(x->straPubInf.cmptxsno,"55555555", 8); \
memcpy(x->straPubInf.settledate,"66666666", 8); \
memcpy(x->straPubInf.icbctxsno,"77777777", 8); \
memcpy(x->straPubInf.retcode,"88888", 5); \
memcpy(x->straPubInf.retmsg,"99999999", 8); \
memcpy(x->straPrivInf.czcardno,"1234567890123456789",19 ); \
memcpy(x->straPrivInf.czcardpwd,"123456789012345678901234",24 ); \
memcpy(x->straPrivInf.acctno,"2020202020202020202020202020202020202020",40 ); \
memcpy(x->straPrivInf.amount,"999998888881",12 ); \
memcpy(x->straPrivInf.icbcotxsno,"123456789012345678901234",20 ); \
memcpy(x->straPrivInf.icbctxsno,"88930200",8 ); \
memcpy(x->straPrivInf.balance,"2222255343332222",16 ); \
memcpy(x->straPrivInf.depositquota,"8787878878788787",16 ); \
memcpy(x->straPrivInf.feerate,"5656565665656565",16 ); \
memcpy(x->straPrivInf.cmptxsno,"34343434343343443434",20 ); \
memcpy(x->straPrivInf.result,"A0",2 ); \
x->straPrivInf.czcardnoflg[0]='Y'; \
x->straPrivInf.czcardpwdflg[0]='Y'; \
x->straPrivInf.acctnoflg[0]='Y'; \
x->straPrivInf.amountflg[0]='Y'; \
x->straPrivInf.icbcotxsnoflg[0]='Y'; \
x->straPrivInf.icbctxsnoflg[0]='Y'; \
x->straPrivInf.balanceflg[0]='Y'; \
x->straPrivInf.depositquotaflg[0]='Y'; \
x->straPrivInf.feerateflg[0]='Y'; \
x->straPrivInf.cmptxsnoflg[0]='Y'; \
x->straPrivInf.resultflg[0]='Y'

#endif