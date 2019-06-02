# GLFW에서의 OpenGL Context

### 컨텍스트 개체

윈도우 객체는 최상위 윈도우와 OpenGL 또는 OpenGL ES 컨텍스트를 캡슐화합니다. 그것은 [glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344) 로 생성되고 [glfwDestroyWindow](https://www.glfw.org/docs/latest/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2) 또는 [glfwTerminate로](https://www.glfw.org/docs/latest/group__init.html#gaaae48c0a18607ea4a4ba951d939f0901) 파괴된다

윈도우와 컨텍스트가 불가분의 관계로 연결되어 있으므로, 윈도우 객체는 컨텍스트 핸들 역할을 한다.

### 컨텍스트 생성 힌트

[glfwWindowHint를](https://www.glfw.org/docs/latest/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033) 사용하여 지정되는 여러 가지 힌트가 있으며, 어떤 종류의 컨텍스트가 만들어 [지는지](https://www.glfw.org/docs/latest/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033) 지정할수 있다

컨텍스트 개체 공유

[glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344) 를 사용하여 창과 OpenGL 또는 OpenGL ES 컨텍스트를 만들 때 컨텍스트가 해당 객체 (텍스처, 정점 및 요소 버퍼 등)를 공유해야하는 다른 창을 지정할 수 있다.

[GLFWwindow](https://www.glfw.org/docs/latest/group__window.html#ga3c96d80d363e67d13a41b5d1821f3242) * second_window = [glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344) (640, 480, "Second Window" , NULL, first_window);

## 오프 스크린 컨텍스트

GLFW는 연관된 창없이 컨텍스트를 만드는 것을 지원하지 않습니다. 그러나 숨겨진 윈도우가있는 컨텍스트는 [GLFW_VISIBLE](https://www.glfw.org/docs/latest/window_guide.html#GLFW_VISIBLE_hint) 윈도우 힌트 로 만들 수 있다 .

[glfwWindowHint](https://www.glfw.org/docs/latest/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033) ( [GLFW_VISIBLE](https://www.glfw.org/docs/latest/group__window.html#gafb3cdc45297e06d8f1eb13adc69ca6c4) , [GLFW_FALSE](https://www.glfw.org/docs/latest/group__init.html#gac877fe3b627d21ef3a0a23e0a73ba8c5) );



[GLFWwindow](https://www.glfw.org/docs/latest/group__window.html#ga3c96d80d363e67d13a41b5d1821f3242) * offscreen_context = [glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344) (640, 480, "" , NULL, NULL);

창을 표시 할 필요가 없으며 컨텍스트를 일반 오프 스크린 컨텍스트로 사용할 수 있다.

### 컨텍스트없는 Windows

[GLFW_CLIENT_API](https://www.glfw.org/docs/latest/window_guide.html#GLFW_CLIENT_API_hint) 힌트를 설정하여 컨텍스트 생성을 비활성화 할 수 있습니다 `GLFW_NO_API`. 컨텍스트없는 Windows는 [glfwMakeContextCurrent](https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157) 또는 [glfwSwapBuffers에](https://www.glfw.org/docs/latest/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14) 전달하면 안된다.

### 현재 상황

OpenGL 또는 OpenGL ES 호출을 만들기 전에 올바른 유형의 현재 컨텍스트가 있어야 한다. 컨텍스트는 한 번에 하나의 스레드에 대해서만 현재 상태 일 수 있으며 스레드는 한 번에 하나의 컨텍스트를 현재 사용할 수 있다.

[glfwMakeContextCurrent](https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157) 를 사용하여 창의 컨텍스트를 최신 상태로 [만듭니다](https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157) .

[glfwMakeContextCurrent](https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157) (윈도우);

현재 컨텍스트의 창은 [glfwGetCurrentContext에](https://www.glfw.org/docs/latest/group__context.html#gac84759b1f6c2d271a4fea8ae89ec980d) 의해 반환됩니다 .

[GLFWwindow](https://www.glfw.org/docs/latest/group__window.html#ga3c96d80d363e67d13a41b5d1821f3242) * window = [glfwGetCurrentContext](https://www.glfw.org/docs/latest/group__context.html#gac84759b1f6c2d271a4fea8ae89ec980d) ();

다음 GLFW 함수는 컨텍스트가 최신이어야 한다다. 현재 컨텍스트없이 이러한 함수를 호출하면 [GLFW_NO_CURRENT_CONTEXT](https://www.glfw.org/docs/latest/group__errors.html#gaa8290386e9528ccb9e42a3a4e16fc0d0) 오류가 발생한다 .

- [glfwSwapInterval](https://www.glfw.org/docs/latest/group__context.html#ga6d4e0cdf151b5e579bd67f13202994ed)
- [glfwExtensionSupported](https://www.glfw.org/docs/latest/group__context.html#ga87425065c011cef1ebd6aac75e059dfa)
- [glfwGetProcAddress](https://www.glfw.org/docs/latest/group__context.html#ga35f1837e6f666781842483937612f163)

### 버퍼 스와핑

GLFW 창은 기본적으로 이중 버퍼링 된다. 이는 두 개의 렌더링 버퍼가 있음을 의미한다.

전체 프레임이 렌더링되면, 렌더링 된 것을 표시하고 새 프레임을 렌더링하기 위해 후면 및 전면 버퍼를 교체해야 한다. 이것은 [glfwSwapBuffers](https://www.glfw.org/docs/latest/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14) 로 수행된다 .

[glfwSwapBuffers](https://www.glfw.org/docs/latest/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14) (윈도우);

### 로더 라이브러리로 확장로드

확장 로더 라이브러리는 OpenGL 및 OpenGL ES 확장과 최신 OpenGL 또는 OpenGL ES API 코어에 모두 액세스하는 가장 쉽고 효과적인 방법이다. 

다음 예제는 기쁘지만 모든 확장 로더 라이브러리는 비슷하게 작동한다.

적절한 현재 컨텍스트를 갖게되면 초기화해야한다.

window = [glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344) (640, 480, "My Window" , NULL, NULL);

**if** (! window)

{

​    ...

}



[glfwMakeContextCurrent](https://www.glfw.org/docs/latest/group__context.html#ga1c04dc242268f827290fe40aa1c91157) (윈도우);



gladLoadGLLoader ((GLADloadproc) [glfwGetProcAddress](https://www.glfw.org/docs/latest/group__context.html#ga35f1837e6f666781842483937612f163) );



## 참고

<https://www.glfw.org/docs/latest/context_guide.html>