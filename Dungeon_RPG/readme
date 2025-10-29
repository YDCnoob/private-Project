#1 개요: 텍스트 기반 콘솔 RPG 게임으로, 플레이어는 몬스터를 처치하며 경험치를 쌓고 레벨업 하는 구조로 구성
    개발 기간: 2025.02~2025.06
    사용 언어: C
    개발 환경: Visual Studio 2022, VScode, GCC
    주요 기능:
		- 저장 / 불러오기 기능
		- 랭킹 시스템
		- 스킬 기반 전투
		- 낮/밤에 따른 경험치 및 골드 획득량 증가
		- 장비 강화

#2 프로젝트 구조
    /rpg_engine
     |- /engine
     |	|- battle.c / battle.h : 전투 로직
     |	|- character.c / character.h : 캐릭터 생성 및 전직
     |	|- engine.h : 공통 상수 및 매크로 정의
     |	|- monster.c / monster.h : 몬스터의 정보 관리
     |	|- save.c / save.h : 진행도 저장/불러오기
     |	|- skill.c / skill.h : 스킬 효과 및 데미지 계산
     |	|- town.c / town.h : 여관(체력 회복 및 낮/밤 시간 변화), 대장간(장비 강화) 담당
     |	|- utils.c / utils.h : 기타 유틸리티 함수
     |- /game
		|- main.c : 메인 게임 실행
		|- story.c / story.h : 스토리 관련 모듈 (개발 예정)

#3 주요 기능 요약
	전투 시스템: 플레이어와 몬스터의 공격/방어/스킬 구현
	경험치/레벨: 몬스터 처치 시 일정 경험치 누적/일정 수치 초과 시 레벨업
	상점: 무기 강화 기능
	저장/불러오기: 구조체를 파일로 저장하여 진행 데이터 유지
	낮/밤 시스템: 밤에는 경험치 및 골드 획득량 1.5배 증가

#4 핵심 코드 예시
	전투 중
	static void playerTurn(CHARACTER* c, MOP* m) {
    	if ((rand()%100) < 30) {
            int idx = rand() % MAX_SKILLS;
            SKILL* sk = &c->skills[idx];
            textcolor(SkyBlue);
            printf("★ 스킬 발동! [%s] ★\n", sk->name);
            textcolor(WHITE);
            sk->effect(c, m);
            Sleep(200);
            return;
        }
        int isCrit = 0;
        int dmg = calculateDamage(c, &isCrit);
        if (isCrit) printCritMessage(c->name, m->name, 1);
        m->hp = clampHP(m->hp - dmg);
        printf("%s에게 %d의 데미지! (남은 체력: %d)\n", m->name, dmg, m->hp);
    }

#5 실행 방법
	1. 컴파일: gcc engine/*.c game/*.c -o rpg.exe
	2. 실행: ./rpg.exe
	3. 또는 동봉된 Dungeon_RPG.exe 실행

#6 개선점 및 배운 점
	배운점
	1. 구조체와 헤더 파일을 통한 모듈화의 중요성
	2. fwrite / fread를 이용한 파일 입출력 구현
	3. 전투 루프 및 확률 기반 스킬 시스템 설계
	개선 예정
	1. 캐릭터 공격력 및 밸런스 조정
	2. GUI 기반 버전

#7 라이선스
	이 프로젝트는 개인 학습용으로 제작되었습니다.
	상업적 이용을 금하며, 코드 일부 인용 시 출처 표기를 권장합니다.

