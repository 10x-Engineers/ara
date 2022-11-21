prepareMakefrag:
	echo "rv64uv_sc_tests = " > Makefrag
	grep $(i) Makefrag >> Makefrag
	cat endOfMakefrag >> Makefrag


restoreMakefrag:
	cat originalMakefrag > Makefrag
