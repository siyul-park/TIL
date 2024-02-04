# OpenGL Warp 리팩토링 일지

## OpenGL Warp

다양한 플렛폼에서 다양한 언어에서 사용될 것을 고려한 OpenGL을 C++환경에서 쉽게 사용할 수 있게 만들어 주는 프로젝트

## Buffer 리팩토링

### 기존 코드

#### Buffer.h

```c++
namespace gl {

class Buffer : public BaseObject<Buffer> {
 public:
  enum class Target {
    Array = GL_ARRAY_BUFFER,
    AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
    CopyRead = GL_COPY_READ_BUFFER,
    CopyWRITE = GL_COPY_WRITE_BUFFER,
    DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
    DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
    ElementArray = GL_ELEMENT_ARRAY_BUFFER,
    PixelPack = GL_PIXEL_PACK_BUFFER,
    PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
    Query = GL_QUERY_BUFFER,
    ShaderStorage = GL_SHADER_STORAGE_BUFFER,
    Texture = GL_TEXTURE_BUFFER,
    TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    Uniform = GL_UNIFORM_BUFFER,
  };

  enum class Usage {
    StreamDraw = GL_STREAM_DRAW,
    StreamRead = GL_STREAM_READ,
    StreamCopy = GL_STREAM_COPY,

    StaticDraw = GL_STATIC_DRAW,
    StaticRead = GL_STATIC_READ,
    StaticCopy = GL_STATIC_COPY,

    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY,
  };

  enum class Format {
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
  };

  template <int N>
  constexpr static Format getFormat();

  enum class Type {
    Byte = GL_BYTE,
    Unsigned_Byte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    Unsigned_Short = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    Unsigned_Int = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
  };

  template <typename T>
  constexpr static Type getType();

  enum class InternalFormat {
    R8 = GL_R8,
    R16 = GL_R16,
    R16F = GL_R16F,
    R32F = GL_R32F,
    R8I = GL_R8I,
    R16I = GL_R16I,
    R32I = GL_R32I,
    R8UI = GL_R8UI,
    R16UI = GL_R16UI,
    R32UI = GL_R32UI,
//    R32U = GL_R32U,

    RG8 = GL_RG8,
    RG16 = GL_RG16,
    RG16F = GL_RG16F,
    RG32F = GL_RG32F,
    RG8I = GL_RG8I,
    RG16I = GL_RG16I,
    RG32I = GL_RG32I,
    RG8UI = GL_RG8UI,
    RG16UI = GL_RG16UI,
    RG32UI = GL_RG32UI,

    RGB8 = GL_RGB8,
    RGB16I = GL_RGB16I,
    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB8I = GL_RGB8I,
    RGB32UI = GL_RGB32UI,

    RGBA8 = GL_RGBA8,
    RGBA16 = GL_RGBA16,
    RGB16UI = GL_RGB16UI,
    RGBA16F = GL_RGBA16F,
    RGBA32F = GL_RGBA32F,
    RGBA8I = GL_RGBA8I,
    RGBA16I = GL_RGBA16I,
    RGBA32I = GL_RGBA32I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16UI = GL_RGBA16UI,
    RGBA32UI = GL_RGBA32UI,
  };

  template <Type type, Format format>
  constexpr static InternalFormat getInternalFormat();

  struct Data {
    template <typename T>
    Data(const T &data) : data{&data}, size{sizeof(data)} {}

    void *data;
    size_t size;
  };

  inline Buffer();
  inline virtual ~Buffer();

  inline void bind(Target target);
  
  inline void alloc(size_t size, Usage usage);

  template <Target target>
  inline static void alloc(size_t size, Usage usage);

  inline void alloc(const Data &data, Usage usage);

  template <Target target>
  inline static void alloc(const Data &data, Usage usage);

  inline void update(const Data &data, int offset);

  template <Target target>
  inline static void update(const Data &data, int offset);

  inline void* map(Usage usage);

  template <Target target>
  inline static void* map(Usage usage);

  inline void unmap();

  template <Target target>
  inline void unmap();

  template <typename T, int N>
  inline void clear(const T (&data)[N]);

  template <Target target, typename T, int N>
  inline static void clear(const T (&data)[N]);

  template <typename T, int N>
  inline void clear(const T (&data)[N], int offset);

  template <Target target, typename T, int N>
  inline static void clear(const T (&data)[N], int offset);
};

}
```

#### 문제점

- 클래스의 크기가 너무 크다.
- Buffer 클래스 내부에 너무 많은 기능이 들어가 있다
- Buffer 클래스에 static으로 접근 할때와 인스턴트 맴버에서 접근 할때 기능이 달라진다.

### 수정 

##### bufferBase.h

```c++
namespace gl {
namespace buffer {

class bufferBase {
 public:
  enum class Usage {
    StreamDraw = GL_STREAM_DRAW,
    StreamRead = GL_STREAM_READ,
    StreamCopy = GL_STREAM_COPY,

    StaticDraw = GL_STATIC_DRAW,
    StaticRead = GL_STATIC_READ,
    StaticCopy = GL_STATIC_COPY,

    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY,
  };

  inline bufferBase() = default;
  inline virtual ~bufferBase() = default;

  inline virtual void alloc(size_t size, Usage usage) = 0;
  inline virtual void alloc(const DataAdapter &data, Usage usage) = 0;

  inline virtual void update(const DataAdapter &data, int offset) = 0;

  inline virtual void *map(Usage usage) = 0;
  inline virtual void unmap() = 0;

  inline virtual void clear(const TypeSupposerAdapter &data) = 0;
  inline virtual void clear(const TypeSupposerAdapter &data, int offset) = 0;
};

}
}
```

- 중복 되는 코드를 BufferBase 클래스로 뽑아 냈다.
- 이 클래스를 상속받아 Target, Buffer 클래스를 구현한다.
- 기존의 Data클래스를 다른 클래스로 분리하고 용도에 맞게 DataAdapter로 바꿨다.
- clear 함수에서 template을 사용하지 않게 전달된 타입에 따라 내부 형식을 추청하는 TypeSuppose를 다른 클래스로 분리를 하였고 일반적인 타입들을 TypeSupposed된 기능을 사용 할수 있게 TypeSupposerAdapter를 전달 받게 수정했다.
- 연관된 클래스들을 묶기 위해 buffer 네임스페이스를 추가했다.



##### bufferDataAdapter

```c++
namespace gl {
namespace buffer {

struct DataAdapter {
  template<typename T>
  DataAdapter(const T &data) : data{&data}, size{sizeof(T)} {}
  template<typename T, int N>
  DataAdapter(const T (&data)[N]) : data{data}, size{sizeof(T[N])} {}

  void *data;
  size_t size;
};

}
}
```

- C++ 기본 타입을 가공하여 OpenGL에서 요구하는 데이터 형식으로 바꾸어 준다.
- 상속이 가능하게 하여, C++ 기본타입을 어떻게 가공할지 정할 수 있게 하였다.

###### 사용

```c++
void exam() {
  int array[4] = {0};
  DataAdapter a{array};
  
  void *data = a.data;
  size_t size = a.size;
}
```



##### bufferTypeSupposerAdapter

```c++
namespace gl{
namespace buffer {

struct TypeSupposerAdapter : public DataAdapter {
  template<typename T>
  TypeSupposerAdapter(const T data)
    : DataAdapter(data), type{Type::get<T>()}, format{Format::get<1>()}, internalFormat{InternalFormat::get<T, 1>()} {}
    
  template<typename T, int N>
  TypeSupposerAdapter(const T (&data)[N])
    : DataAdapter(data), type{Type::get<T>()}, format{Format::get<N>()}, internalFormat{InternalFormat::get<T, N>()} {}

  Type type;
  Format format;
  InternalFormat internalFormat;
};

}
}
```

- DataAdapter를 상속해 기능을 확장시킨다.
- 전달 된 값으로 OpenGL 내부에서 사용할 값을 추청한다.

##### bufferType

```c++
namespace gl{
namespace buffer {

struct Type {
  enum class Types {
    Byte = GL_BYTE,
    Unsigned_Byte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    Unsigned_Short = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    Unsigned_Int = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
  };

  template <typename T>
  constexpr static Types get();

  Types type;
};

}
}
```

- OpenGL 내부에서 사용할 타입들을 정의하고 C++ 타입을 OpenGL 내부 타입으로 바꿔준다.

##### bufferForamt

```c++
namespace gl{
namespace buffer {

struct Format {
  enum class Types {
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
  };

  template <int N>
  constexpr static Format get();

  Types type;
};

}
}
```

- OpenGL 내부에서 사용하는 Format을 정의하고 C++ 타입을 OpenGL 내부 타입으로 바꿔준다.

##### bufferInternalFormat

```c++
namespace gl{
namespace buffer {

struct InternalFormat {
  enum class Types {
    R8 = GL_R8,
    R16 = GL_R16,
    R16F = GL_R16F,
    R32F = GL_R32F,
    R8I = GL_R8I,
    R16I = GL_R16I,
    R32I = GL_R32I,
    R8UI = GL_R8UI,
    R16UI = GL_R16UI,
    R32UI = GL_R32UI,
//    R32U = GL_R32U,

    RG8 = GL_RG8,
    RG16 = GL_RG16,
    RG16F = GL_RG16F,
    RG32F = GL_RG32F,
    RG8I = GL_RG8I,
    RG16I = GL_RG16I,
    RG32I = GL_RG32I,
    RG8UI = GL_RG8UI,
    RG16UI = GL_RG16UI,
    RG32UI = GL_RG32UI,

    RGB8 = GL_RGB8,
    RGB16I = GL_RGB16I,
    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB8I = GL_RGB8I,
    RGB32UI = GL_RGB32UI,

    RGBA8 = GL_RGBA8,
    RGBA16 = GL_RGBA16,
    RGB16UI = GL_RGB16UI,
    RGBA16F = GL_RGBA16F,
    RGBA32F = GL_RGBA32F,
    RGBA8I = GL_RGBA8I,
    RGBA16I = GL_RGBA16I,
    RGBA32I = GL_RGBA32I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16UI = GL_RGBA16UI,
    RGBA32UI = GL_RGBA32UI,
  };

  template <typename T, int N>
  constexpr static Types get();

  Types type;
};

}
}
```

- C++ 타입에 대한 정보를 가지고 OpenGL 내부 타입으로 변환시킨다.

##### buffer.h

```c++
namespace gl {
namespace buffer {

class Buffer : public bufferBase {
 public:
  inline Buffer();
  inline virtual ~Buffer();

  inline void bind(Target target);

  inline virtual void alloc(size_t size, Usage usage) override;
  inline virtual void alloc(const DataAdapter &data, Usage usage) override;

  inline virtual void update(const DataAdapter &data, int offset) override;

  inline virtual void *map(Usage usage) override;
  inline virtual void unmap() override;

  inline virtual void clear(const TypeSupposerAdapter &data) override;
  inline virtual void clear(const TypeSupposerAdapter &data, int offset) override;

 private:
  GLuint name;
};

}
}
```

- 버퍼의 Target지정후 연산하는 부분을 분리 시켰다. 

bufferTarget

```c++
namespace gl{
namespace buffer {

class Target : public bufferBase {
 public:
  enum class Types {
    Array = GL_ARRAY_BUFFER,
    AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
    CopyRead = GL_COPY_READ_BUFFER,
    CopyWRITE = GL_COPY_WRITE_BUFFER,
    DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
    DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
    ElementArray = GL_ELEMENT_ARRAY_BUFFER,
    PixelPack = GL_PIXEL_PACK_BUFFER,
    PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
    Query = GL_QUERY_BUFFER,
    ShaderStorage = GL_SHADER_STORAGE_BUFFER,
    Texture = GL_TEXTURE_BUFFER,
    TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    Uniform = GL_UNIFORM_BUFFER,
  };

  inline Target(Types type);
  inline virtual ~Target();

  inline virtual void alloc(size_t size, Usage usage) override;
  inline virtual void alloc(const DataAdapter &data, Usage usage) override;

  inline virtual void update(const DataAdapter &data, int offset) override;

  inline virtual void *map(Usage usage) override;
  inline virtual void unmap() override;

  inline virtual void clear(const TypeSupposerAdapter &data) override;
  inline virtual void clear(const TypeSupposerAdapter &data, int offset) override;

  Types type;
};

}
}
```

- 기존에 Buffer 클래스에 합쳐져 있던 기능을 분리 시켰다.

