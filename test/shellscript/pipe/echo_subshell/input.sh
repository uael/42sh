echo aaa \
	| (echo bbb 1; cat -e ;echo ccc 1) \
	| (echo bbb 2; cat -e ;echo ccc 2) \
	| (echo bbb 3; cat -e ;echo ccc 3) \
	| (echo bbb 4; cat -e ;echo ccc 4) \
	| (echo bbb 5; cat -e ;echo ccc 5) \
	| (echo bbb 6; cat -e ;echo ccc 6) \
	| (echo bbb 7; cat -e ;echo ccc 7) \
	| (echo bbb 8; cat -e ;echo ccc 8) \
	| (echo bbb 9; cat -e ;echo ccc 9)
