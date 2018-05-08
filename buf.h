struct buf {
  int flags;  // B_VALID or B_DIRIY
  uint dev;   // 设备号
  uint blockno;   // 扇区号？？？
  struct sleeplock lock;
  uint refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  struct buf *qnext; // 指向下一个 buf，以此形成磁盘队列 disk queue
  uchar data[BSIZE];  // 该磁盘扇区数据在内存中的拷贝
};
#define B_VALID 0x2  // buffer has been read from disk
#define B_DIRTY 0x4  // buffer needs to be written to disk

