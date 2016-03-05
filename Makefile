
PROJECTS = \
	GLApp \
	P01-Triangle \

.PHONY: all clean $(PROJECTS) 

all : $(PROJECTS)

GLApp : 
	@echo "=== Building GLApp ==="
	make --no-print-directory -C GLApp -f Makefile

P01-Triangle : 
	@echo "=== Building P01-Triangle ==="
	make --no-print-directory -C P01-Triangle -f Makefile

clean :
	make --no-print-directory -C GLApp -f Makefile clean
	make --no-print-directory -C P01-Triangle -f Makefile clean
