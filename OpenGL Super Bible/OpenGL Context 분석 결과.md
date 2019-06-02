# OpenGL Context 분석 결과

- OpenGL Conctext는 OpenGL의 자원을 가지고 있는 객체이다.
  - 지원엔 OpenGL을 구성하는 모든 자원이 포함 되지만 OpenGL Context를 구현 할때는 일반적으로 기본 프레임 버퍼를 반환 해주는 기능을 제공한다.
- OpenGL의 결과가 실제로 그려지는 스크린 또는 어떠한 데이터에 OpenGL의 내용을 연결해주는 기능을 일반적으로 가지고 있다
- 그외 OpenGL API에서 특정 묶음으로 묶이지 않는 API을 OpenGL Context 클래스에 1차적으로 넣고 관리하며 나중에 묶일수 있을때 분리하여 관리 하기로 한다



### Rendering Context

```c++
namespace gl {

class RenderingContext {
 public:
  enum class DrawMode {
    Points = GL_POINTS,
    Triangles = GL_TRIANGLES,
  };

  explicit RenderingContext() = default;
  virtual ~RenderingContext() = default;

  virtual void doneCurrent() = 0;
  virtual void makeCurrent() = 0;

  virtual void swapBuffers() = 0;

  ::std::unique_ptr<FrameBuffer> getFrameBuffer(const FrameBuffer::Buffer &buffer);

  inline void drawArrays(const DrawMode &mode, int first, size_t count);
  inline void pointSize(float size);

  inline Version getVersion() const;
  inline ::std::string getVendor() const;
  inline ::std::string getRenderer() const;
};

}
```

