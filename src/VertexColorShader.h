#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Texture.h>

#include "Magnum/Math/Matrix4.h"
#include <Magnum/Math/Color.h>
#include "Magnum/Shaders/Generic.h"

namespace Magnum {

    class VertexColorShader : public GL::AbstractShaderProgram {
    public:
        explicit VertexColorShader();

        typedef typename Shaders::Generic3D::Position Position;
        typedef typename Shaders::Generic3D::Normal Normal;
        typedef typename Shaders::Generic3D::Color3 Color3;
        typedef typename Shaders::Generic3D::Color4 Color4;

        VertexColorShader &setModelViewProjectionMatrix(const Matrix4 &matrix) {
            setUniform(_transformationProjectionMatrixUniform, matrix);
            return *this;
        }

    private:
        enum : Int {
            TextureUnit = 0
        };

        Int _transformationProjectionMatrixUniform{0};

    };
}
