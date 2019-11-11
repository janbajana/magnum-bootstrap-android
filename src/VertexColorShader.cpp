#include "VertexColorShader.h"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>

#include "util.h"

namespace Magnum {

    static const std::string vtxShader = R"(
layout(location = 0) uniform mat4 transformationProjectionMatrix;

in highp vec3 position;
in mediump vec3 normal;
in lowp vec3 color;

out lowp vec3 vInterpolatedColor;
out lowp vec3 vNormal;

void main() {
    gl_Position = transformationProjectionMatrix*vec4(position, 1.0f);
    vInterpolatedColor = color;
    vNormal = (transformationProjectionMatrix * vec4(normal.xyz, 0.0)).xyz;
}
)";

    static const std::string frgShader = R"(
in lowp vec3 vInterpolatedColor;
in lowp vec3 vNormal;

out lowp vec4 fragmentColor;

void main() {
    fragmentColor = vec4(vInterpolatedColor, 1.0f);
    //fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

    VertexColorShader::VertexColorShader() {

        LOGD("DAQRI VertexColorShader\n");

        MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GLES300);

        const Utility::Resource rs0{"MagnumBootstrapData"};
        const Utility::Resource rs{"MagnumShaders"};

        GL::Shader vert{GL::Version::GLES300, GL::Shader::Type::Vertex};
        GL::Shader frag{GL::Version::GLES300, GL::Shader::Type::Fragment};

        vert.addSource(rs.get("generic.glsl"))
                .addSource(vtxShader);
        frag.addSource(rs.get("generic.glsl"))
                .addSource(frgShader);

        CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({vert, frag}));

        attachShaders({vert, frag});

        bindAttributeLocation(Position::Location, "position");
        bindAttributeLocation(Normal::Location, "normal");
        bindAttributeLocation(Color3::Location, "color"); /* Color4 is the same */

        CORRADE_INTERNAL_ASSERT_OUTPUT(link());

        _transformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");

        // Set default matrix.
        setModelViewProjectionMatrix(Matrix4{});
    }

}
