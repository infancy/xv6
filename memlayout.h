// Memory layout

// 1MB（ext memery），224MB，4065MB（4096-31）
#define EXTMEM  0x100000            // Start of extended memory
#define PHYSTOP 0xE000000           // Top physical memory
#define DEVSPACE 0xFE000000         // Other devices are at high addresses

// Key addresses for address space layout (see kmap in vm.c for layout)
// 2GB(end of user, base of kernel)，
#define KERNBASE 0x80000000         // First kernel virtual address
#define KERNLINK (KERNBASE+EXTMEM)  // Address where kernel is linked

// per process virtual memory layout
// user memory ...BIOS(I/O space)...kern...
// 0...KENRBASE...KERNBASE+EXTMEM...data...KERNBASE+PHYSTOP
// 0...2GB     ...2GB+1MB        ...xxxx...2GB+224MB

// physical memory layout

#define V2P(a) (((uint) (a)) - KERNBASE)
#define P2V(a) ((void *)(((char *) (a)) + KERNBASE))

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNBASE)    // same as P2V, but without casts
