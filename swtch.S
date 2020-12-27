# Context switch
#
#   void swtch(struct context **old, struct context *new);
# 
# Save the current registers on the stack, creating
# a struct context, and save its address in *old.
# Switch stacks to new and pop previously-saved registers.

.globl swtch
swtch:
  # struct context **old, struct context *new
  movl 4(%esp), %eax
  movl 8(%esp), %edx

  # Save old callee-saved registers
  pushl %ebp
  pushl %ebx
  pushl %esi
  pushl %edi

  # Switch stacks
  # 将当前 esp 保存在 *old 中
  movl %esp, (%eax)
  # 设置新的 esp（即 new）
  movl %edx, %esp

  # Load new callee-saved registers
  popl %edi
  popl %esi
  popl %ebx
  popl %ebp
  # 最后的 ret（2727）指令从**栈中弹出目标进程的 %eip**，从而结束上下文切换工作。
  ret
