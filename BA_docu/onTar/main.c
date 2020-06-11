void main(void) 
{
  sendUartMsg("Start on target Unit-Test\n\n",sizeof("Start on target Unit-Test\n\n"));
  
  //Testgruppe 1:
  sendUartMsg("Testgruppe 1:\n\n",sizeof("Testgruppe 1:\n\n"));

  assertionEqual_uint8("Test getGreatest default", sizeof("Test getGreatest default") , 33 , getGreatest(12,33));
  assertionEqual_uint8("Test getGreatest upper boarder", sizeof("Test getGreatest upper boarder") , 255 , getGreatest(255,33));
  assertionEqual_uint8("Test getGreatest lower boarder", sizeof("Test getGreatest lower boarder") , 1 , getGreatest(1,0));
  sendUartMsg("\n\n",sizeof("\n\n"));
  
  //Testgruppe 2:
  sendUartMsg("Testgruppe 2:\n\n",sizeof("Testgruppe 1:\n\n"));

  assertionEqual_uint8("Test getLeast default", sizeof("Test getLeast default") , 12 , getLeast(12,33));
  assertionEqual_uint8("Test getLeast upper boarder", sizeof("Test getLeast upper boarder") , 33 , getLeast(255,33));
  assertionEqual_uint8("Test getLeast lower boarder", sizeof("Test getLeast lower boarder") , 0 , getLeast(1,0));
  sendUartMsg("\n\n",sizeof("\n\n"));

  sendUartMsg("Finished on target Unit-Test\n",sizeof("Finished on target Unit-Test\n"));
  sendUartMsg("<Done>\n",sizeof("<Done>\n"));   //Command for Host Sys
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
    HAL_Delay(500);
    /* USER CODE BEGIN 3 */
  }
}

