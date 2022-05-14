void sensores()
{

  //************* Lectura de sensor de Voltaje *****************************

  voltaje = random(116,120); // Se genera un numero aleatorio entre 1 y 200

  //voltaje = map(voltaje, 0, 4095, 0, 130);

  //************** Lectura de sensor de Corriente******************************
  
  //corriente = analogRead(4);
  corriente = random(0.1,10);

  //************** Calculo de Potencia *****************************************
  
  potencia = (corriente * voltaje)/1000;
  
  //****************************************************************************
/*
Serial.print("Voltaje: ");
Serial.print(voltaje);
Serial.print(" Corriente: ");
Serial.print(corriente);
Serial.print(" Potencia: ");
Serial.println(potencia);
  */
}
