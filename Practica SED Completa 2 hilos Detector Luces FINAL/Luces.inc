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
; ** LUCES.INC ****************************************************
; **               Francisco Javier Merchán Macías               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telemática                      **
; *****************************************************************
; ** Descripción práctica:                                       **
; **                                                 .           **
; **   Procedimiento para generar luces variadas en el banco de  **
; **  LED y en el display de 7 segmentos.                        **
; **                                                             **
; **                                                             **
; *****************************************************************
LucesInicio
	bsf	STATUS,RP0
	clrf	PORTB
	bcf	STATUS,RP0
LucesContinua
	movlw	b'00000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000001'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01000010'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00100100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00011000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00111100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01111110'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11111111'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11100111'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11000011'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000001'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000001'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11000011'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11100111'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11111111'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'11111111'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01111110'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00111100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00011000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00100100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01000010'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000001'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000001'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000010'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00001000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00010000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00100000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'10000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'01000000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00100000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00010000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00001000'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000100'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000010'
	movwf	PORTB
	call	Retardo_200ms
	movlw	b'00000001'
	movwf	PORTB
	call	Retardo_200ms
	goto LucesContinua