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
; Librería de subrutinas para el manejo de mensajes a visualizar en un visualizador LCD.

	CBLOCK
	LCD_ApuntaCaracter		; Indica la posición del carácter a visualizar
					; respecto del comienzo de todos los mensajes,
					; (posición de la etiqueta "Mensajes").
	LCD_ValorCaracter			; Código ASCII del carácter a 
	ENDC				; visualizar.

; Los mensajes tienen que estar situados dentro de las 256 primeras posiciones de la 
; memoria de programa, es decir, no pueden superar la dirección 0FFh.

; Subrutina "LCD_Mensaje" ---------------------------------------------------------------
;
; Visualiza por pantalla el mensaje apuntado por el registro W.
;
; Los mensajes deben localizarse dentro de una zona encabezada por la etiqueta "Mensajes" y que
; tenga la siguiente estructura:
;
; Mensajes				; ¡Etiqueta obligatoria!
;	addwf	PCL,F
; Mensaje0				; Posición inicial del mensaje.
;	DT ".. ..", 0x00			; Mensaje terminado en 0x00.
; Mensaje1
;	...	
;	...
; FinMensajes
;
; La llamada a esta subrutina se realizará siguiendo este ejemplo:
;
;	movlw	Mensaje0			; Carga la posición del mensaje.
;	call	LCD_Mensaje		; Visualiza el mensaje.
;
LCD_Mensaje
	movwf	LCD_ApuntaCaracter	; Posición del primer carácter del mensaje.
	movlw	Mensajes			; Halla la posición relativa del primer carácter
	subwf	LCD_ApuntaCaracter,F	; del mensaje respecto de etiqueta "Mensajes".
	decf	LCD_ApuntaCaracter,F	; Compensa la posición que ocupa "addwf PCL,F".
LCD_VisualizaOtroCaracter
	movf	LCD_ApuntaCaracter,W
	call	Mensajes			; Obtiene el código ASCII del carácter apuntado.
	movwf	LCD_ValorCaracter		; Guarda el valor de carácter.
	movf	LCD_ValorCaracter,F	; Lo único que hace es posicionar flag Z. En caso
	btfsc	STATUS,Z		; que sea "0x00", que es código indicador final	
	goto	LCD_FinMensaje		; de mensaje, sale fuera.
LCD_NoUltimoCaracter
	call	LCD_Caracter		; Visualiza el carácter ASCII leído.
	incf	LCD_ApuntaCaracter,F	; Apunta a la posición del siguiente carácter 
	goto	LCD_VisualizaOtroCaracter	; dentro del mensaje.
LCD_FinMensaje
	return				; Vuelve al programa principal.

; Subrutina "LCD_MensajeMovimiento" -----------------------------------------------------
;
; Visualiza un mensaje de mayor longitud que los 16 caracteres que pueden representarse
; en una línea, por tanto se desplaza a través de la pantalla.
;
; En el mensaje debe dejarse 16 espacios en blanco, al principio y al final para
; conseguir que el desplazamiento del mensaje sea lo más legible posible.
;
	CBLOCK	
	LCD_CursorPosicion		; Contabiliza la posición del cursor dentro de la
	ENDC				; pantalla LCD

LCD_MensajeMovimiento
	movwf	LCD_ApuntaCaracter	; Posición del primer carácter del mensaje.
	movlw	Mensajes			; Halla la posición relativa del primer carácter
	subwf	LCD_ApuntaCaracter,F	; del mensaje respecto de la etiqueta "Mensajes".
	decf	LCD_ApuntaCaracter,F	; Compensa la posición que ocupa "addwf PCL,F".
LCD_PrimeraPosicion
	clrf	LCD_CursorPosicion	; El cursor en la posición 0 de la línea.
	call	LCD_Borra		; Se sitúa en la primera posición de la línea 1 y
LCD_VisualizaCaracter			; borra la pantalla.
	movlw	LCD_CaracteresPorLinea	; ¿Ha llegado a final de línea?
	subwf	LCD_CursorPosicion,W
	btfss	STATUS,Z
	goto	LCD_NoEsFinalLinea

LCD_EsFinalLinea
	call	Retardo_200ms		; Lo mantiene visualizado durante este tiempo.
	call	Retardo_200ms
	movlw	LCD_CaracteresPorLinea-1; Apunta a la posición del segundo carácter visualizado
	subwf	LCD_ApuntaCaracter,F	; en pantalla, que será el primero en la siguiente
	goto	LCD_PrimeraPosicion	 ; visualización de línea, para producir el efecto
LCD_NoEsFinalLinea			; de desplazamiento hacia la izquierda.
	movf	LCD_ApuntaCaracter,W
	call	Mensajes			; Obtiene el ASCII del carácter apuntado.
	movwf	LCD_ValorCaracter		; Guarda el valor de carácter.
	movf	LCD_ValorCaracter,F	; Lo único que hace es posicionar flag Z. En caso
	btfsc	STATUS,Z		; que sea "0x00", que es código indicador final	
	goto	LCD_FinMovimiento	; de mensaje, sale fuera.
LCD_NoUltimoCaracter2
	call	LCD_Caracter		; Visualiza el carácter ASCII leído.
	incf	LCD_CursorPosicion,F	; Contabiliza el incremento de posición del 
					; cursor en la pantalla.
	incf	LCD_ApuntaCaracter,F	; Apunta a la siguiente posición por visualizar.
	goto	LCD_VisualizaCaracter	; Vuelve a visualizar el siguiente carácter
LCD_FinMovimiento			; de la línea.
	return				; Vuelve al programa principal.
	

