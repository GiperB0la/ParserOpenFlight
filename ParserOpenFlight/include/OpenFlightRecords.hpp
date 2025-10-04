#pragma once
#include <iostream>

enum RecordOpcode : uint16_t
{
    PUSH_LEVEL = 10,
    POP_LEVEL = 11,
    PUSH_SUBFACE= 19,
    POP_SUBFACE = 20,
    PUSH_EXTENSION = 21,
    POP_EXTENSION = 22,
    PUSH_ATTRIBUTE = 122,
    POP_ATTRIBUTE = 123,
    INSTANCE_DEFINITION = 62,
    INSTANCE_REFERENCE = 61,
    HEADER = 1,
    GROUP = 2,
    OBJECT = 4,
    FACE = 5,
    COLOR_PALETTE = 32,
    MATERIAL_PALETTE = 113,
    LIGHT_SOURCE_PALETTE = 102,
    EYEPOINT_AND_TRACKPLANE_PALETTE = 83,
    VERTEX_PALETTE = 67,
    VERTEX_CN = 69,
    LONG_ID = 33,
    VERTEX_LIST = 72
};

#pragma pack(push, 1)
struct Record
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PushLevelRecord
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PopLevelRecord
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PushSubfaceRecord
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PopSubfaceRecord
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PushExtensionRecord
{
    uint16_t opcode;
    uint16_t length;
    char     reserved[18];
    uint16_t vertex_ref_index;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PopExtensionRecord
{
    uint16_t opcode;
    uint16_t length;
    char     reserved[18];
    uint16_t vertex_ref_index;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PushAttributeRecord
{
    uint16_t opcode;
    uint16_t length;
    int32_t  vertex_ref_index;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PopAttributeRecord
{
    uint16_t opcode;
    uint16_t length;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct InstanceDefinitionRecord
{
    uint16_t opcode;
    uint16_t length;
    uint32_t definition_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct InstanceReferenceRecord
{
    uint16_t opcode;
    uint16_t length;
    uint32_t definition_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct HeaderRecord
{
    uint16_t opcode;
    uint16_t length;
    char     id[8];
    int32_t  format_revision;
    int32_t  edit_revision;
    char     date_time[32];
    uint16_t next_group_id;
    uint16_t next_lod_id;
    uint16_t next_object_id;
    uint16_t next_face_id;
    uint16_t unit_multiplier;
    uint8_t  vertex_units;
    uint8_t  set_texwhite_new_faces;
    uint32_t flags;
    uint32_t reserved_68[6];
    uint32_t projection_type;
    uint32_t reserved_96[7];
    uint16_t next_dof_node_id;
    uint16_t vertex_storage_type;
    int32_t  database_origin;
    double   southwest_x;
    double   southwest_y;
    double   delta_x;
    double   delta_y;
    int16_t  next_sound_id;
    uint16_t reserved_166;
    uint32_t reserved_168[2];
    int16_t  next_path_id;
    int16_t  next_clip_id;
    int16_t  next_text_id;
    int16_t  next_bsp_id;
    int16_t  next_switch_id;
    int32_t  reserved_186;
    double   sw_lat;
    double   sw_lon;
    double   ne_lat;
    double   ne_lon;
    double   origin_lat;
    double   origin_lon;
    double   lambert_upper_lat;
    double   lambert_lower_lat;
    int16_t  next_light_source_id;
    int16_t  next_light_point_id;
    int16_t  next_road_id;
    int16_t  next_cat_id;
    int16_t  reserved_260[3];
    int32_t  earth_model;
    int16_t  next_adaptive_node_id;
    int16_t  next_curve_id;
    int16_t  utm_zone;
    char     reserved_278[6];
    double   delta_z;
    double   radius;
    uint16_t next_mesh_node_id;
    uint16_t next_light_point_sys_id;
    uint32_t reserved_304;
    double   earth_major_axis;
    double   earth_minor_axis;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct GroupRecord
{
    uint16_t opcode;
    uint16_t length;
    char     id[8];
    uint16_t relative_priority;
    uint16_t reserved1;
    uint32_t flags;
    uint16_t special_id1;
    uint16_t special_id2;
    uint16_t significance;
    uint8_t  layer_code;
    uint8_t  reserved2;
    uint32_t reserved3;
    uint32_t loop_count;
    float    loop_duration;
    float    last_frame_duration;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ObjectRecord
{
    uint16_t opcode;
    uint16_t length;
    char     id[8];
    uint32_t flags;
    uint16_t relative_priority;
    uint16_t transparency;
    uint16_t special_id1;
    uint16_t special_id2;
    uint16_t significance;
    uint16_t reserved;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FaceRecord
{
    uint16_t opcode;
    uint16_t length;
    char     id[8];
    uint32_t ir_color_code;
    uint16_t relative_priority;
    uint8_t  draw_type;
    uint8_t  texture_white;
    uint16_t color_name_index;
    uint16_t alt_color_name_index;
    uint8_t  reserved_0[2];
    uint8_t  template_billboard;
    uint8_t  reserved_1;
    uint16_t detail_texture_index;
    uint16_t texture_pattern_index;
    uint16_t material_index;
    uint16_t surface_material_code;
    uint16_t feature_id;
    uint32_t ir_material_code;
    uint16_t transparency;
    uint8_t  lod_generation_ctrl;
    uint8_t  line_style_index;
    uint32_t flags;
    uint8_t  light_mode;
    char     reserved_2[7];
    uint32_t packed_color_primary;
    uint32_t packed_color_alt;
    uint16_t texture_mapping_index;
    uint16_t reserved_3;
    uint32_t primary_color_index;
    uint32_t alternate_color_index;
    uint8_t  reserved_4[2];
    uint16_t shader_index;
};
#pragma pack(pop)