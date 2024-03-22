# Union-Find

## Disjoint Set이란
서로 중복되지 않는 부분 집합들 로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조


## Union-Find란

Disjoint Set을 표현할 때 사용하는 알고리즘

아래의 세 가지 연산을 이용하여 Disjoint Set을 트리 구조로 표현한다.

두개의 다른 집합을 O(1)에 합칠수 있고, O(logN) 만에 해당 값이 포함된 집합을 찾을 수 있음

## Union-Find의 연산
make-set(x)

- 초기화
- x를 유일한 원소로 하는 새로운 집합을 만든다.

union(x, y)

- 합하기
- x가 속한 집합과 y가 속한 집합을 합친다.

find(x)

- 찾기

- x가 속한 집합의 대표값(루트 노드 값)을 반환한다.
  
# Reference
https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html

