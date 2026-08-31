/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Mesh.
 */
#ifndef TEAPACKET_GRAPHICS_GS_MESHPARAMS_H
#define TEAPACKET_GRAPHICS_GS_MESHPARAMS_H

#include "TeaPacket/Graphics/GS/VariableType.h"
#include "TeaPacket/Types/Array.h"

typedef TP_ArrayView(tp_u32) TP_GfxGS_MeshIndexList;

typedef struct
{
    /**
     * A pointer to the bytes used to create the vertices for this mesh.
     * @details Data is swizzled in these bytes according to vertexInfo.
     * One vertex should consist of a sequence of bytes.
     * These bytes are ordered and formatting based on the ordering and formatting of vertexInfo.
     *
     * For example, a vertexInfo of a Float with an amount of 2, and an Int with an amount of 4,
     * will require bytes to be formatted as
     * two Floats for Vertex 0, three Ints for Vertex 0, two Floats for Vertex 1, three Ints for Vertex 1, and so on...
     */
    TP_ByteView vertexData;
    /**
     * A list describing the attributes each vertex on this Mesh has.
     * @details Each entry in this list maps to one of the IN attributes in a shader,
     * using its position in the list as the layout position of the attribute to bind to.
     *
     * @warning Drawing a Mesh with a Shader whose IN attributes do not match with the Mesh's vertex attributes is undefined behavior.
     */
    TP_GfxGS_Shader_VarList vertexInfo;
    /**
     * The index data to be used for this mesh. If size is 0, index data is not used.
     * @details This list should be comprised of groups of 3 32-bit Integers, each defining a vertex index that a face should connect to.
     *
     * @warning Any values pointing to vertices outside the valid range of vertices given is undefined behavior.
     * The size of this list must be a multiple of 3. Not doing so is undefined behavior.
     */
    TP_GfxGS_MeshIndexList indexList;
} TP_GfxGS_MeshParams;

#endif
