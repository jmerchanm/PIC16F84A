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
; ** CARGANDO.INC *************************************************
; **               Francisco Javier Merchán Macías               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telemática                      **
; *****************************************************************
; ** Descripción:                                                **
; **                                                             **
; **   Libreria para cargar los datos a enviar                   **
; **                                                             **
; **                                                             **
; **                                                             **
; *****************************************************************

Cargando
	call	Retardo_2s
	movlw	0x08
	movwf	ContadorEnvio			;Cargamos el contador con un 8
	clrf	ENVIO
	call	LCD_Inicializa			;Hacemos un cuadro para meter los valores que carguemos.
	call	LCD_Borra
	movlw	0x03
	call	LCD_PosicionLinea1
	movlw	'['
	call	LCD_Caracter
	movlw	0x0c
	call	LCD_PosicionLinea1
	movlw	']'
	call	LCD_Caracter
	movlw	0x04
	call	LCD_PosicionLinea1

CargandoInicio						;Leemos el interruptor y lo cargamos en un registro.
	btfsc	Pulsador
	goto	CargandoUno
	goto	CargandoCero

CargandoUno
	bsf		STATUS,C
	rrf		ENVIO,1
;   ESCRIBE UN 1 EN LA PANTALLA LCD
	movlw	'1'
	call	LCD_Caracter
	call	Retardo_2s
;   DECREMENTAMOS EL CONTADOR
	decfsz	ContadorEnvio,1
	goto	CargandoInicio
	goto	CargandoFin

CargandoCero
	bcf		STATUS,C
	rrf		ENVIO,1
;   ESCRIBE UN 0 EN LA PANTALLA LCD
	movlw	'0'
	call	LCD_Caracter
	call	Retardo_2s
;   DECREMENTAMOS EL CONTADOR
	decfsz	ContadorEnvio,1
	goto	CargandoInicio
CargandoFin
	call	LCD_Borra
	call	LCD_Linea2
	movlw	MensajeDatCargado
	call	LCD_Mensaje
	call	Retardo_2s

	return