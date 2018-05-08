#include "mmu.h"

  #
  # vectors.S sends all traps here.
  #

.globl alltraps
alltraps:
  # Build trap frame.
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs
  pushal
  
  # Set up data segments.
  # 设置数据段选择符
  movw $(SEG_KDATA<<3), %ax
  movw %ax, %ds
  movw %ax, %es

  # Call trap(tf), where tf=%esp
  # esp 作为 trap 的参数，指向当前的中断帧
  # 调用 trap.c/trap(struct trapframe *tf) 中断函数
  pushl %esp
  call trap
  addl $4, %esp

  # 弹出中断帧以恢复用户模式下的寄存器，然后执行 iret 跳回到用户空间。
  # Return falls through to trapret...
.globl trapret
trapret:
  popal
  popl %gs
  popl %fs
  popl %es
  popl %ds
  addl $0x8, %esp  # trapno and errcode
  iret
