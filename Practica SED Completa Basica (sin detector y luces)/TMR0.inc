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
; *****************************************************************
; **               Francisco Javier Merch�n Mac�as               **
; **                     Fatima Romero Romero                    **
; **                     Esmeralda Rubio Parra                   **
; **                       I.T.T.Telem�tica                      **
; *****************************************************************
; ** Descripci�n:                                                **
; **                                                             **
; **   Libreria para cargar los datos a enviar                   **
; **                                                             **
; **                                                             **
; **                                                             **
; *****************************************************************

;Timer0_500us
;	movlw	TMR0_Carga500us
;	movwf	TMR0
;	bcf		INTCON,T0IF
;Timer0_Rebosamiento
;	btfss	INTCON,T0IF
;	goto	Time0_Rebosamiento
	return
