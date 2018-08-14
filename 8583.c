#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "8583.h"


#define STR_CONVERT_2_DIG( type_def )   \
    register type_def  i;  \
    register INT16  nLen; \
    unsigned char   *spAsc; \
    \
    i = 0; \
    spAsc = (unsigned char *)vvAsc; \
    nLen = vnLen; \
    while (nLen > 0) { \
        if (IS_DIGIT(*spAsc)) { \
            i = i*10 + *spAsc - '0'; \
        } \
/*        else if(*spAsc == 0x20) { \
            if (i > 0) break; \
        } \
*/        else { \
            return BANK_FAIL; \
        } \
        nLen--; \
        spAsc++; \
    } \
    *vvVal = i; \
    return BANK_OK

#define DIG_CONVERT_2_STR(type_def) \
    register type_def  val; \
    register UINT16  nLen; \
    unsigned char   *spAsc; \
     \
    spAsc = (unsigned char *)vvAsc; \
    val = vvVal; \
    nLen = vnLen; \
     \
    memset(spAsc, 0, sizeof(nLen)); \
    spAsc += nLen-1; \
       \
    while (nLen-- > 0) { \
        *spAsc--  =  val%10 + '0'; \
        val /= 10; \
    } \
    if (val > 0) \
        return BANK_FAIL; \
    return BANK_OK 

const fld_descr fd_list[128] =
{   {ISO8583type_BIN,                   64}, /*  1 Additional bitmap for 65-128*/
    {ISO8583type_BCD | ISO8583type_Var, 20}, /*  2 AccNo*/
    {ISO8583type_BCD,                    6}, /*  3 ProcCode*/
    {ISO8583type_BCD,                   12}, /*  4 Amount*/
    {ISO8583type_BCD,                   12}, /*  5 Amount settlement*/
    {ISO8583type_BCD,                   12}, /*  6 Amount billing*/
    {ISO8583type_BCD,                   10}, /*  7 date&time mmddhhmmss */
    {ISO8583type_BCD,                    8}, /*  8 fee Amount  */
    {ISO8583type_BCD,                    8}, /*  9 Amount  rate settle*/
    {ISO8583type_BCD,                    8}, /* 10 Amount  rate*/
    {ISO8583type_BCD,                    6}, /* 11 SysTrace*/
    {ISO8583type_BCD,                    6}, /* 12 Time    */
    {ISO8583type_BCD,                    6}, /* 13 Date    */
    {ISO8583type_BCD,                    4}, /* 14 ExpDate */
    {ISO8583type_BCD,                    4}, /* 15 Settlement date */
    {ISO8583type_BCD,                    4}, /* 16 Date */
    {ISO8583type_BCD,                    4}, /* 17 Date */
    {ISO8583type_BCD,                    4}, /* 18 Merchant Type */
    {ISO8583type_BCD,                    3}, /* 19 Acquiring Country Code */
    {ISO8583type_BCD,                    3}, /* 20 Pan country code */
    {ISO8583type_BCD,                    3}, /* 21 Forwarding Country code */
    {ISO8583type_BCD,                    3}, /* 22 POSentry*/
    {ISO8583type_BCD,                    3}, /* 23 Application Pan */
    {ISO8583type_BCD,                    3}, /* 24 NII     */
    {ISO8583type_BCD,                    2}, /* 25 POScond */
    {ISO8583type_BCD,                    2}, /* 26 POScond */
    {ISO8583type_BCD,                    1}, /* 27 Response len */
    {ISO8583type_BCD,                    8}, /* 28 Fee amount */
    {ISO8583type_BCD,                    8}, /* 29 Settlement fee amount */
    {ISO8583type_BCD,                    8}, /* 30 trans Processing Fee Amount */
    {ISO8583type_BCD,                    8}, /* 31 Settle Processing Fee Amount */
    {ISO8583type_BCD | ISO8583type_Var, 11}, /* 32 Acquiring ID */
    {ISO8583type_BCD | ISO8583type_Var, 11}, /* 33 Forwarding ID */
    {ISO8583type_BCD | ISO8583type_Var, 28}, /* 34 Account Num extended */
    {ISO8583type_BCD | ISO8583type_Var, 37}, /* 35 Track2  */
    {ISO8583type_BCD | ISO8583type_Var, 104}, /* 36 Track3 */
    {ISO8583type_ASC,                   12}, /* 37 RetRefNo*/
    {ISO8583type_ASC,                    6}, /* 38 AuthID  */
    {ISO8583type_ASC,                    2}, /* 39 Response*/
    {ISO8583type_ASC,                    3}, /* 40 Service Code */
    {ISO8583type_ASC,                    8}, /* 41 TID     */
    {ISO8583type_ASC,                   15}, /* 42 CAccID  */
    {ISO8583type_ASC,                   40}, /* 43 CAccName*/
    {ISO8583type_ASC | ISO8583type_Var, 25}, /* 44 AddResp */
    {ISO8583type_ASC | ISO8583type_Var, 76}, /* 45 Track1  */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 46 Additional Data  */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 47 Additional Data  */
    {ISO8583type_BCD | ISO8583type_Var, 999}, /* 48 Additional Data  */
    {ISO8583type_ASC,                    3}, /* 49 Currency Code  Transaction */
    {ISO8583type_ASC,                    3}, /* 50 Currency Code  Settlement  */
    {ISO8583type_ASC,                    3}, /* 51 Currency Code  billing     */
    {ISO8583type_BIN,                   64}, /* 52 PINData */
    {ISO8583type_BCD,                   16}, /* 53 Security Data */
    {ISO8583type_ASC | ISO8583type_Var, 120}, /* 54 AddAmnts */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 55 ICC info */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 56 Reserved */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 57 Reserved */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 58 Reserved */
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 59 Reserved */
    {ISO8583type_BCD | ISO8583type_Var, 999}, /* 60 Reserved*/
    {ISO8583type_BCD | ISO8583type_Var, 999}, /* 61 Reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 62 Reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /* 63 Reserved*/
    {ISO8583type_BIN,                   64}, /* 64 MAC data*/
    {ISO8583type_BIN,                   64}, /* 65 bitmap for 129-192*/
    {ISO8583type_BCD,                    1}, /* 66 Settlement code */
    {ISO8583type_BCD,                    2}, /* 67 extend payment code*/
    {ISO8583type_BCD,                    3}, /* 68 receiving country code*/
    {ISO8583type_BCD,                    3}, /* 69 settlement contry code*/
    {ISO8583type_BCD,                    3}, /* 70 network info code*/
    {ISO8583type_BCD,                    4}, /* 71 message number*/
    {ISO8583type_BCD,                    4}, /* 72 message number,last */
    {ISO8583type_BCD,                    6}, /* 73 date, action*/
    {ISO8583type_BCD,                   10}, /* 74 credit number*/
    {ISO8583type_BCD,                   10}, /* 75 credit reversal number*/
    {ISO8583type_BCD,                   10}, /* 76 debit number*/
    {ISO8583type_BCD,                   10}, /* 77 reversal debit number*/
    {ISO8583type_BCD,                   10}, /* 78 transfer number*/
    {ISO8583type_BCD,                   10}, /* 79 reversal transfer number*/
    {ISO8583type_BCD,                   10}, /* 80 inquiry number*/
    {ISO8583type_BCD,                   10}, /* 81 authorization number*/
    {ISO8583type_BCD,                   12}, /* 82 credit process fee amount*/
    {ISO8583type_BCD,                   12}, /* 83 credit tran fee amount*/
    {ISO8583type_BCD,                   12}, /* 84 debit process fee amount*/
    {ISO8583type_BCD,                   12}, /* 85 debit tran fee amount */
    {ISO8583type_BCD,                   15}, /* 86 credit amount*/
    {ISO8583type_BCD,                   15}, /* 87 credit reversal amount*/
    {ISO8583type_BCD,                   15}, /* 88 debit amount*/
    {ISO8583type_BCD,                   15}, /* 89 debit reversal amount*/
    {ISO8583type_BCD,                   42}, /* 90 original data elements*/
    {ISO8583type_ASC,                    1}, /* 91 file update code*/
    {ISO8583type_BCD,                    2}, /* 92 file security code*/
    {ISO8583type_BCD,                    5}, /* 93 response indicator*/
    {ISO8583type_ASC,                    7}, /* 94 service indicator*/
    {ISO8583type_ASC,                   42}, /* 95 replacement amount*/
    {ISO8583type_ASC,                    8}, /* 96 message security code*/
    {ISO8583type_BCD,                   16}, /* 97 amount, net settlement*/
    {ISO8583type_ASC,                   25}, /* 98 payee*/
    {ISO8583type_BCD | ISO8583type_Var, 11}, /* 99 settlement id code*/
    {ISO8583type_BCD | ISO8583type_Var, 11}, /*100 receiving id code*/
    {ISO8583type_ASC,                   17}, /*101 file name*/
    {ISO8583type_ASC | ISO8583type_Var, 28}, /*102 account identification 1*/
    {ISO8583type_ASC | ISO8583type_Var, 28}, /*103 account identification 2*/
    {ISO8583type_ASC | ISO8583type_Var, 100}, /*104 trans description*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*105 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*106 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*107 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*108 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*109 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*110 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*111 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*112 reserved*/
    {ISO8583type_BCD | ISO8583type_Var, 11}, /*113 authorising agent code*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*114 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*115 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*116 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*117 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*118 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*119 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*120 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*121 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*122 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*123 reserved*/
    {ISO8583type_ASC | ISO8583type_Var, 255}, /*124 info text*/
    {ISO8583type_ASC | ISO8583type_Var, 100}, /*125 network management info*/
    {ISO8583type_ASC | ISO8583type_Var, 100}, /*126 issuer trace id*/
    {ISO8583type_ASC | ISO8583type_Var, 999}, /*127 reserved*/
    {ISO8583type_BIN,                   64}  /*128 MAC data*/
};

const msgtype_str msg[BTYPE_MAX_TRANTYPE] =
{
  {{0x08,0x00}, {0x95, 0x00, 0x00}, 0x03, {0x20,0x20,0x01,0x80,0x00,0x80,0x00,0x00}}, /*INITIALIZATION*/
  {{0x02,0x00}, {0x00, 0x00, 0x00}, 0x00, {0x70,0x02,0x00,0xC0,0x00,0xC0,0x98,0x14}}, /*ICBC_LOAD*/
  {{0x02,0x00}, {0x20, 0x00, 0x00}, 0x00, {0x70,0x02,0x00,0xC0,0x00,0xC0,0x98,0x1C}}, /*ICBC_LOAD_REVERSE*/
  {{0x05,0x00}, {0x31, 0x00, 0x08}, 0x00, {0x70,0x02,0x04,0xC0,0x00,0xC0,0x98,0x14}}, /*ICBC_LOAD_QUREY*/
};



static frame_str frameS, frameR;


/*--------------------------------------------------------------------------
 FUNCTION NAME: ISO8583_AddFld.
 DESCRIPTION:   converts to appropriate format and fills field in the frame
                from the current position.
 PARAMETER:     frPtr   - frame pointer,
                RemLen  - frmae remained buffer(left),
                data    - data to be packed,
                bit     - 1-128,
                fleLen  - data length(only used for Var format field.)
 RETURN:        real length of bytes having been packed in frame.
 NOTE:          for BCD field, parent function should make it in BCD buffer,
                fldLen is the size of ASCII size(not bcd bytes).
 *------------------------------------------------------------------------ */
INT32 ISO8583_AddFld(byte *frPtr, UINT16 RemLen,
                    byte *data, INT32 bit, UINT16 fldLen)
{
 INT32  fSize, hSize=0, i;
 INT32  fIndx = bit-1;
 byte  bcdhead[4]={0};

  /*get real field size(ASCII)*/
  if(fd_list[fIndx].type & ISO8583type_Var)
  {
    i = fldLen;

    if(fldLen > fd_list[fIndx].size)  return BANK_PACKERROR;
    /*get head BCD length*/
    else if(fd_list[fIndx].size<=99)
    {
      hSize = 1;
      nNum2Bcd( fldLen, bcdhead, 1);
    }
    else if((fd_list[fIndx].size>99) && (fd_list[fIndx].size<=999))
    {
      hSize = 2;
      nNum2Bcd( fldLen, bcdhead, 2);
      /*BankUtil_Len2Bcd(fldLen, bcdhead, 2);*/
    }
    else return BANK_PACKERROR;

    if(RemLen < hSize)  return BANK_PACKERROR;
    memcpy(frPtr, bcdhead, hSize);
    frPtr += hSize;
  }
  else  i = fd_list[fIndx].size;

  /*bytes size*/
  if(fd_list[fIndx].type & ISO8583type_BCD)
    fSize = i / 2 + ((i%2)?1:0);
  else if(fd_list[fIndx].type & ISO8583type_BIN)
    fSize = i / 8;
  else fSize = i; /*ASCII*/

  if(RemLen < fSize+hSize)  return BANK_PACKERROR;

  /*copy data to buffer*/
  memcpy(frPtr, data, fSize);

  return fSize+hSize; /*head + data (size of bytes)*/
}


/*-------------------------------------------------------------------------
 FUNCTION NAME: ISO8583_Pack.
 DESCRIPTION:   Build sending frame
 PARAMETER:     msgStr
                frmS   - buffer of packing frame;
 RETURN:        >= 0           - packed data length(TPDU to the last field)
                BANK_PACKERROR - pack frame error.
 NOTES:         none.
 *------------------------------------------------------------------------*/
INT32 ISO8583_Pack(const msgtype_str *msgStr,void *vvpDesBuf)
{
  byte    *frPtr;
  INT32     rv, i;
  UINT16    RemLen, fldLen, tLen;
  byte     tmp[ISO8583BufLen], tmp2[160];
  UINT32  Seg128Exist = FALSE;
  INT16   naOffset[N_MAX_FLD]={0};

  RemLen = ISO8583BufLen;
  
  ComDataDef *strpComData=(ComDataDef *)vvpDesBuf;
  
  /*TPDU*/
  HexStrToByte("6000060000602201000000", frameS.TPDU, 22);
  /*memcpy((char*)frameS.TPDU, "06000060000", 5);   '60' + Dest ID + Orig ID */

  /*Message ID*/
  memcpy((char*)&frameS.msgID,(char*)&msgStr->msgID,2);
  /*bitmap (1-64)*/
  memcpy(frameS.bitmap,msgStr->mask,8);

  frPtr = (byte*)frameS.heap;
  
  GetBitFld(&naOffset, frameS.bitmap);
  
  for (i = 1; i <= 128; i++)
  {
    if ((i > 64) && !Seg128Exist) /*no 65-128 field*/
      break;

    if ( naOffset[i] == -1 )
      continue;

    printf("i=%d\n",i);

    fldLen = 0;
    memset(tmp, 0, sizeof(tmp));
    memset(tmp2, 0, sizeof(tmp2));
    switch (i)
    {
      case   1: /*bitmap of 65-128*/
        memcpy(tmp, (byte*)&(msgStr->mask[2]), 8);
        Seg128Exist = TRUE;  /*next 64 fields exist*/
        break;
      case   2: /*primary account number*/
        fldLen = strlen(strpComData->straPrivInf.czcardno);
        vAsc2Bcd( tmp, (unsigned char*)strpComData->straPrivInf.czcardno, fldLen, 0 );
        break;
      case   3: /*Processing Code*/
        memcpy(tmp, (byte*)msgStr->procCode, 3);
        break;
      case   4: /*Tran amount*/
        vAsc2Bcd( tmp, (unsigned char*)strpComData->straPrivInf.amount, 12, 0 );
        break;
      case  11: /*SysTrace*/
      	vAsc2Bcd( tmp, (unsigned char*)strpComData->straPrivInf.cmptxsno, 6, 0 );
        break;
      case  12: /*Time */
        vAsc2Bcd( tmp, (unsigned char*)strpComData->straPubInf.cmptime, 6, 0 );
        break;
      case  13: /*Date */
      	vAsc2Bcd( tmp, (unsigned char*)&strpComData->straPubInf.cmpdate[4], 4, 0 );
        break;
      case  14:/*ExpDate*/
        break;
      case  15:/*settle date*/
      	vAsc2Bcd( tmp, (unsigned char*)&strpComData->straPubInf.settledate[4], 4, 0 );
      	break;
      case  25: /* Condition Mode */
        tmp[0] = msgStr->Condition;
        break;
      case  26: /* Condition Mode */
        tmp[0] = 0x06;
        break;
      case  37: /*Retrefno  */
        memset(tmp, 0x30, 12);
        break;
      case  38: /*AuthID */
        memset(tmp, 0x30, 6); 
        break;
      case  39: /* Response */
        break;
      case  41: /*TID - POS ID*/
        memcpy(tmp, ICBC_TERM_NO, 8); 
        break;
      case  42: /*CAccID - Merchant ID */ 
        memcpy(tmp, ICBC_MERCHNT_NO, 15);
        break;
      case  49:
        strcpy((char*)tmp, "156");
        break;
      case  52:
        vAsc2Bcd( tmp, (unsigned char*)strpComData->straPrivInf.czcardpwd, 16, 0 );
        break;
      case  53: /*PINData */
        HexStrToByte( "1100000000000000", tmp, 16);
        break;
      case  60: /*reserved */
        {
        	fldLen=11;
        	if(0==memcmp( strpComData->straPubInf.txcode, ICBC_LOAD_TXN, 5))      /*充值*/
			    strcpy((char*)tmp2,"22000137000");
        	else if(0==memcmp( strpComData->straPubInf.txcode, ICBC_LOAD_REVERSE_TXN, 5))/*充值撤销*/
			    strcpy((char*)tmp2,"23000137000");
        	else if(0==memcmp( strpComData->straPubInf.txcode, ICBC_LOAD_QUREY_TXN, 5))/*查询*/
			    strcpy((char*)tmp2,"01000137000");
        	else
        		return BANK_PACKERROR;

			    vAsc2Bcd( tmp, tmp2, fldLen, 0 );
        }
        break;
      case  61: /*original Tran */
        {
        	fldLen=16;
        	sprintf((char *)tmp2,"000137%6.6s%4.4s",
        	        strpComData->straPrivInf.icbcotxsno,
        	        strpComData->straPubInf.txdate);
        	vAsc2Bcd( tmp, tmp2, fldLen, 0 );
        }
        break;
      case  62: /*reserved */
        {
        	fldLen=78;
        	memset(tmp2, 0x20, sizeof(tmp2));
        	sprintf((char*)tmp2,"%-20.20s%-20.20s%-6.6s%012.12s%-20.20s",
	                strpComData->straPrivInf.acctno,
	                strpComData->straPrivInf.icbctxsno,
	                strpComData->straPrivInf.feerate,
	                strpComData->straPrivInf.depositquota,
	                strpComData->straPrivInf.icbcotxsno);
	        memcpy( tmp, tmp2, fldLen);
        }
        break;
      case  64: /*MAC data*/
        if (!Seg128Exist) /*call back to get MAC*/
        {
          tLen = (UINT16)(frPtr - (byte*) & (frameS.msgID));
          /*calc mac */
          /*if (rv == BANK_FAIL)   return BANK_PACKERROR*/
        }
        break;
      case 128: /*MAC data*/
        break;
      default:
        break;
    } /*switch(i)*/

    rv = ISO8583_AddFld(frPtr, RemLen, tmp, i, fldLen);
    if (rv > 0)
    {
      frPtr += rv;
      RemLen -= rv;
    }
    else if (rv < 0)
      return BANK_PACKERROR;
  } /*for(i=1;i<=128;i++)*/

  tLen = (UINT16)(frPtr - (byte*)frameS.TPDU);
  return tLen;
}


/*--------------------------------------------------------------------------
 FUNCTION NAME: ISO8583_GetFld.
 DESCRIPTION:   retrieve field from received frame according to field id.
 PARAMETER:     frPtr   - unpack frame current position,
                data    - unpacked data buffer,
                bit     - 1-128,
                RemLen  - remained bytes in frame buffer,
                HLen    - head bytes, 0 for const field,
                          1-'9'/2-'99'/3-'999' for var field,
                fldLen  - [in], buffer size,
                          [out], real field length.
 RETURN:        >=0       - real length of data bytes to be unpacked,
                BANK_FAIL - failed.
 NOTE:          for BCD field, returned fldLen contains real ASCII length,
                eg: 01 23 4F -> 30 31 32 33 34, fldlen = 5, func return 3.
                for Var format field, func return value exclude BCD LENGTH.
 *------------------------------------------------------------------------ */
INT32 ISO8583_GetFld(byte *frPtr, byte *data, INT32 bit, UINT16 RemLen,
                    UINT16 *HLen, UINT16 *fldLen)
{
  INT16  fSize;
  UINT16 hSize = 0, i;
  INT32  fIndx = bit - 1;
  byte  bcdhead[4];
  
  /*get real field size(ASCII),*/
  if (fd_list[fIndx].type & ISO8583type_Var)
  {
    memset(bcdhead, 0, sizeof(bcdhead));
    if (fd_list[fIndx].size <= 99)
    {
      bcdhead[1] = *frPtr;
      hSize = 1;
    }
    else if (fd_list[fIndx].size <= 999)
    {
      memcpy((byte*)bcdhead, frPtr, 2);
      hSize = 2;
    }
   
    if (BANK_OK!=nBcd2Num(bcdhead, &i, 2))
      return BANK_FAIL;  /*illegal char in compressed length section*/
      
    if (i > fd_list[fIndx].size)
      return BANK_FAIL;
  }
  else
  {
    i = fd_list[fIndx].size;
  }
  
  /*bytes size*/
  if (fd_list[fIndx].type & ISO8583type_BCD)
  {
    /*fSize = i / 2 + ((i%2)?1:0);*/
    fSize = (i + 1) / 2 ;
  }
  else if (fd_list[fIndx].type & ISO8583type_BIN)
  {
    fSize = i / 8;
  }
  else
  {
    fSize = i; /*ASCII*/
  }
  
  if (RemLen < fSize + hSize)
    return BANK_FAIL;
    
  frPtr += hSize;
  
  /*copy data to buffer*/
  memcpy(data, frPtr, fSize);
  *HLen = hSize;
  *fldLen = i;
  
  return fSize + hSize; /*head + data (size of bytes)*/
}

/*-------------------------------------------------------------------------
 FUNCTION NAME: ISO8583_UnPack
 DESCRIPTION:   unpack received ISO8583 frame.
                PackLen - received packlen(start from TPDU).
 RETURN:        BANK_OK       - unpack ok,
                BANK_FAIL     - it seems it's not a correct 8583 frame.
 NOTES:         none.
 *------------------------------------------------------------------------*/
INT32 ISO8583_UnPack(void *vvpDesBuf, UINT16 PackLen)
{
  byte    *frPtr;
  UINT32    mask[4], Value = 0;
  INT16     rv, i;
  UINT16    fldLen, HLen, RemLen;
  byte     tmp[ISO8583BufLen], tmp2[160];
  UINT32  Seg128Exist = FALSE;
  INT16   naOffset[N_MAX_FLD]={0};
  char    sCurrentTime[14+1]={0};
  
  ComDataDef *strpComData=(ComDataDef *)vvpDesBuf;
    
  GetBitFld(&naOffset, frameR.bitmap);
  GetCurrentTime(sCurrentTime);
  
  frPtr = (byte*)frameR.heap;
  RemLen = PackLen - 21; /*skip TPDU+HEADBUF+MSGID+BITMAP*/
  for (i = 1; i <= 128; i++)
  {
    if ((i > 64) && !Seg128Exist) /*no 65-128 field*/
      break;
            
    if ( naOffset[i] == -1 )
      continue;
      
      printf("i=%d\n",i);
      
    memset((byte*)tmp, 0, sizeof(tmp));
    memset((byte*)tmp2, 0, sizeof(tmp2));
    fldLen = ISO8583BufLen;
    HLen = 0;
    
    rv = ISO8583_GetFld(frPtr, tmp, i, RemLen, &HLen, &fldLen);
    
    if (rv == BANK_FAIL)
      return BANK_FAIL;
      
    frPtr += rv;
    RemLen -= rv;
    
    if (rv == 0)
      continue;
      
    switch (i)
    {
      case   1: /*bitmap of 65-128*/
        memcpy((byte*)&mask[2], tmp, 8);
        Seg128Exist = TRUE;  /*next 64 fields exist*/
        break;
      case   2: /*primary account number*/
      	vBcd2Asc( tmp2, tmp, fldLen, 0);
      	strpComData->straPrivInf.czcardnoflg[0]='Y';
      	memcpy(strpComData->straPrivInf.czcardno, tmp2, fldLen);
      	printf("field2:%s\n",tmp2);
      	printf("fldLen:%u\nczcardno:%s\n",fldLen,strpComData->straPrivInf.czcardno);
        break;
      case   3: /*process code */
        vBcd2Asc( tmp2, tmp, fldLen, 0);
        printf("process code:%s\n",tmp2);
        break;
      case   4: /*Tran amount*/
      	strpComData->straPrivInf.amountflg[0]='Y';
      	vBcd2Asc( (unsigned char*)strpComData->straPrivInf.amount, tmp, fldLen, 0);
      	printf("amount:%s\n",strpComData->straPrivInf.amount);
        break;
      case  11: /*SysTrace*/
      	vBcd2Asc((unsigned char*)strpComData->straPubInf.cmptxsno,tmp,fldLen,0);
      	printf("SysTrace:%s\n",strpComData->straPubInf.cmptxsno);
        break;
      case  12: /*Time */
      	vBcd2Asc((unsigned char*)strpComData->straPubInf.cmptime, tmp, fldLen, 0);
      	memcpy( strpComData->straPubInf.txtime, strpComData->straPubInf.cmptime, fldLen);
        printf("Time:%s\n",strpComData->straPubInf.cmptime);
        break;
      case  13: /*Date*/
      	memcpy(strpComData->straPubInf.cmpdate, sCurrentTime, 4);
      	vBcd2Asc((unsigned char*)strpComData->straPubInf.cmpdate[4], tmp, fldLen, 0);
      	memcpy(strpComData->straPubInf.txdate,strpComData->straPubInf.cmpdate,fldLen+4);
      	printf("Date :%s\n",strpComData->straPubInf.cmpdate);
        break;
      case  14: /*ExpDate*/ 
        break;
      case  15: /*settle time*/
      	memcpy(strpComData->straPubInf.settledate, sCurrentTime, 4);
      	vBcd2Asc((unsigned char*)&strpComData->straPubInf.settledate[4], tmp, fldLen, 0);
      	printf("settle time :%s\n",strpComData->straPubInf.settledate);
        break;
      case  25: /*Condition*/
      	printf("%02x\n",tmp[0]);
        break;
      case  26: /*Condition*/
      	printf("%02x\n",tmp[0]);
        break;
      case  32: /*ins*/
      	vBcd2Asc( tmp2, tmp, fldLen, 0);
      	printf("field32 is %.*s\n",fldLen,tmp2);
        break;
      case  37: /*RetRefNo*/
      	memcpy(strpComData->straPubInf.cmptxsno, tmp, fldLen);/*cmp*/
      	strpComData->straPrivInf.cmptxsnoflg[0]='Y';
      	memcpy(strpComData->straPrivInf.cmptxsno, tmp, fldLen);/*icbc*/
      	printf("field37 is %s\n",tmp);
        break;
      case  38: /*AuthID */ 
        break;
      case  39: /*Response*/
      	printf("Response :%2.2s\n",tmp);
        break;
      case  41:
        printf("term_id :%s\n",tmp);
        break;
      case  42:
        printf("Merchant_id :%s\n",tmp);
        break;
      case  49:
        printf("current_code :%s\n",tmp);
        break;
      case  53:
      	vBcd2Asc( tmp2, tmp, fldLen, 0 );
        printf("field53 :%s\n",tmp2);
        break;
      case 60:/*reserved private*/
      	vBcd2Asc( tmp2, tmp, fldLen, 0 );
        printf("fldLen:%u\nfld60:%s\n",fldLen,tmp2);
        break;
      case 61:/*original Message*/
        vBcd2Asc( tmp2, tmp, fldLen, 0 );
        printf("fldLen:%u\n fld61:%s\n",fldLen,tmp2);
        break;
      case 62:/*reserved private*/
      	memcpy(strpComData->straPrivInf.acctno,tmp,20);/*ICBC cardno*/
      	strpComData->straPrivInf.czcardnoflg[0]='Y';
      	sprintf(strpComData->straPubInf.icbctxsno,"%.8s",tmp+20);/*ICBC SysTrace*/
      	sprintf(strpComData->straPrivInf.icbctxsno,"%.8s",tmp+20);/*ICBC SysTrace*/
      	strpComData->straPrivInf.icbctxsnoflg[0]='Y';
      	sprintf(strpComData->straPrivInf.feerate,"%.6s",tmp+40);/*ICBC feerate*/
      	strpComData->straPrivInf.feerateflg[0]='Y';
      	sprintf(strpComData->straPrivInf.depositquota,"%.12s",tmp+46);/*ICBC feerate*/
      	strpComData->straPrivInf.depositquotaflg[0]='Y';
      	sprintf(strpComData->straPrivInf.icbcotxsno,"%.20s",tmp+58);/*ICBC original SysTrace*/
      	strpComData->straPrivInf.icbcotxsnoflg[0]='Y';
      	
      	printf("fldLen:%u\n fld62:%s\n",fldLen,tmp);
        break;
      case 63:/*reserved private*/
      	printf("fldLen:%u\n fld63:%s\n",fldLen,tmp);
        break;
      case  64: /*MAC data*/
        if (!Seg128Exist) /*call back to get MAC*/
        {
        	/*check MAC*/
        }
        break;
      case 128: /*MAC data*/
        break;
      default:/**/
        break;
    } /*switch(i)*/
  } /*for(i=1;i<=128;i++)*/
  
  return BANK_OK;
}

/*-------------------------------------------------------------------------
 FUNCTION NAME: GetBitFld
 DESCRIPTION:   get bitmap in or out bit
                dest: new buffer instead of bitmap
                src:  original bitmap
 RETURN:        none
 NOTES:         none.
 *------------------------------------------------------------------------*/
void GetBitFld(void *dest, void *src)
{
	register INT16 i,j;
	unsigned char *ptrSrc;
	unsigned char cBitMask;
	short *fld;
	
	fld=(short *)dest;
	ptrSrc=(unsigned char *)src;
		
	for (i = 0; i < 8; i++)
	{
      cBitMask = 0x80;
      for (j = 0; j < 8; j++, cBitMask>>= 1)
      {              
          if (ptrSrc[i]&cBitMask)
          {
              fld[i*8+j+1] = 0;
          }
          else
          {
              fld[i*8+j+1] = -1;
          }
      }
	}
	
}



/*-------------------------------------------------------------------------
 FUNCTION NAME: TOOL FUNCTION
 *------------------------------------------------------------------------*/

/*********************
*十六进制转换为字节
*********************/
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen)
{
	short i;
	unsigned char highByte, lowByte;
	
	for (i = 0; i < sourceLen; i += 2)
	{
		highByte = toupper(source[i]);
		lowByte  = toupper(source[i + 1]);

		if (highByte > 0x39)
			highByte -= 0x37;
		else
			highByte -= 0x30;

		if (lowByte > 0x39)
			lowByte -= 0x37;
		else
			lowByte -= 0x30;

		dest[i / 2] = (highByte << 4) | lowByte;
	}
	return;
}

/*********************
*字节转换为十六进制
*********************/
void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen)
{
	short i;
	unsigned char highByte, lowByte;

	for (i = 0; i < sourceLen; i++)
	{
		highByte = source[i] >> 4;
		lowByte = source[i] & 0x0f ;

		highByte += 0x30;

		if (highByte > 0x39)
		        dest[i * 2] = highByte + 0x07;
		else
		        dest[i * 2] = highByte;

		lowByte += 0x30;
		if (lowByte > 0x39)
			dest[i * 2 + 1] = lowByte + 0x07;
		else
			dest[i * 2 + 1] = lowByte;
	}
  return;
}

INT16 nAton( void *vvAsc, UINT16 vnLen, UINT16 *vvVal)
{
    STR_CONVERT_2_DIG(UINT16);
}

int nBcd2Num( void *vvpSrcBuf, unsigned short* vvpDesBuf,int nSrcBufLen)
{
	char dest[4]={0};
	
	ByteToHexStr( (unsigned char*) vvpSrcBuf, dest, nSrcBufLen);
	
	if(nAton(dest,nSrcBufLen*2,vvpDesBuf)!=BANK_OK)
	{
		printf("format error\n");
		return BANK_FAIL;
	}
	
  return BANK_OK;
}

INT16 nNtoa( void *vvAsc, UINT16 vnLen, UINT16 vvVal)
{
    DIG_CONVERT_2_STR(UINT16);
}

int nNum2Bcd( UINT16 vvpSrcBuf, void* vvpDesBuf, UINT16 nSrcBufLen)
{
	unsigned char dest[4]={0};
	
	if(nNtoa(dest, nSrcBufLen*2, vvpSrcBuf)!=BANK_OK)
	{
		printf("format error\n");
		return BANK_FAIL;
	}
	
	HexStrToByte((char*)dest, (unsigned char*) vvpDesBuf, nSrcBufLen*2);
		
  return BANK_OK;
}


int CvtBitMapMd(void *dest, void *src)
{
	register INT16 i;
	int bitlen;
	unsigned char *ptrSrc,*ptrDest;
  
  ptrSrc=(unsigned char *)src;
  ptrDest=(unsigned char *)dest;
  
	if((bitlen=strlen((char*)ptrSrc)) <= 0)
		return -1;
		
	for (i = 0; i < 8; i++)
	{
		*(ptrDest+i) = 
		((ptrSrc[i*2] >= 'A'&& ptrSrc[i*2] <= 'F')?((ptrSrc[i*2]-'A'+0x0A)<<4):((ptrSrc[i*2]-'0')<<4))
      + ((ptrSrc[i*2+1] >= 'A'&& ptrSrc[i*2+1] <= 'F')?(ptrSrc[i*2+1]-'A'+0x0A):(ptrSrc[i*2+1]-'0'));
	}
	
	return 0;
}

void GetCurrentTime(char *sCurrentTime)
{  
   time_t current;             //系统时间类型   
   struct tm *tmCurrentTime;   //时间结构tm
   
   tzset();                    //UNIX时间兼容函数
   time(&current);             //获取当前日期时间
   tmCurrentTime = localtime(&current); //将time_t类型的日期时间转换为tm结构
   sprintf(sCurrentTime, "%4d%02d%02d%02d%02d%02d", 
				 tmCurrentTime->tm_year + 1900, tmCurrentTime->tm_mon + 1,  //tm结构中存放的是从1900年1月后经过的年数和月数
				 tmCurrentTime->tm_mday, tmCurrentTime->tm_hour,
           tmCurrentTime->tm_min, tmCurrentTime->tm_sec);
}

/*
vnConLen    --- asc lenght
vspType     --- 0, right filled with zero, 1 left filled with zero
*/

void vBcd2Asc( unsigned char *vspAscStr, unsigned char* vspBcdStr, int vnConLen, unsigned char *vspType )
{
    int     nCount;

    if( vnConLen & 0x01 && vspType ) 
    {
        nCount = 1;
        vnConLen ++;
    }
    else
        nCount = 0;

    for( ; nCount < vnConLen; nCount ++, vspAscStr ++ ) 
    {
        * vspAscStr = ( ( nCount & 0x01 ) ? ( * vspBcdStr ++ & 0x0f ) : ( * vspBcdStr >> 4 ) );
        * vspAscStr += ( ( * vspAscStr > 9 ) ? ( 'A' - 10 ) : '0' );
    }
    return;
}

/*
vnConLen    --- asc lenght
vspType     --- 0, right filled with zero, 1 left filled with zero
*/
void vAsc2Bcd( unsigned char *vspBcdStr, unsigned char* vspAscStr, int vnConLen, unsigned char* vspType )
{
    int     lnCount;
    char    lsCh, lsCh1;

    if ( vnConLen & 0x01 && vspType )
        lsCh1 = 0;
    else
        lsCh1 = 0x55;

    for ( lnCount = 0; lnCount < vnConLen; vspAscStr ++, lnCount ++ ) 
    {

        if ( * vspAscStr >= 'a' )
            lsCh = * vspAscStr - 'a' + 10;
        else if ( *vspAscStr >= 'A' )
            lsCh = * vspAscStr - 'A' + 10;
        else if ( * vspAscStr >= '0' )
            lsCh = * vspAscStr - '0';
        else
            lsCh = 0;

        if ( lsCh1 == 0x55 )
            lsCh1 = lsCh;
        else {
            * vspBcdStr ++ = ( lsCh1 << 4 ) | lsCh;
            lsCh1 = 0x55;
        }
    }

    if ( lsCh1 != 0x55 )
        * vspBcdStr = lsCh1 << 4;

    return;
}


int main()
{
	int nlen;
//	FILE * pwrite;
	char tmpbuf[1000]={0};
	ComDataDef ComData;
	
	memset(&ComData,0,sizeof(ComDataDef));
	memset(&frameS,0,sizeof(frame_str));
	memset(&frameR,0,sizeof(frame_str));
	SET_COM_DATA((&ComData));
	
	nlen=ISO8583_Pack(&msg[ICBC_LOAD],&ComData);
	
	printf("ISO8583_Pack len is %d\n",nlen);
	
	memcpy(&frameR,&frameS,sizeof(frame_str));
	memset(&ComData,0,sizeof(ComDataDef));
	
	
	ISO8583_UnPack(&ComData, nlen);
	
//	pwrite=fopen(".\\log", "a+");
	
//	nlen=fwrite(&frameS.TPDU, sizeof(frame_str), 1,pwrite);
//	printf("write len is %d\n",nlen);
	
//	fclose(pwrite);
	
	return 0;
}

