default: build

build:
	rm -rf objs
	rm -f app_DB
	test -d objs || mkdir objs
	$(MAKE) -f src/makefile

clean:
	rm -rf objs
	rm -f app_DB

install:
