10조 - 윤은영 교수님을 지켜라(타워 디펜스 게임)
by 정유철, 김다솜, 김현우, 황성민, 서상진

----디렉터리 내용물----
bin : 빌드시 일부 디버그용 파일이 들어갑니다.
documentations :게임을 제작하며 공유한 클래스 다이어그램과 각자 클래스의 사용설명서가 들어가있습니다.
.mdj파일은 starUML을 이용하여 읽습니다.
include : 헤더파일이 들어있는 폴더입니다.
src : .cpp파일이 들어있는 폴더입니다.
resources : 프로그램에 사용되는 image, sound리소스와, 그 작업파일이 들어있습니다. 
.psd파일은 Adobe Photoshop CS2를 이용해 읽습니다.
.flp 파일은 flstudio 11 또는 12를 이용해 읽습니다.


----빌드 방법----
이 프로젝트는 Qt 5.4.2 MSVC2010 OpenGL 32bit위에서 제작되었다.  
다른 버전에서도 컴파일 될 것으로 예상하지만, 테스트된 환경은 위의 환경뿐이다. 
컴파일을 하려면, sangjin.pro 파일을 Qt Creator로 열고,
 qt 5.4.2. MSVC2010 OpenGL 32bit킷을 선택하고 Release모드로 빌드한다. 
컴파일 후 생성되는 exe파일은 sangjin.pro와 같은 경로에 생성된다. 

**Qt Creator 위에서는 Build->run을 통해 잘 실행할 수 있지만, exe파일을 직접 실행할 경우
dll의 디렉터리가 제대로 설정되어있지 않아 실행이 안될 수 있습니다. 이 오류가 뜰 경우
아래의 배포 방법을 따라주세요.


----배포 방법----
생성된 Exe파일을 다른 환경에서도 실행되도록 Deploy하려면 약간 특별한 방법이 필요하다.
 (이 Deploy과정은 사용자의 Qt환경이 5.4.2 msvc2010 opengl임을 가정하고 기술되었으며, 다른 환경일 경우 경로를 적절하게 변경 바람.)
먼저 윈도우 “실행 창에 다음 커맨드를 친다. 

C:\Windows\System32\cmd.exe /A /Q /K C:\Qt\5.4\msvc2010_opengl\bin\qtenv2.bat 

그 다음 컴파일된 sangjin.exe와 resources 폴더를 deploy하고자 하는 빈 폴더로 옮기고. 
실행된 cmd창에서도 cd하여 그 디렉토리로 이동한다. 

그 다음 cmd창에 다음 커맨드를 친다.

c:\qt\5.4\msvc2010_opengl\bin\windeployqt.exe sangjin.exe

  그러면 자동으로 sanjin.exe의 실행에 필요한 동적 라이브러리가 현재 폴더로 자동 복사되며,
이 폴더를 배포하면 Qt가 설치되지 않은 다른 윈도우 환경에서도 실행할 수 있다. 


----라이센스----
이 프로젝트는 수정되지 않은 Qt 5.4.2 라이브러리를 사용하며,
LGPL v3을 따른다.


