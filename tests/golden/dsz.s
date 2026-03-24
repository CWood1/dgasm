	// Test: DSZ and EDSZ with variant coverage and device boundaries

	// --- Labels
label1:
	DSZ label1
	DSZ label2
label2:
	EDSZ label2
	EDSZ label3
label3:

	// --- Dot offset
	DSZ .-1
	EDSZ .-1

	// --- Addressing modes
	DSZ 5, 0
	DSZ .+5, 1
	DSZ 5, 2
	DSZ 5, 3

	EDSZ 5, 0
	EDSZ .+5, 1
	EDSZ 5, 2
	EDSZ 5, 3

	// --- Range checks
	DSZ 0, 0
	DSZ 255, 0
	DSZ .-128, 1
	DSZ .+127, 1
	DSZ -128, 2
	DSZ 127, 2
	DSZ -128, 3
	DSZ 127, 3

	EDSZ 0, 0
	EDSZ 077777, 0
	EDSZ .-037777, 1
	EDSZ .+037777, 1
	EDSZ -040000, 2
	EDSZ 037777, 2
	EDSZ -040000, 3
	EDSZ 037777, 3

	// --- Indirect addressing
	DSZ @0123, 0
	EDSZ @0123, 0
