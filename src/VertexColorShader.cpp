#include "VertexColorShader.h"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>

#include "util.h"

namespace Magnum {

    VertexColorShader::VertexColorShader() {

        LOGD("DAQRI VertexColorShader\n");

        MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GLES300);

        const Utility::Resource rs0{"MagnumBootstrapData"};
        const Utility::Resource rs{"MagnumShaders"};

        GL::Shader vert{GL::Version::GLES300, GL::Shader::Type::Vertex};
        GL::Shader frag{GL::Version::GLES300, GL::Shader::Type::Fragment};

        vert.addSource(rs.get("generic.glsl"))
                .addSource(rs0.get("vertex_color.vert"));
        frag.addSource(rs.get("generic.glsl"))
                .addSource(rs0.get("vertex_color.frag"));

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
