
PROJECTS = \
	GLApp \
	P01-Triangle \
	P02-RotatingQuad \
	P03-Rings \
	P04-PendulumRoom

.PHONY: all clean $(PROJECTS) 

all : $(PROJECTS)

GLApp : 
	@echo "=== Building GLApp ==="
	make --no-print-directory -C GLApp -f Makefile

P01-Triangle : 
	@echo "=== Building P01-Triangle ==="
	make --no-print-directory -C P01-Triangle -f Makefile

P02-RotatingQuad : 
	@echo "=== Building P02-RotatingQuad ==="
	make --no-print-directory -C P02-RotatingQuad -f Makefile

P03-Rings : 
	@echo "=== Building P03-Rings ==="
	make --no-print-directory -C P03-Rings -f Makefile

P04-PendulumRoom : 
	@echo "=== Building P04-PendulumRoom ==="
	make --no-print-directory -C P04-PendulumRoom -f Makefile

clean :
	make --no-print-directory -C GLApp -f Makefile clean
	make --no-print-directory -C P01-Triangle -f Makefile clean
	make --no-print-directory -C P02-RotatingQuad -f Makefile clean
	make --no-print-directory -C P03-Rings -f Makefile clean
	make --no-print-directory -C P04-PendulumRoom -f Makefile clean
