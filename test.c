#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 주사위 오름차순 정렬 함수
void sort_dice(int dice[5]) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (dice[i] > dice[j]) {
                int temp = dice[i];
                dice[i] = dice[j];
                dice[j] = temp;
            }
        }
    }
}

// 엔터 키 입력 대기 함수 (클릭 한 번으로 굴리기 구현)
void wait_for_enter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 족보 판단 및 최고 점수/족보 이름 계산 함수
int evaluate_dice(int dice[5], char *best_hand_name) {
    int count[7] = {0}; // 1~6 주사위 눈별 개수
    for (int i = 0; i < 5; i++) {
        count[dice[i]]++;
    }

    int max_score = 0;
    strcpy(best_hand_name, "족보 없음");

    // 1. 요트 (Yacht): 5개 주사위 눈 모두 동일 -> 50점
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 5) {
            if (50 > max_score) {
                max_score = 50;
                strcpy(best_hand_name, "요트 (Yacht)");
            }
        }
    }

    // 2. 스트레이트 (Straight): 1-2-3-4-5 또는 2-3-4-5-6 -> 30점
    if ((count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1 && count[5] == 1) ||
        (count[2] == 1 && count[3] == 1 && count[4] == 1 && count[5] == 1 && count[6] == 1)) {
        if (30 > max_score) {
            max_score = 30;
            strcpy(best_hand_name, "스트레이트 (Straight)");
        }
    }

    // 3. 풀하우스 (Full House): 3개 동일 + 2개 동일 -> 25점
    int has_three = 0, has_two = 0;
    for (int i = 1; i <= 6; i++) {
        if (count[i] == 3) has_three = 1;
        if (count[i] == 2) has_two = 1;
    }
    if (has_three && has_two) {
        if (25 > max_score) {
            max_score = 25;
            strcpy(best_hand_name, "풀하우스 (Full House)");
        }
    }

    // 4. 포카드 (Four Card): 4개 이상 동일 -> 해당 4개 주사위 눈의 합
    for (int i = 1; i <= 6; i++) {
        if (count[i] >= 4) {
            int score = i * 4;
            if (score > max_score) {
                max_score = score;
                strcpy(best_hand_name, "포카드 (Four Card)");
            }
        }
    }

    // 5. 트리플 (Triple): 3개 이상 동일 -> 해당 3개 주사위 눈의 합
    for (int i = 1; i <= 6; i++) {
        if (count[i] >= 3) {
            int score = i * 3;
            if (score > max_score) {
                max_score = score;
                strcpy(best_hand_name, "트리플 (Triple)");
            }
        }
    }

    // 6. 원페어 (One Pair): 2개 이상 동일 -> 해당 2개 주사위 눈의 합
    for (int i = 6; i >= 1; i--) {
        if (count[i] >= 2) {
            int score = i * 2;
            if (score > max_score) {
                max_score = score;
                strcpy(best_hand_name, "원페어 (One Pair)");
            }
        }
    }

    return max_score;
}

// 주사위 5개를 굴리는 함수
void roll_dice(int dice[5]) {
    for (int i = 0; i < 5; i++) {
        dice[i] = (rand() % 6) + 1;
    }
    sort_dice(dice);
}

int main() {
    // 난수 생성기 초기화
    srand((unsigned int)time(NULL));

    int p1_total_score = 0;
    int p2_total_score = 0;
    int dice[5];
    char hand_name[50];

    printf("========================================\n");
    printf("         주사위 게임 '요트 (Yacht)'      \n");
    printf("========================================\n\n");
    printf("게임 규칙: 총 3라운드 진행 후 합산 점수가 높은 플레이어가 승리합니다.\n");
    printf("1번 플레이어부터 주사위를 굴립니다.\n\n");
    printf("Enter 키를 눌러 게임을 시작하세요...");
    wait_for_enter();

    // 총 3라운드 진행
    for (int round = 1; round <= 3; round++) {
        printf("\n========================================\n");
        printf("            [ 라운드 %d / 3 ]           \n", round);
        printf("========================================\n");

        // [1번 플레이어 턴]
        printf("\n[1번 플레이어] 님의 턴입니다.\n");
        printf("Enter 키를 눌러 주사위 5개를 한 번에 굴리세요...");
        wait_for_enter();

        roll_dice(dice);
        int p1_score = evaluate_dice(dice, hand_name);
        p1_total_score += p1_score;

        printf("🎲 주사위 결과: [%d] [%d] [%d] [%d] [%d]\n", dice[0], dice[1], dice[2], dice[3], dice[4]);
        printf("✨ 적용 족보  : %s (%d점)\n", hand_name, p1_score);
        printf("📊 1번 플레이어 누적 점수: %d점\n", p1_total_score);

        // [2번 플레이어 턴]
        printf("\n----------------------------------------\n");
        printf("[2번 플레이어] 님의 턴입니다.\n");
        printf("Enter 키를 눌러 주사위 5개를 한 번에 굴리세요...");
        wait_for_enter();

        roll_dice(dice);
        int p2_score = evaluate_dice(dice, hand_name);
        p2_total_score += p2_score;

        printf("🎲 주사위 결과: [%d] [%d] [%d] [%d] [%d]\n", dice[0], dice[1], dice[2], dice[3], dice[4]);
        printf("✨ 적용 족보  : %s (%d점)\n", hand_name, p2_score);
        printf("📊 2번 플레이어 누적 점수: %d점\n", p2_total_score);
    }

    // 최종 결과 출력 및 족보 점수 해석
    printf("\n========================================\n");
    printf("               최종 게임 결과           \n");
    printf("========================================\n");
    printf("🏆 1번 플레이어 최종 총점: %d점\n", p1_total_score);
    printf("🏆 2번 플레이어 최종 총점: %d점\n\n", p2_total_score);

    printf("📖 [ 족보 점수 산정 기준 해석 ]\n");
    printf(" - 요트 (Yacht)        : 주사위 5개 눈 동일 (50점)\n");
    printf(" - 스트레이트 (Straight): 1-2-3-4-5 또는 2-3-4-5-6 (30점)\n");
    printf(" - 풀하우스 (Full House): 3개 동일 + 2개 동일 (25점)\n");
    printf(" - 포카드 (Four Card)  : 주사위 4개 이상 동일 (해당 4개 눈의 합)\n");
    printf(" - 트리플 (Triple)     : 주사위 3개 이상 동일 (해당 3개 눈의 합)\n");
    printf(" - 원페어 (One Pair)   : 주사위 2개 이상 동일 (해당 2개 눈의 합)\n");
    printf(" ※ 여러 족보에 해당될 경우 가장 높은 점수의 족보가 자동으로 적용되었습니다.\n");
    printf("----------------------------------------\n");

    // 승자 판정 문구 출력
    if (p1_total_score > p2_total_score) {
        printf("🎉 [1번 플레이어] 님이 승리하셨습니다! 축하합니다! 🎉\n");
    } else if (p2_total_score > p1_total_score) {
        printf("🎉 [2번 플레이어] 님이 승리하셨습니다! 축하합니다! 🎉\n");
    } else {
        printf("🤝 동점으로 [무승부]입니다! 🤝\n");
    }
    printf("========================================\n");

    return 0;
}
