# Spring

## @Autowired

Spring의 의존성 주입 기법

Spring이 협업 빈을 해석하여 빈에 주입



### *@Autowired* Annotations 활성화

```java
@Configuration
@ComponentScan("com.baeldung.autowire.sample")
public class AppConfig {}
```



### *@Autowired* 사용

Annotation 주입이 활성화 되면, Autowiring 필드, 세터, 생성자에 사용될 수 있다.

#### 필드에서 사용

```java
`@Component``(``"fooFormatter"``)``public` `class` `FooFormatter {` `    ``public` `String format() {``        ``return` `"foo"``;``    ``}``}`
```

```java
@Component
public class FooService {
    @Autowired
    private FooFormatter fooFormatter;
 
}
```

위의 예제에서, *FooService* 가 생성 되면 Spring은 *fooFormatter를 찾아서* 삽입한다.

#### 세터에서 사용

```java
public class FooService {
    private FooFormatter fooFormatter;
 
    @Autowired
    public void setFooFormatter(FooFormatter fooFormatter) {
            this.fooFormatter = fooFormatter;
    }
}
```

위의 예제에서, *FooService*를 만들 때 *FooFormatter* 인스턴스로 setter 메서드가 호출된다 .

#### 생성자에서 사용

```java
public class FooService {
    private FooFormatter fooFormatter;
 
    @Autowired
    public FooService(FooFormatter fooFormatter) {
        this.fooFormatter = fooFormatter;
    }
}
```

위 예제에서, *FooService* 가 생성 될 때 *FooFormatter* 의 인스턴스가 생성자에 인수로 삽입된다 .



### @Autowired 및 선택적 의존성

Spring 은 의존 빈이 생성 될 때 *@Autowired* 종속성이 사용 가능할 것으로 기대한다 . 프레임 워크가 연결을 위해 bean을 해석 할 수 없다면, 예외를 던져서 Spring 컨테이너가 성공적으로 시작되는 것을 막는다.

```tex
Caused by: org.springframework.beans.factory.NoSuchBeanDefinitionException: 
No qualifying bean of type [com.autowire.sample.FooDAO] found for dependency: 
expected at least 1 bean which qualifies as autowire candidate for this dependency. 
Dependency annotations: 
{@org.springframework.beans.factory.annotation.Autowired(required=true)}
```

이러한 일이 발생하지 않게하려면 빈을 선택적으로 지정할 수 있다.

```java
public class FooService {
    @Autowired(required = false)
    private FooDAO dataAccessor; 
     
}
```



### Autowire 모호성 제거

기본적으로 Spring은 *@Autowired* 항목을 유형별로 해결한다 . 컨테이너에서 같은 유형의 빈이 두 개 이상 있으면 프레임 워크는 autowiring에 둘 이상의 빈을 사용할 수 있다는 치명적인 예외를 던진다.

#### **@Qualifier에 의한 Autowiring**

*@Qualifie*r를 사용해 필요한 Bean 범위를 좁힐 수 있다

```java
@Component("fooFormatter")
public class FooFormatter implements Formatter {
    public String format() {
        return "foo";
    }
}
```

```java
@Component("barFormatter")
public class BarFormatter implements Formatter {
    public String format() {
        return "bar";
    }
}
```

```java
public class FooService {
    @Autowired
    private Formatter formatter;
}
```

스프링 컨테이너가 주입 할 수 있는 *Formatter의* 두 가지 구현이 있으므로 *FooService를* 생성 할 때 Spring은 *NoUniqueBeanDefinitionException* 예외를 던진다.

```tex
Caused by: org.springframework.beans.factory.NoUniqueBeanDefinitionException: 
No qualifying bean of type [com.autowire.sample.Formatter] is defined: 
expected single matching bean but found 2: barFormatter,fooFormatter
```

*@Qualifier*를 사용하여 범위를 좁히면 이 문제를 피할 수 있다 .

```java
public class FooService {
    @Autowired
    @Qualifier("fooFormatter")
    private Formatter formatter;
}
```

특정 구현의 이름으로 *@Qualifier* 를 지정하면 (이 경우 *fooFormatter)* , Spring이 같은 유형의 여러 빈을 찾을 때 모호성을 피할 수 있다.

*@Qualifier*의 값은 *FooFormatter* 구현 의 *@Component*에 선언된 이름과 일치한다.



#### **사용자 한정어에 의한 Autowiring**

Spring은 우리 자신의 *@Qualifier* 어노테이션 을 생성할 수 있게 해준다 . 맞춤 한정자를 만들려면 주석을 정의하고 아래 정의와 같이 *@Qualifier* 어노테이션을 만들어 준다.

```java
@Qualifier
@Target({
  ElementType.FIELD, ElementType.METHOD, ElementType.TYPE, ElementType.PARAMETER})
@Retention(RetentionPolicy.RUNTIME)
public @interface FormatterType {    
    String value();
}
```

일단 정의되면 *FormatterType* 을 다양한 구현에서 사용하여 사용자 지정 값을 지정할 수 있다.

```java
@FormatterType("Foo")
@Component
public class FooFormatter implements Formatter {
    public String format() {
        return "foo";
    }
}
```

```java
@FormatterType("Bar")
@Component
public class BarFormatter implements Formatter {
    public String format() {
        return "bar";
    }
}
```

구현에 어노테이션을 달면 맞춤 한정자 어노테이션을 아래와 같이 사용할 수 있다.

```java
@Component
public class FooService {
    @Autowired
    @FormatterType("Foo")
    private Formatter formatter;
}

```

*@Target* 어노테이션에 지정된 값은 한정자를 사용하여 주입 되는 곳을 표시할 수 있는 위치를 제한한다.



### **이름으로 Autowiring**

대체로 Spring은 빈 한정자 값으로 빈 이름을 사용한다.

그래서 빈 속성 이름을 정의하면 *fooFormatter* 와 *마찬가지로* Spring은 *FooFormatter* 구현 사이를 일치시키고 *FooService*가 생성 될 때 해당 특정 구현을 삽입한다.

```java
public class FooService {    
    @Autowired
    private Formatter fooFormatter;
}
```



## 참고

https://www.baeldung.com/spring-autowire