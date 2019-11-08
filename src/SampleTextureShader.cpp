#include "SampleTextureShader.h"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>

#include "util.h"

namespace Magnum {

    static const std::string vtxShader = R"(
in vec3 position;
in vec2 texcoord0;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec2 textureScale;

out vec2 vTexcoord0;

void main()
{
    gl_Position = projectionMatrix * (viewMatrix * (modelMatrix * vec4(position, 1.0)));
    vTexcoord0 = texcoord0 * textureScale;
}
)";

    static const std::string frgShader = R"(
in highp vec2 vTexcoord0;
uniform sampler2D srcTex;
out highp vec4 outColor;

void main()
{
    highp vec4 srcColor = texture(srcTex, vTexcoord0);
    outColor = srcColor;
}
)";

    SampleTextureShader::SampleTextureShader() {

        LOGD("DAQRI SampleTextureShader \n");

        MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GLES300);


        const Utility::Resource rs{"MagnumShaders"};

        std::vector<std::string> resList = rs.list();
        for(const auto &ress: resList)
        {
                LOGW("DAQRI res: %s \n", ress.c_str());
        }

        GL::Shader vert{GL::Version::GLES300, GL::Shader::Type::Vertex};
        GL::Shader frag{GL::Version::GLES300, GL::Shader::Type::Fragment};

//        vert.addSource(rs.get("TexturedTriangleShader.vert"));
//        frag.addSource(rs.get("TexturedTriangleShader.frag"));

//        vert.addSource(rs.get("generic.glsl"))
//                .addSource(vtxShader);
//        frag.addSource(rs.get("generic.glsl"))
//                .addSource(frgShader);

        vert.addSource(vtxShader);
        frag.addSource(frgShader);

        CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({vert, frag}));

        attachShaders({vert, frag});

        CORRADE_INTERNAL_ASSERT_OUTPUT(link());

//        _colorUniform = uniformLocation("color");
//
//        setUniform(uniformLocation("textureData"), TextureUnit);
    }

}
