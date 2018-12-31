	AORG 	>6000

; Cartridge ROM header
	BYTE	>AA		; Standard Header
        BYTE	>01		; version
    	BYTE	>01		; # of application programs
	BYTE	>00		; reserved
    	DATA	>0000 		; power up list (unused)
    	DATA	menua 		; program menu entry list
	DATA	>0000		; unused - DSR list
	DATA	>0000		; unused - subprogram list
	DATA	>0000		; unused - interrupt list
	DATA	>0000		; unused - ???

; ForceBASIC program entry
menua:
	DATA	>0000		; next list entry
	DATA	_cart		; asm entry
	BYTE	9		; length of menu string
	TEXT	"BANK TEST"	; menu text
	EVEN

_cart:
	CLR	@>6000
	B	@_start

	

