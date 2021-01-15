build:
	gcc Pack.c -o Packer
	gcc Unpack.c -o Unpacker

Pack:
	./Packer ${ARGS}

Unpack:
	./Unpacker ${ARGS}
	
help:
	@echo Use : \<make build\> to build the project.
	@echo Use : \<make ARGS=\"Directory_name Filename\" run\> to Pack.
	@echo Use : \<make ARGS=\"Filename\" run\> to Unpack.
	@echo Use : \<make help\> for help.
	@echo Use : \<make clean\> to remove executable.
	
clean:
	rm Packer
	rm Unpacker
	
