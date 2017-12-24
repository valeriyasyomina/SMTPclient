client: main.o smtp_client.o message.o message_header.o message_headers_list.o file.o string_list.o
	gcc -o $@ $^
%.o: %.c *.h
	gcc -c $<

clean:
	rm *.o client



