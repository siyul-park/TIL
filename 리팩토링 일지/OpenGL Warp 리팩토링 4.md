# OpenGL Warp

## Buffer

```c++
namespace gl {

class Buffer {
 public:
  Buffer() = default;
  virtual ~Buffer() = default;
};

}
```



### FrameBuffer

```c++
namespace gl {

class FrameBuffer : public Buffer {
 public:
  enum class Buffer {
    Color = GL_COLOR,
  };

  FrameBuffer() = default;
  virtual ~FrameBuffer() = default;

  virtual void clear(GLint drawBuffer, const GLint *value) = 0;
  virtual void clear(GLint drawBuffer, const GLuint *value) = 0;
//  virtual void clear(const Buffer &buffer, GLint drawBuffer, const GLfloat &value) = 0;
  virtual void clear(GLint drawBuffer, const GLfloat *value) = 0;
};

}
```



### BindFrameBuffer

```c++
namespace gl {

class BindFrameBuffer : public FrameBuffer {
 public:
  explicit BindFrameBuffer(RenderingContext &context, const FrameBuffer::Buffer &buffer);
  ~BindFrameBuffer() final;

  void clear(GLint drawBuffer, const GLint *value) final;
  void clear(GLint drawBuffer, const GLuint *value) final;
//  void clear(const Buffer &buffer, GLint drawBuffer, const GLfloat &value) final;
  void clear(GLint drawBuffer, const GLfloat *value) final;

 private:
  RenderingContext *context;
  FrameBuffer::Buffer buffer;
};

}
```

