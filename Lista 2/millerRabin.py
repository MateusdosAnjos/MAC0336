def millerRabin():
	n = int(input("Entre com n: "))
	a = int(input("Entre com a: "))
	s = 0
	if (n%2 == 0):
		print("Numero", n, "é composto")
		return
	else:
		d = n - 1
		while (d%2 == 0):
			d = int(d/2)
			s = s + 1
	print("Imprimindo valores iniciais a e d:")		
	print("a =", a, "d =", d)		
	base = a**d
	print("base = a**d =", a, "^", d)
	r = 0
	print("Entrando no loop r =", r, "s =", s)
	while (r < s):
		mod = (base**(2**r))%n
		print("r =", r, "s =", s, "mod =", mod)
		if(mod == 1):
			print("Número", n, "é composto")
			break
		elif(mod == n-1):
			print("Número", n, "é provavelmente primo")
			return		
		r = r + 1
	print("a =", a, "é testemunha contra a primalidade de n.")	
	return
	
def main():
	millerRabin()
	return
main()	