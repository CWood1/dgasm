	//00, 8, º
	MOV 0,0//0PO

	INC 2, 2
	dw~0, 0, 20
oop:	
	LDA 20,oop,SNR
	JMP donep
