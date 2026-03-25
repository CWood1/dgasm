	// Test: ADC with variant coverage

	// --- Variant sweep - carry
	ADC 0, 0
	ADCZ 0, 0
	ADCO 0, 0
	ADCC 0, 0

	// --- Variant sweep - shift
	ADC 0, 0
	ADCL 0, 0
	ADCR 0, 0
	ADCS 0, 0

	// --- Accumulator sweep (left)
	ADC 0, 0
	ADC 1, 0
	ADC 2, 0
	ADC 3, 0

	// --- Accumulator sweep (right)
	ADC 0, 0
	ADC 0, 1
	ADC 0, 2
	ADC 0, 3

	// --- Variant sweep - shift
	ADC 0, 0
	ADC 0, 0, SKP
	ADC 0, 0, SZC
	ADC 0, 0, SNC
	ADC 0, 0, SZR
	ADC 0, 0, SNR
	ADC 0, 0, SEZ
	ADC 0, 0, SBN
	
	// --- Variant - ignore result
	ADC# 0, 0
