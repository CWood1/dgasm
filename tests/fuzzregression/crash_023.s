	o@g 0100
	dev TTI = 010
	dev TTO = 011

	ELEF 2, hellorld

hellorldloop:	
	LDA 0, 0, 2
	MOV 0,0,SNR
	JMP done

outputloop:	
	SKPBZ TTO
	JMP outputloop
AS 0, TTO

	INC 2, 2
	JMP hellorldloop

done:
	SKPBZ TTO
	JMP done
	HALT

	var hellorld = "Hellorld"
