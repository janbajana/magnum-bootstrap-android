#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/GL/Renderer.h>

#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/Primitives/Cube.h>

#ifndef CORRADE_TARGET_ANDROID
#include <Magnum/Platform/Sdl2Application.h>
#else
#include <Magnum/Platform/AndroidApplication.h>
#endif

#include "SampleTextureShader.h"
#include "VertexColorShader.h"

using namespace Magnum;

class MyApplication: public Platform::Application {
public:
    explicit MyApplication(const Arguments& arguments);

private:

    GL::Mesh _mesh;
    Shaders::VertexColor2D _shader;

    Magnum::SampleTextureShader _sampleShader;
    Magnum::VertexColorShader _vertexColorShader;

    Matrix4 _transformationMatrix, _projectionMatrix, _viewMatrix;
    void drawEvent() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application{arguments} {
    /* TODO: Add your initialization code here */

    using namespace Math::Literals;

//    struct TriangleVertex {
//        Vector3 position;
//        Vector3 nornal;
//        Color3 color;
//    };
//    const TriangleVertex data[]{
//            {{-0.5F, -0.5F, 0.0F}, {0.0F, 0.0F, 0.1F}, 0xff0000_rgbf},    /* Left vertex, red color */
//            {{ 0.5F, -0.5F, 0.0F}, {0.0F, 0.0F, 0.1F}, 0x00ff00_rgbf},    /* Right vertex, green color */
//            {{ 0.0F,  0.5F, 0.0F}, {0.0F, 0.0F, 0.1F}, 0x0000ff_rgbf}     /* Top vertex, blue color */
//    };
//
//    GL::Buffer buffer;
//    buffer.setData(data);
//
//    _mesh.setCount(3)
//            .addVertexBuffer(std::move(buffer), 0,
//                             VertexColorShader::Position{},
//                             VertexColorShader::Normal{},
//                             VertexColorShader::Color3{});

    //Create cube mesh.
    const Trade::MeshData3D cube = Primitives::cubeSolid();
    GL::Buffer vertices;
    vertices.setData(MeshTools::interleave(cube.positions(0), cube.normals(0)));

    Containers::Array<char> indexData;
    MeshIndexType indexType;
    UnsignedInt indexStart, indexEnd;
    std::tie(indexData, indexType, indexStart, indexEnd) =
            MeshTools::compressIndices(cube.indices());
    GL::Buffer indices;
    indices.setData(indexData);

    _mesh.setPrimitive(cube.primitive())
            .setCount(cube.indices().size())
            .addVertexBuffer(std::move(vertices), 0,
                             VertexColorShader::Position{},
                             VertexColorShader::Normal{})
            .setIndexBuffer(std::move(indices), 0, indexType, indexStart, indexEnd);

    _transformationMatrix =
            Matrix4::translation(Vector3::zAxis(-10.0f))*Matrix4::rotationX(25.0_degf)*Matrix4::rotationY(45.0_degf);

    _viewMatrix =
            Matrix4::translation({0.0f, 0.0f, 0.0f});

    _projectionMatrix =
            Matrix4::perspectiveProjection(
                    35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f);

}

void MyApplication::drawEvent() {

    GL::Renderer::setClearColor({0.5, 0, 0, 1});
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth);

    _vertexColorShader.setModelViewProjectionMatrix(_projectionMatrix*(_viewMatrix*_transformationMatrix));
//    _sampleShader.setModelViewProjectionMatrix(_projectionMatrix*(_viewMatrix*_transformationMatrix));
    _mesh.draw(_vertexColorShader);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
