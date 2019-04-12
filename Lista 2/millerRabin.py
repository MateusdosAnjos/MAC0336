def millerRabin():
	n = int(input("Entre com n: "))
	a = int(input("Entre com a: "))
	t = 0
	if (n%2 == 0):
		print("Numero", n, "é composto")
		return
	else:
		c = n - 1
		while (c%2 == 0):
			c = int(c/2)
			t = t + 1
	print("Imprimindo valores iniciais t e c:")		
	print("t =", t, "c =", c)		
	base = a**c
	print("base = a**c =", a, "^", c)
	r = 0
	print("Entrando no loop r =", r, "t =", t)
	while (r <= t):
		mod = (base**(2**r))%n
		print("r =", r, "t =", t, "mod =", mod)
		r = r + 1
		
def main():
	millerRabin()
	return
main()	