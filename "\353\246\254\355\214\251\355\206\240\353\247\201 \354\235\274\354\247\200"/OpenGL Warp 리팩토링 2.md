# OpenGL Warp 리팩토링 일지

처음부터 다시 작성하기로 했다



### Context

내부에서 사용하는 Context를 관리하는 클래스

```c++
namespace gl {

class Context {
 public:
  struct Version {
    int major, minor;
  };

  Context() = default;
  virtual ~Context() = default;

  virtual void init() = 0;
};

}
```

### GL3WContext

```c++
namespace gl {

class GL3WContext : public Context {
 public:
  explicit GL3WContext(const Version &version);
  ~GL3WContext() override;

  void init() override;

 private:
  Version version;
};

}
```

### GLFWContext

```c++
namespace gl {

class GLFWContext : public Context {
 public:
  explicit GLFWContext(const Version &version);
  ~GLFWContext() override;

  void init() override;

 private:
  static void errorCallback(int errorCode, const char* errorDescription);

  Version version;
  bool isInited;
};

}
```

