              .data
_prompt0:     .asciiz       "Please input an Integer: "
_result0:     .asciiz       "Output: "
_linefeed0:   .asciiz       "\n"
              .text
_input:
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $fp,          0($sp)                       # push 2/2
              move          $fp,          $sp                          # set frame pointer
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $ra,          0($sp)                       # push 2/2
              li            $v0,          4                            # set syscall number
              la            $a0,          _prompt0                     # set output message
              syscall                                                  # print prompt
              li            $v0,          5                            # set syscall number
              syscall                                                  # get input
              lw            $ra,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              lw            $fp,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              jr            $ra                                        # return
_output:
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $fp,          0($sp)                       # push 2/2
              move          $fp,          $sp                          # set frame pointer
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $ra,          0($sp)                       # push 2/2
              li            $v0,          4                            # set syscall number
              la            $a0,          _result0                     # set output message
              syscall                                                  # print output message
              li            $v0,          1                            # set syscall number
              lw            $a0,          4($fp)                       # set output
              syscall                                                  # print output
              li            $v0,          4                            # set syscall number
              la            $a0,          _linefeed0                   # set output message
              syscall                                                  # linefeed
              lw            $ra,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              lw            $fp,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              jr            $ra                                        # return
              .globl main
main:
              # --------------- function header begin ---------------- #
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $fp,          0($sp)                       # push 2/2
              move          $fp,          $sp                          # set frame pointer
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $ra,          0($sp)                       # push 2/2
              # ---------------- function header end ----------------- #
              addi          $sp,          $sp,          -16            # local variable
              # -------------- parameter passing begin --------------- #
              # --------------- parameter passing end ---------------- #
              jal           _input                                     # call
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -8             # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
              # -------------------- if contidion -------------------- #
              addi          $v0,          $fp,          -8             # local address
              lw            $v0,          0($v0)                       # variable value
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              li            $v0,          0                            # const
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              slt           $v0,          $v0,          $v1            # $ <= 1/2
              xori          $v0,          $v0,          1              # $ <= 2/2
              beqz          $v0,          End0                         # then
              # -------------- parameter passing begin --------------- #
              li            $v0,          0                            # const
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              # --------------- parameter passing end ---------------- #
              jal           _output                                    # call
              addi          $sp,          $sp,          4              # clear stack
              addi          $sp,          $fp,          -4             # clear stack
              lw            $ra,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              lw            $fp,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              jr            $ra                                        # return
End0:
              li            $v0,          0                            # const
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -12            # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
              li            $v0,          1                            # const
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -16            # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
WCOND0:
              addi          $v0,          $fp,          -8             # local address
              lw            $v0,          0($v0)                       # variable value
              beqz          $v0,          WEND0                        # while begin
              # ------------------ while loop body ------------------- #
              addi          $v0,          $fp,          -12            # local address
              lw            $v0,          0($v0)                       # variable value
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -16            # local address
              lw            $v0,          0($v0)                       # variable value
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              add           $v0,          $v1,          $v0            # plus
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -16            # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
              addi          $v0,          $fp,          -16            # local address
              lw            $v0,          0($v0)                       # variable value
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -12            # local address
              lw            $v0,          0($v0)                       # variable value
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sub           $v0,          $v1,          $v0            # minus
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -12            # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
              addi          $v0,          $fp,          -8             # local address
              lw            $v0,          0($v0)                       # variable value
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              li            $v0,          1                            # const
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sub           $v0,          $v1,          $v0            # minus
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              addi          $v0,          $fp,          -8             # local address
              lw            $v1,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              sw            $v1,          0($v0)                       # assign
              lw            $v0,          0($v0)                       # assign value
              j             WCOND0                                     # back to condition
WEND0:
              # -------------- parameter passing begin --------------- #
              addi          $v0,          $fp,          -12            # local address
              lw            $v0,          0($v0)                       # variable value
              addi          $sp,          $sp,          -4             # push 1/2
              sw            $v0,          0($sp)                       # push 2/2
              # --------------- parameter passing end ---------------- #
              jal           _output                                    # call
              addi          $sp,          $sp,          4              # clear stack
              addi          $sp,          $sp,          16             # clear local
              # --------------- function footer begin ---------------- #
              lw            $ra,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              lw            $fp,          0($sp)                       # pop 1/2
              addi          $sp,          $sp,          4              # pop 2/2
              jr            $ra                                        # return
              # ---------------- function footer end ----------------- #
