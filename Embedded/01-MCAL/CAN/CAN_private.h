/*
 * CAN_private.h
 *
 *  Created on: Feb 3, 2023
 *      Author: ELHOSSENI
 */

#ifndef MCAL_CAN_CAN_PRIVATE_H_
#define MCAL_CAN_CAN_PRIVATE_H_


/***********************************************************************************************************************************************************************************************************************************************************
                                               *******Controller Area Network Register Definition**********
***********************************************************************************************************************************************************************************************************************************************************/
/**
  * @brief Controller Area Network TxMailBox
  */

typedef struct
{
   unit32 TIR;
   unit32 TDTR;
   unit32 TDLR;
   unit32 TDHR;
} CAN_TxMailBoxType_Def;

/**
  * @brief Controller Area Network FIFOMailBox
  */

typedef struct
{
  unit32 RIR;
  unit32 RDTR;
  unit32 RDLR;
  unit32 RDHR;
} CAN_FIFOMailBoxType_Def;

/**
  * @brief Controller Area Network FilterRegister
  */

typedef struct
{
  unit32 FR1;
  unit32 FR2;
} CAN_FilterRegisterType_Def;

/**
  * @brief Controller Area Network
  */

typedef struct
{
  unit32 MCR;
  unit32 MSR;
  unit32 TSR;
  unit32 RF0R;
  unit32 RF1R;
  unit32 IER;
  unit32 ESR;
  unit32 BTR;
  unit32 RESERVED0[88];
  CAN_TxMailBoxType_Def   sTxMailBox[3];
  CAN_FIFOMailBoxType_Def sFIFOMailBox[2];
  unit32  RESERVED1[12];
  unit32  FMR;
  unit32  FM1R;
  unit32  RESERVED2;
  unit32  FS1R;
  unit32  RESERVED3;
  unit32  FFA1R;
  unit32  RESERVED4;
  unit32  FA1R;
  unit32  RESERVED5[8];
  CAN_FilterRegisterType_Def sFilterRegister[14];
} CAN_TypeDef;

/*Peripheral declaration*/


/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Base Address Macros**********
***********************************************************************************************************************************************************************************************************************************************************/
#define CAN1_BASE          0x40006400
#define CAN2_BASE          0x40006800


/***********************************************************************************************************************************************************************************************************************************************************
                                                   ****Peripheral declaration******
***********************************************************************************************************************************************************************************************************************************************************/

#define CAN1                ((volatile CAN_TypeDef*) CAN1_BASE)
#define CAN2                ((volatile CAN_TypeDef*) CAN2_BASE)


/***********************************************************************************************************************************************************************************************************************************************************
                                                   *******Registers Bits Definitions**********
***********************************************************************************************************************************************************************************************************************************************************/


                                  /*!< CAN control and status registers */
/*******************  Bit definition for CAN_MCR register  ********************/
#define  CAN_MCR_INRQ                        ((unit16)0x0001)            /*!< Initialization Request */
#define  CAN_MCR_SLEEP                       ((unit16)0x0002)            /*!< Sleep Mode Request */
#define  CAN_MCR_TXFP                        ((unit16)0x0004)            /*!< Transmit FIFO Priority */
#define  CAN_MCR_RFLM                        ((unit16)0x0008)            /*!< Receive FIFO Locked Mode */
#define  CAN_MCR_NART                        ((unit16)0x0010)            /*!< No Automatic Retransmission */
#define  CAN_MCR_AWUM                        ((unit16)0x0020)            /*!< Automatic Wakeup Mode */
#define  CAN_MCR_ABOM                        ((unit16)0x0040)            /*!< Automatic Bus-Off Management */
#define  CAN_MCR_TTCM                        ((unit16)0x0080)            /*!< Time Triggered Communication Mode */

/*******************  Bit definition for CAN_MSR register  ********************/
#define  CAN_MSR_INAK                        ((unit16)0x0001)            /*!< Initialization Acknowledge */
#define  CAN_MSR_SLAK                        ((unit16)0x0002)            /*!< Sleep Acknowledge */
#define  CAN_MSR_WKUI                        ((unit16)0x0008)            /*!< Wakeup Interrupt */

/*******************  Bit definition for CAN_TSR register  ********************/
#define  CAN_TSR_RQCP0                       ((unit32)0x00000001)        /*!< Request Completed Mailbox0 */
#define  CAN_TSR_TXOK0                       ((unit32)0x00000002)        /*!< Transmission OK of Mailbox0 */
#define  CAN_TSR_ALST0                       ((unit32)0x00000004)        /*!< Arbitration Lost for Mailbox0 */
#define  CAN_TSR_TERR0                       ((unit32)0x00000008)        /*!< Transmission Error of Mailbox0 */
#define  CAN_TSR_ABRQ0                       ((unit32)0x00000080)        /*!< Abort Request for Mailbox0 */
#define  CAN_TSR_RQCP1                       ((unit32)0x00000100)        /*!< Request Completed Mailbox1 */
#define  CAN_TSR_TXOK1                       ((unit32)0x00000200)        /*!< Transmission OK of Mailbox1 */
#define  CAN_TSR_ALST1                       ((unit32)0x00000400)        /*!< Arbitration Lost for Mailbox1 */
#define  CAN_TSR_TERR1                       ((unit32)0x00000800)        /*!< Transmission Error of Mailbox1 */
#define  CAN_TSR_ABRQ1                       ((unit32)0x00008000)        /*!< Abort Request for Mailbox 1 */
#define  CAN_TSR_RQCP2                       ((unit32)0x00010000)        /*!< Request Completed Mailbox2 */
#define  CAN_TSR_TXOK2                       ((unit32)0x00020000)        /*!< Transmission OK of Mailbox 2 */
#define  CAN_TSR_ALST2                       ((unit32)0x00040000)        /*!< Arbitration Lost for mailbox 2 */
#define  CAN_TSR_TERR2                       ((unit32)0x00080000)        /*!< Transmission Error of Mailbox 2 */
#define  CAN_TSR_ABRQ2                       ((unit32)0x00800000)        /*!< Abort Request for Mailbox 2 */
#define  CAN_TSR_CODE                        ((unit32)0x03000000)        /*!< Mailbox Code */

#define  CAN_TSR_TME                         ((unit32)0x1C000000)        /*!< TME[2:0] bits */
#define  CAN_TSR_TME0                        ((unit32)0x04000000)        /*!< Transmit Mailbox 0 Empty */
#define  CAN_TSR_TME1                        ((unit32)0x08000000)        /*!< Transmit Mailbox 1 Empty */
#define  CAN_TSR_TME2                        ((unit32)0x10000000)        /*!< Transmit Mailbox 2 Empty */

/*******************  Bit definition for CAN_RF0R register  *******************/
#define  CAN_RF0R_FMP0                       ((unit8)0x03)               /*!< FIFO 0 Message Pending */
#define  CAN_RF0R_FULL0                      ((unit8)0x08)               /*!< FIFO 0 Full */
#define  CAN_RF0R_FOVR0                      ((unit8)0x10)               /*!< FIFO 0 Overrun */
#define  CAN_RF0R_RFOM0                      ((unit8)0x20)               /*!< Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1R register  *******************/
#define  CAN_RF1R_FMP1                       ((unit8)0x03)               /*!< FIFO 1 Message Pending */
#define  CAN_RF1R_FULL1                      ((unit8)0x08)               /*!< FIFO 1 Full */
#define  CAN_RF1R_FOVR1                      ((unit8)0x10)               /*!< FIFO 1 Overrun */
#define  CAN_RF1R_RFOM1                      ((unit8)0x20)               /*!< Release FIFO 1 Output Mailbox */

/********************  Bit definition for CAN_IER register  *******************/
#define  CAN_IER_TMEIE                       ((unit32)0x00000001)        /*!< Transmit Mailbox Empty Interrupt Enable */
#define  CAN_IER_FMPIE0                      ((unit32)0x00000002)        /*!< FIFO 0 Message Pending Interrupt Enable */
#define  CAN_IER_FMPIE1                      ((unit32)0x00000010)        /*!< FIFO 1 Message Pending Interrupt Enable */

/********************  Bit definition for CAN_ESR register  *******************/
#define  CAN_ESR_LEC                         ((unit32)0x00000070)        /*!< LEC[2:0] bits (Last Error Code) */

                                  /*!< Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define  CAN_TI0R_TXRQ                       ((unit32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI0R_RTR                        ((unit32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI0R_IDE                        ((unit32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI0R_EXID                       ((unit32)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_TI0R_STID                       ((unit32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0R register  *******************/
#define  CAN_TDT0R_DLC                       ((unit32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT0R_TGT                       ((unit32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT0R_TIME                      ((unit32)0xFFFF0000)        /*!< Message Time Stamp */

/******************  Bit definition for CAN_TDL0R register  *******************/
#define  CAN_TDL0R_DATA0                     ((unit32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL0R_DATA1                     ((unit32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL0R_DATA2                     ((unit32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL0R_DATA3                     ((unit32)0xFF000000)        /*!< Data byte 3 */

/******************  Bit definition for CAN_TDH0R register  *******************/
#define  CAN_TDH0R_DATA4                     ((unit32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH0R_DATA5                     ((unit32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH0R_DATA6                     ((unit32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH0R_DATA7                     ((unit32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI1R register  *******************/
#define  CAN_TI1R_TXRQ                       ((unit32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI1R_RTR                        ((unit32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI1R_IDE                        ((unit32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI1R_EXID                       ((unit32)0x001FFFF8)        /*!< Extended Identifier */

/*******************  Bit definition for CAN_TDT1R register  ******************/
#define  CAN_TDT1R_DLC                       ((unit32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT1R_TGT                       ((unit32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT1R_TIME                      ((unit32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL1R register  ******************/
#define  CAN_TDL1R_DATA0                     ((unit32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL1R_DATA1                     ((unit32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL1R_DATA2                     ((unit32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL1R_DATA3                     ((unit32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH1R register  ******************/
#define  CAN_TDH1R_DATA4                     ((unit32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH1R_DATA5                     ((unit32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH1R_DATA6                     ((unit32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH1R_DATA7                     ((unit32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_TI2R register  *******************/
#define  CAN_TI2R_TXRQ                       ((unit32)0x00000001)        /*!< Transmit Mailbox Request */
#define  CAN_TI2R_RTR                        ((unit32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_TI2R_IDE                        ((unit32)0x00000004)        /*!< Identifier Extension */
#define  CAN_TI2R_EXID                       ((unit32)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_TI2R_STID                       ((unit32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2R register  ******************/
#define  CAN_TDT2R_DLC                       ((unit32)0x0000000F)        /*!< Data Length Code */
#define  CAN_TDT2R_TGT                       ((unit32)0x00000100)        /*!< Transmit Global Time */
#define  CAN_TDT2R_TIME                      ((unit32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_TDL2R register  ******************/
#define  CAN_TDL2R_DATA0                     ((unit32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_TDL2R_DATA1                     ((unit32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_TDL2R_DATA2                     ((unit32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_TDL2R_DATA3                     ((unit32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_TDH2R register  ******************/
#define  CAN_TDH2R_DATA4                     ((unit32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_TDH2R_DATA5                     ((unit32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_TDH2R_DATA6                     ((unit32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_TDH2R_DATA7                     ((unit32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define  CAN_RI0R_RTR                        ((unit32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RI0R_IDE                        ((unit32)0x00000004)        /*!< Identifier Extension */
#define  CAN_RI0R_EXID                       ((unit32)0x001FFFF8)        /*!< Extended Identifier */
#define  CAN_RI0R_STID                       ((unit32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define  CAN_RDT0R_DLC                       ((unit32)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT0R_FMI                       ((unit32)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT0R_TIME                      ((unit32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define  CAN_RDL0R_DATA0                     ((unit32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL0R_DATA1                     ((unit32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL0R_DATA2                     ((unit32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL0R_DATA3                     ((unit32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define  CAN_RDH0R_DATA4                     ((unit32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH0R_DATA5                     ((unit32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH0R_DATA6                     ((unit32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH0R_DATA7                     ((unit32)0xFF000000)        /*!< Data byte 7 */

/*******************  Bit definition for CAN_RI1R register  *******************/
#define  CAN_RI1R_RTR                        ((unit32)0x00000002)        /*!< Remote Transmission Request */
#define  CAN_RI1R_IDE                        ((unit32)0x00000004)        /*!< Identifier Extension */
#define  CAN_RI1R_EXID                       ((unit32)0x001FFFF8)        /*!< Extended identifier */
#define  CAN_RI1R_STID                       ((unit32)0xFFE00000)        /*!< Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1R register  ******************/
#define  CAN_RDT1R_DLC                       ((unit32)0x0000000F)        /*!< Data Length Code */
#define  CAN_RDT1R_FMI                       ((unit32)0x0000FF00)        /*!< Filter Match Index */
#define  CAN_RDT1R_TIME                      ((unit32)0xFFFF0000)        /*!< Message Time Stamp */

/*******************  Bit definition for CAN_RDL1R register  ******************/
#define  CAN_RDL1R_DATA0                     ((unit32)0x000000FF)        /*!< Data byte 0 */
#define  CAN_RDL1R_DATA1                     ((unit32)0x0000FF00)        /*!< Data byte 1 */
#define  CAN_RDL1R_DATA2                     ((unit32)0x00FF0000)        /*!< Data byte 2 */
#define  CAN_RDL1R_DATA3                     ((unit32)0xFF000000)        /*!< Data byte 3 */

/*******************  Bit definition for CAN_RDH1R register  ******************/
#define  CAN_RDH1R_DATA4                     ((unit32)0x000000FF)        /*!< Data byte 4 */
#define  CAN_RDH1R_DATA5                     ((unit32)0x0000FF00)        /*!< Data byte 5 */
#define  CAN_RDH1R_DATA6                     ((unit32)0x00FF0000)        /*!< Data byte 6 */
#define  CAN_RDH1R_DATA7                     ((unit32)0xFF000000)        /*!< Data byte 7 */

/*****************************Private Macros************************************/
#define FRAME_DATA              8
#define ZERO                    0
#define BYTE_ZERO               0
#define BYTE_ONE                1
#define BYTE_TWO                2
#define BYTE_THREE              3

                            /*!< CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/
#define  CAN_FMR_FINIT                       ((unit8)0x01)               /*!< Filter Init Mode */

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
}FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{ERROR = 0,
 SUCCESS = !ERROR
}ErrorStatus;



#endif /* MCAL_CAN_CAN_PRIVATE_H_ */
