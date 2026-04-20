#pragma once
#include <memory>
#include <vector>

#include "TeaPacket/MacroUtils/ClassDefUtils.hpp"

namespace TeaPacket::Graphics
{
    struct MeshParameters;
    struct PlatformMesh;
    struct ShaderVariableType;

    /// @brief Represents a reusable piece of geometry.
    /// @details A mesh represents only geometry, specifically a set of vertices and optionally a set of faces.
    class Mesh
    {
    public:

        /// A pointer to the implementation-defined data this mesh uses.
        std::unique_ptr<PlatformMesh> platformMesh;

    public:
        /// The currently active mesh that will be used when DrawMesh() is called.
        static inline Mesh* activeMesh = nullptr;

    private:

    public:
        /// Constructs a mesh via parameters.
        Mesh() = default;
        explicit Mesh(const MeshParameters& parameters);
        ~Mesh();

        TP_OBJ_MOVE_NO_COPY(Mesh)

        /// Sets this mesh to be the currently active mesh, to be used in future DrawMesh() calls.
        void SetActive();
    };
}
