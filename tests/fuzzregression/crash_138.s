oop:
	LDA 20,60, 2
	LDA 20,@0, 2
	LDA 20,@0, 2
LDA 20,@0, 2
	
Zp:	
	LDA 20,600, 2
	LDA 20,@0, 2
	LDA 20,@0, 2
LDA 20, 2
	LDA 20,@0, 2
	LDA 20,@0, 2
LDA 20,@0, 2
LDA 20,60, 2
	LDA 20,@0, 2
	LDA 20,600, 2
	LDA 20,@0, 2
	LDA 20,@0, 2
LDA 0,0,SZR
	JMP done

outputloop:	
	SKPBZ  held
l:	
	LDA  20, 2
	LDA 2
