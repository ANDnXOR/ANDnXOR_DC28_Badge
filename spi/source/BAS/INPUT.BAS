input "What is your name: ", n$

def greeting(a, b)
	return a + " " + b + " by " + n$ + "."
enddef

print greeting("Hello", "world");
