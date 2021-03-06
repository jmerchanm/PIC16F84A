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
; Librer�a de subrutinas para el manejo de mensajes a visualizar en un visualizador LCD.

	CBLOCK
	LCD_ApuntaCaracter		; Indica la posici�n del car�cter a visualizar
					; respecto del comienzo de todos los mensajes,
					; (posici�n de la etiqueta "Mensajes").
	LCD_ValorCaracter			; C�digo ASCII del car�cter a 
	ENDC				; visualizar.

; Los mensajes tienen que estar situados dentro de las 256 primeras posiciones de la 
; memoria de programa, es decir, no pueden superar la direcci�n 0FFh.

; Subrutina "LCD_Mensaje" ---------------------------------------------------------------
;
; Visualiza por pantalla el mensaje apuntado por el registro W.
;
; Los mensajes deben localizarse dentro de una zona encabezada por la etiqueta "Mensajes" y que
; tenga la siguiente estructura:
;
; Mensajes				; �Etiqueta obligatoria!
;	addwf	PCL,F
; Mensaje0				; Posici�n inicial del mensaje.
;	DT ".. ..", 0x00			; Mensaje terminado en 0x00.
; Mensaje1
;	...	
;	...
; FinMensajes
;
; La llamada a esta subrutina se realizar� siguiendo este ejemplo:
;
;	movlw	Mensaje0			; Carga la posici�n del mensaje.
;	call	LCD_Mensaje		; Visualiza el mensaje.
;
LCD_Mensaje
	movwf	LCD_ApuntaCaracter	; Posici�n del primer car�cter del mensaje.
	movlw	Mensajes			; Halla la posici�n relativa del primer car�cter
	subwf	LCD_ApuntaCaracter,F	; del mensaje respecto de etiqueta "Mensajes".
	decf	LCD_ApuntaCaracter,F	; Compensa la posici�n que ocupa "addwf PCL,F".
LCD_VisualizaOtroCaracter
	movf	LCD_ApuntaCaracter,W
	call	Mensajes			; Obtiene el c�digo ASCII del car�cter apuntado.
	movwf	LCD_ValorCaracter		; Guarda el valor de car�cter.
	movf	LCD_ValorCaracter,F	; Lo �nico que hace es posicionar flag Z. En caso
	btfsc	STATUS,Z		; que sea "0x00", que es c�digo indicador final	
	goto	LCD_FinMensaje		; de mensaje, sale fuera.
LCD_NoUltimoCaracter
	call	LCD_Caracter		; Visualiza el car�cter ASCII le�do.
	incf	LCD_ApuntaCaracter,F	; Apunta a la posici�n del siguiente car�cter 
	goto	LCD_VisualizaOtroCaracter	; dentro del mensaje.
LCD_FinMensaje
	return				; Vuelve al programa principal.

; Subrutina "LCD_MensajeMovimiento" -----------------------------------------------------
;
; Visualiza�un mensaje de mayor longitud que los 16 caracteres que pueden representarse
; en una l�nea, por tanto se desplaza a trav�s de la pantalla.
;
; En el mensaje debe dejarse 16 espacios en blanco, al principio y al final para
; conseguir que el desplazamiento del mensaje sea lo m�s legible posible.
;
	CBLOCK	
	LCD_CursorPosicion		; Contabiliza la posici�n del cursor dentro de la
	ENDC				; pantalla LCD

LCD_MensajeMovimiento
	movwf	LCD_ApuntaCaracter	; Posici�n del primer car�cter del mensaje.
	movlw	Mensajes			; Halla la posici�n relativa del primer car�cter
	subwf	LCD_ApuntaCaracter,F	; del mensaje respecto de la etiqueta "Mensajes".
	decf	LCD_ApuntaCaracter,F	; Compensa la posici�n que ocupa "addwf PCL,F".
LCD_PrimeraPosicion
	clrf	LCD_CursorPosicion	; El cursor en la posici�n 0 de la l�nea.
	call	LCD_Borra		; Se sit�a en la primera posici�n de la l�nea 1 y
LCD_VisualizaCaracter			; borra la pantalla.
	movlw	LCD_CaracteresPorLinea	; �Ha llegado a final de l�nea?
	subwf	LCD_CursorPosicion,W
	btfss	STATUS,Z
	goto	LCD_NoEsFinalLinea

LCD_EsFinalLinea
	call	Retardo_200ms		; Lo mantiene visualizado durante este tiempo.
	call	Retardo_200ms
	movlw	LCD_CaracteresPorLinea-1; Apunta a la posici�n del segundo car�cter visualizado
	subwf	LCD_ApuntaCaracter,F	; en pantalla, que ser� el primero en la siguiente
	goto	LCD_PrimeraPosicion	 ; visualizaci�n de l�nea, para producir el efecto
LCD_NoEsFinalLinea			; de desplazamiento hacia la izquierda.
	movf	LCD_ApuntaCaracter,W
	call	Mensajes			; Obtiene el ASCII del car�cter apuntado.
	movwf	LCD_ValorCaracter		; Guarda el valor de car�cter.
	movf	LCD_ValorCaracter,F	; Lo �nico que hace es posicionar flag Z. En caso
	btfsc	STATUS,Z		; que sea "0x00", que es c�digo indicador final	
	goto	LCD_FinMovimiento	; de mensaje, sale fuera.
LCD_NoUltimoCaracter2
	call	LCD_Caracter		; Visualiza el car�cter ASCII le�do.
	incf	LCD_CursorPosicion,F	; Contabiliza el incremento de posici�n del 
					; cursor en la pantalla.
	incf	LCD_ApuntaCaracter,F	; Apunta a la siguiente posici�n por visualizar.
	goto	LCD_VisualizaCaracter	; Vuelve a visualizar el siguiente car�cter
LCD_FinMovimiento			; de la l�nea.
	return				; Vuelve al programa principal.
	

