#Student.py
class Student:
    def __init__(self,name,score) -> None:
        self.__name = name
        self.__score = score
        self.__GPA = -1
        if self.__score >=90 and self.__score <= 100:
            self.__GPA = 4.0
        if self.__score >=85 and self.__score <= 89:
            self.__GPA = 3.7
        if self.__score >=82 and self.__score <= 84:
            self.__GPA = 3.3
        if self.__score >=78 and self.__score <= 81:
            self.__GPA = 3.0
        if self.__score >=74 and self.__score <= 77:
            self.__GPA = 2.7
        if self.__score >=72 and self.__score <= 74:
            self.__GPA = 2.3
        if self.__score >=68 and self.__score <= 71:
            self.__GPA = 2.0
        if self.__score >=64 and self.__score <= 67:
            self.__GPA = 1.5
        if self.__score >=60 and self.__score <= 63:
            self.__GPA = 1.0
        if self.__score < 60:
            self.__GPA = 0.0


    def getScore(self) -> float:
        return self.__score
    
    def getName(self) -> str :
        return self.__name
    
    def getGPA(self) ->str:
        return str(self.__GPA)

        