#ifndef F28004X_GPIO_H
#define F28004X_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// GPIO Individual Register Bit Definitions:

struct GPA_CTRL_BITS
{                        // bits description
    Uint32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO0 to GPIO7
    Uint32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO8 to GPIO15
    Uint32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO16 to GPIO23
    Uint32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO24 to GPIO31
};

union GPA_CTRL_REG
{
    Uint32 all;
    struct GPA_CTRL_BITS bit;
};

struct GPA_16_L_BITS
{                      // bits description
    Uint32 GPIO0  : 2; // 1:0 Select input qualification type for GPIO0
    Uint32 GPIO1  : 2; // 3:2 Select input qualification type for GPIO1
    Uint32 GPIO2  : 2; // 5:4 Select input qualification type for GPIO2
    Uint32 GPIO3  : 2; // 7:6 Select input qualification type for GPIO3
    Uint32 GPIO4  : 2; // 9:8 Select input qualification type for GPIO4
    Uint32 GPIO5  : 2; // 11:10 Select input qualification type for GPIO5
    Uint32 GPIO6  : 2; // 13:12 Select input qualification type for GPIO6
    Uint32 GPIO7  : 2; // 15:14 Select input qualification type for GPIO7
    Uint32 GPIO8  : 2; // 17:16 Select input qualification type for GPIO8
    Uint32 GPIO9  : 2; // 19:18 Select input qualification type for GPIO9
    Uint32 GPIO10 : 2; // 21:20 Select input qualification type for GPIO10
    Uint32 GPIO11 : 2; // 23:22 Select input qualification type for GPIO11
    Uint32 GPIO12 : 2; // 25:24 Select input qualification type for GPIO12
    Uint32 GPIO13 : 2; // 27:26 Select input qualification type for GPIO13
    Uint32 GPIO14 : 2; // 29:28 Select input qualification type for GPIO14
    Uint32 GPIO15 : 2; // 31:30 Select input qualification type for GPIO15
};

union GPA_16_L_REG
{
    Uint32 all;
    struct GPA_16_L_BITS bit;
};

struct GPA_16_H_BITS
{                      // bits description
    Uint32 GPIO16 : 2; // 1:0 Select input qualification type for GPIO16
    Uint32 GPIO17 : 2; // 3:2 Select input qualification type for GPIO17
    Uint32 GPIO18 : 2; // 5:4 Select input qualification type for GPIO18
    Uint32 GPIO19 : 2; // 7:6 Select input qualification type for GPIO19
    Uint32 GPIO20 : 2; // 9:8 Select input qualification type for GPIO20
    Uint32 GPIO21 : 2; // 11:10 Select input qualification type for GPIO21
    Uint32 GPIO22 : 2; // 13:12 Select input qualification type for GPIO22
    Uint32 GPIO23 : 2; // 15:14 Select input qualification type for GPIO23
    Uint32 GPIO24 : 2; // 17:16 Select input qualification type for GPIO24
    Uint32 GPIO25 : 2; // 19:18 Select input qualification type for GPIO25
    Uint32 GPIO26 : 2; // 21:20 Select input qualification type for GPIO26
    Uint32 GPIO27 : 2; // 23:22 Select input qualification type for GPIO27
    Uint32 GPIO28 : 2; // 25:24 Select input qualification type for GPIO28
    Uint32 GPIO29 : 2; // 27:26 Select input qualification type for GPIO29
    Uint32 GPIO30 : 2; // 29:28 Select input qualification type for GPIO30
    Uint32 GPIO31 : 2; // 31:30 Select input qualification type for GPIO31
};

union GPA_16_H_REG
{
    Uint32 all;
    struct GPA_16_H_BITS bit;
};

struct GPA_32_BITS
{                      // bits description
    Uint32 GPIO0  : 1; // 0 Defines direction for this pin in GPIO mode
    Uint32 GPIO1  : 1; // 1 Defines direction for this pin in GPIO mode
    Uint32 GPIO2  : 1; // 2 Defines direction for this pin in GPIO mode
    Uint32 GPIO3  : 1; // 3 Defines direction for this pin in GPIO mode
    Uint32 GPIO4  : 1; // 4 Defines direction for this pin in GPIO mode
    Uint32 GPIO5  : 1; // 5 Defines direction for this pin in GPIO mode
    Uint32 GPIO6  : 1; // 6 Defines direction for this pin in GPIO mode
    Uint32 GPIO7  : 1; // 7 Defines direction for this pin in GPIO mode
    Uint32 GPIO8  : 1; // 8 Defines direction for this pin in GPIO mode
    Uint32 GPIO9  : 1; // 9 Defines direction for this pin in GPIO mode
    Uint32 GPIO10 : 1; // 10 Defines direction for this pin in GPIO mode
    Uint32 GPIO11 : 1; // 11 Defines direction for this pin in GPIO mode
    Uint32 GPIO12 : 1; // 12 Defines direction for this pin in GPIO mode
    Uint32 GPIO13 : 1; // 13 Defines direction for this pin in GPIO mode
    Uint32 GPIO14 : 1; // 14 Defines direction for this pin in GPIO mode
    Uint32 GPIO15 : 1; // 15 Defines direction for this pin in GPIO mode
    Uint32 GPIO16 : 1; // 16 Defines direction for this pin in GPIO mode
    Uint32 GPIO17 : 1; // 17 Defines direction for this pin in GPIO mode
    Uint32 GPIO18 : 1; // 18 Defines direction for this pin in GPIO mode
    Uint32 GPIO19 : 1; // 19 Defines direction for this pin in GPIO mode
    Uint32 GPIO20 : 1; // 20 Defines direction for this pin in GPIO mode
    Uint32 GPIO21 : 1; // 21 Defines direction for this pin in GPIO mode
    Uint32 GPIO22 : 1; // 22 Defines direction for this pin in GPIO mode
    Uint32 GPIO23 : 1; // 23 Defines direction for this pin in GPIO mode
    Uint32 GPIO24 : 1; // 24 Defines direction for this pin in GPIO mode
    Uint32 GPIO25 : 1; // 25 Defines direction for this pin in GPIO mode
    Uint32 GPIO26 : 1; // 26 Defines direction for this pin in GPIO mode
    Uint32 GPIO27 : 1; // 27 Defines direction for this pin in GPIO mode
    Uint32 GPIO28 : 1; // 28 Defines direction for this pin in GPIO mode
    Uint32 GPIO29 : 1; // 29 Defines direction for this pin in GPIO mode
    Uint32 GPIO30 : 1; // 30 Defines direction for this pin in GPIO mode
    Uint32 GPIO31 : 1; // 31 Defines direction for this pin in GPIO mode
};

union GPA_32_REG
{
    Uint32 all;
    struct GPA_32_BITS bit;
};

struct GPB_CTRL_BITS
{                        // bits description
    Uint32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO32 to GPIO39
    Uint32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO40 to GPIO47
    Uint32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO48 to GPIO55
    Uint32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO56 to GPIO63
};

struct GPAAMSEL_BITS
{                       // bits description
    Uint32 rsvd   : 22; // 21-0 Reserved
    Uint32 GPIO22 : 1;  // 22 Analog Mode select for this pin
    Uint32 GPIO23 : 1;  // 23 Analog Mode select for this pin
};

union GPAAMSEL_REG
{
    Uint32 all;
    struct GPAAMSEL_BITS bit;
};

union GPB_CTRL_REG
{
    Uint32 all;
    struct GPB_CTRL_BITS bit;
};

struct GPB_16_L_BITS
{                      // bits description
    Uint32 GPIO32 : 2; // 1:0 Select input qualification type for GPIO32
    Uint32 GPIO33 : 2; // 3:2 Select input qualification type for GPIO33
    Uint32 GPIO34 : 2; // 5:4 Select input qualification type for GPIO34
    Uint32 GPIO35 : 2; // 7:6 Select input qualification type for GPIO35
    Uint32 rsvd1  : 2; // Reserved
    Uint32 GPIO37 : 2; // 11:10 Select input qualification type for GPIO37
    Uint32 rsvd2  : 2; // Reserved
    Uint32 GPIO39 : 2; // 15:14 Select input qualification type for GPIO39
    Uint32 GPIO40 : 2; // 17:16 Select input qualification type for GPIO40
    Uint32 GPIO41 : 2; // 19:18 Select input qualification type for GPIO41
    Uint32 GPIO42 : 2; // 21:20 Select input qualification type for GPIO42
    Uint32 GPIO43 : 2; // 23:22 Select input qualification type for GPIO43
    Uint32 GPIO44 : 2; // 25:24 Select input qualification type for GPIO44
    Uint32 GPIO45 : 2; // 27:26 Select input qualification type for GPIO45
    Uint32 GPIO46 : 2; // 29:28 Select input qualification type for GPIO46
    Uint32 GPIO47 : 2; // 31:30 Select input qualification type for GPIO47
};

union GPB_16_L_REG
{
    Uint32 all;
    struct GPB_16_L_BITS bit;
};

struct GPB_16_H_BITS
{                      // bits description
    Uint32 GPIO48 : 2; // 1:0 Select input qualification type for GPIO48
    Uint32 GPIO49 : 2; // 3:2 Select input qualification type for GPIO49
    Uint32 GPIO50 : 2; // 5:4 Select input qualification type for GPIO50
    Uint32 GPIO51 : 2; // 7:6 Select input qualification type for GPIO51
    Uint32 GPIO52 : 2; // 9:8 Select input qualification type for GPIO52
    Uint32 GPIO53 : 2; // 11:10 Select input qualification type for GPIO53
    Uint32 GPIO54 : 2; // 13:12 Select input qualification type for GPIO54
    Uint32 GPIO55 : 2; // 15:14 Select input qualification type for GPIO55
    Uint32 GPIO56 : 2; // 17:16 Select input qualification type for GPIO56
    Uint32 GPIO57 : 2; // 19:18 Select input qualification type for GPIO57
    Uint32 GPIO58 : 2; // 21:20 Select input qualification type for GPIO58
    Uint32 GPIO59 : 2; // 23:22 Select input qualification type for GPIO59
    Uint32 rsvd1  : 2; // Reserved
    Uint32 rsvd2  : 2; // Reserved
    Uint32 rsvd3  : 2; // Reserved
    Uint32 rsvd4  : 2; // Reserved
};

union GPB_16_H_REG
{
    Uint32 all;
    struct GPB_16_H_BITS bit;
};

struct GPB_32_BITS
{                      // bits description
    Uint32 GPIO32 : 1; // 0 Defines direction for this pin in GPIO mode
    Uint32 GPIO33 : 1; // 1 Defines direction for this pin in GPIO mode
    Uint32 GPIO34 : 1; // 2 Defines direction for this pin in GPIO mode
    Uint32 GPIO35 : 1; // 3 Defines direction for this pin in GPIO mode
    Uint32 rsvd1  : 1; // 4 Defines direction for this pin in GPIO mode
    Uint32 GPIO37 : 1; // 5 Defines direction for this pin in GPIO mode
    Uint32 rsvd2  : 1; // 6 Defines direction for this pin in GPIO mode
    Uint32 GPIO39 : 1; // 7 Defines direction for this pin in GPIO mode
    Uint32 GPIO40 : 1; // 8 Defines direction for this pin in GPIO mode
    Uint32 GPIO41 : 1; // 9 Defines direction for this pin in GPIO mode
    Uint32 GPIO42 : 1; // 10 Defines direction for this pin in GPIO mode
    Uint32 GPIO43 : 1; // 11 Defines direction for this pin in GPIO mode
    Uint32 GPIO44 : 1; // 12 Defines direction for this pin in GPIO mode
    Uint32 GPIO45 : 1; // 13 Defines direction for this pin in GPIO mode
    Uint32 GPIO46 : 1; // 14 Defines direction for this pin in GPIO mode
    Uint32 GPIO47 : 1; // 15 Defines direction for this pin in GPIO mode
    Uint32 GPIO48 : 1; // 16 Defines direction for this pin in GPIO mode
    Uint32 GPIO49 : 1; // 17 Defines direction for this pin in GPIO mode
    Uint32 GPIO50 : 1; // 18 Defines direction for this pin in GPIO mode
    Uint32 GPIO51 : 1; // 19 Defines direction for this pin in GPIO mode
    Uint32 GPIO52 : 1; // 20 Defines direction for this pin in GPIO mode
    Uint32 GPIO53 : 1; // 21 Defines direction for this pin in GPIO mode
    Uint32 GPIO54 : 1; // 22 Defines direction for this pin in GPIO mode
    Uint32 GPIO55 : 1; // 23 Defines direction for this pin in GPIO mode
    Uint32 GPIO56 : 1; // 24 Defines direction for this pin in GPIO mode
    Uint32 GPIO57 : 1; // 25 Defines direction for this pin in GPIO mode
    Uint32 GPIO58 : 1; // 26 Defines direction for this pin in GPIO mode
    Uint32 GPIO59 : 1; // 27 Defines direction for this pin in GPIO mode
    Uint32 rsvd3  : 1; // 28 Defines direction for this pin in GPIO mode
    Uint32 rsvd4  : 1; // 29 Defines direction for this pin in GPIO mode
    Uint32 rsvd5  : 1; // 30 Defines direction for this pin in GPIO mode
    Uint32 rsvd6  : 1; // 31 Defines direction for this pin in GPIO mode
};

union GPB_32_REG
{
    Uint32 all;
    struct GPB_32_BITS bit;
};

struct GPH_CTRL_BITS
{                        // bits description
    Uint32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO224 to GPIO231
    Uint32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO232 to GPIO239
    Uint32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO240 to GPIO247
    Uint32 rsvd1    : 8; // 31:24 Reserved
};

union GPH_CTRL_REG
{
    Uint32 all;
    struct GPH_CTRL_BITS bit;
};

struct GPH_QSEL1_BITS
{                       // bits description
    Uint32 GPIO224 : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO225 : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO226 : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO227 : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO228 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO229 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO230 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO231 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 GPIO232 : 2; // 17:16 Select input qualification type for this GPIO Pin
    Uint32 GPIO233 : 2; // 19:18 Select input qualification type for this GPIO Pin
    Uint32 GPIO234 : 2; // 21:20 Select input qualification type for this GPIO Pin
    Uint32 GPIO235 : 2; // 23:22 Select input qualification type for this GPIO Pin
    Uint32 GPIO236 : 2; // 25:24 Select input qualification type for this GPIO Pin
    Uint32 GPIO237 : 2; // 27:26 Select input qualification type for this GPIO Pin
    Uint32 GPIO238 : 2; // 29:28 Select input qualification type for this GPIO Pin
    Uint32 GPIO239 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPH_QSEL1_REG
{
    Uint32 all;
    struct GPH_QSEL1_BITS bit;
};

struct GPH_QSEL2_BITS
{                       // bits description
    Uint32 GPIO240 : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO241 : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO242 : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO243 : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO244 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO245 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO246 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO247 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 rsvd1   : 2; // 17:16 Reserved
    Uint32 rsvd2   : 2; // 19:18 Reserved
    Uint32 rsvd3   : 2; // 21:20 Reserved
    Uint32 rsvd4   : 2; // 23:22 Reserved
    Uint32 rsvd5   : 2; // 25:24 Reserved
    Uint32 rsvd6   : 2; // 27:26 Reserved
    Uint32 rsvd7   : 2; // 29:28 Reserved
    Uint32 rsvd8   : 2; // 31:30 Reserved
};

union GPH_QSEL2_REG
{
    Uint32 all;
    struct GPH_QSEL2_BITS bit;
};

struct GPH_32_BITS
{ // bits description
    Uint32 GPIO224 : 1;
    Uint32 GPIO225 : 1;
    Uint32 GPIO226 : 1;
    Uint32 GPIO227 : 1;
    Uint32 GPIO228 : 1;
    Uint32 GPIO229 : 1;
    Uint32 GPIO230 : 1;
    Uint32 GPIO231 : 1;
    Uint32 GPIO232 : 1;
    Uint32 GPIO233 : 1;
    Uint32 GPIO234 : 1;
    Uint32 GPIO235 : 1;
    Uint32 GPIO236 : 1;
    Uint32 GPIO237 : 1;
    Uint32 GPIO238 : 1;
    Uint32 GPIO239 : 1;
    Uint32 GPIO240 : 1;
    Uint32 GPIO241 : 1;
    Uint32 GPIO242 : 1;
    Uint32 GPIO243 : 1;
    Uint32 GPIO244 : 1;
    Uint32 GPIO245 : 1;
    Uint32 GPIO246 : 1;
    Uint32 GPIO247 : 1;
    Uint32 rsvd1   : 1;
    Uint32 rsvd2   : 1;
    Uint32 rsvd3   : 1;
    Uint32 rsvd4   : 1;
    Uint32 rsvd5   : 1;
    Uint32 rsvd6   : 1;
    Uint32 rsvd7   : 1;
    Uint32 rsvd8   : 1;
};

union GPH_32_REG
{
    Uint32 all;
    struct GPH_32_BITS bit;
};

struct GPC_CTRL_BITS
{                        // bits description
    Uint32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO224 to GPIO231
    Uint32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO232 to GPIO239
    Uint32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO240 to GPIO247
    Uint32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO240 to GPIO247
};

union GPC_CTRL_REG
{
    Uint32 all;
    struct GPC_CTRL_BITS bit;
};

struct GPC_QSEL1_BITS
{                      // bits description
    Uint32 GPIO64 : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO65 : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO66 : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO67 : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO68 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO69 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO70 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO71 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 GPIO72 : 2; // 17:16 Select input qualification type for this GPIO Pin
    Uint32 GPIO73 : 2; // 19:18 Select input qualification type for this GPIO Pin
    Uint32 GPIO74 : 2; // 21:20 Select input qualification type for this GPIO Pin
    Uint32 GPIO75 : 2; // 23:22 Select input qualification type for this GPIO Pin
    Uint32 GPIO76 : 2; // 25:24 Select input qualification type for this GPIO Pin
    Uint32 GPIO77 : 2; // 27:26 Select input qualification type for this GPIO Pin
    Uint32 GPIO78 : 2; // 29:28 Select input qualification type for this GPIO Pin
    Uint32 GPIO79 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPC_QSEL1_REG
{
    Uint32 all;
    struct GPC_QSEL1_BITS bit;
};

struct GPC_QSEL2_BITS
{                      // bits description
    Uint32 GPIO80 : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO81 : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO82 : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO83 : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO84 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO85 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO86 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO87 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 GPIO88 : 2; // 17:16 Select input qualification type for this GPIO Pin
    Uint32 GPIO89 : 2; // 19:18 Select input qualification type for this GPIO Pin
    Uint32 GPIO90 : 2; // 21:20 Select input qualification type for this GPIO Pin
    Uint32 GPIO91 : 2; // 23:22 Select input qualification type for this GPIO Pin
    Uint32 GPIO92 : 2; // 25:24 Select input qualification type for this GPIO Pin
    Uint32 GPIO93 : 2; // 27:26 Select input qualification type for this GPIO Pin
    Uint32 GPIO94 : 2; // 29:28 Select input qualification type for this GPIO Pin
    Uint32 GPIO95 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPC_QSEL2_REG
{
    Uint32 all;
    struct GPC_QSEL2_BITS bit;
};

struct GPC_16_L_BITS
{                      // bits description
    Uint32 GPIO64 : 2; // 1:0 Select input qualification type for GPIO64
    Uint32 GPIO65 : 2; // 3:2 Select input qualification type for GPIO65
    Uint32 GPIO66 : 2; // 5:4 Select input qualification type for GPIO66
    Uint32 GPIO67 : 2; // 7:6 Select input qualification type for GPIO67
    Uint32 GPIO68 : 2; // 9:8 Select input qualification type for GPIO68
    Uint32 GPIO69 : 2; // 11:10 Select input qualification type for GPIO69
    Uint32 GPIO70 : 2; // 13:12 Select input qualification type for GPIO70
    Uint32 GPIO71 : 2; // 15:14 Select input qualification type for GPIO71
    Uint32 GPIO72 : 2; // 17:16 Select input qualification type for GPIO72
    Uint32 GPIO73 : 2; // 19:18 Select input qualification type for GPIO73
    Uint32 GPIO74 : 2; // 21:20 Select input qualification type for GPIO74
    Uint32 GPIO75 : 2; // 23:22 Select input qualification type for GPIO75
    Uint32 GPIO76 : 2; // 25:24 Select input qualification type for GPIO76
    Uint32 GPIO77 : 2; // 27:26 Select input qualification type for GPIO77
    Uint32 GPIO78 : 2; // 29:28 Select input qualification type for GPIO78
    Uint32 GPIO79 : 2; // 31:30 Select input qualification type for GPIO79
};

union GPC_16_L_REG
{
    Uint32 all;
    struct GPC_16_L_BITS bit;
};

struct GPC_16_H_BITS
{                      // bits description
    Uint32 GPIO80 : 2; // 1:0 Select input qualification type for GPIO64
    Uint32 GPIO81 : 2; // 3:2 Select input qualification type for GPIO65
    Uint32 GPIO82 : 2; // 5:4 Select input qualification type for GPIO66
    Uint32 GPIO83 : 2; // 7:6 Select input qualification type for GPIO67
    Uint32 GPIO84 : 2; // 9:8 Select input qualification type for GPIO68
    Uint32 GPIO85 : 2; // 11:10 Select input qualification type for GPIO69
    Uint32 GPIO86 : 2; // 13:12 Select input qualification type for GPIO70
    Uint32 GPIO87 : 2; // 15:14 Select input qualification type for GPIO71
    Uint32 GPIO88 : 2; // 17:16 Select input qualification type for GPIO72
    Uint32 GPIO89 : 2; // 19:18 Select input qualification type for GPIO73
    Uint32 GPIO90 : 2; // 21:20 Select input qualification type for GPIO74
    Uint32 GPIO91 : 2; // 23:22 Select input qualification type for GPIO75
    Uint32 GPIO92 : 2; // 25:24 Select input qualification type for GPIO76
    Uint32 GPIO93 : 2; // 27:26 Select input qualification type for GPIO77
    Uint32 GPIO94 : 2; // 29:28 Select input qualification type for GPIO78
    Uint32 GPIO95 : 2; // 31:30 Select input qualification type for GPIO79
};

union GPC_16_H_REG
{
    Uint32 all;
    struct GPC_16_H_BITS bit;
};

struct GPC_32_BITS
{                      // bits description
    Uint32 GPIO64 : 1; // 64 Defines direction for this pin in GPIO mode
    Uint32 GPIO65 : 1; // 65 Defines direction for this pin in GPIO mode
    Uint32 GPIO66 : 1; // 66 Defines direction for this pin in GPIO mode
    Uint32 GPIO67 : 1; // 67 Defines direction for this pin in GPIO mode
    Uint32 GPIO68 : 1; // 68 Defines direction for this pin in GPIO mode
    Uint32 GPIO69 : 1; // 69 Defines direction for this pin in GPIO mode
    Uint32 GPIO70 : 1; // 70 Defines direction for this pin in GPIO mode
    Uint32 GPIO71 : 1; // 71 Defines direction for this pin in GPIO mode
    Uint32 GPIO72 : 1; // 72 Defines direction for this pin in GPIO mode
    Uint32 GPIO73 : 1; // 73 Defines direction for this pin in GPIO mode
    Uint32 GPIO74 : 1; // 74 Defines direction for this pin in GPIO mode
    Uint32 GPIO75 : 1; // 75 Defines direction for this pin in GPIO mode
    Uint32 GPIO76 : 1; // 76 Defines direction for this pin in GPIO mode
    Uint32 GPIO77 : 1; // 77 Defines direction for this pin in GPIO mode
    Uint32 GPIO78 : 1; // 78 Defines direction for this pin in GPIO mode
    Uint32 GPIO79 : 1; // 79 Defines direction for this pin in GPIO mode
    Uint32 GPIO80 : 1; // 80 Defines direction for this pin in GPIO mode
    Uint32 GPIO81 : 1; // 81 Defines direction for this pin in GPIO mode
    Uint32 GPIO82 : 1; // 82 Defines direction for this pin in GPIO mode
    Uint32 GPIO83 : 1; // 83 Defines direction for this pin in GPIO mode
    Uint32 GPIO84 : 1; // 84 Defines direction for this pin in GPIO mode
    Uint32 GPIO85 : 1; // 85 Defines direction for this pin in GPIO mode
    Uint32 GPIO86 : 1; // 86 Defines direction for this pin in GPIO mode
    Uint32 GPIO87 : 1; // 87 Defines direction for this pin in GPIO mode
    Uint32 GPIO88 : 1; // 88 Defines direction for this pin in GPIO mode
    Uint32 GPIO89 : 1; // 89 Defines direction for this pin in GPIO mode
    Uint32 GPIO90 : 1; // 90 Defines direction for this pin in GPIO mode
    Uint32 GPIO91 : 1; // 91 Defines direction for this pin in GPIO mode
    Uint32 GPIO92 : 1; // 92 Defines direction for this pin in GPIO mode
    Uint32 GPIO93 : 1; // 93 Defines direction for this pin in GPIO mode
    Uint32 GPIO94 : 1; // 94 Defines direction for this pin in GPIO mode
    Uint32 GPIO95 : 1; // 95 Defines direction for this pin in GPIO mode
};

union GPC_32_REG
{
    Uint32 all;
    struct GPC_32_BITS bit;
};

struct GPD_CTRL_BITS
{                        // bits description
    Uint32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO224 to GPIO231
    Uint32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO232 to GPIO239
    Uint32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO240 to GPIO247
    Uint32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO240 to GPIO247
};

union GPD_CTRL_REG
{
    Uint32 all;
    struct GPD_CTRL_BITS bit;
};

struct GPD_QSEL1_BITS
{                       // bits description
    Uint32 GPIO96  : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO97  : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO98  : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO99  : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO100 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO101 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO102 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO103 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 GPIO104 : 2; // 17:16 Select input qualification type for this GPIO Pin
    Uint32 GPIO105 : 2; // 19:18 Select input qualification type for this GPIO Pin
    Uint32 GPIO106 : 2; // 21:20 Select input qualification type for this GPIO Pin
    Uint32 GPIO107 : 2; // 23:22 Select input qualification type for this GPIO Pin
    Uint32 GPIO108 : 2; // 25:24 Select input qualification type for this GPIO Pin
    Uint32 GPIO109 : 2; // 27:26 Select input qualification type for this GPIO Pin
    Uint32 GPIO110 : 2; // 29:28 Select input qualification type for this GPIO Pin
    Uint32 GPIO111 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPD_QSEL1_REG
{
    Uint32 all;
    struct GPD_QSEL1_BITS bit;
};

struct GPD_QSEL2_BITS
{                       // bits description
    Uint32 GPIO112 : 2; // 1:0 Select input qualification type for this GPIO Pin
    Uint32 GPIO113 : 2; // 3:2 Select input qualification type for this GPIO Pin
    Uint32 GPIO114 : 2; // 5:4 Select input qualification type for this GPIO Pin
    Uint32 GPIO115 : 2; // 7:6 Select input qualification type for this GPIO Pin
    Uint32 GPIO116 : 2; // 9:8 Select input qualification type for this GPIO Pin
    Uint32 GPIO117 : 2; // 11:10 Select input qualification type for this GPIO Pin
    Uint32 GPIO118 : 2; // 13:12 Select input qualification type for this GPIO Pin
    Uint32 GPIO119 : 2; // 15:14 Select input qualification type for this GPIO Pin
    Uint32 GPIO120 : 2; // 17:16 Select input qualification type for this GPIO Pin
    Uint32 GPIO121 : 2; // 19:18 Select input qualification type for this GPIO Pin
    Uint32 GPIO122 : 2; // 21:20 Select input qualification type for this GPIO Pin
    Uint32 GPIO123 : 2; // 23:22 Select input qualification type for this GPIO Pin
    Uint32 GPIO124 : 2; // 25:24 Select input qualification type for this GPIO Pin
    Uint32 GPIO125 : 2; // 27:26 Select input qualification type for this GPIO Pin
    Uint32 GPIO126 : 2; // 29:28 Select input qualification type for this GPIO Pin
    Uint32 GPIO127 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPD_QSEL2_REG
{
    Uint32 all;
    struct GPD_QSEL2_BITS bit;
};

struct GPD_16_L_BITS
{                       // bits description
    Uint32 GPIO96  : 2; // 1:0 Select input qualification type for GPIO96
    Uint32 GPIO97  : 2; // 3:2 Select input qualification type for GPIO97
    Uint32 GPIO98  : 2; // 5:4 Select input qualification type for GPIO98
    Uint32 GPIO99  : 2; // 7:6 Select input qualification type for GPIO99
    Uint32 GPIO100 : 2; // 9:8 Select input qualification type for GPIO100
    Uint32 GPIO101 : 2; // 11:10 Select input qualification type for GPIO101
    Uint32 GPIO102 : 2; // 13:12 Select input qualification type for GPIO102
    Uint32 GPIO103 : 2; // 15:14 Select input qualification type for GPIO103
    Uint32 GPIO104 : 2; // 17:16 Select input qualification type for GPIO104
    Uint32 GPIO105 : 2; // 19:18 Select input qualification type for GPIO105
    Uint32 GPIO106 : 2; // 21:20 Select input qualification type for GPIO106
    Uint32 GPIO107 : 2; // 23:22 Select input qualification type for GPIO107
    Uint32 GPIO108 : 2; // 25:24 Select input qualification type for GPIO108
    Uint32 GPIO109 : 2; // 27:26 Select input qualification type for GPIO109
    Uint32 GPIO110 : 2; // 29:28 Select input qualification type for GPIO110
    Uint32 GPIO111 : 2; // 31:30 Select input qualification type for GPIO111
};

union GPD_16_L_REG
{
    Uint32 all;
    struct GPD_16_L_BITS bit;
};

struct GPD_16_H_BITS
{                       // bits description
    Uint32 GPIO112 : 2; // 1:0 Select input qualification type for GPIO112
    Uint32 GPIO113 : 2; // 3:2 Select input qualification type for GPIO113
    Uint32 GPIO114 : 2; // 5:4 Select input qualification type for GPIO114
    Uint32 GPIO115 : 2; // 7:6 Select input qualification type for GPIO115
    Uint32 GPIO116 : 2; // 9:8 Select input qualification type for GPIO116
    Uint32 GPIO117 : 2; // 11:10 Select input qualification type for GPIO117
    Uint32 GPIO118 : 2; // 13:12 Select input qualification type for GPIO118
    Uint32 GPIO119 : 2; // 15:14 Select input qualification type for GPIO119
    Uint32 GPIO120 : 2; // 17:16 Select input qualification type for GPIO120
    Uint32 GPIO121 : 2; // 19:18 Select input qualification type for GPIO121
    Uint32 GPIO122 : 2; // 21:20 Select input qualification type for GPIO122
    Uint32 GPIO123 : 2; // 23:22 Select input qualification type for GPIO123
    Uint32 GPIO124 : 2; // 25:24 Select input qualification type for GPIO124
    Uint32 GPIO125 : 2; // 27:26 Select input qualification type for GPIO125
    Uint32 GPIO126 : 2; // 29:28 Select input qualification type for GPIO126
    Uint32 GPIO127 : 2; // 31:30 Select input qualification type for GPIO127
};

union GPD_16_H_REG
{
    Uint32 all;
    struct GPD_16_H_BITS bit;
};

struct GPD_32_BITS
{                       // bits description
    Uint32 GPIO96  : 1; // 96 Defines direction for this pin in GPIO mode
    Uint32 GPIO97  : 1; // 97 Defines direction for this pin in GPIO mode
    Uint32 GPIO98  : 1; // 98 Defines direction for this pin in GPIO mode
    Uint32 GPIO99  : 1; // 99 Defines direction for this pin in GPIO mode
    Uint32 GPIO100 : 1; // 100 Defines direction for this pin in GPIO mode
    Uint32 GPIO101 : 1; // 101 Defines direction for this pin in GPIO mode
    Uint32 GPIO102 : 1; // 102 Defines direction for this pin in GPIO mode
    Uint32 GPIO103 : 1; // 103 Defines direction for this pin in GPIO mode
    Uint32 GPIO104 : 1; // 104 Defines direction for this pin in GPIO mode
    Uint32 GPIO105 : 1; // 105 Defines direction for this pin in GPIO mode
    Uint32 GPIO106 : 1; // 106 Defines direction for this pin in GPIO mode
    Uint32 GPIO107 : 1; // 107 Defines direction for this pin in GPIO mode
    Uint32 GPIO108 : 1; // 108 Defines direction for this pin in GPIO mode
    Uint32 GPIO109 : 1; // 109 Defines direction for this pin in GPIO mode
    Uint32 GPIO110 : 1; // 110 Defines direction for this pin in GPIO mode
    Uint32 GPIO111 : 1; // 111 Defines direction for this pin in GPIO mode
    Uint32 GPIO112 : 1; // 112 Defines direction for this pin in GPIO mode
    Uint32 GPIO113 : 1; // 113 Defines direction for this pin in GPIO mode
    Uint32 GPIO114 : 1; // 114 Defines direction for this pin in GPIO mode
    Uint32 GPIO115 : 1; // 115 Defines direction for this pin in GPIO mode
    Uint32 GPIO116 : 1; // 116 Defines direction for this pin in GPIO mode
    Uint32 GPIO117 : 1; // 117 Defines direction for this pin in GPIO mode
    Uint32 GPIO118 : 1; // 118 Defines direction for this pin in GPIO mode
    Uint32 GPIO119 : 1; // 119 Defines direction for this pin in GPIO mode
    Uint32 GPIO120 : 1; // 120 Defines direction for this pin in GPIO mode
    Uint32 GPIO121 : 1; // 121 Defines direction for this pin in GPIO mode
    Uint32 GPIO122 : 1; // 122 Defines direction for this pin in GPIO mode
    Uint32 GPIO123 : 1; // 123 Defines direction for this pin in GPIO mode
    Uint32 GPIO124 : 1; // 124 Defines direction for this pin in GPIO mode
    Uint32 GPIO125 : 1; // 125 Defines direction for this pin in GPIO mode
    Uint32 GPIO126 : 1; // 126 Defines direction for this pin in GPIO mode
    Uint32 GPIO127 : 1; // 127 Defines direction for this pin in GPIO mode
};

union GPD_32_REG
{
    Uint32 all;
    struct GPD_32_BITS bit;
};

struct SPSEL_BITS
{
    Uint32 SPSEL : 1; // LIN_A And SCI_C Switch Taggle, 0: LIN_A 1: SCI_C
    Uint32 rsvd  : 31;
};

union SPSEL_REG
{
    Uint32 all;
    struct SPSEL_BITS bit;
};

struct GPIO_CTRL_REGS
{
    /* clang-format off */
    union GPA_CTRL_REG GPACTRL;   // GPIO A Qualification Sampling Period (GPIO0 to GPIO31) offset:0x00
    union GPA_16_L_REG GPAQSEL1;  // GPIO A Qualification Type (GPIO0 to GPIO15) offset:0x04
    union GPA_16_H_REG GPAQSEL2;  // GPIO A Qualification Type (GPIO16 to GPIO31) offset:0x08
    union GPA_16_L_REG GPAMUX1;   // GPIO A Peripheral Mux (GPIO0 to GPIO15) offset:0x0C
    union GPA_16_H_REG GPAMUX2;   // GPIO A Peripheral Mux (GPIO16 to GPIO31) offset:0x10
    union GPA_32_REG GPADIR;      // GPIO A Direction (GPIO0 to GPIO31) offset:0x14
    union GPA_32_REG GPAPUD;      // GPIO A Pull-Up Disable (GPIO0 to GPIO31) offset:0x18
    union GPA_32_REG GPAINV;      // GPIO A Input Inversion (GPIO0 to GPIO31) offset:0x1C
    union GPA_32_REG GPAODR;      // GPIO A Open Drain Output Mode (GPIO0 to GPIO31) offset:0x20
    union GPAAMSEL_REG GPAAMSEL;  // GPIO A Analog Mode Select (GPIO0 to GPIO31) offset:0x24
    union GPA_16_L_REG GPAGMUX1;  // GPIO A Peripheral Group Mux (GPIO0 to GPIO15) offset:0x28
    union GPA_16_H_REG GPAGMUX2;  // GPIO A Peripheral Group Mux (GPIO16 to GPIO31) offset:0x2C
    union GPA_32_REG GPALOCK;     // GPIO A Lock Register (GPIO0 to GPIO31) offset:0x30
    union GPA_32_REG GPACR;       // GPIO A Lock Register (GPIO0 to GPIO31) offset:0x34
    Uint32 rsvd1[6];              // Reserved offset: 0x38 ~ 0x4C
    union GPB_CTRL_REG GPBCTRL;   // GPIO B Qualification Sampling Period (GPIO32 to GPIO63) offset:0x50
    union GPB_16_L_REG GPBQSEL1;  // GPIO B Qualification Type (GPIO32 to GPIO47) offset:0x54
    union GPB_16_H_REG GPBQSEL2;  // GPIO B Qualification Type (GPIO48 to GPIO63) offset:0x58
    union GPB_16_L_REG GPBMUX1;   // GPIO B Peripheral Mux (GPIO32 to GPIO47) offset:0x5C
    union GPB_16_H_REG GPBMUX2;   // GPIO B Peripheral Mux (GPIO48 to GPIO63) offset:0x60
    union GPB_32_REG GPBDIR;      // GPIO B Direction (GPIO32 to GPIO63) offset:0x64
    union GPB_32_REG GPBPUD;      // GPIO B Pull-Up Disable (GPIO32 to GPIO63) offset:0x68
    union GPB_32_REG GPBINV;      // GPIO B Input Inversion (GPIO32 to GPIO63) offset:0x6C
    union GPB_32_REG GPBODR;      // GPIO B Open Drain Output Mode (GPIO32 to GPIO63) offset:0x70
    Uint32 rsvd2;                 // Reserved (PGBAMSEL) offset: 0x74
    union GPB_16_L_REG GPBGMUX1;  // GPIO B Peripheral Group Mux (GPIO32 to GPIO47) offset:0x78
    union GPB_16_H_REG GPBGMUX2;  // GPIO B Peripheral Group Mux (GPIO48 to GPIO63) offset:0x7C
    union GPB_32_REG GPBLOCK;     // GPIO B Lock Register (GPIO32 to GPIO63) offset:0x80
    union GPB_32_REG GPBCR;       // GPIO B Lock Register (GPIO32 to GPIO63) offset:0x84
    Uint32 rsvd3[6];              // Reserved offset:0x88~0x9C
    union GPC_CTRL_REG GPCCTRL;   // GPIO C Qualification Sampling Period (GPIO64 to GPIO95) offset:0xA0
    union GPC_16_L_REG GPCQSEL1;  // GPIO C Qualification Type (GPIO64 to GPIO79) offset:0xA4
    union GPC_16_H_REG GPCQSEL2;  // GPIO C Qualification Type (GPIO80 to GPIO95) offset:0xA8
    union GPC_16_L_REG GPCMUX1;   // GPIO C Peripheral Mux (GPIO64 to GPIO79) offset:0xAC
    union GPC_16_H_REG GPCMUX2;   // GPIO C Peripheral Mux (GPIO80 to GPIO95) offset:0xB0
    union GPC_32_REG GPCDIR;      // GPIO C Direction (GPIO64 to GPIO95) offset:0xB4
    union GPC_32_REG GPCPUD;      // GPIO C Pull-Up Disable (GPIO64 to GPIO95) offset:0xB8
    union GPC_32_REG GPCINV;      // GPIO C Input Inversion (GPIO64 to GPIO95) offset:0xBC
    union GPC_32_REG GPCODR;      // GPIO C Open Drain Output Mode (GPIO64 to GPIO95) offset:0xC0
    Uint32 rsvd4;                 // Reserved (PGCAMSEL) offset: 0xC4
    union GPC_16_L_REG GPCGMUX1;  // GPIO C Peripheral Group Mux (GPIO64 to GPIO79) offset:0xC8
    union GPC_16_H_REG GPCGMUX2;  // GPIO C Peripheral Group Mux (GPIO80 to GPIO95) offset:0xCC
    union GPC_32_REG GPCLOCK;     // GPIO C Lock Register (GPIO64 to GPIO95) offset:0xD0
    union GPC_32_REG GPCCR;       // GPIO C Lock Register (GPIO64 to GPIO95) offset:0xD4
    Uint32 rsvd5[6];              // Reserved offset:0xD8~0xEC
    union GPD_CTRL_REG GPDCTRL;   // GPIO D Qualification Sampling Period (GPIO96 to GPIO127) offset:0xF0
    union GPD_16_L_REG GPDQSEL1;  // GPIO D Qualification Type (GPIO96 to GPIO111) offset:0xF4
    union GPD_16_H_REG GPDQSEL2;  // GPIO D Qualification Type (GPIO112 to GPIO127) offset:0F8
    union GPD_16_L_REG GPDMUX1;   // GPIO D Peripheral Mux (GPIO96 to GPIO111) offset:0xFC
    union GPD_16_H_REG GPDMUX2;   // GPIO D Peripheral Mux (GPIO112 to GPIO127) offset:0x100
    union GPD_32_REG GPDDIR;      // GPIO D Direction (GPIO96 to GPIO127) offset:0x104
    union GPD_32_REG GPDPUD;      // GPIO D Pull-Up Disable (GPIO96 to GPIO127) offset:0x108
    union GPD_32_REG GPDINV;      // GPIO D Input Inversion (GPIO96 to GPIO127) offset:0x10C
    union GPD_32_REG GPDODR;      // GPIO D Open Drain Output Mode (GPIO96 to GPIO127) offset:0x110
    Uint32 rsvd6;                 // Reserved (PGDAMSEL) offset: 0x114
    union GPD_16_L_REG GPDGMUX1;  // GPIO D Peripheral Group Mux (GPIO96 to GPIO111) offset:0x118
    union GPD_16_H_REG GPDGMUX2;  // GPIO D Peripheral Group Mux (GPIO112 to GPIO127) offset:0x11C
    union GPD_32_REG GPDLOCK;     // GPIO D Lock Register (GPIO96 to GPIO111) offset:0x120
    union GPD_32_REG GPDCR;       // GPIO D Lock Register (GPIO112 to GPIO127) offset:0x124
    Uint32 rsvd7[6];              // Reserved offset:0x128~0x13C
    Uint32 rsvd8[60];             // Reserved (GPE~GPG) offset:0x140~0x22C
    union GPH_CTRL_REG GPHCTRL;   // GPIO H Qualification Sampling Period (GPIO224 to GPIO255) offset:0x230
    union GPH_QSEL1_REG GPHQSEL1; // GPIO H Qualification Type (GPIO224 to GPIO239) offset:0x234
    union GPH_QSEL2_REG GPHQSEL2; // GPIO H Qualification Type (GPIO240 to GPIO255) offset:0x238
    Uint32 vsvd9[2];              // Reserved (GPHMUX) offset:0x23C~0x240
    union GPH_32_REG GPHDIR;      // GPIO H Direction (GPIO96 to GPIO127) offset:0x244
    union GPH_32_REG GPHPUD;      // GPIO H Pull-Up Disable (GPIO224 to GPIO255) offset:0x248
    union GPH_32_REG GPHINV;      // GPIO H Input Inversion (GPIO224 to GPIO255) offset:0x24C
    union GPD_32_REG GPHODR;      // GPIO H Open Drain Output Mode (GPIO96 to GPIO127) offset:0x250
    union GPH_32_REG GPHAMSEL;    // GPIO H Analog Mode Select (GPIO224 to GPIO255) offset:0x254
    Uint32 rsvd10[2];             // Reserved (GPHGMUX) offset:0x258~0x225C
    union GPH_32_REG GPHLOCK;     // GPIO H Lock Register (GPIO224 to GPIO255) offset:0x260
    union GPH_32_REG GPHCR;       // GPIO H Lock Commit Register (GPIO224 to GPIO255) offset:0x264
    Uint32 rsvd11[6];             // Reserved offset:0x268~0x27C
    union SPSEL_REG SPSEL;        // LIN_A And SCI_C Switch Taggle, offset:0x280
    /* clang-format on */
};

struct GPIO_DATA_REGS
{
    union GPA_32_REG GPADAT;    // GPIO A Data Register (GPIO0 to GPIO31), offset:0x00
    union GPA_32_REG GPASET;    // GPIO A Output Set (GPIO0 to GPIO31), offset: 0x04
    union GPA_32_REG GPACLEAR;  // GPIO A Output Clear (GPIO0 to GPIO31), offset: 0x08
    union GPA_32_REG GPATOGGLE; // GPIO A Output Toggle (GPIO0 to GPIO31), offset: 0x0C
    union GPB_32_REG GPBDAT;    // GPIO B Data Register (GPIO32 to GPIO63), offset: 0x10
    union GPB_32_REG GPBSET;    // GPIO B Output Set (GPIO32 to GPIO63), offset: 0x14
    union GPB_32_REG GPBCLEAR;  // GPIO B Output Clear (GPIO32 to GPIO63), offset: 0x18
    union GPB_32_REG GPBTOGGLE; // GPIO B Output Toggle (GPIO32 to GPIO63), offset: 0x1C
    union GPC_32_REG GPCDAT;    // GPIO C Data Register (GPIO64 to GPIO95), offset: 0x20
    union GPC_32_REG GPCSET;    // GPIO C Output Set (GPIO64 to GPIO95), offset: 0x24
    union GPC_32_REG GPCCLEAR;  // GPIO C Output Clear (GPIO64 to GPIO95), offset: 0x28
    union GPC_32_REG GPCTOGGLE; // GPIO C Output Toggle (GPIO64 to GPIO95), offset: 0x2C
    union GPD_32_REG GPDDAT;    // GPIO D Data Register (GPIO96 to GPIO127) offset: 0x30
    union GPD_32_REG GPDSET;    // GPIO D Output Set (GPIO96 to GPIO127), offset: 0x34
    union GPD_32_REG GPDCLEAR;  // GPIO D Output Clear (GPIO96 to GPIO127), offset: 0x38
    union GPD_32_REG GPDTOGGLE; // GPIO D Output Toggle (GPIO96 to GPIO127), offset: 0x3C
    Uint32 rsvd[12];            // Reserved, 0x40~0x6C
    union GPH_32_REG GPHDAT;    // GPIO H Data Register (GPIO224 to GPIO247), offset:0x70
    union GPB_32_REG GPHSET;    // GPIO H Output Set (GPIO224 to GPIO247), offset: 0x74
    union GPB_32_REG GPHCLEAR;  // GPIO H Output Clear (GPIO224 to GPIO247), offset: 0x78
    union GPB_32_REG GPHTOGGLE; // GPIO H Output Toggle (GPIO32 to GPIO63), offset: 0x7C
};

//---------------------------------------------------------------------------
// GPIO External References & Function Declarations:
//
extern volatile struct GPIO_CTRL_REGS GpioCtrlRegs;
extern volatile struct GPIO_DATA_REGS GpioDataRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
