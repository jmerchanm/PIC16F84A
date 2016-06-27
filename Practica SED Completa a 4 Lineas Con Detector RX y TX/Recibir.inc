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
; ** RECIBIR.INC **************************************************
; **               Francisco Javier Merchán Macías               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telemática                      **
; *****************************************************************
; ** Descripción:                                                **
; **                                                             **
; **   Recibir									                 **
; **                                                             **
; **                                                             **
; **  Emitimos por RA1                                           **
; **  Recibimos por RA0 (Para comprobar si el otro es emisor o no**
; *****************************************************************

Recibir
	clrw
	movlw	0x08
	movwf	ContadorReceptor		;Cargamos el contador con un 8

	clrw
	call	LCD_Borra
	movlw	MensajeRecibiendo
	call	LCD_Mensaje
	call	Retardo_2s

;----------------PRUEBA-----------------------
;Comprobar
;	btfsc	PuertaRecibir
;	goto	RecibirUno
;	goto	RecibirCero

;RecibirUno
;	call	LCD_Borra
;	movlw	RecibimosUno
;	call	LCD_Mensaje
;	call	Retardo_100ms
;	goto	Comprobar

;RecibirCero
;	call	LCD_Borra
;	movlw	RecibimosCero
;	call	LCD_Mensaje
;	call	Retardo_100ms
;	goto	Comprobar
;---------------FIN PRUEBA--------------------

;Empezamos a Recibir el bit START
BitStart
;Ponemos a 1 las puertas para evitar Falsos Positivos
;PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA
	bsf		PuertaRecibir				;Ponemos a 1 las puertas de salida
	bsf		PuertaEnviar				;Ponemos a 1 las puertas de salida
	bsf		EntradaComprobar
	bsf		SalidaComprobar
	bsf		TRISB,0
	bsf		TRISB,1
	bsf		TRISB,2
	bsf		TRISB,3
;PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA

	btfsc	PuertaRecibir	;COMPROBAMOS SI ES UN 0 (Bit de Start)
	goto	BitStart		;Si es 1 vuelve a comprobar hasta que le llega un 0
							;Si es 0 POSIBLEMENTE tenemos el bit de Start y continuamos el codigo.
	call	Retardo_200ms
	call	Retardo_200ms
	call	Retardo_100ms	;Esperamos medio segundo para comprobar si es un 0 o no
	btfsc	PuertaRecibir	;VOLVEMOS A COMPROBAR QUE ES UN 0.
	goto	BitStart		;No es el bit de Start, es un error.
	call	LCD_Borra		;Si es el bit de Start lo muestra en pantalla
	call	LCD_Linea1
	movlw	MensajeBitStart
	call	LCD_Mensaje
	call	Retardo_200ms
	call	Retardo_200ms
	call	Retardo_100ms	;Esperamos otro medio segundo
	call	Retardo_200ms	;200ms más para no estar al comienzo del bit, sino un poco más al medio.
	call	LCD_Linea2

DRecibido				;SI ES EL BIT DE START (comenzamos a recibir)
	btfsc	PuertaRecibir
	goto	RecUno
	goto	RecCero

RecUno
;   ESCRIBE UN 1 EN LA PANTALLA LCD
	movlw	'1'
	call	LCD_Caracter
	call	Retardo_1s
;	GUARDAMOS LO QUE RECIBIMOS EN UN REGISTRO
	bsf		STATUS,C
	rrf		DatosRecibido,1
;   DECREMENTAMOS EL CONTADOR
	decfsz	ContadorReceptor,1
	goto	DRecibido				;Ir al inicio de DRecibido o lo que es lo mismo DatoRecibido
	goto	BitStop

RecCero
;   ESCRIBE UN 0 EN LA PANTALLA LCD
	movlw	'0'
	call	LCD_Caracter
	call	Retardo_1s
;	GUARDAMOS LO QUE RECIBIMOS EN UN REGISTRO
	bcf		STATUS,C
	rrf		DatosRecibido,1
;   DECREMENTAMOS EL CONTADOR
	decfsz	ContadorReceptor,1
	goto	DRecibido				;Ir al inicio de DRecibido o lo que es lo mismo DatoRecibido

BitStop
	call	Retardo_1s
	call	LCD_Linea1
	movlw	MensajeBStop
	call	LCD_Mensaje
	call	Retardo_2s

FinReceptor
	call	LCD_Borra
	movlw	RecCorrect
	call	LCD_Mensaje
	call	Retardo_2s

PintarEnLeds
;	call	LCD_OFF				;Apagamos el LCD
;   CONFIGURACIÓN DE ENTRADAS Y SALIDAS ***************************
	bsf		STATUS, RP0			;Acceso al banco 1
	clrf	TRISB				;Todas las líneas del Puerto B como salida
	bcf 	STATUS, RP0			;Acceso al banco 0
;	FIN DE CONFIGURACIÓN DE LAS ENTRADAS Y SALIDAS

;	MOSTRAMOS EL DATO RECIBIDO EN LOS LEDs
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB7_1
	goto	RB7_0
RB7_1	
	bsf		PORTB,7
	goto	RB6_Continua
RB7_0	
	bcf		PORTB,7

RB6_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB6_1
	goto	RB6_0
RB6_1
	bsf		PORTB,6
	goto	RB5_Continua
RB6_0	
	bcf		PORTB,6

RB5_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB5_1
	goto	RB5_0
RB5_1
	bsf		PORTB,5
	goto	RB4_Continua
RB5_0	
	bcf		PORTB,5

RB4_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB4_1
	goto	RB4_0
RB4_1
	bsf		PORTB,4
	goto	RB3_Continua
RB4_0	
	bcf		PORTB,4

RB3_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB3_1
	goto	RB3_0
RB3_1
	bsf		PORTB,3
	goto	RB2_Continua
RB3_0	
	bcf		PORTB,3

RB2_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB2_1
	goto	RB2_0
RB2_1
	bsf		PORTB,2
	goto	RB1_Continua
RB2_0	
	bcf		PORTB,2

RB1_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB1_1
	goto	RB1_0
RB1_1
	bsf		PORTB,1
	goto	RB0_Continua
RB1_0	
	bcf		PORTB,1

RB0_Continua
	rrf		DatosRecibido,1
	btfsc	STATUS,C
	goto	RB0_1
	goto	RB0_0
RB0_1
	bsf		PORTB,0
	goto	RB_Fin
RB0_0	
	bcf		PORTB,0

RB_Fin
	return