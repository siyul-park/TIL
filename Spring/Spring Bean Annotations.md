# Spring

## Spring Bean Annotations

*Spring* 컨테이너에서 빈을 설정하는 방법

1. XML 구성을 사용
2. 설정 클래스에서 *@Bean* 어노테이션을 사용하여 bean을 선언
3. org.springframework.stereotype* 패키지 의 주석 중 하나를 사용하여 클래스를 표시 하고 나머지는 구성 요소 검색으로 남겨 둠



### **구성 요소 스캐닝**

컴포넌트 스캐닝이 가능하다면 Spring은 bean을위한 패키지를 자동으로 스캔할 수있다.

*@ComponentScan* **은 어노테이션 구성을 사용하여 클래스를 검색** 할 **패키지를 구성힌다** . 기본 패키지 이름을 *basePackages* 또는 *value* 인수 중 하나를 사용하여 직접 지정할 수 있다 ( *value* 는 *basePackages* 의 별칭 ).

```java
@Configuration
@ComponentScan(basePackages = "com.baeldung.annotations")
class VehicleFactoryConfig {}
```

또한 *basePackageClasses* 인수를 사용하여 기본 패키지의 클래스를 가리킬 수 있다 .

```java
@Configuration
@ComponentScan(basePackageClasses = VehicleFactoryConfig.class)
class VehicleFactoryConfig {}
```

두 인수는 배열이므로 각각에 대해 여러 패키지를 제공할 수 있다.

인수가 지정되지 않으면 스캔은 *@ComponentScan* 어노테이션이있는 클래스가 있는 동일한 패키지에서 발생한다 .

*@ComponentScan* 은 Java 8 반복 어노테이션 기능을 사용합니다. 즉, 클래스를 여러 번 표시할 수 있다.

```java
@Configuration
@ComponentScan(basePackages = "com.baeldung.annotations")
@ComponentScan(basePackageClasses = VehicleFactoryConfig.class)
class VehicleFactoryConfig {}
```

또는 *@ComponentScans* 를 사용하여 여러 개의 *@ComponentScan* 구성 을 지정할 수 있습니다.

```java
@Configuration
@ComponentScans({ 
  @ComponentScan(basePackages = "com.baeldung.annotations"), 
  @ComponentScan(basePackageClasses = VehicleFactoryConfig.class)
})
class VehicleFactoryConfig {}
```

 **XML 구성을 사용** 할때 다음과 같이 쉽게 할수도 있다

```xml
<context:component-scan base-package="com.baeldung" />
```

### **@Component**

*@Component* 는 클래스 수준의 어노테이션이다. 컴포넌트 스캔 중에 **Spring Framework는 @Component로** **주석 처리 된 클래스를 자동으로 감지** 한다.

예 :

```java
@Component
class CarUtility {
    // ...
}
```

기본적으로이 클래스의 빈(Bean) 인스턴스는 소문자 이니셜이있는 클래스 이름과 동일한 이름을 가진다. 그 위에, 우리는 이 주석 의 선택적 *값* 인수를 사용하여 다른 이름을 지정할 수 있다 .

이후 *@Repository* , *@Service* , *@Configuration* 및 *@Controller는* 모든 메타 어노테이션이다 *@Component는* , 그들은 행동을 명명 같은 빈(Bean)을 공유 할 수 있습니다. 또한 Spring은 구성 요소 검색 프로세스 중에 자동으로 선택ㅏㄴ다.

### **@Repository**

DAO 또는 리포지토리 클래스는 대개 응용 프로그램의 데이터베이스 액세스 계층을 나타내며 *@Repository* 로  어노테이션을 추가 해야 한다.

```java
@Repository
class VehicleRepository {
    // ...
}
```

이 주석을 사용하는 한 가지 장점 **은 자동 보존 예외 변환이 활성화되어 있다는 것** 이다. Hibernate와 같은 영속 프레임 워크를 사용할 때, *@Repository로* 주석 처리 된 클래스 내에서 발생 된 네이티브 예외 는 자동으로 Spring의 *DataAccessExeption* 의 서브 클래스로 변환된다 .

**예외 변환을 가능하게하려면** 우리 고유의 *PersistenceExceptionTranslationPostProcessor* Bean 을 선언해야 한다 .

```java
@Bean
public PersistenceExceptionTranslationPostProcessor exceptionTranslation() {
    return new PersistenceExceptionTranslationPostProcessor();
}
```

대부분의 경우 Spring은 위의 단계를 자동으로 수행한다

또는 XML 구성을 통하여 한다

```java
<bean class=
  "org.springframework.dao.annotation.PersistenceExceptionTranslationPostProcessor"/>
```

### **@Service**

응용 프로그램 의 **비즈니스 로직** 은 대개 서비스 계층 내에 있다. 따라서 *@Service* 어노테이션을 사용하여 클래스가 해당 계층에 속해 있음을 나타낸다.

```java
@Service
public class VehicleService {
    // ...    
}
```

## **6. @Controller**

*@Controller* 는 **Spring MVC** 에서이 클래스가 **컨트롤러** 역할을한다는 것을 Spring Framework에 알려주는 클래스 레벨 어노테이션이다 .

```java
@Controller
public class VehicleController {
    // ...
}
```

## 7. *@Configuration*

*설정* 클래스는 *@Bean으로* 어노테이션 처리 된 **bean 정의 메소드를 포함** 할 수 **있다** :

```java
@Configuration
class VehicleFactoryConfig {
 
    @Bean
    Engine engine() {
        return new Engine();
    }
 
}
```

## **8. 스테레오 타입 어노테이션 및 AOP**

Spring 스테레오 타입 어노테이션을 사용할 때 특정 스테레오 타입을 가진 모든 클래스를 대상으로하는 pointcut을 만드는 것은 쉽다.

예를 들어 DAO 계층에서 메소드의 실행 시간을 측정한다고 가정하자. *@Repository* 스테레오 타입 을 이용하여 다음과 같은 aspect (AspectJ 어노테이션 사용)를 만들 것이다 :

```java
@Aspect
@Component
public class PerformanceAspect {
    @Pointcut("within(@org.springframework.stereotype.Repository *)")
    public void repositoryClassMethods() {};
 
    @Around("repositoryClassMethods()")
    public Object measureMethodExecutionTime(ProceedingJoinPoint joinPoint) 
      throws Throwable {
        long start = System.nanoTime();
        Object returnValue = joinPoint.proceed();
        long end = System.nanoTime();
        String methodName = joinPoint.getSignature().getName();
        System.out.println(
          "Execution of " + methodName + " took " + 
          TimeUnit.NANOSECONDS.toMillis(end - start) + " ms");
        return returnValue;
    }
}

```

이 예에서는 *@Repository로* 어노테이션 처리 된 클래스의 모든 메소드와 일치하는 pointcut을 작성했다 . 우리는 *@Around* advice를 사용하여 그 pointcut을 타깃으로하고 인터셉트 된 메소드 호출의 실행 시간을 결정했다.

이 접근 방식을 사용하여 로깅, 성능 관리, 감사 또는 기타 동작을 각 응용 프로그램 계층에 추가 할 수 있다.