# Spring

## Bean

*Spring에서 애플리케이션의 백본을 형성하고 Spring IoC 컨테이너에 의해 관리되는 객체*

 **객체를 생성하지 않고 종속성을 정의하여 제어 반전을 가져온다 **



### 예제

#### **도메인 클래스**

클래스 선언이 있다고 가정하자.

```java
public class Company {
    private Address address;
 
    public Company(Address address) {
        this.address = address;
    }
 
    // getter, setter and other properties
}
```

이 클래스에는 *Address* 유형의 협력자가 필요하다  .

```java
public class Address {
    private String street;
    private int number;
 
    public Address(String street, int number) {
        this.street = street;
        this.number = number;
    }
 
    // getters and setters
}

```



#### **전통적 접근법**

일반적으로 클래스의 생성자를 사용하여 객체를 만든다.

```java
Address address = new Address("High Street", 1000);
Company company = new Company(address);
```

이 접근 방식에는 아무런 문제가 없지만 더 나은 방식으로 종속성을 관리하는 것이 좋다

수십 또는 수백 개의 클래스가있는 응용 프로그램을 상상해보아라. 때로는 전체 애플리케이션에서 클래스의 단일 인스턴스를 공유하기를 원할 때도 있고. 각 유스 케이스 별로 별도의 객체가 필요할 때가 있다

이러한 많은 수의 객체를 관리하는 것을 효과적으로 처리하는 방법이 있다. **이것이 제어 반전이다.**

자체적으로 의존성을 구성하는 대신 객체는 IoC 컨테이너에서 의존성을 검색 할 수 있다. **컨테이너에 적절한 구성 메타 데이터를 제공하기만 하면 된다.**



#### **빈 구성**

우선, *Company* 클래스에 *@Component* 어노테이션을 지정하자.

```java
@Component
public class Company {
    // this body is the same as before
}
```

다음은 IoC 컨테이너에 빈 메타 데이터를 제공하는 구성 클래스이다.

```java
@Configuration
@ComponentScan(basePackageClasses = Company.class)
public class Config {
    @Bean
    public Address getAddress() {
        return new Address("High Street", 1000);
    }
}

```

구성 클래스는 *Address* 유형의 빈을 작성한다  . 또한 *@ComponentScan* 어노테이션을 전달한다. 이 어노테이션은 컨테이너가 *Company* 클래스를 포함하는 패키지에서 Bean을 찾도록 지시한다 .

**Spring IoC 컨테이너가 이러한 유형의 객체를 구성하면 모든 객체는 IoC 컨테이너에 의해 관리되는 것으로 Spring Bean이라고 불린다.**



#### **IoC 내부 동작**

구성 클래스에 빈을 정의 **했으므로 AnnotationConfigApplicationContext 클래스 의 인스턴스가 있어야 컨테이너를 빌드 할 수 있다.**

```java
ApplicationContext context = new AnnotationConfigApplicationContext(Config.class);
```

빠른 테스트는 bean의 속성 값뿐만 아니라 존재를 확인한다.

```java
`Company company = context.getBean(``"company"``, Company.``class``);``assertEquals(``"High Street"``, company.getAddress().getStreet());``assertEquals(``1000``, company.getAddress().getNumber());`
```

결과는 IoC 컨테이너가 빈을 올바르게 생성하고 초기화했음을 증명한다.



## 참고

https://www.baeldung.com/spring-bean