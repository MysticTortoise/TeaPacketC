#pragma once
#include "TeaPacket/Graphics/Mesh.h"

#include "TeaPacket/Graphics/MeshParams.hpp"
#include "TeaPacket/Types/ClassDef.hpp"

#include "TeaPacket/Types/TPArray.hpp"

namespace TeaPacket::Graphics
{
    class Mesh
    {
    public:
        TP_ClassWrapperDef(Mesh, TP_Graphics)

        explicit Mesh(const MeshParams& params):
        Mesh(TP_Graphics_MeshParams{
            .vertexData = SpanToTPArray(params.vertexData),
            .vertexInfo = SpanToTPArrayCast(params.vertexInfo, TP_Graphics_VariableType),
            .indexList = SpanToTPArray(params.indexList)
        })
        {}

        void SetActive() const
        {
            TP_Graphics_Mesh_SetActive(p);
        }
    };
}
