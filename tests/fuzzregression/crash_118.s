	org 0100
	dev TTI = 010
	dev TTO = 011
Eop:	
	LDA 0, 0, 2
	MOV 0,0,SNR
	JMP 010
	dev TTO = 011
Eop:	
	LDA 0, 0, 2
	MOV 0,0,SNR
	JMP done

outputloop:	
	SKPBZ TTO
	JMP:
	SKPBZ TTO
	JMP done
	HALT

	var hellorld = "Hellorld"
