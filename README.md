# ft_container
## 목표 : STL 자료구조 공부와 구현
- C++ STL의 여러가지 컨테이너 타입을 구현하세요.
- 각 컨테이너마다 적절한 이름을 붙인 클래스 파일을 제출하세요.
- 네임스페이스는 항상 ft를 사용하세요.
- 컨테이너는 ft::<contatiner>로 테스트 됩니다.
- C++98로 코딩하는 거니까 컨테이너의 새로운 기능들은 구현하지마세요.
- 모든 옛날 기능들(도태된 기능 포함)은 구현하세요.

## 필수 충족 사항 
| 필수 충족사항 | 
| --- |
| - 컨테이너들을 구현하고, 필요한 파일들 <container>.hpp을 제출하세요. |
| - 멤버 함수 get_allocator는 안해도 되고 |
| - 나머지 멤버 함수들은 하세요. |
| - Non-member 오버로드도 하세요. |
| - 만약 컨테이너에 iterator 시스템이 있으면 반드시 재구현 하세요. |
| - 구현할 내용을 https://www.cplusplus.com/에서 참고할 수 있습니다. |
|  -기존 컨테이너에서 제공되는 것 이외에 추가적인 public function을 구현해 넣지 마세요. |
| - 그 이외의 모든 것은 반드시 private 아니면 protected여야 합니다. |
| - 모든 public fuction, public variable은 근거가 있어야 합니다. |
| - non-member 오버로드는 friend 키워드 사용 가능!!! |
| - 모든 friend의 사용이 근거가 있어야하며, 평가중에 확인할 것임. |
| - 아래와 같은 컨테이너들과 그와 관련된 함수들을 제출하세요. |
| - STL 사용을 금지하고 STD라이브러리 사용은 가능합니다 |

## Vector의 구조와 특징
### 벡터의 구조 
이미지 출처 : https://jhnyang.tistory.com/230  
![2022-11-17 오후 9-26-53](https://user-images.githubusercontent.com/57505385/202446239-59f1b339-2861-4495-8274-9165e8df3709.png)

### 벡터의 특징
- 벡터의 메모리 구조 특징은 배열과 같습니다. 연속된 메모리 공간의 공간 할당입니다
- 중간에 위치한 데이터의 삽입, 삭제시 데이터를 1칸씩 밀거나 당겨야해서 최악의경우 거의 O(n)번의 연산이 필요함

### 벡터의 장점 
- 익숙한 배열 개념
- index에 직접적으로 접근이 가능

### 벡터의 단점
- 중간에 데이터를 삭제하거나 삽입하는 경우가 빈번하지 않을때 
- 중간에 위치한 데이터의 삽입,삭제시 데이터를 1칸씩 밀거나 당겨야해서 최악의경우 거의 O(n)번의 연산이 필요함

## Stack
- 타 컨테이너를 이용하여 top에서는 입,출력이 이루어지게 만든것 (실제 구현도 그렇게 되어있음)

## Map의 구조와 특징   
### Map의 개념도  
- 출처 : https://blog-of-gon.tistory.com/187  
![맵](https://user-images.githubusercontent.com/57505385/202449693-f6466f4f-bfd0-4bcc-a95d-53088b9b7a8b.png)  
### Map의 구조
- C++ STL의 map은 rbtree로 제작되어있습니다  
- RBTree의 구현은 https://www.cs.usfca.edu/~galles/visualization/RedBlack.html 이곳의 시뮬레이터를 보며 구현하였습니다
- 출처 : https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC
![rbtree](https://user-images.githubusercontent.com/57505385/202450102-19cdc7c9-23ae-415e-b2eb-5d276a38583f.png)
### Map의 특징
- Key와 Value로 구성
- Key의 중복을 허용하지 않음
- RBtree가 가지는 특성 (데이터 삽입,삭제시 재정렬이 이루어짐)

