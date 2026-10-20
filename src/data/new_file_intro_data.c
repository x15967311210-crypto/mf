#include "macros.h"
#include "oam.h"

#include "gba/memory.h"

#include "constants/text.h"

#include "data/new_file_intro_data.h"

static const u16 sOamFrame_597708[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 128, 4, 0),
};

static const u16 sOamFrame_597710[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 129, 4, 0),
};

static const u16 sOamFrame_597718[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 130, 4, 0),
};

static const u16 sOamFrame_597720[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 131, 4, 0),
};

static const u16 sOamFrame_597728[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 8, 0),
};

static const u16 sOamFrame_597730[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 8, 0),
};

static const u16 sOamFrame_597738[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 8, 0),
};

static const u16 sOamFrame_597740[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 8, 0),
};

static const u16 sOamFrame_597748[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 24, 8, 0),
};

static const u16 sOamFrame_597750[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_59775e[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597766[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597774[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-20, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(3, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597788[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597790[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-20, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(3, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_5977a4[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(0, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5977b2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-32, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
};

static const u16 sOamFrame_5977d8[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-8, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(16, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
};

static const u16 sOamFrame_5977f2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-64, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(-64, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
};

static const u16 sOamFrame_597800[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597856[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5978ac[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597902[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597958[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5979ae[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597a04[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597a5a[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597ab0[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597b06[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597b5c[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597bb2[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u8 sPadding_597c08[2] = {0, 0};

static const u16 sOamFrame_597c0a[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c32[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(-12, -8, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c6a[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(0, -20, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(8, -20, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
};

static const u16 sOamFrame_597cb4[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-4, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
};

static const u16 sOamFrame_597d04[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(-16, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-4, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597d5a[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(-16, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(0, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 3, 0),
    OAM_ENTRY(-4, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597da4[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-8, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-16, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(0, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(-8, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 3, 0),
    OAM_ENTRY(-4, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597ddc[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-8, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(-16, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
    OAM_ENTRY(0, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 3, 0),
};

static const u16 sOamFrame_597df6[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -44, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(0, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
    OAM_ENTRY(-8, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 3, 0),
};

static const u16 sOamFrame_597e0a[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
};

static const u16 sOamFrame_597e12[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e20[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e28[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e36[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e44[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e4c[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e5a[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(14, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 512, 2, 0),
    OAM_ENTRY(46, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 580, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e6e[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(14, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 517, 2, 0),
    OAM_ENTRY(46, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 585, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e82[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(13, -21, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e90[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-30, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 526, 2, 0),
    OAM_ENTRY(-2, -27, OAM_DIMS_32x32, OAM_X_FLIP, 526, 2, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597ea4[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597eac[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-30, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 530, 2, 0),
    OAM_ENTRY(-2, -25, OAM_DIMS_32x32, OAM_X_FLIP, 530, 2, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

const struct FrameData sOam_597ec0[2] = {
    [0] = {
        .pFrame = sOamFrame_597708,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ed0[2] = {
    [0] = {
        .pFrame = sOamFrame_597710,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ee0[2] = {
    [0] = {
        .pFrame = sOamFrame_597718,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ef0[2] = {
    [0] = {
        .pFrame = sOamFrame_597720,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f00[2] = {
    [0] = {
            .pFrame = sOamFrame_597728,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f10[2] = {
    [0] = {
            .pFrame = sOamFrame_597730,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f20[2] = {
    [0] = {
            .pFrame = sOamFrame_597738,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f30[2] = {
    [0] = {
            .pFrame = sOamFrame_597740,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f40[2] = {
    [0] = {
            .pFrame = sOamFrame_597748,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f50[7] = {
    [0] = {
            .pFrame = sOamFrame_597e5a,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_59775e,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e6e,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e5a,
            .timer = 1
    },
    [4] = {
            .pFrame = sOamFrame_59775e,
            .timer = 1
    },
    [5] = {
            .pFrame = sOamFrame_597e82,
            .timer = 1
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f88[5] = {
    [0] = {
            .pFrame = sOamFrame_597e90,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597788,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597eac,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597788,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fb0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977a4,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fc0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977b2,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fd0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977d8,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fe0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977f2,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ff0[2] = {
    [0] = {
            .pFrame = sOamFrame_597800,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598000[12] = {
    [0] = {
            .pFrame = sOamFrame_597c0a,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_597c12,
            .timer = 4
    },
    [2] = {
            .pFrame = sOamFrame_597c32,
            .timer = 4
    },
    [3] = {
            .pFrame = sOamFrame_597c6a,
            .timer = 4
    },
    [4] = {
            .pFrame = sOamFrame_597cb4,
            .timer = 4
    },
    [5] = {
            .pFrame = sOamFrame_597d04,
            .timer = 4
    },
    [6] = {
            .pFrame = sOamFrame_597d5a,
            .timer = 6
    },
    [7] = {
            .pFrame = sOamFrame_597da4,
            .timer = 7
    },
    [8] = {
            .pFrame = sOamFrame_597ddc,
            .timer = 8
    },
    [9] = {
            .pFrame = sOamFrame_597df6,
            .timer = 9
    },
    [10] = {
            .pFrame = sOamFrame_597e0a,
            .timer = 10
    },
    [11] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598060[5] = {
    [0] = {
            .pFrame = sOamFrame_597e12,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597e20,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e28,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e20,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598088[5] = {
    [0] = {
            .pFrame = sOamFrame_597e36,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597e44,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e4c,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e44,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const u16 sIntroSamusShipPal[5 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_ship.pal");
const u16 sPal_598150[2 * PAL_ROW] = INCBIN_U16("data/new_file_intro/598150.pal"); // Loaded to PALRAM but not used?

const u32 sIntroSamusHelmetCloseupTilemap[172] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup.tm.lz");

static const u8 sBlob_598440_598818[] = INCBIN_U8("data/Blob_598440_598818.bin");

const u16 sIntroSamusHelmetCloseupPal[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_helmet_closeup.pal");

const u32 sIntroSamusShipFlyingTextTilemap[125] = INCBIN_U32("data/new_file_intro/samus_ship_flying_text.tm.lz");

const u16 sPal_598a8c[1 * PAL_ROW] = INCBIN_U16("data/new_file_intro/598a8c.pal");
const u16 sIntroSamusCloseupGrayscalePal[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_helmet_closeup_grayscale.pal");

const u16 sSr388SpaceAndSurfacePal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/sr388_space_and_surface.pal");

const u32 sIntroSr388SurfaceTilemap[551] = INCBIN_U32("data/new_file_intro/sr388_surface.tm.lz");
const u32 sIntroSr388SpaceBgTilemap[265] = INCBIN_U32("data/new_file_intro/sr388_space_bg.tm.lz");
const u32 sIntroSr388PlanetTilemap[199] = INCBIN_U32("data/new_file_intro/sr388_planet.tm.lz");

static const u16 sOamFrame_599d08[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 0, 8, 0),
};

static const u16 sOamFrame_599d10[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 8, 0),
};

static const u16 sOamFrame_599d18[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 8, 0),
};

static const u16 sOamFrame_599d20[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 8, 0),
};

static const u16 sOamFrame_599d28[OAM_DATA_SIZE(52)] = {
    52,
    OAM_ENTRY_MODE(0, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 152, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -48, OAM_DIMS_32x8, OAM_NO_FLIP, 216, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(64, -64, OAM_DIMS_32x32, OAM_NO_FLIP, 256, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(96, -64, OAM_DIMS_8x32, OAM_NO_FLIP, 287, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 260, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 264, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, -64, OAM_DIMS_64x32, OAM_NO_FLIP, 144, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(32, -64, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 248, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-16, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 266, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 332, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(16, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 334, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(24, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 335, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(32, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 272, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(40, -32, OAM_DIMS_64x32, OAM_NO_FLIP, 273, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(40, 0, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-80, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 402, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-48, 0, OAM_DIMS_8x32, OAM_NO_FLIP, 512, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 513, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 545, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 16, OAM_DIMS_16x16, OAM_NO_FLIP, 579, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 609, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 547, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(8, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 519, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(8, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 583, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 16, OAM_DIMS_8x16, OAM_NO_FLIP, 582, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 16, OAM_DIMS_8x16, OAM_NO_FLIP, 581, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 549, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 0, OAM_DIMS_8x16, OAM_NO_FLIP, 518, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 517, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(16, 32, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(80, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 620, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-88, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 281, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, 32, OAM_DIMS_32x32, OAM_NO_FLIP, 283, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 392, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 502, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-16, 40, OAM_DIMS_16x16, OAM_NO_FLIP, 440, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 48, OAM_DIMS_16x8, OAM_NO_FLIP, 470, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 407, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 409, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 406, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 439, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 438, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-80, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 523, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-56, 88, OAM_DIMS_32x8, OAM_NO_FLIP, 442, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-72, 80, OAM_DIMS_32x8, OAM_NO_FLIP, 410, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 414, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 478, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 72, OAM_DIMS_8x16, OAM_NO_FLIP, 587, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 588, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
};

static const u16 sOamFrame_599e62[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(-128, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-64, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 744, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(64, 0, OAM_DIMS_32x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(96, 0, OAM_DIMS_16x32, OAM_NO_FLIP, 764, 0, 0),
    OAM_ENTRY(96, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 892, 0, 0),
    OAM_ENTRY(-128, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 992, 0, 0),
    OAM_ENTRY(-96, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 996, 0, 0),
    OAM_ENTRY(-64, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1000, 0, 0),
    OAM_ENTRY(-32, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 0, 0),
    OAM_ENTRY(0, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 0, 0),
    OAM_ENTRY(32, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1012, 0, 0),
    OAM_ENTRY(64, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1016, 0, 0),
    OAM_ENTRY(96, 64, OAM_DIMS_16x8, OAM_NO_FLIP, 1020, 0, 0),
    OAM_ENTRY(80, -64, OAM_DIMS_32x64, OAM_NO_FLIP, 506, 0, 0),
    OAM_ENTRY(72, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 697, 0, 0),
    OAM_ENTRY(-128, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 704, 0, 0),
};

static const u16 sOamFrame_599eca[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(80, -64, OAM_DIMS_32x64, OAM_NO_FLIP, 506, 0, 0),
    OAM_ENTRY(72, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 697, 0, 0),
    OAM_ENTRY(-128, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 704, 0, 0),
};

static const u16 sOamFrame_599ede[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(2, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_599ee6[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(3, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 18, 1, 0),
};

static const u16 sOamFrame_599eee[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(4, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 20, 1, 0),
};

static const u16 sOamFrame_599ef6[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(2, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 124, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 30, 1, 0),
};

static const u16 sOamFrame_599f04[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f12[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 60, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f2c[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f46[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f6c[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f98[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599fd0[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_59a00e[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(-30, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 0, 0),
    OAM_ENTRY(-14, 80, OAM_DIMS_8x8, OAM_NO_FLIP, 54, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_59a058[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(-30, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 0, 0),
    OAM_ENTRY(-14, 80, OAM_DIMS_8x8, OAM_NO_FLIP, 54, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
};

static const u16 sOamFrame_59a096[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 798, 6, 0),
};

const struct FrameData sOam_59a0a0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d08,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0b0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d10,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0c0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d18,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0d0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d20,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0e0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d28,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0f0[2] = {
    [0] = {
            .pFrame = sOamFrame_599e62,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a100[13] = {
    [0] = {
            .pFrame = sOamFrame_59a096,
            .timer = 80
    },
    [1] = {
            .pFrame = sOamFrame_599ef6,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_599f04,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_599f12,
            .timer = 1
    },
    [4] = {
            .pFrame = sOamFrame_599f2c,
            .timer = 1
    },
    [5] = {
            .pFrame = sOamFrame_599f46,
            .timer = 1
    },
    [6] = {
            .pFrame = sOamFrame_599f6c,
            .timer = 1
    },
    [7] = {
            .pFrame = sOamFrame_599f98,
            .timer = 1
    },
    [8] = {
            .pFrame = sOamFrame_599fd0,
            .timer = 1
    },
    [9] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 212
    },
    [10] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 220
    },
    [11] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 200
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a168[2] = {
    [0] = {
            .pFrame = sOamFrame_599eca,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a178[8] = {
    [0] = {
            .pFrame = sOamFrame_59a096,
            .timer = 116
    },
    [1] = {
            .pFrame = sOamFrame_599ede,
            .timer = 12
    },
    [2] = {
            .pFrame = sOamFrame_599ee6,
            .timer = 8
    },
    [3] = {
            .pFrame = sOamFrame_599eee,
            .timer = 4
    },
    [4] = {
            .pFrame = sOamFrame_599d28,
            .timer = 140
    },
    [5] = {
            .pFrame = sOamFrame_59a096,
            .timer = 240
    },
    [6] = {
            .pFrame = sOamFrame_59a096,
            .timer = 200
    },
    [7] = FRAME_DATA_TERMINATOR
};

const u32 sIntroSr388SpaceAndSurfaceObjGfx[3538] = INCBIN_U32("data/new_file_intro/sr388_space_and_surface_objects.gfx.lz");
const u16 sIntroSr388SpaceAndSurfaceObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/sr388_space_and_surface_objects.pal");

const u8 sArray_59db00[8] = {20, 30, 40, 50, 40, 30, 0, 0};

const u32 sIntroHornoadEncounterObjGfx[4252] = INCBIN_U32("data/new_file_intro/hornoad_encounter_obj.gfx.lz");
const u16 sIntroHornoadEncounterObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/hornoad_encounter_obj.pal");

static const u16 sOamFrame_5a1f78[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1f98[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 534, 8, 0),
	OAM_ENTRY(-12, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-5, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-5, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-13, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1fb8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -7, OAM_DIMS_16x16, OAM_X_FLIP, 538, 8, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(2, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(2, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-6, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1fd8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -13, OAM_DIMS_16x16, OAM_X_FLIP, 540, 8, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(2, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(2, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-6, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1ff8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -15, OAM_DIMS_16x16, OAM_X_FLIP, 542, 8, 0),
	OAM_ENTRY(-16, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2018[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-16, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2038[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-16, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2058[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -15, OAM_DIMS_16x8, OAM_X_FLIP, 613, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 528, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 530, 9, 0),
};

static const u16 sOamFrame_5a2078[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2098[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_X_FLIP, 525, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 581, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 527, 9, 0),
};

static const u16 sOamFrame_5a20b8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a20d8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a20f8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 552, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2118[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-10, -16, OAM_DIMS_8x16, OAM_X_FLIP, 585, 9, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 590, 9, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_8x16, OAM_X_FLIP, 578, 9, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x16, OAM_X_FLIP, 585, 9, 0),
};

static const u16 sOamFrame_5a2132[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(2, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 585, 9, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 590, 9, 0),
	OAM_ENTRY(4, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 578, 9, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 585, 9, 0),
};

static const u16 sOamFrame_5a214c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-6, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-4, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(0, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a216c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 552, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a218c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 615, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a21b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a21d2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 534, 9, 0),
	OAM_ENTRY(-12, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-5, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-13, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(-5, -14, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a21f2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -7, OAM_DIMS_16x16, OAM_X_FLIP, 538, 9, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(2, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-6, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2212[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -13, OAM_DIMS_16x16, OAM_X_FLIP, 540, 9, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(2, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-6, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2232[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -15, OAM_DIMS_16x16, OAM_X_FLIP, 542, 9, 0),
	OAM_ENTRY(-16, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(-8, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2252[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-16, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2272[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-16, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2292[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-7, -15, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -22, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -15, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -21, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22d2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-9, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22f2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-13, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-10, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-17, -23, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2312[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 583, 9, 0),
};

static const u16 sOamFrame_5a2332[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-6, -23, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-16, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 542, 9, 0),
	OAM_ENTRY(-6, -14, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(1, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(0, -11, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-7, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2358[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -22, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_X_FLIP, 538, 9, 0),
	OAM_ENTRY(-7, -14, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-1, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-9, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a237e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-14, -23, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-10, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a23a4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-15, -22, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-9, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a23ca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 618, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a23ea[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 528, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 530, 9, 0),
};

static const u16 sOamFrame_5a2404[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -13, OAM_DIMS_16x8, OAM_X_FLIP, 618, 9, 0),
	OAM_ENTRY(-8, -21, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2424[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-9, -11, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2444[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-8, -21, OAM_DIMS_16x16, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2464[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x8, OAM_X_FLIP, 579, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2484[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -11, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24c4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24e4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2504[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -11, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
};

static const u16 sOamFrame_5a2524[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
};

static const u16 sOamFrame_5a2544[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2564[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2584[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-19, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 647, 3, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 649, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 711, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 713, 3, 0),
};

static const u16 sOamFrame_5a25bc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 652, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 716, 3, 0),
};

static const u16 sOamFrame_5a25e8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -33, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -41, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -41, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 643, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 707, 3, 0),
};

static const u16 sOamFrame_5a2614[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-19, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 640, 3, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 642, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 704, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 706, 3, 0),
};

static const u16 sOamFrame_5a264c[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 645, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 709, 3, 0),
};

static const u16 sOamFrame_5a2678[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -33, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -41, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -41, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 714, 3, 0),
};

static const u16 sOamFrame_5a26a4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-12, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 868, 3, 0),
	OAM_ENTRY(4, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 870, 3, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 996, 3, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 998, 3, 0),
};

static const u16 sOamFrame_5a26be[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -40, OAM_DIMS_16x32, OAM_X_FLIP, 868, 3, 0),
	OAM_ENTRY(-12, -40, OAM_DIMS_8x32, OAM_X_FLIP, 870, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_16x8, OAM_X_FLIP, 996, 3, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_8x8, OAM_X_FLIP, 998, 3, 0),
};

static const u16 sOamFrame_5a26d8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 686, 3, 0),
	OAM_ENTRY(4, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 688, 3, 0),
};

static const u16 sOamFrame_5a2704[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -24, OAM_DIMS_16x8, OAM_X_FLIP, 960, 3, 0),
	OAM_ENTRY(-6, -24, OAM_DIMS_8x8, OAM_X_FLIP, 962, 3, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_32x16, OAM_X_FLIP, 896, 3, 0),
	OAM_ENTRY(-6, -40, OAM_DIMS_16x8, OAM_X_FLIP, 865, 3, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_X_FLIP, 867, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_16x16, OAM_X_FLIP, 686, 3, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x16, OAM_X_FLIP, 688, 3, 0),
};

static const u16 sOamFrame_5a2730[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 606, 3, 0),
};

static const u16 sOamFrame_5a273e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 3, 0),
	OAM_ENTRY(7, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 605, 3, 0),
};

static const u16 sOamFrame_5a274c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 694, 3, 0),
	OAM_ENTRY(1, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 606, 3, 0),
};

static const u16 sOamFrame_5a275a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 694, 3, 0),
	OAM_ENTRY(2, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 3, 0),
};

static const u16 sOamFrame_5a2768[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 728, 3, 0),
};

static const u16 sOamFrame_5a2770[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 729, 3, 0),
};

static const u16 sOamFrame_5a2778[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 730, 3, 0),
};

static const u16 sOamFrame_5a2780[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 731, 3, 0),
};

static const u16 sOamFrame_5a2788[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 732, 3, 0),
};

static const u16 sOamFrame_5a2790[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a27aa[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -1, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -17, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -1, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a27dc[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-16, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -18, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -2, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -2, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-32, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -33, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-32, -17, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(12, -8, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a2826[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-16, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -19, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -3, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -3, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-32, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -34, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-32, -18, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-4, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(12, -9, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(12, -25, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-4, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5a287c[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-16, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -21, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-32, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -35, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-32, -19, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-4, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(12, -26, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(12, -10, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-4, -10, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-33, -41, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
	OAM_ENTRY(-26, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5a28de[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-32, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-32, -20, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -36, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-4, -27, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(12, -27, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(12, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-4, -11, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-34, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(17, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(-40, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(-28, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(10, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
};

static const u16 sOamFrame_5a2934[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-4, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-4, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(12, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(12, -28, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-35, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(18, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(-41, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(-30, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(-34, 2, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(17, 1, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
};

static const u16 sOamFrame_5a297e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(19, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(-42, -50, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(25, -41, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(-36, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(14, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(20, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
};

static const u16 sOamFrame_5a29a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(8, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(-43, -51, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(26, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(-38, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(23, 7, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
};

static const u16 sOamFrame_5a29c4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(27, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
};

static const u16 sOamFrame_5a29d2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 800, 4, 0),
};

static const u16 sOamFrame_5a29da[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 802, 4, 0),
};

static const u16 sOamFrame_5a29e2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 804, 4, 0),
};

static const u16 sOamFrame_5a29ea[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 806, 4, 0),
};

static const u16 sOamFrame_5a29f2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 4, 0),
};

static const u16 sOamFrame_5a29fa[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 810, 4, 0),
};

static const u16 sOamFrame_5a2a02[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a2a1c[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
};

static const u16 sOamFrame_5a2a36[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
};

static const u16 sOamFrame_5a2a50[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
};

static const u16 sOamFrame_5a2a6a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
};

static const u16 sOamFrame_5a2a84[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-64, -24, OAM_DIMS_64x32, OAM_NO_FLIP, 816, 14, 0),
	OAM_ENTRY(-64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 944, 14, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 948, 14, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 952, 14, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
};

static const u16 sOamFrame_5a2ac8[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
};

const struct FrameData sOam_5a2af0[13] = {
	[0] = {
		.pFrame = sOamFrame_5a2484,
		.timer = 34
	},
	[1] = {
		.pFrame = sOamFrame_5a24a4,
		.timer = 22
	},
	[2] = {
		.pFrame = sOamFrame_5a24c4,
		.timer = 18
	},
	[3] = {
		.pFrame = sOamFrame_5a24e4,
		.timer = 16
	},
	[4] = {
		.pFrame = sOamFrame_5a2504,
		.timer = 34
	},
	[5] = {
		.pFrame = sOamFrame_5a2524,
		.timer = 22
	},
	[6] = {
		.pFrame = sOamFrame_5a2544,
		.timer = 18
	},
	[7] = {
		.pFrame = sOamFrame_5a2564,
		.timer = 16
	},
	[8] = {
		.pFrame = sOamFrame_5a2504,
		.timer = 34
	},
	[9] = {
		.pFrame = sOamFrame_5a2524,
		.timer = 22
	},
	[10] = {
		.pFrame = sOamFrame_5a2544,
		.timer = 18
	},
	[11] = {
		.pFrame = sOamFrame_5a2564,
		.timer = 16
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_IdleUnused[2] = {
	[0] = {
		.pFrame = sOamFrame_5a1f78,
		.timer = 10
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_JumpingUnused[5] = {
	[0] = {
		.pFrame = sOamFrame_5a1f98,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a1fb8,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a1fd8,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a1ff8,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_BouncingUnused[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2018,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5a2038,
		.timer = 3
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Shaking[5] = {
	[0] = {
		.pFrame = sOamFrame_5a2078,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5a2058,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a2078,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5a2098,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Panting[5] = {
	[0] = {
		.pFrame = sOamFrame_5a20b8,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a20f8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Chomping[12] = {
	[0] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a2292,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a22b2,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a22d2,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5a22f2,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5a2312,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5a2292,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5a22b2,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5a22d2,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5a22f2,
		.timer = 2
	},
	[11] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2c58[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2118,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Biting[5] = {
	[0] = {
		.pFrame = sOamFrame_5a216c,
		.timer = 10
	},
	[1] = {
		.pFrame = sOamFrame_5a218c,
		.timer = 10
	},
	[2] = {
		.pFrame = sOamFrame_5a216c,
		.timer = 10
	},
	[3] = {
		.pFrame = sOamFrame_5a21b2,
		.timer = 10
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Jumping[5] = {
	[0] = {
		.pFrame = sOamFrame_5a21d2,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a21f2,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a2212,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a2232,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Bouncing[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2252,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 3
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_MidAir[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2332,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a2358,
		.timer = 255
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Walking[7] = {
	[0] = {
		.pFrame = sOamFrame_5a2584,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a25bc,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a25e8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a2614,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5a264c,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5a2678,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d28[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d38[3] = {
	[0] = {
		.pFrame = sOamFrame_5a26a4,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a26be,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Turning[3] = {
	[0] = {
		.pFrame = sOamFrame_5a26be,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a26a4,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Idle[2] = {
	[0] = {
		.pFrame = sOamFrame_5a26d8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d78[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d88[2] = {
	[0] = {
		.pFrame = sOamFrame_5a26d8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d98[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileOam_Horizontal[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2730,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5a273e,
		.timer = 2
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileOam_Diagonal[3] = {
	[0] = {
		.pFrame = sOamFrame_5a274c,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5a275a,
		.timer = 2
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileTrailOam[6] = {
	[0] = {
		.pFrame = sOamFrame_5a2768,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a2770,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a2778,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a2780,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5a2788,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileExplosionOam_Small[6] = {
	[0] = {
		.pFrame = sOamFrame_5a2a02,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5a2a1c,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5a2a36,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5a2a50,
		.timer = 6
	},
	[4] = {
		.pFrame = sOamFrame_5a2a6a,
		.timer = 6
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileExplosionOam_Big[11] = {
	[0] = {
		.pFrame = sOamFrame_5a2790,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a27aa,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a27dc,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a2826,
		.timer = 6
	},
	[4] = {
		.pFrame = sOamFrame_5a287c,
		.timer = 6
	},
	[5] = {
		.pFrame = sOamFrame_5a28de,
		.timer = 6
	},
	[6] = {
		.pFrame = sOamFrame_5a2934,
		.timer = 6
	},
	[7] = {
		.pFrame = sOamFrame_5a297e,
		.timer = 6
	},
	[8] = {
		.pFrame = sOamFrame_5a29a4,
		.timer = 6
	},
	[9] = {
		.pFrame = sOamFrame_5a29c4,
		.timer = 6
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388XParasiteOam_Floating[7] = {
	[0] = {
		.pFrame = sOamFrame_5a29d2,
		.timer = 5
	},
	[1] = {
		.pFrame = sOamFrame_5a29da,
		.timer = 5
	},
	[2] = {
		.pFrame = sOamFrame_5a29e2,
		.timer = 5
	},
	[3] = {
		.pFrame = sOamFrame_5a29ea,
		.timer = 5
	},
	[4] = {
		.pFrame = sOamFrame_5a29f2,
		.timer = 5
	},
	[5] = {
		.pFrame = sOamFrame_5a29fa,
		.timer = 5
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388CaveEntranceBgOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2a84,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BlackRectangeOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2ac8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5a2ee8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-5, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a2ef6[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 2, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a2f04[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 6, 0, 0),
	OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 37, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a2f1e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 9, 0, 0),
	OAM_ENTRY(-12, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 72, 0, 0),
	OAM_ENTRY(8, -21, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 0, 0),
	OAM_ENTRY(-16, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5a2f38[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-7, -39, OAM_DIMS_16x32, OAM_NO_FLIP, 12, 0, 0),
	OAM_ENTRY(-10, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 0, 0),
	OAM_ENTRY(9, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a2f4c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 14, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 18, 0, 0),
	OAM_ENTRY(-5, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 64, 0, 0),
};

static const u16 sOamFrame_5a2f60[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-7, -37, OAM_DIMS_16x32, OAM_NO_FLIP, 16, 0, 0),
	OAM_ENTRY(6, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 82, 0, 0),
	OAM_ENTRY(9, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 50, 0, 0),
};

static const u16 sOamFrame_5a2f74[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -39, OAM_DIMS_16x32, OAM_NO_FLIP, 20, 0, 0),
	OAM_ENTRY(8, -33, OAM_DIMS_8x32, OAM_NO_FLIP, 22, 0, 0),
	OAM_ENTRY(-16, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 19, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a2f8e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-7, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 23, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 121, 0, 0),
	OAM_ENTRY(9, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 57, 0, 0),
	OAM_ENTRY(-15, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 25, 0, 0),
};

static const u16 sOamFrame_5a2fa8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-6, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 26, 0, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 83, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a2fbc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 61, 0, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a2fd0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(2, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 2, 0, 0),
	OAM_ENTRY(-15, -16, OAM_DIMS_16x16, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a2fe4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 137, 0, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 168, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 6, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 8, 0, 0),
	OAM_ENTRY(8, -32, OAM_DIMS_8x8, OAM_X_FLIP, 37, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a300a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 30, 0, 0),
	OAM_ENTRY(6, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 9, 0, 0),
	OAM_ENTRY(4, -18, OAM_DIMS_8x16, OAM_X_FLIP, 72, 0, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a302a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(1, -27, OAM_DIMS_8x8, OAM_NO_FLIP, 60, 0, 0),
	OAM_ENTRY(-9, -39, OAM_DIMS_16x32, OAM_X_FLIP, 12, 0, 0),
	OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_X_FLIP, 75, 0, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x8, OAM_X_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a3044[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-3, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 61, 0, 0),
	OAM_ENTRY(-12, -40, OAM_DIMS_16x32, OAM_X_FLIP, 14, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a3058[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-10, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 92, 0, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 80, 0, 0),
	OAM_ENTRY(-9, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 94, 0, 0),
	OAM_ENTRY(-14, -15, OAM_DIMS_8x16, OAM_X_FLIP, 82, 0, 0),
	OAM_ENTRY(-17, -29, OAM_DIMS_8x8, OAM_X_FLIP, 50, 0, 0),
};

static const u16 sOamFrame_5a3078[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 130, 0, 0),
	OAM_ENTRY(2, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-8, -39, OAM_DIMS_16x32, OAM_X_FLIP, 20, 0, 0),
	OAM_ENTRY(-16, -33, OAM_DIMS_8x32, OAM_X_FLIP, 22, 0, 0),
	OAM_ENTRY(0, -7, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3098[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(1, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-9, -40, OAM_DIMS_16x32, OAM_X_FLIP, 23, 0, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_X_FLIP, 121, 0, 0),
	OAM_ENTRY(-17, -16, OAM_DIMS_8x16, OAM_X_FLIP, 57, 0, 0),
	OAM_ENTRY(7, -32, OAM_DIMS_8x8, OAM_X_FLIP, 25, 0, 0),
};

static const u16 sOamFrame_5a30be[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-6, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 134, 0, 0),
	OAM_ENTRY(2, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 136, 0, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x32, OAM_X_FLIP, 26, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x16, OAM_X_FLIP, 83, 0, 0),
	OAM_ENTRY(-2, -8, OAM_DIMS_16x8, OAM_X_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a30de[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 200, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 201, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 192, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3110[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 194, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 202, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 203, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3142[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 196, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 232, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 233, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3174[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 180, 0, 0),
	OAM_ENTRY(-11, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 0, 0),
	OAM_ENTRY(-3, -33, OAM_DIMS_8x8, OAM_NO_FLIP, 143, 0, 0),
	OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 198, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 234, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 235, 0, 0),
	OAM_ENTRY(-18, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a31a6[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 200, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 201, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 192, 0, 0),
};

static const u16 sOamFrame_5a31d2[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 194, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 202, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 203, 0, 0),
};

static const u16 sOamFrame_5a31fe[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 196, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 232, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 233, 0, 0),
};

static const u16 sOamFrame_5a322a[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 186, 0, 0),
	OAM_ENTRY(-4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 159, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 198, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 234, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 235, 0, 0),
};

static const u16 sOamFrame_5a3256[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 200, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 201, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 192, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a328e[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 194, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 202, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 203, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a32c6[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 196, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 232, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 233, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a32fe[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-10, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 180, 0, 0),
    OAM_ENTRY(-11, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 0, 0),
    OAM_ENTRY(-3, -33, OAM_DIMS_8x8, OAM_NO_FLIP, 143, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 198, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 234, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 235, 0, 0),
    OAM_ENTRY(-21, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-18, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3336[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 200, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 201, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 192, 0, 0),
};

static const u16 sOamFrame_5a3368[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 194, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 202, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 203, 0, 0),
};

static const u16 sOamFrame_5a339a[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 196, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 232, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 233, 0, 0),
};

static const u16 sOamFrame_5a33cc[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(13, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(2, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-6, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 186, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 159, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 198, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 234, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 235, 0, 0),
};

static const u16 sOamFrame_5a33fe[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 206, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 268, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 270, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a342a[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 271, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 273, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a3456[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 300, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 302, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a3482[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 0, 0),
    OAM_ENTRY(-12, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 303, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 305, 0, 0),
    OAM_ENTRY(-19, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a34ae[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 218, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 216, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 268, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 270, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 206, 0, 0),
};

static const u16 sOamFrame_5a34e0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 250, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 248, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 271, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 273, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 208, 0, 0),
};

static const u16 sOamFrame_5a3512[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 251, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 219, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 264, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 300, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 302, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 210, 0, 0),
};

static const u16 sOamFrame_5a3544[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 0, 0),
    OAM_ENTRY(-2, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 221, 0, 0),
    OAM_ENTRY(14, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 252, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 274, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 266, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 303, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 305, 0, 0),
    OAM_ENTRY(-4, -35, OAM_DIMS_16x16, OAM_X_FLIP, 212, 0, 0),
};

static const u16 sOamFrame_5a3576[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 206, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 268, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 270, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a35a8[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 271, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 273, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a35da[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 300, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 302, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a360c[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 0, 0),
    OAM_ENTRY(-12, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 303, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 305, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-19, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a363e[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 218, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 216, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 268, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 270, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 206, 0, 0),
};

static const u16 sOamFrame_5a3676[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 250, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 248, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 271, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 273, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 208, 0, 0),
};

static const u16 sOamFrame_5a36ae[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 251, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 219, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 264, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 300, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 302, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 210, 0, 0),
};

static const u16 sOamFrame_5a36e6[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 0, 0),
    OAM_ENTRY(-2, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 221, 0, 0),
    OAM_ENTRY(12, -39, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(14, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 252, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 274, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 266, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 303, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 305, 0, 0),
    OAM_ENTRY(-4, -35, OAM_DIMS_16x16, OAM_X_FLIP, 212, 0, 0),
};

static const u16 sOamFrame_5a371e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-15, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 0, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 278, 0, 0),
    OAM_ENTRY(-7, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 285, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 320, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 322, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 0, 0),
};

static const u16 sOamFrame_5a3744[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 279, 0, 0),
    OAM_ENTRY(4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 281, 0, 0),
    OAM_ENTRY(-4, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 317, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 323, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 357, 0, 0),
};

static const u16 sOamFrame_5a376a[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-10, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 282, 0, 0),
    OAM_ENTRY(6, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 284, 0, 0),
    OAM_ENTRY(-10, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 124, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 320, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 322, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 354, 0, 0),
};

static const u16 sOamFrame_5a3790[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-8, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
	OAM_ENTRY(-1, -33, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
	OAM_ENTRY(-8, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-5, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a37bc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-9, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-10, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-18, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 66, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a37e8[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 70, 0, 0),
	OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a381a[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-11, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 73, 0, 0),
	OAM_ENTRY(-12, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 72, 0, 0),
	OAM_ENTRY(8, -21, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a384c[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-10, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 76, 0, 0),
	OAM_ENTRY(-10, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 0, 0),
	OAM_ENTRY(9, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a387e[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-8, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
	OAM_ENTRY(-1, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
	OAM_ENTRY(-9, -27, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
	OAM_ENTRY(-7, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 326, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a38aa[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-7, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(1, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-7, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-16, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 328, 0, 0),
	OAM_ENTRY(6, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 82, 0, 0),
	OAM_ENTRY(2, -28, OAM_DIMS_8x8, OAM_NO_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a38dc[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-8, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-1, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-8, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 330, 0, 0),
	OAM_ENTRY(8, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 86, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
	OAM_ENTRY(2, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3914[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-9, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-2, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-9, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-8, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-18, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 332, 0, 0),
	OAM_ENTRY(9, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 57, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 121, 0, 0),
};

static const u16 sOamFrame_5a3946[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-9, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-9, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-6, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 334, 0, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 83, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 28, 0, 0),
	OAM_ENTRY(-18, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3978[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(1, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-8, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-5, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_16x16, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a399e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(2, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 66, 0, 0),
	OAM_ENTRY(-15, -16, OAM_DIMS_16x16, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a39c4[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-3, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 70, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 8, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a39f0[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-3, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-6, -39, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 73, 0, 0),
	OAM_ENTRY(4, -18, OAM_DIMS_8x16, OAM_X_FLIP, 72, 0, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a3a1c[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -23, OAM_DIMS_16x16, OAM_X_FLIP, 76, 0, 0),
	OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_X_FLIP, 75, 0, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x8, OAM_X_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a3a48[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(1, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-7, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-6, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-9, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_16x16, OAM_X_FLIP, 326, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a3a6e[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-9, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-7, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 328, 0, 0),
	OAM_ENTRY(-14, -15, OAM_DIMS_8x16, OAM_X_FLIP, 82, 0, 0),
	OAM_ENTRY(-10, -24, OAM_DIMS_8x8, OAM_X_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3a9a[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(1, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-5, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_X_FLIP, 330, 0, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 86, 0, 0),
	OAM_ENTRY(0, -7, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
	OAM_ENTRY(-10, -18, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3acc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-4, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-8, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 332, 0, 0),
	OAM_ENTRY(-17, -16, OAM_DIMS_8x16, OAM_X_FLIP, 57, 0, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_X_FLIP, 121, 0, 0),
};

static const u16 sOamFrame_5a3af8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-10, -24, OAM_DIMS_16x16, OAM_X_FLIP, 334, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x16, OAM_X_FLIP, 83, 0, 0),
	OAM_ENTRY(-2, -8, OAM_DIMS_16x8, OAM_X_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a3b24[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-10, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-10, -27, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 336, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 338, 0, 0),
	OAM_ENTRY(-19, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3b50[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-3, -38, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-10, -30, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-9, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 340, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(-2, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3b82[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 342, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_16x8, OAM_NO_FLIP, 370, 0, 0),
};

static const u16 sOamFrame_5a3bae[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -28, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -20, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 344, 0, 0),
	OAM_ENTRY(-9, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 346, 0, 0),
};

static const u16 sOamFrame_5a3bda[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-12, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-5, -26, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-12, -19, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -29, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 348, 0, 0),
};

static const u16 sOamFrame_5a3c00[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -31, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 350, 0, 0),
	OAM_ENTRY(-9, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 378, 0, 0),
};

static const u16 sOamFrame_5a3c2c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(3, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-3, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 336, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 338, 0, 0),
};

static const u16 sOamFrame_5a3c52[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -39, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-4, -38, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 340, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x16, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-6, -29, OAM_DIMS_8x8, OAM_X_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3c7e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_X_FLIP, 342, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_16x8, OAM_X_FLIP, 370, 0, 0),
};

static const u16 sOamFrame_5a3ca4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -27, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -30, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -18, OAM_DIMS_16x16, OAM_X_FLIP, 344, 0, 0),
	OAM_ENTRY(-7, -2, OAM_DIMS_16x8, OAM_X_FLIP, 346, 0, 0),
};

static const u16 sOamFrame_5a3cca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(4, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -29, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_16x16, OAM_X_FLIP, 348, 0, 0),
};

static const u16 sOamFrame_5a3cea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -31, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -34, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 350, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_16x8, OAM_X_FLIP, 378, 0, 0),
};

static const u16 sOamFrame_5a3d10[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 417, 0, 0),
    OAM_ENTRY(-7, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 448, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d36[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 418, 0, 0),
    OAM_ENTRY(-10, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 450, 0, 0),
    OAM_ENTRY(6, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 419, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d62[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 396, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 475, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 420, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 484, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 486, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d8e[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 422, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 487, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 489, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3dba[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 426, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 490, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3de0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 428, 0, 0),
    OAM_ENTRY(-7, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e06[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 430, 0, 0),
    OAM_ENTRY(-11, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 462, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e2c[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 396, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 475, 0, 0),
    OAM_ENTRY(-19, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 465, 0, 0),
    OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 434, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e52[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 437, 0, 0),
    OAM_ENTRY(-11, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 469, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e78[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 441, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 505, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e9e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_X_FLIP, 417, 0, 0),
    OAM_ENTRY(-9, -16, OAM_DIMS_16x16, OAM_X_FLIP, 448, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3ec4[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_X_FLIP, 418, 0, 0),
    OAM_ENTRY(-6, -16, OAM_DIMS_16x16, OAM_X_FLIP, 450, 0, 0),
    OAM_ENTRY(-14, -9, OAM_DIMS_8x8, OAM_X_FLIP, 419, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3ef0[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 400, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 415, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 420, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 484, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 486, 0, 0),
};

static const u16 sOamFrame_5a3f1c[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 422, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 487, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 489, 0, 0),
};

static const u16 sOamFrame_5a3f48[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 426, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 490, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3f6e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 428, 0, 0),
    OAM_ENTRY(-9, -8, OAM_DIMS_16x8, OAM_X_FLIP, 492, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3f94[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_X_FLIP, 430, 0, 0),
    OAM_ENTRY(-21, -16, OAM_DIMS_32x16, OAM_X_FLIP, 462, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3fba[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 400, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 415, 0, 0),
    OAM_ENTRY(-13, -16, OAM_DIMS_32x16, OAM_X_FLIP, 465, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_16x8, OAM_X_FLIP, 434, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3fe0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_16x8, OAM_X_FLIP, 437, 0, 0),
    OAM_ENTRY(-21, -16, OAM_DIMS_32x16, OAM_X_FLIP, 469, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a4006[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 441, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 505, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

const struct FrameData sOam_5a402c[11] = {
    [0] = {
            .pFrame = sOamFrame_5a2ee8,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a2ef6,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a2f04,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a2f1e,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a2f38,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a2f4c,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a2f60,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a2f74,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a2f8e,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a2fa8,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4084[11] = {
    [0] = {
            .pFrame = sOamFrame_5a2fbc,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a2fd0,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a2fe4,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a300a,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a302a,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a3044,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a3058,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a3078,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3098,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a30be,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_IdleLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a30de,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3110,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3142,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a40fc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3174,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3110,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_IdleRight[4] = {
    [0] = {
            .pFrame = sOamFrame_5a31a6,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a31d2,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a31fe,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4134[3] = {
    [0] = {
            .pFrame = sOamFrame_5a322a,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a31d2,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_MissileArmedLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3256,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a328e,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a32c6,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_FiringMissileLeft[3] = {
    [0] = {
            .pFrame = sOamFrame_5a32fe,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a328e,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4184[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3336,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3368,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a339a,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41a4[3] = {
    [0] = {
            .pFrame = sOamFrame_5a33cc,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3368,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41bc[4] = {
    [0] = {
            .pFrame = sOamFrame_5a33fe,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a342a,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3456,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41dc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3482,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a342a,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41f4[4] = {
    [0] = {
            .pFrame = sOamFrame_5a34ae,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a34e0,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3512,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4214[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3544,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a34e0,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_MissileArmedUpLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3576,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a35a8,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a35da,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_FiringMissileUpLeft[3] = {
    [0] = {
            .pFrame = sOamFrame_5a360c,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a35a8,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4264[4] = {
    [0] = {
            .pFrame = sOamFrame_5a363e,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3676,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a36ae,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4284[3] = {
    [0] = {
            .pFrame = sOamFrame_5a36e6,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3676,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_TurningRight[4] = {
    [0] = {
            .pFrame = sOamFrame_5a371e,
            .timer = 2
    },
    [1] = {
            .pFrame = sOamFrame_5a3744,
            .timer = 2
    },
    [2] = {
            .pFrame = sOamFrame_5a376a,
            .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_TurningLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a376a,
            .timer = 2
    },
    [1] = {
            .pFrame = sOamFrame_5a3744,
            .timer = 2
    },
    [2] = {
            .pFrame = sOamFrame_5a371e,
            .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a42dc[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3790,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a37bc,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a37e8,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a381a,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a384c,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a387e,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a38aa,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a38dc,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3914,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a3946,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4334[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3978,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a399e,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a39c4,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a39f0,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a3a1c,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a3a48,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a3a6e,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a3a9a,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3acc,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a3af8,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a438c[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3b24,
            .timer = 6
    },
    [1] = {
            .pFrame = sOamFrame_5a3b50,
            .timer = 6
    },
    [2] = {
            .pFrame = sOamFrame_5a3b82,
            .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43ac[2] = {
    [0] = {
            .pFrame = sOamFrame_5a3bae,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43bc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3bda,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3c00,
            .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43d4[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3c2c,
            .timer = 6
    },
    [1] = {
            .pFrame = sOamFrame_5a3c52,
            .timer = 6
    },
    [2] = {
            .pFrame = sOamFrame_5a3c7e,
            .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43f4[2] = {
    [0] = {
            .pFrame = sOamFrame_5a3ca4,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4404[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3cca,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3cea,
            .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_WalkingLeft[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3d10,
            .timer = 5
    },
    [1] = {
            .pFrame = sOamFrame_5a3d36,
            .timer = 5
    },
    [2] = {
            .pFrame = sOamFrame_5a3d62,
            .timer = 5
    },
    [3] = {
            .pFrame = sOamFrame_5a3d8e,
            .timer = 5
    },
    [4] = {
            .pFrame = sOamFrame_5a3dba,
            .timer = 5
    },
    [5] = {
            .pFrame = sOamFrame_5a3de0,
            .timer = 5
    },
    [6] = {
            .pFrame = sOamFrame_5a3e06,
            .timer = 5
    },
    [7] = {
            .pFrame = sOamFrame_5a3e2c,
            .timer = 5
    },
    [8] = {
            .pFrame = sOamFrame_5a3e52,
            .timer = 5
    },
    [9] = {
            .pFrame = sOamFrame_5a3e78,
            .timer = 5
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_WalkingRight[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3e9e,
            .timer = 5
    },
    [1] = {
            .pFrame = sOamFrame_5a3ec4,
            .timer = 5
    },
    [2] = {
            .pFrame = sOamFrame_5a3ef0,
            .timer = 5
    },
    [3] = {
            .pFrame = sOamFrame_5a3f1c,
            .timer = 5
    },
    [4] = {
            .pFrame = sOamFrame_5a3f48,
            .timer = 5
    },
    [5] = {
            .pFrame = sOamFrame_5a3f6e,
            .timer = 5
    },
    [6] = {
            .pFrame = sOamFrame_5a3f94,
            .timer = 5
    },
    [7] = {
            .pFrame = sOamFrame_5a3fba,
            .timer = 5
    },
    [8] = {
            .pFrame = sOamFrame_5a3fe0,
            .timer = 5
    },
    [9] = {
            .pFrame = sOamFrame_5a4006,
            .timer = 5
    },
    [10] = FRAME_DATA_TERMINATOR
};

const u32 sIntroHornoadEncounterBgGfx[4027] = INCBIN_U32("data/new_file_intro/hornoad_encounter_bg.gfx.lz");

const u32 sTilemap_5a83b8[196] = INCBIN_U32("data/new_file_intro/5a83b8.tm.lz");
const u32 sTilemap_5a86c8[479] = INCBIN_U32("data/new_file_intro/5a86c8.tm.lz");

const u16 sPal_5a8e44[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a8e44.pal");

const u32 sTilemap_5a9044[135] = INCBIN_U32("data/new_file_intro/5a9044.tm.lz");

const u16 sPal_5a9260[15 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a9260.pal");
const u16 sPal_5a9440[15 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a9440.pal");

const u16 sArray_5a9620[30] = {
	C_16_2_8(0, 36),
	C_16_2_8(1, 12),
	C_16_2_8(2, 12),
	C_16_2_8(3, 36),
	C_16_2_8(2, 12),
	C_16_2_8(1, 12),
	C_16_2_8(0, 36),
	C_16_2_8(1, 12),
	C_16_2_8(2, 12),
	C_16_2_8(3, 36),
	C_16_2_8(4, 12),
	C_16_2_8(5, 12),
	C_16_2_8(6, 12),
	C_16_2_8(7, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36),
	C_16_2_8(9, 12),
	C_16_2_8(10, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36),
	C_16_2_8(9, 12),
	C_16_2_8(10, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36)
};

const u32 sIntroMetroidVaccineObjGfx[1485] = INCBIN_U32("data/new_file_intro/metroid_vaccine_obj.gfx.lz");

static const u16 sOamFrame_5aad90[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5aaefa[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5ab064[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5ab1ce[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5ab338[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5ab4a2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ab60c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ab776[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ab8e0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5aba4a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5abbb4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5abd1e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5abe88[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5abff2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5ac15c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5ac2c6[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5ac430[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5ac59a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ac704[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ac86e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ac9d8[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5acb42[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5accac[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5ace16[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5acf80[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5ad0ea[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad254[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad3be[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
};

static const u16 sOamFrame_5ad528[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad692[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad7fc[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5ad966[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5adad0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5adc3a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5adda4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5adf0e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ae078[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ae1e2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ae34c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5ae4b6[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5ae620[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5ae78a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5ae8f4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5aea5e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5aebc8[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5aed32[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5aee9c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5af006[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5af170[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5af2da[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5af444[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5af5ae[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5af718[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5af882[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5af9ec[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5afb56[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5afcc0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5afe2a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
};

static const u16 sOamFrame_5aff94[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5b00fe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-112, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0106[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-103, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0114[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-96, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 10, 6, 0),
};

static const u16 sOamFrame_5b0128[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-87, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 148, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b013c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b0150[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 150, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b016a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 150, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-88, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 11, 6, 0),
};

static const u16 sOamFrame_5b0184[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b019e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-44, 31, OAM_DIMS_8x8, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b01c4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b01e4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_8x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-56, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 15, 6, 0),
};

static const u16 sOamFrame_5b020a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_16x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0230[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-13, 31, OAM_DIMS_8x32, OAM_NO_FLIP, 140, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_16x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-72, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 13, 6, 0),
};

static const u16 sOamFrame_5b025c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-64, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 14, 6, 0),
};

static const u16 sOamFrame_5b0282[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(3, 31, OAM_DIMS_8x32, OAM_NO_FLIP, 142, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-56, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 15, 6, 0),
};

static const u16 sOamFrame_5b02ae[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(3, 31, OAM_DIMS_16x32, OAM_NO_FLIP, 142, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 6, 0),
};

static const u16 sOamFrame_5b02da[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_64x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(16, -59, OAM_DIMS_16x32, OAM_NO_FLIP, 24, 6, 0),
};

static const u16 sOamFrame_5b0306[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b030e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b0316[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b031e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b0326[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b032e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b0336[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b033e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b0346[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-120, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b034e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-118, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-126, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b035c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-116, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-124, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b036a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-114, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-122, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b0378[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0380[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0390[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0398[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-120, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-118, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03a8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-116, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03b0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-114, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03b8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-112, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-110, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03c8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-108, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03d0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-106, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-104, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03e0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-102, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-100, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03f0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-98, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03f8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-96, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0400[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-94, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b040e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 5, 0),
	OAM_ENTRY(-92, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
};

static const u16 sOamFrame_5b041c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 30, 5, 0),
	OAM_ENTRY(-90, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b042a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 5, 0),
	OAM_ENTRY(-88, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 340, 5, 0),
};

static const u16 sOamFrame_5b0438[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 5, 0),
	OAM_ENTRY(-86, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 344, 5, 0),
};

static const u16 sOamFrame_5b0446[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 94, 5, 0),
	OAM_ENTRY(-84, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 348, 5, 0),
};

static const u16 sOamFrame_5b0454[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 154, 5, 0),
	OAM_ENTRY(-82, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 360, 5, 0),
};

static const u16 sOamFrame_5b0462[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 156, 5, 0),
	OAM_ENTRY(-80, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
};

static const u16 sOamFrame_5b0470[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 158, 5, 0),
	OAM_ENTRY(-78, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b047e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 5, 0),
	OAM_ENTRY(-76, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 372, 5, 0),
};

static const u16 sOamFrame_5b048c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 5, 0),
	OAM_ENTRY(-74, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 376, 5, 0),
};

static const u16 sOamFrame_5b049a[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 5, 0),
};

static const u16 sOamFrame_5b04a2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 216, 5, 0),
};

static const u16 sOamFrame_5b04aa[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 218, 5, 0),
};

static const u16 sOamFrame_5b04b2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 220, 5, 0),
};

static const u16 sOamFrame_5b04ba[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 222, 5, 0),
};

static const u16 sOamFrame_5b04c2[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 380, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 5, 0),
};

static const u16 sOamFrame_5b04d0[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 5, 0),
};

static const u16 sOamFrame_5b04de[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 382, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 5, 0),
};

static const u16 sOamFrame_5b04ec[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 5, 0),
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b04fa[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 392, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 5, 0),
};

static const u16 sOamFrame_5b0508[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 394, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 5, 0),
};

static const u16 sOamFrame_5b0516[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 396, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b0524[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 280, 5, 0),
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 398, 5, 0),
};

static const u16 sOamFrame_5b0532[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 282, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 400, 5, 0),
};

static const u16 sOamFrame_5b0540[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 284, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 404, 0, 0),
};

static const u16 sOamFrame_5b054e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 286, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 408, 5, 0),
};

static const u16 sOamFrame_5b055c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0564[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-54, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b056c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-52, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0574[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-50, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b057c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-48, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0584[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-46, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b058c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-44, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0594[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-42, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b059c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-38, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-36, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-34, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-32, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-30, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-28, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-26, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-24, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-22, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-20, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-18, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0604[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-14, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b060c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-12, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0614[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-10, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b061c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0624[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-6, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b062c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0634[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-2, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b063c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0644[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b064c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(4, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0654[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(6, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b065c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(8, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0664[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(10, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b066c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(12, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0674[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(14, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b067c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0684[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(18, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b068c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(20, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0694[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(22, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b069c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(24, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(26, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(28, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(30, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(32, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(34, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(36, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(38, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(40, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(42, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(44, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(46, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(48, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0704[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(50, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b070c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(52, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0714[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(54, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b071c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0724[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(58, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b072c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(60, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0734[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(62, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b073c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(64, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0744[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(66, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b074c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(68, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0754[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(70, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b075c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(72, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0764[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(74, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b076c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(76, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0774[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(78, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b077c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(80, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0784[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(82, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b078c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(84, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0794[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(86, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b079c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(88, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(90, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(92, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(94, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(96, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(98, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(100, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(102, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(104, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(106, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(108, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(110, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(112, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0804[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(114, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b080c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(116, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0814[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(118, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b081c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(120, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

const struct FrameData sIntroMetroidVaccineDoubleHelixOam[60] = {
	[0] = {
		.pFrame = sOamFrame_5aad90,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5aaefa,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5ab064,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5ab1ce,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5ab338,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5ab4a2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5ab60c,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5ab776,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5ab8e0,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5aba4a,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5abbb4,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5abd1e,
		.timer = 2
	},
	[12] = {
		.pFrame = sOamFrame_5abe88,
		.timer = 2
	},
	[13] = {
		.pFrame = sOamFrame_5abff2,
		.timer = 2
	},
	[14] = {
		.pFrame = sOamFrame_5ac15c,
		.timer = 2
	},
	[15] = {
		.pFrame = sOamFrame_5ac2c6,
		.timer = 2
	},
	[16] = {
		.pFrame = sOamFrame_5ac430,
		.timer = 2
	},
	[17] = {
		.pFrame = sOamFrame_5ac59a,
		.timer = 2
	},
	[18] = {
		.pFrame = sOamFrame_5ac704,
		.timer = 2
	},
	[19] = {
		.pFrame = sOamFrame_5ac86e,
		.timer = 2
	},
	[20] = {
		.pFrame = sOamFrame_5ac9d8,
		.timer = 2
	},
	[21] = {
		.pFrame = sOamFrame_5acb42,
		.timer = 2
	},
	[22] = {
		.pFrame = sOamFrame_5accac,
		.timer = 2
	},
	[23] = {
		.pFrame = sOamFrame_5ace16,
		.timer = 2
	},
	[24] = {
		.pFrame = sOamFrame_5acf80,
		.timer = 2
	},
	[25] = {
		.pFrame = sOamFrame_5ad0ea,
		.timer = 2
	},
	[26] = {
		.pFrame = sOamFrame_5ad254,
		.timer = 2
	},
	[27] = {
		.pFrame = sOamFrame_5ad3be,
		.timer = 2
	},
	[28] = {
		.pFrame = sOamFrame_5ad528,
		.timer = 2
	},
	[29] = {
		.pFrame = sOamFrame_5ad692,
		.timer = 2
	},
	[30] = {
		.pFrame = sOamFrame_5ad7fc,
		.timer = 2
	},
	[31] = {
		.pFrame = sOamFrame_5ad966,
		.timer = 2
	},
	[32] = {
		.pFrame = sOamFrame_5adad0,
		.timer = 2
	},
	[33] = {
		.pFrame = sOamFrame_5adc3a,
		.timer = 2
	},
	[34] = {
		.pFrame = sOamFrame_5adda4,
		.timer = 2
	},
	[35] = {
		.pFrame = sOamFrame_5adf0e,
		.timer = 2
	},
	[36] = {
		.pFrame = sOamFrame_5ae078,
		.timer = 2
	},
	[37] = {
		.pFrame = sOamFrame_5ae1e2,
		.timer = 2
	},
	[38] = {
		.pFrame = sOamFrame_5ae34c,
		.timer = 2
	},
	[39] = {
		.pFrame = sOamFrame_5ae4b6,
		.timer = 2
	},
	[40] = {
		.pFrame = sOamFrame_5ae620,
		.timer = 2
	},
	[41] = {
		.pFrame = sOamFrame_5ae78a,
		.timer = 2
	},
	[42] = {
		.pFrame = sOamFrame_5ae8f4,
		.timer = 2
	},
	[43] = {
		.pFrame = sOamFrame_5aea5e,
		.timer = 2
	},
	[44] = {
		.pFrame = sOamFrame_5aebc8,
		.timer = 2
	},
	[45] = {
		.pFrame = sOamFrame_5aed32,
		.timer = 2
	},
	[46] = {
		.pFrame = sOamFrame_5aee9c,
		.timer = 2
	},
	[47] = {
		.pFrame = sOamFrame_5af006,
		.timer = 2
	},
	[48] = {
		.pFrame = sOamFrame_5af170,
		.timer = 2
	},
	[49] = {
		.pFrame = sOamFrame_5af2da,
		.timer = 2
	},
	[50] = {
		.pFrame = sOamFrame_5af444,
		.timer = 2
	},
	[51] = {
		.pFrame = sOamFrame_5af5ae,
		.timer = 2
	},
	[52] = {
		.pFrame = sOamFrame_5af718,
		.timer = 2
	},
	[53] = {
		.pFrame = sOamFrame_5af882,
		.timer = 2
	},
	[54] = {
		.pFrame = sOamFrame_5af9ec,
		.timer = 2
	},
	[55] = {
		.pFrame = sOamFrame_5afb56,
		.timer = 2
	},
	[56] = {
		.pFrame = sOamFrame_5afcc0,
		.timer = 2
	},
	[57] = {
		.pFrame = sOamFrame_5afe2a,
		.timer = 2
	},
	[58] = {
		.pFrame = sOamFrame_5aff94,
		.timer = 2
	},
	[59] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroMetroidVaccineTextboxesOam[21] = {
	[0] = {
		.pFrame = sOamFrame_5b00fe,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5b0106,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5b0114,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5b0128,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5b013c,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5b0150,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5b016a,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5b0184,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5b019e,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5b01c4,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5b01e4,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5b020a,
		.timer = 2
	},
	[12] = {
		.pFrame = sOamFrame_5b0230,
		.timer = 2
	},
	[13] = {
		.pFrame = sOamFrame_5b025c,
		.timer = 2
	},
	[14] = {
		.pFrame = sOamFrame_5b0282,
		.timer = 2
	},
	[15] = {
		.pFrame = sOamFrame_5b02ae,
		.timer = 2
	},
	[16] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[17] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[18] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[19] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[20] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroMetroidVaccineElectrocardiogramOam[146] = {
	[0] = {
		.pFrame = sOamFrame_5b0306,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b030e,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b0316,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b031e,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b0326,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b032e,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b0336,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b033e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b0346,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b034e,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b035c,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b036a,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b0378,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5b0380,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b0388,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b0390,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b0398,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b03a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5b03a8,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b03b0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b03b8,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b03c0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b03c8,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5b03d0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b03d8,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b03e0,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b03e8,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b03f0,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5b03f8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b0400,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b040e,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b041c,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b042a,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b0438,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b0446,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b0454,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b0462,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b0470,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b047e,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b048c,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b049a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b04a2,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b04aa,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b04b2,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b04ba,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b04c2,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b04d0,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b04de,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b04ec,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b04fa,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b0508,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b0516,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b0524,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b0532,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b0540,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b054e,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b055c,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b0564,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b056c,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b0574,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b057c,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b0584,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b058c,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b0594,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b059c,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b05a4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b05ac,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b05b4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b05bc,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b05c4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b05cc,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b05d4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b05dc,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b05e4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b05ec,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b05f4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b05fc,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b0604,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b060c,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b0614,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b061c,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b0624,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b062c,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b0634,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b063c,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b0644,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b064c,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b0654,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b065c,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b0664,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b066c,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b0674,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b067c,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b0684,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b068c,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b0694,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b069c,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b06a4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b06ac,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b06b4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b06bc,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b06c4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b06cc,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b06d4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b06dc,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b06e4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b06ec,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b06f4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b06fc,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b0704,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b070c,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b0714,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b071c,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b0724,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b072c,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b0734,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b073c,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b0744,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b074c,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b0754,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b075c,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b0764,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b076c,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b0774,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b077c,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b0784,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b078c,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b0794,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b079c,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b07a4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b07ac,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b07b4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b07bc,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b07c4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b07cc,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b07d4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b07dc,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b07e4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b07ec,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b07f4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b07fc,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b0804,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b080c,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b0814,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b081c,
		.timer = 1
	},
	[145] = FRAME_DATA_TERMINATOR
};

const u16 sIntroMetroidVaccineObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/metroid_vaccine_obj.pal");

const u32 sIntroMetroidVaccineBgGfx[2794] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg.gfx.lz");

const u16 sIntroMetroidVaccineBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/metroid_vaccine_bg.pal");

const u32 sIntroMetroidVaccineBg1Tilemap[106] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg1.tm.lz");
const u32 sIntroMetroidVaccineBg2Tilemap[109] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg2.tm.lz");
const u32 sIntroMetroidVaccineBg3Tilemap[208] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg3.tm.lz");

const u32 sIntroSamusNervousSystemObjGfx[2495] = INCBIN_U32("data/new_file_intro/samus_nervous_system_obj.gfx.lz");

static const u16 sOamFrame_5b6c7c[OAM_DATA_SIZE(31)] = {
	31,
	OAM_ENTRY(8, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 263, 3, 0),
	OAM_ENTRY(8, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 295, 1, 0),
	OAM_ENTRY(8, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 327, 2, 0),
	OAM_ENTRY(-96, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 2, 0),
	OAM_ENTRY(-96, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 3, 0),
	OAM_ENTRY(-88, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 2, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 322, 3, 0),
	OAM_ENTRY(-88, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 321, 3, 0),
	OAM_ENTRY(-72, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 323, 2, 0),
	OAM_ENTRY(-96, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 320, 3, 0),
	OAM_ENTRY(-80, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 292, 3, 0),
	OAM_ENTRY(-72, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 293, 3, 0),
	OAM_ENTRY(-72, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 261, 3, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 262, 3, 0),
	OAM_ENTRY(-80, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 260, 3, 0),
	OAM_ENTRY(88, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 2, 0),
	OAM_ENTRY(80, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 2, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 266, 3, 0),
	OAM_ENTRY(72, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 265, 3, 0),
	OAM_ENTRY(64, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 264, 3, 0),
	OAM_ENTRY(88, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 267, 3, 0),
	OAM_ENTRY(-72, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 2, 0),
	OAM_ENTRY(-96, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 352, 3, 0),
	OAM_ENTRY(-88, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 353, 3, 0),
	OAM_ENTRY(-80, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 3, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 355, 3, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 324, 1, 0),
	OAM_ENTRY(-64, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 356, 1, 0),
	OAM_ENTRY(-72, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 3, 0),
	OAM_ENTRY(-72, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 2, 0),
	OAM_ENTRY(-64, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 3, 0),
};

static const u16 sOamFrame_5b6d38[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 4, 0),
};

static const u16 sOamFrame_5b6d40[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 4, 0),
};

static const u16 sOamFrame_5b6d48[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 4, 0),
};

static const u16 sOamFrame_5b6d50[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 4, 0),
};

static const u16 sOamFrame_5b6d58[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 4, 0),
};

static const u16 sOamFrame_5b6d60[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 4, 0),
};

static const u16 sOamFrame_5b6d68[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 4, 0),
};

static const u16 sOamFrame_5b6d70[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 4, 0),
};

static const u16 sOamFrame_5b6d78[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 4, 0),
};

static const u16 sOamFrame_5b6d80[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 4, 0),
};

static const u16 sOamFrame_5b6d88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 4, 0),
};

static const u16 sOamFrame_5b6d90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 4, 0),
};

static const u16 sOamFrame_5b6d98[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 4, 0),
};

static const u16 sOamFrame_5b6da0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 4, 0),
};

static const u16 sOamFrame_5b6da8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 4, 0),
};

static const u16 sOamFrame_5b6db0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 4, 0),
};

static const u16 sOamFrame_5b6db8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 6, 0),
};

static const u16 sOamFrame_5b6dc0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 6, 0),
};

static const u16 sOamFrame_5b6dc8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b6dd0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b6dd8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 6, 0),
};

static const u16 sOamFrame_5b6de0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 6, 0),
};

static const u16 sOamFrame_5b6de8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 6, 0),
};

static const u16 sOamFrame_5b6df0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 6, 0),
};

static const u16 sOamFrame_5b6df8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 6, 0),
};

static const u16 sOamFrame_5b6e00[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 6, 0),
};

static const u16 sOamFrame_5b6e08[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 6, 0),
};

static const u16 sOamFrame_5b6e10[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 6, 0),
};

static const u16 sOamFrame_5b6e18[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 6, 0),
};

static const u16 sOamFrame_5b6e20[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 6, 0),
};

static const u16 sOamFrame_5b6e28[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 6, 0),
};

static const u16 sOamFrame_5b6e30[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 6, 0),
};

static const u16 sOamFrame_5b6e38[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 7, 0),
};

static const u16 sOamFrame_5b6e40[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 7, 0),
};

static const u16 sOamFrame_5b6e48[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 7, 0),
};

static const u16 sOamFrame_5b6e50[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 7, 0),
};

static const u16 sOamFrame_5b6e58[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 7, 0),
};

static const u16 sOamFrame_5b6e60[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 7, 0),
};

static const u16 sOamFrame_5b6e68[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 7, 0),
};

static const u16 sOamFrame_5b6e70[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 7, 0),
};

static const u16 sOamFrame_5b6e78[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 7, 0),
};

static const u16 sOamFrame_5b6e80[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 7, 0),
};

static const u16 sOamFrame_5b6e88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 7, 0),
};

static const u16 sOamFrame_5b6e90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 7, 0),
};

static const u16 sOamFrame_5b6e98[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 7, 0),
};

static const u16 sOamFrame_5b6ea0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 7, 0),
};

static const u16 sOamFrame_5b6ea8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 7, 0),
};

static const u16 sOamFrame_5b6eb0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 7, 0),
};

static const u16 sOamFrame_5b6eb8[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-32, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6ed2[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-30, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(14, -30, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-30, 14, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(14, 14, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6eec[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-28, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(12, -28, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-28, 12, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(12, 12, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f06[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-26, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(10, -26, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-26, 10, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(10, 10, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f20[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f3a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-22, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(6, -22, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-22, 6, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(6, 6, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f54[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-20, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(4, -20, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-20, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(4, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f6e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-18, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(2, -18, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-18, 2, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(2, 2, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6f90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b6f98[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fa6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fba[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fd4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6ffa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-57, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(-25, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b701a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 304, 5, 0),
};

static const u16 sOamFrame_5b703a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b705a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b707a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 273, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 277, 5, 0),
};

static const u16 sOamFrame_5b709a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 305, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 309, 5, 0),
};

static const u16 sOamFrame_5b70ba[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 337, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 341, 5, 0),
};

static const u16 sOamFrame_5b70da[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -10, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b70fa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b711a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7134[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7148[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b7156[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b715e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-60, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-44, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 371, 5, 0),
};

static const u16 sOamFrame_5b716c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b7174[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b717c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b718a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-15, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b71a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b71c4[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-2, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(30, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b71f0[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7216[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b723c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7262[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7288[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b72ae[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b72d4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b72fa[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 13, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 13, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7320[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7346[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7366[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b737a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(9, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7390[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(17, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b739e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(25, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b73a6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b73ae[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b73bc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b73d0[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b73ea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(21, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(53, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7410[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7430[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b7450[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7470[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7490[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b74b0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b74d0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b74f0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 5, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7510[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7530[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b754a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b755e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b756c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(32, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7574[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(40, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7582[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(48, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b758a[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7592[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b75a0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b75b4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
};

static const u16 sOamFrame_5b75ce[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(18, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(50, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b75f4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7614[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b7634[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7654[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7674[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b7694[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b76b4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b76d4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -10, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b76f4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 329, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7714[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b772e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7742[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7750[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(29, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7758[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(37, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7766[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(45, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b776e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7776[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b7784[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
};

static const u16 sOamFrame_5b779e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b77be[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b77ea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-37, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(-5, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7810[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 304, 5, 0),
};

static const u16 sOamFrame_5b7836[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b785c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b7882[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 273, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 277, 5, 0),
};

static const u16 sOamFrame_5b78a8[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 305, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 309, 5, 0),
};

static const u16 sOamFrame_5b78ce[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 337, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 341, 5, 0),
};

static const u16 sOamFrame_5b78f4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 13, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 13, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b791a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7940[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7960[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7974[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b7982[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b798a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-40, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-24, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 371, 5, 0),
};

static const u16 sOamFrame_5b7998[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b79a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b79a8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 388, 5, 0),
};

static const u16 sOamFrame_5b79b0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 389, 5, 0),
};

static const u16 sOamFrame_5b79b8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 390, 5, 0),
};

static const u16 sOamFrame_5b79c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 391, 5, 0),
};

static const u16 sOamFrame_5b79c8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 392, 5, 0),
};

static const u16 sOamFrame_5b79d0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 452, 5, 0),
};

static const u16 sOamFrame_5b79d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 453, 5, 0),
};

static const u16 sOamFrame_5b79e0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 454, 5, 0),
};

static const u16 sOamFrame_5b79e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 455, 5, 0),
};

static const u16 sOamFrame_5b79f0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 456, 5, 0),
};

static const u16 sOamFrame_5b79f8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 395, 5, 0),
};

static const u16 sOamFrame_5b7a00[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 399, 5, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 403, 5, 0),
};

static const u16 sOamFrame_5b7a0e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 357, 3, 0),
};

static const u16 sOamFrame_5b7a16[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a1e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a2c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a40[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a5a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a80[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a8e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-15, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7aa8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7ac8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-2, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(30, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7af4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7b02[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b16[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b30[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(21, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(53, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7b56[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7b64[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b78[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
};

static const u16 sOamFrame_5b7b92[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(18, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(50, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7bb8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7bc6[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
};

static const u16 sOamFrame_5b7be0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7c00[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_1[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a80,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b717c,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a8e,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b718a,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7aa8,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b71a4,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b71f0,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7216,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b723c,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7262,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7288,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b72ae,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b72d4,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b72fa,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b7320,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7346,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7366,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b737a,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7388,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7390,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b739e,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b73a6,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_2[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7af4,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b73ae,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7b02,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b73bc,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7b16,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b73d0,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b7410,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7430,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7450,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7470,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7490,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b74b0,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b74d0,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b74f0,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b7510,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7530,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b754a,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b755e,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b756c,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7574,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7582,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b758a,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_3[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7b56,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b7592,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7b64,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b75a0,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7b78,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b75b4,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b75f4,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7614,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7634,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7654,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7674,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b7694,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b76b4,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b76d4,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b76f4,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7714,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b772e,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7742,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7750,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7758,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7766,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b776e,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_4[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a1e,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b6f98,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a2c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b6fa6,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7a40,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b6fba,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b6ffa,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b701a,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b703a,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b705a,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b707a,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b709a,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b70ba,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b70da,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b70fa,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b711a,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7134,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7148,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7156,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b715e,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b716c,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b7174,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_5[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7bb8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b7776,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7bc6,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b7784,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7be0,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b779e,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b77ea,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7810,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7836,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b785c,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7882,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b78a8,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b78ce,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b78f4,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b791a,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7940,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7960,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7974,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7982,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b798a,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7998,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b79a0,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_6[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a1e,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b6f98,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a2c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b6fa6,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7a40,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b6fba,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b6ffa,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b701a,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b703a,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b705a,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b707a,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b709a,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b70ba,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b70da,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b70fa,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b711a,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7134,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7148,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7156,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b715e,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b716c,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b7174,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCountdownOam_Fast[11] = {
	[0] = {
		.pFrame = sOamFrame_5b79f0,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5b79e8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5b79e0,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5b79d8,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5b79d0,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5b79c8,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5b79c0,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5b79b8,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5b79b0,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5b79a8,
		.timer = 8
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCountdownOam_Slow[11] = {
	[0] = {
		.pFrame = sOamFrame_5b79f0,
		.timer = 80
	},
	[1] = {
		.pFrame = sOamFrame_5b79e8,
		.timer = 80
	},
	[2] = {
		.pFrame = sOamFrame_5b79e0,
		.timer = 80
	},
	[3] = {
		.pFrame = sOamFrame_5b79d8,
		.timer = 80
	},
	[4] = {
		.pFrame = sOamFrame_5b79d0,
		.timer = 80
	},
	[5] = {
		.pFrame = sOamFrame_5b79c8,
		.timer = 80
	},
	[6] = {
		.pFrame = sOamFrame_5b79c0,
		.timer = 80
	},
	[7] = {
		.pFrame = sOamFrame_5b79b8,
		.timer = 80
	},
	[8] = {
		.pFrame = sOamFrame_5b79b0,
		.timer = 80
	},
	[9] = {
		.pFrame = sOamFrame_5b79a8,
		.timer = 80
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemNumber281Oam[2] = {
	[0] = {
		.pFrame = sOamFrame_5b79f8,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCornerTextOam[3] = {
	[0] = {
		.pFrame = sOamFrame_5b7a00,
		.timer = 40
	},
	[1] = {
		.pFrame = sOamFrame_5b7a0e,
		.timer = 30
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemNervePartsOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5b6c7c,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_1[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_2[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_3[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6df0,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6df8,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e00,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e08,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e10,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6e18,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6e20,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6e28,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6e30,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6db8,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6dc0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6dc8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6dd0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6dd8,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6de0,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6de8,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_4[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_5[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6e50,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6e58,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e60,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e68,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e70,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6e78,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6e80,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6e88,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6e90,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6e98,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6ea0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6ea8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6eb0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6e38,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6e40,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6e48,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_6[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6e10,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6e18,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e20,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e28,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e30,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6db8,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6dc0,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6dc8,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6dd0,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6dd8,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6de0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6de8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6df0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6df8,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6e00,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6e08,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const u16 sIntroSamusNervousSystemObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_nervous_system_obj.pal");

const u32 sIntroSamusNervousSystemBgGfx[4869] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg.gfx.lz");

const u16 sIntroSamusNervousSystemBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_nervous_system_bg.pal");

const u32 sIntroSamusNervousSystemBg3Tilemap[369] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg3.tm.lz");
const u32 sIntroSamusNervousSystemBg2Tilemap[63] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg2.tm.lz");
const u32 sIntroSamusNervousSystemBg1Tilemap[68] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg1.tm.lz");

const u16 sPal_5bf838[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf838.pal");
const u16 sPal_5bf8b8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf8b8.pal");
const u16 sPal_5bf938[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf938.pal");
const u16 sPal_5bf9b8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf9b8.pal");
const u16 sPal_5bfa38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfa38.pal");
const u16 sPal_5bfab8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfab8.pal");
const u16 sPal_5bfb38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfb38.pal");
const u16 sPal_5bfbb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfbb8.pal");
const u16 sPal_5bfc38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfc38.pal");
const u16 sPal_5bfcb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfcb8.pal");
const u16 sPal_5bfd38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfd38.pal");
const u16 sPal_5bfdb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfdb8.pal");

const u32 sIntroVariaSuitCoveredInXParasitesGfx[4230] = INCBIN_U32("data/new_file_intro/suit_covered_in_parasites.gfx.lz");
const u32 sIntroHazmatTeamGfx[4915] = INCBIN_U32("data/new_file_intro/hazmat_team.gfx.lz");

const u16 sIntroSamusFoundPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_found.pal");

const u32 sIntroVariaSuitCoveredInXParasitesTilemap[385] = INCBIN_U32("data/new_file_intro/suit_covered_in_parasites.tm.lz");
const u32 sIntroHazmatTeamTilemap[395] = INCBIN_U32("data/new_file_intro/hazmat_team.tm.lz");

const u32 sIntroSuitRemovalSurgeryGfx[7003] = INCBIN_U32("data/new_file_intro/suit_removal_surgery.gfx.lz");
const u32 sIntroSuitRemovalSurgeryTilemap[551] = INCBIN_U32("data/new_file_intro/suit_removal_surgery.tm.lz");

const u32 sIntroMetroidVaccineVialGfx[3525] = INCBIN_U32("data/new_file_intro/metroid_vaccine_vial.gfx.lz");
const u32 sIntroMetroidVaccineVialTilemap[385] = INCBIN_U32("data/new_file_intro/metroid_vaccine_vial.tm.lz");

const u32 sIntroSamusRebornBgTopGfx[6616] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_top.gfx.lz");
const u32 sIntroSamusRebornBgBottomGfx[3537] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_bottom.gfx.lz");
const u16 sIntroSamusRebornBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_reborn_bg.pal");
const u32 sIntroSamusRebornBgTopTilemap[551] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_top.tm.lz");
const u32 sIntroSamusRebornBgBottomTilemap[368] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_bottom.tm.lz");

static const u8 sBlob_5dfd6c_5e116c[] = INCBIN_U8("data/Blob_5dfd6c_5e116c.bin");

const u32 sIntroApproachingBslObjGfx[3614] = INCBIN_U32("data/new_file_intro/approaching_bsl_obj.gfx.lz");

const u32 sIntroFlyingToBslBgGfx[4107] = INCBIN_U32("data/new_file_intro/5e49e4.gfx.lz");
const u32 sIntroArrivingAtBslSpaceMapBgGfx[2178] = INCBIN_U32("data/new_file_intro/space_map_bg");
const u32 sIntroFlyingToBslObjGfx[3286] = INCBIN_U32("data/new_file_intro/5eac18.gfx.lz");

const u32 sIntroSamusMonologueBgGfx[3282] = INCBIN_U32("data/new_file_intro/samus_monologue_bg.gfx.lz");

static const u16 sOamFrame_5f12b8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-7, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(-1, -7, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(-1, -1, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-7, -1, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 725, 3, 0),
};

static const u16 sOamFrame_5f12d8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 724, 3, 0),
};

static const u16 sOamFrame_5f12f8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-9, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(1, 1, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-9, 1, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 723, 3, 0),
};

static const u16 sOamFrame_5f1318[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 5, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(5, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-13, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 802, 3, 0),
};

static const u16 sOamFrame_5f1338[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
};

static const u16 sOamFrame_5f1352[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(3, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-11, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 802, 3, 0),
};

static const u16 sOamFrame_5f1372[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(2, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-10, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
};

static const u16 sOamFrame_5f138c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1394[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f139c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f13a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f13ac[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13ba[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13c8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13d6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13de[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13e6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13ee[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 547, 3, 0),
};

static const u16 sOamFrame_5f13f6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 552, 9, 0),
};

static const u16 sOamFrame_5f13fe[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -24, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
};

static const u16 sOamFrame_5f1424[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f142c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f1434[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -3, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f143c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f1444[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f144c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-3, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f1454[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1468[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1470[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1484[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f148c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -22, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f14a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f14a8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14c4[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -22, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f14e0[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f14ee[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 578, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1502[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1510[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 578, 3, 0),
};

static const u16 sOamFrame_5f1518[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1520[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1528[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1536[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_Y_FLIP, 578, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f154a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1558[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 578, 3, 0),
};

static const u16 sOamFrame_5f1560[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1568[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
};

static const u16 sOamFrame_5f1594[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
};

static const u16 sOamFrame_5f15c0[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
};

static const u16 sOamFrame_5f15ec[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1618[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1644[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1670[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 6, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1684[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 5, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1698[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -1, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f16ac[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 5, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f16c0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f16d4[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f16e8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f16fc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f1710[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1724[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1738[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f174c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f1760[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1768[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1770[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -3, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1778[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -2, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1780[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1788[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-6, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1790[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-3, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1798[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-2, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f17a0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
	OAM_ENTRY(38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 744, 3, 0),
};

static const u16 sOamFrame_5f17c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
};

static const u16 sOamFrame_5f17c8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f17e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f17f0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
	OAM_ENTRY(38, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 744, 3, 0),
};

static const u16 sOamFrame_5f1810[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
};

static const u16 sOamFrame_5f1818[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(38, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f1838[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f1840[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f1860[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f186e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f188e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f189c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f18bc[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f18ca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f18ea[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f18f8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-29, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 942, 3, 0),
	OAM_ENTRY(-15, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 976, 3, 0),
	OAM_ENTRY(17, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 980, 3, 0),
};

static const u16 sOamFrame_5f190c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 944, 8, 0),
};

static const u16 sOamFrame_5f1920[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 945, 8, 0),
};

static const u16 sOamFrame_5f1934[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 946, 8, 0),
};

static const u16 sOamFrame_5f1948[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 947, 8, 0),
};

static const u16 sOamFrame_5f195c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 948, 8, 0),
};

static const u16 sOamFrame_5f1970[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 949, 8, 0),
};

static const u16 sOamFrame_5f1984[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 788, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 790, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 788, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 790, 8, 0),
};

static const u16 sOamFrame_5f199e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 820, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 822, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 820, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 822, 8, 0),
};

static const u16 sOamFrame_5f19b8[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 852, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 854, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 852, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 854, 8, 0),
};

static const u16 sOamFrame_5f19d2[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 884, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 886, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 884, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 886, 8, 0),
};

static const u16 sOamFrame_5f19ec[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 884, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 884, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 885, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 885, 8, 0),
};

static const u16 sOamFrame_5f1a06[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 11, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 11, 0),
};

static const u16 sOamFrame_5f1a14[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 12, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 12, 0),
};

static const u16 sOamFrame_5f1a22[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 13, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 13, 0),
};

static const u16 sOamFrame_5f1a30[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 14, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 14, 0),
};

static const u16 sOamFrame_5f1a3e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 11, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 11, 0),
};

static const u16 sOamFrame_5f1a4c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 12, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 12, 0),
};

static const u16 sOamFrame_5f1a5a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 13, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 13, 0),
};

static const u16 sOamFrame_5f1a68[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 14, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 14, 0),
};

static const u16 sOamFrame_5f1a76[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 448, 6, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 450, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1a8a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 451, 6, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 453, 6, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1a9e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 454, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 456, 6, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1ab2[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 457, 6, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 459, 6, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1ac6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 480, 6, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 482, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1ada[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 483, 6, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 485, 6, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1aee[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 486, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 488, 6, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1b02[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 489, 6, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 491, 6, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1b16[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 3, 0),
};

static const u16 sOamFrame_5f1b24[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 5, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 5, 0),
};

static const u16 sOamFrame_5f1b32[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 3, 0),
};

static const u16 sOamFrame_5f1b40[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 5, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 5, 0),
};

static const u16 sOamFrame_5f1b4e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 917, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 921, 8, 0),
};

static const u16 sOamFrame_5f1b5c[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 441, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 445, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 447, 8, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
};

static const u16 sOamFrame_5f1b76[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 473, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 477, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 479, 8, 0),
};

static const u16 sOamFrame_5f1b8a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 505, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 509, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 511, 8, 0),
};

static const u16 sOamFrame_5f1b9e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 409, 3, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 414, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 413, 8, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
	OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
};

static const u16 sOamFrame_5f1bbe[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 405, 3, 0),
};

static const u16 sOamFrame_5f1bcc[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 437, 3, 0),
};

static const u16 sOamFrame_5f1bda[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 407, 3, 0),
};

static const u16 sOamFrame_5f1be8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 441, 3, 0),
};

static const u16 sOamFrame_5f1bf0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 473, 3, 0),
};

static const u16 sOamFrame_5f1bf8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 505, 3, 0),
};

const struct FrameData sOam_5f1c00[5] = {
	[0] = {
		.pFrame = sOamFrame_5f12b8,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f12d8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f12f8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f12d8,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1c28[5] = {
	[0] = {
		.pFrame = sOamFrame_5f143c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1444,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f144c,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1444,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslMonologueCursorOam[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1424,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f142c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1434,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f142c,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1c78[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1318,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f1338,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5f1352,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5f1372,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5f1352,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5f1338,
		.timer = 3
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1cb0[5] = {
	[0] = {
		.pFrame = sOamFrame_5f138c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1760,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1768,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1760,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1cd8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1394,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1770,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1778,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1770,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d00[5] = {
	[0] = {
		.pFrame = sOamFrame_5f139c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1780,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1788,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1780,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d28[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13a4,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1790,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1798,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1790,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d50[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13ac,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f13ba,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f13c8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f13ba,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d78[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13d6,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f13de,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f13e6,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f13de,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamTextCursorOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5f13ee,
		.timer = 30
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1db0[3] = {
	[0] = {
		.pFrame = sOamFrame_5f13ee,
		.timer = 16
	},
	[1] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 16
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1dc8[2] = {
	[0] = {
		.pFrame = sOamFrame_5f13fe,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1dd8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f14d8,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5f14e0,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f14ee,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5f1502,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5f1510,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5f1518,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 8
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e18[8] = {
	[0] = {
		.pFrame = sOamFrame_5f1520,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5f1528,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1536,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5f154a,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5f1558,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5f1560,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 8
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e58[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1568,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1594,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f15c0,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f15ec,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1618,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1644,
		.timer = 1
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e90[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1568,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1ea0[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1fa8[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f20b0[33] = {
	[0] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f21b8[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f22c0[5] = {
	[0] = {
		.pFrame = sOamFrame_5f17a0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f17c0,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f17c8,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f17e8,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f22e8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f17f0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1810,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1818,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1838,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2310[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1840,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1860,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f186e,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f188e,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2338[5] = {
	[0] = {
		.pFrame = sOamFrame_5f189c,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f18bc,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f18ca,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f18ea,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2360[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b4e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2370[2] = {
	[0] = {
		.pFrame = sOamFrame_5f190c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2380[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1920,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2390[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1934,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23a0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1948,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23b0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f195c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23c0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1970,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23d0[10] = {
	[0] = {
		.pFrame = sOamFrame_5f1984,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f199e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f19b8,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f19d2,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f19ec,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f19d2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f19b8,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f199e,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f1984,
		.timer = 2
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2420[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1a06,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1a14,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1a22,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1a30,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f1a22,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f1a14,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2458[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1a3e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1a4c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1a5a,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1a68,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f1a5a,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f1a4c,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2490[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1b16,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5f1b24,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5f1b16,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5f1b24,
		.timer = 6
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24b8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1b32,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5f1b40,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5f1b32,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5f1b40,
		.timer = 6
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24e0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a76,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24f0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a8a,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2500[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a9e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2510[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ab2,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2520[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ac6,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2530[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ada,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2540[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1aee,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2550[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b02,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2560[2] = {
	[0] = {
		.pFrame = sOamFrame_5f18f8,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2570[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b5c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2580[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b76,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2590[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b8a,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25a0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b9e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25b0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bbe,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25c0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bcc,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25d0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bda,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25e0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1be8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25f0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bf0,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2600[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bf8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5f2610[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 711, 9, 0),
	OAM_ENTRY(-8, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 521, 9, 0),
};

static const u16 sOamFrame_5f262a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 710, 9, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2644[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 710, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 646, 9, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2670[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -3, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(8, -3, OAM_DIMS_32x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-24, -3, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(-40, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(24, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2696[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(-40, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(8, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
};

static const u16 sOamFrame_5f26bc[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-40, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 10, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 10, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f2700[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-40, -22, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -22, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 6, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 14, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -22, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 10, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f2744[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-40, -28, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -28, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -20, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 12, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 20, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -28, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
	OAM_ENTRY(-32, -20, OAM_DIMS_64x32, OAM_NO_FLIP, 536, 1, 0),
	OAM_ENTRY(-32, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 664, 1, 0),
	OAM_ENTRY(0, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 668, 1, 0),
};

static const u16 sOamFrame_5f279a[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-40, -32, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_64x32, OAM_NO_FLIP, 536, 1, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 664, 1, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 668, 1, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f27f0[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-88, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-88, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-104, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-88, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-88, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
};

static const u16 sOamFrame_5f2828[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-64, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-64, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-64, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2872[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-48, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f28bc[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-40, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2912[OAM_DATA_SIZE(13)] = {
	13,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2962[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f29ca[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2a32[OAM_DATA_SIZE(19)] = {
	19,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(32, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2aa6[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(48, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2b14[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(64, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(64, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2b8e[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(80, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2c08[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(96, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(96, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(96, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2c8e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-106, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 462, 3, 0),
	OAM_ENTRY(-115, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 464, 3, 0),
	OAM_ENTRY(-112, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-84, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2cb4[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-113, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 3, 0),
	OAM_ENTRY(-93, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 3, 0),
	OAM_ENTRY(-109, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 494, 3, 0),
	OAM_ENTRY(-102, 0, OAM_DIMS_16x8, OAM_X_FLIP, 494, 3, 0),
	OAM_ENTRY(-110, 12, OAM_DIMS_32x8, OAM_X_FLIP, 496, 3, 0),
	OAM_ENTRY(-118, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 496, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-60, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2cf2[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-114, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 392, 3, 0),
	OAM_ENTRY(-90, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 396, 3, 0),
	OAM_ENTRY(-76, 4, OAM_DIMS_32x8, OAM_X_FLIP, 392, 3, 0),
	OAM_ENTRY(-120, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 500, 3, 0),
	OAM_ENTRY(-105, 12, OAM_DIMS_32x8, OAM_X_FLIP, 500, 3, 0),
	OAM_ENTRY(-111, 1, OAM_DIMS_32x8, OAM_NO_FLIP, 468, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-44, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2d36[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-115, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 424, 3, 0),
	OAM_ENTRY(-59, 4, OAM_DIMS_32x8, OAM_X_FLIP, 424, 3, 0),
	OAM_ENTRY(-90, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 428, 3, 0),
	OAM_ENTRY(-73, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 428, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-28, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2d6e[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-116, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-116, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-42, 2, OAM_DIMS_32x8, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-42, 6, OAM_DIMS_32x8, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-96, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-96, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-96, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2dd0[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-117, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-117, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-25, 0, OAM_DIMS_32x8, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-25, 8, OAM_DIMS_32x8, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-52, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-52, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-72, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2e32[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-118, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-118, 2, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-8, -2, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-8, 2, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-32, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-32, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(20, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2e9a[OAM_DATA_SIZE(19)] = {
	19,
	OAM_ENTRY(-119, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-119, 4, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(9, -4, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(9, 4, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(36, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2f0e[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-120, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-120, 6, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(26, -6, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(26, 6, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(0, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(0, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(52, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2f88[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-121, -7, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-121, 7, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(43, -7, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(43, 7, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(6, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(6, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(24, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(24, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(68, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f300e[OAM_DATA_SIZE(23)] = {
	23,
	OAM_ENTRY(-122, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-122, 8, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(60, -8, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(60, 8, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(32, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(84, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f309a[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(100, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f30d2[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 630, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 530, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 594, 8, 0),
};

static const u16 sOamFrame_5f30e6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 8, 0),
};

static const u16 sOamFrame_5f30fa[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 694, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 534, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 598, 8, 0),
};

static const u16 sOamFrame_5f310e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 626, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 690, 8, 0),
};

static const u16 sOamFrame_5f3122[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 692, 8, 0),
};

static const u16 sOamFrame_5f3130[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 552, 9, 0),
};

static const u16 sOamFrame_5f3138[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 772, 8, 0),
};

static const u16 sOamFrame_5f3140[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 8, 0),
};

static const u16 sOamFrame_5f3148[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3150[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3164[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3184[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-112, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f31b0[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-80, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -12, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
};

static const u16 sOamFrame_5f321e[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -16, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
};

static const u16 sOamFrame_5f328c[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-80, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -20, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x16, OAM_X_FLIP, 735, 8, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 735, 8, 0),
};

static const u16 sOamFrame_5f3306[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(56, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(56, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-104, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(-104, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 735, 9, 0),
	OAM_ENTRY(104, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(104, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x16, OAM_X_FLIP, 735, 9, 0),
};

static const u16 sOamFrame_5f3380[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f3388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
};

static const u16 sOamFrame_5f3390[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
};

static const u16 sOamFrame_5f339e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33d2[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33fe[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-120, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -12, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f346c[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-120, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -16, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f34da[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-120, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -20, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(112, -4, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
};

static const u16 sOamFrame_5f3554[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-120, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(112, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
};

static const u16 sOamFrame_5f35da[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3606[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3632[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3688[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f36de[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f370a[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3736[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f378c[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f37e2[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 780, 0, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 770, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 770, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f3826[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 910, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 780, 0, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 770, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 770, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f3870[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 784, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
};

static const u16 sOamFrame_5f38b4[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 908, 3, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 784, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
};

static const u16 sOamFrame_5f38fe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 772, 8, 0),
};

static const u16 sOamFrame_5f3906[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 8, 0),
};

static const u16 sOamFrame_5f390e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3916[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-12, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3924[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-24, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3950[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-24, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f398e[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f39d2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f39da[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 776, 9, 0),
};

static const u16 sOamFrame_5f39e2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f39ea[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-12, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-20, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f39f8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-24, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3a24[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-24, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 580, 9, 0),
};

static const u16 sOamFrame_5f3a62[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3aa6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 791, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3aba[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 793, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 857, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3ace[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 795, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 859, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3ae2[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 2, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 64, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 66, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3b2c[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 3, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 5, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 67, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 69, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3b76[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 6, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 70, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 72, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3bc0[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 9, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 73, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3c04[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 12, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 14, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 76, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 78, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3c48[OAM_DATA_SIZE(23)] = {
	23,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-35, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0, 5, 0),
	OAM_ENTRY(-19, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 2, 5, 0),
	OAM_ENTRY(-35, 2, OAM_DIMS_16x8, OAM_NO_FLIP, 64, 5, 0),
	OAM_ENTRY(-19, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 66, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 17, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 21, 5, 0),
	OAM_ENTRY(-10, -23, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-2, -29, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(30, -29, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 27, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3cd4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(119, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 144, 5, 0),
};

static const u16 sOamFrame_5f3cdc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(111, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 143, 5, 0),
};

static const u16 sOamFrame_5f3ce4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(111, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 143, 5, 0),
	OAM_ENTRY(103, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 142, 5, 0),
};

static const u16 sOamFrame_5f3cf2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
};

static const u16 sOamFrame_5f3cfa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(87, 6, OAM_DIMS_16x8, OAM_NO_FLIP, 139, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d1a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(87, 6, OAM_DIMS_16x8, OAM_NO_FLIP, 139, 5, 0),
	OAM_ENTRY(79, 6, OAM_DIMS_8x8, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d40[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d60[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(63, 11, OAM_DIMS_8x8, OAM_NO_FLIP, 112, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d86[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(55, 11, OAM_DIMS_16x8, OAM_NO_FLIP, 111, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3dac[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(55, 11, OAM_DIMS_16x8, OAM_NO_FLIP, 111, 5, 0),
	OAM_ENTRY(47, 11, OAM_DIMS_8x8, OAM_NO_FLIP, 110, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3dd8[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e10[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 108, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e4e[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(23, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 107, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e8c[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3eca[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3f08[OAM_DATA_SIZE(13)] = {
	13,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
};

static const u16 sOamFrame_5f3f58[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
};

static const u16 sOamFrame_5f3fae[OAM_DATA_SIZE(15)] = {
	15,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
};

static const u16 sOamFrame_5f400a[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 17, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 21, 5, 0),
};

static const u16 sOamFrame_5f4072[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 27, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 5, 0),
};

static const u16 sOamFrame_5f40da[OAM_DATA_SIZE(47)] = {
	47,
	OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 2, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 195, 2, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 226, 2, 0),
	OAM_ENTRY(8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 199, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 201, 2, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 320, 2, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 2, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 2, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 298, 2, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 362, 2, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 2, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 176, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 2, 0),
	OAM_ENTRY(-16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 303, 2, 0),
	OAM_ENTRY(-8, 80, OAM_DIMS_16x8, OAM_NO_FLIP, 336, 2, 0),
	OAM_ENTRY(-32, 64, OAM_DIMS_8x8, OAM_NO_FLIP, 269, 2, 0),
	OAM_ENTRY(24, 64, OAM_DIMS_8x8, OAM_NO_FLIP, 276, 2, 0),
	OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 243, 2, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 261, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 6, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 292, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 262, 4, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 197, 4, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 229, 4, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 227, 4, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 290, 4, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 4, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 324, 4, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 355, 4, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 356, 4, 0),
	OAM_ENTRY(-16, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 177, 4, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 225, 7, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 7, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 7, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 194, 7, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 234, 7, 0),
	OAM_ENTRY(40, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 267, 7, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 300, 7, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 209, 7, 0),
	OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 242, 7, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 181, 7, 0),
	OAM_ENTRY(40, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 184, 7, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 214, 7, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 207, 7, 0),
	OAM_ENTRY(-24, 64, OAM_DIMS_8x16, OAM_NO_FLIP, 270, 7, 0),
	OAM_ENTRY(16, 64, OAM_DIMS_8x16, OAM_NO_FLIP, 275, 7, 0),
	OAM_ENTRY(-16, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 271, 7, 0),
};

static const u16 sOamFrame_5f41f6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 149, 5, 0),
};

const struct FrameData sIntroArrivingAtBslBslPopupOam_Opening[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 84
	},
	[1] = {
		.pFrame = sOamFrame_5f2610,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f262a,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f2644,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2670,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f2696,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f26bc,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f2700,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2744,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f279a,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslBslPopupOam_Closing[10] = {
	[0] = {
		.pFrame = sOamFrame_5f279a,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f2744,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2700,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f26bc,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2696,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f2670,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2644,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f262a,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f2610,
		.timer = 1
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelFrameOam_Opening[13] = {
	[0] = {
		.pFrame = sOamFrame_5f27f0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f2828,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f2872,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f28bc,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2912,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2962,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f29ca,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2a32,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2aa6,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f2b14,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f2b8e,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f2c08,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelFrameOam_Closing[13] = {
	[0] = {
		.pFrame = sOamFrame_5f2c08,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f2b8e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2b14,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f2aa6,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2a32,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f29ca,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2962,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2912,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f28bc,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f2872,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f2828,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f27f0,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelBackgroundOam_Opening[13] = {
	[0] = {
		.pFrame = sOamFrame_5f2c8e,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f2cb4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f2cf2,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f2d36,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2d6e,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2dd0,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2e32,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2e9a,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2f0e,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f2f88,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f300e,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f309a,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelBackgroundOam_Closing[13] = {
	[0] = {
		.pFrame = sOamFrame_5f309a,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f300e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2f88,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f2f0e,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2e9a,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2e32,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2dd0,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2d6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f2d36,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f2cf2,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f2cb4,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f2c8e,
		.timer = 255
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Opening[5] = {
	[0] = {
		.pFrame = sOamFrame_5f30d2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f30e6,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f30fa,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Closing[5] = {
	[0] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f30fa,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f30e6,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f30d2,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4498[2] = {
	[0] = {
		.pFrame = sOamFrame_5f3122,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f44a8[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3138,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3140,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3148,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3150,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3164,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3184,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f31b0,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f321e,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f328c,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3306,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4500[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3306,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f328c,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f321e,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f31b0,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3184,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3164,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3150,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3148,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3140,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3138,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4558[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f35da,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3606,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3632,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3688,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f45b0[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3688,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3632,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3606,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f35da,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4608[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f36de,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f370a,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3736,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f378c,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4660[11] = {
	[0] = {
		.pFrame = sOamFrame_5f378c,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3736,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f370a,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f36de,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f46b8[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3380,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3388,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3390,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f339e,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f33b2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f33d2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f33fe,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f346c,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f34da,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3554,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4710[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3554,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f34da,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f346c,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f33fe,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f33d2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f33b2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f339e,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3390,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3388,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3380,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4768[2] = {
	[0] = {
		.pFrame = sOamFrame_5f37e2,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4778[3] = {
	[0] = {
		.pFrame = sOamFrame_5f37e2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3826,
		.timer = 8
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4790[2] = {
	[0] = {
		.pFrame = sOamFrame_5f3870,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47a0[3] = {
	[0] = {
		.pFrame = sOamFrame_5f3870,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f38b4,
		.timer = 8
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47b8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f38fe,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3906,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f390e,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3916,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3924,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3950,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f398e,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47f8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f398e,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3950,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3924,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3916,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f390e,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3906,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f38fe,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4838[8] = {
	[0] = {
		.pFrame = sOamFrame_5f39d2,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f39da,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f39e2,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f39ea,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f39f8,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3a24,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3a62,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4878[8] = {
	[0] = {
		.pFrame = sOamFrame_5f3a62,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3a24,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f39f8,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f39ea,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f39e2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f39da,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f39d2,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Glowing[6] = {
	[0] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3aa6,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f3aba,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f3ace,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f3aa6,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslShipTrajectoryOam[26] = {
	[0] = {
		.pFrame = sOamFrame_5f3cd4,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f3cdc,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5f3ce4,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5f3cf2,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5f3cfa,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5f3d1a,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5f3d40,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5f3d60,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5f3d86,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5f3dac,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5f3dd8,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5f3e10,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5f3e4e,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5f3e8c,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5f3eca,
		.timer = 27
	},
	[15] = {
		.pFrame = sOamFrame_5f3f08,
		.timer = 15
	},
	[16] = {
		.pFrame = sOamFrame_5f3f58,
		.timer = 3
	},
	[17] = {
		.pFrame = sOamFrame_5f3fae,
		.timer = 3
	},
	[18] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[19] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[20] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[21] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[22] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[23] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[24] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[25] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslPlanetsAndShipOam[6] = {
	[0] = {
		.pFrame = sOamFrame_5f3ae2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3b2c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f3b76,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f3bc0,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f3c04,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusCuredScreenGlareOam[3] = {
	[0] = {
		.pFrame = sOamFrame_5f40da,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f41f6,
		.timer = 1
	},
	[2] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5f4a00[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-37, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(-5, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 0, 0),
};

static const u16 sOamFrame_5f4a14[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-35, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-35, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 136, 0, 0),
	OAM_ENTRY(-3, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 140, 0, 0),
};

static const u16 sOamFrame_5f4a28[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-33, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 0, 0),
	OAM_ENTRY(-33, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 148, 0, 0),
};

static const u16 sOamFrame_5f4a3c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 24, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 156, 0, 0),
};

static const u16 sOamFrame_5f4a50[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5f4a64[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 168, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 296, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 0, 0),
};

static const u16 sOamFrame_5f4a78[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 176, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 304, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 308, 0, 0),
};

static const u16 sOamFrame_5f4a8c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 312, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 316, 0, 0),
};

static const u16 sOamFrame_5f4aa0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 448, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 452, 0, 0),
};

static const u16 sOamFrame_5f4ab4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 336, 0, 0),
};

static const u16 sOamFrame_5f4abc[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 544, 1, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 556, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_64x32, OAM_NO_FLIP, 484, 1, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_64x64, OAM_NO_FLIP, 612, 1, 0),
	OAM_ENTRY(-16, 56, OAM_DIMS_32x16, OAM_NO_FLIP, 870, 1, 0),
};

static const u16 sOamFrame_5f4adc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 3, 0),
};

static const u16 sOamFrame_5f4ae4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 795, 3, 0),
	OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 797, 3, 0),
};

static const u16 sOamFrame_5f4afe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 378, 3, 0),
};

static const u16 sOamFrame_5f4b06[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 378, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 440, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 440, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 440, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 440, 3, 0),
};

static const u16 sOamFrame_5f4b26[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 444, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 444, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 444, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 444, 3, 0),
	OAM_ENTRY(6, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(14, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(22, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-14, -4, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-22, -4, OAM_DIMS_8x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-30, -4, OAM_DIMS_8x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 380, 3, 0),
};

static const u16 sOamFrame_5f4b6a[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 572, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 572, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 572, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 572, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(36, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-36, -4, OAM_DIMS_32x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-52, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 382, 3, 0),
};

static const u16 sOamFrame_5f4ba2[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 568, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 568, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 568, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 568, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5f4be0[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
};

static const u16 sOamFrame_5f4c36[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-96, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
};

static const u16 sOamFrame_5f4ca4[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-96, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
};

static const u16 sOamFrame_5f4cee[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-36, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-72, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-108, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(20, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(56, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(92, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
};

static const u16 sOamFrame_5f4d14[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
};

const struct FrameData sIntroArrivingAtBslSamusShipOam[11] = {
	[0] = {
		.pFrame = sOamFrame_5f4a00,
		.timer = 50
	},
	[1] = {
		.pFrame = sOamFrame_5f4a14,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f4a28,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f4a3c,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f4a50,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f4a64,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5f4a78,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5f4a8c,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5f4aa0,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5f4ab4,
		.timer = 50
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslBslOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5f4abc,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslThrusterExplosionOam[18] = {
	[0] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f4b26,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f4b6a,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f4ba2,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5f4be0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5f4c36,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5f4ca4,
		.timer = 4
	},
	[15] = {
		.pFrame = sOamFrame_5f4cee,
		.timer = 5
	},
	[16] = {
		.pFrame = sOamFrame_5f4d14,
		.timer = 6
	},
	[17] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslThrustersOam[4] = {
	[0] = {
		.pFrame = sOamFrame_5f4afe,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[3] = FRAME_DATA_TERMINATOR
};

static const u8 sBlob_5f4e54_5f4ed4[] = INCBIN_U8("data/Blob_5f4e54_5f4ed4.bin");

const u16 sPal_5f4ed4[12 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5f4ed4.pal");
const u16 sIntroArrivingAtBslSpaceMapPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/space_map.pal");
const u16 sIntroApproachingBslObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/approaching_bsl_obj.pal");

const u32 sIntroTilemap_5f5454[385] = INCBIN_U32("data/new_file_intro/5f5454.tm.lz");
const u32 sIntroArrivingAtBslSpaceMapTilemap[368] = INCBIN_U32("data/new_file_intro/5f5a58.tm.lz");
const u32 sIntroSamusMonologueBgTilemap[368] = INCBIN_U32("data/new_file_intro/samus_monologue_bg.tm.lz");
const u32 sIntroTilemap_5f65d8[238] = INCBIN_U32("data/new_file_intro/5f65d8.tm.lz");

static const u8 sBlob_5f6990_prefix[0x79E0] = INCBIN_U8("data/Blob_5f6990_prefix.bin");

static const struct FrameData sIntroLandingFrameData[26] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7548),
        .timer = 8
    },
    [1] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7592),
        .timer = 8
    },
    [2] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x75FA),
        .timer = 8
    },
    [3] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7662),
        .timer = 8
    },
    [4] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x76CA),
        .timer = 8
    },
    [5] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7732),
        .timer = 8
    },
    [6] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x77B8),
        .timer = 8
    },
    [7] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x783E),
        .timer = 8
    },
    [8] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x78C4),
        .timer = 8
    },
    [9] = FRAME_DATA_TERMINATOR,
    [10] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x78C4),
        .timer = 8
    },
    [11] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x783E),
        .timer = 8
    },
    [12] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x77B8),
        .timer = 8
    },
    [13] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7732),
        .timer = 8
    },
    [14] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x76CA),
        .timer = 8
    },
    [15] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7662),
        .timer = 8
    },
    [16] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x75FA),
        .timer = 8
    },
    [17] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7592),
        .timer = 8
    },
    [18] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7548),
        .timer = 8
    },
    [19] = FRAME_DATA_TERMINATOR,
    [20] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x794A),
        .timer = 4
    },
    [21] = FRAME_DATA_TERMINATOR,
    [22] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x798E),
        .timer = 4
    },
    [23] = FRAME_DATA_TERMINATOR,
    [24] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_prefix + 0x7548),
        .timer = 4
    },
    [25] = FRAME_DATA_TERMINATOR
};

static const u8 sBlob_5f6990_middle[0x1098] = INCBIN_U8("data/Blob_5f6990_middle.bin");

static const struct FrameData sIntroShipLandingFrameData[70] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 8
    },
    [1] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x538),
        .timer = 8
    },
    [2] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x49A),
        .timer = 8
    },
    [3] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x3FC),
        .timer = 8
    },
    [4] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x352),
        .timer = 8
    },
    [5] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x2A8),
        .timer = 8
    },
    [6] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x1FE),
        .timer = 8
    },
    [7] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x154),
        .timer = 8
    },
    [8] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xAA),
        .timer = 8
    },
    [9] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x0),
        .timer = 100
    },
    [10] = FRAME_DATA_TERMINATOR,
    [11] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 4
    },
    [12] = FRAME_DATA_TERMINATOR,
    [13] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 12
    },
    [14] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x65C),
        .timer = 12
    },
    [15] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x6EE),
        .timer = 12
    },
    [16] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x780),
        .timer = 12
    },
    [17] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x6EE),
        .timer = 12
    },
    [18] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x65C),
        .timer = 12
    },
    [19] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 255
    },
    [20] = FRAME_DATA_TERMINATOR,
    [21] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x0),
        .timer = 8
    },
    [22] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x812),
        .timer = 8
    },
    [23] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x8BC),
        .timer = 8
    },
    [24] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x812),
        .timer = 8
    },
    [25] = FRAME_DATA_TERMINATOR,
    [26] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x0),
        .timer = 4
    },
    [27] = FRAME_DATA_TERMINATOR,
    [28] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x966),
        .timer = 4
    },
    [29] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x9D4),
        .timer = 4
    },
    [30] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xA4E),
        .timer = 4
    },
    [31] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xAEC),
        .timer = 4
    },
    [32] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xB8A),
        .timer = 4
    },
    [33] = FRAME_DATA_TERMINATOR,
    [34] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xC72),
        .timer = 4
    },
    [35] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xCE0),
        .timer = 4
    },
    [36] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xD72),
        .timer = 4
    },
    [37] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xE04),
        .timer = 4
    },
    [38] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xE66),
        .timer = 4
    },
    [39] = FRAME_DATA_TERMINATOR,
    [40] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xE98),
        .timer = 4
    },
    [41] = FRAME_DATA_TERMINATOR,
    [42] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xEA6),
        .timer = 4
    },
    [43] = FRAME_DATA_TERMINATOR,
    [44] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xEE4),
        .timer = 4
    },
    [45] = FRAME_DATA_TERMINATOR,
    [46] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x0),
        .timer = 50
    },
    [47] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xAA),
        .timer = 8
    },
    [48] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x154),
        .timer = 8
    },
    [49] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x1FE),
        .timer = 8
    },
    [50] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x2A8),
        .timer = 8
    },
    [51] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x352),
        .timer = 8
    },
    [52] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x3FC),
        .timer = 8
    },
    [53] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x49A),
        .timer = 8
    },
    [54] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x538),
        .timer = 8
    },
    [55] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 50
    },
    [56] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x5CA),
        .timer = 12
    },
    [57] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x65C),
        .timer = 12
    },
    [58] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x6EE),
        .timer = 12
    },
    [59] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x780),
        .timer = 100
    },
    [60] = FRAME_DATA_TERMINATOR,
    [61] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xF16),
        .timer = 6
    },
    [62] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xF54),
        .timer = 6
    },
    [63] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xF92),
        .timer = 6
    },
    [64] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0xFD0),
        .timer = 6
    },
    [65] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x100E),
        .timer = 6
    },
    [66] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x104C),
        .timer = 6
    },
    [67] = FRAME_DATA_TERMINATOR,
    [68] = {
        .pFrame = (const u16*)((u8*)sBlob_5f6990_middle + 0x108A),
        .timer = 4
    },
    [69] = FRAME_DATA_TERMINATOR
};

static const u8 sBlob_5f6990_after[0x1234] = INCBIN_U8("data/Blob_5f6990_after.bin");

const u32 sIntroSamusSittingGfx[4818] = INCBIN_U32("data/new_file_intro/samus_sitting.gfx.lz");
const u16 sIntroSamusSittingPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_sitting.pal");
const u32 sIntroSamusSittingTilemap[171] = INCBIN_U32("data/new_file_intro/samus_sitting.tm.lz");

static const u8 sBlob_605930_605d08[] = INCBIN_U8("data/Blob_605930_605d08.bin");

const u32 sTitleScreenSpaceBackgroundGfx[830] = INCBIN_U32("data/menus/title_screen/space_background.gfx.lz");

static const u8 sBlob_606a00_609020[] = INCBIN_U8("data/Blob_606a00_609020.bin");

const u16 sPal_609020[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/609020.pal");
const u16 sTitleScreenSpaceBackgroundPal[8 * PAL_ROW] = INCBIN_U16("data/menus/title_screen/space_background.pal");

const u32 sTitleScreenSpaceBackgroundTilemap[172] = INCBIN_U32("data/menus/title_screen/space_background.tm.lz");

static const u8 sBlob_6094d0_before[0x1738] = INCBIN_U8("data/Blob_6094d0_before.bin");

static const struct FrameData sIntroMonologueFrameData[9] = {
    [0] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x688),
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR,
    [2] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x690),
        .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR,
    [4] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x698),
        .timer = 4
    },
    [5] = FRAME_DATA_TERMINATOR,
    [6] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6A0),
        .timer = 4
    },
    [7] = FRAME_DATA_TERMINATOR,
    [8] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6A8),
        .timer = 255
    }
};

static const struct FrameData sIntroFrameDataAfter[159] = {
    [0] = FRAME_DATA_TERMINATOR,
    [1] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6B0),
        .timer = 255
    },
    [2] = FRAME_DATA_TERMINATOR,
    [3] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6B8),
        .timer = 255
    },
    [4] = FRAME_DATA_TERMINATOR,
    [5] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6C0),
        .timer = 255
    },
    [6] = FRAME_DATA_TERMINATOR,
    [7] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6C8),
        .timer = 4
    },
    [8] = FRAME_DATA_TERMINATOR,
    [9] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1982),
        .timer = 1
    },
    [10] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6DE),
        .timer = 1
    },
    [11] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1996),
        .timer = 1
    },
    [12] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1982),
        .timer = 1
    },
    [13] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x6DE),
        .timer = 1
    },
    [14] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x19AA),
        .timer = 1
    },
    [15] = FRAME_DATA_TERMINATOR,
    [16] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x19B8),
        .timer = 1
    },
    [17] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x19CC),
        .timer = 1
    },
    [18] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x19D4),
        .timer = 1
    },
    [19] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x19CC),
        .timer = 1
    },
    [20] = FRAME_DATA_TERMINATOR,
    [21] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x724),
        .timer = 4
    },
    [22] = FRAME_DATA_TERMINATOR,
    [23] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x732),
        .timer = 4
    },
    [24] = FRAME_DATA_TERMINATOR,
    [25] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x758),
        .timer = 4
    },
    [26] = FRAME_DATA_TERMINATOR,
    [27] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x772),
        .timer = 4
    },
    [28] = FRAME_DATA_TERMINATOR,
    [29] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x780),
        .timer = 4
    },
    [30] = FRAME_DATA_TERMINATOR,
    [31] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB8A),
        .timer = 4
    },
    [32] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB92),
        .timer = 4
    },
    [33] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xBB2),
        .timer = 4
    },
    [34] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xBEA),
        .timer = 4
    },
    [35] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xC34),
        .timer = 4
    },
    [36] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xC84),
        .timer = 4
    },
    [37] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xCDA),
        .timer = 6
    },
    [38] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xD24),
        .timer = 7
    },
    [39] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xD5C),
        .timer = 8
    },
    [40] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xD76),
        .timer = 9
    },
    [41] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xD8A),
        .timer = 10
    },
    [42] = FRAME_DATA_TERMINATOR,
    [43] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xD92),
        .timer = 1
    },
    [44] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDA0),
        .timer = 1
    },
    [45] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDA8),
        .timer = 1
    },
    [46] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDA0),
        .timer = 1
    },
    [47] = FRAME_DATA_TERMINATOR,
    [48] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDB6),
        .timer = 1
    },
    [49] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDC4),
        .timer = 1
    },
    [50] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDCC),
        .timer = 1
    },
    [51] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDC4),
        .timer = 1
    },
    [52] = FRAME_DATA_TERMINATOR,
    [53] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDDA),
        .timer = 140
    },
    [54] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB88),
        .timer = 140
    },
    [55] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xDF4),
        .timer = 180
    },
    [56] = FRAME_DATA_TERMINATOR,
    [57] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE0E),
        .timer = 4
    },
    [58] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE16),
        .timer = 4
    },
    [59] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE24),
        .timer = 4
    },
    [60] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE38),
        .timer = 4
    },
    [61] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE52),
        .timer = 4
    },
    [62] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE72),
        .timer = 4
    },
    [63] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE98),
        .timer = 4
    },
    [64] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xEC4),
        .timer = 4
    },
    [65] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xEF6),
        .timer = 4
    },
    [66] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xF2E),
        .timer = 4
    },
    [67] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xF6C),
        .timer = 4
    },
    [68] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xFB0),
        .timer = 4
    },
    [69] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xFFA),
        .timer = 4
    },
    [70] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x104A),
        .timer = 4
    },
    [71] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x10A0),
        .timer = 4
    },
    [72] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x10FC),
        .timer = 100
    },
    [73] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB88),
        .timer = 100
    },
    [74] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x115E),
        .timer = 6
    },
    [75] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1166),
        .timer = 6
    },
    [76] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1174),
        .timer = 6
    },
    [77] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1188),
        .timer = 6
    },
    [78] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x11A2),
        .timer = 6
    },
    [79] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x11C2),
        .timer = 6
    },
    [80] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x11E8),
        .timer = 6
    },
    [81] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1214),
        .timer = 6
    },
    [82] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1246),
        .timer = 6
    },
    [83] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x127E),
        .timer = 6
    },
    [84] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x12BC),
        .timer = 6
    },
    [85] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1300),
        .timer = 6
    },
    [86] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x134A),
        .timer = 120
    },
    [87] = FRAME_DATA_TERMINATOR,
    [88] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE0E),
        .timer = 4
    },
    [89] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE16),
        .timer = 4
    },
    [90] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE24),
        .timer = 4
    },
    [91] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE38),
        .timer = 4
    },
    [92] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE52),
        .timer = 4
    },
    [93] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE72),
        .timer = 4
    },
    [94] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xE98),
        .timer = 4
    },
    [95] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xEC4),
        .timer = 4
    },
    [96] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xEF6),
        .timer = 4
    },
    [97] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xF2E),
        .timer = 4
    },
    [98] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xF6C),
        .timer = 4
    },
    [99] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xFB0),
        .timer = 4
    },
    [100] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xFFA),
        .timer = 4
    },
    [101] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x104A),
        .timer = 4
    },
    [102] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x10A0),
        .timer = 4
    },
    [103] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x10FC),
        .timer = 100
    },
    [104] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB88),
        .timer = 100
    },
    [105] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x139A),
        .timer = 6
    },
    [106] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x13A2),
        .timer = 6
    },
    [107] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x13B0),
        .timer = 6
    },
    [108] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x13C4),
        .timer = 6
    },
    [109] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x13DE),
        .timer = 6
    },
    [110] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x13FE),
        .timer = 6
    },
    [111] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1424),
        .timer = 6
    },
    [112] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1450),
        .timer = 120
    },
    [113] = FRAME_DATA_TERMINATOR,
    [114] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1482),
        .timer = 3
    },
    [115] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x148A),
        .timer = 3
    },
    [116] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1498),
        .timer = 3
    },
    [117] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x14AC),
        .timer = 3
    },
    [118] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x14FC),
        .timer = 3
    },
    [119] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x154C),
        .timer = 3
    },
    [120] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x159C),
        .timer = 3
    },
    [121] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x15F2),
        .timer = 3
    },
    [122] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1630),
        .timer = 3
    },
    [123] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x166E),
        .timer = 3
    },
    [124] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x16AC),
        .timer = 3
    },
    [125] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x16F0),
        .timer = 3
    },
    [126] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1734),
        .timer = 3
    },
    [127] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1778),
        .timer = 3
    },
    [128] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x17B6),
        .timer = 3
    },
    [129] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x17F4),
        .timer = 3
    },
    [130] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x184A),
        .timer = 3
    },
    [131] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x189A),
        .timer = 3
    },
    [132] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x18E4),
        .timer = 3
    },
    [133] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1916),
        .timer = 3
    },
    [134] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x193C),
        .timer = 3
    },
    [135] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB88),
        .timer = 200
    },
    [136] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1482),
        .timer = 3
    },
    [137] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x148A),
        .timer = 3
    },
    [138] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1498),
        .timer = 3
    },
    [139] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x14AC),
        .timer = 3
    },
    [140] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x14FC),
        .timer = 3
    },
    [141] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x154C),
        .timer = 3
    },
    [142] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x159C),
        .timer = 3
    },
    [143] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x15F2),
        .timer = 3
    },
    [144] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1630),
        .timer = 3
    },
    [145] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x166E),
        .timer = 3
    },
    [146] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x16AC),
        .timer = 3
    },
    [147] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x16F0),
        .timer = 3
    },
    [148] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1734),
        .timer = 3
    },
    [149] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1778),
        .timer = 3
    },
    [150] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x17B6),
        .timer = 3
    },
    [151] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x17F4),
        .timer = 3
    },
    [152] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x184A),
        .timer = 3
    },
    [153] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x189A),
        .timer = 3
    },
    [154] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x18E4),
        .timer = 3
    },
    [155] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x1916),
        .timer = 3
    },
    [156] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0x193C),
        .timer = 3
    },
    [157] = {
        .pFrame = (const u16*)((u8*)sTitleScreenSpaceBackgroundTilemap + 0xB88),
        .timer = 126
    },
    [158] = FRAME_DATA_TERMINATOR
};

const u8 sIntroSpaceTilemap[1320] = INCBIN_U8("data/new_file_intro/space_bg.tm.lz");
const u8 sIntroBslTilemap[1586] = INCBIN_U8("data/new_file_intro/bsl_bg.tm.lz");

static const u8 padding[2] = {0, 0};

const u32 sIntroBslSpaceBgGfx[4421] = INCBIN_U32("data/new_file_intro/bsl_space_bg.gfx.lz");

static const u8 sBlob_6101b8_612e48[] = INCBIN_U8("data/Blob_6101b8_612e48.bin");

const u16 sIntroBslSpaceBgPal[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/bsl_space_bg.pal");
const u16 sPal_612f48[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/612f48.pal");

const u32 sNextPageArrowGfx[8] = INCBIN_U32("data/new_file_intro/next_page_arrow.gfx");

static const u16 sOamFrame_613168[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

static const u16 sOamFrame_613170[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

static const u16 sOamFrame_613178[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

const struct FrameData sIntroNextPageArrowOam[5] = {
    [0] = {
            .pFrame = sOamFrame_613168,
            .timer = 8
    },
    [1] = {
            .pFrame = sOamFrame_613170,
            .timer = 8
    },
    [2] = {
            .pFrame = sOamFrame_613178,
            .timer = 8
    },
    [3] = {
            .pFrame = sOamFrame_613170,
            .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const u16 sNextPageArrowPal[1 * PAL_ROW] = INCBIN_U16("data/new_file_intro/next_page_arrow.pal");

static const u8 sBlob_6131c8_63a19c[] = INCBIN_U8("data/Blob_6131c8_63a19c.bin");

const u16 sCutsceneTextNone[2] = {
    CHAR_TERMINATOR, CHAR_TERMINATOR
};

const u32 sIntroSr388SurfaceBgGfx0[686] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_0.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx1[767] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_1.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx2[848] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_2.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx3[641] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_3.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx4[577] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_4.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx5[655] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_5.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx6[513] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_6.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx7[177] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_7.gfx.lz");

const u32 sIntroSr388PlanetBgGfx0[719] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_0.gfx.lz");
const u32 sIntroSr388PlanetBgGfx1[809] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_1.gfx.lz");
const u32 sIntroSr388PlanetBgGfx2[794] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_2.gfx.lz");
const u32 sIntroSr388PlanetBgGfx3[782] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_3.gfx.lz");
const u32 sIntroSr388PlanetBgGfx4[772] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_4.gfx.lz");

const u32 sIntroBslObjectGfx0[448] = INCBIN_U32("data/new_file_intro/bsl_object_0.gfx.lz");
const u32 sIntroBslObjectGfx1[402] = INCBIN_U32("data/new_file_intro/bsl_object_1.gfx.lz");
const u32 sIntroBslObjectGfx2[420] = INCBIN_U32("data/new_file_intro/bsl_object_2.gfx.lz");
const u32 sIntroBslObjectGfx3[124] = INCBIN_U32("data/new_file_intro/bsl_object_3.gfx.lz");
const u32 sIntroBslObjectGfx4[298] = INCBIN_U32("data/new_file_intro/bsl_object_4.gfx.lz");
const u32 sIntroBslObjectGfx5[186] = INCBIN_U32("data/new_file_intro/bsl_object_5.gfx.lz");
const u32 sIntroBslObjectGfx6[543] = INCBIN_U32("data/new_file_intro/bsl_object_6.gfx.lz");
const u32 sIntroBslObjectGfx7[482] = INCBIN_U32("data/new_file_intro/bsl_object_7.gfx.lz");

const u32 sIntroSamusSittingBgGfx0[920] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_0.gfx.lz");
const u32 sIntroSamusSittingBgGfx1[978] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_1.gfx.lz");
const u32 sIntroSamusSittingBgGfx2[962] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_2.gfx.lz");
const u32 sIntroSamusSittingBgGfx3[944] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_3.gfx.lz");
const u32 sIntroSamusSittingBgGfx4[800] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_4.gfx.lz");

const u32 sIntroSamusHelmetCloseupBgGfx0[598] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_0.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx1[848] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_1.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx2[908] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_2.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx3[812] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_3.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx4[844] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_4.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx5[403] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_5.gfx.lz");

struct NewFileIntroGfxBlob {
    u8 seg_0000_D6C8[0xD6C8];
    const u16 *pD6C8; /* +0xD6C8 -> +0xD6BE */
    u8 seg_D6CC_D6D0[0x4];
    const u16 *pD6D0; /* +0xD6D0 -> +0xBD64 */
    u8 seg_D6D4_D6D8[0x4];
    const u16 *pD6D8; /* +0xD6D8 -> +0xBD78 */
    u8 seg_D6DC_D6E0[0x4];
    const u16 *pD6E0; /* +0xD6E0 -> +0xBD92 */
    u8 seg_D6E4_D6E8[0x4];
    const u16 *pD6E8; /* +0xD6E8 -> +0xBDAC */
    u8 seg_D6EC_D6F0[0x4];
    const u16 *pD6F0; /* +0xD6F0 -> +0xBDCC */
    u8 seg_D6F4_D6F8[0x4];
    const u16 *pD6F8; /* +0xD6F8 -> +0xBDEC */
    u8 seg_D6FC_D700[0x4];
    const u16 *pD700; /* +0xD700 -> +0xBE0C */
    u8 seg_D704_D708[0x4];
    const u16 *pD708; /* +0xD708 -> +0xBE2C */
    u8 seg_D70C_D710[0x4];
    const u16 *pD710; /* +0xD710 -> +0xBE4C */
    u8 seg_D714_D718[0x4];
    const u16 *pD718; /* +0xD718 -> +0xBE6C */
    u8 seg_D71C_D720[0x4];
    const u16 *pD720; /* +0xD720 -> +0xBE8C */
    u8 seg_D724_D728[0x4];
    const u16 *pD728; /* +0xD728 -> +0xBEB8 */
    u8 seg_D72C_D730[0x4];
    const u16 *pD730; /* +0xD730 -> +0xBEE4 */
    u8 seg_D734_D738[0x4];
    const u16 *pD738; /* +0xD738 -> +0xBF10 */
    u8 seg_D73C_D740[0x4];
    const u16 *pD740; /* +0xD740 -> +0xBF3C */
    u8 seg_D744_D748[0x4];
    const u16 *pD748; /* +0xD748 -> +0xBF68 */
    u8 seg_D74C_D750[0x4];
    const u16 *pD750; /* +0xD750 -> +0xBF94 */
    u8 seg_D754_D758[0x4];
    const u16 *pD758; /* +0xD758 -> +0xBFC0 */
    u8 seg_D75C_D760[0x4];
    const u16 *pD760; /* +0xD760 -> +0xBFF2 */
    u8 seg_D764_D768[0x4];
    const u16 *pD768; /* +0xD768 -> +0xC02A */
    u8 seg_D76C_D770[0x4];
    const u16 *pD770; /* +0xD770 -> +0xC062 */
    u8 seg_D774_D778[0x4];
    const u16 *pD778; /* +0xD778 -> +0xC09A */
    u8 seg_D77C_D780[0x4];
    const u16 *pD780; /* +0xD780 -> +0xC0D2 */
    u8 seg_D784_D788[0x4];
    const u16 *pD788; /* +0xD788 -> +0xC10A */
    u8 seg_D78C_D790[0x4];
    const u16 *pD790; /* +0xD790 -> +0xC142 */
    u8 seg_D794_D798[0x4];
    const u16 *pD798; /* +0xD798 -> +0xC180 */
    u8 seg_D79C_D7A0[0x4];
    const u16 *pD7A0; /* +0xD7A0 -> +0xC1C4 */
    u8 seg_D7A4_D7A8[0x4];
    const u16 *pD7A8; /* +0xD7A8 -> +0xC208 */
    u8 seg_D7AC_D7B0[0x4];
    const u16 *pD7B0; /* +0xD7B0 -> +0xC24C */
    u8 seg_D7B4_D7B8[0x4];
    const u16 *pD7B8; /* +0xD7B8 -> +0xC290 */
    u8 seg_D7BC_D7C0[0x4];
    const u16 *pD7C0; /* +0xD7C0 -> +0xC2D4 */
    u8 seg_D7C4_D7C8[0x4];
    const u16 *pD7C8; /* +0xD7C8 -> +0xC318 */
    u8 seg_D7CC_D7D0[0x4];
    const u16 *pD7D0; /* +0xD7D0 -> +0xC35C */
    u8 seg_D7D4_D7D8[0x4];
    const u16 *pD7D8; /* +0xD7D8 -> +0xC3A6 */
    u8 seg_D7DC_D7E0[0x4];
    const u16 *pD7E0; /* +0xD7E0 -> +0xC3F6 */
    u8 seg_D7E4_D7E8[0x4];
    const u16 *pD7E8; /* +0xD7E8 -> +0xC446 */
    u8 seg_D7EC_D7F0[0x4];
    const u16 *pD7F0; /* +0xD7F0 -> +0xC496 */
    u8 seg_D7F4_D7F8[0x4];
    const u16 *pD7F8; /* +0xD7F8 -> +0xC4E6 */
    u8 seg_D7FC_D800[0x4];
    const u16 *pD800; /* +0xD800 -> +0xD6BE */
    u8 seg_D804_D808[0x4];
    const u16 *pD808; /* +0xD808 -> +0xC4E6 */
    u8 seg_D80C_D810[0x4];
    const u16 *pD810; /* +0xD810 -> +0xD6BE */
    u8 seg_D814_D818[0x4];
    const u16 *pD818; /* +0xD818 -> +0xC4E6 */
    u8 seg_D81C_D820[0x4];
    const u16 *pD820; /* +0xD820 -> +0xD6BE */
    u8 seg_D824_D828[0x4];
    const u16 *pD828; /* +0xD828 -> +0xC536 */
    u8 seg_D82C_D830[0x4];
    const u16 *pD830; /* +0xD830 -> +0xC58C */
    u8 seg_D834_D838[0x4];
    const u16 *pD838; /* +0xD838 -> +0xC5E8 */
    u8 seg_D83C_D840[0x4];
    const u16 *pD840; /* +0xD840 -> +0xC64A */
    u8 seg_D844_D848[0x4];
    const u16 *pD848; /* +0xD848 -> +0xC6B2 */
    u8 seg_D84C_D850[0x4];
    const u16 *pD850; /* +0xD850 -> +0xC720 */
    u8 seg_D854_D858[0x4];
    const u16 *pD858; /* +0xD858 -> +0xC782 */
    u8 seg_D85C_D860[0x4];
    const u16 *pD860; /* +0xD860 -> +0xC7F0 */
    u8 seg_D864_D868[0x4];
    const u16 *pD868; /* +0xD868 -> +0xC876 */
    u8 seg_D86C_D870[0x4];
    const u16 *pD870; /* +0xD870 -> +0xC876 */
    u8 seg_D874_D878[0x4];
    const u16 *pD878; /* +0xD878 -> +0xC876 */
    u8 seg_D87C_D880[0x4];
    const u16 *pD880; /* +0xD880 -> +0xC876 */
    u8 seg_D884_D890[0xC];
    const u16 *pD890; /* +0xD890 -> +0xB780 */
    u8 seg_D894_D898[0x4];
    const u16 *pD898; /* +0xD898 -> +0xB7C4 */
    u8 seg_D89C_D8A0[0x4];
    const u16 *pD8A0; /* +0xD8A0 -> +0xB802 */
    u8 seg_D8A4_D8A8[0x4];
    const u16 *pD8A8; /* +0xD8A8 -> +0xB846 */
    u8 seg_D8AC_D8B0[0x4];
    const u16 *pD8B0; /* +0xD8B0 -> +0xB88A */
    u8 seg_D8B4_D8B8[0x4];
    const u16 *pD8B8; /* +0xD8B8 -> +0xB8C8 */
    u8 seg_D8BC_D8C0[0x4];
    const u16 *pD8C0; /* +0xD8C0 -> +0xB906 */
    u8 seg_D8C4_D8C8[0x4];
    const u16 *pD8C8; /* +0xD8C8 -> +0xB938 */
    u8 seg_D8CC_D8D8[0xC];
    const u16 *pD8D8; /* +0xD8D8 -> +0xB734 */
    u8 seg_D8DC_D8E0[0x4];
    const u16 *pD8E0; /* +0xD8E0 -> +0xB760 */
    u8 seg_D8E4_D8F0[0xC];
    const u16 *pD8F0; /* +0xD8F0 -> +0xD6BE */
    u8 seg_D8F4_D8F8[0x4];
    const u16 *pD8F8; /* +0xD8F8 -> +0xB970 */
    u8 seg_D8FC_D900[0x4];
    const u16 *pD900; /* +0xD900 -> +0xB978 */
    u8 seg_D904_D908[0x4];
    const u16 *pD908; /* +0xD908 -> +0xB980 */
    u8 seg_D90C_D910[0x4];
    const u16 *pD910; /* +0xD910 -> +0xB988 */
    u8 seg_D914_D918[0x4];
    const u16 *pD918; /* +0xD918 -> +0xB990 */
    u8 seg_D91C_D920[0x4];
    const u16 *pD920; /* +0xD920 -> +0xB998 */
    u8 seg_D924_D928[0x4];
    const u16 *pD928; /* +0xD928 -> +0xB9A0 */
    u8 seg_D92C_D930[0x4];
    const u16 *pD930; /* +0xD930 -> +0xB9A8 */
    u8 seg_D934_D938[0x4];
    const u16 *pD938; /* +0xD938 -> +0xB9C2 */
    u8 seg_D93C_D940[0x4];
    const u16 *pD940; /* +0xD940 -> +0xB9EE */
    u8 seg_D944_D948[0x4];
    const u16 *pD948; /* +0xD948 -> +0xBA20 */
    u8 seg_D94C_D950[0x4];
    const u16 *pD950; /* +0xD950 -> +0xBA58 */
    u8 seg_D954_D958[0x4];
    const u16 *pD958; /* +0xD958 -> +0xBAAE */
    u8 seg_D95C_D960[0x4];
    const u16 *pD960; /* +0xD960 -> +0xBB16 */
    u8 seg_D964_D968[0x4];
    const u16 *pD968; /* +0xD968 -> +0xBB84 */
    u8 seg_D96C_D970[0x4];
    const u16 *pD970; /* +0xD970 -> +0xBB84 */
    u8 seg_D974_D978[0x4];
    const u16 *pD978; /* +0xD978 -> +0xBB84 */
    u8 seg_D97C_D980[0x4];
    const u16 *pD980; /* +0xD980 -> +0xBB84 */
    u8 seg_D984_D990[0xC];
    const u16 *pD990; /* +0xD990 -> +0xD6BE */
    u8 seg_D994_D998[0x4];
    const u16 *pD998; /* +0xD998 -> +0xD69E */
    u8 seg_D99C_D9A0[0x4];
    const u16 *pD9A0; /* +0xD9A0 -> +0xD67E */
    u8 seg_D9A4_D9A8[0x4];
    const u16 *pD9A8; /* +0xD9A8 -> +0xD658 */
    u8 seg_D9AC_D9B0[0x4];
    const u16 *pD9B0; /* +0xD9B0 -> +0xD638 */
    u8 seg_D9B4_D9B8[0x4];
    const u16 *pD9B8; /* +0xD9B8 -> +0xD618 */
    u8 seg_D9BC_D9C0[0x4];
    const u16 *pD9C0; /* +0xD9C0 -> +0xD5EC */
    u8 seg_D9C4_D9C8[0x4];
    const u16 *pD9C8; /* +0xD9C8 -> +0xD5C0 */
    u8 seg_D9CC_D9D0[0x4];
    const u16 *pD9D0; /* +0xD9D0 -> +0xD594 */
    u8 seg_D9D4_D9D8[0x4];
    const u16 *pD9D8; /* +0xD9D8 -> +0xD568 */
    u8 seg_D9DC_D9E0[0x4];
    const u16 *pD9E0; /* +0xD9E0 -> +0xD53C */
    u8 seg_D9E4_D9E8[0x4];
    const u16 *pD9E8; /* +0xD9E8 -> +0xD516 */
    u8 seg_D9EC_D9F0[0x4];
    const u16 *pD9F0; /* +0xD9F0 -> +0xD4F0 */
    u8 seg_D9F4_D9F8[0x4];
    const u16 *pD9F8; /* +0xD9F8 -> +0xD4C4 */
    u8 seg_D9FC_DA00[0x4];
    const u16 *pDA00; /* +0xDA00 -> +0xD498 */
    u8 seg_DA04_DA08[0x4];
    const u16 *pDA08; /* +0xDA08 -> +0xD46C */
    u8 seg_DA0C_DA10[0x4];
    const u16 *pDA10; /* +0xDA10 -> +0xD440 */
    u8 seg_DA14_DA18[0x4];
    const u16 *pDA18; /* +0xDA18 -> +0xD414 */
    u8 seg_DA1C_DA20[0x4];
    const u16 *pDA20; /* +0xDA20 -> +0xD3EE */
    u8 seg_DA24_DA28[0x4];
    const u16 *pDA28; /* +0xDA28 -> +0xD3C2 */
    u8 seg_DA2C_DA30[0x4];
    const u16 *pDA30; /* +0xDA30 -> +0xD39C */
    u8 seg_DA34_DA38[0x4];
    const u16 *pDA38; /* +0xDA38 -> +0xD37C */
    u8 seg_DA3C_DA40[0x4];
    const u16 *pDA40; /* +0xDA40 -> +0xD350 */
    u8 seg_DA44_DA48[0x4];
    const u16 *pDA48; /* +0xDA48 -> +0xD324 */
    u8 seg_DA4C_DA50[0x4];
    const u16 *pDA50; /* +0xDA50 -> +0xD2F8 */
    u8 seg_DA54_DA58[0x4];
    const u16 *pDA58; /* +0xDA58 -> +0xD2CC */
    u8 seg_DA5C_DA60[0x4];
    const u16 *pDA60; /* +0xDA60 -> +0xD2A0 */
    u8 seg_DA64_DA68[0x4];
    const u16 *pDA68; /* +0xDA68 -> +0xD27A */
    u8 seg_DA6C_DA70[0x4];
    const u16 *pDA70; /* +0xDA70 -> +0xD254 */
    u8 seg_DA74_DA78[0x4];
    const u16 *pDA78; /* +0xDA78 -> +0xD234 */
    u8 seg_DA7C_DA80[0x4];
    const u16 *pDA80; /* +0xDA80 -> +0xD214 */
    u8 seg_DA84_DA88[0x4];
    const u16 *pDA88; /* +0xDA88 -> +0xD1E8 */
    u8 seg_DA8C_DA90[0x4];
    const u16 *pDA90; /* +0xDA90 -> +0xD1BC */
    u8 seg_DA94_DAA0[0xC];
    const u16 *pDAA0; /* +0xDAA0 -> +0xD190 */
    u8 seg_DAA4_DAA8[0x4];
    const u16 *pDAA8; /* +0xDAA8 -> +0xD164 */
    u8 seg_DAAC_DAB0[0x4];
    const u16 *pDAB0; /* +0xDAB0 -> +0xD138 */
    u8 seg_DAB4_DAB8[0x4];
    const u16 *pDAB8; /* +0xDAB8 -> +0xD10C */
    u8 seg_DABC_DAC0[0x4];
    const u16 *pDAC0; /* +0xDAC0 -> +0xD0E6 */
    u8 seg_DAC4_DAC8[0x4];
    const u16 *pDAC8; /* +0xDAC8 -> +0xD0C0 */
    u8 seg_DACC_DAD0[0x4];
    const u16 *pDAD0; /* +0xDAD0 -> +0xD0A0 */
    u8 seg_DAD4_DAD8[0x4];
    const u16 *pDAD8; /* +0xDAD8 -> +0xD080 */
    u8 seg_DADC_DAE0[0x4];
    const u16 *pDAE0; /* +0xDAE0 -> +0xD04E */
    u8 seg_DAE4_DAE8[0x4];
    const u16 *pDAE8; /* +0xDAE8 -> +0xD01C */
    u8 seg_DAEC_DAF0[0x4];
    const u16 *pDAF0; /* +0xDAF0 -> +0xCFEA */
    u8 seg_DAF4_DAF8[0x4];
    const u16 *pDAF8; /* +0xDAF8 -> +0xCFB8 */
    u8 seg_DAFC_DB00[0x4];
    const u16 *pDB00; /* +0xDB00 -> +0xCF92 */
    u8 seg_DB04_DB08[0x4];
    const u16 *pDB08; /* +0xDB08 -> +0xCF66 */
    u8 seg_DB0C_DB10[0x4];
    const u16 *pDB10; /* +0xDB10 -> +0xCF40 */
    u8 seg_DB14_DB18[0x4];
    const u16 *pDB18; /* +0xDB18 -> +0xCF1A */
    u8 seg_DB1C_DB20[0x4];
    const u16 *pDB20; /* +0xDB20 -> +0xCEFA */
    u8 seg_DB24_DB28[0x4];
    const u16 *pDB28; /* +0xDB28 -> +0xCEDA */
    u8 seg_DB2C_DB30[0x4];
    const u16 *pDB30; /* +0xDB30 -> +0xCEAE */
    u8 seg_DB34_DB38[0x4];
    const u16 *pDB38; /* +0xDB38 -> +0xCE82 */
    u8 seg_DB3C_DB40[0x4];
    const u16 *pDB40; /* +0xDB40 -> +0xCE56 */
    u8 seg_DB44_DB48[0x4];
    const u16 *pDB48; /* +0xDB48 -> +0xCE2A */
    u8 seg_DB4C_DB50[0x4];
    const u16 *pDB50; /* +0xDB50 -> +0xCDFE */
    u8 seg_DB54_DB58[0x4];
    const u16 *pDB58; /* +0xDB58 -> +0xCDD8 */
    u8 seg_DB5C_DB60[0x4];
    const u16 *pDB60; /* +0xDB60 -> +0xCDB2 */
    u8 seg_DB64_DB68[0x4];
    const u16 *pDB68; /* +0xDB68 -> +0xCD92 */
    u8 seg_DB6C_DB70[0x4];
    const u16 *pDB70; /* +0xDB70 -> +0xCD72 */
    u8 seg_DB74_DB78[0x4];
    const u16 *pDB78; /* +0xDB78 -> +0xCD4C */
    u8 seg_DB7C_DB80[0x4];
    const u16 *pDB80; /* +0xDB80 -> +0xCD26 */
    u8 seg_DB84_DB88[0x4];
    const u16 *pDB88; /* +0xDB88 -> +0xCD00 */
    u8 seg_DB8C_DB90[0x4];
    const u16 *pDB90; /* +0xDB90 -> +0xCCDA */
    u8 seg_DB94_DB98[0x4];
    const u16 *pDB98; /* +0xDB98 -> +0xCCB4 */
    u8 seg_DB9C_DBA0[0x4];
    const u16 *pDBA0; /* +0xDBA0 -> +0xCC94 */
    u8 seg_DBA4_DBA8[0x4];
    const u16 *pDBA8; /* +0xDBA8 -> +0xCC74 */
    u8 seg_DBAC_DBB0[0x4];
    const u16 *pDBB0; /* +0xDBB0 -> +0xCC42 */
    u8 seg_DBB4_DBB8[0x4];
    const u16 *pDBB8; /* +0xDBB8 -> +0xCC10 */
    u8 seg_DBBC_DBC0[0x4];
    const u16 *pDBC0; /* +0xDBC0 -> +0xCBDE */
    u8 seg_DBC4_DBC8[0x4];
    const u16 *pDBC8; /* +0xDBC8 -> +0xCBAC */
    u8 seg_DBCC_DBD0[0x4];
    const u16 *pDBD0; /* +0xDBD0 -> +0xCB86 */
    u8 seg_DBD4_DBD8[0x4];
    const u16 *pDBD8; /* +0xDBD8 -> +0xCB5A */
    u8 seg_DBDC_DBE0[0x4];
    const u16 *pDBE0; /* +0xDBE0 -> +0xCB34 */
    u8 seg_DBE4_DBE8[0x4];
    const u16 *pDBE8; /* +0xDBE8 -> +0xCB0E */
    u8 seg_DBEC_DBF0[0x4];
    const u16 *pDBF0; /* +0xDBF0 -> +0xCAEE */
    u8 seg_DBF4_DBF8[0x4];
    const u16 *pDBF8; /* +0xDBF8 -> +0xCACE */
    u8 seg_DBFC_DC00[0x4];
    const u16 *pDC00; /* +0xDC00 -> +0xCAA2 */
    u8 seg_DC04_DC08[0x4];
    const u16 *pDC08; /* +0xDC08 -> +0xCA76 */
    u8 seg_DC0C_DC10[0x4];
    const u16 *pDC10; /* +0xDC10 -> +0xCA4A */
    u8 seg_DC14_DC18[0x4];
    const u16 *pDC18; /* +0xDC18 -> +0xCA1E */
    u8 seg_DC1C_DC20[0x4];
    const u16 *pDC20; /* +0xDC20 -> +0xC9F2 */
    u8 seg_DC24_DC28[0x4];
    const u16 *pDC28; /* +0xDC28 -> +0xC9CC */
    u8 seg_DC2C_DC30[0x4];
    const u16 *pDC30; /* +0xDC30 -> +0xC9A6 */
    u8 seg_DC34_DC38[0x4];
    const u16 *pDC38; /* +0xDC38 -> +0xC986 */
    u8 seg_DC3C_DC40[0x4];
    const u16 *pDC40; /* +0xDC40 -> +0xC966 */
    u8 seg_DC44_DC48[0x4];
    const u16 *pDC48; /* +0xDC48 -> +0xC93A */
    u8 seg_DC4C_DC50[0x4];
    const u16 *pDC50; /* +0xDC50 -> +0xC90E */
    u8 seg_DC54_DC60[0xC];
    const u16 *pDC60; /* +0xDC60 -> +0xBC10 */
    u8 seg_DC64_DC68[0x4];
    const u16 *pDC68; /* +0xDC68 -> +0xBC2A */
    u8 seg_DC6C_DC70[0x4];
    const u16 *pDC70; /* +0xDC70 -> +0xBC44 */
    u8 seg_DC74_DC78[0x4];
    const u16 *pDC78; /* +0xDC78 -> +0xBC5E */
    u8 seg_DC7C_DC80[0x4];
    const u16 *pDC80; /* +0xDC80 -> +0xBC78 */
    u8 seg_DC84_DC88[0x4];
    const u16 *pDC88; /* +0xDC88 -> +0xBC92 */
    u8 seg_DC8C_DC90[0x4];
    const u16 *pDC90; /* +0xDC90 -> +0xBCAC */
    u8 seg_DC94_DC98[0x4];
    const u16 *pDC98; /* +0xDC98 -> +0xBCC6 */
    u8 seg_DC9C_DCA0[0x4];
    const u16 *pDCA0; /* +0xDCA0 -> +0xBCE0 */
    u8 seg_DCA4_DCA8[0x4];
    const u16 *pDCA8; /* +0xDCA8 -> +0xBCFA */
    u8 seg_DCAC_DCB8[0xC];
    const u16 *pDCB8; /* +0xDCB8 -> +0xBD3C */
    u8 seg_DCBC_DCC0[0x4];
    const u16 *pDCC0; /* +0xDCC0 -> +0xBD34 */
    u8 seg_DCC4_DCC8[0x4];
    const u16 *pDCC8; /* +0xDCC8 -> +0xBD2C */
    u8 seg_DCCC_DCD0[0x4];
    const u16 *pDCD0; /* +0xDCD0 -> +0xBD24 */
    u8 seg_DCD4_DCD8[0x4];
    const u16 *pDCD8; /* +0xDCD8 -> +0xBD1C */
    u8 seg_DCDC_DCE0[0x4];
    const u16 *pDCE0; /* +0xDCE0 -> +0xBD14 */
    u8 seg_DCE4_DCE8[0x4];
    const u16 *pDCE8; /* +0xDCE8 -> +0xBD5C */
    u8 seg_DCEC_DCF0[0x4];
    const u16 *pDCF0; /* +0xDCF0 -> +0xBD54 */
    u8 seg_DCF4_DCF8[0x4];
    const u16 *pDCF8; /* +0xDCF8 -> +0xBD4C */
    u8 seg_DCFC_DD00[0x4];
    const u16 *pDD00; /* +0xDD00 -> +0xBD44 */
    u8 seg_DD04_DD10[0xC];
    const u16 *pDD10; /* +0xDD10 -> +0xBD5C */
    u8 seg_DD14_DD18[0x4];
    const u16 *pDD18; /* +0xDD18 -> +0xBD54 */
    u8 seg_DD1C_DD20[0x4];
    const u16 *pDD20; /* +0xDD20 -> +0xBD4C */
    u8 seg_DD24_DD28[0x4];
    const u16 *pDD28; /* +0xDD28 -> +0xBD44 */
    u8 seg_DD2C_DD30[0x4];
    const u16 *pDD30; /* +0xDD30 -> +0xBD3C */
    u8 seg_DD34_DD38[0x4];
    const u16 *pDD38; /* +0xDD38 -> +0xBD34 */
    u8 seg_DD3C_DD40[0x4];
    const u16 *pDD40; /* +0xDD40 -> +0xBD2C */
    u8 seg_DD44_DD48[0x4];
    const u16 *pDD48; /* +0xDD48 -> +0xBD24 */
    u8 seg_DD4C_DD50[0x4];
    const u16 *pDD50; /* +0xDD50 -> +0xBD1C */
    u8 seg_DD54_DD58[0x4];
    const u16 *pDD58; /* +0xDD58 -> +0xBD14 */
    u8 seg_DD5C_DD68[0xC];
    const u16 *pDD68; /* +0xDD68 -> +0xBD44 */
    u8 seg_DD6C_DD70[0x4];
    const u16 *pDD70; /* +0xDD70 -> +0xBD3C */
    u8 seg_DD74_DD78[0x4];
    const u16 *pDD78; /* +0xDD78 -> +0xBD34 */
    u8 seg_DD7C_DD80[0x4];
    const u16 *pDD80; /* +0xDD80 -> +0xBD2C */
    u8 seg_DD84_DD88[0x4];
    const u16 *pDD88; /* +0xDD88 -> +0xBD24 */
    u8 seg_DD8C_DD90[0x4];
    const u16 *pDD90; /* +0xDD90 -> +0xBD1C */
    u8 seg_DD94_DD98[0x4];
    const u16 *pDD98; /* +0xDD98 -> +0xBD14 */
    u8 seg_DD9C_DDA0[0x4];
    const u16 *pDDA0; /* +0xDDA0 -> +0xBD5C */
    u8 seg_DDA4_DDA8[0x4];
    const u16 *pDDA8; /* +0xDDA8 -> +0xBD54 */
    u8 seg_DDAC_DDB0[0x4];
    const u16 *pDDB0; /* +0xDDB0 -> +0xBD4C */
    u8 seg_DDB4_DDC0[0xC];
    const u16 *pDDC0; /* +0xDDC0 -> +0xBD34 */
    u8 seg_DDC4_DDC8[0x4];
    const u16 *pDDC8; /* +0xDDC8 -> +0xBD34 */
    u8 seg_DDCC_DDD0[0x4];
    const u16 *pDDD0; /* +0xDDD0 -> +0xBD34 */
    u8 seg_DDD4_DDD8[0x4];
    const u16 *pDDD8; /* +0xDDD8 -> +0xBD2C */
    u8 seg_DDDC_DDE0[0x4];
    const u16 *pDDE0; /* +0xDDE0 -> +0xBD2C */
    u8 seg_DDE4_DDE8[0x4];
    const u16 *pDDE8; /* +0xDDE8 -> +0xBD2C */
    u8 seg_DDEC_14394[0x65A8];
} __attribute__((packed));

static const struct NewFileIntroGfxBlob sBlob_64e470_662804 = {
    .seg_0000_D6C8 = INCBIN_U8("data/Blob_64e470_seg_0000_D6C8.bin"),
    .pD6C8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D6CC_D6D0 = INCBIN_U8("data/Blob_64e470_seg_D6CC_D6D0.bin"),
    .pD6D0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD64),
    .seg_D6D4_D6D8 = INCBIN_U8("data/Blob_64e470_seg_D6D4_D6D8.bin"),
    .pD6D8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD78),
    .seg_D6DC_D6E0 = INCBIN_U8("data/Blob_64e470_seg_D6DC_D6E0.bin"),
    .pD6E0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD92),
    .seg_D6E4_D6E8 = INCBIN_U8("data/Blob_64e470_seg_D6E4_D6E8.bin"),
    .pD6E8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBDAC),
    .seg_D6EC_D6F0 = INCBIN_U8("data/Blob_64e470_seg_D6EC_D6F0.bin"),
    .pD6F0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBDCC),
    .seg_D6F4_D6F8 = INCBIN_U8("data/Blob_64e470_seg_D6F4_D6F8.bin"),
    .pD6F8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBDEC),
    .seg_D6FC_D700 = INCBIN_U8("data/Blob_64e470_seg_D6FC_D700.bin"),
    .pD700 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBE0C),
    .seg_D704_D708 = INCBIN_U8("data/Blob_64e470_seg_D704_D708.bin"),
    .pD708 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBE2C),
    .seg_D70C_D710 = INCBIN_U8("data/Blob_64e470_seg_D70C_D710.bin"),
    .pD710 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBE4C),
    .seg_D714_D718 = INCBIN_U8("data/Blob_64e470_seg_D714_D718.bin"),
    .pD718 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBE6C),
    .seg_D71C_D720 = INCBIN_U8("data/Blob_64e470_seg_D71C_D720.bin"),
    .pD720 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBE8C),
    .seg_D724_D728 = INCBIN_U8("data/Blob_64e470_seg_D724_D728.bin"),
    .pD728 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBEB8),
    .seg_D72C_D730 = INCBIN_U8("data/Blob_64e470_seg_D72C_D730.bin"),
    .pD730 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBEE4),
    .seg_D734_D738 = INCBIN_U8("data/Blob_64e470_seg_D734_D738.bin"),
    .pD738 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBF10),
    .seg_D73C_D740 = INCBIN_U8("data/Blob_64e470_seg_D73C_D740.bin"),
    .pD740 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBF3C),
    .seg_D744_D748 = INCBIN_U8("data/Blob_64e470_seg_D744_D748.bin"),
    .pD748 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBF68),
    .seg_D74C_D750 = INCBIN_U8("data/Blob_64e470_seg_D74C_D750.bin"),
    .pD750 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBF94),
    .seg_D754_D758 = INCBIN_U8("data/Blob_64e470_seg_D754_D758.bin"),
    .pD758 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBFC0),
    .seg_D75C_D760 = INCBIN_U8("data/Blob_64e470_seg_D75C_D760.bin"),
    .pD760 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBFF2),
    .seg_D764_D768 = INCBIN_U8("data/Blob_64e470_seg_D764_D768.bin"),
    .pD768 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC02A),
    .seg_D76C_D770 = INCBIN_U8("data/Blob_64e470_seg_D76C_D770.bin"),
    .pD770 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC062),
    .seg_D774_D778 = INCBIN_U8("data/Blob_64e470_seg_D774_D778.bin"),
    .pD778 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC09A),
    .seg_D77C_D780 = INCBIN_U8("data/Blob_64e470_seg_D77C_D780.bin"),
    .pD780 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC0D2),
    .seg_D784_D788 = INCBIN_U8("data/Blob_64e470_seg_D784_D788.bin"),
    .pD788 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC10A),
    .seg_D78C_D790 = INCBIN_U8("data/Blob_64e470_seg_D78C_D790.bin"),
    .pD790 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC142),
    .seg_D794_D798 = INCBIN_U8("data/Blob_64e470_seg_D794_D798.bin"),
    .pD798 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC180),
    .seg_D79C_D7A0 = INCBIN_U8("data/Blob_64e470_seg_D79C_D7A0.bin"),
    .pD7A0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC1C4),
    .seg_D7A4_D7A8 = INCBIN_U8("data/Blob_64e470_seg_D7A4_D7A8.bin"),
    .pD7A8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC208),
    .seg_D7AC_D7B0 = INCBIN_U8("data/Blob_64e470_seg_D7AC_D7B0.bin"),
    .pD7B0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC24C),
    .seg_D7B4_D7B8 = INCBIN_U8("data/Blob_64e470_seg_D7B4_D7B8.bin"),
    .pD7B8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC290),
    .seg_D7BC_D7C0 = INCBIN_U8("data/Blob_64e470_seg_D7BC_D7C0.bin"),
    .pD7C0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC2D4),
    .seg_D7C4_D7C8 = INCBIN_U8("data/Blob_64e470_seg_D7C4_D7C8.bin"),
    .pD7C8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC318),
    .seg_D7CC_D7D0 = INCBIN_U8("data/Blob_64e470_seg_D7CC_D7D0.bin"),
    .pD7D0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC35C),
    .seg_D7D4_D7D8 = INCBIN_U8("data/Blob_64e470_seg_D7D4_D7D8.bin"),
    .pD7D8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC3A6),
    .seg_D7DC_D7E0 = INCBIN_U8("data/Blob_64e470_seg_D7DC_D7E0.bin"),
    .pD7E0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC3F6),
    .seg_D7E4_D7E8 = INCBIN_U8("data/Blob_64e470_seg_D7E4_D7E8.bin"),
    .pD7E8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC446),
    .seg_D7EC_D7F0 = INCBIN_U8("data/Blob_64e470_seg_D7EC_D7F0.bin"),
    .pD7F0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC496),
    .seg_D7F4_D7F8 = INCBIN_U8("data/Blob_64e470_seg_D7F4_D7F8.bin"),
    .pD7F8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC4E6),
    .seg_D7FC_D800 = INCBIN_U8("data/Blob_64e470_seg_D7FC_D800.bin"),
    .pD800 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D804_D808 = INCBIN_U8("data/Blob_64e470_seg_D804_D808.bin"),
    .pD808 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC4E6),
    .seg_D80C_D810 = INCBIN_U8("data/Blob_64e470_seg_D80C_D810.bin"),
    .pD810 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D814_D818 = INCBIN_U8("data/Blob_64e470_seg_D814_D818.bin"),
    .pD818 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC4E6),
    .seg_D81C_D820 = INCBIN_U8("data/Blob_64e470_seg_D81C_D820.bin"),
    .pD820 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D824_D828 = INCBIN_U8("data/Blob_64e470_seg_D824_D828.bin"),
    .pD828 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC536),
    .seg_D82C_D830 = INCBIN_U8("data/Blob_64e470_seg_D82C_D830.bin"),
    .pD830 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC58C),
    .seg_D834_D838 = INCBIN_U8("data/Blob_64e470_seg_D834_D838.bin"),
    .pD838 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC5E8),
    .seg_D83C_D840 = INCBIN_U8("data/Blob_64e470_seg_D83C_D840.bin"),
    .pD840 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC64A),
    .seg_D844_D848 = INCBIN_U8("data/Blob_64e470_seg_D844_D848.bin"),
    .pD848 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC6B2),
    .seg_D84C_D850 = INCBIN_U8("data/Blob_64e470_seg_D84C_D850.bin"),
    .pD850 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC720),
    .seg_D854_D858 = INCBIN_U8("data/Blob_64e470_seg_D854_D858.bin"),
    .pD858 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC782),
    .seg_D85C_D860 = INCBIN_U8("data/Blob_64e470_seg_D85C_D860.bin"),
    .pD860 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC7F0),
    .seg_D864_D868 = INCBIN_U8("data/Blob_64e470_seg_D864_D868.bin"),
    .pD868 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC876),
    .seg_D86C_D870 = INCBIN_U8("data/Blob_64e470_seg_D86C_D870.bin"),
    .pD870 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC876),
    .seg_D874_D878 = INCBIN_U8("data/Blob_64e470_seg_D874_D878.bin"),
    .pD878 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC876),
    .seg_D87C_D880 = INCBIN_U8("data/Blob_64e470_seg_D87C_D880.bin"),
    .pD880 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC876),
    .seg_D884_D890 = INCBIN_U8("data/Blob_64e470_seg_D884_D890.bin"),
    .pD890 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB780),
    .seg_D894_D898 = INCBIN_U8("data/Blob_64e470_seg_D894_D898.bin"),
    .pD898 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB7C4),
    .seg_D89C_D8A0 = INCBIN_U8("data/Blob_64e470_seg_D89C_D8A0.bin"),
    .pD8A0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB802),
    .seg_D8A4_D8A8 = INCBIN_U8("data/Blob_64e470_seg_D8A4_D8A8.bin"),
    .pD8A8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB846),
    .seg_D8AC_D8B0 = INCBIN_U8("data/Blob_64e470_seg_D8AC_D8B0.bin"),
    .pD8B0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB88A),
    .seg_D8B4_D8B8 = INCBIN_U8("data/Blob_64e470_seg_D8B4_D8B8.bin"),
    .pD8B8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB8C8),
    .seg_D8BC_D8C0 = INCBIN_U8("data/Blob_64e470_seg_D8BC_D8C0.bin"),
    .pD8C0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB906),
    .seg_D8C4_D8C8 = INCBIN_U8("data/Blob_64e470_seg_D8C4_D8C8.bin"),
    .pD8C8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB938),
    .seg_D8CC_D8D8 = INCBIN_U8("data/Blob_64e470_seg_D8CC_D8D8.bin"),
    .pD8D8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB734),
    .seg_D8DC_D8E0 = INCBIN_U8("data/Blob_64e470_seg_D8DC_D8E0.bin"),
    .pD8E0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB760),
    .seg_D8E4_D8F0 = INCBIN_U8("data/Blob_64e470_seg_D8E4_D8F0.bin"),
    .pD8F0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D8F4_D8F8 = INCBIN_U8("data/Blob_64e470_seg_D8F4_D8F8.bin"),
    .pD8F8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB970),
    .seg_D8FC_D900 = INCBIN_U8("data/Blob_64e470_seg_D8FC_D900.bin"),
    .pD900 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB978),
    .seg_D904_D908 = INCBIN_U8("data/Blob_64e470_seg_D904_D908.bin"),
    .pD908 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB980),
    .seg_D90C_D910 = INCBIN_U8("data/Blob_64e470_seg_D90C_D910.bin"),
    .pD910 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB988),
    .seg_D914_D918 = INCBIN_U8("data/Blob_64e470_seg_D914_D918.bin"),
    .pD918 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB990),
    .seg_D91C_D920 = INCBIN_U8("data/Blob_64e470_seg_D91C_D920.bin"),
    .pD920 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB998),
    .seg_D924_D928 = INCBIN_U8("data/Blob_64e470_seg_D924_D928.bin"),
    .pD928 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB9A0),
    .seg_D92C_D930 = INCBIN_U8("data/Blob_64e470_seg_D92C_D930.bin"),
    .pD930 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB9A8),
    .seg_D934_D938 = INCBIN_U8("data/Blob_64e470_seg_D934_D938.bin"),
    .pD938 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB9C2),
    .seg_D93C_D940 = INCBIN_U8("data/Blob_64e470_seg_D93C_D940.bin"),
    .pD940 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xB9EE),
    .seg_D944_D948 = INCBIN_U8("data/Blob_64e470_seg_D944_D948.bin"),
    .pD948 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBA20),
    .seg_D94C_D950 = INCBIN_U8("data/Blob_64e470_seg_D94C_D950.bin"),
    .pD950 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBA58),
    .seg_D954_D958 = INCBIN_U8("data/Blob_64e470_seg_D954_D958.bin"),
    .pD958 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBAAE),
    .seg_D95C_D960 = INCBIN_U8("data/Blob_64e470_seg_D95C_D960.bin"),
    .pD960 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBB16),
    .seg_D964_D968 = INCBIN_U8("data/Blob_64e470_seg_D964_D968.bin"),
    .pD968 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBB84),
    .seg_D96C_D970 = INCBIN_U8("data/Blob_64e470_seg_D96C_D970.bin"),
    .pD970 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBB84),
    .seg_D974_D978 = INCBIN_U8("data/Blob_64e470_seg_D974_D978.bin"),
    .pD978 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBB84),
    .seg_D97C_D980 = INCBIN_U8("data/Blob_64e470_seg_D97C_D980.bin"),
    .pD980 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBB84),
    .seg_D984_D990 = INCBIN_U8("data/Blob_64e470_seg_D984_D990.bin"),
    .pD990 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD6BE),
    .seg_D994_D998 = INCBIN_U8("data/Blob_64e470_seg_D994_D998.bin"),
    .pD998 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD69E),
    .seg_D99C_D9A0 = INCBIN_U8("data/Blob_64e470_seg_D99C_D9A0.bin"),
    .pD9A0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD67E),
    .seg_D9A4_D9A8 = INCBIN_U8("data/Blob_64e470_seg_D9A4_D9A8.bin"),
    .pD9A8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD658),
    .seg_D9AC_D9B0 = INCBIN_U8("data/Blob_64e470_seg_D9AC_D9B0.bin"),
    .pD9B0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD638),
    .seg_D9B4_D9B8 = INCBIN_U8("data/Blob_64e470_seg_D9B4_D9B8.bin"),
    .pD9B8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD618),
    .seg_D9BC_D9C0 = INCBIN_U8("data/Blob_64e470_seg_D9BC_D9C0.bin"),
    .pD9C0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD5EC),
    .seg_D9C4_D9C8 = INCBIN_U8("data/Blob_64e470_seg_D9C4_D9C8.bin"),
    .pD9C8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD5C0),
    .seg_D9CC_D9D0 = INCBIN_U8("data/Blob_64e470_seg_D9CC_D9D0.bin"),
    .pD9D0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD594),
    .seg_D9D4_D9D8 = INCBIN_U8("data/Blob_64e470_seg_D9D4_D9D8.bin"),
    .pD9D8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD568),
    .seg_D9DC_D9E0 = INCBIN_U8("data/Blob_64e470_seg_D9DC_D9E0.bin"),
    .pD9E0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD53C),
    .seg_D9E4_D9E8 = INCBIN_U8("data/Blob_64e470_seg_D9E4_D9E8.bin"),
    .pD9E8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD516),
    .seg_D9EC_D9F0 = INCBIN_U8("data/Blob_64e470_seg_D9EC_D9F0.bin"),
    .pD9F0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD4F0),
    .seg_D9F4_D9F8 = INCBIN_U8("data/Blob_64e470_seg_D9F4_D9F8.bin"),
    .pD9F8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD4C4),
    .seg_D9FC_DA00 = INCBIN_U8("data/Blob_64e470_seg_D9FC_DA00.bin"),
    .pDA00 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD498),
    .seg_DA04_DA08 = INCBIN_U8("data/Blob_64e470_seg_DA04_DA08.bin"),
    .pDA08 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD46C),
    .seg_DA0C_DA10 = INCBIN_U8("data/Blob_64e470_seg_DA0C_DA10.bin"),
    .pDA10 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD440),
    .seg_DA14_DA18 = INCBIN_U8("data/Blob_64e470_seg_DA14_DA18.bin"),
    .pDA18 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD414),
    .seg_DA1C_DA20 = INCBIN_U8("data/Blob_64e470_seg_DA1C_DA20.bin"),
    .pDA20 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD3EE),
    .seg_DA24_DA28 = INCBIN_U8("data/Blob_64e470_seg_DA24_DA28.bin"),
    .pDA28 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD3C2),
    .seg_DA2C_DA30 = INCBIN_U8("data/Blob_64e470_seg_DA2C_DA30.bin"),
    .pDA30 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD39C),
    .seg_DA34_DA38 = INCBIN_U8("data/Blob_64e470_seg_DA34_DA38.bin"),
    .pDA38 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD37C),
    .seg_DA3C_DA40 = INCBIN_U8("data/Blob_64e470_seg_DA3C_DA40.bin"),
    .pDA40 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD350),
    .seg_DA44_DA48 = INCBIN_U8("data/Blob_64e470_seg_DA44_DA48.bin"),
    .pDA48 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD324),
    .seg_DA4C_DA50 = INCBIN_U8("data/Blob_64e470_seg_DA4C_DA50.bin"),
    .pDA50 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD2F8),
    .seg_DA54_DA58 = INCBIN_U8("data/Blob_64e470_seg_DA54_DA58.bin"),
    .pDA58 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD2CC),
    .seg_DA5C_DA60 = INCBIN_U8("data/Blob_64e470_seg_DA5C_DA60.bin"),
    .pDA60 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD2A0),
    .seg_DA64_DA68 = INCBIN_U8("data/Blob_64e470_seg_DA64_DA68.bin"),
    .pDA68 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD27A),
    .seg_DA6C_DA70 = INCBIN_U8("data/Blob_64e470_seg_DA6C_DA70.bin"),
    .pDA70 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD254),
    .seg_DA74_DA78 = INCBIN_U8("data/Blob_64e470_seg_DA74_DA78.bin"),
    .pDA78 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD234),
    .seg_DA7C_DA80 = INCBIN_U8("data/Blob_64e470_seg_DA7C_DA80.bin"),
    .pDA80 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD214),
    .seg_DA84_DA88 = INCBIN_U8("data/Blob_64e470_seg_DA84_DA88.bin"),
    .pDA88 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD1E8),
    .seg_DA8C_DA90 = INCBIN_U8("data/Blob_64e470_seg_DA8C_DA90.bin"),
    .pDA90 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD1BC),
    .seg_DA94_DAA0 = INCBIN_U8("data/Blob_64e470_seg_DA94_DAA0.bin"),
    .pDAA0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD190),
    .seg_DAA4_DAA8 = INCBIN_U8("data/Blob_64e470_seg_DAA4_DAA8.bin"),
    .pDAA8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD164),
    .seg_DAAC_DAB0 = INCBIN_U8("data/Blob_64e470_seg_DAAC_DAB0.bin"),
    .pDAB0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD138),
    .seg_DAB4_DAB8 = INCBIN_U8("data/Blob_64e470_seg_DAB4_DAB8.bin"),
    .pDAB8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD10C),
    .seg_DABC_DAC0 = INCBIN_U8("data/Blob_64e470_seg_DABC_DAC0.bin"),
    .pDAC0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD0E6),
    .seg_DAC4_DAC8 = INCBIN_U8("data/Blob_64e470_seg_DAC4_DAC8.bin"),
    .pDAC8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD0C0),
    .seg_DACC_DAD0 = INCBIN_U8("data/Blob_64e470_seg_DACC_DAD0.bin"),
    .pDAD0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD0A0),
    .seg_DAD4_DAD8 = INCBIN_U8("data/Blob_64e470_seg_DAD4_DAD8.bin"),
    .pDAD8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD080),
    .seg_DADC_DAE0 = INCBIN_U8("data/Blob_64e470_seg_DADC_DAE0.bin"),
    .pDAE0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD04E),
    .seg_DAE4_DAE8 = INCBIN_U8("data/Blob_64e470_seg_DAE4_DAE8.bin"),
    .pDAE8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xD01C),
    .seg_DAEC_DAF0 = INCBIN_U8("data/Blob_64e470_seg_DAEC_DAF0.bin"),
    .pDAF0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCFEA),
    .seg_DAF4_DAF8 = INCBIN_U8("data/Blob_64e470_seg_DAF4_DAF8.bin"),
    .pDAF8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCFB8),
    .seg_DAFC_DB00 = INCBIN_U8("data/Blob_64e470_seg_DAFC_DB00.bin"),
    .pDB00 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCF92),
    .seg_DB04_DB08 = INCBIN_U8("data/Blob_64e470_seg_DB04_DB08.bin"),
    .pDB08 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCF66),
    .seg_DB0C_DB10 = INCBIN_U8("data/Blob_64e470_seg_DB0C_DB10.bin"),
    .pDB10 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCF40),
    .seg_DB14_DB18 = INCBIN_U8("data/Blob_64e470_seg_DB14_DB18.bin"),
    .pDB18 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCF1A),
    .seg_DB1C_DB20 = INCBIN_U8("data/Blob_64e470_seg_DB1C_DB20.bin"),
    .pDB20 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCEFA),
    .seg_DB24_DB28 = INCBIN_U8("data/Blob_64e470_seg_DB24_DB28.bin"),
    .pDB28 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCEDA),
    .seg_DB2C_DB30 = INCBIN_U8("data/Blob_64e470_seg_DB2C_DB30.bin"),
    .pDB30 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCEAE),
    .seg_DB34_DB38 = INCBIN_U8("data/Blob_64e470_seg_DB34_DB38.bin"),
    .pDB38 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCE82),
    .seg_DB3C_DB40 = INCBIN_U8("data/Blob_64e470_seg_DB3C_DB40.bin"),
    .pDB40 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCE56),
    .seg_DB44_DB48 = INCBIN_U8("data/Blob_64e470_seg_DB44_DB48.bin"),
    .pDB48 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCE2A),
    .seg_DB4C_DB50 = INCBIN_U8("data/Blob_64e470_seg_DB4C_DB50.bin"),
    .pDB50 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCDFE),
    .seg_DB54_DB58 = INCBIN_U8("data/Blob_64e470_seg_DB54_DB58.bin"),
    .pDB58 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCDD8),
    .seg_DB5C_DB60 = INCBIN_U8("data/Blob_64e470_seg_DB5C_DB60.bin"),
    .pDB60 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCDB2),
    .seg_DB64_DB68 = INCBIN_U8("data/Blob_64e470_seg_DB64_DB68.bin"),
    .pDB68 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCD92),
    .seg_DB6C_DB70 = INCBIN_U8("data/Blob_64e470_seg_DB6C_DB70.bin"),
    .pDB70 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCD72),
    .seg_DB74_DB78 = INCBIN_U8("data/Blob_64e470_seg_DB74_DB78.bin"),
    .pDB78 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCD4C),
    .seg_DB7C_DB80 = INCBIN_U8("data/Blob_64e470_seg_DB7C_DB80.bin"),
    .pDB80 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCD26),
    .seg_DB84_DB88 = INCBIN_U8("data/Blob_64e470_seg_DB84_DB88.bin"),
    .pDB88 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCD00),
    .seg_DB8C_DB90 = INCBIN_U8("data/Blob_64e470_seg_DB8C_DB90.bin"),
    .pDB90 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCCDA),
    .seg_DB94_DB98 = INCBIN_U8("data/Blob_64e470_seg_DB94_DB98.bin"),
    .pDB98 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCCB4),
    .seg_DB9C_DBA0 = INCBIN_U8("data/Blob_64e470_seg_DB9C_DBA0.bin"),
    .pDBA0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCC94),
    .seg_DBA4_DBA8 = INCBIN_U8("data/Blob_64e470_seg_DBA4_DBA8.bin"),
    .pDBA8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCC74),
    .seg_DBAC_DBB0 = INCBIN_U8("data/Blob_64e470_seg_DBAC_DBB0.bin"),
    .pDBB0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCC42),
    .seg_DBB4_DBB8 = INCBIN_U8("data/Blob_64e470_seg_DBB4_DBB8.bin"),
    .pDBB8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCC10),
    .seg_DBBC_DBC0 = INCBIN_U8("data/Blob_64e470_seg_DBBC_DBC0.bin"),
    .pDBC0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCBDE),
    .seg_DBC4_DBC8 = INCBIN_U8("data/Blob_64e470_seg_DBC4_DBC8.bin"),
    .pDBC8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCBAC),
    .seg_DBCC_DBD0 = INCBIN_U8("data/Blob_64e470_seg_DBCC_DBD0.bin"),
    .pDBD0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCB86),
    .seg_DBD4_DBD8 = INCBIN_U8("data/Blob_64e470_seg_DBD4_DBD8.bin"),
    .pDBD8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCB5A),
    .seg_DBDC_DBE0 = INCBIN_U8("data/Blob_64e470_seg_DBDC_DBE0.bin"),
    .pDBE0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCB34),
    .seg_DBE4_DBE8 = INCBIN_U8("data/Blob_64e470_seg_DBE4_DBE8.bin"),
    .pDBE8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCB0E),
    .seg_DBEC_DBF0 = INCBIN_U8("data/Blob_64e470_seg_DBEC_DBF0.bin"),
    .pDBF0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCAEE),
    .seg_DBF4_DBF8 = INCBIN_U8("data/Blob_64e470_seg_DBF4_DBF8.bin"),
    .pDBF8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCACE),
    .seg_DBFC_DC00 = INCBIN_U8("data/Blob_64e470_seg_DBFC_DC00.bin"),
    .pDC00 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCAA2),
    .seg_DC04_DC08 = INCBIN_U8("data/Blob_64e470_seg_DC04_DC08.bin"),
    .pDC08 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCA76),
    .seg_DC0C_DC10 = INCBIN_U8("data/Blob_64e470_seg_DC0C_DC10.bin"),
    .pDC10 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCA4A),
    .seg_DC14_DC18 = INCBIN_U8("data/Blob_64e470_seg_DC14_DC18.bin"),
    .pDC18 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xCA1E),
    .seg_DC1C_DC20 = INCBIN_U8("data/Blob_64e470_seg_DC1C_DC20.bin"),
    .pDC20 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC9F2),
    .seg_DC24_DC28 = INCBIN_U8("data/Blob_64e470_seg_DC24_DC28.bin"),
    .pDC28 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC9CC),
    .seg_DC2C_DC30 = INCBIN_U8("data/Blob_64e470_seg_DC2C_DC30.bin"),
    .pDC30 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC9A6),
    .seg_DC34_DC38 = INCBIN_U8("data/Blob_64e470_seg_DC34_DC38.bin"),
    .pDC38 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC986),
    .seg_DC3C_DC40 = INCBIN_U8("data/Blob_64e470_seg_DC3C_DC40.bin"),
    .pDC40 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC966),
    .seg_DC44_DC48 = INCBIN_U8("data/Blob_64e470_seg_DC44_DC48.bin"),
    .pDC48 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC93A),
    .seg_DC4C_DC50 = INCBIN_U8("data/Blob_64e470_seg_DC4C_DC50.bin"),
    .pDC50 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xC90E),
    .seg_DC54_DC60 = INCBIN_U8("data/Blob_64e470_seg_DC54_DC60.bin"),
    .pDC60 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC10),
    .seg_DC64_DC68 = INCBIN_U8("data/Blob_64e470_seg_DC64_DC68.bin"),
    .pDC68 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC2A),
    .seg_DC6C_DC70 = INCBIN_U8("data/Blob_64e470_seg_DC6C_DC70.bin"),
    .pDC70 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC44),
    .seg_DC74_DC78 = INCBIN_U8("data/Blob_64e470_seg_DC74_DC78.bin"),
    .pDC78 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC5E),
    .seg_DC7C_DC80 = INCBIN_U8("data/Blob_64e470_seg_DC7C_DC80.bin"),
    .pDC80 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC78),
    .seg_DC84_DC88 = INCBIN_U8("data/Blob_64e470_seg_DC84_DC88.bin"),
    .pDC88 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBC92),
    .seg_DC8C_DC90 = INCBIN_U8("data/Blob_64e470_seg_DC8C_DC90.bin"),
    .pDC90 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBCAC),
    .seg_DC94_DC98 = INCBIN_U8("data/Blob_64e470_seg_DC94_DC98.bin"),
    .pDC98 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBCC6),
    .seg_DC9C_DCA0 = INCBIN_U8("data/Blob_64e470_seg_DC9C_DCA0.bin"),
    .pDCA0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBCE0),
    .seg_DCA4_DCA8 = INCBIN_U8("data/Blob_64e470_seg_DCA4_DCA8.bin"),
    .pDCA8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBCFA),
    .seg_DCAC_DCB8 = INCBIN_U8("data/Blob_64e470_seg_DCAC_DCB8.bin"),
    .pDCB8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD3C),
    .seg_DCBC_DCC0 = INCBIN_U8("data/Blob_64e470_seg_DCBC_DCC0.bin"),
    .pDCC0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DCC4_DCC8 = INCBIN_U8("data/Blob_64e470_seg_DCC4_DCC8.bin"),
    .pDCC8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DCCC_DCD0 = INCBIN_U8("data/Blob_64e470_seg_DCCC_DCD0.bin"),
    .pDCD0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD24),
    .seg_DCD4_DCD8 = INCBIN_U8("data/Blob_64e470_seg_DCD4_DCD8.bin"),
    .pDCD8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD1C),
    .seg_DCDC_DCE0 = INCBIN_U8("data/Blob_64e470_seg_DCDC_DCE0.bin"),
    .pDCE0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD14),
    .seg_DCE4_DCE8 = INCBIN_U8("data/Blob_64e470_seg_DCE4_DCE8.bin"),
    .pDCE8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD5C),
    .seg_DCEC_DCF0 = INCBIN_U8("data/Blob_64e470_seg_DCEC_DCF0.bin"),
    .pDCF0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD54),
    .seg_DCF4_DCF8 = INCBIN_U8("data/Blob_64e470_seg_DCF4_DCF8.bin"),
    .pDCF8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD4C),
    .seg_DCFC_DD00 = INCBIN_U8("data/Blob_64e470_seg_DCFC_DD00.bin"),
    .pDD00 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD44),
    .seg_DD04_DD10 = INCBIN_U8("data/Blob_64e470_seg_DD04_DD10.bin"),
    .pDD10 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD5C),
    .seg_DD14_DD18 = INCBIN_U8("data/Blob_64e470_seg_DD14_DD18.bin"),
    .pDD18 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD54),
    .seg_DD1C_DD20 = INCBIN_U8("data/Blob_64e470_seg_DD1C_DD20.bin"),
    .pDD20 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD4C),
    .seg_DD24_DD28 = INCBIN_U8("data/Blob_64e470_seg_DD24_DD28.bin"),
    .pDD28 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD44),
    .seg_DD2C_DD30 = INCBIN_U8("data/Blob_64e470_seg_DD2C_DD30.bin"),
    .pDD30 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD3C),
    .seg_DD34_DD38 = INCBIN_U8("data/Blob_64e470_seg_DD34_DD38.bin"),
    .pDD38 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DD3C_DD40 = INCBIN_U8("data/Blob_64e470_seg_DD3C_DD40.bin"),
    .pDD40 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DD44_DD48 = INCBIN_U8("data/Blob_64e470_seg_DD44_DD48.bin"),
    .pDD48 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD24),
    .seg_DD4C_DD50 = INCBIN_U8("data/Blob_64e470_seg_DD4C_DD50.bin"),
    .pDD50 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD1C),
    .seg_DD54_DD58 = INCBIN_U8("data/Blob_64e470_seg_DD54_DD58.bin"),
    .pDD58 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD14),
    .seg_DD5C_DD68 = INCBIN_U8("data/Blob_64e470_seg_DD5C_DD68.bin"),
    .pDD68 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD44),
    .seg_DD6C_DD70 = INCBIN_U8("data/Blob_64e470_seg_DD6C_DD70.bin"),
    .pDD70 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD3C),
    .seg_DD74_DD78 = INCBIN_U8("data/Blob_64e470_seg_DD74_DD78.bin"),
    .pDD78 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DD7C_DD80 = INCBIN_U8("data/Blob_64e470_seg_DD7C_DD80.bin"),
    .pDD80 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DD84_DD88 = INCBIN_U8("data/Blob_64e470_seg_DD84_DD88.bin"),
    .pDD88 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD24),
    .seg_DD8C_DD90 = INCBIN_U8("data/Blob_64e470_seg_DD8C_DD90.bin"),
    .pDD90 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD1C),
    .seg_DD94_DD98 = INCBIN_U8("data/Blob_64e470_seg_DD94_DD98.bin"),
    .pDD98 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD14),
    .seg_DD9C_DDA0 = INCBIN_U8("data/Blob_64e470_seg_DD9C_DDA0.bin"),
    .pDDA0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD5C),
    .seg_DDA4_DDA8 = INCBIN_U8("data/Blob_64e470_seg_DDA4_DDA8.bin"),
    .pDDA8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD54),
    .seg_DDAC_DDB0 = INCBIN_U8("data/Blob_64e470_seg_DDAC_DDB0.bin"),
    .pDDB0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD4C),
    .seg_DDB4_DDC0 = INCBIN_U8("data/Blob_64e470_seg_DDB4_DDC0.bin"),
    .pDDC0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DDC4_DDC8 = INCBIN_U8("data/Blob_64e470_seg_DDC4_DDC8.bin"),
    .pDDC8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DDCC_DDD0 = INCBIN_U8("data/Blob_64e470_seg_DDCC_DDD0.bin"),
    .pDDD0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD34),
    .seg_DDD4_DDD8 = INCBIN_U8("data/Blob_64e470_seg_DDD4_DDD8.bin"),
    .pDDD8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DDDC_DDE0 = INCBIN_U8("data/Blob_64e470_seg_DDDC_DDE0.bin"),
    .pDDE0 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DDE4_DDE8 = INCBIN_U8("data/Blob_64e470_seg_DDE4_DDE8.bin"),
    .pDDE8 = (const u16*)((const u8*)&sBlob_64e470_662804 + 0xBD2C),
    .seg_DDEC_14394 = INCBIN_U8("data/Blob_64e470_seg_DDEC_14394.bin"),
};

const u32 sIntroTilemap_662804[318] = INCBIN_U32("data/new_file_intro/662804.tm.lz");

static const u8 sBlob_662cfc_663820[] = INCBIN_U8("data/Blob_662cfc_663820.bin");

const u16 sIntroPal_663820[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/663820.pal");

struct NewFileIntroDataBlob {
    u8 before0[0x530];
    const u8 *p0530;
    u8 gap0530[4];
    const u8 *p0538;
    u8 gap0538[4];
    const u8 *p0540;
    u8 gap0540[4];
    const u8 *p0548;
    u8 gap0548[4];
    u8 term0550[8];
    const u8 *p0558;
    u8 gap0558[4];
    u8 term0560[8];
    u8 before2[0x54];
    const u8 *p05BC;
    u8 gap05C0[4];
    const u8 *p05C4;
    u8 gap05C8[4];
    u8 term05CC[8];
    const u8 *p05D4;
    u8 gap05D8[4];
    const u8 *p05DC;
    u8 gap05E0[4];
    const u8 *p05E4;
    u8 gap05E8[4];
    const u8 *p05EC;
    u8 gap05F0[4];
    const u8 *p05F4;
    u8 gap05F8[4];
    const u8 *p05FC;
    u8 gap0600[4];
    u8 term0604[8];
    u8 beforeCutscene[0x159E0 - 0x060C];
    struct FrameData cutsceneFrameData[52]; /* +0x159E0..+0x15B80 */
    u8 after[0x1F70C - 0x15B80];
} __attribute__((packed));

static const struct NewFileIntroDataBlob sBlob_6638a0_682fac = {
    .before0 = INCBIN_U8("data/Blob_6638a0_before0.bin"),
    .p0530 = (const u8*)&sBlob_6638a0_682fac + 0x240,
    .gap0530 = INCBIN_U8("data/Blob_6638a0_gap_0530.bin"),
    .p0538 = (const u8*)&sBlob_6638a0_682fac + 0x392,
    .gap0538 = INCBIN_U8("data/Blob_6638a0_gap_0538.bin"),
    .p0540 = (const u8*)&sBlob_6638a0_682fac + 0x240,
    .gap0540 = INCBIN_U8("data/Blob_6638a0_gap_0540.bin"),
    .p0548 = (const u8*)&sBlob_6638a0_682fac + 0x392,
    .gap0548 = INCBIN_U8("data/Blob_6638a0_gap_0548.bin"),
    .term0550 = INCBIN_U8("data/Blob_6638a0_term_0550.bin"),
    .p0558 = (const u8*)&sBlob_6638a0_682fac + 0x4E4,
    .gap0558 = INCBIN_U8("data/Blob_6638a0_gap_0558.bin"),
    .term0560 = INCBIN_U8("data/Blob_6638a0_term_0560.bin"),
    .before2 = INCBIN_U8("data/Blob_6638a0_before2.bin"),
    .p05BC = (const u8*)&sBlob_6638a0_682fac + 0x568,
    .gap05C0 = INCBIN_U8("data/Blob_6638a0_gap_05C0.bin"),
    .p05C4 = (const u8*)&sBlob_6638a0_682fac + 0x576,
    .gap05C8 = INCBIN_U8("data/Blob_6638a0_gap_05C8.bin"),
    .term05CC = INCBIN_U8("data/Blob_6638a0_term_05CC.bin"),
    .p05D4 = (const u8*)&sBlob_6638a0_682fac + 0x584,
    .gap05D8 = INCBIN_U8("data/Blob_6638a0_gap_05D8.bin"),
    .p05DC = (const u8*)&sBlob_6638a0_682fac + 0x592,
    .gap05E0 = INCBIN_U8("data/Blob_6638a0_gap_05E0.bin"),
    .p05E4 = (const u8*)&sBlob_6638a0_682fac + 0x5A0,
    .gap05E8 = INCBIN_U8("data/Blob_6638a0_gap_05E8.bin"),
    .p05EC = (const u8*)&sBlob_6638a0_682fac + 0x5AE,
    .gap05F0 = INCBIN_U8("data/Blob_6638a0_gap_05F0.bin"),
    .p05F4 = (const u8*)&sBlob_6638a0_682fac + 0x5A0,
    .gap05F8 = INCBIN_U8("data/Blob_6638a0_gap_05F8.bin"),
    .p05FC = (const u8*)&sBlob_6638a0_682fac + 0x592,
    .gap0600 = INCBIN_U8("data/Blob_6638a0_gap_0600.bin"),
    .term0604 = INCBIN_U8("data/Blob_6638a0_term_0604.bin"),
    .beforeCutscene = INCBIN_U8("data/Blob_6638a0_seg_060C_159E0.bin"),
    .cutsceneFrameData = {
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x152E8), .timer = 0x10 }, /* +0x159E0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15302), .timer = 0x10 }, /* +0x159E8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1531C), .timer = 0x10 }, /* +0x159F0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15302), .timer = 0x10 }, /* +0x159F8 */
        FRAME_DATA_TERMINATOR, /* +0x15A00 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1529A), .timer = 0x10 }, /* +0x15A08 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x152B4), .timer = 0x10 }, /* +0x15A10 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x152CE), .timer = 0x10 }, /* +0x15A18 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x152B4), .timer = 0x10 }, /* +0x15A20 */
        FRAME_DATA_TERMINATOR, /* +0x15A28 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x153CA), .timer = 0x03 }, /* +0x15A30 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15414), .timer = 0x03 }, /* +0x15A38 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15470), .timer = 0x02 }, /* +0x15A40 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x154C6), .timer = 0x01 }, /* +0x15A48 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15528), .timer = 0x01 }, /* +0x15A50 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x155A2), .timer = 0x01 }, /* +0x15A58 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1564C), .timer = 0x01 }, /* +0x15A60 */
        FRAME_DATA_TERMINATOR, /* +0x15A68 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1564C), .timer = 0x01 }, /* +0x15A70 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x155A2), .timer = 0x01 }, /* +0x15A78 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15528), .timer = 0x01 }, /* +0x15A80 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x154C6), .timer = 0x01 }, /* +0x15A88 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15470), .timer = 0x02 }, /* +0x15A90 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15414), .timer = 0x03 }, /* +0x15A98 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x153CA), .timer = 0x03 }, /* +0x15AA0 */
        FRAME_DATA_TERMINATOR, /* +0x15AA8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15726), .timer = 0x08 }, /* +0x15AB0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1579A), .timer = 0x08 }, /* +0x15AB8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1580E), .timer = 0x08 }, /* +0x15AC0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15882), .timer = 0x08 }, /* +0x15AC8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x158F6), .timer = 0x08 }, /* +0x15AD0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1596A), .timer = 0x08 }, /* +0x15AD8 */
        FRAME_DATA_TERMINATOR, /* +0x15AE0 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15336), .timer = 0x08 }, /* +0x15AE8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15380), .timer = 0x08 }, /* +0x15AF0 */
        FRAME_DATA_TERMINATOR, /* +0x15AF8 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15048), .timer = 0xFF }, /* +0x15B00 */
        FRAME_DATA_TERMINATOR, /* +0x15B08 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x1506E), .timer = 0xFF }, /* +0x15B10 */
        FRAME_DATA_TERMINATOR, /* +0x15B18 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15232), .timer = 0xFF }, /* +0x15B20 */
        FRAME_DATA_TERMINATOR, /* +0x15B28 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x150E2), .timer = 0x04 }, /* +0x15B30 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15156), .timer = 0x04 }, /* +0x15B38 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x151CA), .timer = 0x04 }, /* +0x15B40 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15232), .timer = 0x04 }, /* +0x15B48 */
        FRAME_DATA_TERMINATOR, /* +0x15B50 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15232), .timer = 0x06 }, /* +0x15B58 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x151CA), .timer = 0x06 }, /* +0x15B60 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x15156), .timer = 0x06 }, /* +0x15B68 */
        { .pFrame = (const u16*)((const u8*)&sBlob_6638a0_682fac + 0x150E2), .timer = 0x06 }, /* +0x15B70 */
        FRAME_DATA_TERMINATOR, /* +0x15B78 */
    },
    .after = INCBIN_U8("data/Blob_6638a0_seg_15B80_1F70C.bin"),
};
