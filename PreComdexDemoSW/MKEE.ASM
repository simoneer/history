subttl IBM CONFIDENTIAL RESTRICTED - MKEE
;-------------------------------------------------------------------------
;
;       Move the ICE -> EEPROM space.
;
;       Will map 128K of the upper 1/2MB area where the EEPROM is into
;       the C0000 to DFFFF memory area.
;
;       Default is moving only the last 64K ICE into the last 64K EEPROM.
;
;-------------------------------------------------------------------------
IF1
 %OUT Pass 1 assembling
ELSE
 %OUT Pass 2 assembling
ENDIF
CR      EQU     0DH
LF      EQU     0AH                     ;Common constants
EOF     EQU     1AH
TAB     EQU     09H
BELL    EQU     07H
TRUE    EQU     -1
FALSE   EQU     0
;-------------------------------------------------------------------------
;
;       [[ Prefix area ]]
;
CODE    SEGMENT WORD    PUBLIC 'CODE'
        ASSUME  CS:CODE,DS:CODE,ES:CODE,SS:nothing
;
PREFIX  DB      256 DUP(?)
EnvSeg     EQU  PREFIX+2CH              ;Environment pointer
FCB1       EQU  PREFIX+5CH              ;FCB1 on entry, used also with 'dos'
FCB2       EQU  PREFIX+6CH              ;FCB2 on entry, used also with 'dos'
InputLine  EQU  PREFIX+81H              ;command line user used to load me.

;

; Setup Vadem VG230 internal register
VOUT    MACRO   X1,Y1                   ; Address/data to send to VG230
        Mov     Al,X1                   ; Point index to proper reg
        Out     26h,al                  ; Setup the index
        Mov     Al,Y1                   ; Get the data to send out
        Out     27h,al                  ; Set the register
        ENDM
; Get data from Vadem VG230 internal register
VIN     MACRO   X1                      ; Address to get from VG230
        Mov     Al,X1                   ; Point index to proper reg
        Out     26h,al                  ; Setup the index
        Jmp     $+2                     ; Slight delay just in case
        In      Al,27h                  ; Get the register
        ENDM
; Setup mapping address registers
;
;               Memory map starting address:
;          xx xxxx xxxx xx00 0000 0000 0000
;               EEPROM 16k block ##
;          00 0001 000x xx00 0000 0000 0000
;               0100 0xxx
;
; Format is: SEGMENT, Block#
SETMAP  MACRO   x,y
        Mov     Al,x                    ; Point mapping index to Segment #
        Out     6Ch,Al
        Mov     Al,90h                  ; Enable RAM map
        Out     6Fh,Al
        Mov     Al,y+20h                ; Setup block number at upper 1/2MB area
        Out     6Eh,Al
        ENDM
        org     0100h
EEProm         Proc    Near
;-------------------------------------------------------------------------
;       Setup areas to be moved....
;-------------------------------------------------------------------------
Main:   Mov     Ax,0C000h               ; Destination segment
        Mov     Es,Ax
        Mov     Ax,0F000h               ; Source segment
        Mov     Ds,Ax
;-------------------------------------------------------------------------
;       Set up 512K x 8 SRAM mode (8 bit bus)
;-------------------------------------------------------------------------
        Vout    04h,82h                 ; Enable, 1 Bank, 512x8 SRAM mode
        Vout    05h,0E1h                ; 8bit: RAM & ROM, Normal Rfsh

;-------------------------------------------------------------------------
;       Setup the mapping:
;               First 128K of 2MB area -> C000:0 to D000:FFFF
;               Each SETMAP below sets 16K of the area
;-------------------------------------------------------------------------
        SETMAP  0C0h,0
        SETMAP  0C4h,1
        SETMAP  0C8h,2
        SETMAP  0CCh,3
        SETMAP  0D0h,4
        SETMAP  0D4h,5
        SETMAP  0D8h,6
        SETMAP  0DCh,7
;------------------------------------------------------------------------

        Mov     byte ptr Es:[5555h],0AAh ;  protect mode eeprom
        Mov     byte ptr Es:[0AAAAh],55h
        Mov     byte ptr Es:[5555h],080h
        Mov     byte ptr Es:[5555h],0AAh
        Mov     byte ptr Es:[0AAAAh],55h
        Mov     byte ptr Es:[5555h],20h
;
        ; Delay 10ms via Vadem time base register
        VIN     31h
        Add     Al,256/5                ; Increase by amount it will get to
                                        ; in 10ms
        Mov     Bl,Al                   ; Hold first value for comparison
Wt1:    VIN     31h
        Cmp     Al,Bl                   ; Got to new value (or past it) yet?
        Jne     Wt1
;
;-------------------------------------------------------------------------
;       Now Move the ICE -> EEPROM
;-------------------------------------------------------------------------
        Mov     Di,0                    ; Destination offset
        Mov     Si,0                    ; Source offset
        Cld
Next:   Mov     Cx,8                    ; Move 8 bytes within 30us (OK?)
MoreDat: Rep Movsb                      ; ICE -> EEPROM

        ; Delay 10ms via Vadem time base register
        VIN     31h
        Add     Al,48h                  ; Increase by amount it will get to
                                        ; in 15.4ms
        Mov     Bl,Al                   ; Hold first value for comparison
Wait10: VIN     31h
        Cmp     Al,Bl                   ; Got to new value (or past it) yet?
        Jne     Wait10

Ck2:    cmp     Si,0                    ; Gone through all 64K of ICE?
        Jne     Next
        Hlt                             ; Done -- turn on ICE's halt light

EEProm          Endp
CODE    Ends
        End     Main
