	// Test: ISZ and EISZ with variant coverage and device boundaries

	// --- Labels
label1:
	ISZ label1
	ISZ label2
label2:

	// --- Dot offset
	ISZ .-1

	// --- Addressing modes
	ISZ 5, 0
	ISZ .+5, 1
	ISZ 5, 2
	ISZ 5, 3

	// --- Range checks
	ISZ 0, 0
	ISZ 255, 0
	ISZ .-128, 1
	ISZ .+127, 1
	ISZ -128, 2
	ISZ 127, 2
	ISZ -128, 3
	ISZ 127, 3

	// --- Indirect addressing
	ISZ @0123, 0
