~~~c
 // 自定义错误码，从0x100开始
#define LU_ERROR_OPERATION_NOT_PERMITTED                    0x100
#define LU_ERROR_NO_SUCH_FILE_OR_DIRECTORY                  0x101
#define LU_ERROR_NO_SUCH_PROCESS                            0x102
#define LU_ERROR_INTERRUPTED_SYSTEM_CALL                    0x103
#define LU_ERROR_INPUT_OUTPUT_ERROR                         0x104
#define LU_ERROR_NO_SUCH_DEVICE_OR_ADDRESS                  0x105
#define LU_ERROR_ARGUMENT_LIST_TOO_LONG                     0x106
#define LU_ERROR_EXEC_FORMAT_ERROR                          0x107
#define LU_ERROR_BAD_FILE_DESCRIPTOR                        0x108
#define LU_ERROR_NO_CHILD_PROCESSES                         0x109
#define LU_ERROR_TRY_AGAIN                                  0x10A
#define LU_ERROR_OUT_OF_MEMORY                              0x10B
#define LU_ERROR_PERMISSION_DENIED                          0x10C
#define LU_ERROR_BAD_ADDRESS                                0x10D
#define LU_ERROR_BLOCK_DEVICE_REQUIRED                      0x10E
#define LU_ERROR_DEVICE_OR_RESOURCE_BUSY                    0x10F
#define LU_ERROR_FILE_EXISTS                                0x110
#define LU_ERROR_CROSS_DEVICE_LINK                          0x111
#define LU_ERROR_NO_SUCH_DEVICE                             0x112
#define LU_ERROR_NOT_A_DIRECTORY                            0x113
#define LU_ERROR_IS_A_DIRECTORY                             0x114
#define LU_ERROR_INVALID_ARGUMENT                           0x115
#define LU_ERROR_FILE_TABLE_OVERFLOW                        0x116
#define LU_ERROR_TOO_MANY_OPEN_FILES                        0x117
#define LU_ERROR_NOT_A_TYPEWRITER                           0x118
#define LU_ERROR_TEXT_FILE_BUSY                             0x119
#define LU_ERROR_FILE_TOO_LARGE                             0x11A
#define LU_ERROR_NO_SPACE_LEFT_ON_DEVICE                    0x11B
#define LU_ERROR_ILLEGAL_SEEK                               0x11C
#define LU_ERROR_READ_ONLY_FILE_SYSTEM                      0x11D
#define LU_ERROR_TOO_MANY_LINKS                             0x11E
#define LU_ERROR_BROKEN_PIPE                                0x11F
#define LU_ERROR_MATH_ARGUMENT_OUT_OF_DOMAIN_OF_FUNCTION    0x120
#define LU_ERROR_RESULT_TOO_REPRESENTABLE                   0x121
#define LU_MAX_ERROR_CODE                                   0x122  // 假设错误码的最大值
~~~