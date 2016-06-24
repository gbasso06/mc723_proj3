import sys
import random

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

if len(sys.argv) != 3:
	print "Wrong number of arguments. Please, inform the width and depth of the matrix."
	exit(1)

n = int(sys.argv[1])
m = int(sys.argv[2])

matriz = [[0 for x in range(m)] for y in range(n)] 

for i in range(0, n):
	for j in range(0, m):
		matriz[i][j] = random.randint(0,100);

print "resultado: \n\n";

print("int matriz1[N][N] = {")
for i in range(0, n):
	print "\t{ ",
	for j in range(0, m):
		if (j != m-1):
			print (str(matriz[i][j]) + ", "),
		else:
			print (str(matriz[i][j])),
	if i != n-1:
		print "},"
	else:
		print "}"
	
print "};"
