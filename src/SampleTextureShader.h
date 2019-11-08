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

        SampleTextureShader &setModelViewProjectionMatrix(const Matrix4 &matrix) {
            setUniform(mTransformationProjectionMatrixUniform, matrix);
            return *this;
        }

        SampleTextureShader &setColor(const Color3 &color)
        {
            setUniform(mColorUniform, color);
            return *this;
        }

        SampleTextureShader &setTextureScale(const Vector3 &scale)
        {
            setUniform(mTextureScaleUnitform, scale);
            return *this;
        }

    private:
        enum : Int {
            TextureUnit = 0
        };

        Int mTransformationProjectionMatrixUniform{0};
        Int mTextureScaleUnitform{1};
        Int mColorUniform{2};

    };

}
