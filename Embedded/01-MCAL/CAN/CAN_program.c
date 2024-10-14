/*******************************************************************************
**  FILENAME     : Can.c                                                        **
**                                                                            **
**  VERSION      : 1.2.0                                                       **
**                                                                            **
**  DATE         : 2022-04-28                                                  **
**                                                                            **
**  PLATFORM     : stm32f103                                                   **
**                                                                            **
**  AUTHOR       : Hosseni Gamal                                               **
**                                                                            **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
*******************************************************************************/



/**********************************************include******************************************/
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/CAN/CAN_Interface.h"
#include "../Inc/MCAL/CAN/CAN_Private.h"
#include "../Inc/MCAL/CAN/CAN_config.h"
/*
Description: CAN Rx message structure for pending interrupt
*/



/******************************************************************************
* \Syntax          : void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct)
* \Description     : Initializes the CAN peripheral with the provided configuration settings.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral to be initialized.
*                    CANInitStruct - Pointer to a structure containing initialization settings.
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void CAN_VoidInit(CAN_TypeDef* CANx, CAN_InitTypeDef* CANInitStruct)
{

 /* Request to exit Sleep mode */
  CANx->MCR &= ~CAN_MCR_SLEEP;

  /* Request initialisation */
  CANx->MCR |= CAN_MCR_INRQ ;

	 /* Wait for initialization mode */
  while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CANx->MSR))
     || (CAN_MSR_INAK != (CAN_MSR_INAK & CANx->MSR)));



                           /******************* SET MCR register configuration**************************/

	/* Set the time triggered communication mode */
    if (CANInitStruct->CAN_TTCM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TTCM;
    }
    else
    {
      CANx->MCR &= ~(unit32)CAN_MCR_TTCM;
    }
		 /* Set the automatic bus-off management */
    if (CANInitStruct->CAN_ABOM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_ABOM;
    }
    else
    {
      CANx->MCR &= ~(unit32)CAN_MCR_ABOM;
    }

	   /* Set the automatic wake-up mode */
    if (CANInitStruct->CAN_AWUM == ENABLE)
    {
      CANx->MCR |= CAN_MCR_AWUM;
    }
    else
    {
      CANx->MCR &= ~(unit32)CAN_MCR_AWUM;
    }

		/* Set the no automatic retransmission */
    if (CANInitStruct->CAN_NART == ENABLE)
    {
      CANx->MCR |= CAN_MCR_NART;
    }
    else
    {
      CANx->MCR &= ~(unit32)CAN_MCR_NART;
    }

		/* Set the transmit FIFO priority */
    if (CANInitStruct->CAN_TXFP == ENABLE)
    {
      CANx->MCR |= CAN_MCR_TXFP;
    }
    else
    {
      CANx->MCR &= ~(unit32)CAN_MCR_TXFP;
    }


    CANx->BTR =(unit32)         ((unit32)CANInitStruct->CAN_MODE << 30   )
                       |     ((unit32)CANInitStruct->CAN_SJW  << 24   )
                       |     ((unit32)CANInitStruct->CAN_BS1  << 16   )
                       |     ((unit32)CANInitStruct->CAN_BS2  << 20   )
                       |     ((unit32)CANInitStruct->CAN_Prescaler-1  ) ;


    /* Request leave initialisation */
    CANx->MCR &= ~(unit32)CAN_MCR_INRQ;

}
/******************************************************************************
* \Syntax          : void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
* \Description     : Configures a filter bank for incoming CAN messages.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CAN_FilterInitStruct - Pointer to a structure containing filter configuration.
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void CAN_VoidFilterSet(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
       unit32 Local_unit32filterNumberPosition ; // filter posotion number in the register
	   unit8  Local_unit8FilterBankExidId ;	   //contain exdended [15 :17] of filter id
	   unit8  Local_unit8FilterBankRtrId  ; //contain rtr offilter id
	   unit8  Local_unit8FilterBankIdeId  ; //contain ide of filter id
	   unit16 Local_unit16FilterBankStdId ;//contain std id of filter id

       unit8  Local_unit8FilterBankExidMaskId ;	//contain exdended [15 :17] of filter mask id
	   unit8  Local_unit8FilterBankRtrMaskId  ;  //contain rtr of filter  mask id
	   unit8  Local_unit8FilterBankIdeIdMask  ;  //contain ide of filter  mask id
	   unit16 Local_unit16FilterBankStdIdMask ; //contain std id of filter mask id

       unit16 Local_unit16FilterbankId  ;  // new id to set in 16-scale filter bank
	   unit16 Local_unit16FilterbankMaskId  ;  // new maske id to set in 16-scale filter bank


	            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of filter id */
 	     Local_unit8FilterBankExidId   = (unit8)   ((0x00038000 & CAN_FilterInitStruct->CAN_FilterId) >> 15  ) ;
		 Local_unit8FilterBankRtrId    = (unit8)   ((0x00000002 & CAN_FilterInitStruct->CAN_FilterId) << 3   ) ;
		 Local_unit8FilterBankIdeId    = (unit8)   ((0x00000004 & CAN_FilterInitStruct->CAN_FilterId) << 1   ) ;
		 Local_unit16FilterBankStdId   = (unit16)  ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterId) >> 16  );

			            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of  filter mask id */
	     Local_unit8FilterBankExidMaskId = (unit8) ((0x00038000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 15  ) ;
		 Local_unit8FilterBankRtrMaskId  = (unit8) ((0x00000002 & CAN_FilterInitStruct->CAN_FilterMaskId) << 3   ) ;
		 Local_unit8FilterBankIdeIdMask  = (unit8) ((0x00000004 & CAN_FilterInitStruct->CAN_FilterMaskId) << 1   ) ;
		 Local_unit16FilterBankStdIdMask =(unit16) ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 16  ) ;



Local_unit32filterNumberPosition = ( (unit32)(1) ) << CAN_FilterInitStruct->CAN_FilterBankNumber;

	/* Initialisation mode for the filter */
	CAN1->FMR |= CAN_FMR_FINIT;

	/* Filter Deactivation */
	 CAN1->FA1R &= ~(unit32)Local_unit32filterNumberPosition;

	if (CAN_FilterInitStruct->CAN_FilterBankScale == CAN_FilterScale_16bit)
	{

		/* 16-bit scale for the filter */
		CAN1->FS1R &= ~(unit32)Local_unit32filterNumberPosition;

		/* Filter mapping
		*   15-8        7-5    4   3     2-0
		* STID[10:3] STID[2:0] RTR IDE EXID[17:15]
		* */
									   /*Get masked filter id and filter mask id*/
		 Local_unit16FilterbankId         = (unit16) ( Local_unit8FilterBankExidId     | Local_unit8FilterBankRtrId
											    | Local_unit8FilterBankIdeId     | Local_unit16FilterBankStdId    );

		 Local_unit16FilterbankMaskId      = (unit16)(Local_unit8FilterBankExidMaskId   | Local_unit8FilterBankRtrMaskId
											    | Local_unit8FilterBankIdeIdMask | Local_unit16FilterBankStdIdMask );

				/* Filter Mode */
		 if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
		 {
		   /*Id/Mask mode for the filter*/
		   CAN1->FM1R &= ~(unit32)Local_unit32filterNumberPosition;
													 /*FR1 =FR2 = [Local_unit16FilterbankMaskId |Local_unit16FilterbankId]*/
				CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 =  ((0x0000FFFF &  (unit32)Local_unit16FilterbankMaskId) << 16 )
																						| (0x0000FFFF &  (unit32)Local_unit16FilterbankId            ) ;
				CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =  ((0x0000FFFF &  (unit32)Local_unit16FilterbankMaskId) << 16 )
																						| (0x0000FFFF &  (unit32)Local_unit16FilterbankId            ) ;

		}
		else /* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/
		{
			/*Identifier list mode for the filter*/
			CAN1->FM1R |= (unit32)Local_unit32filterNumberPosition;

			/*FR1 =FR2 = [Local_unit16FilterbankId |Local_unit16FilterbankId]*/
			CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (unit32)Local_unit16FilterbankId) << 16 )
																					   | (0x0000FFFF &  (unit32)Local_unit16FilterbankId        ) ;
			CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = ((0x0000FFFF &  (unit32)Local_unit16FilterbankId) << 16 )
																				 | (0x0000FFFF &  (unit32)Local_unit16FilterbankId        ) ;

		}
	}

if (CAN_FilterInitStruct->CAN_FilterBankScale == CAN_FilterScale_32bit)
{
   /* 32-bit scale for the filter */
   CAN1->FS1R |= (unit32)Local_unit32filterNumberPosition;

		/* Filter Mode */
	 if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
	 {
	   /*Id/Mask mode for the filter*/
	   CAN1->FM1R &= ~(unit32)Local_unit32filterNumberPosition;

	   /* for scale 32bit FilterbankID = FR1 and FilterbankMASK = FR2 */
	   CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (unit32)CAN_FilterInitStruct->CAN_FilterId ;
	   CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (unit32)CAN_FilterInitStruct->CAN_FilterMaskId ;
	 }

	 else /* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

	 {
				/*Id list mode for the filter*/
	   CAN1->FM1R |= (unit32)Local_unit32filterNumberPosition;

	   /* for scale 32bit FilterbankID = FilterbankMASK = FR1 = FR2 */
	   CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (unit32)CAN_FilterInitStruct->CAN_FilterId ;
	   CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (unit32)CAN_FilterInitStruct->CAN_FilterId ;

	 }

}

	/* specify Filter FIFO  */
 if (CAN_FilterInitStruct->CAN_FilterFIFONumber == CAN_Filter_FIFO0)
 {
   CAN1->FFA1R &= ~(unit32)Local_unit32filterNumberPosition;     // FIFO 0 chosen for the filter

 }

 if (CAN_FilterInitStruct->CAN_FilterFIFONumber == CAN_Filter_FIFO1)
 {

   CAN1->FFA1R |= (unit32)Local_unit32filterNumberPosition;   // FIFO 1 chosen for the filter
 }

 if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
 {
   CAN1->FA1R |= Local_unit32filterNumberPosition;  	 // Filter activation

 }

 CAN1->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */

}

/******************************************************************************
* \Syntax          : unit8 CAN_unit8Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
* \Description     : Transmits a CAN message using the specified CAN peripheral and mailbox.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral to use for transmission.
*                    TxMessage - Pointer to the CAN transmit message structure.
* \Parameters (out): None
* \Return value:   : unit8 - Mailbox number used for transmission.
*******************************************************************************/
unit8 CAN_VoidTransmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{

	unit8 Local_unit8TransMailboxNumber = 0; //contain empty mailbox number
    unit8 Local_unit8TransDataCounter ; //counter to set data into Transit Data register byte by byte

		 while(!(CAN1->TSR & CAN_TSR_TME0));   // Block until mailbox 0 is empty

		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TIR = 0;     //reset identifier register

		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TIR |= (TxMessage->IDE << 2) | (TxMessage->RTR << 1 ) ;//setrtr and ide of input fram

		//set CAN identifier
		if (TxMessage->IDE) //extended
		{
			CANx->sTxMailBox[Local_unit8TransMailboxNumber].TIR |= (TxMessage->ID << 3); //extended
		}
		else //standard
		{
			CANx->sTxMailBox[Local_unit8TransMailboxNumber].TIR |= (TxMessage->ID << 21); //standard
		}

		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDTR = (CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDTR & (~0x0f))		//set data length
				                                               | TxMessage->DATA_LENGHT ;

		/*reset transmit data registers*/
		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDLR = 0;
		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDHR = 0;

		for ( Local_unit8TransDataCounter = 0; Local_unit8TransDataCounter < TxMessage->DATA_LENGHT; Local_unit8TransDataCounter++)
		{

			if (Local_unit8TransDataCounter < 4)           //set LSB (16 bits) of the Data
			{
				CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDLR |= (TxMessage->DATA[Local_unit8TransDataCounter] << (8 * Local_unit8TransDataCounter)); // masking word byte by byte to low register
			}
			else /*(Local_unit8DataCounter >= 4) */  //set MSB (16 bits) of the Data
			{
				CANx->sTxMailBox[Local_unit8TransMailboxNumber].TDHR |= (TxMessage->DATA[Local_unit8TransDataCounter] << (8 * (Local_unit8TransDataCounter - 4)));// masking word byte by byte to high register
			}

		}

		CANx->sTxMailBox[Local_unit8TransMailboxNumber].TIR |= CAN_TI0R_TXRQ;  //Transmit Mailbox Request
//	}

		  return Local_unit8TransMailboxNumber; // return result state

}
/******************************************************************************
* \Syntax          : void CAN_VoidReceive(CAN_TypeDef* CANx, unit8 Copy_unit8FifoNumber, CanRxMsg* RxMessage)
* \Description     : Receives a CAN message from the specified FIFO and fills the RxMessage structure.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral to receive from.
*                    Copy_unit8FifoNumber - FIFO number to receive from (CAN_FIFO0 or CAN_FIFO1).
* \Parameters (out): RxMessage - Pointer to a structure to store the received message.
* \Return value:   : None
*******************************************************************************/
void CAN_VoidReceive(CAN_TypeDef* CANx, unit8 Copy_unit8FifoNumber, CanRxMsg* RxMessage)
{


	while ((CANx->RF0R & CAN_RF0R_RFOM0));// wait until receive a massage
	unit8 Local_unit8ReceivDataCounter ; //counter to Get data into Receiv Data register byte by byte

		RxMessage->DATA_LENGHT = (CANx->sFIFOMailBox[Copy_unit8FifoNumber].RDTR & (unit8)0x0F); //get data length

		RxMessage->IDE = (CANx->sFIFOMailBox[Copy_unit8FifoNumber].RIR & (unit8)0x04) ; // get IDE

		RxMessage->RTR = (CANx->sFIFOMailBox[Copy_unit8FifoNumber].RIR & (unit8)0x02) ; //get RTR

        RxMessage->FMI =  ((CANx->sFIFOMailBox[Copy_unit8FifoNumber].RDTR >> 8) & (unit8)0x0F) ;	// 0xFFGet the FMI

		if ( RxMessage->IDE == 0X00 ) //standard
		{
			RxMessage->ID = ( CANx->sFIFOMailBox[Copy_unit8FifoNumber].RIR >> 21) & ((unit32)0x000007FF) ; //get 11 bit of standard id
		}
		else//extended
		{
			RxMessage->ID = ( CANx->sFIFOMailBox[Copy_unit8FifoNumber].RIR >> 3 ) & ((unit32)0x1FFFFFFF) ; // get 29 bit of extended message
		}

		for ( Local_unit8ReceivDataCounter = 0;  Local_unit8ReceivDataCounter< RxMessage->DATA_LENGHT; Local_unit8ReceivDataCounter++)

		{
			if (Local_unit8ReceivDataCounter < 4)  //get LSB (16 bits) of the Data
			{
				RxMessage->DATA[Local_unit8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_unit8FifoNumber].RDLR >> (Local_unit8ReceivDataCounter* 8))  & 0xFF; //get Data from low register byte by byte
			}
			else /*(Local_unit8ReceivDataCounter >= 4)*/  //Get LSB (16 bits) of the Data
			{
				RxMessage->DATA[Local_unit8ReceivDataCounter] = (CANx->sFIFOMailBox[Copy_unit8FifoNumber].RDHR >> ((Local_unit8ReceivDataCounter - 4) * 8)) & 0xFF; //get Data from high register byte by byte
			}

		}

		if (Copy_unit8FifoNumber == CAN_FIFO0) //check for input FIFO to release
		{

			CANx->RF0R |= CAN_RF0R_RFOM0;  //release FIFO 0

		}

		else if ( Copy_unit8FifoNumber == CAN_FIFO1)
		{

			CANx->RF1R |= CAN_RF1R_RFOM1;  //release FIFO 1

		}

		else
		{

			/*wrong fifo number input*/
		}

}
/******************************************************************************
* \Syntax          : unit8 CAN_unit8GetLastErrorCodeType(CAN_TypeDef* CANx)
* \Description     : Retrieves the last error code from the CAN peripheral.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral.
* \Parameters (out): None
* \Return value:   : unit8 - Last error code type.
*******************************************************************************/
unit8 CAN_unit8GetLastErrorCodeType(CAN_TypeDef* CANx)
{
  unit8 Local_unit8ErrorcodeType=0; //contain Code error Type

  Local_unit8ErrorcodeType = (((unit8)CANx->ESR) & (unit8)CAN_ESR_LEC); // Get the last error code

  return Local_unit8ErrorcodeType;//Return the error code
}

/******************************************************************************
* \Syntax          : void CAN_VoidInterruptSet(CAN_TypeDef* CANx, unit32 Copy_unit32CanInterruptType, FunctionalState Copy_unit8InterruptNewState)
* \Description     : Enables or disables CAN interrupts.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral.
*                    Copy_unit32CanInterruptType - Bitwise OR of interrupt types to enable/disable.
*                    Copy_unit8InterruptNewState - New state of interrupts (ENABLE or DISABLE).
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void CAN_VoidInterruptSet(CAN_TypeDef* CANx, unit32 Copy_unit32CanInterruptType, FunctionalState Copy_unit8InterruptNewState)
{

  if (Copy_unit8InterruptNewState == ENABLE) //check for input new state of input interrupt
  {

    CANx->IER |= Copy_unit32CanInterruptType; // Enable the selected CANx interrupt
  }
  else if (Copy_unit8InterruptNewState == DISABLE)
  {
    CANx->IER &= ~Copy_unit32CanInterruptType; // Disable the selected CANx interrupt

  }
	else
	{
	   /*WRONG STATE INPUT*/
	}
}
/******************************************************************************
* \Syntax          : void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , unit8 Copy_unit8MailBoxNumber)
* \Description     : Enables or disables the Time Trigger Communication Mode for a mailbox.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : CANx - Pointer to the CAN peripheral.
*                    NewState - New state of Time Trigger Communication Mode (ENABLE or DISABLE).
*                    Copy_unit8MailBoxNumber - Mailbox number (0, 1, or 2).
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void CAN_VoidTimeTriggerCommMode(CAN_TypeDef* CANx, FunctionalState NewState , unit8 Copy_unit8MailBoxNumber)
{

	if ( Copy_unit8MailBoxNumber > 2) //check to mail box number
	{

	/*wrong input mail box*/
	return   ;

	}

  if (NewState == ENABLE)
  {

		/*This bit is active only when the hardware is in the Time Trigger Communication mode*/

    CANx->MCR |= CAN_MCR_TTCM;  //  Enable the TTCM mode

    CANx->sTxMailBox[Copy_unit8MailBoxNumber].TDTR |= (unit32)CAN_TDT0R_TGT; // set the bit

  }
  else if (NewState == DISABLE)
  {

    CANx->MCR &= ~(unit32)CAN_MCR_TTCM;     // Disable the TTCM mode

    CANx->sTxMailBox[Copy_unit8MailBoxNumber].TDTR &= (unit32)~CAN_TDT0R_TGT; //reset thebit

  }

	else
    {
	/*wrong input state*/
	}
}

void USB_HP_CAN1_TX0_IRQHandler (void)
	{
                                  /*Check For Request completed mailbox */

		CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving


  if (CAN1->TSR & CAN_TSR_RQCP0)   // request completed mbx 0
		{

    CAN1->TSR |= CAN_TSR_RQCP0;                    // reset request complete mbx 0

    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt

  }
	else if(CAN1->TSR & CAN_TSR_RQCP1)          // request completed mbx 1
{

	  CAN1->TSR |= CAN_TSR_RQCP1;                    // reset request complete mbx 0

    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt

}
else if(CAN1->TSR & CAN_TSR_RQCP2)          // request completed mbx 1
{

	  CAN1->TSR |= CAN_TSR_RQCP2;                    // reset request complete mbx 0

    CAN1->IER &= ~CAN_IER_TMEIE;                   // disable  TME interrupt
}

else
{
     /*no data t capture*/
}

}
/************************************************END OF FUNCTION*******************************/
void USB_LP_CAN1_RX0_IRQHandler (void) {

		CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving


  if (CAN1->RF0R & CAN_RF0R_FMP0)  // CHECK IF fifo 0 is not empty
	{
		CAN_VoidReceive ( CAN1 , CAN_FIFO0 ,&RxMessage);                       // read the message of FIFO 0
	}
	else if (CAN1->RF1R & CAN_RF1R_FMP1)       // CHECK IF fifo 1 is not empty
	{
	CAN_VoidReceive ( CAN1 , CAN_FIFO1,&RxMessage);                  // read the message	of FIFO 1
	}
}
/************************************************END OF FUNCTION*******************************/
static void Can_voidSynRecieveArray( CAN_TypeDef* CANx, unit8 Copy_unit8FifoNumber, unit8 *recData, unit8 NumOfBytes)
{

  unit8 counter1 = ZERO ;
	unit8 Frame_Number = (NumOfBytes / FRAME_DATA) ;

	for(unit8 Data_Counter1 = ZERO ; Data_Counter1 < Frame_Number ; Data_Counter1++)
	{

		CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

		while (!(CAN1->RF0R & CAN_RF0R_FMP0));  // wait until fifo 0 become pending

		CAN_VoidReceive ( CANx , Copy_unit8FifoNumber ,&RxMessage);                       // read the message of FIFO 0

		for( unit8 Data_Counter = ZERO ; Data_Counter < FRAME_DATA ; Data_Counter++)
		{

			recData[counter1++]= RxMessage.DATA[Data_Counter];
		}
	}

}

/************************************************END OF FUNCTION*******************************/
void Can_uint32SynRecieveWord(CAN_TypeDef* CANx, unit8 Copy_unit8FifoNumber, unit8* recData)
{


  CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

  while (!(CAN1->RF0R & CAN_RF0R_FMP0));  // wait until fifo 0 become pending

	CAN_VoidReceive ( CANx , Copy_unit8FifoNumber ,&RxMessage);   // read the message of FIFO 0

	//Copy_unit32Data = (unit32)((RxMessage.DATA[BYTE_THREE]<<24) | (RxMessage.DATA[BYTE_TWO]<<16) | (RxMessage.DATA[BYTE_ONE]<<8) | (RxMessage.DATA[BYTE_ZERO]) ) ;
	recData[0] =  RxMessage.DATA[BYTE_ZERO];
	recData[1] =  RxMessage.DATA[BYTE_ONE];
	recData[2] =  RxMessage.DATA[BYTE_TWO];
	recData[3] =  RxMessage.DATA[BYTE_THREE];
}

/************************************************END OF FUNCTION*******************************/
long long timeout = 3000000;
ReturnStatus Can_unit8SynRecieveNumOfByte( CAN_TypeDef* CANx, unit8 Copy_unit8FifoNumber, unit8 *recData, unit8 NumOfBytes)
{
  CanRxMsg   RxMessage;               // CAN messge   struct  for  receiving

   while (!(CAN1->RF0R & CAN_RF0R_FMP0))
   {
	   if (timeout == 0)
		   return NOT_OK;

	   timeout--;
   }
   timeout = 3000000;
   // wait until fifo 0 become pending

	CAN_VoidReceive ( CANx , Copy_unit8FifoNumber ,&RxMessage);   // read the message of FIFO 0
	if ( (NumOfBytes <= 8 )&&(NumOfBytes > 0 ))
	{
		for (int i = 0; i < NumOfBytes ; i++)
		{
			recData[i] = (unit8)((RxMessage.DATA[i])) ;
		}
	}
	else if ( NumOfBytes > 8)
	{
		Can_voidSynRecieveArray(CANx, Copy_unit8FifoNumber, recData, NumOfBytes);
	}
return OK;
}
