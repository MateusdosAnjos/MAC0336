def millerRabin(n, a):
	t = 0
	if (n%2 == 0):
		#print("Numero", n, "é composto")
		return False
	else:
		c = n - 1
		while (c%2 == 0):
			c = int(c/2)
			t = t + 1
	#print("Imprimindo valores iniciais t e c:")		
	#print("t =", t, "c =", c)		
	base = a**c
	#print("base = a**c =", a, "^", c)
	r = 0
	#print("Entrando no loop r =", r, "t =", t)
	mod = 0
	while (r <= t):
		modAnt = mod
		mod = (base**(2**r))%n
		#print("r" + str(r), "=",  mod)
		if (mod == 1):
			if (modAnt == n-1):
				#print("É provavelmente primo")
				return True
		r = r + 1
	#print("É composto")
	return False
		
def main():
	primo = 0
	composto = 0
	n = int(input("Entre com n: "))
	for a in range(2, n-1):
		if(millerRabin(n, a)):
			primo = primo + 1
		else:
			composto = composto + 1	
	print("tentativas =", a)
	print("numero de vezes dado como primo =", primo)
	print("numero de vezes dado como composto =", composto)
	if (composto != 0):
		print("relação primo/composto =", primo/composto)
	if (primo != 0):
		print("relaçao composto/primo =", composto/primo)		
	return
main()	