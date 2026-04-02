	// Test: JMP and EJMP with variant coverage and device boundaries

	// --- Labels
label1:
	JMP label1
	JMP label2
label2:

	// --- Dot offset
	JMP .-1

	// --- Addressing modes
	JMP 5, 0
	JMP .+5, 1
	JMP 5, 2
	JMP 5, 3

	// --- Range checks
	JMP 0, 0
	JMP 255, 0
	JMP .-128, 1
	JMP .+127, 1
	JMP -128, 2
	JMP 127, 2
	JMP -128, 3
	JMP 127, 3

	// --- Indirect addressing
	JMP @0123, 0
