//syscall 335

#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_my_print(int pid, long long start, long long end){
	printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld", pid, start/1000000000, start%1000000000, end/1000000000, end%1000000000);
}