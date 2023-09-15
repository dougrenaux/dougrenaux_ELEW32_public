;__________________________________________________________________________________
;       Disciplina de Sistemas Embarcados - 2023-2
;       Prof. Douglas Renaux
; __________________________________________________________________________________
;
;		Lab 1
; __________________________________________________________________________________


;------------------------------------------------------------------------------
;
;      GLOBAL Directives
;
;------------------------------------------------------------------------------
				PRESERVE8
                THUMB

;------------------------------------------------------------------------------
;
;      Defines
;
;------------------------------------------------------------------------------
				ALIAS R1, R1_A


;------------------------------------------------------------------------------
;
;      DATA
;
;------------------------------------------------------------------------------
				
Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


                AREA    CONST, READONLY, ALIGN=3       
var_a           DCW     0x5

                AREA    DATA, NOINIT, READWRITE, ALIGN=3       
var_b           SPACE   0x10



;------------------------------------------------------------------------------
;
;      Exception vector
;
;------------------------------------------------------------------------------
; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                ; Top of Stack
                DCD     __main                      ; where execution starts
                DCD     Default_Handler             ; NMI Handler
                DCD     Default_Handler             ; Hard Fault Handler
                DCD     Default_Handler             ; MPU Fault Handler
                DCD     Default_Handler             ; Bus Fault Handler
                DCD     Default_Handler             ; Usage Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     Default_Handler             ; SVCall Handler
                DCD     Default_Handler             ; Debug Monitor Handler
                DCD     0                           ; Reserved
                DCD     Default_Handler             ; PendSV Handler
                DCD     Default_Handler             ; SysTick Handler
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

;------------------------------------------------------------------------------
;
;      CODE
;
;------------------------------------------------------------------------------
                AREA    ||.text||, CODE, READONLY
                ENTRY
                ;IMPORT  _main
                EXPORT  __main           

;------------------------------------------------------------------------------
;      	Function: __main
;		Description: entry point
;------------------------------------------------------------------------------
__main   		PROC
                LDR     R0, =0x5000
				NOP
                
                LDR     R3,=var_a
                LDR     R4,[R3]
				
                LDR     R3,=var_b
                LDR     R4,[R3]

loop            B       loop
                ENDP
                    
;------------------------------------------------------------------------------
;      	Function: Default_Handler
;		Description: Handler for System Exceptions
;------------------------------------------------------------------------------
Default_Handler PROC
                EXPORT  Default_Handler               [WEAK]
                B       .
                ENDP

				ALIGN
                END
