; * Práctica de Sistemas Electrónicos Digitales de la Ingeniería Técnica
; * de Telecomunicación, especialidad Telemática.
; *
; * Copyright 2008 Francisco Javier Merchán Macías,
; *                Fátima Romero Romero,
; *                Esmeralda Rubio Parra.
; *
; * This program is free software: you can redistribute it and/or modify
; * it under the terms of the GNU Affero General Public License as published
; * by the Free Software Foundation, either version 3 of the License, or
; * (at your option) any later version.
; *
; * This program is distributed in the hope that it will be useful,
; * but WITHOUT ANY WARRANTY; without even the implied warranty of
; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; * GNU Affero General Public License for more details.
; *
; * You should have received a copy of the GNU Affero General Public License
; * along with this program.  If not, see <http://www.gnu.org/licenses/>.
; *
; ** PLANTILLA.ASM ************************************************
; **               Francisco Javier Merchán Macías               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telemática                      **
; *****************************************************************
; ** Descripción práctica:                                       **
; **                                                 .           **
; **   Emisor y receptor.                                        **
; **                                                             **
; **                                                             **
; **                                                             **
; *****************************************************************

; ZONA DE DATOS **********************************************************************

	__CONFIG _CP_OFF& _WDT_OFF&_PWRTE_ON&_XT_OSC	; Configuración para el grabador

	LIST P=16F84A					; Indica el tipo de mC utilizado.
	INCLUDE <P16F84A.INC>			; Incluye las definiciones de registros y constantes asociadas a este mC.

	CBLOCK 0x0C			;La zona de memoria de usuario comienza en esta dirección de memoria RAM de datos
	ENVIO
	ContadorEnvio
	ContadorEmisor		;Contador para ENVIO.INC
	ContadorReceptor	;Contador para RECIBIR.INC
	DatosRecibido		;Para guardar el dato en RECIBIR.INC
	ENDC

;   CONSTANTES ****************************************************
	#DEFINE Pulsador		PORTA,4
	#DEFINE PuertaEnviar	PORTB,1
	#DEFINE PuertaRecibir	PORTB,0

;ZONA DE CODIGO **********************************************************************
	ORG 0

Inicio
;   CONFIGURACIÓN DE ENTRADAS Y SALIDAS ***************************
	bsf		STATUS, RP0			;Acceso al banco 1
	bcf		TRISB,1		;RB1 como salida. (PUERTA DE ENVIO DE DATOS)
	bsf		TRISB,0		;RB0 como entrada. (PUERTA DE RECEPCION DE DATOS)
	bsf		TRISA,3		;RA3 como entrada (INTERRUPTOR)
	bsf		TRISA,4		;RA3 como entrada (INTERRUPTOR)
	bcf 	STATUS, RP0			;Acceso al banco 0

;Aquí empieza el programa en sí...
Principal
	call	Presentacion
	call	Elegir
Dormir
	sleep
	goto	Dormir

;-----------INICIO Instrucciones para el inicio y presentacion---------------------------------------
Presentacion
	call	LCD_Inicializa
	call	LCD_Borra
	movlw	MensajeBienvenida
	call	LCD_Mensaje
	call	Retardo_2s
	movlw	0x40
	call	LCD_PosicionLinea1
	movlw	MensajeElige
	call	LCD_Mensaje
	call	Retardo_2s
	return
;-----------FIN Instrucciones para el inicio y presentacion---------------------------------------

; Mensajes ----------------------------------------
Mensajes
	addwf	PCL,F
MensajeBienvenida				;En subrutina Presentacion de PLANTILLA.ASM
	DT "Practica SED", 0x00
MensajeElige					;En subrutina Presentacion de PLANTILLA.ASM
	DT "Elige TX o RX:", 0x00
Mensaje0						;En subrutina de ELIGIR.INC
	DT "0=Recept", 0x00
Mensaje1						;En subrutina de ELIGIR.INC
	DT "1=Emisor", 0x00
MensajeDatCargado				;En subrutina de CARGANDO.INC
	DT "Datos Cargados", 0x00
MensajeEmitiendo				;En subrutina de EMITIR.INC
	DT "EMITIENDO RB1", 0x00
MensajeRecibiendo				;En subrutina de RECIBIR.INC
	DT "RECIBIENDO RB0", 0x00
MensDatosEnv					;En subrutina de EMITIR.INC
	DT "Datos ENVIADOS", 0x00
RecCorrect						;En subrutina de RECIBIR.INC
	DT "RECEPCCION OK", 0x00
MensajeBitStart					;En subrutina de RECIBIR.INC
	DT "Bit Start", 0x00
MensajeBStop					;En subrutina de RECIBIR.INC
	DT "Bit Stop ", 0x00

	INCLUDE	<LCD_4BIT.INC>
	INCLUDE <LCD_MENS.INC>
	INCLUDE <RETARDOS.INC>
	INCLUDE <CARGANDO.INC>		;Includes Propios
	INCLUDE <ELEGIR.INC>
	INCLUDE <EMITIR.INC>
	INCLUDE <RECIBIR.INC>

	END