# IJVM Emulator

Requires make and GCC or Clang (C11 Compiler)

Run `make ijvm` to build the ijvm binary

Run an IJVM program using `./ijvm binary`. For example `./ijvm files/advanced/example.ijvm`.

## Supported Operations

```
  case OP_BIPUSH:
  case OP_DUP:
  case OP_ERR:
  case OP_GOTO:
  case OP_HALT:
  case OP_IADD:
  case OP_IAND:
  case OP_IFEQ:
  case OP_IFLT:
  case OP_ICMPEQ:
  case OP_IINC:
  case OP_ILOAD:
  case OP_IN:
  case OP_INVOKEVIRTUAL:
  case OP_IOR:
  case OP_IRETURN:
  case OP_ISTORE:
  case OP_ISUB:
  case OP_LDC_W:
  case OP_NOP:
  case OP_OUT:
  case OP_POP:
  case OP_SWAP:
  case OP_WIDE:
```
