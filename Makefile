all: process.c all.c process_scheduling.c fifo.c rr.c sjf.c psjf.c heap.c sort.c
	gcc process.c all.c -o process
	gcc process_scheduling.c fifo.c rr.c sjf.c psjf.c heap.c heap_sjf.c sort.c all.c -o ps

clean:
	rm -f process ps