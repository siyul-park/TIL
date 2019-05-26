# OpenGL Warp

## Rendering Context

OpenGL context 관리 클래스

```c++
namespace gl {

class RenderingContext {
 public:
  explicit RenderingContext() = default;
  virtual ~RenderingContext() = default;

  virtual void doneCurrent() = 0;
  virtual void makeCurrent() = 0;

  virtual void swapBuffers() = 0;
};

}
```



### glfw 구현

``` c++
namespace gl {
namespace internal {

class GLFWRenderingContext : public RenderingContext {
 public:
  explicit GLFWRenderingContext(Surface &surface);
  ~GLFWRenderingContext() final;

  void doneCurrent() final;
  void makeCurrent() final;

  void swapBuffers() final;
 private:
  void makeCurrent(Surface* surface);

  Surface *surface;
};

}
}
```



## Window

window 클래스

```c++
namespace gl {

class Window {
 public:
  Window() = default;
  virtual ~Window() = default;

  virtual const ::std::string getTitle() const = 0;
  virtual const Size getSize() const = 0;
  virtual bool shouldClose() const =0;
};

}
```



## Surface

OpenGL이 그릴 표면 클래스

```c++
namespace gl {

class Surface : public Window {
 public:
  Surface() = default;
  virtual ~Surface() = default;

  virtual void* getPlatformSurface() = 0;
  virtual const void* getPlatformSurface() const = 0;
};

}
```



## Window Surface

window에 그려지는 surface 클래스

```c++
namespace gl {

class WindowSurface : public Surface {
 public:
  WindowSurface() = default;
  virtual ~WindowSurface() = default;
};

}
```

### glfw 구현

```c++
namespace gl {
namespace internal {

class GLFWWindowSurface : public WindowSurface {
 public:
  GLFWWindowSurface(const ::std::string &title, const Size &size);
  ~GLFWWindowSurface() final;

  const ::std::string getTitle() const final;
  const Size getSize() const final;

  bool shouldClose() const final;

  void* getPlatformSurface() final;
  const void* getPlatformSurface() const final;

 private:
  GLFWwindow *window;

  ::std::string title;
};

}
}
```



## Off Screen Surface

window에 그려지지 않는 surface

```c++
namespace gl {

class OffScreenSurface : public Surface {
 public:
  OffScreenSurface() = default;
  virtual ~OffScreenSurface() = default;
};

}
```



## Factory

플렛폼에 따라 달라질수 있는 클래스를 생성하기 위한 팩토리

```c++
namespace gl {

class Factory {
 public:
  Factory() = default;
  virtual ~Factory() = default;

  virtual ::std::unique_ptr<Surface> createSurface(const ::std::string &title, const Size &size) const = 0;
  virtual ::std::unique_ptr<WindowSurface> createWindowSurface(const ::std::string &title, const Size &size) const = 0;
  virtual ::std::unique_ptr<OffScreenSurface> createOffScreenSurface(const ::std::string &title, const Size &size) const = 0;

  virtual ::std::unique_ptr<RenderingContext> createRenderingContext(Surface& surface) const = 0;
};

}
```



### glfw 구현

```c++
class GLFWFactory : public Factory {
 public:
  GLFWFactory(const Initializer::Version &version);
  ~GLFWFactory() final;

  ::std::unique_ptr<Surface> createSurface(const ::std::string &title, const Size &size) const final;
  ::std::unique_ptr<WindowSurface> createWindowSurface(const ::std::string &title, const Size &size) const final;
  ::std::unique_ptr<OffScreenSurface> createOffScreenSurface(const ::std::string &title, const Size &size) const final;

  ::std::unique_ptr<RenderingContext> createRenderingContext(Surface& surface) const final;

 private:
  ::std::unique_ptr<Initializer> initializer;
};

}
}
```



## Example 

### 윈도우 만들기

```c++
#include "factory/internal/glfwFactory.h"

int main() {
  gl::internal::GLFWFactory glfwFactory{{4, 3}};

  auto surface = glfwFactory.createWindowSurface("Test", {1024, 768});
  auto rendererContext = glfwFactory.createRenderingContext(*surface);

  while (!surface->shouldClose()) {
    rendererContext->swapBuffers();
  }

  return 0;
}
```

