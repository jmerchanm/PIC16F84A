; * Pr�ctica de Sistemas Electr�nicos Digitales de la Ingenier�a T�cnica
; * de Telecomunicaci�n, especialidad Telem�tica.
; *
; * Copyright 2008 Francisco Javier Merch�n Mac�as,
; *                F�tima Romero Romero,
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
; ** ELEGIR.INC ***************************************************
; **               Francisco Javier Merch�n Mac�as               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telem�tica                      **
; *****************************************************************
; ** Descripci�n:                                                **
; **                                                             **
; **   Libreria para elegir si es emisor o receptor              **
; **                                                             **
; **                                                             **
; **                                                             **
; *****************************************************************

Elegir
	btfss	Pulsador		;Si es 0 ejecuta la siguiente instrucci�n, si es 1 salta la instrucci�n
	goto	ElegirEsCero

ElegirNoEsCero				;Esto es el EMISOR
	call	LCD_Borra
	movlw	Mensaje1
	call	LCD_Mensaje
	call	Retardo_2s

	call	Cargando
	call	Emitir

	goto	ElegirFIN

ElegirEsCero				;Este es el RECEPTOR
	call	LCD_Borra
	movlw	Mensaje0
	call	LCD_Mensaje
	call	Retardo_2s

	call	Recibir
	goto	ElegirFIN

ElegirFIN
	return