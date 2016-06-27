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

; ** EMITIR.INC ***************************************************
; **               Francisco Javier Merchán Macías               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telemática                      **
; *****************************************************************
; ** Descripción:                                                **
; **                                                             **
; **   Emitir									                 **
; **                                                             **
; **       El registro que contiene los datos es ENVIO           **
; **  PuertaEnviar:  Emitimos por RB1                            **
; **  PuertaRecibir: Recibimos por RB2                           **
; *****************************************************************

Emitir
; Comprobamos si el receptor es un receptor o emisor, para evitar problemas de emisión
	movlw	0x08
	movwf	ContadorEmisor

; Empezamos a enviar el bit START
	clrw						;Ponemos mensaje EMITIENDO
	call	LCD_Borra
	movlw	MensajeEmitiendo
	call	LCD_Mensaje
	call	Retardo_1s

;PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA
	bsf		TRISB,0				;Ponemos a 1 las puertas de salida
	bsf		TRISB,1				;Ponemos a 1 las puertas de salida
;PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA PRUEBA
	
	bcf		PuertaEnviar				;Enviamos un 0. BIT de START
	call	Retardo_1s

; Emitimos la cadena almacenada
ComenzamosAEmitir
	rrf		ENVIO,1
	btfsc	STATUS,C
	goto	EnviarUno			;Envia un 1
	goto	EnviarCero			;Envia un 0

EnviarUno
	bsf		PuertaEnviar
	call	Retardo_1s
	decfsz	ContadorEmisor,F
	goto	ComenzamosAEmitir
	goto	EmitirFIN

EnviarCero	
	bcf		PuertaEnviar
;	call	Retardo_5s
	call	Retardo_1s
	decfsz	ContadorEmisor,F
	goto	ComenzamosAEmitir
;	goto	EmitirFIN			; No hace falta esta instrucción porque tenemos el codigo debajo.

EmitirFIN
;Ponemos el BIT de STOP
	bsf		PuertaEnviar
	call	Retardo_2s
	call	LCD_Borra
	movlw	MensDatosEnv
	call	LCD_Mensaje
	call	Retardo_2s
	return