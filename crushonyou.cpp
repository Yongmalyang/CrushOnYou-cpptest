#include <iostream>
#include <stdio.h>
using namespace std;

int randNum = 30;//랜덤

int turn;//현재 턴 수
int maxTurn = 15;//제한 턴 수

int lovers_len = 6; int places_len = 6; int reason_len = 9;

string lovers[6] = {"red", "blue", "yellow", "green", "pink", "black"};
string places[6] = {"콘서트장 백스테이지", "도서관 책장 뒤", "아쿠아리움", "그의 집 앞", "전망대", "고급 레스토랑"};
//피크닉, 비행기 안, 등등...
string reason[9] = {"첫사랑", "짝사랑", "질투", "한눈에 반한 이상형과 이어지", "소꿉친구를 사랑", "재회", "결혼", "홧김에 고백", "스며들어서 좋아"};

//후보, 장소, 이유는 각각 셔플된 후 같은 인덱스에 있는 애들끼리 매칭됨.
//그 중 정답이 4라면, 4번 인덱스의 후보, 4번 인덱스의 장소, 4번 인덱스의 이유가 정답이 됨

bool first_meet[6]; //첫만남인지 아닌지

int place_to_be[6];
//각 인물이 어디에 있는지.. 결정
//예: place_to_be[0] = 3이라면 red는 3번장소, 즉 그의 집앞에 있음
int placeInput;//이번 턴에 가볼 장소
int loverInput;//이번 턴에 간 장소에서 대화할 사람
int whosHereCnt=0;//이번 턴의 장소에 몇 명 있는지

int answer;//최종 답
int fake_lover; //페이크 러버

bool isGameOver=false;

void setGame()//세팅부터!
{
    for(int i=0;i<places_len;i++) { place_to_be[i]=i; }//각 턴에 인물들이 어디에 있는지, 초기화해두기

    for(int i=0; i<randNum; i++)//셔플
    {
        int randNum1 = rand() % lovers_len;
        int randNum2 = rand() % lovers_len;
        string temp;
        temp = lovers[randNum1];
        lovers[randNum1] = lovers[randNum2];
        lovers[randNum2] = temp;
    }

    for(int i=0; i<randNum; i++)//셔플22
    {
        int randNum1 = rand() % places_len;
        int randNum2 = rand() % places_len;
        string temp;
        temp = places[randNum1];
        places[randNum1] = places[randNum2];
        places[randNum2] = temp;
    }

    for(int i=0; i<randNum; i++)//셔플33
    {
        int randNum1 = rand() % reason_len;
        int randNum2 = rand() % reason_len;
        string temp;
        temp = reason[randNum1];
        reason[randNum1] = reason[randNum2];
        reason[randNum2] = temp;
    }

    answer = rand() % lovers_len;//정답은??!
    while(1)
    {
        fake_lover = rand() % lovers_len;
        if(fake_lover!=answer) break;
    }

    for(int i=0; i<lovers_len; i++)
    {
        first_meet[i] = false;
    }

}

void shufflePlace() // 인물들 장소 이동
{
    for(int i=0; i<places_len; i++)
    {
        place_to_be[i] = rand() % places_len;
    }
}

void giveHint_normal(int lover_input) //대화 이후 힌트를 얻는 장소, 평일 중에
{
    int hintInput_place;
    int hintInput_reason;

    cout << "그래서, 어느 장소에 관해 궁금한 건데?\n";
    for(int i=0; i<places_len; i++)
    {
        cout << places[i] << ": "<<i<<"번 선택\n";

    }
    cin >> hintInput_place;
    if(hintInput_place == lover_input)
    {
        cout << places[hintInput_place] <<"? 당연히 좋아하지. 내가 제일 좋아하는 장소야!\n\n";
    }
    else
    {
        cout << places[hintInput_place] <<"(이)라... 거긴 내가 그렇게 좋아하는 곳은 아니야.\n\n";
    }

    cout << "또 궁금한 거 있어? 좀 더 흥미로운 정보를 줄 수도 있는데.... (어떤 내용에 관해 질문하시겠습니까?)\n";
    for(int i=0; i<reason_len; i++)
    {
        cout << reason[i] << ": "<<i<<"번 선택\n";
    }

    cin >> hintInput_reason;

    if(hintInput_reason >= lovers_len)
    {
        cout << "어.. 잘 모르겠네. 아마 "<<reason[hintInput_reason]<<"하(고 싶)은/는 사람은 우리 중에는 없을 거야.\n\n";
    }
    else if(hintInput_reason == lover_input)
    {
        cout << "글쎄... 나와 살짝 관련이 있을 수도? \n\n";
    }
    else
    {
        cout << "음, 일단 나는 해당되지 않아. 잘못 짚은 것 같은데?\n\n";
    }

}

void giveHint_weekend(int lover_input)
{
    int weekendInput;

    cout << "0: "<<lovers[lover_input]<<"(이)가 좋아하는 장소\n";
    cout << "1: "<<lovers[lover_input]<<"(이)의 좋아하는 사람과의 관계\n";
    cout << "2: 비밀 편지에 대한 내용\n\n";
    cout << "무엇에 대한 질문을 하시겠습니까? \n";
    cin >> weekendInput;

    switch(weekendInput)
    {
        case 0: //장소 질문
        cout << "내("<<lovers[lover_input]<<")가 좋아하는 장소? 아무래도 " << places[lover_input] <<"겠지?\n";
        break;

        case 1: //이유 질문
        cout << "단도직입적으로 물어보는구나. 사실 나("<<lovers[lover_input]<<")는 " << reason[lover_input] << "하(고 싶)은/는 사람이 있어...\n";
        break;

        case 2: //편지 질문
        if(loverInput==answer){ cout << "다 알고 있었구나.\n"; }
        else if(loverInput!=answer){ cout << "편지? 무슨 편지를 말하는 거야?\n"; }
        break;

        default: break;
    }
}

void showAnswer() //개발자확인용
{
    cout << "~~ 아래는 정답 입니다 ~~\n\n";
    for(int i=0; i<lovers_len; i++)
    {
        cout << i<<": "<<lovers[i]<<", "<<places[i]<<", "<<reason[i]<<"\n";
    }
    cout << "\n최종 답: "<<places[answer] << "에서 " << lovers[answer] << "(이)가 기다린다. 고백의 이유는 " << reason[answer]<<"\n";
    cout << "페이크 러버: "<< lovers[fake_lover] <<"\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void inputFinalAnswer()
{
    int finalInput_lover, finalInput_place, finalInput_reason;

    cout << "~~~~~ 최종 정답을 입력하세요. ~~~~~\n";
    cout << "[비밀편지의 주인공은?] \n";
    for(int k=0; k<lovers_len; k++) { cout <<  k << ": " << lovers[k] << "\n"; }
    cin >> finalInput_lover;
    if(finalInput_lover==answer)
    {
        cout << "정답입니다. \n\n[비밀편지의 프로포즈 장소는?]\n";
        for(int j=0; j<places_len; j++) { cout <<  j << ": " << places[j] << "\n"; }
        cin >> finalInput_place;
        if(finalInput_place==answer)
        {
            cout << "정답입니다. \n\n[비밀편지의 주인공이 당신에게 고백하는 이유는?]\n";
            for(int i=0; i<reason_len; i++){ cout << reason[i] << ": "<<i<<"번 선택\n"; }
            cin >> finalInput_reason;
            if(finalInput_reason==answer)
            {
                cout << "정답입니다. 축하합니다! Game Clear!! 사용한 턴 수: " << turn+1 << "\n\n";
                isGameOver=true;
            }
            else{ cout << "틀렸습니다. Game Over."; isGameOver=true;}
        }
        else{ cout << "틀렸습니다. Game Over."; isGameOver=true;}
    }
    else{ cout << "틀렸습니다. Game Over."; isGameOver=true;}
}

void playTurn_normal()
{
    cout << "[선택 가능 장소] \n";
    for(int j=0; j<places_len; j++)
    {
        cout <<  j << ": " << places[j] << "\n";
    }
    cout << "\n어디로 가시겠습니까? \n";
    cin >> placeInput;
    cout << "\n\n당신을 기다리고 있던 사람(들): \n";

    for(int i=0; i<places_len; i++)
    {
        if(place_to_be[i]==placeInput)
        {
            cout << lovers[i] << "(" << i << "번 선택) ";
            whosHereCnt++; //이 장소에 있는 사람++
        }
    }

    if(whosHereCnt!=0)
    {
        cout << "\n\n누구와 대화하시겠습니까?\n";
        cin >> loverInput;
        if(!first_meet[loverInput])
        {
            if(loverInput==answer || loverInput==fake_lover)
            {
                cout << "\n그래, 맞아. 널 좋아해. \n\n";
            }
            else
            {
                cout << "\n널 좋아하느냐고? 음... 이거 좀 민망한걸.\n\n";
            }
            first_meet[loverInput] = true;
        }
        giveHint_normal(loverInput);
        cout << "정답을 입력하시겠습니까? 정답 입력은 단 한번뿐이며, 틀리면 게임오버입니다. \n(YES면 1번, NO면 0번)\n";
        int stopInput;
        cin >> stopInput;
        if(stopInput==1)
        {
            inputFinalAnswer();
        }
    }
    else
    {
        cout << "이곳에는 아무도 없습니다. 이번 턴은 수확 없이 진행됩니다.\n\n";
    }

    whosHereCnt=0;
    if(!isGameOver){cout << "(이번 턴이 종료되었습니다.)\n\n";}
}

void playTurn_weekend()
{
    cout << "오늘은 주말입니다. 메신저로 원하는 사람과 마음껏 대화하세요!\n[대화 가능 인물]\n";
    for(int k=0; k<lovers_len; k++) { cout <<  to_string(k) << ": " << lovers[k] << "\n"; }

    cout << "\n\n누구와 대화하시겠습니까?\n";
    cin >> loverInput;
    if(!first_meet[loverInput])
    {
        if(loverInput==answer || loverInput==fake_lover){ cout << "\n그래, 맞아. 널 좋아해. \n\n"; }
        else { cout << "\n널 좋아하느냐고? 음... 이거 좀 민망한걸.\n\n"; }
        first_meet[loverInput] = true;
    }
    giveHint_weekend(loverInput);
    cout << "정답을 입력하시겠습니까? 정답 입력은 단 한번뿐이며, 틀리면 게임오버입니다. \n(YES면 1번, NO면 0번)\n";
    int stopInput;
    cin >> stopInput;
    if(stopInput==1)
    {
        inputFinalAnswer();
    }
    if(!isGameOver){cout << "(이번 턴이 종료되었습니다.)\n\n";}

}

void showPrologue()
{
    cout << "[안녕, 우연히 이곳에서 너를 만나게 되다니 믿기지 않아. 이런 게 운명이라는 거겠지. "
            "이 기회로 나는 너에게 전하지 못했던 말을 전하고 싶어. 너도 같은 마음이라면 나를 알아봐 줘.]\n\n";
    cout << "편지를 받은 지 1일차. 졸업식은 14일 후인데... 그 전까지 이 사람을 찾을 수 있을까?\n\n";
}

int main()
{
    setGame();
    showPrologue();
    for(turn=0; turn<maxTurn; turn++)
    {
        shufflePlace();
        cout << "~~~~~"<< turn+1 <<"번째 턴~~~~~\n";
        if(turn==5 || turn==6 || turn==12 || turn==13) { playTurn_weekend(); } //주말
        else if(turn==14) { inputFinalAnswer(); } //마지막턴
        else{ playTurn_normal(); }
        if(isGameOver) break;
    }
    showAnswer();
}
