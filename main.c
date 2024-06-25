/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

int32 Lectura;
volatile float32 Tension_ADC[4];
char A[12],B[12],C[12],D[12]; /*Usare el str2 para indicar el numero de canal al cual pertenece la info */
/*volatile float32 str2 = 1; Esta configuracion ya no sera utilizada, mejor pondre a,b,c,d*/

CY_ISR(Enviar)
{    
    /*---------------------Seccion de lectura de la ADC_1, pero de la primer señal---------------------*/
    AMux_1_FastSelect(0);  /*Esto realiza toda la diferencia ya que solo tengo una ADC disponible*/
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    Lectura = ADC_1_GetResult32();
    ADC_1_StopConvert();
    
    /*Termina la lectura de datos y empiezo la conversion*/
    Tension_ADC[0] = ADC_1_CountsTo_Volts(Lectura);    
    sprintf(A,"%.3f",Tension_ADC[0]);

    
    /*---------------------------------Lectura del segundo canal---------------------------------------*/
    AMux_1_FastSelect(1);  /*Esto realiza toda la diferencia ya que solo tengo una ADC disponible*/
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    Lectura = ADC_1_GetResult32();
    ADC_1_StopConvert();
        
    /*Termina la lectura de datos y empiezo la conversion*/
    Tension_ADC[1] = ADC_1_CountsTo_Volts(Lectura);    
    sprintf(B,"%.3f",Tension_ADC[1]);

    
    /*---------------------------------Lectura del tercer canal---------------------------------------*/
    AMux_1_FastSelect(2);  /*Esto realiza toda la diferencia ya que solo tengo una ADC disponible*/
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    Lectura = ADC_1_GetResult32();
    ADC_1_StopConvert();
        
    /*Termina la lectura de datos y empiezo la conversion*/
    Tension_ADC[2] = ADC_1_CountsTo_Volts(Lectura);    
    sprintf(C,"%.3f",Tension_ADC[2]);

    
    /*--------------------------------Lectura del cuarto sensor---------------------------------------*/
    
    AMux_1_FastSelect(3);  /*Esto realiza toda la diferencia ya que solo tengo una ADC disponible*/
    ADC_1_StartConvert();
    ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
    Lectura = ADC_1_GetResult32();
    ADC_1_StopConvert();
        
    /*Termina la lectura de datos y empiezo la conversion*/
    Tension_ADC[3] = ADC_1_CountsTo_Volts(Lectura);    
    sprintf(D,"%.3f \n",Tension_ADC[3]);
    
    
    /*En vez de realizar la cuarta lectura, se recomineda hacer la interpolacion
    Tension_ADC[2] = Tension_ADC[3] + Tension_ADC[1] - Tension_ADC[0]; //D + B - A
    sprintf(C,"%.3f",Tension_ADC[2]);*/
    
    
    /*Envio los datos*/
    //UART_PutString("A \n \r");/*numero del sensor*/
    //UART_PutString(A);/*Valor de la medicion*/
    //UART_PutString("B \n \r");/*numero del sensor*/
    //UART_PutString(B);/*Valor de la medicion*/
    //UART_PutString("C \n \r");/*numero del sensor*/
    //UART_PutString(C);/*Valor de la medicion*/
    //UART_PutString("D \n \r");/*numero del sensor*/
    //UART_PutString(D);/*Valor de la medicion*/
    
    /*Envio los datos*/
    UART_PutString("A ");/*numero del sensor*/
    UART_PutString(A);/*Valor de la medicion*/
    UART_PutString(" B ");/*numero del sensor*/
    UART_PutString(B);/*Valor de la medicion*/
    UART_PutString(" C ");/*numero del sensor*/
    UART_PutString(C);/*Valor de la medicion*/
    UART_PutString(" D ");/*numero del sensor*/
    UART_PutString(D);/*Valor de la medicion*/
}

int main(void)
{
    CyGlobalIntEnable;
    AMux_1_Start();
    PWM_1_Start();
    ADC_1_Start(); 
    UART_Start();
    isr_Envio_StartEx(Enviar);
    
    for(;;)
    {        
        
    }
}

/* [] END OF FILE */
