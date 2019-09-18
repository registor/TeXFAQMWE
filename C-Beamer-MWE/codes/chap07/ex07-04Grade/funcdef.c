//函数定义
char GetGrade(int iScore)
{
    char chResult;

    if (iScore < 60){
        chResult = 'F';
    }
    else if (iScore < 70){
        chResult = 'D';
    }
    else if (iScore < 80){
        chResult = 'C';
    }
    else if (iScore < 90){
        chResult = 'B';
    }
    else if (iScore <= 100){
        chResult = 'A';
    }
    else{
        chResult = 0;
    }

    return chResult;
}

