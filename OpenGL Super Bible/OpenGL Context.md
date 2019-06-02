# OpenGL Context

컨텍스트는이 OpenGL 인스턴스와 관련된 모든 상태를 저장한다.

한 프로그램에서 OpenGL을 독립적으로 여러번 사용하기를 원할수 있다. 이 것을 위해 OpenGL은 자신의 모든 데이터를 저장하는 OpenGL Context를 만들고 이 Context로 OpenGL의 기능을 제어할 수 있다.



## 컨텍스트 정보 요청

OpenGL 컨텍스트에 대한 많은 정보가 요청될 수 있습니다.

### OpenGL 버전 번호

OpenGL 메이저 및 마이너 버전 번호를 얻으려면 다음 함수를 호출 할 수 있습니다.

```
glGetIntegerv ( GL_MAJOR_VERSION , *);
glGetIntegerv ( GL_MINOR_VERSION , *);
```

OpenGL 버전 3.0 이상에서 사용할 수 있습니다. 사용할 수없는 경우 대신 다음을 사용할 수 있습니다.

```
glGetString ( GL_VERSION );
```

리턴 된 문자열은 "<major version>. <minor version>"으로 시작합니다. 부 버전에 이어 또 다른 '.'가있을 수 있으며 그 다음에 벤더 고유의 빌드 번호가있을 수 있습니다. 문자열은 더 많은 콘텐츠를 가질 수 있습니다. 이는 완전히 공급 업체에 따라 다릅니다 (따라서 OpenGL 표준의 일부가 아닙니다).

예를 들어, 반환 된 문자열은 "2.0.6914 WinXP SSE / SSE2 / SSE3 / 3DNow!"와 같을 수 있습니다. 2.0은 지원되는 GL의 실제 버전 번호입니다. 6914는 드라이버 빌드 번호입니다. WinXP는 OS입니다. SSE / SSE2 / SSE3 / 3DNow! 드라이버가 사용할 수있는 CPU 기능입니다.

경우에 따라 [glGetString (GL_VERSION)](https://www.khronos.org/opengl/wiki/GLAPI/glGetString) 은 AGP, PCI 또는 PCIEx와 같이 사용 된 버스 유형도 반환합니다.

### 공급 업체 문자열

OpenGL 구현에는 구현 업체를 식별하는 데 사용되는 공급 업체 문자열이 관련되어 있습니다.

```
glGetString ( GL_VENDOR );
```

"ATI Technologies", "NVIDIA Corporation", "INTEL"등이 될 수 있습니다. 특정 공급 업체의 문자열이 향후 구현에서 동일하게 유지된다는 보장은 없습니다. Windows의 경우 "Microsoft"라고 표시되면 Windows 소프트웨어 렌더러 또는 Windows Direct3D 래퍼를 사용하고있는 것입니다. 이 경우 아직 그래픽 드라이버를 설치하지 않았을 것입니다.

### 렌더러 이름

이것은 구현에 의해 사용되는 렌더러의 이름입니다.

```
glGetString ( GL_RENDERER );
```

이 문자열은 종종 GPU의 이름입니다. Mesa3d의 경우에는 "Gallium 0.4 on NVA8"이됩니다. Windows Direct3D 래퍼가 사용되고있는 경우에도 "Direct3D"라고 말할 수 있습니다.

### 확장 프로그램 목록

확장 프로그램은 하나씩 쿼리 할 수 있습니다. 이렇게하려면 먼저 [glGetIntegerv (GL_NUM_EXTENSIONS, *)](https://www.khronos.org/opengl/wiki/GLAPI/glGetIntegerv) 를 사용하여 구현에서 지원하는 확장의 수를 가져옵니다. 그런 다음 이것으로 각 항목을 반복합니다.

```
glGetStringi ( GL_EXTENSIONS , k);
```

여기서 *k는* GL_NUM_EXTENSIONS 미만 값.

#### 기존 확장 목록



공백으로 구분 된 확장명 목록을 포함하는 문자열은 다음과 같이 쿼리 할 수 있습니다.

```
glGetString ( GL_EXTENSIONS );
```

### 컨텍스트 플래그

거기 [는 OpenGL 컨텍스트의 여러 종류](https://www.khronos.org/opengl/wiki/OpenGL_Context#Context_types) .

이 쿼리로 컨텍스트가 지원하는 프로필을 검색 할 수 있습니다.

```
glGetIntegerv ( GL_CONTEXT_PROFILE_MASK , *);
```

여기에는 GL_CONTEXT_CORE_PROFILE_BIT 또는 GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 비트가 포함될 수 있지만 동시에 둘 다 포함될 수는 없습니다.

컨텍스트의 다른 기능은 컨텍스트 플래그를 통해 감지 할 수 있습니다.

```
glGetIntegerv ( GL_CONTEXT_FLAGS , *);
```

사용 가능한 컨텍스트 플래그는 다음과 같습니다.

- GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT

  컨텍스트는 순방향 호환 컨텍스트입니다.

- GL_CONTEXT_FLAG_DEBUG_BIT

  컨텍스트는 디버그 컨텍스트입니다.

- GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT

  컨텍스트는 강력한 메모리 액세스 기능을 지원합니다.

- GL_CONTEXT_FLAG_NO_ERROR_BIT

  컨텍스트는 OpenGL 오류를보고하지 않습니다.

### 쉐이딩 언어 버전

구현에서 지원하는 GLSL의 기본 버전을 쿼리 할 수 있습니다.

```
glGetString ( GL_SHADING_LANGUAGE_VERSION를 );
```

버전 문자열은 컨텍스트 버전 문자열과 거의 동일한 형식입니다. 차이점은 부 버전은 항상 두 자릿수입니다.

#### 지원되는 GLSL 버전

|                  |      |      |
| :--------------- | ---- | ---- |
| 버전의 핵심      | 4.6  |      |
| 버전 이후의 코어 | 4.3  |      |

인덱싱 된 get을 통해 GLSL의 특정 버전에 대한 지원을 쿼리 할 수 있습니다. 지원 GLSL 버전의 수와 쿼리 [glGetIntegerv (GL_NUM_SHADING_LANGUAGE_VERSIONS, *)](https://www.khronos.org/opengl/wiki/GLAPI/glGetIntegerv) . 각 개별 버전은 색인 문자열에서 쿼리 할 수 있습니다



## 참고

<https://www.khronos.org/opengl/wiki/OpenGL_Context>