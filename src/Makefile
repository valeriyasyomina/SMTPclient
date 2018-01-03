CFLAGS = -Wall -Werror -g3
OBJ = main.o smtp_client.o message.o message_list.o message_header.o message_headers_list.o file.o string_list.o domain_info.o domain_info_list.o smtp_operation.o logger.o

	
%.o: %.c *.h
	gcc -c $< $(CFLAGS)


client: $(OBJ)
	gcc -L/usr/lib/ -o $@ $^ -lfiredns -lrt

logger: logger_main.o logger_process.o logger.o file.o
	gcc -o $@ $^ -lrt

clean:
	rm client logger $(OBJ)

.PHONY: clean




