wakeserver: server.o anet.o ae_epoll.o ae.o zmalloc.o networking.o adlist.o dict.o sds.o protocol.o wstable.o
	gcc -o wakeserver -g main.c $^ -I.

server.o: server.c
	gcc -c -g -o $@ $^

anet.o: anet.c
	gcc -c -g -o $@ $^

ae_epoll.o:  ae_epoll.c
	gcc -c -g -o $@ $^

ae.o: ae.c
	gcc -c -g -o $@ $^

zmalloc.o: zmalloc.c
	gcc -c -g -o $@ $^

networking.o: networking.c
	gcc -c -g -o $@ $^

adlist.o: adlist.c
	gcc -c -g -o $@ $^

dict.o: dict.c
	gcc -c -g -o $@ $^

protocol.o: protocol.c
	gcc -c -g -o $@ $^

wstable.o: wstable.c
	gcc -c -g -o $@ $^


#libwake: server.o anet.o ae_epoll.o ae.o zmalloc.o networking.o adlist.o dict.o sds.o protocol.o
	#ar rcs libwake.a $^

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf wakeserver
