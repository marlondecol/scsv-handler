.SILENT:

all:
	$(MAKE) compile
	$(MAKE) run

compile:
	gcc "SCSV Handler.c" Headers/*.c -o app -lm

run:
	./app

clean:
	rm app