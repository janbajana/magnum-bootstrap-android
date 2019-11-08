#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Texture.h>

#include "Magnum/Math/Matrix4.h"
#include <Magnum/Math/Color.h>
#include "Magnum/Shaders/Generic.h"

namespace Magnum {

    class SampleTextureShader : public GL::AbstractShaderProgram {
    public:
        typedef GL::Attribute<0, Vector2> Position;
        typedef GL::Attribute<1, Vector2> TextureCoordinates;

        explicit SampleTextureShader();

        SampleTextureShader &bindTexture(GL::Texture2D &texture) {
            texture.bind(TextureUnit);
            return *this;
        }

        SampleTextureShader &setTransformationMatrix(const Matrix4 &matrix) {
            setUniform(mTransformationMatrixUniform, matrix);
            return *this;
        }

        SampleTextureShader &setProjectionMatrix(const Matrix4 &matrix) {
            setUniform(mProjectionMatrixUniform, matrix);
            return *this;
        }

        SampleTextureShader &setViewMatrix(const Matrix4 &matrix) {
            setUniform(mViewMatrixUniform, matrix);
            return *this;
        }

    private:
        enum : Int {
            TextureUnit = 0
        };

        Int _colorUniform;
        Int mTransformationMatrixUniform{0};
        Int mProjectionMatrixUniform{0};
        Int mViewMatrixUniform{0};
    };

}
