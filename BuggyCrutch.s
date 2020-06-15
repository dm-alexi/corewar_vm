.name		"Buggy Crutch"
.comment	"No, you're a towel!"

entry:
	st		r1, 26
	st		r1, 26
	st		r1, 26
	st		r1, 26
	st		r1, 39
lives:
	live	%21
	live	%21
	live	%21
	live	%21
	ld		:entry, r15
	zjmp	%:lives
	st		r2, :entry
splitter:
	live	%21
	fork	%:lives
	ld		:entry, r15
	zjmp	%:splitter
