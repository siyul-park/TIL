# gRPC란?

모든 환경에서 실행할 수있는 최신 오픈 소스 고성능 RPC (원격 프로 시저 호출) 프레임 워크.



## protocol buffer

**gRPC**는 IDL(Interface Definition Language)로 **protocol buffer**를 사용한다.

**protocol buffer**는 **직렬화 데이터 구조**이다. 어떤 언어나 플랫폼에서도 통신 프로토콜이나 데이터 저장을 사용할 때, 구조화된 데이터를 전환하게 해주는 방법이다.

직렬화의 종류에는 대표적으로 Json과 XML이 있다.

프로토콜 버퍼로 작업할 때는 `proto file`에서 직렬화하려는 데이터 구조를 정의한다.
프로토콜 버퍼는 하나의 프로그래밍 언어가 아니라 여러 프로그래밍 언어를 지원하기 때문에, 특정 언어에 종속성이 없는 형태로 데이터 타입을 정의하게 되는데, 이 파일을 `proto file`이라고 한다.

프로토콜 버퍼 데이터는 일련의 '이름-값'의 쌍을 포함하는 작은 논리적 레코드인 **메시지**로 구성된다.

```proto
message Person {
  string name = 1;
  int32 id = 2;
  bool has_ponycopter = 3;
}
```

이렇게 작성된 `proto file`을 `protoc 컴파일러`로 컴파일 하면 데이터에 접근할 수 있는 각 언어에 맞는 형태의 **데이터 클래스**를 생성해준다. 만들어진 클래스는 각 필드를 위한 접근자 뿐 아니라 전체 구조를 바이트로 직렬화하거나 바이트로부터 전체 구조를 파싱하는 메서드들을 제공한다.

기존의 HTTP/1.1 기반 Rest API 에 비해서 다음과 같은 장점을 가진다

- 직렬화/비직렬화 과정이 JSON 에 비해서 빠르다
- IDL이기 때문에 코드가 스팩을 바로 정의한다
- HTTP/2를 사용하기 때문에 네트워크 비용이 HTTP/1.1 보다 빠르고(바이너리로 전달), 보다 많은 기능을 사용 가능하다



## RPC(Remote Communication Mechanism)

RPC(원격 프로시저 호출)는 한 프로그램이 네트워크의 세부 정보를 이해하지 않고도 네트워크 안의 다른 컴퓨터에 있는 프로그램에서 서비스를 요청하는 프로토콜. RPC는 client-server 모델을 사용한다. 클라이언트에서 서비스를 요청(function call)하면, 서버에서 서비스를 제공한다.



## 참고

https://grpc.io/docs/what-is-grpc/introduction/

https://velog.io/@dojun527/gRPC%EB%9E%80

https://chacha95.github.io/2020-06-15-gRPC1/

https://developers.google.com/protocol-buffers/docs/overview

https://www.andrewconnell.com/blog/grpc-and-protocol-buffers-an-alternative-to-rest-apis-and-json/

