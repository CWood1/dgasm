	// Test: JMP and EJMP with variant coverage and device boundaries

	// --- Labels
label1:
	JMP label1
	JMP label2
label2:
	EJMP label2
	EJMP label3
label3:

	// --- Dot offset
	JMP .-1
	EJMP .-1

	// --- Addressing modes
	JMP 5, 0
	JMP .+5, 1
	JMP 5, 2
	JMP 5, 3

	EJMP 5, 0
	EJMP .+5, 1
	EJMP 5, 2
	EJMP 5, 3

	// --- Range checks
	JMP 0, 0
	JMP 255, 0
	JMP .-128, 1
	JMP .+127, 1
	JMP -128, 2
	JMP 127, 2
	JMP -128, 3
	JMP 127, 3

	EJMP 0, 0
	EJMP 077777, 0
	EJMP .-037777, 1
	EJMP .+037777, 1
	EJMP -040000, 2
	EJMP 037777, 2
	EJMP -040000, 3
	EJMP 037777, 3

	// --- Indirect addressing
	JMP @0123, 0
	EJMP @0123, 0
