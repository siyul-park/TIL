# QT에서의 OpenGL Context

### QOpenGLContext Class

## 상세 설명

[QOpenGLContext의](https://doc.qt.io/qt-5/qopenglcontext.html) 클래스는에 렌더링 OpenGL을 가능하게 네이티브는 OpenGL 컨텍스트를 나타냅니다

[QOpenGLContext](https://doc.qt.io/qt-5/qopenglcontext.html) 는 기본 OpenGL 컨텍스트의 OpenGL 상태를 나타냅니다. 콘텍스트를 설정하려면 콘텍스트를 사용할 서페이스와 일치하도록 화면과 형식을 설정하고, 필요한 경우 [setShareContext](https://doc.qt.io/qt-5/qopenglcontext.html#setShareContext) () 로 다른 콘텍스트와 리소스를 공유하게하고 , 마지막으로 [create](https://doc.qt.io/qt-5/qopenglcontext.html#create) ( ). 컨텍스트가 성공적으로 초기화되었는지 확인 하려면 반환 값 또는 [isValid](https://doc.qt.io/qt-5/qopenglcontext.html#isValid) ()를 사용하십시오.

컨텍스트는 [makeCurrent](https://doc.qt.io/qt-5/qopenglcontext.html#makeCurrent) () 를 호출하여 주어진 표면에 대해 현재 상태로 만들 수 있습니다 . OpenGL 렌더링이 완료되면 [swapBuffers](https://doc.qt.io/qt-5/qopenglcontext.html#swapBuffers) ()를 호출 하여 표면의 전면 및 후면 버퍼를 교체하여 새로 렌더링 된 내용을 볼 수있게합니다. 특정 플랫폼을 지원 할 수 있으려면, [QOpenGLContext가](https://doc.qt.io/qt-5/qopenglcontext.html) 전화 할 것을 요구 [makeCurrent를](https://doc.qt.io/qt-5/qopenglcontext.html#makeCurrent) 호출 한 후, 다시 새로운 프레임을 렌더링 시작하기 전에 () [swapBuffers를](https://doc.qt.io/qt-5/qopenglcontext.html#swapBuffers) ().

응용 프로그램이 렌더링되지 않을 때와 같이 컨텍스트가 일시적으로 필요하지 않은 경우 자원을 확보하기 위해 컨텍스트를 삭제하는 것이 유용 할 수 있습니다. [aboutToBeDestroyed](https://doc.qt.io/qt-5/qopenglcontext.html#aboutToBeDestroyed) () 신호에 연결 하여 [QOpenGLContext](https://doc.qt.io/qt-5/qopenglcontext.html) 자체 와 다른 소유권으로 할당 된 자원을 [정리할 수](https://doc.qt.io/qt-5/qopenglcontext.html) 있습니다.

일단 [QOpenGLContext](https://doc.qt.io/qt-5/qopenglcontext.html) 가 만들어 지면 [QOpenGLFunctions](https://doc.qt.io/qt-5/qopenglfunctions.html) , [QOpenGLBuffer](https://doc.qt.io/qt-5/qopenglbuffer.html) , [QOpenGLShaderProgram](https://doc.qt.io/qt-5/qopenglshaderprogram.html) 및 [QOpenGLFramebufferObject](https://doc.qt.io/qt-5/qopenglframebufferobject.html) 와 같은 Qt의 OpenGL Enabler를 사용하여 플랫폼에 독립적 인 방식으로 렌더링 할 수 있습니다 . Qt 인 에이 블러를 사용하지 않고도 플랫폼의 OpenGL API를 직접 사용할 수도 있지만 잠재적으로는 이식성을 희생합니다. 후자는 OpenGL 1.x 또는 OpenGL ES 1.x를 사용하고자 할 때 필요합니다.



### 스레드 선호도

[QOpenGLContext](https://doc.qt.io/qt-5/qopenglcontext.html) 는 [moveToThread](https://doc.qt.io/qt-5/qobject.html#moveToThread) () 를 사용하여 다른 스레드로 이동할 수 있습니다 . [QOpenGLContext](https://doc.qt.io/qt-5/qopenglcontext.html) 객체가 속한 스레드와 다른 스레드에서 [makeCurrent](https://doc.qt.io/qt-5/qopenglcontext.html#makeCurrent) ()를 호출하지 마십시오 . 컨텍스트는 한 번에 하나의 스레드와 한 표면에 대해서만 현재 상태 일 수 있으며 스레드는 한 번에 하나의 컨텍스트 전류를 갖습니다.



### 컨텍스트 자원 공유

텍스쳐와 버텍스 버퍼 객체 같은 자원은 컨텍스트간에 공유 될 수 있습니다. 사용 [setShareContext를](https://doc.qt.io/qt-5/qopenglcontext.html#setShareContext) 호출하기 전에 () [생성](https://doc.qt.io/qt-5/qopenglcontext.html#create) 문맥이 자원을 공유하도록 지정하는 (). [QOpenGLContext는](https://doc.qt.io/qt-5/qopenglcontext.html) 내부적 으로 [shareGroup](https://doc.qt.io/qt-5/qopenglcontext.html#shareGroup) () 으로 액세스 할 수 있고 주어진 공유 그룹의 모든 컨텍스트를 찾는 데 사용할 수 있는 [QOpenGLContextGroup](https://doc.qt.io/qt-5/qopenglcontextgroup.html) 객체를 추적 합니다 . 공유 그룹은 성공적으로 초기화되고 공유 그룹의 기존 컨텍스트와 공유하는 모든 컨텍스트로 구성됩니다. 비공유 컨텍스트에는 단일 컨텍스트로 구성된 공유 그룹이 있습니다.



### 기본 프레임 버퍼

특정의 플랫폼에서는, 0 이외의 framebuffer가 현재의 표면에 응해 디폴트의 프레임 버퍼가됩니다. glBindFramebuffer (0)를 호출하는 대신 glBindFramebuffer (ctx-> [defaultFramebufferObject](https://doc.qt.io/qt-5/qopenglcontext.html#defaultFramebufferObject) ())를 사용하여 응용 프로그램이 다른 플랫폼간에 이식 가능한지 확인하는 것이 좋습니다 . 그러나 [QOpenGLFunctions :: glBindFramebuffer](https://doc.qt.io/qt-5/qopenglfunctions.html#glBindFramebuffer) ()를 사용하면 자동으로 수행됩니다.

### Public Types

| enum | **OpenGLModuleType** { LibGL, LibGLES } |
| ---- | --------------------------------------- |
|      |                                         |



### Public Functions

|                            | **QOpenGLContext**(QObject **parent* = nullptr)              |
| -------------------------- | ------------------------------------------------------------ |
| virtual                    | **~QOpenGLContext**()                                        |
| bool                       | **create**()                                                 |
| GLuint                     | **defaultFramebufferObject**() const                         |
| void                       | **doneCurrent**()                                            |
| QSet<QByteArray>           | **extensions**() const                                       |
| QOpenGLExtraFunctions *    | **extraFunctions**() const                                   |
| QSurfaceFormat             | **format**() const                                           |
| QOpenGLFunctions *         | **functions**() const                                        |
| QFunctionPointer           | **getProcAddress**(const QByteArray &*procName*) const       |
| QFunctionPointer           | **getProcAddress**(const char **procName*) const             |
| bool                       | **hasExtension**(const QByteArray &*extension*) const        |
| bool                       | **isOpenGLES**() const                                       |
| bool                       | **isValid**() const                                          |
| bool                       | **makeCurrent**(QSurface **surface*)                         |
| QVariant                   | **nativeHandle**() const                                     |
| QScreen *                  | **screen**() const                                           |
| void                       | **setFormat**(const QSurfaceFormat &*format*)                |
| void                       | **setNativeHandle**(const QVariant &*handle*)                |
| void                       | **setScreen**(QScreen **screen*)                             |
| void                       | **setShareContext**(QOpenGLContext **shareContext*)          |
| QOpenGLContext *           | **shareContext**() const                                     |
| QOpenGLContextGroup *      | **shareGroup**() const                                       |
| QSurface *                 | **surface**() const                                          |
| void                       | **swapBuffers**(QSurface **surface*)                         |
| QAbstractOpenGLFunctions * | **versionFunctions**(const QOpenGLVersionProfile &*versionProfile* = QOpenGLVersionProfile()) const |
| TYPE *                     | **versionFunctions**() const                                 |

- 31 public functions inherited from [QObject](https://doc.qt.io/qt-5/qobject.html#public-functions)



### Signals

| void | **aboutToBeDestroyed**() |
| ---- | ------------------------ |
|      |                          |

- 2 signals inherited from [QObject](https://doc.qt.io/qt-5/qobject.html#signals)



### Static Public Members

| bool                             | **areSharing**(QOpenGLContext **first*, QOpenGLContext **second*) |
| -------------------------------- | ------------------------------------------------------------ |
| QOpenGLContext *                 | **currentContext**()                                         |
| QOpenGLContext *                 | **globalShareContext**()                                     |
| void *                           | **openGLModuleHandle**()                                     |
| QOpenGLContext::OpenGLModuleType | **openGLModuleType**()                                       |
| const QMetaObject                | **staticMetaObject**                                         |
| bool                             | **supportsThreadedOpenGL**()                                 |



## 참조

<https://doc.qt.io/qt-5/qopenglcontext.html>