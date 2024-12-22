# GameplayAbilitySystem
언리얼 게임플레이 프레임워크에 대한 예제

이 프로젝트에서는 기존에 만들었던 언리얼 프로젝트들을 다시 돌아보며<br/>
효율적인 액션 및 상태를 관리하기 위해 기초부터 심화까지 방법론을 제시한다.<br/>
멀티플레이 내용도 고려하고 있으며 최적화 등에 대한 이야기도 나누게 될 것이다.<br/>

### GAS란?
- 언리얼에서 주창하는 능력치, 버프, 액션 등을 효과적으로 관리하기 위한 유연한 프레임워크(..라고 주장한다.)
- 포트나이트에 적용된 프레임워크
- 게임 플레이 중 레벨업, 장비 업그레이드, 시간 경과에 따른 피해량 증가 등
- 동적으로 액션을 할당하고 해제하는 일련의 흐름을 의미함

### 만드는 방법의 기조
- `클래스의 분리` : 단일 책임의 원칙과 조금만 알기에 따라 액션과 이를 관리할 컴포넌트를 캐릭터와 분리한다.<br/>
![image](https://github.com/user-attachments/assets/8c22b2e9-1fb2-41cf-9fce-aa1481e71264)
<br/>

- `블루프린트와 유연한 연동` : 액션의 관리는 C++로 수행하되, 액션마다 가져야 할 저마다의 개성을 블프에서 재정의한다.<br/>
![image](https://github.com/user-attachments/assets/b81a63ab-0d69-44fb-9ae5-d66e552a350c)
<br/>

- `게임플레이 태그` : 계층화된 FName 태그 시스템으로 수많은 bool과 enum을 대체한다.</br>
![image](https://github.com/user-attachments/assets/1f129a7c-e55d-4060-b98b-64dfe129c318)
<br/>

### 문서
> 언리얼 기술 문서<br/>
> https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine?application_version=5.4<br/>
> 깃허브 문서<br/>
> https://github.com/tranek/GASDocumentation<br/>
> 프레임워크에 대한 이야기<br/>
> https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-framework-in-unreal-engine?application_version=5.4<br/>
> 샘플 프로젝트<br/>
> https://dev.epicgames.com/documentation/en-us/unreal-engine/sample-game-projects-for-unreal-engine?application_version=5.4<br/>

### 네트워크 상에서 서버/클라이언트가 소유한 객체들
- 플레이어컨트롤러는 로컬과 서버에만 존재. 다른 클라이언트에게는 없다.
- 플레이어스테이트는 어디에나 있다. 클라이언트는 다른 클라이언트의 플레이어스테이트도 갖고 있다.
- 플레이어스테이트는 캐릭터가 죽어도 유지되는 특징이 있다.
- 게임모드는 서버에만 존재하며, 게임스테이트는 게임모드의 정보들을 배열로 간직하고 있다.
- 게임모드의 데이터를 전달하려면 게임스테이트를 통해서 전달해야 한다.
![image](https://github.com/user-attachments/assets/b1070c04-3db8-44bd-9b58-1b9b9852980e)
