#include "SampleTextureShader.h"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>

#include "util.h"

namespace Magnum {

    SampleTextureShader::SampleTextureShader() {

        LOGD("DAQRI SampleTextureShader \n");

        MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GLES300);

        const Utility::Resource rs{"MagnumShaders"};
        const Utility::Resource rs2{"MagnumBootstrapData"};

        GL::Shader vert{GL::Version::GLES300, GL::Shader::Type::Vertex};
        GL::Shader frag{GL::Version::GLES300, GL::Shader::Type::Fragment};

        vert.addSource(rs.get("generic.glsl"))
                .addSource(rs2.get("sample_texture.vert"));
        frag.addSource(rs.get("generic.glsl"))
                .addSource(rs2.get("sample_texture.frag"));

        CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({vert, frag}));

        attachShaders({vert, frag});

        CORRADE_INTERNAL_ASSERT_OUTPUT(link());

        mTransformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");
        mTextureScaleUnitform = uniformLocation("color");
        mColorUniform = uniformLocation("textureScale");

        setUniform(uniformLocation("srcTex"), TextureUnit);

        setModelViewProjectionMatrix(Matrix4{});
        setColor(Color3{1.0F, 1.0F, 1.0F});
        setTextureScale(Vector3{1.0F, 1.0F, 1.0F});
    }
}
