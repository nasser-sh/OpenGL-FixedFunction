
PROJECTS = \
	GLApp \
	P01-Triangle \
    P02-RotatingQuad

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

clean :
	make --no-print-directory -C GLApp -f Makefile clean
	make --no-print-directory -C P01-Triangle -f Makefile clean
	make --no-print-directory -C P02-RotatingQuad -f Makefile clean
