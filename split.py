f = open("/home/alexander/oldhome/md2.log").readlines()
n = len(f)
n //= 2
for i in range(n, len(f)): 
	print(f[i])
