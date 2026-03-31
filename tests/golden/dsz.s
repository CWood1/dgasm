	// Test: DSZ and EDSZ with variant coverage and device boundaries

	// --- Labels
label1:
	DSZ label1
	DSZ label2
label2:

	// --- Dot offset
	DSZ .-1

	// --- Addressing modes
	DSZ 5, 0
	DSZ .+5, 1
	DSZ 5, 2
	DSZ 5, 3

	// --- Range checks
	DSZ 0, 0
	DSZ 255, 0
	DSZ .-128, 1
	DSZ .+127, 1
	DSZ -128, 2
	DSZ 127, 2
	DSZ -128, 3
	DSZ 127, 3

	// --- Indirect addressing
	DSZ @0123, 0
