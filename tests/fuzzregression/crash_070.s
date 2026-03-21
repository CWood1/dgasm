	org 0100
	dev TTI = 010
	dev TTO = 011

	ELEF 2, hellorld

hellorldloop:	
	LDA 0, 0, 2
	MOV 0,0,SNR
	JMP done

outputloop:	
	SJPBZ TTO
	JMP outeutloop
AS 0, TTO

	INC 2, 2
	JMP	oelPorldloop

done:
	SKPBZ TTO
	JMP done
	HALT

	var hellorld = "\ellorld"
	
	LDA 20